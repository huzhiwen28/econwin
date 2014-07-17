/*
本文件实现全局变量的数据库后台保存实现

*/
#include <iostream>
#include <QList>
#include <QString>
#include "basicservice.h"
#include "DBBackend.h"
extern bool threadrun;

extern QList<struct varUInt> varUIntlist;
extern QList<struct varInt> varIntlist;
extern QList<struct varUShort> varUShortlist;
extern QList<struct varShort> varShortlist;
extern QList<struct varULongLong> varULongLonglist;
extern QList<struct varLongLong> varLongLonglist;
extern QList<struct varULong> varULonglist;
extern QList<struct varLong> varLonglist;
extern QList<struct varFloat> varFloatlist;
extern QList<struct varDouble> varDoublelist;


//数据库
DB mydb;

DB::DB()
{
	sqldbopen = false;

	SQLQueueflag = false; //0：当前记录写入SQLQueue   1：当前记录写入SQLQueue2
	SQLQueuechg = false; //0 队列没有改变 1队列改变了
	SQLQueuechg2 = false; //0 队列没有改变 1队列改变了

}

DB::~DB()
{
	// TODO Auto-generated destructor stub
	sqldb.close();
}

void DB::close()
{
}
//新增事件记录
bool DB::init()
{
	if (QFile::exists(QApplication::applicationDirPath() + QString("/sysdb")))
	{
		//数据库初始化
		sqldb = QSqlDatabase::addDatabase("QSQLITE","conn");

		sqldb.setDatabaseName(QApplication::applicationDirPath() + QString("/sysdb"));

		if (!sqldb.open())
		{
			sqldbopen = false;
			return false;
		}
		else
		{
			sqldbopen = true;
			return true;
		}
	}
	else
	{
		sqldbopen = false;
		return false;
	}
}

//取得id的值
bool DB::GetValue(const QString& id, int& value)
{
	SQLmutex.lock();
	QSqlQuery query = sqldb.exec(QString("SELECT value FROM save where id='") + id + QString("'"));
    SQLmutex.unlock();

	if (query.first())
	{ 
		bool ok;
		value = query.value(0).toInt(&ok);
		return true;
	}
	else
	{
		return false;
	}
}
bool DB::GetValue(const QString& id,unsigned int& value)
{
	SQLmutex.lock();
	QSqlQuery query = sqldb.exec(QString("SELECT value FROM save where id='") + id + QString("'"));
    SQLmutex.unlock();

	if (query.first())
	{ 
		bool ok;
		value = query.value(0).toUInt(&ok);
		return true;
	}
	else
	{
		return false;
	}
}
bool DB::GetValue(const QString& id, short& value)
{
	SQLmutex.lock();
	QSqlQuery query = sqldb.exec(QString("SELECT value FROM save where id='") + id + QString("'"));
    SQLmutex.unlock();

	if (query.first())
	{ 
		bool ok;
		value = query.value(0).toString().toShort(&ok);
		return true;
	}
	else
	{
		return false;
	}
}
bool DB::GetValue(const QString& id, unsigned short& value)
{
	SQLmutex.lock();
	QSqlQuery query = sqldb.exec(QString("SELECT value FROM save where id='") + id + QString("'"));
    SQLmutex.unlock();

	if (query.first())
	{ 
		bool ok;
		value = query.value(0).toString().toUShort(&ok);
		return true;
	}
	else
	{
		return false;
	}
}
bool DB::GetValue(const QString& id, long long& value)
{
	SQLmutex.lock();
	QSqlQuery query = sqldb.exec(QString("SELECT value FROM save where id='") + id + QString("'"));
    SQLmutex.unlock();

	if (query.first())
	{ 
		bool ok;
		value = query.value(0).toLongLong(&ok);
		return true;
	}
	else
	{
		return false;
	}
}
bool DB::GetValue(const QString& id, unsigned long long& value)
{
	SQLmutex.lock();
	QSqlQuery query = sqldb.exec(QString("SELECT value FROM save where id='") + id + QString("'"));
    SQLmutex.unlock();

	if (query.first())
	{ 
		bool ok;
		value = query.value(0).toULongLong(&ok);
		return true;
	}
	else
	{
		return false;
	}
}
bool DB::GetValue(const QString& id, long& value)
{
	SQLmutex.lock();
	QSqlQuery query = sqldb.exec(QString("SELECT value FROM save where id='") + id + QString("'"));
    SQLmutex.unlock();

	if (query.first())
	{ 
		bool ok;
		value = query.value(0).toString().toLong(&ok);
		return true;
	}
	else
	{
		return false;
	}
}
bool DB::GetValue(const QString& id, unsigned long& value)
{
	SQLmutex.lock();
	QSqlQuery query = sqldb.exec(QString("SELECT value FROM save where id='") + id + QString("'"));
    SQLmutex.unlock();

	if (query.first())
	{ 
		bool ok;
		value = query.value(0).toString().toULong(&ok);
		return true;
	}
	else
	{
		return false;
	}
}
bool DB::GetValue(const QString& id, float& value)
{
	SQLmutex.lock();
	QSqlQuery query = sqldb.exec(QString("SELECT value FROM save where id='") + id + QString("'"));
    SQLmutex.unlock();

	if (query.first())
	{ 
		bool ok;
		value = query.value(0).toString().toFloat(&ok);
		return true;
	}
	else
	{
		return false;
	}
}
bool DB::GetValue(const QString& id, double& value)
{
	SQLmutex.lock();
	QSqlQuery query = sqldb.exec(QString("SELECT value FROM save where id='") + id + QString("'"));
    SQLmutex.unlock();

	if (query.first())
	{ 
		bool ok;
		value = query.value(0).toDouble(&ok);
		return true;
	}
	else
	{
		return false;
	}
}
//保存ID的值
bool DB::SaveValue(const QString& id, const int value)
{
	SQLQueueflagmutex.lock();
	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg2 = true;
    }
	SQLQueueflagmutex.unlock();

	return true;
}
bool DB::SaveValue(const QString& id, const unsigned int value)
{
	SQLQueueflagmutex.lock();
	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg2 = true;
    }
	SQLQueueflagmutex.unlock();

	return true;
}
bool DB::SaveValue(const QString& id, const short value)
{
	SQLQueueflagmutex.lock();
	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg2 = true;
    }
	SQLQueueflagmutex.unlock();

	return true;
}
bool DB::SaveValue(const QString& id, const unsigned short value)
{
	SQLQueueflagmutex.lock();
	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg2 = true;
    }
	SQLQueueflagmutex.unlock();

	return true;
}
bool DB::SaveValue(const QString& id, const long long value)
{
	SQLQueueflagmutex.lock();
	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg2 = true;
    }
	SQLQueueflagmutex.unlock();

	return true;
}
bool DB::SaveValue(const QString& id, const unsigned long long value)
{
	SQLQueueflagmutex.lock();
	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg2 = true;
    }
	SQLQueueflagmutex.unlock();

	return true;
}
bool DB::SaveValue(const QString& id, const long value)
{
	SQLQueueflagmutex.lock();
	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg2 = true;
    }
	SQLQueueflagmutex.unlock();

	return true;
}
bool DB::SaveValue(const QString& id, const unsigned long value)
{
	SQLQueueflagmutex.lock();
	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg2 = true;
    }
	SQLQueueflagmutex.unlock();

	return true;
}
bool DB::SaveValue(const QString& id, const float value)
{
	SQLQueueflagmutex.lock();
	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg2 = true;
    }
	SQLQueueflagmutex.unlock();

	return true;
}
bool DB::SaveValue(const QString& id, const double value)
{
	SQLQueueflagmutex.lock();
	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("update save set value =") + QString::number(value) + QString("  where id = '") + id + QString("'"));
		SQLQueuechg2 = true;
    }
	SQLQueueflagmutex.unlock();

	return true;
}

//新增ID
bool DB::NewId(const QString& id,const int value,const QString& text)
{
	SQLQueueflagmutex.lock();

	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg2 = true;
	}
	SQLQueueflagmutex.unlock();
	return true;

}
bool DB::NewId(const QString& id,const unsigned int value,const QString& text)
{
	SQLQueueflagmutex.lock();

	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg2 = true;
	}
	SQLQueueflagmutex.unlock();
	return true;

}
bool DB::NewId(const QString& id,const short value,const QString& text)
{
	SQLQueueflagmutex.lock();

	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg2 = true;
	}
	SQLQueueflagmutex.unlock();
	return true;

}
bool DB::NewId(const QString& id,const unsigned short value,const QString& text)
{
	SQLQueueflagmutex.lock();

	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg2 = true;
	}
	SQLQueueflagmutex.unlock();
	return true;

}
bool DB::NewId(const QString& id,const long long value,const QString& text)
{
	SQLQueueflagmutex.lock();

	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg2 = true;
	}
	SQLQueueflagmutex.unlock();
	return true;

}
bool DB::NewId(const QString& id,const unsigned long long value,const QString& text)
{
	SQLQueueflagmutex.lock();

	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg2 = true;
	}
	SQLQueueflagmutex.unlock();
	return true;

}
bool DB::NewId(const QString& id,const long value,const QString& text)
{
	SQLQueueflagmutex.lock();

	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg2 = true;
	}
	SQLQueueflagmutex.unlock();
	return true;

}
bool DB::NewId(const QString& id,const unsigned long value,const QString& text)
{
	SQLQueueflagmutex.lock();

	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg2 = true;
	}
	SQLQueueflagmutex.unlock();
	return true;

}
bool DB::NewId(const QString& id,const float value,const QString& text)
{
	SQLQueueflagmutex.lock();

	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg2 = true;
	}
	SQLQueueflagmutex.unlock();
	return true;

}
bool DB::NewId(const QString& id,const double value,const QString& text)
{
	SQLQueueflagmutex.lock();

	if (SQLQueueflag == false)
	{
		SQLQueue.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg = true;
	}
	else
	{
		SQLQueue2.append(QString("insert into save(id,value,text)  values('") + id + QString("',") + QString::number(value) + QString(",'") + text + QString("')"));
		SQLQueuechg2 = true;
	}
	SQLQueueflagmutex.unlock();
	return true;

}

DBBackend::DBBackend()
{

}

DBBackend::~DBBackend()
{

}

void DBBackend::run()
{
	while (threadrun == true)
	{

		//查看数据是否改变
		QList<struct varUInt>::iterator iUI;
		for(iUI = varUIntlist.begin();iUI != varUIntlist.end();++ iUI)
		{
			if((*iUI).sqlval != (*(*iUI).p))
			{
				mydb.SaveValue((*iUI).id,(*(*iUI).p));
				(*iUI).sqlval = (*(*iUI).p);
			}
		}
		QList<struct varInt>::iterator iI;
		for(iI = varIntlist.begin();iI != varIntlist.end();++ iI)
		{
			if((*iI).sqlval != (*(*iI).p))
			{
				mydb.SaveValue((*iI).id,(*(*iI).p));
				(*iI).sqlval = (*(*iI).p);
			}
		}
		QList<struct varUShort>::iterator iUS;
		for(iUS = varUShortlist.begin();iUS != varUShortlist.end();++ iUS)
		{
			if((*iUS).sqlval != (*(*iUS).p))
			{
				mydb.SaveValue((*iUS).id,(*(*iUS).p));
				(*iUS).sqlval = (*(*iUS).p);
			}
		}
		QList<struct varShort>::iterator iS;
		for(iS = varShortlist.begin();iS != varShortlist.end();++ iS)
		{
			if((*iS).sqlval != (*(*iS).p))
			{
				mydb.SaveValue((*iS).id,(*(*iS).p));
				(*iS).sqlval = (*(*iS).p);
			}
		}
		QList<struct varULongLong>::iterator iULL;
		for(iULL = varULongLonglist.begin();iULL != varULongLonglist.end();++ iULL)
		{
			if((*iULL).sqlval != (*(*iULL).p))
			{
				mydb.SaveValue((*iULL).id,(*(*iULL).p));
				(*iULL).sqlval = (*(*iULL).p);
			}
		}
		QList<struct varLongLong>::iterator iLL;
		for(iLL = varLongLonglist.begin();iLL != varLongLonglist.end();++ iLL)
		{
			if((*iLL).sqlval != (*(*iLL).p))
			{
				mydb.SaveValue((*iLL).id,(*(*iLL).p));
				(*iLL).sqlval = (*(*iLL).p);
			}
		}
		QList<struct varULong>::iterator iUL;
		for(iUL = varULonglist.begin();iUL != varULonglist.end();++ iUL)
		{
			if((*iUL).sqlval != (*(*iUL).p))
			{
				mydb.SaveValue((*iUL).id,(*(*iUL).p));
				(*iUL).sqlval = (*(*iUL).p);
			}
		}
		QList<struct varLong>::iterator iL;
		for(iL = varLonglist.begin();iL != varLonglist.end();++ iL)
		{
			if((*iL).sqlval != (*(*iL).p))
			{
				mydb.SaveValue((*iL).id,(*(*iL).p));
				(*iL).sqlval = (*(*iL).p);
			}
		}
		QList<struct varFloat>::iterator iF;
		for(iF = varFloatlist.begin();iF != varFloatlist.end();++ iF)
		{
			if((*iF).sqlval != (*(*iF).p))
			{
				mydb.SaveValue((*iF).id,(*(*iF).p));
				(*iF).sqlval = (*(*iF).p);
			}
		}
		QList<struct varDouble>::iterator iD;
		for(iD = varDoublelist.begin();iD != varDoublelist.end();++ iD)
		{
			if((*iD).sqlval != (*(*iD).p))
			{
				mydb.SaveValue((*iD).id,(*(*iD).p));
				(*iD).sqlval = (*(*iD).p);
			}
		}
		for(iD = varLuavarlist.begin();iD != varLuavarlist.end();++ iD)
		{
			if((*iD).sqlval != (*(*iD).p))
			{
				mydb.SaveValue((*iD).id,(*(*iD).p));
				(*iD).sqlval = (*(*iD).p);
			}
		}		
		if (mydb.sqldbopen == true)
		{
			if (mydb.SQLQueueflag == 0)
			{
				if (mydb.SQLQueuechg == 1)
				{
					mydb.SQLQueueflagmutex.lock();
					mydb.SQLQueueflag = 1;
					mydb.SQLQueueflagmutex.unlock();
					QList<QString>::iterator it;

					mydb.SQLmutex.lock();
					mydb.sqldb.transaction();
					for (it = mydb.SQLQueue.begin(); it != mydb.SQLQueue.end();++it)
					{
						mydb.sqldb.exec(*it);
					}
					mydb.sqldb.commit();
					mydb.SQLmutex.unlock();

					mydb.SQLQueue.clear();

					mydb.SQLQueuechg = 0;
				}
			}
			else if(mydb.SQLQueueflag == 1)
			{
				if (mydb.SQLQueuechg2 == 1)
				{
					mydb.SQLQueueflagmutex.lock();
					mydb.SQLQueueflag = 0;
					mydb.SQLQueueflagmutex.unlock();

					QList<QString>::iterator it;

					mydb.SQLmutex.lock();
					mydb.sqldb.transaction();
					for (it = mydb.SQLQueue2.begin(); it != mydb.SQLQueue2.end();++it)
					{
						mydb.sqldb.exec(*it);
					}
					mydb.sqldb.commit();
					mydb.SQLmutex.unlock();

					mydb.SQLQueue2.clear();

					mydb.SQLQueuechg2 = 0;
				}
			}
		}
		msleep(1000);
	}
	if (mydb.sqldbopen == true)
	{
		if (mydb.SQLQueueflag == 0)
		{
			if (mydb.SQLQueuechg == 1)
			{
				mydb.SQLQueueflagmutex.lock();
				mydb.SQLQueueflag = 1;
				mydb.SQLQueueflagmutex.unlock();
				QList<QString>::iterator it;

				mydb.SQLmutex.lock();
				mydb.sqldb.transaction();
				for (it = mydb.SQLQueue.begin(); it != mydb.SQLQueue.end();++it)
				{
					mydb.sqldb.exec(*it);
				}
				mydb.sqldb.commit();
				mydb.SQLmutex.unlock();

				mydb.SQLQueue.clear();

				mydb.SQLQueuechg = 0;
			}
		}
		else if(mydb.SQLQueueflag == 1)
		{
			if (mydb.SQLQueuechg2 == 1)
			{
				mydb.SQLQueueflagmutex.lock();
				mydb.SQLQueueflag = 0;
				mydb.SQLQueueflagmutex.unlock();

				QList<QString>::iterator it;

				mydb.SQLmutex.lock();
				mydb.sqldb.transaction();
				for (it = mydb.SQLQueue2.begin(); it != mydb.SQLQueue2.end();++it)
				{
					mydb.sqldb.exec(*it);
				}
				mydb.sqldb.commit();
				mydb.SQLmutex.unlock();

				mydb.SQLQueue2.clear();

				mydb.SQLQueuechg2 = 0;
			}
		}
	}

}

