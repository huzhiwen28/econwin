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
	//发送数据长度
	unsigned int commsendbufflen;
	//接收数据区指针
	unsigned char *pcommrecvbuff;
	//通讯间隔时间，毫秒
	unsigned int intervalms;
	//多少循环通讯一次，设置值
	unsigned int loopset;
	//当前循环计数，计数为0的时候，就进行一次通讯
	unsigned int loopcnt;
	//发送数据包长度
	unsigned int sendpacklen;
	//接收数据包长
	unsigned int recvpacklen;
	//设备结构指针
	void * pdevice;
	//设置数据和通信数据映射处理in,p为设备结构指针
	void (*in_handle)(void * p);
	//设置数据和通信数据映射处理out,p为设备结构指针
	void (*out_handle)(void * p);
	//节点是否握手成功
	bool shakehand;
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
