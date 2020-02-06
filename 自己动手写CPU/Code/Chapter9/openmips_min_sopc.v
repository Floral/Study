
`include "defines.v"

module openmips_min_sopc(

	input wire	clk,
	input wire	rst
	
);

  //连接指令存储器
	wire[`InstAddrBus] inst_addr;
	wire[`InstBus] inst;
	wire rom_ce;
 
	//实例化处理器open MIPS
 	openmips openmips0(
		.clk(clk),
		.rst(rst),
	
		.rom_data_i(inst),
		.rom_addr_o(inst_addr),
		.rom_ce_o(rom_ce)
	
	);
	
	inst_rom inst_rom0(
		.ce(rom_ce),
		.addr(inst_addr),
		.inst(inst)
	);


endmodule