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
#include "device.h"
#include "mainloop.h"

#include <windows.h>
extern lua_State* L;

QList<struct _devicenode> devicenodes;

//设备初始化
struct tdevice107* tdevice107_init(unsigned int id,unsigned char luaflag)
{
	//分配内存
	struct tdevice107* pdevice = (struct tdevice107*)malloc(sizeof(struct tdevice107));
	//id
	pdevice->id = id;

	//内存初始化
	memset(pdevice->sendbuff,0,100);
	memset(pdevice->recvbuff,0,100);

	//模块类型
	pdevice->moduletype = 1;

	//端口类型
	pdevice->ports[0].type = 2;
	pdevice->ports[0].pv = (void *)(&(pdevice->outval));
	pdevice->ports[0].change = false;

	//端口类型
	pdevice->ports[1].type = 0;
	pdevice->ports[1].pv = (void *)(&(pdevice->inval));
	pdevice->ports[1].change = false;

	pdevice->luaflag = luaflag;

	//注册到全局模块列表
	struct _devicenode t;
	t.id = id;
	t.moduletype = pdevice->moduletype;
	t.pdevice = (void *)pdevice;
    devicenodes.append(t);

	//注册到通讯节点模块列表
	struct tcommnode comnode;
	comnode.id = id;
	comnode.pcommsendbuff =pdevice->sendbuff;
	comnode.sendpacklen = 1500;
	comnode.recvpacklen = 1500;
	comnode.commsendbufflen = comnode.sendpacklen-15;
	comnode.pcommrecvbuff = pdevice->recvbuff;
	comnode.intervalms = 0;//通迅间隔时间，对于linux要设定，否者通迅占用过多的cpu，windows可以不设
	comnode.loopset = 1;
	comnode.loopcnt = comnode.loopset;
	comnode.pdevice =(void *)pdevice;
	comnode.in_handle = tdevice107_in_handler;
	comnode.out_handle = tdevice107_out_handler;
	comnode.shakehand = false;

	commnodes.append(comnode);

	//模块的参数初始化，普通包的长度
	pdevice->sendbuff[79] = (unsigned char)(comnode.sendpacklen & 0x00ff);
	pdevice->sendbuff[80] = (unsigned char)((comnode.sendpacklen >> 8) & 0x00ff);
	pdevice->sendbuff[81] = (unsigned char)(comnode.recvpacklen & 0x00ff);
	pdevice->sendbuff[82] = (unsigned char)((comnode.recvpacklen >> 8) & 0x00ff);
	return pdevice;
}
//提供给lua的注册接口
int mytdevice107_init(lua_State* L)
{
	int id = (int)luaL_checknumber(L,1);
	tdevice107_init(id,1);
	return 0;
}

//设备输入数据处理回调接口
void tdevice107_in_handler(void *p)
{
	struct tdevice107* pdevice = (struct tdevice107*)p;
	//处理数据映射
	pdevice->inval.inportall = pdevice->recvbuff[0];
	if(pdevice->luaflag == 1)
	{
		lua_getglobal(L,"set107inport");
		lua_pushinteger(L,pdevice->id);
		lua_pushboolean(L,pdevice->inval.inportbit.in0);
		lua_pushboolean(L,pdevice->inval.inportbit.in1);
		lua_pushboolean(L,pdevice->inval.inportbit.in2);
		lua_pushboolean(L,pdevice->inval.inportbit.in3);
		lua_pushboolean(L,pdevice->inval.inportbit.in4);
		lua_pushboolean(L,pdevice->inval.inportbit.in5);
		lua_pushboolean(L,pdevice->inval.inportbit.in6);
		lua_pushboolean(L,pdevice->inval.inportbit.in7);
		lua_pcall(L,9,0,0);
	}
}


//设备输出数据处理回调接口
void tdevice107_out_handler(void *p)
{
	struct tdevice107* pdevice = (struct tdevice107*)p; 
	if(pdevice->luaflag == 1)
	{
		if(pdevice->ports[0].change == true)
		{
			pdevice->ports[0].change = false;
			lua_getglobal(L,"set107outport");
			lua_pushinteger(L,pdevice->id);
			lua_pushboolean(L,pdevice->outval.outportbit.out0);
			lua_pushboolean(L,pdevice->outval.outportbit.out1);
			lua_pushboolean(L,pdevice->outval.outportbit.out2);
			lua_pushboolean(L,pdevice->outval.outportbit.out3);
			lua_pushboolean(L,pdevice->outval.outportbit.out4);
			lua_pushboolean(L,pdevice->outval.outportbit.out5);
			lua_pushboolean(L,pdevice->outval.outportbit.out6);
			lua_pushboolean(L,pdevice->outval.outportbit.out7);
			lua_pcall(L,9,0,0);
		}
		else
		{
			lua_getglobal(L,"get107outport");
			lua_pushinteger(L,pdevice->id);
			lua_pcall(L,1,1,0);
			if(lua_isnumber(L,-1))
			{
				pdevice->outval.outportall = lua_tointeger(L,-1);
				lua_pop(L,1);
			}
		}
	}
	
	//处理数据映射
	pdevice->sendbuff[0] = pdevice->outval.outportall;
}


//设备的初始化函数
struct tdevice207*  tdevice207_init(unsigned int id,unsigned char luaflag)
{
	//内存分配
	struct tdevice207* pdevice = (struct tdevice207*)malloc(sizeof(struct tdevice207));

	//id
	pdevice->id = id;
	//初始化内存
	memset(pdevice->sendbuff,0,100);
	memset(pdevice->recvbuff,0,100);

	//模块类型
	pdevice->moduletype = 2;

	//端口类型
	pdevice->ports[0].type = 0;
	pdevice->ports[0].pv = (void *)(&(pdevice->inval0));
	pdevice->ports[0].change = false;

	//端口类型
	pdevice->ports[1].type = 0;
	pdevice->ports[1].pv = (void *)(&(pdevice->inval1));
	pdevice->ports[1].change = false;

	//端口类型
	pdevice->ports[2].type = 2;
	pdevice->ports[2].pv = (void *)(&(pdevice->outval0));
	pdevice->ports[2].change = false;

	//端口类型
	pdevice->ports[3].type = 2;
	pdevice->ports[3].pv = (void *)(&(pdevice->outval1));
	pdevice->ports[3].change = false;

	pdevice->luaflag = luaflag;

	//注册到全局模块列表
	struct _devicenode t;
	t.id = id;
	t.moduletype = pdevice->moduletype;
	t.pdevice = (void *)pdevice;
	devicenodes.append(t);


	//注册到通讯节点模块列表
	struct tcommnode comnode;
	comnode.id = id;
	comnode.pcommsendbuff =pdevice->sendbuff;
	comnode.sendpacklen = 1500;
	comnode.recvpacklen = 1500;
	comnode.commsendbufflen = comnode.sendpacklen-15;
	comnode.pcommrecvbuff = pdevice->recvbuff;
	comnode.intervalms = 0;//通迅间隔时间，对于linux要设定，否者通迅占用过多的cpu，windows可以不设
	comnode.loopset = 1;
	comnode.loopcnt = comnode.loopset;
	comnode.pdevice =(void *)pdevice;
	comnode.in_handle = tdevice207_in_handler;
	comnode.out_handle = tdevice207_out_handler;
	comnode.shakehand = false;

	commnodes.append(comnode);

	//模块的参数初始化，普通包的长度
	pdevice->sendbuff[79] = (unsigned char)(comnode.sendpacklen & 0x00ff);
	pdevice->sendbuff[80] = (unsigned char)((comnode.sendpacklen >> 8) & 0x00ff);
	pdevice->sendbuff[81] = (unsigned char)(comnode.recvpacklen & 0x00ff);
	pdevice->sendbuff[82] = (unsigned char)((comnode.recvpacklen >> 8) & 0x00ff);

	return pdevice;
}

//提供给lua的注册接口
int mytdevice207_init(lua_State* L)
{
	int id = (int)luaL_checknumber(L,1);
	tdevice207_init(id,1);
	return 0;
}

//设备输入数据处理回调接口
void tdevice207_in_handler(void *p)
{
	struct tdevice207* pdevice = (struct tdevice207*)p;
	//处理数据映射
	pdevice->inval0.inportall = pdevice->recvbuff[0];
	pdevice->inval1.inportall = pdevice->recvbuff[1];
	if(pdevice->luaflag == 1)
	{
		lua_getglobal(L,"set207inport");
		lua_pushinteger(L,pdevice->id);
		lua_pushboolean(L,pdevice->inval0.inportbit.in0);
		lua_pushboolean(L,pdevice->inval0.inportbit.in1);
		lua_pushboolean(L,pdevice->inval0.inportbit.in2);
		lua_pushboolean(L,pdevice->inval0.inportbit.in3);
		lua_pushboolean(L,pdevice->inval0.inportbit.in4);
		lua_pushboolean(L,pdevice->inval0.inportbit.in5);
		lua_pushboolean(L,pdevice->inval0.inportbit.in6);
		lua_pushboolean(L,pdevice->inval0.inportbit.in7);
		lua_pcall(L,9,0,0);

		lua_getglobal(L,"set207inport2");
		lua_pushinteger(L,pdevice->id);
		lua_pushboolean(L,pdevice->inval1.inportbit.in0);
		lua_pushboolean(L,pdevice->inval1.inportbit.in1);
		lua_pushboolean(L,pdevice->inval1.inportbit.in2);
		lua_pushboolean(L,pdevice->inval1.inportbit.in3);
		lua_pushboolean(L,pdevice->inval1.inportbit.in4);
		lua_pushboolean(L,pdevice->inval1.inportbit.in5);
		lua_pushboolean(L,pdevice->inval1.inportbit.in6);
		lua_pushboolean(L,pdevice->inval1.inportbit.in7);
		lua_pcall(L,9,0,0);

	}

}

//设备输出数据处理回调接口
void tdevice207_out_handler(void *p)
{
	struct tdevice207* pdevice = (struct tdevice207*)p;

	if(pdevice->luaflag == 1)
	{
		if(pdevice->ports[2].change == true)
		{
			pdevice->ports[2].change = false;
			lua_getglobal(L,"set207outport");
			lua_pushinteger(L,pdevice->id);
			lua_pushboolean(L,pdevice->outval0.outportbit.out0);
			lua_pushboolean(L,pdevice->outval0.outportbit.out1);
			lua_pushboolean(L,pdevice->outval0.outportbit.out2);
			lua_pushboolean(L,pdevice->outval0.outportbit.out3);
			lua_pushboolean(L,pdevice->outval0.outportbit.out4);
			lua_pushboolean(L,pdevice->outval0.outportbit.out5);
			lua_pushboolean(L,pdevice->outval0.outportbit.out6);
			lua_pushboolean(L,pdevice->outval0.outportbit.out7);
			lua_pcall(L,9,0,0);
		}
		else
		{
			lua_getglobal(L,"get207outport");
			lua_pushinteger(L,pdevice->id);
			lua_pcall(L,1,1,0);
			if(lua_isnumber(L,-1))
			{
				pdevice->outval0.outportall = lua_tointeger(L,-1);
				lua_pop(L,1);
			}

		}
		if(pdevice->ports[3].change == true)
		{
			pdevice->ports[3].change = false;
			lua_getglobal(L,"set207outport2");
			lua_pushinteger(L,pdevice->id);
			lua_pushboolean(L,pdevice->outval1.outportbit.out0);
			lua_pushboolean(L,pdevice->outval1.outportbit.out1);
			lua_pushboolean(L,pdevice->outval1.outportbit.out2);
			lua_pushboolean(L,pdevice->outval1.outportbit.out3);
			lua_pushboolean(L,pdevice->outval1.outportbit.out4);
			lua_pushboolean(L,pdevice->outval1.outportbit.out5);
			lua_pushboolean(L,pdevice->outval1.outportbit.out6);
			lua_pushboolean(L,pdevice->outval1.outportbit.out7);
			lua_pcall(L,9,0,0);
		}
		else
		{
			lua_getglobal(L,"get207outport2");
			lua_pushinteger(L,pdevice->id);
			lua_pcall(L,1,1,0);
			if(lua_isnumber(L,-1))
			{
				pdevice->outval1.outportall = lua_tointeger(L,-1);
				lua_pop(L,1);
			}

		}
	}

	//处理数据映射
	pdevice->sendbuff[0] = pdevice->outval0.outportall;
	pdevice->sendbuff[1] = pdevice->outval1.outportall;
}
