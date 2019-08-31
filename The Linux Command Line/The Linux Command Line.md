# The Linux Command Line



## Directories on the Linux under the root /

|             |                                                              |
| ----------- | ------------------------------------------------------------ |
| /bin        | binaries(programs) are used by the system to boot            |
| /boot       | contains Linux kernel, etc.    Interesting files:1./boot/grub/grub.conf or menu.lst  2./boot/vmlinuz (or something similar), the linux kernel |
| /dev        | hard ware devices                                            |
| /etc        | contains system-wide configuration files.    Interesting files:1./etc/crontab    2./etc/fstab,     3./etc/passwd, a list of system accounts |
| /home       |                                                              |
| /lib        | contains shared library files                                |
| /lost+found | relates to system recovery                                   |
| /mnt        |                                                              |
| /opt        | the place to install "optional" software                     |
| /sbin       | system binaries.                                             |
| /var        | "var" is the abbreviation of variable or various, and it means the files in this directories are likely to change. |





## 5-Working with Commands

- type
- which
- help
- man
- apropos: give you some advice about using which command depend on what you give the keyword.
- info
- whatis: display a one-line description of a man page matching a specified keyword.
- alias





## 6-Redirection

### standard output/error redirection

`>` is the **standard output redirection** operator, but rewriting the destination file. If we want to append the content, then use `>>`. 

`2>` is the **standard error out** redirection operator.

What if we want to redirect both standard output and error into a file?

We can use the `&>` or `&>>` to do this.



### **/dev/null**

/dev/null if a file that accepts input and does nothing with it, just like a black hole which eats up all of the input.

This file are usually used to suppress the error and status messages.



### cat

`cat [file...]` can redirect the content of file to the standard output which is the screen by default.

Specially, if we don't add any arguments to cat, it accepts standard input and redirect it to the standard output.

### standard input redirection

`<` is redirection operator.



### Pipelines(P61)

Pipe operator `|`  is often used as the form `command1 | command2`, and it redirect the standard output of command1 to the standard input command2.

> The difference between `>` and `|`
>
> - `>` is used to redirect output to a file
> - `|` is used to connect two command, such as `ls -l /usr/bin | less`



### wc - print line, word, and byte counts

wc - is the acronym of 'word count'.



### head/tail - print First/Last part of Files

They all have an argument `-n` followed by the number of you want to display.

Tail has an option `-f` which allows us to view files in real time.



### tee - read from stdin and ouput to both stdout and files

tee can accept input from stdin and copy it to both standard output and to one or more files.

It's very useful in pipeline.

example:`ls /usr/bin | tee ls.txt | grep zip`

Execute this command and you will see a file named "ls.txt" is created in your current folder and it stores the result of `ls /usr/bin`.

At the same time, the result will also be piped to `grep zip` command, then print some lines in your terminal.