/*
这是该CPU的32个通用寄存器，属于译码阶段
*/

`include "defines.v"

module regfile(
    input wire  clk,
    input wire  rst,

    //写端口
    input wire  we, //writeEnable
    input wire[`RegAddrBus] waddr,  //写入地址
    input wire[`RegBus]     wdata,  //写入的数据

    //读端口1
    input wire re1, //readEnable1,第一个读端口的使能信号
    input wire[`RegAddrBus] raddr1,
    output reg[`RegBus]     rdata1,

    //读端口2
    input wire re2, //readEnable2,第二个读端口的使能信号
    input wire[`RegAddrBus] raddr2,
    output reg[`RegBus]     rdata2
);

    //*********定义32个32位寄存器************
    reg[`RegBus] regs[0:`RegNum-1];

    //写操作,注意这里的敏感信号，写操作是时序电路，故对时钟信号敏感
    always @(posedge clk ) begin
        if (rst == `RstDisable) begin
            if((we == `WriteEnable) && (waddr != `RegNumLog2'h0)) begin
                regs[waddr] <= wdata;
            end
        end
    end

    //**********读端口1的读操作*************
    //特殊情况优先考虑，放前面；读操作是组合电路，addr变化就立即输出rdata，所以对任何输入都敏感
    always @(*) begin
        if (rst == `RstEnable) begin
            rdata1 <= `ZeroWord;
        end else if (raddr1 == `RegNumLog2'h0) begin
            rdata1 <= `ZeroWord;
        end else if ((raddr1 == waddr) && (we == `WriteEnable) && (re1 ==`ReadEnable)) begin
            rdata1 <= wdata;
        end else if (re1 == `ReadEnable)  begin
            rdata1 <= regs[raddr1];
        end else begin
            rdata1 <= `ZeroWord;
        end
    end

    //**********读端口2的读操作*************
    //特殊情况优先考虑，放前面
    always @(*) begin
        if (rst == `RstEnable) begin
            rdata2 <= `ZeroWord;
        end else if (raddr2 == `RegNumLog2'h0) begin
            rdata2 <= `ZeroWord;
        end else if ((raddr2 == waddr) && (we == `WriteEnable) && (re2 ==`ReadEnable)) begin
            rdata2 <= wdata;
        end else if (re2 == `ReadEnable)  begin
            rdata2 <= regs[raddr2];
        end else begin
            rdata2 <= `ZeroWord;
        end
    end

endmodule // regfile