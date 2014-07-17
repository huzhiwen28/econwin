/*
本文件实现用户定义任务观察界面
*/
#ifndef TASKVIEW_H
#define TASKVIEW_H

#include <QtGui/QDialog>
#include <QEvent>
#include "ui_taskview.h"
#include <Windows.h>
#include <QMutex>
#include <QString>
#include <QWaitCondition>
#include <QPicture>
#include <QPainter>
#include <QTimer>
#include <QList>

class pb: public QPushButton
{
	Q_OBJECT

public:
	pb(QWidget *parent = 0)		;
	~	pb();

	int num;
	int type;
	void setnum(int n);

signals:
	void buttonClicked(int num);

public slots:
	void sendsignal();

};


class taskview : public QDialog
{
	Q_OBJECT

public:
	taskview(QWidget *parent = 0, Qt::WFlags flags = 0);
	~taskview();
	QList<pb*> buttonlist;

private:
	Ui::taskviewClass ui;
	QTimer mytimer;


protected:
	void closeEvent(QCloseEvent *e);

private slots:
	void on_backpb_clicked();
	void mytimeupdate();

};


#endif // TASKVIEW_H
