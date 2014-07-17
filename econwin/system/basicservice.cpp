/*
本文件提供一些PLC任务的基础服务
定时器
上升沿和下降沿触发
全局变量
*/
#include "basicservice.h"
#include <QString>
#include <iostream>
#include <Windows.h>
#include <QMessageBox>
#include <QFile>
#include <QApplication>
#include "DBBackend.h"
#include "lua.hpp"

extern DB mydb;
extern lua_State* L;


TON::TON(int timems)
{
	PT = timems;//ms
	Q = false;//输出信号
	INPUT = false;//输入信号
	oldIN = false;
}

TON::~TON()
{
	// TODO Auto-generated destructor stub
}

void TON::setms(int ms)
{
	PT = ms;//ms
}

void TON::checkin(bool in)//运行接口
{
	INPUT = in;
	if( (!oldIN) && INPUT)//上升
	{
		//记忆时间点
		t.start();
	}
	else if(oldIN && INPUT)//一直为正
	{
		if(t.elapsed()> PT)
		{
		     Q = true;
		}
	}
	else
	{
		Q = false;
	}
	oldIN = INPUT;
}




R_TRIG::R_TRIG()
{
	Q = false;//输出信号
	INPUT = false;//输入信号
	oldIN = false;
}


R_TRIG::~R_TRIG()
{
	// TODO Auto-generated destructor stub
}


void R_TRIG::checkin(bool in)//运行接口
{
	INPUT = in;
	if( (!oldIN) && INPUT)//上升
	{
		Q = true;
	}
	else
	{
		Q = false;
	}
	oldIN = INPUT;
}


F_TRIG::F_TRIG()
{
	Q = false;//输出信号
	INPUT = false;//输入信号
	oldIN = false;
}


F_TRIG::~F_TRIG()
{
	// TODO Auto-generated destructor stub
}


void F_TRIG::checkin(bool in)//运行接口
{
	INPUT = in;
	if(oldIN && (!INPUT))//下降
	{
		Q = true;
	}
	else
	{
		Q = false;
	}
	oldIN = INPUT;
}

QList<struct varUInt> varUIntlist;
QList<struct varInt> varIntlist;
QList<struct varUShort> varUShortlist;
QList<struct varShort> varShortlist;
QList<struct varULongLong> varULongLonglist;
QList<struct varLongLong> varLongLonglist;
QList<struct varULong> varULonglist;
QList<struct varLong> varLonglist;
QList<struct varFloat> varFloatlist;
QList<struct varDouble> varDoublelist;
QList<struct varDouble> varLuavarlist;
QList<QTime *> timerlist;

//提供给lua的变量注册接口
int myvar_register(lua_State* L)
{
	const char *id = luaL_checkstring(L,1);
	double defaultval = luaL_checknumber(L,2);
	bool persist = luaL_checknumber(L,3);
	double *p = (double*)malloc(sizeof(double));
	*p = defaultval;

	//产生内存变量
	struct varDouble t;
	double val= 0;
	
	//id是str
	t.id = id;
	
	t.p = p;

	//persist false普通变量 true 保持变量
	if(persist != 0)
	{

		//在sql中查找是否有变量，如果没有则产生条目，否者将变量值读入到内存变量
		if(mydb.GetValue(id,val))
		{
			*p = val;
			t.sqlval = val;
		}
		else
		{
			//printf("newval\n");
			mydb.NewId(id,*p,"");
			t.sqlval = *p;
		}
	}
	else
	{
		t.sqlval = *p;
	}

	//内存列表
	varLuavarlist.append(t);
	lua_pushnumber(L,*p);
	return 1;
}

//变量注册
void var_register(const QString& id,unsigned int* p,bool persist)
{
	//产生内存变量
	struct varUInt t;
	unsigned int val= 0;
	
	//id是str
	t.id = id;
	
	t.p = p;
	//persist false普通变量 true 保持变量
	if(persist)
	{

		//在sql中查找是否有变量，如果没有则产生条目，否者将变量值读入到内存变量
		if(mydb.GetValue(id,val))
		{
			*p = val;
			t.sqlval = val;
		}
		else
		{
			printf("newval\n");
			mydb.NewId(id,*p,"");
			t.sqlval = *p;
		}
	}
	else
	{
		t.sqlval = *p;
	}

	//内存列表
	varUIntlist.append(t);

}

//变量注册
void var_register(const QString& id,int* p,bool persist)
{
	//产生内存变量
	struct varInt t;
	int val= 0;
	
	//id是str
	t.id = id;
	
	t.p = p;

	//persist false普通变量 true 保持变量
	if(persist)
	{

		//在sql中查找是否有变量，如果没有则产生条目，否者将变量值读入到内存变量
		if(mydb.GetValue(id,val))
		{
			*p = val;
			t.sqlval = val;
		}
		else
		{
			printf("newval\n");
			mydb.NewId(id,*p,"");
			t.sqlval = *p;
		}
	}
	else
	{
		t.sqlval = *p;
	}

	//内存列表
	varIntlist.append(t);

}

void var_register(const  QString& id,unsigned short* p,bool persist)
{
	//产生内存变量
	struct varUShort t;
	unsigned short val= 0;
	
	//id是str
	t.id = id;
	
	t.p = p;

	//persist false普通变量 true 保持变量
	if(persist)
	{

		//在sql中查找是否有变量，如果没有则产生条目，否者将变量值读入到内存变量
		if(mydb.GetValue(id,val))
		{
			*p = val;
			t.sqlval = val;
		}
		else
		{
			printf("newval\n");
			mydb.NewId(id,*p,"");
			t.sqlval = *p;
		}
	}
	else
	{
		t.sqlval = *p;
	}
	//内存列表
	varUShortlist.append(t);

}

void var_register(const  QString& id,short* p,bool persist)
{
	//产生内存变量
	struct varShort t;
	short val= 0;
	
	//id是str
	t.id = id;
	
	t.p = p;

	//persist false普通变量 true 保持变量
	if(persist)
	{

		//在sql中查找是否有变量，如果没有则产生条目，否者将变量值读入到内存变量
		if(mydb.GetValue(id,val))
		{
			*p = val;
			t.sqlval = val;
		}
		else
		{
			printf("newval\n");
			mydb.NewId(id,*p,"");
			t.sqlval = *p;
		}
	}
	else
	{
		t.sqlval = *p;
	}

	//内存列表
	varShortlist.append(t);

}

void var_register(const  QString& id,unsigned long long* p,bool persist)
{
	//产生内存变量
	struct varULongLong t;
	unsigned long long val= 0;
	
	//id是str
	t.id = id;
	
	t.p = p;

	//persist false普通变量 true 保持变量
	if(persist)
	{

		//在sql中查找是否有变量，如果没有则产生条目，否者将变量值读入到内存变量
		if(mydb.GetValue(id,val))
		{
			*p = val;
			t.sqlval = val;
		}
		else
		{
			printf("newval\n");
			mydb.NewId(id,*p,"");
			t.sqlval = *p;
		}
	}
	else
	{
		t.sqlval = *p;
	}

	//内存列表
	varULongLonglist.append(t);

}

void var_register(const  QString& id,long long* p,bool persist)
{
	//产生内存变量
	struct varLongLong t;
	long long  val= 0;
	
	//id是str
	t.id = id;
	
	t.p = p;

	//persist false普通变量 true 保持变量
	if(persist)
	{

		//在sql中查找是否有变量，如果没有则产生条目，否者将变量值读入到内存变量
		if(mydb.GetValue(id,val))
		{
			*p = val;
			t.sqlval = val;
		}
		else
		{
			printf("newval\n");
			mydb.NewId(id,*p,"");
			t.sqlval = *p;
		}
	}
	else
	{
		t.sqlval = *p;
	}

	//内存列表
	varLongLonglist.append(t);

}

void var_register(const  QString& id,unsigned long* p,bool persist)
{
	//产生内存变量
	struct varULong t;
	unsigned long val= 0;
	
	//id是str
	t.id = id;
	
	t.p = p;

	//persist false普通变量 true 保持变量
	if(persist)
	{

		//在sql中查找是否有变量，如果没有则产生条目，否者将变量值读入到内存变量
		if(mydb.GetValue(id,val))
		{
			*p = val;
			t.sqlval = val;
		}
		else
		{
			printf("newval\n");
			mydb.NewId(id,*p,"");
			t.sqlval = *p;
		}
	}
	else
	{
		t.sqlval = *p;
	}

	//内存列表
	varULonglist.append(t);

}

void var_register(const  QString& id,long* p,bool persist)
{
	//产生内存变量
	struct varLong t;
	long val= 0;
	
	//id是str
	t.id = id;
	
	t.p = p;

	//persist false普通变量 true 保持变量
	if(persist)
	{

		//在sql中查找是否有变量，如果没有则产生条目，否者将变量值读入到内存变量
		if(mydb.GetValue(id,val))
		{
			*p = val;
			t.sqlval = val;
		}
		else
		{
			printf("newval\n");
			mydb.NewId(id,*p,"");
			t.sqlval = *p;
		}
	}
	else
	{
		t.sqlval = *p;
	}

	//内存列表
	varLonglist.append(t);

}

void var_register(const  QString& id,float* p,bool persist)
{
	//产生内存变量
	struct varFloat t;
	float val= 0;
	
	//id是str
	t.id = id;
	
	t.p = p;

	//persist false普通变量 true 保持变量
	if(persist)
	{

		//在sql中查找是否有变量，如果没有则产生条目，否者将变量值读入到内存变量
		if(mydb.GetValue(id,val))
		{
			*p = val;
			t.sqlval = val;
		}
		else
		{
			printf("newval\n");
			mydb.NewId(id,*p,"");
			t.sqlval = *p;
		}
	}
	else
	{
		t.sqlval = *p;
	}

	//内存列表
	varFloatlist.append(t);

}

void var_register(const  QString& id,double* p,bool persist)
{
	//产生内存变量
	struct varDouble t;
	double val= 0;
	
	//id是str
	t.id = id;
	
	t.p = p;

	//persist false普通变量 true 保持变量
	if(persist)
	{

		//在sql中查找是否有变量，如果没有则产生条目，否者将变量值读入到内存变量
		if(mydb.GetValue(id,val))
		{
			*p = val;
			t.sqlval = val;
		}
		else
		{
			printf("newval\n");
			mydb.NewId(id,*p,"");
			t.sqlval = *p;
		}
	}
	else
	{
		t.sqlval = *p;
	}

	//内存列表
	varDoublelist.append(t);

}

//c++ => lua
void flushctolua(void)
{
	QList<struct varDouble>::iterator iD;
	for(iD = varLuavarlist.begin();iD != varLuavarlist.end();++ iD)
	{
		lua_pushnumber(L,*(*iD).p);
		lua_setglobal(L,(*iD).id.toAscii());
	}
}

//lua=> c++
void flushluatoc(void)
{
	QList<struct varDouble>::iterator iD;
	for(iD = varLuavarlist.begin();iD != varLuavarlist.end();++ iD)
	{
		lua_getglobal(L,(*iD).id.toAscii());
		if(lua_isnumber(L,-1))
		{
			*(*iD).p = lua_tonumber(L,-1);
		}
		lua_pop(L,1);
	}
}

int mynewtimer(lua_State* L)
{
	QTime* pt = new QTime;
	timerlist.append(pt);
	lua_pushnumber(L,timerlist.count()-1);
	//printf("mynewtimer\n");
	return 1;
}
int mystarttimer(lua_State* L)
{
	int id = (int)luaL_checknumber(L,1);
	timerlist[id]->start();
	//printf("mystarttimer\n");
	return 0;
}
int mytimerelapsed(lua_State* L)
{
	int id = (int)luaL_checknumber(L,1);
	lua_pushnumber(L,timerlist[id]->elapsed());
	return 1;
}



