/*
指令存储器ROM模块
*/
`include "defines.v"

module inst_rom(

	input wire              	ce,
	input wire[`InstAddrBus]	addr,
	output reg[`InstBus]		inst
);
	//定义一个数组，相当于ROM的存储空间，大小是InstMemNum，元素宽度是InstBus
	reg[`InstBus]  inst_mem[0:`InstMemNum-1];

	//使用文件inst_rom.data初始化rom
	initial $readmemh ( "inst_rom.data", inst_mem );

	always @ (*) begin
		if (ce == `ChipDisable) begin
			inst <= `ZeroWord;
	  end else begin
		  inst <= inst_mem[addr[`InstMemNumLog2+1:2]];	//由于openmips是按照字节寻址的，而一条指令为4个字节，所以实际取的地址要除以4
		end
	end

endmodule