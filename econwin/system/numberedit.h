#ifndef NUMBEREDIT_H
#define NUMBEREDIT_H

#include <QtGui/QDialog>
#include <QEvent>

#include "ui_numberedit.h"
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


class numberedit : public QDialog
{
	Q_OBJECT

public:
	numberedit(QWidget *parent = 0, Qt::WFlags flags = 0);
	~numberedit();

	int vartype;//变量类型 0整型 1浮点型
	QString targetvar;//绑定变量

	int zhengshuwei;//整数部分位数
	int xiaoshuwei;//小数部分位数
	int shuru;//是否支持输入

	int fanweijiancha;//范围检查 0不检查 1检查
	int zuixiaozhi;//最小值
	int zuidazhi;//最小值

	QString fontcolor;//文本颜色
	QString fontfamily;//文本字体
	int fontpointSize;//文本大小
	int fontweight;//笔划粗细
	bool fontitalic;//斜体

	int border;//边框宽度
	QString bordercolor;//边框颜色
	QString intercolor;//内部颜色


private:
	Ui::numbereditClass ui;


protected:
	void closeEvent(QCloseEvent *e);

private slots:
	void on_backpb_clicked();
	void on_pb_wenzicolor_clicked();
	void on_pb_ziti_clicked();
	void on_pb_biankuangyanse_clicked();
	void on_pb_juxingyanse_clicked();
	void on_pb_targetvar_clicked();
};
#endif //NUMBEREDIT_H