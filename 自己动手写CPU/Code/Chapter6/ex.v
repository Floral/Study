/*
五级流水线中的执行阶段
*/

`include "defines.v"

module ex(
    input  wire rst,

    //译码阶段送到执行阶段的信息
    input  wire [`AluOpBus]     aluop_i,
    input  wire [`AluSelBus]    alusel_i,
    input  wire [`RegBus]       reg1_i,
    input  wire [`RegBus]       reg2_i,
    input  wire [`RegAddrBus]   wd_i,
    input  wire                 wreg_i,

    //执行结果
    output reg [`RegAddrBus]    wd_o,
    output reg                  wreg_o,
    output reg [`RegBus]        wdata_o
);
    //保存逻辑运算的结果
    reg[`RegBus]    logicout;
    reg[`RegBus]    shiftres;   //保存移位运算结果

    /**************第一部分：依据aluop_i指示的运算子类型进行运算，此处只有逻辑“或”运算*******/
    always @(*) begin
        if (rst == `RstEnable) begin
            logicout <= `ZeroWord;
        end else begin
            case (aluop_i)
                `EXE_OR_OP:begin
                    logicout <= reg1_i | reg2_i;
                end 
                `EXE_AND_OP:begin
                    logicout <= reg1_i & reg2_i;
                end
                `EXE_NOR_OP:begin
                    logicout <= ~(reg1_i|reg2_i);
                end
                `EXE_XOR_OP:begin
                    logicout <= reg1_i ^ reg2_i;
                end
                default: begin
                    logicout <= `ZeroWord;
                end
            endcase
        end //if
    end     //always

    always @(*) begin
        if(rst == `RstEnable) begin
            shiftres    <=  `ZeroWord;
        end else begin
            case(aluop_i)
                `EXE_SLL_OP:begin       //逻辑左移
                    shiftres    <=  reg2_i  <<  reg1_i[4:0];
                end
                `EXE_SRL_OP:begin       //逻辑右移
                    shiftres    <=  reg2_i  >>  reg1_i[4:0];
                end
                `EXE_SRA_OP:begin       //算术右移
                    shiftres    <=  ({32{reg2_i[31]}}<<(6'd32-{1'b0, reg1_i[4:0]}))
                                    | reg2_i >> reg1_i[4:0];
                end
                default: begin
                    shiftres    <=  `ZeroWord;
                end
	    endcase
        end //if
    end //always


    //*****************第三部分:依据alusel_i指示的运算类型，选择一个运算结果作为最终结果 *************/
    always @(*) begin
        wd_o    <=  wd_i;
        wreg_o  <=  wreg_i;
        case (alusel_i)
            `EXE_RES_LOGIC: begin
                wdata_o <=  logicout;   //选择逻辑运算结果为最终运算结果
            end 
            `EXE_RES_SHIFT: begin
                wdata_o <=  shiftres;   //选择移位运算结果为最终运算结果
            end
            default: begin
                wdata_o <=  `ZeroWord;
            end
        endcase
    end


endmodule // ex