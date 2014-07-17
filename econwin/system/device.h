/*
本文件实现外部各类设备的定义
每种设备要实现如下3类接口
//设备初始化
void tdevice107_init(struct tdevice107* pdevice,unsigned int id);
//设备输入数据处理回调接口
void tdevice107_in_handler(void *p);
//设备输出数据处理回调接口
void tdevice107_out_handler(void *p);
*/
#ifndef DEVICE_H
#define DEVICE_H
#include <QList>
#include "lua.hpp"

extern QList<struct _devicenode> devicenodes;

//外部设备定义配置，每种设备的结构和处理都不一样，所以有多少外部设备，就有多少定义配置

//方便对端口进行操作的工具
struct toutportbit{
	unsigned char out0:1;
	unsigned char out1:1;
	unsigned char out2:1;
	unsigned char out3:1;
	unsigned char out4:1;
	unsigned char out5:1;
	unsigned char out6:1;
	unsigned char out7:1;
};

union outport{
	struct toutportbit outportbit;
	unsigned char outportall;
};

struct tinportbit{
	unsigned char in0:1;
	unsigned char in1:1;
	unsigned char in2:1;
	unsigned char in3:1;
	unsigned char in4:1;
	unsigned char in5:1;
	unsigned char in6:1;
	unsigned char in7:1;
};

union inport{
	struct tinportbit inportbit;
	unsigned char inportall;
};

struct port{
	unsigned char type;//端口类型0:input8 1:input16 2:output8 3:output16 4:DA 6:AD 7
	void* pv;
	bool change;//端口改变标识，主要给lua空间设备用
};

//设备节点
struct _devicenode{
	unsigned int id;
	unsigned char moduletype;
	void *pdevice;
};
//107设备
struct tdevice107
{
   	unsigned char sendbuff[1500];
   	unsigned char recvbuff[1500];
   	unsigned int id;
	unsigned char moduletype;//模块类型

	struct port ports[2];

	union outport  outval;
	union inport   inval;
	unsigned char luaflag;
};


//设备的初始化函数
struct tdevice107* tdevice107_init(unsigned int id,unsigned char luaflag = 0);
int mytdevice107_init(lua_State* L);

//设备输入数据处理回调接口
void tdevice107_in_handler(void *p);

//设备输出数据处理回调接口
void tdevice107_out_handler(void *p);

//207设备
struct tdevice207
{
   	unsigned char sendbuff[1500];
   	unsigned char recvbuff[1500];
   	unsigned int id;
	unsigned char moduletype;//模块类型

	struct port ports[4];

	union outport  outval0;
	union outport  outval1;

	union inport  inval0;
	union inport  inval1;

	unsigned char luaflag;
};


//设备的初始化函数
struct tdevice207*  tdevice207_init(unsigned int id,unsigned char luaflag = 0);
int mytdevice207_init(lua_State* L);

//设备输入数据处理回调接口
void tdevice207_in_handler(void *p);

//设备输出数据处理回调接口
void tdevice207_out_handler(void *p);

#endif /* DEVICE_H */