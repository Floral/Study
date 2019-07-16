# C++ Primer 5th

## Chapter 1.Getting Start

### Some command in Linux

- compile the source code

```bash
$ g++ (-Wall) -o <outname> <sourcefilename>
```

- get the return code of last executed program

```bash
$ echo $?
```





### iostream

iostream includes the istream and ostream.

### Standard Input and Output Objects

`cin` and `cout` are known as the standard input and output,respectively.

`cerr` is referred to as the standard error, and `clog` are for general information about the execution of the program.



### Output operator

The output operator is defined as `<<` in C++. It must have two operands, and the left-hand operand must be and ostream object. The result of output operator is its left-hand operand. That is, the result is the ostream on which we wrote the given value.



- endl

The `endl` is a special value called a manipulator. It has two function:

1. ending the current line;
2. **flushing the buffer.**

 Flushing the buffer ensures that all the output the program has generated so far is actually written to the output stream, rather than sitting in memory waiting to be written.

- scope operator

We use scope operator `::` to say that int which namespace that we want to call the function or manipulator. eg:

```c++
std::cin
std::endl
```



### Input operator

The input operator `>>` behaves analogously to the output operator. Also return its left-hand operand.





### 1.4.3. Reading an Unknown Number of Inputs

```c++
#include <iostream>
int main()
{
	int sum = 0, value = 0;
	// read until end-of-file, calculating a running total of all values read
	while (std::cin >> value)
	sum += value; // equivalent to sum = sum + value
	std::cout << "Sum is: " << sum << std::endl;
	return 0;
}
```

   The statement `std:cin>>value` returns the left operand of input operator `>>` , which in this case is *std::cin*. When tests the condition of *while*, it tests *std::cin*.

​    When *istream* is used as a condition, the test is **true** if the *istream* hasn't encounter an error, and **false** if it encounter the end-of-file or invalid input( such as reading a value that is not the variable type is declared ). 

> ​    When we enter input to a program from the keyboard, different operating systems use different conventions to allow us to indicates end-of-file.
>
> ​	In Windows: press `ctrl` and `z` simultaneously.
>
> ​	In Unix: press `ctrl` and `d` simultaneously.



### 1.5. Introducing classes

​	A class defines a type along with a collection of operations that are related to that type.

​	Conventionally, we define a new class in a header file that we write our own, and the name of header files are derived from the name of class. Header files that we write usually have a suffix of **.h**, but some programmers use .H, .hpp, or .hxx. The standard library headers typically have no suffix at all. Compilers usually don’t care about the form of header file names, but IDEs sometimes do.



> TIPS:
>
> It can be tedious to repeatedly type these transactions as input to the programs you are testing. Most operating systems support file redirection, which lets us associate a named file with the standard input and the standard output:
>
> $ addItems  <infile >outfile
>
> Assuming $ is the system prompt and our addition program has been compiled into an executable file named addItems.exe (or addItems on UNIX systems), this command will read transactions from a file named infile and write its output to a file named outfile in the current directory.



#### 1.5.2 A First Look at Member Functions

​	dot operator --" . ", call operator -- "()".



## Part I: The Basics

### Chapter 2 Variables and Basic Types



>  以下由于看英文版的速度太慢，而时间有限，故决定一刷先看中文版，二刷再看英文版，但在看中文版的时候以英文版作为辅助

- 算术类型（arithmetic type）
- 空类型（void）



#### 算术类型

​		C++标准规定了算术类型所占位数的**最小值**（浮点型有点特别，其规定的是有效数字的位数），同时允许编译器赋予这些类型更多的位数，这也就是说，在不同系统、不同编译器、不同机器下，同一种类型的位数可能不一样，这就导致了C++可移植性稍微差了点。

​		除了char这个基本字符型，C++还提供了一些支持国际化的字符型（扩展字符集）：wchar_t、char16_t、char32_t。他们的最小为数分别是16 、16 、32。后面两个是Unicode字符。

> 内置类型的机器实现
>
> ​		要赋予内存中某个地址明确的含义，必须首先知道存储在改地址的数据的类型，类型决定了数据所占的比特数以及该如何解释这些比特的内容。



##### 带符号类型和无符号类型

除了bool和扩展字符型之外，其他的整型可以分为有符号的和无符号的。

int、short、long和long long默认都是带符号的，要想得到无符号的，就要在这些声明前加上unsigned。

比较特别的是char类型，他有三种：char、signed char和unsigned char。虽然有三种，但只有两种表现形式：有符号的和无符号的。其中char并不就是signed char，它既可能是有符号的，也可能是无符号的，具体**由编译器决定**。

> 选择类型的一些准则：
>
> - 当数值肯定不为负数时，则选用无符号类型。
> - 一般选用int进行整数运算，而不用short，因为short的位数比较小。
> - 在算术表达式中不要用char或bool，因为char的有无符号不确定，如果确实需要用char来表示一个不大的整数，请指明signed和unsigned。而bool在算术表达式中只能取0或1两个值。
> - 执行浮点运算一般选用double。



##### 类型转换

​		对象的类型**定义了对象能包含的数据和能参与的运算**，其中一种运算被大多数类型支持，就是将对象从一种给定的类型**转换**为另一种相关类型。

​		常见的是把int型当做if或循环的判断条件，这里就会自动的转换为bool型。

###### 含有无符号类型的表达式

​		当一个算术表达式中既有无符号数又有int型是，那么int值就会转换成无符号数。

​		当从无符号数中减去一个值时，不管这个值是不是无符号数，我们都必须确保结果不是一个负值，这里有一个有趣的例子：

```c++
#include<iostream>

int main()
{
    unsigned u=42,i=10;
    std::cout<< i-u <<std::endl;
    std::cout<< (signed int)(i-u) <<std::endl;
    return 0;
}

//如果int是32位，其结果是：
//4294967264
//-32
```

​		这里涉及到数字在计算机中的表示方法——都是通过补码来完成存储和计算的，但是其**显示的结果取决于我们如果解释这个补码**，如果解释为无符号数（第一个输出语句），其结果就是一个正数，如果强制转换为有符号类型来解释，那么结果就是-32。

##### 2.1.3字面值常量

​		形如42的值被称作**字面值常量（literal）**，字面值常量的形式和值决定了它的数据类型。

**整形和浮点型字面值：**

​		八进制数以0开头，十六进制以0x开头。20的三种写法：20（十进制），024（八进制），0x14（十六进制）。

​		默认情况下，十进制的字面值是带符号数，八进制和十六进制既可能是有符号数也可能是无符号数。



**字符和字符串字面值** 	P36

​		单个字符用单引号括起来，字符串用双引号括起来，但是单个字符也能用双引号括起来。编译器会在每个字符串结尾添加一个空字符（'\0'），因此字符串常量的实际长度要比它的内容多1。



**转义序列	P36**

​		转义序列就是以反斜线开始的一些特殊字符。如：换行符，制表符等等。

​		还有一种比较特殊的被称作泛化的转义序列，用于表示字符，形式有：以\x后紧跟的1个或多个十六进制数字、以\后紧跟的1-3位八进制数字。数字部分表示的是字符对应的数值。



**指定字面值常量的类型	P37**

​		我们可以给字面值敞亮表达式通过添加前缀或后缀来改变他们的默认类型。具体见书P37。



**布尔和指针的字面值常量**

​		true和false是布尔类型的字面值，nullptr是指针字面值。



#### 2.2变量	P38

​		C++中，变量（variable）和对象（object）一般可以互换使用。

> 大多数人习惯认为对象是具有某种税局类型的内存空间。

​		C++中，初始化和赋值是两种完全不同的操作，但是在很多编程语言中，二者的区别几乎可以忽略不计，即使在C++中这种区别也无关紧要，但我们必须要有一个这种认识！



**列表初始化	P39**

​		C++提供了4中初始化的方法：

- int units_sold=0;
- int units_sold={0};
- int units_sold{0};
- int units_sold(0);

其中2、3两种用花括号来初始化的形式成为**列表初始化（list initialization）**。当用于内置类型的变量时，这种初始化形式有一个重要特点：如果我们使用列表初始化且存在丢失信息的风险，则编译器将报错，而其他形式的初始化并不会报错，且会丢失信息。具体例子见书P40。



**默认初始化	P40**

​		如果变量定义时没有杯指定初值，那么变量就会被默认初始化，被赋予”默认值“，默认值由变量类型决定，同时变量定义的位置也会对此有影响。**任何定义在函数体外部的变量被初始化为0，定义在函数体内部的内置类型变量将不被初始化，其值是未定义的。**



> 建议任何内置类型的变量都要手动初始化，因为如果未初始化，使用的将是一个不确定的值，这样造成的后果比逻辑错误更严重。



##### 2.2.2变量声明和定义的关系！！！！！！	P41

​		变量的声明和定义不是一个概念！！！

​		**声明**使得名字为程序所知，一个文件如果想使用别处定义的名字则必须包含对那个名字的声明。而**定义**负责创建与名字关联的实体。

​		变量声明规定了变量的类型和名字，在这一点上定义与之相同。但是除此之外，定义还申请存储空间，也可能会为变量赋一个初始值。

​		如果想要声明一个变量而非定义它，就在变量名前添加关键字extern，**而且不要显式地初始化变量：**

```c++
extern int i;	//声明i而非定义i
int j;	//声明并定义j
```

> 变量能且只能被定义一次，但是可以被多次声明。

​		变量的定义只能出现在一个文件中，如果其他文件要用到该变量，必须对其进行声明，但绝对不能重复定义。

>如果一个要在一个文件中使用另一个文件中的变量，则被使用的变量必须声明在文件作用域，也就是最外层，在其他文件中使用的时候要加上extern关键字。
>
>同时，要注意的是，要在一个文件中（前者）使用其他文件（后者）中的变量，我们有两种做法，第一种是直接在这个文件中include那个被使用的变量所在的文件，这样只用手动编译前者（也就是包含include的那个）；第二种方式是将不加include语句，但是要将后者编译成静态链接文件.o（使用-c选项），然后将前者与.o文件同时编译。

##### 2.2.3标识符

- 必须以字母或下划线开头

- 变量名一般用小写字母
- 用户自定义的类名一般用大写字母开头
- 多个单词一般用驼峰规则或者下划线来分割单词



#### 2.3复合类型	P45

​		这里先介绍两种符合类型：引用和指针。

##### 引用

> C++11中新增了”右值引用“，会在后面介绍，其主要用于内置类。严格来说，当我们使用术语”引用（reference）“时，指的是”左值引用“。xuanxiang

​		**引用（reference）**为对象起了另外一个名字，引用类型引用另外一种类型。定义形式：&d，d是声明的变量名。例如：`int ival=1024;int &refVal=ival;//refVal指向ival（是ival的另一个名字）`引用类型必须被初始化，否则会报错，定义引用时，会把引用和它的初始值**绑定（bind）**在一起，并且无法重新绑定。

> 引用**并非对象**，它只是为一个已经存在的对象起另外一个名字。



##### 指针

- 指针本身就是一个对象，允许对指针赋值和拷贝
- 指针无须在定义是赋初始值，但在编程时最好手动初始化，以避免其随机值带来的影响。
- 给指针赋值，它们的类型必须一致。



​		定义形式：*d，d是变量名。需要配合`&取址符`来定义。

​		空指针不指向任何对象。可以通过以下几种方法得到空指针：

```c++
int *p1=nullptr;
int *p2=0;
//先#include<cstdlib>
int *p3 = NULL;
```

​		在现在的C++中，建议使用前两种形式。



**void\*指针**

​		`void*`指针能指向任何类型的对象。但由于我们不知道它指向的地址到底是什么类型的对象，因此我们不能直接操作void*指针所指的对象。



**指向指针的引用**

​		当`*`和`&`叠加使用时，例如：`int *&r=p;`，那么我们应该从右往左读，最靠近变量名的修饰符决定了变量的性质。这里的r是一个指向指针的引用。



#### 2.4 const限定符

​		必须初始化，且不能修改。

​		默认情况下，const对象仅在文件内有效，如果要在不同文件中使用同一个const变量，那么就要在定义和声明处都加上extern关键字（非const变量只用在声明处加上extern），同时定义是定义在文件作用域。



> 今后要注意区分：指向常量的指针和常量指针。这是两个东西而不是一个。声明方式也不一样。具体见书P56。



##### constexpr和常量表达式

​		常量表达式（const expression）是指值不会改变并且在编译过程就能得到计算结果的表达式。对于字面值，要使用const声明才能算作常量表达式。

###### constexpr变量

​		constexpr关键字用于声明常量表达式变量，编译器会帮助验证你所定义的变量是不是常量表达式。



#### 2.5 处理类型	P60



##### 2.5.1 类型别名

​		定义一个类型的别名的传统方法是用关键字typedef：`typedef double wages;`。C++11提供了一种新的方法：使用using——别名声明，例子：`using SI = Sales_item;`，使SI等效于Sales_item。



##### 2.5.2 auto类型说明符

​		auto类型可以自动让编译器通过初始值判断这个变量是什么类型的，因此auto定义的变量必须有初始值。



##### 2.5.3 decltype 类型指示符

​		decltype返回的是操作数的数据类型，可以用它来声明一个变量，而不需要像auto一样必须通过初始化来定义。例：

```c++
const int ci=0,&cj=ci;
decltype(ci) x=0;
decltype(cj) y=x;
```

​	如果decltype后括号中的表达式的内容是解引用操作，那么decltype将得到引用类型，如果是外层带括号的表达式`decltype((ci))`，那么得到的也是引用类型，如果只是一个表达式，但是不带括号，例如：`decltype(ci+0)`，那么得到的就是int型。



#### 2.6 自定义数据结构 P64



##### 2.6.1 struct结构体

例：

```c++
struct Sales_data{
    std::string bookNo;
    unsigned units_sold=0;
    double revenue=0.0;
};
```

​		以struct关键字开始，紧接着的是结构体的名字，然后是花括号包括的具体内容，最后别忘了加上分号（这是因为可以直接在右花括号后面直接接变量名以示对该类型对象的定义）。





##### 2.6.3 编写自己的头文件

头文件的名字必须和类的名字一致，同时，为了保障当头文件被多次包含到一个文件中的时候也能正常工作，需要用预处理器来解决问题。

**预处理器**

​		预处理器是在编译之前执行的一段程序，可以部分的改变我们所写的程序。之前已经用到了一项预处理功能#include，当预处理器看到#include标记时就会用指定的头文件的内容代替#include。

​		我们这里要用到的是**头文件保护符（header guard）**，头文件保护符以来与处理变量。预处理变量只有两种状态：已定义和未定义。#define指定把一个名字设定为预处理变量，#ifdef和#ifndef用来检测预处理变量是否被定义，前者当被定义时为真，后者当为被定义时为真，当检查结果为真时，则执行后续操作直到遇到#endif指令为止。

> 整个程序中的预处理变量包括头文件保护符必须唯一，通常使用类的名字来构建保护符的名字，同时，预处理变量的名字全部大写。





### 第三章 字符串、向量和数组

#### 3.1 命名空间的using声明	P74

​		之前我们在使用每个标准库函数前都加上了`std::`来说明我们使用的是命名空间std中的名字，但是这样显得有些繁琐，如今我们可以用**using声明**来简化，形式如下：

```c++
using namespace::name;
//一个例子：
using std::cin;
```

​		一旦声明了上述语句，就可以在后面的代码中直接访问命名空间中的名字。

注意事项：

- 每个名字都需要独立的using声明
- 头文件不应包含using声明



#### 3.2 标准库类型string	P75

本节介绍一些string的常用操作

##### 3.2.1 定义和初始化string对象

初始化string有以下几种方式：

```c++
//1.
string s1;
//2.
string s2(s1);		//s2是s1的副本
//3.
string s2 = s1;		//等价于s2(s1),s2是s1的副本
//4.
string s3("value");		//s3是字面值“value”的副本，除了字面值最后的那个空字符外
//貌似string s3{"value"}也是一样的效果
//5.
string s3 = "value";	//等价于上一种方式
//6.
string s4(n,'c');	//把s4初始化为由连续n个字符c组成的串
```



##### string对象上的操作

**读写string对象**

可以通过cin和cout来读写。

> 在执行读操作的时候，string对象会自动忽略开头的空白并从第一个真正的字符开始读起，直到遇见下一处空白为止。



**读取位置数量的string对象**

```c++
int main()
{
    string word;
    while(cin >> word)
        cout<<word<<endl;
    return 0;
}
```

该程序在遇到EOF或非法输入时结束输入。



**用getline读取一整行**

为了让string能读取到字符串中的空白，我们使用`getline`来代替`>>`，getline读取一次会读取到遇到换行符的位置（**会读入换行符但是不会将换行符存入字符串中**）。示例：

```c++
int main()
{
    string line;
    while(getline(cin,line))
        cout<<line <<endl;
    return 0;
}
```



**string的empty和size操作**

`string.empty()`用来判断string对象是否为空，若为空则为真。`string.size()`返回的是string对象的长度。



**string::size_type类型**

`string.size()`返回的是一个string::size_type类型的值，而不是int或unsigned。它是一种无符号类型，注意不要轻易的把无符号类型和有符号数放在一个表达式中，否则有符号数会被自动转成无符号数。

**比较string对象**

可以直接用==、!=、<、<=、>、>=等操作符来比较string，不等关系比较的原则是比较第一个不相等的字符的字典序，如果两个不等长，但是短字符串是长字符串开头的一部分，那么短字符串小。

**string对象的赋值和加法**

比较简单，具体见书P80



##### 3.2.3 处理string对象中的字符

cctype头文件中提供了一系列标准库函数来处理字符串中的字符。P82

> C++版本的C标准库头文件
>
> C++版本的C标准库头文件的名称与C版本的有些不一样，C++版本的将C版本的后缀.h去掉了，在第一个字母前加上了一个字母c，例如：C的一个标准库头文件name.h的C++版本是cname，在以后的C++程序中，都建议使用C++版本的标准库头文件



**范围for语句**

```c++
for( declaration: expression)
    statement
```

与Java中的范围for语句功能一样。

**用范围for语句改变字符串中的字符**

要改变string对象中字符的值，必须把循环变量定义成引用类型，假设我们要把整个string对象转换成大写，只要对其中每个字符调用toupper函数并将结果再赋给原字符就可以了:

```c++
string s("Hello World!!!");
for(auto &c:s)
    c=toupper(c);
cout<<s<<endl;
```



**只处理一部分字符**

用**下表运算符（[]）**可以处理特定位置的字符。下标从0开始。

> **注意！！！**
>
> C++标准并不要求标准库检测下标是否合法，一旦使用了超出范围的下标，就会产生不可预知的结果。其下表范围必须大于等于0，小于size()的值。



#### 3.3 标准库类型vector	P86

​		vector表示对象的集合，其中所有对象的类型都相同。集合中每个对象都有一个与之对应的索引，索引用于访问对象。因为vector“容纳着”其他对象，所以它也常被称作**容器（container）**。vector在头文件vector中。

​		vector是一个类模板，它本身不是类，使用模板时需要指出编译器应该把类实例化成何种类型，类型写在尖括号中。示例：

```c++
vector<int> ivec;
vector<Sales_item>	Sales_vec;
vector<vector<string>> file;	//以前，还需要在string后的两个尖括号中加一个空格来区分>>符号
```



##### 3.3.1 定义和初始化vector对象

P87



**值初始化的**

​		当使用`vector<T> vec(n)`来创建一个vector时，会创建一个能容纳n个元素的vector，此时库会创建一个之初始化的元素初值，并把它赋给容器中的所有元素。这个初值由vector对象中元素的类型`T`决定。

​		如果vector对象的元素是内置类型，如int，则元素初始值自动设为0，如果是某种类，如string，则由该类默认初始化。



**列表初始值还是元素数量**

对于`vector<int>`的初始化，可能会有歧义，这里就要通过圆括号和花括号来区分了，简单来说就是，圆括号决定的是vector本身的属性，花括号的内容是vector内每个元素的值。



##### 3.3.2 向vector对象中添加元素

​		由于C++的vector能高效地增长，因此我们不需要在创建vector的时候指定大小，只有一种情况是例外，那就是所有元素的值都一样时，其他情况一般都是先定义一个空的vector对象，再在运行时向其中添加具体的值。

​		添加元素的操作由vector的成员函数**push_back**完成，例：`vec.push_back(T);`，其中vec是一个定义好的vector对象，T是vector包含的元素类型。

> 由此可见vector与一种数据结构很相似——栈。
>
> 在使用vector的时候，有一条隐含的要求：如果循环体内部包含有vector对象添加元素的语句，则不能用范围for循环。具体原因在5.4.3节介绍。



##### 3.3.3 其他vector操作	P91

​		访问vector中的元素也能通过范围for循环。

**计算vector内对象的索引**

​		vector内元素的索引与string一样，也是从0开始算起的。

**不能用下表形式添加元素（但是能通过下表来修改元素的值）**

​		只能通过push_back来添加。

> vector也存在下标不在正确范围内的情况，而且非常常见，由于这种错误不能被编译器发现，因此需要我们编程的时候非常仔细，同时，确保下标合法的一种有效手段就是尽可能使用范围for语句。
>
> 通过下表访问不存在的元素会导致严重后果——缓冲区溢出(buffer overflow)，这也可能导致程序出现安全问题。

