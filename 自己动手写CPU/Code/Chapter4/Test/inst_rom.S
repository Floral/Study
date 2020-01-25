.org 0x0          # 指示程序从地址0x0开始
.global _start    # 定义一个全局符号_start
.set noat         # 允许自由使用寄存器$1 
_start:
   ori $1,$0,0x1100        # $1 = $0 | 0x1100 = 0x1100
   ori $2,$0,0x0020        # $2 = $0 | 0x0020 = 0x0020
   ori $3,$0,0xff00        # $3 = $0 | 0xff00 = 0xff00
   ori $4,$0,0xffff        # $4 = $0 | 0xffff = 0xffff
