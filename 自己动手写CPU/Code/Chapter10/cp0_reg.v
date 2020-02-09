`include "defines.v"


module cp0_reg(
    input  wire             clk,
    input  wire             rst,

    input  wire             we_i,
    input  wire [4:0]       waddr_i,
    input  wire [4:0]       raddr_i,
    input  wire [`RegBus]   data_i,

    input  wire [5:0]       int_i,

    output reg [`RegBus]    data_o,
	output reg [`RegBus]    count_o,
	output reg [`RegBus]    compare_o,
	output reg [`RegBus]    status_o,
	output reg [`RegBus]    cause_o,
	output reg [`RegBus]    epc_o,
	output reg [`RegBus]    config_o,
	output reg [`RegBus]    prid_o,
	
	output reg                   timer_int_o 
);
    


endmodule // cp0_reg