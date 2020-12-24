# Altium Designer(AD)简易教程



由于本人记忆力较差，每次过了一段时间不用AD的话，就会忘了该怎么操作。特此写下本文简要记录一下AD软件的功能区域和从原理图到PCB打板的流程（不包括画图的细节操作），以供快速回忆。

> 本文的软件版本为18版



## 从原理图到PCB流程

主要分为两个步骤：

1. 原理图绘制
2. PCB绘制

这两步是有先后关系的。

说简单点画原理图的主要任务就是完成电路的“逻辑”连线，也就是哪个引脚接哪个引脚，不需要管线路的具体形状和位置，当线路比较多的时候一般都是用网络标号来完成逻辑连接的。

PCB绘制则是跟据原理图的逻辑连线，来布置元件的位置、线路的走法。AD软件会跟据你的原理图的逻辑连线给出连线的提示，所以不用担心不知道要怎么连线，你需要关心的是线的走法。





## 软件界面

进入软件后的界面如下（未打开任何项目）：

![image-20201214204708919](Altium%20Designer(AD)%E7%AE%80%E6%98%93%E6%95%99%E7%A8%8B/image-20201214204708919.png)

左上角主菜单栏的File可以打开或新建项目；View可以控制整体界面中panel和bar的显示与否（例如左侧的Projects栏和右侧的Libraries（未显示））以及后面PCB的视图选择等，与显示相关的东西应该都在这；Project栏目中可编译原理图（对，没错，原理图也是需要编译的......不过程序的编译不一样哈，这里的编译是用来检查原理图是否有错误以及得到网表给画PCB的时候用）；Windows里面可以分屏，以同时显示多个原理图/PCB。



新建一个完整的PCB工程（原理图和PCB）是如下的选项（而不是中间的二级目录的PCB）：

![image-20201214205942823](Altium%20Designer(AD)%E7%AE%80%E6%98%93%E6%95%99%E7%A8%8B/image-20201214205942823.png)



接着左侧Projects栏就会出现一个新的工程（如下图后缀为PrjPCB的项），此时仍然不能直接开始画原理图，需要向此工程添加原理图文件和PCB文件才能画，右键该项目，可以向该项目添加新的（Add New）原理图文件（Schematic）和PCB文件，也可以直接添加已经存在的Schematic和PCB。

![image-20201214210437795](Altium%20Designer(AD)%E7%AE%80%E6%98%93%E6%95%99%E7%A8%8B/image-20201214210437795.png)



下图是我创建完Schematic和PCB后的界面，当前显示的是原理图文件

![image-20201214210747658](Altium%20Designer(AD)%E7%AE%80%E6%98%93%E6%95%99%E7%A8%8B/image-20201214210747658.png)



以下是我个人对软件界面的分区（自己瞎起的名字）：

![Snipaste_2020-12-14_21-22-22](Altium%20Designer(AD)%E7%AE%80%E6%98%93%E6%95%99%E7%A8%8B/Snipaste_2020-12-14_21-22-22.png)

PS：右侧的Properties Panel是需要手动点击右上角的按钮打开的。

### 1. 菜单栏

菜单栏中比较常用的有：

1. Edit项中的对齐（Align）功能，在画PCB的时候对美观有强迫症的同学非常有用

2. Project项的编译（Compile）功能；

3. Design项的由原理图更新到PCB功能、Rules功能（线路的电气规则，这个对画PCB的影响很大）以及板子形状（Board Shape）；

4. Tool项里面的东西跟据你当前的界面是Schematic还是PCB有关；

   Schematic中常用的有封装管理器（Footprint Manager）和元器件标号（Annotation）。

<img src="Altium%20Designer(AD)%E7%AE%80%E6%98%93%E6%95%99%E7%A8%8B/image-20201214214448808.png" alt="image-20201214214448808" style="zoom:50%;" />

​				PCB中的Tools常用的有如下几个：

<img src="Altium%20Designer(AD)%E7%AE%80%E6%98%93%E6%95%99%E7%A8%8B/image-20201214214756416.png" alt="image-20201214214756416" style="zoom:50%;" />

5. Reports中的Measure Distance

<img src="Altium%20Designer(AD)%E7%AE%80%E6%98%93%E6%95%99%E7%A8%8B/image-20201214214921166.png" alt="image-20201214214921166" style="zoom:50%;" />

6. Window项里的分屏
7. 最后是PCB界面才会显示的Route项，即，跟布线相关的操作

<img src="Altium%20Designer(AD)%E7%AE%80%E6%98%93%E6%95%99%E7%A8%8B/image-20201214215020013.png" alt="image-20201214215020013" style="zoom:50%;" />