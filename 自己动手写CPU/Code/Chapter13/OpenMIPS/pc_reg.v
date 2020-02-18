/*
这是五级流水线的第一阶段——取指令，的实现代码
*/

`include "defines.v"

module pc_reg(
    input  wire                 clk,    //时钟信号
    input  wire                 rst,    //复位信号
    input  wire [5:0]           stall,      //来自控制模块CTRL

    //来自译码阶段ID的信息
    input  wire                 branch_flag_i,  
    input  wire [`RegBus]       branch_target_address_i,

    input  wire                 flush,
    input  wire [`RegBus]       new_pc,
    
    output reg[`InstAddrBus]    pc,
    output reg                  ce
);

    always @(posedge clk) begin
        if (rst == `RstEnable) begin
            ce <= `ChipDisable;      //复位时指令存储器禁用
        end else begin
            ce <= `ChipEnable;
        end
    end

    //这相当于一个MUX
    always @(posedge clk) begin
        if (ce == `ChipDisable) begin
            pc <= 32'h30000000;      //指令寄存器禁用的时候，PC=0
        end else begin
            if (flush == 1'b1) begin
                pc  <=  new_pc; //flush==1表示有异常发生，从而转入异常处理例程
            end else if(stall[0] == `NoStop) begin
                if(branch_flag_i == `Branch) begin
                    pc  <=  branch_target_address_i;
                end else begin
                    pc <= pc + 4'h4;         //指令寄存器使能的时候，PC的值每时钟周期加4（因为地址是按字节编址，而数据线是32位）
                end
            end
        end
    end
endmodule