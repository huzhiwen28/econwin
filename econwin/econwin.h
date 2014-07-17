#ifndef ECONWIN_H
#define ECONWIN_H

#include <QtGui/QDialog>
#include "ui_econwin.h"
#include <QTimer>
#include <QMap>
#include <QString>
#include <QPainter>
#include <QPicture>
#include <QScrollArea>

struct hmipb{
	QString text;//按钮上的文本
	QString fontcolor;//文本颜色
	QString fontfamily;//文本字体
	int fontpointSize;//文本大小
	int fontweight;//笔划粗细
	bool fontitalic;//斜体

	int operation;//操作类型 1置位复位 2翻转 3页面跳转
	QString targetvar;//绑定变量
	int targetpage;//目标页面

	int colortype;//指示灯类型 1 无指示灯 2有指示灯
	QString coloroff;//指示灯变量off的颜色
	QString coloron;//指示灯变量on的颜色
	QString colorvar;//指示灯绑定的变量

	bool clicked;
};

struct hmirect{
	int border;//边框宽度
	QString bordercolor;//边框颜色
	QString intercolor;//内部颜色
};

struct hmitext{
	QString text;//按钮上的文本
	QString fontcolor;//文本颜色
	QString fontfamily;//文本字体
	int fontpointSize;//文本大小
	int fontweight;//笔划粗细
	bool fontitalic;//斜体

	int touming;//0 透明 1 不透明
	int border;//边框宽度
	QString bordercolor;//边框颜色
	QString intercolor;//内部颜色
};

struct hminumber{
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
};


struct _lightdata{
	QString text;//文本
	QString fontcolor;//文本颜色
	QString fontfamily;//文本字体
	int fontpointSize;//文本大小
	int fontweight;//笔划粗细
	bool fontitalic;//斜体

	int border;//边框宽度
	QString bordercolor;//边框颜色
	QString intercolor;//内部颜色

};

//指示灯
struct hmilight{
	QString targetvar;//绑定变量

	int number;//指示灯状态数量1-32

	//每种指示灯状态对应的数据
	struct _lightdata lightdata[32];
};

struct _hmiwidget{
	//控件位置
	int x;
	int y;
	int w;
	int h;

	int widgettype; // 0label 1button
	void * pdata; //各类控件的数据
};

struct _page{
	int	id;
	QString	name;
	QString	color;
	int	needpasswd;
	QString	passwd;
	int len;
};

struct _hmiproject{
	int len;
	int firstpageid;

	QList <int> idlist;
	QList < struct _page > pagelist; 
	QList < QList<struct _hmiwidget> > hmipagelist; 
};



class MyWidget : public QWidget
 {
     Q_OBJECT

 public:
     MyWidget(QWidget *parent);
	 char chgflag;
	QAction*    Act_movebehind;

 public slots:
     void animate();
	 void movebehind();

 protected:
     void paintEvent(QPaintEvent *event);
	 void mouseMoveEvent( QMouseEvent * event );
	 void mousePressEvent( QMouseEvent * event );
	 void keyPressEvent( QKeyEvent * event );
	 void mouseReleaseEvent( QMouseEvent * event );
 	 void contextMenuEvent(QContextMenuEvent *event);
	 void mouseDoubleClickEvent( QMouseEvent * event ); 
 };

class econwin : public QDialog
{
	Q_OBJECT

public:
	econwin(QWidget *parent = 0, Qt::WFlags flags = 0);
	~econwin();
	QTimer mytimer;
	MyWidget * basewidget;
	bool checkyemianchanshu;

	bool projectneedsave;
	bool intcall;

private:
	Ui::econwinClass ui;

private slots:
	void on_pb_new_clicked();
	void on_pb_shezhishouye_clicked();
	void on_pb_shanchuyemian_clicked();
	void on_pb_zhenjiayemian_clicked();
	void on_pb_zhishideng_clicked();
	void on_pb_shuzhi_clicked();
	void on_pb_wenzhi_clicked();
	void on_pb_juxing_clicked();
	void on_pushButton_read_clicked();
	void on_pushButton_save_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_clicked();
	void on_pb_yunxing_clicked();
	void mytimeupdate();
	void onTableClicked(int,int);

	void onShuxingTableChanged(int,int);
	void onShuxingTableClicked(int,int);

protected:
	void closeEvent(QCloseEvent *e);
	void keyPressEvent( QKeyEvent * event );

};

class KeyPressEater: public QObject
{
	Q_OBJECT

public:
	KeyPressEater(QObject *parent = 0);
	~	KeyPressEater();

protected:
	bool eventFilter(QObject *obj, QEvent *event);
};




#endif // ECONWIN_H

