/*
这是五级流水线的第二阶段——译码阶段
*/

`include "defines.v"

module id(
    input  wire  rst,
    input  wire[`InstAddrBus]   pc_i,     //所要译码的指令对应的地址
    input  wire[`InstBus]       inst_i,

    //读取的Regfile的值
    input  wire[`RegBus]        reg1_data_i,
    input  wire[`RegBus]        reg2_data_i,

    //处于执行阶段的指令的运算结果
    input  wire                 ex_wreg_i,      //处于执行阶段的指令是否要写入目的寄存器
    input  wire [`RegBus]       ex_wdata_i,     //写入的寄存器的数据
    input  wire [`RegAddrBus]   ex_wd_i,        //写入的寄存器的地址

    //处于访存阶段的指令的运算结果
    input  wire                 mem_wreg_i,
    input  wire [`RegBus]       mem_wdata_i,
    input  wire [`RegAddrBus]   mem_wd_i,

    //输出给Regfile的信息（为了读取Regfile里的数据
    output reg              reg1_read_o,    //接读端口1的使能信号
    output reg              reg2_read_o,    //接读端口2的使能信号
    output reg[`RegAddrBus] reg1_addr_o,
    output reg[`RegAddrBus] reg2_addr_o,

    //送到执行阶段的信息
    output reg[`AluOpBus]   aluop_o,    //指令要进行的运算的子类型
    output reg[`AluSelBus]  alusel_o,   //指令要进行的运算的类型
    output reg[`RegBus]     reg1_o,     //送到执行阶段的源操作数1
    output reg[`RegBus]     reg2_o,     //源操作数2
    output reg[`RegAddrBus] wd_o,       //指令要写入的目的寄存器的地址
    output reg              wreg_o      //是否有要写入的目的寄存器

);
    //取得指令的指令码，功能码
    //ori指令只需判断26-31bit的值，就能判断该指令是否是ori指令
    wire [5:0] op = inst_i[31:26];
    wire [4:0] op2 = inst_i[10:6];
    wire [5:0] op3 = inst_i[5:0];
    wire [4:0] op4 = inst_i[20:16];

    //保存指令执行所需要的立即数
    reg[`RegBus] imm;

    //指示指令是否有效
    reg instvalid;

    /**************第一部分：对指令进行译码**********/
    always @(*) begin
        if(rst == `RstEnable) begin
            aluop_o     <=  `EXE_NOP_OP;
            alusel_o    <=  `EXE_RES_NOP;
            wd_o        <=  `NOPRegAddr;
            instvalid   <=  `InstValid;
            reg1_read_o <=  1'b0;
            reg2_read_o <=  1'b0;
            reg1_addr_o <=  `NOPRegAddr;
            reg2_addr_o <=  `NOPRegAddr;
            imm <=32'h0;
        end else begin
            aluop_o     <=  `EXE_NOP_OP;
            alusel_o    <=  `EXE_RES_NOP;
            wd_o        <=  inst_i[15:11];
            wreg_o      <=  `WriteDisable;
            instvalid   <=  `InstInvalid;
            reg1_read_o <=  1'b0;
            reg2_read_o <=  1'b0;
            reg1_addr_o <=  inst_i[25:21];     //这两个是默认情况下的操作数来源地址
            reg2_addr_o <=  inst_i[20:16];
            imm <=  `ZeroWord;

            case (op)   //通过op的值判断是否是ori指令
                `EXE_ORI: begin
                    //ori指令需要将结果写入目的寄存器，所以wreg_o为WriteEnable
                    wreg_o  <=  `WriteEnable;

                    //运算的子类型是逻辑“或”运算
                    aluop_o <=  `EXE_OR_OP;

                    //运算类型是逻辑运算
                    alusel_o    <=  `EXE_RES_LOGIC;

                    //需要通过Regfile的读端口1读取寄存器
                    reg1_read_o <=  1'b1;

                    //不需要读端口2的数据
                    reg2_read_o <=  1'b0;

                    //指令执行所需要的立即数，拼接成32位
                    imm <= {16'h0, inst_i[15:0]};

                    //指令执行要写的目的寄存器
                    wd_o <= inst_i[20:16];

                    //ori指令是有效指令
                    instvalid   <=  `InstValid;
                end 
                default: begin
                    
                end 
            endcase     //case op         
        end     //if
    end         //always


    /**************第二部分：确定运算的源操作数1***************/
    /*
    给reg1/2_o赋值的过程增加了两中情况:
    1.如果Regfile模块读端口1/2要取的寄存器就是执行阶段要写的寄存器，那么直接吧执行阶段的结果ex_wdata_i作为reg1/2_o的值
    2.如果Regfile模块读端口1/2要取的寄存器就是访存阶段要写的寄存器，那么直接把访存阶段的结果mem_wdata_i作为reg1/2_o的值
    */
    always @(*) begin
        if (rst == `RstEnable) begin
            reg1_o <= `ZeroWord;
        end else if ((reg1_read_o == 1'b1) && (ex_wreg_i == 1'b1)
                    && (ex_wd_i == reg1_addr_o )) begin
            reg1_o <= ex_wdata_i;
        end else if ((reg1_read_o == 1'b1) && (mem_wreg_i == 1'b1)
                    && (mem_wd_i == reg1_addr_o )) begin
            reg1_o <= mem_wdata_i;
        end else if (reg1_read_o == 1'b1) begin
            reg1_o <= reg1_data_i;      //Regfile读端口1 的输出
        end else if (reg1_read_o == 1'b0) begin
            reg1_o <= imm;              //不是从寄存器读的话就是立即数
        end else begin
            reg1_o <= `ZeroWord;
        end
    end

    /**************第二部分：确定运算的源操作数2*************/
    always @(*) begin
        if (rst == `RstEnable) begin
            reg2_o <= `ZeroWord;
        end else if ((reg2_read_o == 1'b1) && (ex_wreg_i == 1'b1)
                    && (ex_wd_i == reg2_addr_o )) begin
            reg2_o <= ex_wdata_i;
        end else if ((reg2_read_o == 1'b1) && (mem_wreg_i == 1'b1)
                    && (mem_wd_i == reg2_addr_o )) begin
            reg2_o <= mem_wdata_i;
        end else if (reg2_read_o == 1'b1) begin
            reg2_o <= reg2_data_i;      //Regfile读端口2 的输出
        end else if (reg2_read_o == 1'b0) begin
            reg2_o <= imm;
        end else begin
            reg2_o <= `ZeroWord;
        end
    end


    
endmodule // id