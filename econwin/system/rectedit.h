#ifndef RECTEDIT_H
#define RECTEDIT_H

#include <QtGui/QDialog>
#include <QEvent>

#include "ui_rectedit.h"
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


class rectedit : public QDialog
{
	Q_OBJECT

public:
	rectedit(QWidget *parent = 0, Qt::WFlags flags = 0);
	~rectedit();

	int border;//边框宽度
	QString bordercolor;//边框颜色
	QString intercolor;//内部颜色
	

private:
	Ui::recteditClass ui;


protected:
	void closeEvent(QCloseEvent *e);

private slots:
	void on_backpb_clicked();
	void on_pb_biankuangyanse_clicked();
	void on_pb_juxingyanse_clicked();
};
#endif //RECTEDIT_H