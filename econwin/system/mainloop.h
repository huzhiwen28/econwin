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
#ifndef BACKEND_H
#define BACKEND_H

#include <qthread>
#include <QTime>
#include <QTimer>
#include <QThread>
#include <Qlist>

extern QList<struct tcommnode> commnodes;

//通讯模块节点结构
struct tcommnode {
	//commid
	unsigned int id;

	//发送数据区指针
	unsigned char *pcommsendbuff;

	//接收数据区指针
	unsigned char *pcommrecvbuff;

	//定时写的长度
	unsigned char PDOwritelen;
	//定时写的目标地址
	unsigned char PDOwriteaddr;
	//定时读的地址
	unsigned char PDOreadaddr;
	//定时读的长度
	unsigned char PDOreadlen;

	//设备结构指针
	void * pdevice;
	//设置数据和通信数据映射处理in,p为设备结构指针
	void (*in_handle)(void * p);
	//设置数据和通信数据映射处理out,p为设备结构指针
	void (*out_handle)(void * p);
	//节点是否握手成功
	//bool shakehand;
};

class backend: public QThread
{

	Q_OBJECT

public:

	backend();
	virtual ~backend();

protected:
	virtual void run();
};

class backend2: public QThread
{

	Q_OBJECT

public:

	backend2();
	virtual ~backend2();

protected:
	virtual void run();
};



#endif /* BACKEND_H */
