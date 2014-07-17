/*
本文件提供修改内存全局变量的功能

*/
#include <QMutex>
#include <QString>
#include "lua.hpp"
#include "chgvarval.h"
#include "basicservice.h"

//lua不支持多线程，采用独占锁
extern QMutex luamutex;

struct _tnode{
	char type;
	void* p;
};

chgvarval::chgvarval(QWidget *parent,Qt::WFlags flags)
: QDialog(parent, flags)
{
	ui.setupUi(this);
}

chgvarval::~chgvarval()
{
}

void chgvarval::on_backpb_clicked()
{
	bool ok = false;
	if(chgflag == true)
	{
		if((pt->type) == 1)
		{
			unsigned int v;
			unsigned int* vp = (unsigned int*)(pt->p);
			v =  ui.lineEdit->text().toUInt(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 2)
		{
			int v;
			int* vp = (int*)(pt->p);
			v =  ui.lineEdit->text().toInt(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 3)
		{
			unsigned short v;
			unsigned short* vp = (unsigned short*)(pt->p);
			v =  ui.lineEdit->text().toUShort(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 4)
		{
			short v;
			short* vp = (short*)(pt->p);
			v =  ui.lineEdit->text().toShort(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 5)
		{
			unsigned long long v;
			unsigned long long * vp = (unsigned long long*)(pt->p);
			v =  ui.lineEdit->text().toULongLong(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 6)
		{
			long long v;
			long long * vp = (long long*)(pt->p);
			v =  ui.lineEdit->text().toLongLong(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 7)
		{
			unsigned long v;
			unsigned long * vp = (unsigned long*)(pt->p);
			v =  ui.lineEdit->text().toULong(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 8)
		{
			long v;
			long * vp = (long*)(pt->p);
			v =  ui.lineEdit->text().toLong(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 9)
		{
			float v;
			float * vp = (float*)(pt->p);
			v =  ui.lineEdit->text().toFloat(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 10)
		{
			double v;
			double * vp = (double*)(pt->p);
			v =  ui.lineEdit->text().toDouble(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 11)
		{
			double v;
			double * vp = (double*)(pt->p);
			v =  ui.lineEdit->text().toDouble(&ok);
			if(ok)
			{
				luamutex.lock();
				(*vp) = v;
				luamutex.unlock();
			}
		}
	}

	close();
}
void chgvarval::closeEvent(QCloseEvent *e)
{
	bool ok = false;
	if(chgflag == true)
	{
		if((pt->type) == 1)
		{
			unsigned int v;
			unsigned int* vp = (unsigned int*)(pt->p);
			v =  ui.lineEdit->text().toUInt(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 2)
		{
			int v;
			int* vp = (int*)(pt->p);
			v =  ui.lineEdit->text().toInt(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 3)
		{
			unsigned short v;
			unsigned short* vp = (unsigned short*)(pt->p);
			v =  ui.lineEdit->text().toUShort(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 4)
		{
			short v;
			short* vp = (short*)(pt->p);
			v =  ui.lineEdit->text().toShort(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 5)
		{
			unsigned long long v;
			unsigned long long * vp = (unsigned long long*)(pt->p);
			v =  ui.lineEdit->text().toULongLong(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 6)
		{
			long long v;
			long long * vp = (long long*)(pt->p);
			v =  ui.lineEdit->text().toLongLong(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 7)
		{
			unsigned long v;
			unsigned long * vp = (unsigned long*)(pt->p);
			v =  ui.lineEdit->text().toULong(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 8)
		{
			long v;
			long * vp = (long*)(pt->p);
			v =  ui.lineEdit->text().toLong(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 9)
		{
			float v;
			float * vp = (float*)(pt->p);
			v =  ui.lineEdit->text().toFloat(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 10)
		{
			double v;
			double * vp = (double*)(pt->p);
			v =  ui.lineEdit->text().toDouble(&ok);
			if(ok)
				(*vp) = v;
		}
		else if(pt->type == 11)
		{
			double v;
			double * vp = (double*)(pt->p);
			v =  ui.lineEdit->text().toDouble(&ok);
			if(ok)
			{
				luamutex.lock();
				(*vp) = v;
				luamutex.unlock();
			}
		}

	}

	close();
}

void chgvarval::setnode(struct _tnode* pnode)
{
	pt = pnode;

	if((pt->type) == 1)
	{
		unsigned int* vp = (unsigned int*)(pt->p);
		ui.lineEdit->setText(QString::number((*(vp))));
	}
	else if(pt->type == 2)
	{
		int* vp = (int*)(pt->p);
		ui.lineEdit->setText(QString::number((*(vp))));
	}
	else if(pt->type == 3)
	{
		unsigned short* vp = (unsigned short*)(pt->p);
		ui.lineEdit->setText(QString::number((*(vp))));
	}
	else if(pt->type == 4)
	{
		short* vp = (short*)(pt->p);
		ui.lineEdit->setText(QString::number((*(vp))));
	}
	else if(pt->type == 5)
	{
		unsigned long long * vp = (unsigned long long*)(pt->p);
		ui.lineEdit->setText(QString::number((*(vp))));
	}
	else if(pt->type == 6)
	{
		long long * vp = (long long*)(pt->p);
		ui.lineEdit->setText(QString::number((*(vp))));
	}
	else if(pt->type == 7)
	{
		unsigned long * vp = (unsigned long*)(pt->p);
		ui.lineEdit->setText(QString::number((*(vp))));
	}
	else if(pt->type == 8)
	{
		long * vp = (long*)(pt->p);
		ui.lineEdit->setText(QString::number((*(vp))));
	}
	else if(pt->type == 9)
	{
		float * vp = (float*)(pt->p);
		ui.lineEdit->setText(QString::number((*(vp))));
	}
	else if(pt->type == 10)
	{
		double * vp = (double*)(pt->p);
		ui.lineEdit->setText(QString::number((*(vp))));
	}
	else if(pt->type == 11)
	{
		double * vp = (double*)(pt->p);
		ui.lineEdit->setText(QString::number((*(vp))));
	}
	chgflag = false;
}


void chgvarval::on_lineEdit_textChanged(const QString &)
{
	chgflag = true;
}