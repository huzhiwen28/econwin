#include "luaview.h"
#include <QString>
#include <QtGui/QApplication>
#include <QMap>
#include <QFile>
#include <QMutex>
#include <iostream>
#include <QTextStream>
#include <QPushButton>
#include "econwin.h"
#include "sys.h"
#include "lua.hpp"
extern lua_State* L;

QMap<QString,struct _var> globalvarmap;

//QMap<int,struct _varlist> linevarmap;

QList<struct _filelinevarmap> filelinevarmaplist;

QList<QString> filecontent;
QList<QString> filenamelist;

//lua不支持多线程，采用独占锁
extern QMutex luamutex;

//输入输出用
extern QTextStream cin;  
extern QTextStream cout;
extern QTextStream cerr;

QScrollBar * v;

bool freshgloballuavar = false;
int currentfileindex = 0;

int beginline,endline;
int oldbeginline,oldendline;

Widget::Widget(QWidget *parent)
     : QWidget(parent)
 {
	 chgflag = true;
	 Act_editval  = new QAction(tr("修改值"), this);
	connect(Act_editval, SIGNAL(triggered()), this, SLOT(editval()));
 }

 void Widget::animate()
 {
     //repaint(0,0,400,400);
     repaint();
 } 

 void Widget::paintEvent(QPaintEvent *event)
 {
	 {
		 beginline = v->value() / 16;
		 endline = (v->value() + v->pageStep())/16+1;

		 if(endline > filecontent.count())
		 {	 
			 endline = filecontent.count();
		 }
		 QPainter painter;

		 painter.begin(this);

		 for(int i=beginline;i< endline;i++)
		 {
			 painter.drawText(5,i*16,filecontent[i]);
		 }

		 painter.setPen(QPen(Qt::darkGreen, 1));

		 for(int i=beginline;i< endline;i++)
		 {
			 if(!filelinevarmaplist[currentfileindex].linevarmap.contains(i))
			 {
				 continue;
			 }
			 struct _varlist varlist = filelinevarmaplist[currentfileindex].linevarmap.value(i);

			 for(int ii = 0;ii< varlist.varlist.count();ii++ )
			 {
				 struct _linevar var = varlist.varlist[ii];

				 struct _var gvar = globalvarmap.value(var.name);
				 if(gvar.vartype == 0)
				 {
					 //painter.boundingRect(QRectF(var.loc*6,(varlist.line-2)*16-6,16*10,8),Qt::AlignLeft,QString::number(gvar.varval.ivar));
					 //painter.drawRect(QRectF(var.loc*6,(varlist.line-2)*16-14,6* QString::number(gvar.varval.ivar).length()+2,8));
					 painter.drawText(var.loc*6,(varlist.line-2)*16-6, QString::number(gvar.varval.ivar));

				 }
				 else if(gvar.vartype == 1)
				 {
					 if(gvar.varval.bvar == 0)
					 {
						 painter.drawText(var.loc*6,(varlist.line-2)*16-6, "false");
					 }
					 else
					 {
						 painter.drawText(var.loc*6,(varlist.line-2)*16-6, "true");
					 }
				 }
				 else if(gvar.vartype == 2)
				 {
					 painter.drawText(var.loc*6,(varlist.line-2)*16-6, QString::number(gvar.varval.dvar));
				 }
			 }
		 }
		 painter.end();
	 }
 } 

void Widget::contextMenuEvent(QContextMenuEvent *event)
{
	 for(int i=beginline;i< endline;i++)
	 {
		 if(!filelinevarmaplist[currentfileindex].linevarmap.contains(i))
		 {
			 continue;
		 }
		 struct _varlist varlist = filelinevarmaplist[currentfileindex].linevarmap.value(i);

		 for(int ii = 0;ii< varlist.varlist.count();ii++ )
		 {
			 struct _linevar var = varlist.varlist[ii];

			 struct _var gvar = globalvarmap.value(var.name);
			 if(gvar.vartype == 0)
			 {
				 if( (((var.loc*6) <= event->x()) && (event->x() <=( var.loc*6 + 6* QString::number(gvar.varval.ivar).length()+12)))
					 && ( (((varlist.line-2)*16 -16) <= event->y() ) && (event->y() <= (((varlist.line-2)*16 -16 + 8))))
					 )
				 {
					 QMenu *menu=new QMenu(this);

					 menu->addAction(Act_editval);

					 menu->exec(QCursor::pos());
				 }

			 }
			 else if(gvar.vartype == 1)
			 {
				 if(gvar.varval.bvar == 0)
				 {
					 if( (((var.loc*6) <= event->x()) && (event->x() <=( var.loc*6 + 6* 5+12)))
						 && ( (((varlist.line-2)*16 -16) <= event->y() ) && (event->y() <= (((varlist.line-2)*16 -16 + 8))))
						 )
					 {
						 QMenu *menu=new QMenu(this);

						 menu->addAction(Act_editval);

						 menu->exec(QCursor::pos());
					 }
				 }
				 else
				 {
					 if( (((var.loc*6) <= event->x()) && (event->x() <=( var.loc*6 + 6* 4+12)))
						 && ( (((varlist.line-2)*16 -16) <= event->y() ) && (event->y() <= (((varlist.line-2)*16 -16 + 8))))
						 )
					 {
						 QMenu *menu=new QMenu(this);

						 menu->addAction(Act_editval);

						 menu->exec(QCursor::pos());
					 }
				 }
			 }
			 else if(gvar.vartype == 2)
			 {
				 if( (((var.loc*6) <= event->x()) && (event->x() <=( var.loc*6 + 6* QString::number(gvar.varval.dvar).length()+12)))
					 && ( (((varlist.line-2)*16 -16) <= event->y() ) && (event->y() <= (((varlist.line-2)*16 -16 + 8))))
					 )
				 {
					 QMenu *menu=new QMenu(this);

					 menu->addAction(Act_editval);

					 menu->exec(QCursor::pos());
				 }
			 }
		 }
	 }
}

void Widget::editval()
{
	QMessageBox msgBox;
	msgBox.setText("找不到记录文件");
	msgBox.setWindowTitle("错误");
	msgBox.setStandardButtons(QMessageBox::Yes );
	QAbstractButton* tb = msgBox.button(QMessageBox::Yes);
	tb->setText("确定");
	msgBox.exec();
}

 GLWidget::GLWidget(QWidget *parent)
     :QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
 {
	 textFont.setPixelSize(100);
    textPen = QPen(Qt::black);

 }

 void GLWidget::animate()
 {
     repaint();
 } 

  void GLWidget::paintEvent(QPaintEvent *event)
 {
 	QPainter painter;
	painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

	for(int i=0;i< filecontent.count();i++)
	{
		painter.drawText(5,i*16,filecontent[i]);
	}
	painter.end();
 
 } 

luaview::luaview(QWidget *parent,Qt::WFlags flags)
: QDialog(parent, flags)
{
	currentfileindex = 0;
	ui.setupUi(this);
	for(int i = 0;i < filenamelist.count();i++)
	{
		ui.cbfilenamelist->insertItem(i,filenamelist[i]);
	}

	if(filenamelist.count() >= 1)
	{
		QString filename = QCoreApplication::applicationDirPath() + "/" + filenamelist[0];

		filecontent.clear();
		QFile file(filename);

		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			return;
		QTextStream in(&file);
		QString myline,line;

		myline = in.readLine();
		line = myline.replace("	","    ");

		while (!line.isNull()) {
			myline = in.readLine();
			line = myline.replace("	","    ");
			filecontent.append(line);
		} 

		file.close();
	}

	native = new Widget(this);
	native->setGeometry(30,20,871,filecontent.count()*16);


	//openGL = new GLWidget(this);
	//openGL->setGeometry(30,20,871,filecontent.count()*16);

	scrollArea = new QScrollArea(this);
	scrollArea->setBackgroundRole(QPalette::Light);
	scrollArea->setWidget(native);
	scrollArea->setGeometry(30,30,871,611);
	v = scrollArea->verticalScrollBar();

	if(filenamelist.count() >= 1)
	{
		luamutex.lock();

		//函数名设置值
		lua_getglobal(L,"freshviewedvar");
		lua_pushinteger(L,currentfileindex+1);
		lua_pushinteger(L,0);
		lua_pushinteger(L,v->pageStep()/16+1);
		lua_pcall(L,3,0,0);

		//函数名设置值
		lua_getglobal(L,"freshviewedvarval");
		lua_pcall(L,0,0,0);
		luamutex.unlock();
	}

	first = false;

	//connect(&mytimer, SIGNAL(timeout()), openGL, SLOT(animate()));
	//connect(&mytimer, SIGNAL(timeout()), native, SLOT(animate()));
	connect(&mytimer, SIGNAL(timeout()), this, SLOT(mytimeupdate()));
	mytimer.start(200); //100ms定时
}

luaview::~luaview()
{
	mytimer.disconnect(this);
}

void luaview::closeEvent(QCloseEvent *e)
{
	mytimer.disconnect(this);
	close();
}

void luaview::mytimeupdate()
{
	freshgloballuavar = true;
	mytimer.stop();

	native->animate();
	//openGL->animate();

	mytimer.start(200);

}
void luaview::on_backpb_clicked()
{
	mytimer.stop();
	mytimer.disconnect(this);
	close();
}



void luaview::on_cbfilenamelist_currentIndexChanged ( int index )
{
	//第一次窗口生成的时候不刷新
	if(first == false)
	{
		freshgloballuavar = false;

		mytimer.stop();
		freshgloballuavar = false;

		currentfileindex = index;

		luamutex.lock();

		//函数名设置值
		lua_getglobal(L,"freshviewedvar");
		lua_pushinteger(L,currentfileindex+1);
		lua_pushinteger(L,0);
		lua_pushinteger(L,v->pageStep()/16+1);
		lua_pcall(L,3,0,0);

		//函数名设置值
		lua_getglobal(L,"freshviewedvarval");
		lua_pcall(L,0,0,0);
		luamutex.unlock();

		QString filename = QCoreApplication::applicationDirPath() + "/" + filenamelist[index];

		filecontent.clear();
		QFile file(filename);

		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			return;
		QTextStream in(&file);
		QString myline,line;

		myline = in.readLine();
		line = myline.replace("	","    ");

		while (!line.isNull()) {
			myline = in.readLine();
			line = myline.replace("	","    ");
			filecontent.append(line);
		} 

		file.close();

		native->setGeometry(30,20,871,filecontent.count()*16);
		mytimer.start(200);

	}
}