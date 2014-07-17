/*
本文件提供用户任务注册的接口

*/
#include "controltask.h"
extern lua_State* L;

QList<struct controltask> tasklist;
QList<struct luacontroltask> luatasklist;

void task_register(const  QString& taskname,unsigned int intervalms,void (*taskcallback)(void))
{
	struct controltask t;
	t.runflag = true;
	t.taskname = taskname;
	t.intervalms = intervalms;
	t.taskcallback = taskcallback;
	tasklist.append(t);
}

void luatask_register(const  QString& taskname,unsigned int intervalms)
{
	struct luacontroltask t;
	t.runflag = true;
	t.taskname = taskname;
	t.intervalms = intervalms;
	luatasklist.append(t);
}

int mytaskregister(lua_State* L)
{
	const char * taskname = luaL_checkstring(L,1);
	int intervalms = (int)luaL_checknumber(L,2);
	luatask_register(taskname,intervalms);
	//printf("mytaskregister\n");
	return 0;
}

