/*
本文件提供修改内存全局变量的功能

*/
#ifndef CHGVARVAL_H
#define CHGVARVAL_H

#include <QtGui/QDialog>
#include <QEvent>
#include "ui_chgvarval.h"
#include <Windows.h>
#include <QMutex>
#include <QString>
#include <QWaitCondition>
#include <QPicture>
#include <QPainter>
#include <QTimer>
#include <QList>



class chgvarval : public QDialog
{
	Q_OBJECT

public:
	chgvarval(QWidget *parent = 0, Qt::WFlags flags = 0);
	~chgvarval();
	void setnode(struct _tnode*);
	bool chgflag;

private:
	Ui::chgvarvalClass ui;
	struct _tnode* pt;

protected:
	void closeEvent(QCloseEvent *e);

private slots:
	void on_lineEdit_textChanged(const QString &);
	void on_backpb_clicked();
};


#endif // CHGVARVAL_H