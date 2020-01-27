# 自己动手写CPU

## 第一章

### 指令集架构ISA（Instruction Set Architecture）

ISA将编程所需了解的硬件信息从硬件系统中抽象出来。从软件人员的角度看，ISA包括一套指令集和一些寄存器。
简单地说，ISA就是提供给汇编程序员的最底层硬件的接口。

### 微架构（Microarchitecture）

微架构是ISA的一个具体实现。ISA好比设计规范，微架构则是具体实现。用编程里的概念类比，ISA就是接口（所能实现的各种功能），微架构就是实现功能的具体方式（采用的不同的算法），因此，同样的ISA，不同的微架构，会带来不同的性能。

- ISA主要分为CISC和RISC。
- CISC目前主流只有x86
- RISC主流包括ARM、SPARC、POWER、MIPS



其他博主的blog：

https://blog.csdn.net/qq_42914528/article/details/81779727



## 第四章

首先要做的就是搭建一个流水线结构。所谓流水线，在电路上的结构就是组合逻辑和时序逻辑电路



## 第五章

本书OpenMIPS采用数据前推的方法解决RAW（Read After Write）的问题。

译码阶段输出的Aluop和Alusel是为了方便执行阶段执行操作的判断。

无论是寄存器位移版本（sllv、srav、srlv）还是立即数位移版本（sll、sra、srl），最终都是通过reg1_o和reg2_o输出两个操作数给id_ex.v至ex.v。

对任意一条而言，译码工作的主要内容是：确定要读取的寄存器的情况、要执行的运算和要写入的目的寄存器三方面的信息。