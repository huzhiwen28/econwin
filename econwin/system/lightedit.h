#ifndef LIGHTEDIT_H
#define LIGHTEDIT_H

#include <QtGui/QDialog>
#include <QEvent>

#include "ui_lightedit.h"
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
#include "econwin.h"


class lightedit : public QDialog
{
	Q_OBJECT

public:
	lightedit(QWidget *parent = 0, Qt::WFlags flags = 0);
	~lightedit();

	struct hmilight data;
	bool init;
	bool comboinit;
	int currentindex;
	bool textinit;

private:
	Ui::lighteditClass ui;


protected:
	void closeEvent(QCloseEvent *e);

private slots:
	void on_combo_dangqianzhuangtai_currentIndexChanged(int index );
	void on_backpb_clicked();
	void on_combo_zhuangtaishuliang_currentIndexChanged(int index );
	void on_pb_targetvar_clicked();
	void on_pb_ziti_clicked();
	void on_pb_wenzicolor_clicked();
	void on_pb_biankuangyanse_clicked();
	void on_pb_juxingyanse_clicked();
	void on_le_biankuanghoudu_textChanged(const QString& text);
	void on_wenzi_textChanged();
};
#endif //LIGHTEDIT_H