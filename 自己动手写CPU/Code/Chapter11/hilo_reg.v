/*
特殊寄存器HI和LO
*/
`include "defines.v"

module hilo_reg(
    input  wire             clk,
    input  wire             rst,

    //写端口
    input  wire             we,     //HI、LO寄存器的写使能端口，WriteEnable
    input  wire [`RegBus]   hi_i,   //写入HI的值
    input  wire [`RegBus]   lo_i,   //写入LO的值

    //读端口，由于这个模块总共只有两个寄存器，直接用两个输出端口存值，不需要像regfile一样使用regs保存，再通过输出端口rdata选择某一/两个reg输出
    output reg [`RegBus]    hi_o,   //HI的值
    output reg [`RegBus]    lo_o    //LO的值
);

    always @(posedge clk) begin
        if (rst == `RstEnable) begin
            hi_o    <=  `ZeroWord;
            lo_o    <=  `ZeroWord;
        end else if(we == `WriteEnable) begin
            hi_o    <=  hi_i;
            lo_o    <=  lo_i;
        end
    end

endmodule // hilo_reg