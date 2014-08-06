/*
本文件实现和外部模块的通信、用户定义任务的执行
系统开始运行后，首先是握手
握手成功后进行普通的节点通讯
全部握手成功才可以运行任务
执行顺序是
...
输入输出
任务执行
输入输出
...
*/
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include "pcap.h"
#include <QMutex>
#include <QWaitCondition>
#include <QTime>
#include <QTextStream> 
#include "mainloop.h"
#include "sys.h"
#include "device.h"
#include "controltask.h"
#include "basicservice.h"
#include "lua.hpp"
#include "econwin.h"
#include "luaview.h"

extern lua_State* L;

extern bool threadrun;
extern bool comopen;

//是否全部握手过
bool allshake = false;

//握手包长度，这个是双方约定的数量，之所以定义大一点是因为握手时可能会做很多的事情
static int shakehandlen = 1500;

//事件消息传递对象
extern pcap_t *adhandle;

//lua不支持多线程，采用独占锁
QMutex luamutex;


QMutex waitmutex;
QWaitCondition etherwait;
int cnt = 0;

static unsigned int failcnt = 0;//通讯失败计数
static unsigned int successcnt = 0;//通讯成功计数
static unsigned char senddata[1500];


/* prototype of the packet handler */
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);


extern unsigned int aint;

//通信节点数组
QList<struct tcommnode> commnodes;
extern QMap<QString,struct _var> globalvarmap;

extern QList<struct _varlist> linevarlist;

extern QTextStream cin;  
extern QTextStream cout;  
extern QTextStream cerr;
extern bool freshgloballuavar;

extern int beginline,endline;
extern int oldbeginline,oldendline;
extern int currentfileindex;

backend::backend()
{
	// TODO Auto-generated constructor stub

}

backend::~backend()
{
	// TODO Auto-generated destructor stub
}


//线程主循环
void backend::run()
{
	int interval = 1;	// 1ms

	struct pcap_pkthdr *header;
	const u_char *pkt_data;

	int res;
	bool ret = false;
	int loopcnt = 0;
	unsigned int nodeindex = 0;

	unsigned int nodenum = commnodes.count();

	aint = 0;


	//初始化PLC任务时间
	{
		//运行任务
		QList<struct controltask>::iterator itask;
		for(itask = tasklist.begin();itask != tasklist.end();++ itask)
		{
			(*itask).t.start();
		}
	}

	while (threadrun == true)
	{
		if( econwinrun == true)
		{
			//如果有节点
			if(commnodes.count() >0)
			{
				//发送数据
				//假设在以太网上，设置MAC的目的地址为 0:0:0:0:0:id
				senddata[0] = 0x00;
				senddata[1] = 0x00;
				senddata[2] = 0x00;
				senddata[3] = 0x00;
				senddata[4] = 0x00;
				//目标为第一个节点
				senddata[5] = commnodes[0].id;

				//设置MAC源地址为 0:0:0:0:0:240
				senddata[6] = 0x00;
				senddata[7] = 0x00;
				senddata[8] = 0x00;
				senddata[9] = 0x00;
				senddata[10] = 0x00;
				senddata[11] = 240;

				//协议头
				senddata[12] = 0x88;
				senddata[13] = 0xa1;

				//包的类型 01普通 02广播
				senddata[14] = 0x01;

				//包经过节点跳数记录，初始为0，然后每经过一个节点，跳数+1，跳数作为从节点索引地址用，也作为PC机对返回数据包校验用
				senddata[15] = 0x00;

				//跟踪栈内地址
				//起始地址为帧头+ (节点数目+1)×每节点描述空间，所有节点描叙空间完成后，还有一个最后一个字节指向PC的id
				unsigned short inframeindex = 16 + commnodes.count()*9 + 1;
				//每个节点的操作地址map，每个节点有写操作和读操作地址
				for(nodeindex = 0;nodeindex < nodenum;nodeindex++)
				{
					luamutex.lock();
					//回调函数调用，模块输出映射处理
					commnodes[nodeindex].out_handle(commnodes[nodeindex].pdevice);
					luamutex.unlock();
					
					//组帧，接受发送全部在一个以太网帧内，类似ethercat
					senddata[16+nodeindex * 9 +0 ] = commnodes[nodeindex].id;//id作为以太网帧路由使用

					//写操作索引为，在数据帧内数据地址(16位)，待写数据长度(8位)，对应设备的起始地址(8位)
					senddata[16+nodeindex * 9 +1 ] = inframeindex & 0x00ff;//写内存地址低8位
					senddata[16+nodeindex * 9 +2 ] = (inframeindex>>8) & 0x00ff;//写内存地址高8位
					senddata[16+nodeindex * 9 +3 ] = commnodes[nodeindex].PDOwritelen;//写长度
					senddata[16+nodeindex * 9 +4 ] = commnodes[nodeindex].PDOwriteaddr;//写目标地址

					//复制数据
					memcpy(senddata+inframeindex,commnodes[nodeindex].pcommsendbuff,commnodes[nodeindex].PDOwritelen);
					inframeindex += commnodes[nodeindex].PDOwritelen;//帧内数据指针移动

	
					//读操作索引为，在数据帧内数据地址(16位)，待读数据长度(8位)，对应设备的起始地址(8位)
					senddata[16+nodeindex * 9 +5 ] = inframeindex & 0x00ff;//读内存地址低8位
					senddata[16+nodeindex * 9 +6 ] = (inframeindex>>8) & 0x00ff;//读内存地址高8位
					senddata[16+nodeindex * 9 +7 ] = commnodes[nodeindex].PDOreadlen;//读长度
					senddata[16+nodeindex * 9 +8 ] = commnodes[nodeindex].PDOreadaddr;//读目标地址
					inframeindex += commnodes[nodeindex].PDOreadlen;//帧内数据指针移动

				}
				//指向PC机的ID节点
				senddata[16+commnodes.count() * 9 +0 ] = 240;

				//数据帧小于64，按64发送
				if(inframeindex < 64)
				{
					if (pcap_sendpacket(adhandle, senddata,64 /* size */) != 0)
					{
						printf("\nError sending the packet: \n", pcap_geterr(adhandle));
					}
				}
				//否则按真实大小发送
				else
				{
					if (pcap_sendpacket(adhandle, senddata,inframeindex /* size */) != 0)
					{
						printf("\nError sending the packet: \n", pcap_geterr(adhandle));
					}
				}
				//等返回数据
				waitmutex.lock();
				ret = etherwait.wait(&waitmutex,11);
				waitmutex.unlock();
				//错误数据包处理
				if( ret == false)
				{
					aint = aint + 1;
					//printf("outtime");
				}
				//正确数据包处理
				else
				{
					for(nodeindex = 0;nodeindex < nodenum;nodeindex++)
					{
						luamutex.lock();
						//回调函数调用，模块输入映射处理
						commnodes[nodeindex].in_handle(commnodes[nodeindex].pdevice);
						luamutex.unlock();
					}
					//启动所有用户定义任务
					if(allshake == false)
						allshake = true;

					{
						//运行C PLC任务
						QList<struct controltask>::iterator itask;
						for(itask = tasklist.begin();itask != tasklist.end();++ itask)
						{
							//到达任务运行间隔时间或者运行间隔时间为0
							if(((*itask).t.elapsed()> (*itask).intervalms) ||
								((*itask).intervalms == 0))
							{
								//任务执行体
								if((((*itask).taskcallback != (void (*)(void))0)) && ((*itask).runflag == true) && (allshake == true))
								{
									(*itask).taskcallback();
									(*itask).t.start();
								}
							}
						}

						luamutex.lock();

						//同步变量c=>lua
						flushctolua();
						//运行LUA PLC任务
						QList<struct luacontroltask>::iterator iluatask;
						for(iluatask = luatasklist.begin();iluatask != luatasklist.end();++ iluatask)
						{
							//到达任务运行间隔时间或者运行间隔时间为0
							if(((*iluatask).t.elapsed()> (*iluatask).intervalms) ||
								((*iluatask).intervalms == 0))
							{
								//任务执行体
								if(((*iluatask).runflag == true) && (allshake == true))
								{
									//函数名
									lua_getglobal(L,(*iluatask).taskname.toAscii());
									lua_pcall(L,0,0,0);
									(*iluatask).t.start();
								}
							}
						}

						//同步变量lua=>c
						flushluatoc();

						//同步lua程序中的全局变量
						if(freshgloballuavar == true)
						{
							freshgloballuavar = false;

							//是否改变变量刷新范围
							if((beginline == oldbeginline) && (endline == oldendline))
							{
							}
							else
							{
								oldbeginline = beginline;
								oldendline = endline;
								//函数名设置值
								lua_getglobal(L,"freshviewedvar");
								lua_pushinteger(L,currentfileindex+1);
								lua_pushinteger(L,beginline);
								lua_pushinteger(L,endline);
								lua_pcall(L,3,0,0);
							}

							//函数名设置值
							lua_getglobal(L,"freshviewedvarval");
							lua_pcall(L,0,0,0);

							//变量刷新到Qt viewvarvallen

							lua_getglobal(L,"viewvarvallen");
							if(lua_isnumber(L,-1))
							{
								int viewvarvallen = lua_tonumber(L,-1);
								for(int i =1;i <= viewvarvallen;i++)
								{
									lua_getglobal(L,"viewedvarval");
									lua_pushinteger(L,i);
									lua_gettable(L,-2);
									if(lua_istable(L,-1))
									{
										QString name;
										lua_pushstring(L,"name");
										lua_gettable(L,-2);
										if(lua_isstring(L,-1))
										{
											name = QString(lua_tostring(L,-1));
										}

										lua_pop(L,1);

										lua_pushstring(L,"val");
										lua_gettable(L,-2);

										struct _var tvar = globalvarmap.value(name);
										if(tvar.vartype == 0)
										{
											if(lua_isnumber(L,-1))
											{
												tvar.varval.ivar = lua_tointeger(L,-1);
												globalvarmap[name] = tvar;

												//cout << name <<"," << tvar.varval.ivar << endl;
											}
										}
										else if(tvar.vartype == 1)
										{
											if(lua_isboolean(L,-1))
											{
												tvar.varval.bvar = lua_toboolean(L,-1);
												globalvarmap[name] = tvar;
												//cout << name <<"," << tvar.varval.bvar << endl;
											}
										}
										else if(tvar.vartype == 2)
										{
											if(lua_isnumber(L,-1))
											{
												tvar.varval.dvar = lua_tonumber(L,-1);
												globalvarmap[name] = tvar;
												//cout << name <<"," << tvar.varval.dvar << endl;
											}
										}

										lua_pop(L,1);

									}
									lua_pop(L,1);
									lua_pop(L,1);
								}
							}
							lua_pop(L,1);

						}

						/*if(((loopcnt++)%1000) == 0)
						{
						//函数名
						lua_getglobal(L,"viewvar");
						lua_pcall(L,0,0,0);
						}
						*/
						luamutex.unlock();
					}
				}
				//等待1ms，尽量形成1ms周期的通信节奏，防止网络包过快，PC机丢包，同时防止CPU利用率过高
				msleep(1);
			}
			//没有通信节点
			else
			{
				msleep(100);
			}

		}

		else//系统没有运行
		{
			msleep(100);
		}
	}
errgoto:
	return;
}

//接受帧数据处理回调函数
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	int res;
	struct tm *ltime;
	char timestr[16];
	//struct pcap_pkthdr *header;
	//const u_char *pkt_data;
	time_t local_tv_sec;
	unsigned int nodeindex = 0;
	unsigned int nodenum = commnodes.count();
	//帧校验处理
	if((pkt_data[12] == 0x88)
		&& (pkt_data[13] == 0xa1)
		&& (pkt_data[14] == 0x01)
		&& (pkt_data[15] == nodenum)//节点计数

		&& (pkt_data[0] == 0)
		&& (pkt_data[1] == 0)
		&& (pkt_data[2] == 0)
		&& (pkt_data[3] == 0)
		&& (pkt_data[4] == 0)
		&& (pkt_data[5] == 240)
		)
	{
		//数据复制
		unsigned short inframeindex = 0;
		for(nodeindex = 0;nodeindex < nodenum;nodeindex++)
		{
			inframeindex = pkt_data[16+nodeindex * 9 +5 ] + (((unsigned short)(pkt_data[16+nodeindex * 9 +6 ]) )<< 8);
			memcpy(commnodes[nodeindex].pcommrecvbuff,pkt_data+inframeindex,commnodes[nodeindex].PDOreadlen);
		}
		

		waitmutex.lock();
		etherwait.wakeAll();
		waitmutex.unlock();
		cnt ++;
	}

}


backend2::backend2()
{
	// TODO Auto-generated constructor stub

}

backend2::~backend2()
{
	// TODO Auto-generated destructor stub
}

//线程主循环
void backend2::run()
{
	struct pcap_pkthdr *header;
	const u_char *pkt_data;

	int res;
	int cnt = 0;

	while (threadrun == true)
	{
		if( econwinrun == true)
		{
			/* 开始捕获 */
			pcap_loop(adhandle, 0, packet_handler, NULL);
		}

		else
		{
			msleep(100);
		}
	}
}