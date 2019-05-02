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

