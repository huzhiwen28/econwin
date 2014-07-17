/*
用户配置外部模块的地方
确定系统中有多少模块，其ID为多少
*/
#include "device.h"
struct tdevice207* id1;
struct tdevice107* id2;

//初始化设备节点，所有的外部设备要在此函数中初始化
void devicenodes_init(void)
{
	//初始化外部模块
	//id1 = tdevice207_init(1);
	//id2 = tdevice107_init(2);
}
