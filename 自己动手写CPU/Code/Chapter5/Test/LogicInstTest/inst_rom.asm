
inst_rom.om:     file format elf32-tradbigmips


Disassembly of section .text:

00000000 <_start>:
   0:	3c010101 	lui	at,0x101
   4:	34210101 	ori	at,at,0x101
   8:	34221100 	ori	v0,at,0x1100
   c:	00220825 	or	at,at,v0
  10:	302300fe 	andi	v1,at,0xfe
  14:	00610824 	and	at,v1,at
  18:	3824ff00 	xori	a0,at,0xff00
  1c:	00810826 	xor	at,a0,at
  20:	00810827 	nor	at,a0,at

Disassembly of section .MIPS.abiflags:

00000028 <_ram_end-0x18>:
  28:	00002001 	movf	a0,zero,$fcc0
  2c:	01010001 	movt	zero,t0,$fcc0
	...
  38:	00000001 	movf	zero,zero,$fcc0
  3c:	00000000 	nop

Disassembly of section .reginfo:

00000000 <.reginfo>:
   0:	0000001e 	0x1e
	...

Disassembly of section .gnu.attributes:

00000000 <.gnu.attributes>:
   0:	41000000 	bc0f	4 <_start+0x4>
   4:	0f676e75 	jal	d9db9d4 <_ram_end+0xd9db994>
   8:	00010000 	sll	zero,at,0x0
   c:	00070401 	0x70401
