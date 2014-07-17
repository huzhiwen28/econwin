/*
用户全局变量定义的地方
*/
#include "basicservice.h"
#include <QString>

unsigned int aint = 0;
unsigned int bint = 200;
int cint = 0;
unsigned short dushort = 0;
short eshort = 0;
unsigned long long full = 0;
long long gll = 0;
unsigned long hul = 0;
long il = 0;
float jf = 0.0;
double kd = 0.0;

int iiii = 1;
int variii[1000];

//注册用户全局变量
void initGlobalvar(void)
{

	//普通全局变量
	var_register("错误通讯次数",&aint);
	var_register("bint",&bint);
	var_register("cint",&cint);
	var_register("dushort",&dushort);
	var_register("eshort",&eshort);
	var_register("full",&full);
	var_register("gll",&gll);
	var_register("hul",&hul);
	var_register("il",&il);


	//保持全局变量
	var_register("jf",&jf,true);
	var_register("kd",&kd,true);
}