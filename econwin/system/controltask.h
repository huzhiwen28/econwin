/*
本文件提供用户任务注册的接口

*/
#ifndef CONTROLTASK_H
#define CONTROLTASK_H

#include <QTime>
#include <QTimer>
#include <QString>
#include <QList>
#include "lua.hpp"

struct controltask
{
		QString taskname;
		unsigned int intervalms;//任务运行间隔时间，如果为0则,尽可能快的运行，也即每个IO刷新周期都运行一次
		bool runflag;//任务执行标识
		void (*taskcallback)(void);
		QTime t;
};

//变量注册
void task_register(const  QString& taskname,unsigned int intervalms,void (*taskcallback)(void));
extern QList<struct controltask> tasklist;

struct luacontroltask
{
		QString taskname;
		unsigned int intervalms;//任务运行间隔时间，如果为0则,尽可能快的运行，也即每个IO刷新周期都运行一次
		bool runflag;//任务执行标识
		QTime t;
};

//变量注册
void luatask_register(const  QString& taskname,unsigned int intervalms);
extern QList<struct luacontroltask> luatasklist;

int mytaskregister(lua_State* L);
#endif