#include "textedit.h"

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


textedit::textedit(QWidget *parent,Qt::WFlags flags)
: QDialog(parent, flags)
{
	ui.setupUi(this);
	hmitext * ptext = (hmitext *)hmiproject.hmipagelist[currenthmipageindex][currenthmiwidgetindex].pdata;

	text = ptext->text;//文本
	fontcolor= ptext->fontcolor;//文本颜色
	fontfamily= ptext->fontfamily;//文本字体
	fontpointSize =ptext->fontpointSize;//文本大小
	fontweight= ptext->fontweight;//笔划粗细
	fontitalic= ptext->fontitalic;//斜体

	touming = ptext->touming;//0 透明 1 不透明
	border= ptext->border;
	bordercolor = ptext->bordercolor;
	intercolor = ptext->intercolor;

	QFont font = QFont(fontfamily,fontpointSize,fontweight,fontitalic);
	ui.wenzi->setCurrentFont(font);
	ui.wenzi->setText(text);

	QString style;
	style = "background-color: " + fontcolor;
	ui.pb_wenzicolor->setStyleSheet(style);

	if(touming == 0)
	{
		ui.rb_touming->setChecked(true);
	}
	else if(touming == 1)
	{
		ui.rb_butouming->setChecked(true);
	}

	ui.le_biankuanghoudu->setText(QString::number(border));

	style = "background-color: " + bordercolor;
	ui.pb_biankuangyanse->setStyleSheet(style);

	style = "background-color: " + intercolor;
	ui.pb_juxingyanse->setStyleSheet(style);
}

textedit::~textedit()
{
}

void textedit::on_backpb_clicked()
{
	hmitext * ptext = (hmitext *)hmiproject.hmipagelist[currenthmipageindex][currenthmiwidgetindex].pdata;

	QTextDocument* doc = ui.wenzi->document();
	if(ptext->text != doc->toPlainText())
	{
		peconwin->projectneedsave = true;
		ptext->text = doc->toPlainText();
	}
	if(ptext->fontcolor != fontcolor)
	{
		peconwin->projectneedsave = true;
		ptext->fontcolor = fontcolor;
	}
	if(ptext->fontfamily != fontfamily)
	{
		peconwin->projectneedsave = true;
		ptext->fontfamily = fontfamily;
	}
	if(ptext->fontpointSize != fontpointSize)
	{
		peconwin->projectneedsave = true;
		ptext->fontpointSize = fontpointSize;
	}
	if(ptext->fontweight != fontweight)
	{
		peconwin->projectneedsave = true;
		ptext->fontweight = fontweight;
	}
	if(ptext->fontitalic != fontitalic)
	{
		peconwin->projectneedsave = true;
		ptext->fontitalic = fontitalic;
	}

	if(ui.rb_touming->isChecked())
	{
		if(ptext->touming != 0)
		{
			peconwin->projectneedsave = true;
			ptext->touming = 0;
		}
	}
	else if(ui.rb_butouming->isChecked())
	{
		if(ptext->touming != 1)
		{
			peconwin->projectneedsave = true;
			ptext->touming = 1;
		}
	}

	border = ui.le_biankuanghoudu->text().toInt();
	if(ptext->border != border)
	{
		peconwin->projectneedsave = true;
		ptext->border = border;
	}
	if(ptext->bordercolor != bordercolor)
	{
		peconwin->projectneedsave = true;
		ptext->bordercolor = bordercolor;
	}
	if(ptext->intercolor != intercolor)
	{
		peconwin->projectneedsave = true;
		ptext->intercolor = intercolor;
	}
	if(peconwin->projectneedsave)
		peconwin->setWindowTitle(tr("ecomwin：") + projecthmifilename + "*");
	else
		peconwin->setWindowTitle(tr("ecomwin：") + projecthmifilename);

	close();
}
void textedit::closeEvent(QCloseEvent *e)
{
	close();
}

void textedit::on_pb_biankuangyanse_clicked()
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
void textedit::on_pb_juxingyanse_clicked()
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

void textedit::on_pb_ziti_clicked()
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

		QTextDocument* doc = ui.wenzi->document();
		text = doc->toPlainText();

		ui.wenzi->setCurrentFont(font);
		ui.wenzi->setText(text);

	} else {
		// the user canceled the dialog; font is set to the initial
		// value, in this case Helvetica [Cronyx], 10
	} 
}

void textedit::on_pb_wenzicolor_clicked()
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

