/*
CTRL模块，用于流水线暂停
*/
`include "defines.v"

module ctrl(
    input  wire             rst,
    input  wire             stallreq_from_id,
    input  wire             stallreq_from_ex,

    //来自MEM模块的信号
    input  wire [31:0]      excepttype_i,
    input  wire [`RegBus]   cp0_epc_i,

    output reg [`RegBus]    new_pc,
    output reg              flush,

    output reg[5:0]     stall
);

    /*
    stall[0]表示取值地址PC是否不变，为1表示暂停，下同
    stall[1]表示流水线取指阶段是否暂停
    stall[2]表示译码阶段是否暂停
    stall[3]表示执行阶段是否暂停
    stall[4]表示访存阶段是否暂停
    stall[5]表示回写阶段是否暂停(这个暂时没用)
    */

    always @(*) begin
        if (rst == `RstEnable) begin
            stall    <=  6'b000000;
            flush    <=  1'b0;
            new_pc   <=  `ZeroWord;
        end else if(excepttype_i != `ZeroWord) begin
		    flush <= 1'b1;
		    stall <= 6'b000000;
			case (excepttype_i)
				32'h00000001:begin   //interrupt
					new_pc <= 32'h00000020;
				end
				32'h00000008:begin   //syscall
					new_pc <= 32'h00000040;
				end
				32'h0000000a:begin   //inst_invalid
					new_pc <= 32'h00000040;
				end
				32'h0000000d:begin   //trap
					new_pc <= 32'h00000040;
				end
				32'h0000000c:begin   //ov
					new_pc <= 32'h00000040;
				end
				32'h0000000e:begin   //eret
					new_pc <= cp0_epc_i;
				end
				default	: begin
				end
			endcase
        end else if(stallreq_from_ex == `Stop) begin
            stall   <=  6'b001111;
            flush   <=  1'b0;
        end else if(stallreq_from_id == `Stop) begin
            stall   <=  6'b000111;
            flush   <=  1'b0;
        end else begin
            stall   <=  6'b000000;
            flush   <=  1'b0;
            new_pc  <=  `ZeroWord;
        end
    end

endmodule // ctrl