#ifndef VARVIEW_H
#define VARVIEW_H

#include <QtGui/QDialog>
#include <QEvent>
/*
本文件实现用户定义全局变量观察界面
*/
#include "ui_varview.h"
#include <Windows.h>
#include <QMutex>
#include <QString>
#include <QWaitCondition>
#include <QPicture>
#include <QPainter>
#include <QTimer>
#include <QList>
#include <QScrollArea>
#include <QScrollBar>

struct _tnode{
	char type;
	void* p;
};

extern QList<struct _tnode> nodelist;


class varview : public QDialog
{
	Q_OBJECT

public:
	varview(QWidget *parent = 0, Qt::WFlags flags = 0);
	~varview();
	QScrollBar * vb; //verticalScrollBar
private:
	Ui::varviewClass ui;
	QTimer mytimer;
	QList<struct _tnode> nodelist;

	int allvalcount;

protected:
	void closeEvent(QCloseEvent *e);

private slots:
	void on_backbt_clicked();
	void mytimeupdate();
	void onTableClicked(int,int);

};


#endif // VARVIEW_H
