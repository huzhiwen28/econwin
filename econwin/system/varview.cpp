/*
本文件实现用户定义全局变量观察界面
*/
#include "varview.h"
#include <QTableWidgetItem>
#include "basicservice.h"
#include "chgvarval.h"
#include <QTextStream> 

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

//输入输出用
extern QTextStream cin;  
extern QTextStream cout;
extern QTextStream cerr;


varview::varview(QWidget *parent,Qt::WFlags flags)
: QDialog(parent, flags)
{
	ui.setupUi(this);
	//ui.vartable->setShowGrid(false);
	ui.vartable->setRowCount(varUIntlist.count() + varIntlist.count() + varUShortlist.count() + 
		varShortlist.count() + varULongLonglist.count() + varLongLonglist.count() + varULonglist.count() + 
		varLonglist.count() + varFloatlist.count() + varDoublelist.count() + varLuavarlist.count());

	int col,row;
	col = 0;
	row = 0;
	struct _tnode t;

	//查看数据是否改变
	QList<struct varUInt>::iterator iUI;
	for(iUI = varUIntlist.begin();iUI != varUIntlist.end();++ iUI)
	{
		t.type = 1;
		t.p = ((void *)(*iUI).p);
		nodelist.append(t);

		ui.vartable->setItem(col,0, new QTableWidgetItem((*iUI).id));
		ui.vartable->setItem(col,1, new QTableWidgetItem("unsigned int"));
		ui.vartable->setItem(col,2, new QTableWidgetItem(QString::number(*(*iUI).p)));

		ui.vartable->item(col,0)->setFlags(0);
		ui.vartable->item(col,1)->setFlags(0);
		ui.vartable->item(col,2)->setFlags(0);
		ui.vartable->item(col,0)->setForeground(Qt::black);
		ui.vartable->item(col,1)->setForeground(Qt::black);
		ui.vartable->item(col,2)->setForeground(Qt::black);

		col ++;
	}
	QList<struct varInt>::iterator iI;
	for(iI = varIntlist.begin();iI != varIntlist.end();++ iI)
	{
		t.type = 2;
		t.p = ((void *)(*iI).p);
		nodelist.append(t);

		ui.vartable->setItem(col,0, new QTableWidgetItem((*iI).id));
		ui.vartable->setItem(col,1, new QTableWidgetItem("int"));
		ui.vartable->setItem(col,2, new QTableWidgetItem(QString::number(*(*iI).p)));
		ui.vartable->item(col,0)->setFlags(0);
		ui.vartable->item(col,1)->setFlags(0);
		ui.vartable->item(col,2)->setFlags(0);
		ui.vartable->item(col,0)->setForeground(Qt::black);
		ui.vartable->item(col,1)->setForeground(Qt::black);
		ui.vartable->item(col,2)->setForeground(Qt::black);
		col ++;
	}
	QList<struct varUShort>::iterator iUS;
	for(iUS = varUShortlist.begin();iUS != varUShortlist.end();++ iUS)
	{
		t.type = 3;
		t.p = ((void *)(*iUS).p);
		nodelist.append(t);

		ui.vartable->setItem(col,0, new QTableWidgetItem((*iUS).id));
		ui.vartable->setItem(col,1, new QTableWidgetItem("unsigned short"));
		ui.vartable->setItem(col,2, new QTableWidgetItem(QString::number(*(*iUS).p)));
		ui.vartable->item(col,0)->setFlags(0);
		ui.vartable->item(col,1)->setFlags(0);
		ui.vartable->item(col,2)->setFlags(0);
		ui.vartable->item(col,0)->setForeground(Qt::black);
		ui.vartable->item(col,1)->setForeground(Qt::black);
		ui.vartable->item(col,2)->setForeground(Qt::black);
		col ++;
	}
	QList<struct varShort>::iterator iS;
	for(iS = varShortlist.begin();iS != varShortlist.end();++ iS)
	{
		t.type = 4;
		t.p = ((void *)(*iS).p);
		nodelist.append(t);

		ui.vartable->setItem(col,0, new QTableWidgetItem((*iS).id));
		ui.vartable->setItem(col,1, new QTableWidgetItem("short"));
		ui.vartable->setItem(col,2, new QTableWidgetItem(QString::number(*(*iS).p)));
		ui.vartable->item(col,0)->setFlags(0);
		ui.vartable->item(col,1)->setFlags(0);
		ui.vartable->item(col,2)->setFlags(0);
		ui.vartable->item(col,0)->setForeground(Qt::black);
		ui.vartable->item(col,1)->setForeground(Qt::black);
		ui.vartable->item(col,2)->setForeground(Qt::black);
		col ++;
	}
	QList<struct varULongLong>::iterator iULL;
	for(iULL = varULongLonglist.begin();iULL != varULongLonglist.end();++ iULL)
	{
		t.type = 5;
		t.p = ((void *)(*iULL).p);
		nodelist.append(t);

		ui.vartable->setItem(col,0, new QTableWidgetItem((*iULL).id));
		ui.vartable->setItem(col,1, new QTableWidgetItem("unsigned long long"));
		ui.vartable->setItem(col,2, new QTableWidgetItem(QString::number(*(*iULL).p)));
		ui.vartable->item(col,0)->setFlags(0);
		ui.vartable->item(col,1)->setFlags(0);
		ui.vartable->item(col,2)->setFlags(0);
		ui.vartable->item(col,0)->setForeground(Qt::black);
		ui.vartable->item(col,1)->setForeground(Qt::black);
		ui.vartable->item(col,2)->setForeground(Qt::black);
		col ++;
	}
	QList<struct varLongLong>::iterator iLL;
	for(iLL = varLongLonglist.begin();iLL != varLongLonglist.end();++ iLL)
	{
		t.type = 6;
		t.p = ((void *)(*iLL).p);
		nodelist.append(t);

		ui.vartable->setItem(col,0, new QTableWidgetItem((*iLL).id));
		ui.vartable->setItem(col,1, new QTableWidgetItem("long long"));
		ui.vartable->setItem(col,2, new QTableWidgetItem(QString::number(*(*iLL).p)));
		ui.vartable->item(col,0)->setFlags(0);
		ui.vartable->item(col,1)->setFlags(0);
		ui.vartable->item(col,2)->setFlags(0);
		ui.vartable->item(col,0)->setForeground(Qt::black);
		ui.vartable->item(col,1)->setForeground(Qt::black);
		ui.vartable->item(col,2)->setForeground(Qt::black);
		col ++;
	}
	QList<struct varULong>::iterator iUL;
	for(iUL = varULonglist.begin();iUL != varULonglist.end();++ iUL)
	{
		t.type = 7;
		t.p = ((void *)(*iUL).p);
		nodelist.append(t);

		ui.vartable->setItem(col,0, new QTableWidgetItem((*iUL).id));
		ui.vartable->setItem(col,1, new QTableWidgetItem("unsigned long"));
		ui.vartable->setItem(col,2, new QTableWidgetItem(QString::number(*(*iUL).p)));
		ui.vartable->item(col,0)->setFlags(0);
		ui.vartable->item(col,1)->setFlags(0);
		ui.vartable->item(col,2)->setFlags(0);
		ui.vartable->item(col,0)->setForeground(Qt::black);
		ui.vartable->item(col,1)->setForeground(Qt::black);
		ui.vartable->item(col,2)->setForeground(Qt::black);
		col ++;
	}
	QList<struct varLong>::iterator iL;
	for(iL = varLonglist.begin();iL != varLonglist.end();++ iL)
	{
		t.type = 8;
		t.p = ((void *)(*iL).p);
		nodelist.append(t);

		ui.vartable->setItem(col,0, new QTableWidgetItem((*iL).id));
		ui.vartable->setItem(col,1, new QTableWidgetItem("long"));
		ui.vartable->setItem(col,2, new QTableWidgetItem(QString::number(*(*iL).p)));
		ui.vartable->item(col,0)->setFlags(0);
		ui.vartable->item(col,1)->setFlags(0);
		ui.vartable->item(col,2)->setFlags(0);
		ui.vartable->item(col,0)->setForeground(Qt::black);
		ui.vartable->item(col,1)->setForeground(Qt::black);
		ui.vartable->item(col,2)->setForeground(Qt::black);
		col ++;
	}
	QList<struct varFloat>::iterator iF;
	for(iF = varFloatlist.begin();iF != varFloatlist.end();++ iF)
	{
		t.type = 9;
		t.p = ((void *)(*iF).p);
		nodelist.append(t);

		ui.vartable->setItem(col,0, new QTableWidgetItem((*iF).id));
		ui.vartable->setItem(col,1, new QTableWidgetItem("float"));
		ui.vartable->setItem(col,2, new QTableWidgetItem(QString::number(*(*iF).p)));
		ui.vartable->item(col,0)->setFlags(0);
		ui.vartable->item(col,1)->setFlags(0);
		ui.vartable->item(col,2)->setFlags(0);
		ui.vartable->item(col,0)->setForeground(Qt::black);
		ui.vartable->item(col,1)->setForeground(Qt::black);
		ui.vartable->item(col,2)->setForeground(Qt::black);
		col ++;
	}
	QList<struct varDouble>::iterator iD;
	for(iD = varDoublelist.begin();iD != varDoublelist.end();++ iD)
	{
		t.type = 10;
		t.p = ((void *)(*iD).p);
		nodelist.append(t);

		ui.vartable->setItem(col,0, new QTableWidgetItem((*iD).id));
		ui.vartable->setItem(col,1, new QTableWidgetItem("double"));
		ui.vartable->setItem(col,2, new QTableWidgetItem(QString::number(*(*iD).p)));
		ui.vartable->item(col,0)->setFlags(0);
		ui.vartable->item(col,1)->setFlags(0);
		ui.vartable->item(col,2)->setFlags(0);
		ui.vartable->item(col,0)->setForeground(Qt::black);
		ui.vartable->item(col,1)->setForeground(Qt::black);
		ui.vartable->item(col,2)->setForeground(Qt::black);
		col ++;
	}

	for(iD = varLuavarlist.begin();iD != varLuavarlist.end();++ iD)
	{
		//lua double
		t.type = 11;
		t.p = ((void *)(*iD).p);
		nodelist.append(t);

		ui.vartable->setItem(col,0, new QTableWidgetItem((*iD).id));
		ui.vartable->setItem(col,1, new QTableWidgetItem("double"));
		ui.vartable->setItem(col,2, new QTableWidgetItem(QString::number(*(*iD).p)));
		ui.vartable->item(col,0)->setFlags(0);
		ui.vartable->item(col,1)->setFlags(0);
		ui.vartable->item(col,2)->setFlags(0);
		ui.vartable->item(col,0)->setForeground(Qt::black);
		ui.vartable->item(col,1)->setForeground(Qt::black);
		ui.vartable->item(col,2)->setForeground(Qt::black);
		col ++;
	}
	vb = ui.vartable->verticalScrollBar();
	allvalcount = col;

	connect(&mytimer, SIGNAL(timeout()), this, SLOT(mytimeupdate()));
	mytimer.start(200); //100ms定时

	connect(ui.vartable,SIGNAL(cellClicked( int, int)),this,SLOT(onTableClicked(int,int)));


	//ui.vartable->setRowCount(2);
}

varview::~varview()
{
}

void varview::on_backbt_clicked()
{
	//mytimer.stop();
	mytimer.disconnect(this);
	close();
}
void varview::closeEvent(QCloseEvent *e)
{
	mytimer.disconnect(this);
	close();
}

//局部刷新表格值
void varview::mytimeupdate()
{
	int beginline,endline;

	beginline = vb->value();
	endline = (vb->value() + vb->pageStep()) +1;
	if(endline > allvalcount )
	{	 
		endline = allvalcount;
	}

	for(int i = beginline;i < endline;i++)
	{
		struct _tnode tnode =  nodelist[i];
		if(tnode.type == 1)
		{
			unsigned int* vp = (unsigned int*)(tnode.p);
			ui.vartable->item(i,2)->setText(QString::number(*vp));
		}
		else if(tnode.type == 2)
		{
			int* vp = (int*)(tnode.p);
			ui.vartable->item(i,2)->setText(QString::number(*vp));
		}
		else if(tnode.type == 3)
		{
			unsigned short* vp = (unsigned short*)(tnode.p);
			ui.vartable->item(i,2)->setText(QString::number(*vp));
		}
		else if(tnode.type == 4)
		{
			short* vp = (short*)(tnode.p);
			ui.vartable->item(i,2)->setText(QString::number(*vp));
		}
		else if(tnode.type == 5)
		{
			unsigned long long * vp = (unsigned long long*)(tnode.p);
			ui.vartable->item(i,2)->setText(QString::number(*vp));
		}
		else if(tnode.type == 6)
		{
			long long * vp = (long long*)(tnode.p);
			ui.vartable->item(i,2)->setText(QString::number(*vp));
		}
		else if(tnode.type == 7)
		{
			unsigned long * vp = (unsigned long*)(tnode.p);
			ui.vartable->item(i,2)->setText(QString::number(*vp));
		}
		else if(tnode.type == 8)
		{
			long * vp = (long*)(tnode.p);
			ui.vartable->item(i,2)->setText(QString::number(*vp));
		}
		else if(tnode.type == 9)
		{
			float * vp = (float*)(tnode.p);
			ui.vartable->item(i,2)->setText(QString::number(*vp));
		}
		else if(tnode.type == 10)
		{
			double * vp = (double*)(tnode.p);
			ui.vartable->item(i,2)->setText(QString::number(*vp));
		}
		else if(tnode.type == 11)
		{
			double * vp = (double*)(tnode.p);
			ui.vartable->item(i,2)->setText(QString::number(*vp));
		}
	}
}

//参数设置输入框
void varview::onTableClicked(int row,int col)
{
	if(col == 2)
	{
		chgvarval Dlg;
		Dlg.setnode(&(nodelist[row]));
		Dlg.exec();
	}
}