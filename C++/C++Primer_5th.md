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

