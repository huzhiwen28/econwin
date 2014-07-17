/*
本文件实现全局变量的数据库后台保存实现

*/

#ifndef DBBACKEND_H_
#define DBBACKEND_H_

#include <qthread>
#include <QTime>
#include <QTimer>
#include <QThread>
#include <QtSql>
#include <QMutex>
#include <QTableView>
#include <QSqlTableModel>
#include <QString>
#include <QApplication>

class DB
{
public:
	DB();
	virtual ~DB();
	bool init();
	void close();

	//取得id的值
	bool GetValue(const  QString& id,int& value);
	bool GetValue(const  QString& id,unsigned int& value);
	bool GetValue(const  QString& id,short& value);
	bool GetValue(const  QString& id,unsigned short& value);
	bool GetValue(const  QString& id,long long& value);
	bool GetValue(const  QString& id,unsigned long long& value);
	bool GetValue(const  QString& id,long& value);
	bool GetValue(const  QString& id,unsigned long& value);
	bool GetValue(const  QString& id,float& value);
	bool GetValue(const  QString& id,double& value);

	//保存id的值
	bool SaveValue(const QString& id,const int value);
	bool SaveValue(const QString& id,const unsigned int value);
	bool SaveValue(const QString& id,const short value);
	bool SaveValue(const QString& id,const unsigned short value);
	bool SaveValue(const QString& id,const long long value);
	bool SaveValue(const QString& id,const unsigned long long value);
	bool SaveValue(const QString& id,const long value);
	bool SaveValue(const QString& id,const unsigned long value);
	bool SaveValue(const QString& id,const float value);
	bool SaveValue(const QString& id,const double value);

    //新增ID
	bool NewId(const QString& id,const int value,const QString& text);
	bool NewId(const QString& id,const unsigned int value,const QString& text);
	bool NewId(const QString& id,const short value,const QString& text);
	bool NewId(const QString& id,const unsigned short value,const QString& text);
	bool NewId(const QString& id,const long long value,const QString& text);
	bool NewId(const QString& id,const unsigned long long value,const QString& text);
	bool NewId(const QString& id,const long value,const QString& text);
	bool NewId(const QString& id,const unsigned long value,const QString& text);
	bool NewId(const QString& id,const float value,const QString& text);
	bool NewId(const QString& id,const double value,const QString& text);

public:

	//SQL缓存队列
	QList<QString> SQLQueue;
	QList<QString> SQLQueue2;

	//数据库
	QSqlDatabase sqldb;

	//是否打开了数据库
	bool sqldbopen;

	bool SQLQueueflag; //0：当前记录写入SQLQueue   1：当前记录写入SQLQueue2
	//队列标识锁
	QMutex SQLQueueflagmutex;

	//操作锁，我对数据库系统自身的锁暂时不放心
	QMutex SQLmutex;

	//队列改变标识
	bool SQLQueuechg; //0 队列没有改变 1队列改变了
	bool SQLQueuechg2; //0 队列没有改变 1队列改变了
};

//数据库后台
class DBBackend: public QThread
{

	Q_OBJECT

public:

	DBBackend();
	virtual ~DBBackend();

protected:
	virtual void run();

};

#endif /* DBBACKEND_H_ */