#include "rectedit.h"

#include <QTextStream>
#include <QList>
#include <QInputDialog>
#include <QColorDialog>
#include <QTextEdit>
#include <QTextDocument>
#include <QFontDialog>

#include "econwin.h"
#include "basicservice.h"
#include "chgvarval.h"


//输入输出用
extern QTextStream cin;  
extern QTextStream cout;
extern QTextStream cerr;
extern econwin * peconwin;
extern QString projecthmifilename;
extern bool projecthmirun;

extern QList<struct _hmiwidget> hmiwidgetlist;
extern struct _hmiproject hmiproject;

//当前选择的控件是哪个
extern int currenthmiwidgetindex;
extern int currenthmipageindex;


rectedit::rectedit(QWidget *parent,Qt::WFlags flags)
: QDialog(parent, flags)
{
	ui.setupUi(this);
	hmirect * prect = (hmirect *)hmiproject.hmipagelist[currenthmipageindex][currenthmiwidgetindex].pdata;

	border= prect->border;
	bordercolor = prect->bordercolor;
	intercolor = prect->intercolor;

	ui.le_biankuanghoudu->setText(QString::number(border));

	QString style;
	style = "background-color: " + bordercolor;
	ui.pb_biankuangyanse->setStyleSheet(style);

	style = "background-color: " + intercolor;
	ui.pb_juxingyanse->setStyleSheet(style);
}

rectedit::~rectedit()
{
}

void rectedit::on_backpb_clicked()
{
	//mytimer.stop();
	//mytimer.disconnect(this);
	hmirect * prect = (hmirect *)hmiproject.hmipagelist[currenthmipageindex][currenthmiwidgetindex].pdata;


	if(prect->border != ui.le_biankuanghoudu->text().toInt())
	{
		peconwin->projectneedsave = true;
		prect->border = ui.le_biankuanghoudu->text().toInt();
	}

	if(prect->bordercolor != bordercolor)
	{
		peconwin->projectneedsave = true;
		prect->bordercolor = bordercolor;
	}
	if(prect->intercolor != intercolor)
	{
		peconwin->projectneedsave = true;
		prect->intercolor = intercolor;
	}

	if(peconwin->projectneedsave)
		peconwin->setWindowTitle(tr("ecomwin：") + projecthmifilename + "*");
	else
		peconwin->setWindowTitle(tr("ecomwin：") + projecthmifilename);

	close();
}
void rectedit::closeEvent(QCloseEvent *e)
{
	//mytimer.disconnect(this);
	close();
}

void rectedit::on_pb_biankuangyanse_clicked()
{
	QColor choosecolor = QColorDialog::getColor(QColor(bordercolor));
	if(choosecolor.isValid())
	{
		bordercolor = choosecolor.name();
		QString style;
		style = "background-color: " + bordercolor;
		ui.pb_biankuangyanse->setStyleSheet(style);
	}

}
void rectedit::on_pb_juxingyanse_clicked()
{
	QColor choosecolor = QColorDialog::getColor(QColor(intercolor));
	if(choosecolor.isValid())
	{
		intercolor = choosecolor.name();
		QString style;
		style = "background-color: " + intercolor;
		ui.pb_juxingyanse->setStyleSheet(style);
	}
}



