#include "lightedit.h"

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

extern QList<struct _hmiwidget> hmiwidgetlist;
extern struct _hmiproject hmiproject;

//当前选择的控件是哪个
extern int currenthmiwidgetindex;
extern int currenthmipageindex;



lightedit::lightedit(QWidget *parent,Qt::WFlags flags)
: QDialog(parent, flags)
{
	ui.setupUi(this);
	currentindex = 0;
	init = true;
	comboinit = false;
	hmilight * plight = (hmilight *)hmiproject.hmipagelist[currenthmipageindex][currenthmiwidgetindex].pdata;

	data = *plight;

	ui.le_targetvar->setText(data.targetvar);
	for(int i =1;i <= 32;i++)
	{
		ui.combo_zhuangtaishuliang->addItem(QString::number(i));
	}
	ui.combo_zhuangtaishuliang->setCurrentIndex(data.number-1);

	comboinit = true;
	for(int i =0;i < data.number;i++)
	{
		ui.combo_dangqianzhuangtai->addItem(QString::number(i));
	}
	ui.combo_dangqianzhuangtai->setCurrentIndex(0);
	comboinit = false;
	textinit = true;

	QFont font = QFont(data.lightdata[0].fontfamily,data.lightdata[0].fontpointSize,data.lightdata[0].fontweight,data.lightdata[0].fontitalic);
	ui.wenzi->setCurrentFont(font);
	ui.wenzi->setText(data.lightdata[0].text);

	QString style;
	style = "background-color: " + data.lightdata[0].fontcolor;
	ui.pb_wenzicolor->setStyleSheet(style);

	ui.le_biankuanghoudu->setText(QString::number(data.lightdata[0].border));

	style = "background-color: " + data.lightdata[0].bordercolor;
	ui.pb_biankuangyanse->setStyleSheet(style);

	style = "background-color: " + data.lightdata[0].intercolor;
	ui.pb_juxingyanse->setStyleSheet(style);
	textinit = false;


	init = false;

}

lightedit::~lightedit()
{
}

void lightedit::on_backpb_clicked()
{
	hmilight * plight = (hmilight *)hmiproject.hmipagelist[currenthmipageindex][currenthmiwidgetindex].pdata;


	if((plight->number != data.number)
		|| (plight->targetvar != data.targetvar)
		)
	{
		peconwin->projectneedsave = true;
	}

	for(int i = 0;i < data.number;i++)
	{
		if((plight->lightdata[i].border != data.lightdata[i].border)
			|| (plight->lightdata[i].bordercolor != data.lightdata[i].bordercolor)
			|| (plight->lightdata[i].fontcolor != data.lightdata[i].fontcolor)
			|| (plight->lightdata[i].fontfamily != data.lightdata[i].fontfamily)
			|| (plight->lightdata[i].fontitalic != data.lightdata[i].fontitalic)
			|| (plight->lightdata[i].fontpointSize != data.lightdata[i].fontpointSize)
			|| (plight->lightdata[i].fontweight != data.lightdata[i].fontweight)
			|| (plight->lightdata[i].intercolor != data.lightdata[i].intercolor)
			|| (plight->lightdata[i].text != data.lightdata[i].text)
			)
		{
			peconwin->projectneedsave = true;
			break;
		}

	}

	*plight = data;

	if(peconwin->projectneedsave)
		peconwin->setWindowTitle(tr("ecomwin：") + projecthmifilename + "*");
	else
		peconwin->setWindowTitle(tr("ecomwin：") + projecthmifilename);

	close();
}

void lightedit::closeEvent(QCloseEvent *e)
{
	//mytimer.disconnect(this);
	close();
}

void lightedit::on_combo_zhuangtaishuliang_currentIndexChanged(int index )
{
	if(init == false)
	{
		int newnumber = index + 1;
		if((newnumber >= 0) && (newnumber < 32) && (newnumber !=  data.number))
		{
			data.number = newnumber;
			comboinit = true;
			currentindex = ui.combo_dangqianzhuangtai->currentIndex();
			ui.combo_dangqianzhuangtai->clear();
			for(int i =0;i < data.number;i++)
			{
				ui.combo_dangqianzhuangtai->addItem(QString::number(i));
			}

			comboinit = false;
			if(currentindex >= data.number)
			{
				ui.combo_dangqianzhuangtai->setCurrentIndex(0);
			}
			else
			{
				ui.combo_dangqianzhuangtai->setCurrentIndex(currentindex);
			}
		}
	}
}


void lightedit::on_combo_dangqianzhuangtai_currentIndexChanged(int index)
{
	if(comboinit == false)
	{
		currentindex = index;

		textinit = true;
		QFont font = QFont(data.lightdata[currentindex].fontfamily,data.lightdata[currentindex].fontpointSize,data.lightdata[currentindex].fontweight,data.lightdata[currentindex].fontitalic);
		ui.wenzi->setCurrentFont(font);
		ui.wenzi->setText(data.lightdata[currentindex].text);

		QString style;
		style = "background-color: " + data.lightdata[currentindex].fontcolor;
		ui.pb_wenzicolor->setStyleSheet(style);

		ui.le_biankuanghoudu->setText(QString::number(data.lightdata[currentindex].border));

		style = "background-color: " + data.lightdata[currentindex].bordercolor;
		ui.pb_biankuangyanse->setStyleSheet(style);

		style = "background-color: " + data.lightdata[currentindex].intercolor;
		ui.pb_juxingyanse->setStyleSheet(style);
		textinit = false;
	}
}

void lightedit::on_pb_targetvar_clicked()
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
		tr("目标变量："), items, items.indexOf(data.targetvar), false, &ok);
	if (ok && !item.isEmpty())
	{
		data.targetvar = item;
		ui.le_targetvar->setText(item);
	}
}

void lightedit::on_pb_ziti_clicked()
{
	bool ok;
	QFont font = QFontDialog::getFont(
		&ok, QFont(data.lightdata[currentindex].fontfamily,data.lightdata[currentindex].fontpointSize,data.lightdata[currentindex].fontweight,data.lightdata[currentindex].fontitalic), this);
	if (ok) {
		// the user clicked OK and font is set to the font the user selected

		data.lightdata[currentindex].fontfamily = font.family();
		data.lightdata[currentindex].fontpointSize = font.pointSize();
		data.lightdata[currentindex].fontweight = font.weight();
		data.lightdata[currentindex].fontitalic = font.italic();		
		ui.wenzi->setCurrentFont(font);
		ui.wenzi->setText(data.lightdata[currentindex].text);

	} else {
		// the user canceled the dialog; font is set to the initial
		// value, in this case Helvetica [Cronyx], 10
	} 
}

void lightedit::on_pb_wenzicolor_clicked()
{
	QColor choosecolor = QColorDialog::getColor(QColor(data.lightdata[currentindex].fontcolor));
	if(choosecolor.isValid())
	{
		data.lightdata[currentindex].fontcolor = choosecolor.name();
		QString style;
		style = "background-color: " + data.lightdata[currentindex].fontcolor;
		ui.pb_wenzicolor->setStyleSheet(style);
	}
}

void lightedit::on_pb_biankuangyanse_clicked()
{
	QColor choosecolor = QColorDialog::getColor(QColor(data.lightdata[currentindex].bordercolor));
	if(choosecolor.isValid())
	{
		data.lightdata[currentindex].bordercolor = choosecolor.name();
		QString style;
		style = "background-color: " + data.lightdata[currentindex].bordercolor;
		ui.pb_biankuangyanse->setStyleSheet(style);
	}

}
void lightedit::on_pb_juxingyanse_clicked()
{
	QColor choosecolor = QColorDialog::getColor(QColor(data.lightdata[currentindex].intercolor));
	if(choosecolor.isValid())
	{
		data.lightdata[currentindex].intercolor = choosecolor.name();
		QString style;
		style = "background-color: " + data.lightdata[currentindex].intercolor;
		ui.pb_juxingyanse->setStyleSheet(style);
	}
}

void lightedit::on_le_biankuanghoudu_textChanged(const QString& text)
{
	if(textinit == false)
	{
		int num = text.toInt();
		if(num >0)
		{
			data.lightdata[currentindex].border = num;
		}
	}
}

void lightedit::on_wenzi_textChanged()
{
	if(textinit == false)
	{
		QTextDocument* doc = ui.wenzi->document();
		data.lightdata[currentindex].text = doc->toPlainText();
	}
}
