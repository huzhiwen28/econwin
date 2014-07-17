econwin
=======

ECONWIN 不是组态王，是和PLC 类似的控制器，和以往的工控机控制系统相比较，它强调通过以太网
来扩展外部模块，实现一个易扩展、较易使用、实时的控制器系统。

ECONWIN开发工具，采用VC2003+Qt+lua脚本，其开发理念是尽可能的使用开源环境搭建一个稳定易用的PC控制器，ECONWIN的外围模块则采用
廉价的stm32 107以太网板来制作，一个PC控制器通过以太网交换机可以任意扩展外部模块。这个是KISS理念在PC工控领域的尝试。

特点：
用户任务可以采用C++编写，也可以采用lua脚本编写，econwin提供变量观察和编辑、任务启停、模块观察、lua脚本任务的监控、简易HMI
界面等功能，可以快速的给学生和爱好者展示控制器的设计和应用理念。

快速体验
1）取得econwin所有的文件，解压到一个文件夹中，进入econwinpackage文件夹。

2）安装“网口驱动程序”文件夹中的可执行程序，这个是网卡驱动。

3）退回到“econwinpackage”文件夹，进入“econwin”文件夹，双击“econwin.exe”可执行程序，系统即可运行。


基于lua脚本的开发
对于大部分的用户来说，采用lua脚本即可快速开发系统

1）fileregister.lua文件是注册PLC任务用，fileregister("usertask1.lua");注册了一个文件名为usertask1.lua的任务，可以采用
fileregister("usertask1.lua"，2);的方式来设定任务执行周期为2ms，否者则任务是尽可能的快跑。

2）globalvar.lua是定义全局变量的地方，a=var_register("a",0.2,1);表示定义个a变量，其初始值为0.2，要断电记忆
button4 = var_register("button4",0,0);则表示定义个button4变量，其初始值为0，不需要记忆

3）usertask1.lua是PLC控制程序真正的内容，它被周期性的执行。

lua开发环境采用lua for windows即可。
我网盘的链接

http://pan.baidu.com/s/1gd68X0J

使用C++开发

c++系统主要是针对需要保护的控制程序编写，另外系统的模块类型和功能的扩展，也是通过C++来编写，如果需要编写c++程序，建议下载
vs2003+Qt。
我网盘的链接

http://pan.baidu.com/s/1i3zEeKP
