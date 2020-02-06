/*
CTRL模块，用于流水线暂停
*/
`include "defines.v"

module ctrl(
    input  wire         rst,
    input  wire         stallreq_from_id,
    input  wire         stallreq_from_ex,
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
       end else if(stallreq_from_ex == `Stop) begin
           stall    <=  6'b001111;
       end else if(stallreq_from_id == `Stop) begin
           stall    <=  6'b000111;
       end else begin
           stall    <=  6'b000000;
       end
    end

endmodule // ctrl