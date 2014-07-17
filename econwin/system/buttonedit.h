#ifndef BUTTONEDIT_H
#define BUTTONEDIT_H

#include <QtGui/QDialog>
#include <QEvent>

#include "ui_buttonedit.h"
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


class buttonedit : public QDialog
{
	Q_OBJECT

public:
	buttonedit(QWidget *parent = 0, Qt::WFlags flags = 0);
	~buttonedit();

	QString text1;
	QString fontcolor;

	QString fontfamily;
	int fontpointSize;
	int fontweight;
	bool fontitalic;

	int operation;
	QString targetvar;
	int targetpage;
	int colortype;
	QString coloroff;

	QString coloron;
	QString colorvar;
	

private:
	Ui::buttoneditClass ui;


protected:
	void closeEvent(QCloseEvent *e);

private slots:
	void on_pb_targetpage_clicked();
	void on_pb_biaoqiancolor_clicked();
	void on_pb_ziti_clicked();
	void on_backpb_clicked();
	void on_pb_targetvar_clicked();
	void on_pb_zhishivar_clicked();
	void on_pb_oncolor_clicked();
	void on_pb_offcolor_clicked();
};
#endif //BUTTONEDIT_H