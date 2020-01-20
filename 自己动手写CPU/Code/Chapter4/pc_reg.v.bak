/*
这是五级流水线的第一阶段——取指令，的实现代码
*/

`include "defines.v"

module pc_reg(
    input wire  clk,    //时钟信号
    input wire  rst,    //复位信号
    output reg[`InstAddrBus] pc,
    output reg  ce
);

    always @(posedge clk) begin
        if (rst == `RstEnable) begin
            ce <= `ChipDisable      //复位时指令存储器禁用
        end else begin
            ce <= `ChipEnable
        end
    end

    always @(posedge clk) begin
        if (ce == `ChipDisable) begin
            pc <= 32'h00000000      //指令寄存器禁用的时候，PC=0
        end else begin
            pc <= pc + 4'h4         //指令寄存器使能的时候，PC的值每时钟周期加4（因为地址是按字节编址，而数据线是32位）
        end
    end
endmodule