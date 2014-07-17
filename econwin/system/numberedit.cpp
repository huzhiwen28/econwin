#include "numberedit.h"

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

numberedit::numberedit(QWidget *parent,Qt::WFlags flags)
: QDialog(parent, flags)
{
	ui.setupUi(this);
	hminumber * pnumber = (hminumber *)hmiproject.hmipagelist[currenthmipageindex][currenthmiwidgetindex].pdata;

	vartype = pnumber->vartype;//变量类型 0整型 1浮点型
	targetvar = pnumber->targetvar;//绑定变量

	zhengshuwei = pnumber->zhengshuwei;//整数部分位数
	xiaoshuwei = pnumber->xiaoshuwei;//小数部分位数
	shuru = pnumber->shuru;//是否支持输入

	fanweijiancha = pnumber->fanweijiancha;//范围检查 0不检查 1检查
	zuixiaozhi = pnumber->zuixiaozhi;//最小值
	zuidazhi = pnumber->zuidazhi;//最小值

	fontcolor = pnumber->fontcolor;//文本颜色
	fontfamily = pnumber->fontfamily;//文本字体
	fontpointSize =pnumber->fontpointSize;//文本大小
	fontweight = pnumber->fontweight;//笔划粗细
	fontitalic = pnumber->fontitalic;//斜体

	border= pnumber->border;
	bordercolor = pnumber->bordercolor;
	intercolor = pnumber->intercolor;

	QString style;
	style = "background-color: " + fontcolor;
	ui.pb_wenzicolor->setStyleSheet(style);

	if(vartype == 0)
	{
		ui.rb_zhengshu->setChecked(true);
	}
	else if(vartype == 1)
	{
		ui.rb_fudianshu->setChecked(true);
	}

	ui.le_zhengshuwei->setText(QString::number(zhengshuwei));
	ui.le_xiaoshuwei->setText(QString::number(xiaoshuwei));

	ui.le_targetvar->setText(targetvar);

	if(shuru == 0)
	{
		ui.cb_shuru->setChecked(false);
	}
	else if(shuru == 1)
	{
		ui.cb_shuru->setChecked(true);
	}

	if(fanweijiancha == 0)
	{
		ui.cb_fanweijiancha->setChecked(false);
	}
	else if(fanweijiancha == 1)
	{
		ui.cb_fanweijiancha->setChecked(true);
	}

	ui.le_zuixiaozhi->setText(QString::number(zuixiaozhi));
	ui.le_zuidazhi->setText(QString::number(zuidazhi));

	ui.le_biankuanghoudu->setText(QString::number(border));

	style = "background-color: " + bordercolor;
	ui.pb_biankuangyanse->setStyleSheet(style);

	style = "background-color: " + intercolor;
	ui.pb_juxingyanse->setStyleSheet(style);
}

numberedit::~numberedit()
{
}

void numberedit::on_backpb_clicked()
{
	hminumber * pnumber = (hminumber *)hmiproject.hmipagelist[currenthmipageindex][currenthmiwidgetindex].pdata;

	if(ui.rb_zhengshu->isChecked())
	{
		if(pnumber->vartype != 0)
		{
			peconwin->projectneedsave = true;
			pnumber->vartype = 0;
		}
	}
	else if(ui.rb_fudianshu->isChecked())
	{
		if(pnumber->vartype != 1)
		{
			peconwin->projectneedsave = true;
			pnumber->vartype = 1;
		}
	}

	if(pnumber->targetvar != targetvar)
	{
		peconwin->projectneedsave = true;
		pnumber->targetvar = targetvar;
	}
	if(pnumber->zhengshuwei != ui.le_zhengshuwei->text().toInt())
	{
		peconwin->projectneedsave = true;
		pnumber->zhengshuwei = ui.le_zhengshuwei->text().toInt();
	}
	if(pnumber->xiaoshuwei != ui.le_xiaoshuwei->text().toInt())
	{
		peconwin->projectneedsave = true;
		pnumber->xiaoshuwei = ui.le_xiaoshuwei->text().toInt();
	}

	if(ui.cb_shuru->isChecked())
	{
		if(pnumber->shuru != 1)
		{
			peconwin->projectneedsave = true;
			pnumber->shuru = 1;
		}
	}
	else if(ui.rb_fudianshu->isChecked())
	{
		if(pnumber->shuru != 0)
		{
			peconwin->projectneedsave = true;
			pnumber->shuru = 0;
		}
	}

	if(ui.cb_fanweijiancha->isChecked())
	{
		if(pnumber->fanweijiancha != 1)
		{
			peconwin->projectneedsave = true;
			pnumber->fanweijiancha = 1;
		}
	}
	else
	{
		if(pnumber->fanweijiancha != 0)
		{
			peconwin->projectneedsave = true;
			pnumber->fanweijiancha = 0;
		}
	}
	if(pnumber->zuixiaozhi != ui.le_zuixiaozhi->text().toInt())
	{
		peconwin->projectneedsave = true;
		pnumber->zuixiaozhi = ui.le_zuixiaozhi->text().toInt();
	}
	if(pnumber->zuidazhi != ui.le_zuidazhi->text().toInt())
	{
		peconwin->projectneedsave = true;
		pnumber->zuidazhi = ui.le_zuidazhi->text().toInt();
	}

	if(pnumber->fontcolor != fontcolor)
	{
		peconwin->projectneedsave = true;
		pnumber->fontcolor = fontcolor;
	}
	if(pnumber->fontfamily != fontfamily)
	{
		peconwin->projectneedsave = true;
		pnumber->fontfamily = fontfamily;
	}
	if(pnumber->fontpointSize != fontpointSize)
	{
		peconwin->projectneedsave = true;
		pnumber->fontpointSize = fontpointSize;
	}

	if(pnumber->fontweight != fontweight)
	{
		peconwin->projectneedsave = true;
		pnumber->fontweight = fontweight;
	}
	if(pnumber->fontitalic != fontitalic)
	{
		peconwin->projectneedsave = true;
		pnumber->fontitalic = fontitalic;
	}

	if(pnumber->border != ui.le_biankuanghoudu->text().toInt())
	{
		peconwin->projectneedsave = true;
		pnumber->border = ui.le_biankuanghoudu->text().toInt();
	}
	if(pnumber->bordercolor != bordercolor)
	{
		peconwin->projectneedsave = true;
		pnumber->bordercolor = bordercolor;
	}
	if(pnumber->intercolor != intercolor)
	{
		peconwin->projectneedsave = true;
		pnumber->intercolor = intercolor;
	}
	if(peconwin->projectneedsave)
		peconwin->setWindowTitle(tr("ecomwin：") + projecthmifilename + "*");
	else
		peconwin->setWindowTitle(tr("ecomwin：") + projecthmifilename);


	close();
}
void numberedit::closeEvent(QCloseEvent *e)
{
	close();
}

void numberedit::on_pb_biankuangyanse_clicked()
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
void numberedit::on_pb_juxingyanse_clicked()
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

void numberedit::on_pb_ziti_clicked()
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

	} else {
		// the user canceled the dialog; font is set to the initial
		// value, in this case Helvetica [Cronyx], 10
	} 
}

void numberedit::on_pb_wenzicolor_clicked()
{
	QColor choosecolor = QColorDialog::getColor(QColor(fontcolor));
	if(choosecolor.isValid())
	{
		fontcolor = choosecolor.name();
		QString style;
		style = "background-color: " + fontcolor;
		ui.pb_wenzicolor->setStyleSheet(style);
	}
}
void numberedit::on_pb_targetvar_clicked()
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
	QString item = QInputDialog::getItem(this, tr("设置目标变量"),
		tr("目标变量："), items, items.indexOf(targetvar), false, &ok);
	if (ok && !item.isEmpty())
	{
		targetvar = item;
		ui.le_targetvar->setText(item);
	}
}
