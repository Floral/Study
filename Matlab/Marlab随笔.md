# Matlab

## 常用命令

### 求多项式的根

### roots命令

作用：求多项式的根

格式：`r=roots(A)`

其中A是多项式的系数向量，从最高次项到零次项，中间没有的项系数写为0。

### format命令

格式：`format (格式名)`

一般有以下几种格式：

- short——5位近似定点数
- long——15位近似定点数
- hex——16进制数
- bank——银行格式，固定元和分
- rat——最小整数比例（分数）表示

格式名也可缺省不写，等同于short



### nargin与nargout

在调用函数时，MATLAB用两个永久变量nargin和nargout分别记录调用该函数时的输入实参和输出实参的个数。只要在函数文件中包含这两个变量，就可以准确地知道该函数文件被调用时的输入输出参数个数，从而决定函数如何进行处理。

例如：

```matlab
function fout=charray(a,b,c)
    if nargin==1
       fout=a;
    elseif nargin==2
       fout=(a+b)/2;
    elseif nargin==3
       fout=(a+b+c)/3;
    end
```

### global定义全局变量

一般来说matlab是不用定义变量的，类似python。

但是函数文件内部的变量是局部的，要想与其他函数文件共享，那么就需要用global关键字来定义全局变量了。

我们在命令行调用函数前要用global定义函数中使用的全局变量：

```matlab
global ALPHA BETA
x1=1;
x2=2;
y=f(x1,x2)
```

函数中也要声明全局变量：

```matlab
function y=f(a,b)
	global ALPHA BETA;	%使用全局变量的时候也要加global
	f=ALPHA*x1+BETA*y2;
end
```

我们在命令行调用函数前要用global定义函数中使用的

全局变量。

### inv()命令

格式：`inv(A)`

#### normplot()用来验证是否符合正态分布

绘制出来的是正态分位数图求矩阵A的逆矩阵

### impulse()函数

格式：`impulse()`



### normrnd()函数

有两种格式：

`normrnd(mu,sigma)`和`normrnd(mu,sigma，[size1,size2...,sizeN])`

功能：产生服从mu和sigma参数的正态分布的一个数或者是一组数。

#### normplot()用来验证是否符合正态分布

绘制出来的是正态分位数图

### dsolve命令

求微分方程的解析解



### cumsum()函数

用于返回一列或一行的积累量，具体请看文档



### repmat()函数

repeat matrix的简写，顾名思义就是生成重复的矩阵，具体请doc一下。

### all()函数

相当于与（&）函数，如果all(A)中的参数A的某一列的数值都是非零的，那么那一列的结果就是1，反之则为0。



### rng

用来指定随机数生成器，会影响rand，randi等随机数生成函数的结果。

## 第二章 整数规划

### intlinprog()函数

用于求解整数线性规划问题，其中有一个参数intcon是用来规定哪些下标的变量只能是整数的。

例如：X=[x1,x2,x3,x4,x5,x6]，其中x2, x3, x6只能取整数
intcon = [2,3,6]
如果所有变量都只能取整数，则：intcon = [1,2,3,4,5,6]; 比较方便的写法是:intcon = 1:6
如果只有x4取整数，则：intcon = 4;就是约束整形变量



## 第三章 非线性规划

> 匿名函数的用法，具体百度

### 非线性规划的Matlab解法

#### fmincon()函数



### 无约束问题的Matlab解法

#### jacobian()函数

求某个表达式的偏导数。

#### subs()函数

subs(s,old,new)，用新的值来替换s中老的值并计算。常用来带入表达式的某个点。

#### eig()函数

eig()函数用于求某个矩阵的特征值。

#### fminunc()函数和fminsearch()函数

都是求解无约束极小值的问题。

#### solve()函数

用于求解方程（组）的根。



### 约束极值问题

#### 二次规划

目标函数最高次数为2次，约束条件全为线性。

##### quadprog()函数



#### 构造惩罚函数



#### fminbnd函数



#### fseminf函数

#### fminmax函数



## 第四章 图与网络模型

求解最短路径的两个算法：

1. Dijkstra算法
2. Floyd算法



构造最小生成树的两个算法：

1. prim算法——选点
2. Kruskal算法——选边

## 小技巧

- 一行公式太长了写不下可以在某个附后后面加上三个小数点，然后回车在下一行接着写，例如：

```matlab
    f=x(1)^2+x(2)^2+3*x(3)^2+4*x(4)^2+2*x(5)^2-8*x(1)-...
    2*x(2)-3*x(3)-x(4)-2*x(5);
```



- 直接对某个向量或者矩阵使用不等号比较就可以得到每个元素与不等号比较之后的逻辑结果。

- 对矩阵使用相等运算符==可以得到与原矩阵中每一个元素与等号右边的值是否相同的逻辑结果矩阵，大小与原矩阵相同。

## Matlab编程遇到的一些坑

### Octave和Matlab的数据互通问题

Octave的save命令保存的默认文件格式不能用Matlab打开，会报错。所以在Octave保存变量的时候要加一个参数'-mat7-binary'。实例：

```matlab
save('-mat7-binary','parameter_name');
```

