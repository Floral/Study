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

### Standard Input and Output Obejects

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

​    When *istream* is used as a condition, the test is **true** if the *istream* hasn't encounter an error, and **false** if it encounter the end-of-file or invalid input( such as reading a value that is not the variable is declared ). 

> ​    When we enter input to a program from the keyboard, different operating systems use different conventions to allow us to indicates end-of-file.
>
> ​	In Windows: press `ctrl` and `z` simultaneously.
>
> ​	In Unix: press `ctrl` and `d` simultaneously.

