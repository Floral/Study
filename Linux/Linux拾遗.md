# Anaconda

run

	$ source /opt/anaconda/bin/activate root
	$ source /opt/anaconda/bin/deactivate root

to activate and deactivate the anaconda enviroment.



# Bumblebee

active discrete graphics card

```bash
sudo tee /proc/acpi/bbswitch <<< ON
```



# Chrome

--proxy-server=host:port
              Specify the HTTP/SOCKS4/SOCKS5 proxy server to use for requests.  This overrides any environment variables or  settings
              picked via the options dialog.  An individual proxy server is specified using the format:

                [<proxy-scheme>://]<proxy-host>[:<proxy-port>]
    
              Where <proxy-scheme> is the protocol of the proxy server, and is one of:
    
                "http", "socks", "socks4", "socks5".
                Examples:
    
                    --proxy-server="foopy:99"
                        Use the HTTP proxy "foopy:99" to load all URLs.
    
                    --proxy-server="socks://foobar:1080"
                        Use the SOCKS v5 proxy "foobar:1080" to load all URLs.
    
                    --proxy-server="socks4://foobar:1080"
                        Use the SOCKS v4 proxy "foobar:1080" to load all URLs.
    
                    --proxy-server="socks5://foobar:66"
                        Use the SOCKS v5 proxy "foobar:66" to load all URLs.



# 用ssh在远程服务器python绘图时

要选择一个不需要gui的后端，例如agg，否则会报错





# VIM

- 跳到特定的某一行，有两种方式：

  1. 在正常模式中直接输入`行号+gg`（+只是表示连接，实际并不包含+号）
  2. 输入冒号进入命令行模式，然后直接输入行号并回车

- vim的分割模式

  在命令行模式中输入`split 另一个文件名`，vim就会将窗口分割成两个部分，分别显示当前文件和你输入的另一个文件，默认是上下分割，也可以使用左右分割的命令：`vsplit`。可以使用split命令打开多个文件，请君自行探索。

  如何在这些窗口中切换？按住`Ctrl`，再双击w键。



# 关于每次启动shell自动运行某个脚本的方法

https://blog.csdn.net/stpeace/article/details/49031389