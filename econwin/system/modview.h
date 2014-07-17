/*
本文件实现模块端口观察功能
*/
#ifndef MODVIEW_H
#define MODVIEW_H

#include <QtGui/QDialog>
#include <QEvent>
#include "ui_modview.h"
#include <Windows.h>
#include <QMutex>
#include <QString>
#include <QWaitCondition>
#include <QPicture>
#include <QPainter>
#include <QTimer>
#include <QList>
#include "device.h"

struct _portnode{
	unsigned char porttype;
	void * pport;
};

class pb2: public QPushButton
{
	Q_OBJECT

public:
	pb2(QWidget *parent = 0)		;
	~	pb2();

	port* pport;
	void setport(port* pp);

signals:
	void buttonClicked(int num);

public slots:
	void sendsignal();
};

class modview : public QDialog
{
	Q_OBJECT

public:
	modview(QWidget *parent = 0, Qt::WFlags flags = 0);
	~modview();

private:
	Ui::modviewClass ui;
	QTimer mytimer;
	bool first;

	QList<struct _portnode> portlist;
	int deviceindex;


protected:
	void closeEvent(QCloseEvent *e);

private slots:
	void on_backpb_clicked();
	void mytimeupdate();
	void on_cbmodid_currentIndexChanged ( int index );

};


#endif // MODVIEW_H
