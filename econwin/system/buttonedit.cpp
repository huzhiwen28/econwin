#include "buttonedit.h"

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

extern QList<struct varUInt> varUIntlist;
extern QList<struct varInt> varIntlist;
extern QList<struct varUShort> varUShortlist;
extern QList<struct varShort> varShortlist;
extern QList<struct varULongLong> varULongLonglist;
extern QList<struct varLongLong> varLongLonglist;
extern QList<struct varULong> varULonglist;
extern QList<struct varLong> varLonglist;
extern QList<struct varFloat> varFloatlist;
extern QList<struct varDouble> varDoublelist;

//输入输出用
extern QTextStream cin;  
extern QTextStream cout;
extern QTextStream cerr;
extern econwin * peconwin;
extern QString projecthmifilename;
extern bool projecthmirun;

//extern QList<struct _hmiwidget> hmiwidgetlist;
extern struct _hmiproject hmiproject;

//当前选择的控件是哪个
extern int currenthmiwidgetindex;
extern int currenthmipageindex;


buttonedit::buttonedit(QWidget *parent,Qt::WFlags flags)
: QDialog(parent, flags)
{
	ui.setupUi(this);
	hmipb * ppb = (hmipb *)hmiproject.hmipagelist[currenthmipageindex][currenthmiwidgetindex].pdata;

	text1 = ppb->text;
	fontcolor = ppb->fontcolor;

	fontfamily = ppb->fontfamily;
	fontpointSize = ppb->fontpointSize;
	fontweight = ppb->fontweight;
	fontitalic = ppb->fontitalic;

	operation= ppb->operation;
	targetvar= ppb->targetvar;
	targetpage = ppb->targetpage;
	colortype= ppb->colortype;
	coloroff= ppb->coloroff;
	coloron = ppb->coloron;
	colorvar = ppb->colorvar;

	QFont font = QFont(fontfamily,fontpointSize,fontweight,fontitalic);
	ui.biaoqian->setCurrentFont(font);
	ui.biaoqian->setText(ppb->text);

	QString style;
	style = "background-color: " + ppb->fontcolor;
	ui.pb_biaoqiancolor->setStyleSheet(style);

	if(ppb->operation == 1)
	{
		ui.rb_zhiweifuwei->setChecked(true);
	}
	else if(ppb->operation == 2)
	{
		ui.rb_weifanzhuan->setChecked(true);
	}
	else if(ppb->operation == 3)
	{
		ui.rb_yemiantiaozhuan->setChecked(true);
	}

	ui.le_targetvar->setText(ppb->targetvar);
	ui.le_targetpage->setText(QString::number(ppb->targetpage));

	if(ppb->colortype == 1)
	{
		ui.rb_kaiguan->setChecked(true);
	}
	else if(ppb->colortype == 2)
	{
		ui.rb_zhishidenkaiguan->setChecked(true);
	}
	else if(ppb->colortype == 3)
	{
		ui.rb_yemiantiaozhuan->setChecked(true);
	}

	ui.le_zhishivar->setText(ppb->colorvar);

	style = "background-color: " + ppb->coloron;
	ui.pb_oncolor->setStyleSheet(style);

	style = "background-color: " + ppb->coloroff;
	ui.pb_offcolor->setStyleSheet(style);
	//connect(&mytimer, SIGNAL(timeout()), this, SLOT(mytimeupdate()));
	//mytimer.start(200); //100ms定时


	//ui.vartable->setRowCount(2);
}

buttonedit::~buttonedit()
{
}

void buttonedit::on_backpb_clicked()
{
	//mytimer.stop();
	//mytimer.disconnect(this);
	hmipb * ppb = (hmipb *)hmiproject.hmipagelist[currenthmipageindex][currenthmiwidgetindex].pdata;

	QTextDocument* doc = ui.biaoqian->document();
	if(ppb->text != doc->toPlainText())
	{
		peconwin->projectneedsave = true;
		ppb->text = doc->toPlainText();
	}
	if(ppb->fontcolor != fontcolor)
	{
		peconwin->projectneedsave = true;
		ppb->fontcolor = fontcolor;
	}
	if(ppb->fontfamily != fontfamily)
	{
		peconwin->projectneedsave = true;
		ppb->fontfamily = fontfamily;
	}
	if(ppb->fontpointSize != fontpointSize)
	{
		peconwin->projectneedsave = true;
		ppb->fontpointSize = fontpointSize;
	}
	if(ppb->fontweight != fontweight)
	{
		peconwin->projectneedsave = true;
		ppb->fontweight = fontweight;
	}
	if(ppb->fontitalic != fontitalic)
	{
		peconwin->projectneedsave = true;
		ppb->fontitalic = fontitalic;
	}
	if(ppb->targetpage != targetpage)
	{
		peconwin->projectneedsave = true;
		ppb->targetpage = targetpage;
	}

	if(ui.rb_zhiweifuwei->isChecked())
	{
		if(ppb->operation != 1)
		{
			peconwin->projectneedsave = true;
			ppb->operation = 1;
		}
	}
	else if(ui.rb_weifanzhuan->isChecked())
	{
		if(ppb->operation != 2)
		{
			peconwin->projectneedsave = true;
			ppb->operation = 2;
		}
	}
	else if(ui.rb_yemiantiaozhuan->isChecked())
	{
		if(ppb->operation != 3)
		{
			peconwin->projectneedsave = true;
			ppb->operation = 3;
		}
	}

	if(ui.rb_kaiguan->isChecked())
	{
		if(ppb->colortype != 1)
		{
			peconwin->projectneedsave = true;
			ppb->colortype = 1;
		}
	}
	else if(ui.rb_zhishidenkaiguan->isChecked())
	{
		if(ppb->colortype != 2)
		{
			peconwin->projectneedsave = true;
			ppb->colortype = 2;
		}
	}

	if(ppb->targetvar != targetvar)
	{
		peconwin->projectneedsave = true;
		ppb->targetvar = targetvar;
	}
	if(ppb->coloroff != coloroff)
	{
		peconwin->projectneedsave = true;
		ppb->coloroff = coloroff;
	}
	if(ppb->coloron != coloron)
	{
		peconwin->projectneedsave = true;
		ppb->coloron = coloron;
	}
	if(ppb->colorvar != colorvar)
	{
		peconwin->projectneedsave = true;

		ppb->colorvar = colorvar;
	}

	if(peconwin->projectneedsave)
		peconwin->setWindowTitle(tr("ecomwin：") + projecthmifilename + "*");
	else
		peconwin->setWindowTitle(tr("ecomwin：") + projecthmifilename);

	close();
}
void buttonedit::closeEvent(QCloseEvent *e)
{
	//mytimer.disconnect(this);
	close();
}

void buttonedit::on_pb_targetvar_clicked()
{
	QStringList items;
	QList<struct varUInt>::iterator iUI;
	for(iUI = varUIntlist.begin();iUI != varUIntlist.end();++ iUI)
	{
		items << (*iUI).id;
	}

	QList<struct varInt>::iterator iI;
	for(iI = varIntlist.begin();iI != varIntlist.end();++ iI)
	{
		items << (*iI).id;
	}

	QList<struct varUShort>::iterator iUS;
	for(iUS = varUShortlist.begin();iUS != varUShortlist.end();++ iUS)
	{
		items << (*iUS).id;
	}

	QList<struct varShort>::iterator iS;
	for(iS = varShortlist.begin();iS != varShortlist.end();++ iS)
	{
		items << (*iS).id;
	}
	QList<struct varULongLong>::iterator iULL;
	for(iULL = varULongLonglist.begin();iULL != varULongLonglist.end();++ iULL)
	{
		items << (*iULL).id;
	}

	QList<struct varLongLong>::iterator iLL;
	for(iLL = varLongLonglist.begin();iLL != varLongLonglist.end();++ iLL)
	{
		items << (*iLL).id;
	}
	QList<struct varULong>::iterator iUL;
	for(iUL = varULonglist.begin();iUL != varULonglist.end();++ iUL)
	{
		items << (*iUL).id;
	}

	QList<struct varLong>::iterator iL;
	for(iL = varLonglist.begin();iL != varLonglist.end();++ iL)
	{
		items << (*iL).id;
	}
	QList<struct varFloat>::iterator iF;
	for(iF = varFloatlist.begin();iF != varFloatlist.end();++ iF)
	{
		items << (*iF).id;
	}

	QList<struct varDouble>::iterator iD;
	for(iD = varDoublelist.begin();iD != varDoublelist.end();++ iD)
	{
		items << (*iD).id;
	}
	for(iD = varLuavarlist.begin();iD != varLuavarlist.end();++ iD)
	{
		items << (*iD).id;
	}
	bool ok;
	QString item = QInputDialog::getItem(this, tr("选择开关目标变量"),
		tr("开关目标变量："), items, items.indexOf(targetvar), false, &ok);
	if (ok && !item.isEmpty())
	{
		targetvar = item;
		ui.le_targetvar->setText(item);
	}
}

void buttonedit::on_pb_zhishivar_clicked()
{
	QStringList items;
	QList<struct varUInt>::iterator iUI;
	for(iUI = varUIntlist.begin();iUI != varUIntlist.end();++ iUI)
	{
		items << (*iUI).id;
	}

	QList<struct varInt>::iterator iI;
	for(iI = varIntlist.begin();iI != varIntlist.end();++ iI)
	{
		items << (*iI).id;
	}

	QList<struct varUShort>::iterator iUS;
	for(iUS = varUShortlist.begin();iUS != varUShortlist.end();++ iUS)
	{
		items << (*iUS).id;
	}

	QList<struct varShort>::iterator iS;
	for(iS = varShortlist.begin();iS != varShortlist.end();++ iS)
	{
		items << (*iS).id;
	}
	QList<struct varULongLong>::iterator iULL;
	for(iULL = varULongLonglist.begin();iULL != varULongLonglist.end();++ iULL)
	{
		items << (*iULL).id;
	}

	QList<struct varLongLong>::iterator iLL;
	for(iLL = varLongLonglist.begin();iLL != varLongLonglist.end();++ iLL)
	{
		items << (*iLL).id;
	}
	QList<struct varULong>::iterator iUL;
	for(iUL = varULonglist.begin();iUL != varULonglist.end();++ iUL)
	{
		items << (*iUL).id;
	}

	QList<struct varLong>::iterator iL;
	for(iL = varLonglist.begin();iL != varLonglist.end();++ iL)
	{
		items << (*iL).id;
	}
	QList<struct varFloat>::iterator iF;
	for(iF = varFloatlist.begin();iF != varFloatlist.end();++ iF)
	{
		items << (*iF).id;
	}

	QList<struct varDouble>::iterator iD;
	for(iD = varDoublelist.begin();iD != varDoublelist.end();++ iD)
	{
		items << (*iD).id;
	}
	for(iD = varLuavarlist.begin();iD != varLuavarlist.end();++ iD)
	{
		items << (*iD).id;
	}
	bool ok;
	QString item = QInputDialog::getItem(this, tr("选择指示灯变量"),
		tr("指示灯变量："), items, items.indexOf(colorvar), false, &ok);
	if (ok && !item.isEmpty())
	{
		colorvar = item;
		ui.le_zhishivar->setText(item);
	}
}

void buttonedit::on_pb_oncolor_clicked()
{
	QColor choosecolor = QColorDialog::getColor(QColor(coloron));
	if(choosecolor.isValid())
	{
		coloron = choosecolor.name();
		QString style;
		style = "background-color: " + coloron;
		ui.pb_oncolor->setStyleSheet(style);
	}

}
void buttonedit::on_pb_offcolor_clicked()
{
	QColor choosecolor = QColorDialog::getColor(QColor(coloroff));
	if(choosecolor.isValid())
	{
		coloroff = choosecolor.name();
		QString style;
		style = "background-color: " + coloroff;
		ui.pb_offcolor->setStyleSheet(style);
	}
}

void buttonedit::on_pb_ziti_clicked()
{
	bool ok;
	QFont font = QFontDialog::getFont(
		&ok, QFont(fontfamily,fontpointSize,fontweight,fontitalic), this);
	if (ok) {
		// the user clicked OK and font is set to the font the user selected

		fontfamily = font.family();
		fontpointSize = font.pointSize();
		fontweight = font.weight();
		fontitalic = font.italic();

		QTextDocument* doc = ui.biaoqian->document();
		text1 = doc->toPlainText();

		ui.biaoqian->setCurrentFont(font);
		ui.biaoqian->setText(text1);

	} else {
		// the user canceled the dialog; font is set to the initial
		// value, in this case Helvetica [Cronyx], 10
	} 
}

void buttonedit::on_pb_biaoqiancolor_clicked()
{
	QColor choosecolor = QColorDialog::getColor(QColor(fontcolor));
	if(choosecolor.isValid())
	{
		fontcolor = choosecolor.name();
		QString style;
		style = "background-color: " + fontcolor;
		ui.pb_biaoqiancolor->setStyleSheet(style);
	}
}

void buttonedit::on_pb_targetpage_clicked()
{
	QStringList items;
	for(int i = 0;i < hmiproject.idlist.count();i++)
	{
		items << QString::number(hmiproject.idlist[i]);
	}
	bool ok;
	QString item = QInputDialog::getItem(this, tr("选择转跳页面"),
		tr("转跳页面："), items, items.indexOf(QString::number(targetpage)), false, &ok);
	if (ok && !item.isEmpty())
	{
		targetpage = item.toInt();
		ui.le_targetpage->setText(item);
	}
}

