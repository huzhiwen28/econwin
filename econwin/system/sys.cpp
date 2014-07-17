/*
本文件实现系统界面
*/
#include "sys.h"
#include <QTimer>
#include <QTime>
#include <iostream>
#include <stdlib.h>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "pcap.h"
#include <iphlpapi.h>
#include "econwin.h"

#include "varview.h"
#include "taskview.h"
#include "modview.h"
#include "luaview.h"

extern pcap_t *adhandle;
extern bool threadrun;
extern int netcardindex;
extern struct bpf_program fcode;
extern int cnt;
extern econwin * peconwin;

/* Callback function invoked by libpcap for every incoming packet */
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);

sys::sys(QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags)
{
	bool ok;
	ui.setupUi(this);
	succeedcnt = 0;

	pcap_if_t *alldevs;
	pcap_if_t *d;
	int inum;
	int i=0;
	char errbuf[PCAP_ERRBUF_SIZE];
	
	/* Retrieve the device list */
	if(pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
		//exit(1);
	}
	int  nCount  = 0;  	
	/* Print the list */
	for(d=alldevs; d; d=d->next)
	{
		//printf("%d. %s", ++i, d->name);
		if (d->description)
		{
			QString device;
			device.append(d->description);
			ui.comboBox->insertItem(nCount,device);
			nCount++;
		}

		else
			printf(" (No description available)\n");
	}

	pcap_freealldevs(alldevs);
	if(econwinrun)
	{
		if(ui.comboBox->count() > (netcardindex+1))
		{
			ui.comboBox->setCurrentIndex(netcardindex);
		}
		ui.comboBox->setDisabled(true);
		ui.pushButton_4->setDisabled(true);
		ui.label_4->setPixmap(QPixmap(":/econwin/system/io1.PNG"));
	}
	else
	{
		if(ui.comboBox->count() > (netcardindex+1))
		{
			ui.comboBox->setCurrentIndex(netcardindex);
		}
		ui.pushButton_3->setDisabled(true);
		ui.label_4->setPixmap(QPixmap(":/econwin/system/io0.PNG"));
	}
}

sys::~sys()
{
}
//启动
void sys::on_pushButton_4_clicked()
{

	pcap_if_t *alldevs;
	pcap_if_t *d;
	int inum;
	int i=0;
	char errbuf[PCAP_ERRBUF_SIZE];
	netcardindex = ui.comboBox->currentIndex();

	/* Retrieve the device list */
	if(pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
		//exit(1);
	}


	/* Jump to the selected adapter */
	for(d=alldevs, i=0; i<netcardindex ;d=d->next, i++);

	/* Open the device */
	/* Open the adapter */
	if ((adhandle= pcap_open_live(d->name,	// name of the device
		65536,			// portion of the packet to capture. 
		// 65536 grants that the whole packet will be captured on all the MACs.
		1,				// promiscuous mode (nonzero means promiscuous)
		1,			// read timeout
		errbuf			// error buffer
		)) == NULL)
	{
		fprintf(stderr,"\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return;
	}

    // configure pcap for maximum responsiveness
    if (pcap_setmintocopy(adhandle, 0) != 0)
    {
        printf("pcap_setmintocopy failed\n");
    }

	//compile the filter
	if(pcap_compile(adhandle, &fcode, "ether dst 0:0:0:0:0:f0", 1, 0) < 0)
	{
		fprintf(stderr,"\nError compiling filter: wrong syntax.\n");
		//return;
	}

	//set the filter
	if(pcap_setfilter(adhandle, &fcode)<0)
	{
		fprintf(stderr,"\nError setting the filter\n");
		//return;
	}	
	printf("\nlistening on %s...\n", d->description);

	/* At this point, we don't need any more the device list. Free it */
	pcap_freealldevs(alldevs);

	econwinrun = true;

	ui.label_4->setPixmap(QPixmap(":/econwin/system/io1.PNG"));
	ui.comboBox->setDisabled(true);
	ui.pushButton_4->setDisabled(true);
	ui.pushButton_3->setDisabled(false);
}
//停止
void sys::on_pushButton_3_clicked()
{
	if (econwinrun == true)
	{
		econwinrun = false;
		Sleep(100);

		pcap_close(adhandle);

		ui.label_4->setPixmap(QPixmap(":/econwin/system/io0.PNG"));
		ui.comboBox->setDisabled(false);
		ui.pushButton_4->setDisabled(false);
		ui.pushButton_3->setDisabled(true);
	}
}


void sys::on_pushButton_clicked()
{
	varview Dlg;
	Dlg.exec();
}

void sys::on_pushButton_2_clicked()
{
	taskview Dlg;
	Dlg.exec();
}


void sys::on_pushButton_5_clicked()
{
	modview Dlg;
	Dlg.exec();

}

void sys::on_pbluaview_clicked()
{
	luaview Dlg;
	Dlg.exec();
}