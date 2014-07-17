/*
本文件提供修改模块端口值（类型为2）的功能

*/
#ifndef CHGTYPE2_H
#define CHGTYPE2_H

#include <QtGui/QDialog>
#include <QEvent>
#include "ui_chgtype2.h"
#include <Windows.h>
#include <QMutex>
#include <QString>
#include <QWaitCondition>
#include <QPicture>
#include <QPainter>
#include <QTimer>
#include <QList>
#include "device.h"


class chgtype2 : public QDialog
{
	Q_OBJECT

public:
	chgtype2(QWidget *parent = 0, Qt::WFlags flags = 0);
	~chgtype2();
	void setport(port* pp);

private:
	Ui::chgtype2Class ui;
	port* pport;


protected:
	void closeEvent(QCloseEvent *e);

private slots:
	void on_cb0_stateChanged(int);
	void on_cb1_stateChanged(int);
	void on_cb2_stateChanged(int);
	void on_cb3_stateChanged(int);
	void on_cb4_stateChanged(int);
	void on_cb5_stateChanged(int);
	void on_cb6_stateChanged(int);
	void on_cb7_stateChanged(int);
	void on_backpb_clicked();

};


#endif // CHGTYPE2_H
