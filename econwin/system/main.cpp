/*
程序入口
*/
#include <QtGui/QApplication>
#include <QFile>
#include <QDir>
#include <QStringList>
#include <QObject>
#include <QTextStream> 
#include "pcap.h"
#include <iphlpapi.h>
#include "econwin.h"
#include "luaview.h"
#include <QtGui>
#include "mainloop.h"
#include "pcap.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Mmsystem.h>
#include "controltask.h"
#include "DBBackend.h"
#include "basicservice.h"
#include "device.h"
#include "lua.hpp"
#include "luaview.h"

lua_State* L;
lua_State* L3;

econwin * peconwin = 0;
#define ENVWINDOWS

extern DB mydb;

//是否全部握手过
extern bool allshake;

extern QMap<QString,struct _var> globalvarmap;
extern QList<struct _filelinevarmap> filelinevarmaplist;
extern QList<QString> filecontent;
extern QList<QString> filenamelist;


int netcardindex = 0;
pcap_t *adhandle;
struct bpf_program fcode;
bool threadrun = true;

//启动启动并运行
bool econwinrun = false;

QString projecthmifilename = "";
bool projecthmirun = false;

#ifdef ENVWINDOWS

//定时器处理函数，空函数
void WINAPI onTimeFunc(UINT wTimerID, UINT msg,DWORD dwUser,DWORD dwl,DWORD dw2)
{

}
#endif



//注册所有的用户任务
void init_usertask(void);

//初始化设备节点
void devicenodes_init(void);

//输入输出用
QTextStream cin(stdin, QIODevice::ReadOnly);  
QTextStream cout(stdout, QIODevice::WriteOnly);  
QTextStream cerr(stderr, QIODevice::WriteOnly);

void initGlobalvar(void);
extern QList<QString> filenamelist;


KeyPressEater::KeyPressEater(QObject *parent) :
QObject(parent)
{

}
KeyPressEater::~KeyPressEater()
{

}
//各类按键事件处理
bool KeyPressEater::eventFilter(QObject *obj, QEvent *event)
{
	//鼠标按键事件
	if ( event->type() == QEvent::MouseButtonDblClick
		|| event->type() == QEvent::MouseButtonPress
		|| event->type() == QEvent::MouseButtonRelease
		|| event->type() == QEvent::MouseMove)
	{
		return QObject::eventFilter(obj, event);
	}
	
#ifndef TEST
	else if(event->type() == QEvent::KeyPress)//过滤‘esc’按键
	{
		QKeyEvent *ke = static_cast<QKeyEvent *>(event);
		if (ke->key() == Qt::Key_Escape) {
			qDebug("esc");
			return true;
		}
		return QObject::eventFilter(obj, event);
	}
#endif
	
	else
	{
		// standard event processing
		return QObject::eventFilter(obj, event);
	}
}
/*
static int myexchange(lua_State* L)
{
	double a = luaL_checknumber(L,1);
	double b = luaL_checknumber(L,2);
	double c = a;
	a = b;
	b = c;
	lua_pushnumber(L,a);
	lua_pushnumber(L,b);
	return 2;
}
*/

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//库放置的位置，这个是为了便于程序搜索DLL
	QStringList ttt = a.libraryPaths();
	ttt.append(QCoreApplication::applicationDirPath() + QString("/plugins"));
	a.setLibraryPaths(ttt);

	//KeyPressEater *pkeyPressEater = new KeyPressEater();
	//a.installEventFilter(pkeyPressEater);

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

	//QString filename = QCoreApplication::applicationDirPath() + "/button.wlua";

	L = luaL_newstate();
	luaL_openlibs(L);//打开标准库

	//lua_pushcfunction(L,myexchange);
	//lua_setglobal(L,"myexchange");

	lua_pushcfunction(L,myvar_register);
	lua_setglobal(L,"var_register");

	lua_pushcfunction(L,mynewtimer);
	lua_setglobal(L,"newtimer");

	lua_pushcfunction(L,mystarttimer);
	lua_setglobal(L,"starttimer");

	lua_pushcfunction(L,mytimerelapsed);
	lua_setglobal(L,"timerelapsed");

	lua_pushcfunction(L,mytaskregister);
	lua_setglobal(L,"taskregister");

	lua_pushcfunction(L,mytdevice107_init);
	lua_setglobal(L,"tdevice107_init");

	lua_pushcfunction(L,mytdevice207_init);
	lua_setglobal(L,"tdevice207_init");

	L3 = luaL_newstate();
	luaL_openlibs(L3);//打开标准库

	//数据库初始化
	if (mydb.init() == false)
	{
		QMessageBox msgBox;
		msgBox.setText("找不到记录文件");
		msgBox.setWindowTitle("错误");
		msgBox.setStandardButtons(QMessageBox::Yes );
		QAbstractButton* tb = msgBox.button(QMessageBox::Yes);
		tb->setText("确定");
		msgBox.exec();

		return 1;
	}


	QString filename = QCoreApplication::applicationDirPath() + "/luasystem/device.lua";

	if(luaL_loadfile(L,filename.toAscii().data()) || lua_pcall(L,0,0,0) )
	{
		printf("不能执行配置%s",lua_tostring(L,-1));
	}

	filename = QCoreApplication::applicationDirPath() + "/luasystem/basicservice.lua";

	if(luaL_loadfile(L,filename.toAscii().data()) || lua_pcall(L,0,0,0) )
	{
		printf("不能执行配置%s",lua_tostring(L,-1));
	}

	filename = QCoreApplication::applicationDirPath() + "/globalvar.lua";

	if(luaL_loadfile(L,filename.toAscii().data()) || lua_pcall(L,0,0,0) )
	{
		printf("不能执行配置%s",lua_tostring(L,-1));
	}

	filename = QCoreApplication::applicationDirPath() + "/fileregister.lua";

	if(luaL_loadfile(L,filename.toAscii().data()) || lua_pcall(L,0,0,0) )
	{
		printf("不能执行配置%s",lua_tostring(L,-1));
	}

	lua_getglobal(L,"filenamelistlen");
	if(lua_isnumber(L,-1))
	{

		int len = lua_tointeger(L,-1);
		lua_pop(L,1);
		lua_getglobal(L,"filenamelist");
		for(int i = 1;i <= len ;i++)
		{
			lua_pushinteger(L,i);
			lua_gettable(L,-2);
			if(lua_isstring(L,-1))
			{
				filenamelist.append(lua_tostring(L,-1));
				filename = QCoreApplication::applicationDirPath() + "/" + QString(lua_tostring(L,-1));
				if(luaL_loadfile(L,filename.toAscii().data()) || lua_pcall(L,0,0,0) )
				{
					printf("不能执行配置%s",lua_tostring(L,-1));
				}
			}
			lua_pop(L,1);
		}
		lua_pop(L,1);
	}

	//lua全局变量处理程序
	filename = QCoreApplication::applicationDirPath() + "/luasystem/viewlua.lua";

	if(luaL_loadfile(L,filename.toAscii().data()) || lua_pcall(L,0,0,0) )
	{
		printf("不能执行配置%s",lua_tostring(L,-1));
	}

	//变量清除空
	//globalvarmap.clear();
	//filelinevarmaplist.clear();

	//处理所有的文件，获得全局变量
	for(int i = 0;i < filenamelist.count();i++)
	{
		filename = QCoreApplication::applicationDirPath() + "/" + filenamelist[i];
		//函数名设置值
		lua_getglobal(L,"process");
		lua_pushstring(L,filename.toAscii());
		lua_pcall(L,1,0,0);
	}

	//取得所有的变量数量globalvarnum
	lua_getglobal(L,"globalvarnum");//S:globalvarnum
	
	if(lua_isnumber(L,-1))
	{
		int globalvarnum = lua_tointeger(L,-1);
		//清空栈
		lua_pop(L,1);//S:
		//printf("globalvarnum:%d\n",globalvarnum);

		lua_getglobal(L,"globalvar2");//S:globalvar2
		for(int i =1;i <= globalvarnum;i++)
		{
			//printf("i:%d\n",i);
			//globalvar2[i]表
			lua_pushinteger(L,i);
			lua_gettable(L,-2);//S:globalvar2,globalvar2[i]
			if(lua_istable(L,-1))
			{
				QString name;
				//globalvar2[i].name字符串
				lua_pushstring(L,"name");
				lua_gettable(L,-2);//S:globalvar2,globalvar2[i],globalvar2[i].name
				if(lua_isstring(L,-1))
				{
					//printf("%s\n",lua_tostring(L,-1));
					name = QString(lua_tostring(L,-1));
					lua_pop(L,1);//S:globalvar2,globalvar2[i]
				}
				struct _var var;
				
				//globalvar2[i].t字符串
				lua_pushstring(L,"t");//S:globalvar2,globalvar2[i],globalvar2[i].t
				lua_gettable(L,-2);
				if(lua_isnumber(L,-1))
				{
					var.vartype = lua_tonumber(L,-1);
					
					//printf("%d\n",lua_tointeger(L,-1));
					lua_pop(L,1);//S:globalvar2,globalvar2[i]
				}

				globalvarmap.insert(name,var);

			}
			lua_pop(L,1);//S:globalvar2
		}
		//清空栈
		lua_pop(L,1);//S:
		//cout << canshuquyuhuafenlen << endl;
	}

	//获取全局行变量
	lua_getglobal(L,"linevar");//linevar

	for(int i = 0;i < filenamelist.count();i++)
	{

		struct _filelinevarmap filelinevarmap;

		lua_pushinteger(L,i+1);
		lua_gettable(L,-2);//linevar,linevar[i]

		lua_pushstring(L,"lineindex");
		lua_gettable(L,-2);//linevar,linevar[i],linevar[i].lineindex

		int lineindex = 0;
		if(lua_isnumber(L,-1))
		{
			lineindex = lua_tointeger(L,-1);
			//cout << "lineindex:" << lineindex << endl;
			//清空栈
			lua_pop(L,1);//linevar,linevar[i]
		}

		for(int ii =1;ii <= lineindex;ii++)
		{
			//printf("ii:%d\n",ii);
			//linevr[i][ii]表
			lua_pushinteger(L,ii);
			lua_gettable(L,-2);//linevar,linevar[i],linevr[i][ii]
			if(lua_istable(L,-1))
			{
				int len = 0;
				//linevar[i].len字符串
				lua_pushstring(L,"len");
				lua_gettable(L,-2);//linevar,linevar[i],linevr[i][ii],linevr[i][ii].len
				if(lua_isnumber(L,-1))
				{
					//printf("%s\n",lua_tostring(L,-1));
					len = lua_tointeger(L,-1);
					lua_pop(L,1);//linevar,linevar[i],linevr[i][ii]
					struct _varlist tempvarlist;
					tempvarlist.line = ii;
					for(int iii =1;iii <= len;iii++)
					{
						lua_pushinteger(L,iii);
						lua_gettable(L,-2);//linevar,linevar[i],linevr[i][ii],linevr[i][ii][iii]
						if(lua_istable(L,-1))
						{
							struct _linevar linevar;
							lua_pushstring(L,"name");
							lua_gettable(L,-2);//linevar,linevar[i],linevr[i][ii],linevr[i][ii][iii],linevr[i][ii][iii].name
							if(lua_isstring(L,-1))
							{
								linevar.name =  QString(lua_tostring(L,-1));
								//cout << linevar.name << endl;
							}
							lua_pop(L,1);//linevar,linevar[i],linevr[i][ii],linevr[i][ii][iii]

							lua_pushstring(L,"location");//linevar,linevar[i],linevr[i][ii],linevr[i][ii][iii],linevr[i][ii][iii].location
							lua_gettable(L,-2);
							if(lua_isnumber(L,-1))
							{
								linevar.loc =  lua_tointeger(L,-1);
						
							}
							lua_pop(L,1);//linevar,linevar[i],linevr[i][ii],linevr[i][ii][iii]
							tempvarlist.varlist.append(linevar);
						}
						lua_pop(L,1);//linevar,linevar[i],linevr[i][ii]
					}
					filelinevarmap.linevarmap.insert(ii,tempvarlist);
				}
			}
			lua_pop(L,1);//linevar,linevar[i]
		}
		lua_pop(L,1);//linevar
		filelinevarmaplist.append(filelinevarmap);
	}
	lua_pop(L,1);//

	//保持全局变量初始化
	initGlobalvar();

	//初始化用户任务
	init_usertask();

	//初始化设备节点
	devicenodes_init();

	//数据库后台初始化
	DBBackend DBBackendinst;
	DBBackendinst.start();

	filename = QCoreApplication::applicationDirPath() + "/para.lua";

	if(luaL_loadfile(L3,filename.toAscii().data()) || lua_pcall(L3,0,0,0) )
	{
		printf("不能执行配置%s",lua_tostring(L3,-1));
	}

	//获取全局行变量
	lua_getglobal(L3,"netcardindex");//netcardindex
	if(lua_isnumber(L3,-1))
	{
		netcardindex =  lua_tointeger(L3,-1);
	}
	lua_pop(L3,1);

	lua_getglobal(L3,"econwinrun");//netcardindex
	if(lua_isnumber(L3,-1))
	{
		if(lua_tointeger(L3,-1) == 0)
			econwinrun =  false;
		else if(lua_tointeger(L3,-1) == 1)
			econwinrun =  true;
	}
	lua_pop(L3,1);

	lua_getglobal(L3,"projectname");//netcardindex
	if(lua_isstring(L3,-1))
	{
		projecthmifilename =  lua_tostring(L3,-1);
	}
	lua_pop(L3,1);

	lua_getglobal(L3,"hmirun");//netcardindex
	if(lua_isnumber(L3,-1))
	{
		if(lua_tointeger(L3,-1) == 0)
			projecthmirun =  false;
		else if(lua_tointeger(L3,-1) == 1)
			projecthmirun =  true;
	}
	lua_pop(L3,1);

	econwin w;
	peconwin = &w;
	w.show();

#ifdef ENVWINDOWS
	//多媒体定时器，为了提高工控机线程调度精度
	MMRESULT timer_id;
	timer_id = timeSetEvent(1, 1, (LPTIMECALLBACK)onTimeFunc, DWORD(1), TIME_PERIODIC);
#endif


	
	if (econwinrun == true)
	{
		pcap_if_t *alldevs;
		pcap_if_t *d;
		int inum;
		int i=0;
		char errbuf[PCAP_ERRBUF_SIZE];

		/* Retrieve the device list */
		if(pcap_findalldevs(&alldevs, errbuf) == -1)
		{
			fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
			//exit(1);
		}


		/* Jump to the selected adapter */
		for(d=alldevs, i=0; i<netcardindex ;d=d->next, i++);

		/* Open the device */
		/* Open the adapter */
		if ((adhandle= pcap_open_live(d->name,	// name of the device
			65536,			// portion of the packet to capture. 
			// 65536 grants that the whole packet will be captured on all the MACs.
			1,				// promiscuous mode (nonzero means promiscuous)
			1,			// read timeout
			errbuf			// error buffer
			)) == NULL)
		{
			fprintf(stderr,"\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
			/* Free the device list */
			pcap_freealldevs(alldevs);
			return 0;
		}

		// configure pcap for maximum responsiveness
		if (pcap_setmintocopy(adhandle, 0) != 0)
		{
			printf("pcap_setmintocopy failed\n");
		}

		//compile the filter
		if(pcap_compile(adhandle, &fcode, "ether dst 0:0:0:0:0:f0", 1, 0) < 0)
		{
			fprintf(stderr,"\nError compiling filter: wrong syntax.\n");
		}

		//设置过滤器
		if(pcap_setfilter(adhandle, &fcode)<0)
		{
			fprintf(stderr,"\nError setting the filter\n");
		}	
		printf("\nlistening on %s...\n", d->description);

		/* At this point, we don't need any more the device list. Free it */
		pcap_freealldevs(alldevs);
	}

	//后台线程，跑通信发送帧，PLC任务等
	backend backendinst;
	backendinst.start();
	backendinst.setPriority(QThread::TimeCriticalPriority);

	//后台线程，以太网数据帧接受处理
	backend2 backendinst2;
	backendinst2.start();
	backendinst2.setPriority(QThread::TimeCriticalPriority);

	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	a.exec();

	//退出任务界面后，首先停止用户逻辑任务
	allshake = false;

	//模块输出值设置为默认值


	//等1秒
	Sleep(1000);
	//确保数据刷新到数据库文件中
	while ((mydb.SQLQueuechg == true) 
		|| (mydb.SQLQueuechg2 == true))
	{
		;
	}
	//停止通信、PLC运行
	if (econwinrun == true)
	{
		econwinrun = false;
		Sleep(100);

		//关闭网卡
		pcap_close(adhandle);
	}

	threadrun = false;

	//等待线程退出
	backendinst.wait();
	backendinst2.wait();

	DBBackendinst.wait();
	//关闭lua虚拟机
	lua_close(L);
	lua_close(L3);

}
