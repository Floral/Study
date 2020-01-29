
inst_rom.om:     file format elf32-tradbigmips


Disassembly of section .text:

00000000 <_start>:
   0:	3c010000 	lui	at,0x0
   4:	3c02ffff 	lui	v0,0xffff
   8:	3c030505 	lui	v1,0x505
   c:	3c040000 	lui	a0,0x0
  10:	0041200a 	movz	a0,v0,at
  14:	0061200b 	movn	a0,v1,at
  18:	0062200b 	movn	a0,v1,v0
  1c:	0043200a 	movz	a0,v0,v1
  20:	00000011 	mthi	zero
  24:	00400011 	mthi	v0
  28:	00600011 	mthi	v1
  2c:	00002010 	mfhi	a0
  30:	00600013 	mtlo	v1
  34:	00400013 	mtlo	v0
  38:	00200013 	mtlo	at
  3c:	00002012 	mflo	a0

Disassembly of section .MIPS.abiflags:

00000040 <_ram_end-0x20>:
  40:	00002001 	movf	a0,zero,$fcc0
  44:	01010001 	movt	zero,t0,$fcc0
	...
  50:	00000001 	movf	zero,zero,$fcc0
  54:	00000000 	nop

Disassembly of section .reginfo:

00000000 <.reginfo>:
   0:	0000001e 	0x1e
	...

Disassembly of section .gnu.attributes:

00000000 <.gnu.attributes>:
   0:	41000000 	bc0f	4 <_start+0x4>
   4:	0f676e75 	jal	d9db9d4 <_ram_end+0xd9db974>
   8:	00010000 	sll	zero,at,0x0
   c:	00070401 	0x70401
