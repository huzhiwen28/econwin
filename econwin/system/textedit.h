#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QtGui/QDialog>
#include <QEvent>

#include "ui_textedit.h"
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


class textedit : public QDialog
{
	Q_OBJECT

public:
	textedit(QWidget *parent = 0, Qt::WFlags flags = 0);
	~textedit();

	QString text;//文本
	QString fontcolor;//文本颜色
	QString fontfamily;//文本字体
	int fontpointSize;//文本大小
	int fontweight;//笔划粗细
	bool fontitalic;//斜体

	int touming;//0 透明 1 不透明

	int border;//边框宽度
	QString bordercolor;//边框颜色
	QString intercolor;//内部颜色
	

private:
	Ui::texteditClass ui;


protected:
	void closeEvent(QCloseEvent *e);

private slots:
	void on_backpb_clicked();
	void on_pb_wenzicolor_clicked();
	void on_pb_ziti_clicked();
	void on_pb_biankuangyanse_clicked();
	void on_pb_juxingyanse_clicked();
};
#endif //TEXTEDIT_H