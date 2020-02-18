/*
这是五级流水线由第一阶段到第二阶段过度的实现代码
if_id是instruction fetch 和 instruction decode的缩写
*/

`include "defines.v"

module if_id(
    input wire clk,
    input wire rst,

    //
    input wire[`InstAddrBus]    if_pc,
    input wire[`InstBus]        if_inst,

    input  wire [5:0]           stall,

    input  wire                 flush,
    //
    output reg[`InstAddrBus]    id_pc,
    output reg[`InstBus]        id_inst
);

    always @(posedge clk ) begin
        if (rst == `RstEnable) begin
            id_pc   <=  `ZeroWord;
            id_inst <=  `ZeroWord;
        end else if(flush == 1'b1) begin
            id_pc   <=  `ZeroWord;
            id_inst <=  `ZeroWord;
        end else if(stall[1] == `Stop && stall[2] == `NoStop) begin
            id_pc   <=  `ZeroWord;
            id_inst <=  `ZeroWord;
        end else if(stall[1] == `NoStop) begin
            id_pc   <=  if_pc;
            id_inst <=  if_inst;
        end
    end

endmodule // if_id