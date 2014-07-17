/*
本文件提供修改模块端口值（类型为2）的功能

*/
#include "chgtype2.h"
#include <QTableWidgetItem>
#include "basicservice.h"
#include "controltask.h"



chgtype2::chgtype2(QWidget *parent,Qt::WFlags flags)
: QDialog(parent, flags)
{
	ui.setupUi(this);
}

chgtype2::~chgtype2()
{
}

void chgtype2::on_backpb_clicked()
{
	//mytimer.stop();
	close();
}
void chgtype2::closeEvent(QCloseEvent *e)
{
	close();
}

void chgtype2::setport(port* pp)
{
	pport = pp;
	union outport *pval =  (union outport*)pport->pv;
	if(pval->outportbit.out0 == 1)
	{
		ui.cb0->setChecked(true);
	}
	if(pval->outportbit.out1 == 1)
	{
		ui.cb1->setChecked(true);
	}
	if(pval->outportbit.out2 == 1)
	{
		ui.cb2->setChecked(true);
	}
	if(pval->outportbit.out3 == 1)
	{
		ui.cb3->setChecked(true);
	}
	if(pval->outportbit.out4 == 1)
	{
		ui.cb4->setChecked(true);
	}
	if(pval->outportbit.out5 == 1)
	{
		ui.cb5->setChecked(true);
	}
	if(pval->outportbit.out6 == 1)
	{
		ui.cb6->setChecked(true);
	}
	if(pval->outportbit.out7 == 1)
	{
		ui.cb7->setChecked(true);
	}

}


void chgtype2::on_cb7_stateChanged(int state)
{
	union outport *pval =  (union outport*)pport->pv;

	if(state == Qt::Unchecked)
	{
		pval->outportbit.out7 = 0;
	}
	else
	{
		pval->outportbit.out7 = 1;
	}
	pport->change = true;
}

void chgtype2::on_cb6_stateChanged(int state)
{
	union outport *pval =  (union outport*)pport->pv;

	if(state == Qt::Unchecked)
	{
		pval->outportbit.out6 = 0;
	}
	else
	{
		pval->outportbit.out6 = 1;
	}
	pport->change = true;

}

void chgtype2::on_cb5_stateChanged(int state)
{
	union outport *pval =  (union outport*)pport->pv;

	if(state == Qt::Unchecked)
	{
		pval->outportbit.out5 = 0;
	}
	else
	{
		pval->outportbit.out5 = 1;
	}
	pport->change = true;

}

void chgtype2::on_cb4_stateChanged(int state)
{
	union outport *pval =  (union outport*)pport->pv;

	if(state == Qt::Unchecked)
	{
		pval->outportbit.out4 = 0;
	}
	else
	{
		pval->outportbit.out4 = 1;
	}
	pport->change = true;

}

void chgtype2::on_cb3_stateChanged(int state)
{
	union outport *pval =  (union outport*)pport->pv;

	if(state == Qt::Unchecked)
	{
		pval->outportbit.out3 = 0;
	}
	else
	{
		pval->outportbit.out3 = 1;
	}
	pport->change = true;

}

void chgtype2::on_cb2_stateChanged(int state)
{
	union outport *pval =  (union outport*)pport->pv;

	if(state == Qt::Unchecked)
	{
		pval->outportbit.out2 = 0;
	}
	else
	{
		pval->outportbit.out2 = 1;
	}
	pport->change = true;

}

void chgtype2::on_cb1_stateChanged(int state)
{
	union outport *pval =  (union outport*)pport->pv;

	if(state == Qt::Unchecked)
	{
		pval->outportbit.out1 = 0;
	}
	else
	{
		pval->outportbit.out1 = 1;
	}
	pport->change = true;

}

void chgtype2::on_cb0_stateChanged(int state)
{
	union outport *pval =  (union outport*)pport->pv;

	if(state == Qt::Unchecked)
	{
		pval->outportbit.out0 = 0;
	}
	else
	{
		pval->outportbit.out0 = 1;
	}
	pport->change = true;

}