/*
本文件实现模块端口观察功能
*/
#include "modview.h"
#include <QTableWidgetItem>
#include "basicservice.h"
#include "controltask.h"
#include "device.h"
#include <QLabel>
#include "taskview.h"
#include "chgtype2.h"

//端口类型0界面
struct type0{
	QLabel* portname;//端口名称
	QLabel* bitstate;//端口位值
	QLabel* bitnum;//端口位编号
	union inport* pval;//端口指向的值指针
};

//端口类型2界面
struct type2{
	QLabel* portname;//端口名称
	QLabel* bitstate;//端口位值
	QLabel* bitnum;//端口位编号
	pb2* pbwidget;//按钮
	union outport* pval;//端口指向的值指针
};


//产生信号的按钮
pb2::pb2(QWidget *parent) :
QPushButton(parent)
{
	connect(this, SIGNAL(clicked()), this, SLOT(sendsignal()));
}

//发送信号
void pb2::sendsignal()
{
	chgtype2 Dlg;
	Dlg.setport(pport);
	Dlg.exec();
}

//设置端口指针
void pb2::setport(port* pp)
{
	pport = pp;
}

pb2::~pb2()
{

}

modview::modview(QWidget *parent,Qt::WFlags flags)
: QDialog(parent, flags)
{
	ui.setupUi(this);

	first = true;
	int nCount = 0;
	QList<struct _devicenode>::iterator imod;
	for(imod = devicenodes.begin();imod != devicenodes.end();++ imod)
	{
		ui.cbmodid->insertItem(nCount,QString::number((*imod).id));
		nCount ++;
	}

	deviceindex = 0;

	//构造第一个模块
	if(devicenodes[0].moduletype == 1)
	{
		ui.lineEdit->setText("107");
		struct tdevice107 *pdevice = (struct tdevice107 *)devicenodes[0].pdevice;
		int portnum = sizeof(pdevice->ports)/sizeof(struct port);

		struct _portnode node;
		int yloc = 0;
		pb* pbwidget;

		for(int i = 0;i< portnum;i++)
		{
			if(pdevice->ports[i].type == 0)
			{
				union inport *pval =  (union inport*)pdevice->ports[i].pv;

				struct type0 *typenode = new type0();
				typenode->portname = new QLabel(ui.portsview);
				typenode->portname->setGeometry(5,yloc+10,150,30);
				typenode->portname->setText(QString("输入端口") + QString::number(i));

				typenode->bitstate = new QLabel(ui.portsview);
				typenode->bitstate->setGeometry(70,yloc+30,150,30);
				QString bitstate = QString("[ ");
				for(int ii= 7 ;ii >= 0;ii--)
				{

					if((((pval->inportall) >> ii) & 0x01) == 0x01)
					{
						bitstate = bitstate + QString("1 ");
					}
					else
					{
						bitstate = bitstate + QString("0 ");
					}
				}
				bitstate = bitstate + QString("]");

				typenode->bitstate->setText(bitstate);

				typenode->bitnum = new QLabel(ui.portsview);
				typenode->bitnum->setGeometry(70,yloc+10,150,30);
				typenode->bitnum->setText("位[ 7 6 5 4 3 2 1 0 ]");

				typenode->pval = pval;

				yloc += 60;

				node.porttype = pdevice->ports[i].type;
				node.pport = (void*)typenode;
				portlist.append(node);
			}

			else if(pdevice->ports[i].type == 2)
			{
				union outport *pval =  (union outport*)pdevice->ports[i].pv;

				struct type2 *typenode = new type2();
				typenode->portname = new QLabel(ui.portsview);
				typenode->portname->setGeometry(5,yloc+10,150,30);
				typenode->portname->setText(QString("输出端口") + QString::number(i));

				typenode->bitstate = new QLabel(ui.portsview);
				typenode->bitstate->setGeometry(70,yloc+30,150,30);
				QString bitstate = QString("[ ");
				for(int ii= 7 ;ii >= 0;ii--)
				{

					if((((pval->outportall) >> ii) & 0x01) == 0x01)
					{
						bitstate = bitstate + QString("1 ");
					}
					else
					{
						bitstate = bitstate + QString("0 ");
					}
				}
				bitstate = bitstate + QString("]");

				typenode->bitstate->setText(bitstate);

				typenode->bitnum = new QLabel(ui.portsview);
				typenode->bitnum->setGeometry(70,yloc+10,150,30);
				typenode->bitnum->setText("位[ 7 6 5 4 3 2 1 0 ]");

				typenode->pval = pval;

				typenode->pbwidget = new pb2(ui.portsview);
				typenode->pbwidget->setText("修改");
				typenode->pbwidget->setport(pdevice->ports + i);
				typenode->pbwidget->setGeometry(200,yloc+10,80,30);

				yloc += 60;

				node.porttype = pdevice->ports[i].type;
				node.pport = (void*)typenode;
				portlist.append(node);
			}
		}
	}
	else if(devicenodes[0].moduletype == 2)
	{
		ui.lineEdit->setText("207");
		struct tdevice207 *pdevice = (struct tdevice207 *)devicenodes[0].pdevice;
		int portnum = sizeof(pdevice->ports)/sizeof(struct port);

		struct _portnode node;
		int yloc = 0;
		pb* pbwidget;

		for(int i = 0;i< portnum;i++)
		{
			if(pdevice->ports[i].type == 0)
			{
				union inport *pval =  (union inport*)pdevice->ports[i].pv;

				struct type0 *typenode = new type0();
				typenode->portname = new QLabel(ui.portsview);
				typenode->portname->setGeometry(5,yloc+10,150,30);
				typenode->portname->setText(QString("输入端口") + QString::number(i));

				typenode->bitstate = new QLabel(ui.portsview);
				typenode->bitstate->setGeometry(70,yloc+30,150,30);
				QString bitstate = QString("[ ");
				for(int ii= 7 ;ii >= 0;ii--)
				{

					if((((pval->inportall) >> ii) & 0x01) == 0x01)
					{
						bitstate = bitstate + QString("1 ");
					}
					else
					{
						bitstate = bitstate + QString("0 ");
					}
				}
				bitstate = bitstate + QString("]");

				typenode->bitstate->setText(bitstate);

				typenode->bitnum = new QLabel(ui.portsview);
				typenode->bitnum->setGeometry(70,yloc+10,150,30);
				typenode->bitnum->setText("位[ 7 6 5 4 3 2 1 0 ]");

				typenode->pval = pval;

				yloc += 60;

				node.porttype = pdevice->ports[i].type;
				node.pport = (void*)typenode;
				portlist.append(node);
			}

			else if(pdevice->ports[i].type == 2)
			{
				union outport *pval =  (union outport*)pdevice->ports[i].pv;

				struct type2 *typenode = new type2();
				typenode->portname = new QLabel(ui.portsview);
				typenode->portname->setGeometry(5,yloc+10,150,30);
				typenode->portname->setText(QString("输出端口") + QString::number(i));

				typenode->bitstate = new QLabel(ui.portsview);
				typenode->bitstate->setGeometry(70,yloc+30,150,30);
				QString bitstate = QString("[ ");
				for(int ii= 7 ;ii >= 0;ii--)
				{

					if((((pval->outportall) >> ii) & 0x01) == 0x01)
					{
						bitstate = bitstate + QString("1 ");
					}
					else
					{
						bitstate = bitstate + QString("0 ");
					}
				}
				bitstate = bitstate + QString("]");

				typenode->bitstate->setText(bitstate);

				typenode->bitnum = new QLabel(ui.portsview);
				typenode->bitnum->setGeometry(70,yloc+10,150,30);
				typenode->bitnum->setText("位[ 7 6 5 4 3 2 1 0 ]");

				typenode->pval = pval;

				typenode->pbwidget = new pb2(ui.portsview);
				typenode->pbwidget->setText("修改");
				typenode->pbwidget->setport(pdevice->ports + i);
				typenode->pbwidget->setGeometry(200,yloc+10,80,30);

				yloc += 60;

				node.porttype = pdevice->ports[i].type;
				node.pport = (void*)typenode;
				portlist.append(node);
			}
		}
	}



	first = false;

	connect(&mytimer, SIGNAL(timeout()), this, SLOT(mytimeupdate()));
	mytimer.start(200); //100ms定时

	//ui.vartable->setRowCount(2);
}

modview::~modview()
{
	QList<struct _portnode>::iterator iport;
	for(iport = portlist.begin();iport != portlist.end();++ iport)
	{
		if((*iport).porttype == 0)
		{
			struct type0 *typenode = (struct type0 *)(*iport).pport;
			delete typenode;
		}
		else if((*iport).porttype == 2)
		{
			struct type2 *typenode = (struct type2 *)(*iport).pport;
			delete typenode;
		}
	}
}

void modview::on_backpb_clicked()
{
	//mytimer.stop();
	mytimer.disconnect(this);
	close();
}
void modview::on_cbmodid_currentIndexChanged ( int index )
{
	//第一次窗口生成的时候不刷新
	if(first == false)
	{
		//删除原来控件，防止内存泄漏
		QList<struct _portnode>::iterator iport;
		for(iport = portlist.begin();iport != portlist.end();++ iport)
		{
			if((*iport).porttype == 0)
			{
				struct type0 *typenode = (struct type0 *)(*iport).pport;

				delete typenode->portname;
				delete typenode->bitstate;
				delete typenode->bitnum;

				delete typenode;
			}
			else if((*iport).porttype == 2)
			{
				struct type2 *typenode = (struct type2 *)(*iport).pport;

				delete typenode->portname;
				delete typenode->bitstate;
				delete typenode->bitnum;
				delete typenode->pbwidget;

				delete typenode;
			}
		}
		portlist.clear();

		if(devicenodes[index].moduletype == 1)
		{
			ui.lineEdit->setText("107");
			struct tdevice107 *pdevice = (struct tdevice107 *)devicenodes[index].pdevice;
			int portnum = sizeof(pdevice->ports)/sizeof(struct port);

			struct _portnode node;
			int yloc = 0;
			//动态生成控件并显示
			for(int i = 0;i< portnum;i++)
			{
				if(pdevice->ports[i].type == 0)
				{
					union inport *pval =  (union inport*)pdevice->ports[i].pv;

					struct type0 *typenode = new type0();
					typenode->portname = new QLabel(ui.portsview);
					typenode->portname->setGeometry(5,yloc+10,150,30);
					typenode->portname->setText(QString("输入端口") + QString::number(i));
					typenode->portname->show();


					typenode->bitstate = new QLabel(ui.portsview);
					typenode->bitstate->setGeometry(70,yloc+30,150,30);
					QString bitstate = QString("值[ ");
					for(int ii= 7 ;ii >= 0;ii--)
					{

						if((((pval->inportall) >> ii) & 0x01) == 0x01)
						{
							bitstate = bitstate + QString("1 ");
						}
						else
						{
							bitstate = bitstate + QString("0 ");
						}
					}
					bitstate = bitstate + QString("]");

					typenode->bitstate->setText(bitstate);
					typenode->bitstate->show();

					typenode->bitnum = new QLabel(ui.portsview);
					typenode->bitnum->setGeometry(70,yloc+10,150,30);
					typenode->bitnum->setText("位[ 7 6 5 4 3 2 1 0 ]");
					typenode->bitnum->show();

					typenode->pval = pval;

					yloc += 60;


					node.porttype = pdevice->ports[i].type;
					node.pport = (void*)typenode;
					portlist.append(node);
				}

				if(pdevice->ports[i].type == 2)
				{
					union outport *pval =  (union outport*)pdevice->ports[i].pv;

					struct type2 *typenode = new type2();
					typenode->portname = new QLabel(ui.portsview);
					typenode->portname->setGeometry(5,yloc+10,150,30);
					typenode->portname->setText(QString("输出端口") + QString::number(i));
					typenode->portname->show();


					typenode->bitstate = new QLabel(ui.portsview);
					typenode->bitstate->setGeometry(70,yloc+30,150,30);
					QString bitstate = QString("值[ ");
					for(int ii= 7 ;ii >= 0;ii--)
					{

						if((((pval->outportall) >> ii) & 0x01) == 0x01)
						{
							bitstate = bitstate + QString("1 ");
						}
						else
						{
							bitstate = bitstate + QString("0 ");
						}
					}
					bitstate = bitstate + QString("]");

					typenode->bitstate->setText(bitstate);
					typenode->bitstate->show();

					typenode->bitnum = new QLabel(ui.portsview);
					typenode->bitnum->setGeometry(70,yloc+10,150,30);
					typenode->bitnum->setText("位[ 7 6 5 4 3 2 1 0 ]");
					typenode->bitnum->show();

					typenode->pval = pval;

					typenode->pbwidget = new pb2(ui.portsview);
					typenode->pbwidget->setText("修改");
					typenode->pbwidget->setport(pdevice->ports + i);
					typenode->pbwidget->setGeometry(200,yloc+10,80,30);
					typenode->pbwidget->show();

					yloc += 60;


					node.porttype = pdevice->ports[i].type;
					node.pport = (void*)typenode;
					portlist.append(node);
				}
			}
		}
		else if(devicenodes[index].moduletype == 2)
		{
			ui.lineEdit->setText("207");
			struct tdevice207 *pdevice = (struct tdevice207 *)devicenodes[index].pdevice;
			int portnum = sizeof(pdevice->ports)/sizeof(struct port);

			struct _portnode node;
			int yloc = 0;
			//动态生成控件并显示
			for(int i = 0;i< portnum;i++)
			{
				if(pdevice->ports[i].type == 0)
				{
					union inport *pval =  (union inport*)pdevice->ports[i].pv;

					struct type0 *typenode = new type0();
					typenode->portname = new QLabel(ui.portsview);
					typenode->portname->setGeometry(5,yloc+10,150,30);
					typenode->portname->setText(QString("输入端口") + QString::number(i));
					typenode->portname->show();


					typenode->bitstate = new QLabel(ui.portsview);
					typenode->bitstate->setGeometry(70,yloc+30,150,30);
					QString bitstate = QString("值[ ");
					for(int ii= 7 ;ii >= 0;ii--)
					{

						if((((pval->inportall) >> ii) & 0x01) == 0x01)
						{
							bitstate = bitstate + QString("1 ");
						}
						else
						{
							bitstate = bitstate + QString("0 ");
						}
					}
					bitstate = bitstate + QString("]");

					typenode->bitstate->setText(bitstate);
					typenode->bitstate->show();

					typenode->bitnum = new QLabel(ui.portsview);
					typenode->bitnum->setGeometry(70,yloc+10,150,30);
					typenode->bitnum->setText("位[ 7 6 5 4 3 2 1 0 ]");
					typenode->bitnum->show();

					typenode->pval = pval;

					yloc += 60;


					node.porttype = pdevice->ports[i].type;
					node.pport = (void*)typenode;
					portlist.append(node);
				}

				if(pdevice->ports[i].type == 2)
				{
					union outport *pval =  (union outport*)pdevice->ports[i].pv;

					struct type2 *typenode = new type2();
					typenode->portname = new QLabel(ui.portsview);
					typenode->portname->setGeometry(5,yloc+10,150,30);
					typenode->portname->setText(QString("输出端口") + QString::number(i));
					typenode->portname->show();


					typenode->bitstate = new QLabel(ui.portsview);
					typenode->bitstate->setGeometry(70,yloc+30,150,30);
					QString bitstate = QString("值[ ");
					for(int ii= 7 ;ii >= 0;ii--)
					{

						if((((pval->outportall) >> ii) & 0x01) == 0x01)
						{
							bitstate = bitstate + QString("1 ");
						}
						else
						{
							bitstate = bitstate + QString("0 ");
						}
					}
					bitstate = bitstate + QString("]");

					typenode->bitstate->setText(bitstate);
					typenode->bitstate->show();

					typenode->bitnum = new QLabel(ui.portsview);
					typenode->bitnum->setGeometry(70,yloc+10,150,30);
					typenode->bitnum->setText("位[ 7 6 5 4 3 2 1 0 ]");
					typenode->bitnum->show();

					typenode->pval = pval;

					typenode->pbwidget = new pb2(ui.portsview);
					typenode->pbwidget->setText("修改");
					typenode->pbwidget->setport(pdevice->ports + i);
					typenode->pbwidget->setGeometry(200,yloc+10,80,30);
					typenode->pbwidget->show();

					yloc += 60;


					node.porttype = pdevice->ports[i].type;
					node.pport = (void*)typenode;
					portlist.append(node);
				}
			}
		}

	}
}

void modview::closeEvent(QCloseEvent *e)
{
	mytimer.disconnect(this);
	close();
}

void modview::mytimeupdate()
{
	QList<struct _portnode>::iterator iport;
	for(iport = portlist.begin();iport != portlist.end();++ iport)
	{
		if((*iport).porttype == 0)
		{
			struct type0 *typenode = (struct type0 *)(*iport).pport;
			QString bitstate = QString("值[ ");
			for(int i= 7 ;i >= 0;i--)
			{

				if((((typenode->pval->inportall) >> i) & 0x01) == 0x01)
				{
					bitstate = bitstate + QString("1 ");
				}
				else
				{
					bitstate = bitstate + QString("0 ");
				}
			}
			bitstate = bitstate + QString("]");

			typenode->bitstate->setText(bitstate);
		}

		else if((*iport).porttype == 2)
		{
			struct type2 *typenode = (struct type2 *)(*iport).pport;
			QString bitstate = QString("值[ ");
			for(int i= 7 ;i >= 0;i--)
			{

				if((((typenode->pval->outportall) >> i) & 0x01) == 0x01)
				{
					bitstate = bitstate + QString("1 ");
				}
				else
				{
					bitstate = bitstate + QString("0 ");
				}
			}
			bitstate = bitstate + QString("]");

			typenode->bitstate->setText(bitstate);
		}
	}

}

