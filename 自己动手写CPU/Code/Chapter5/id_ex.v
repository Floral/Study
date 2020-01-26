/*
这是译码阶段到执行阶段的过度模块
本模块只有一个时序电路，只是简单地将译码阶段的结果在时钟周期地上升沿传递到执行阶段
*/

`include "defines.v"

module id_ex(
    input  wire  clk,
    input  wire  rst,

    //从译码阶段传递过来的信息
    input  wire [`AluOpBus]     id_aluop,
    input  wire [`AluSelBus]    id_alusel,
    input  wire [`RegBus]       id_reg1,
    input  wire [`RegBus]       id_reg2,
    input  wire [`RegAddrBus]   id_wd,
    input  wire                 id_wreg,

    //传递给执行阶段的信息
    output reg [`AluOpBus]      ex_aluop,
    output reg [`AluSelBus]     ex_alusel,
    output reg [`RegBus]        ex_reg1,
    output reg [`RegBus]        ex_reg2,
    output reg [`RegAddrBus]    ex_wd,
    output reg                  ex_wreg                   
);

    always @(posedge clk) begin
        if (rst == `RstEnable) begin
            ex_aluop    <=  `EXE_NOP_OP;
            ex_alusel   <=  `EXE_RES_NOP;
            ex_reg1     <=  `ZeroWord;
            ex_reg2     <=  `ZeroWord;
            ex_wd       <=  `NOPRegAddr;
            ex_wreg     <=  `WriteDisable;
        end else begin
            ex_aluop    <=  id_aluop;
            ex_alusel   <=  id_alusel;
            ex_reg1     <=  id_reg1;
            ex_reg2     <=  id_reg2;
            ex_wd       <=  id_wd;
            ex_wreg     <=  id_wreg;
        end
    end

endmodule // id_ex