/*
除法模块
*/

`include "defines.v"

module div(
    input  wire     clk,
    input  wire     rst,

    input  wire         signed_div_i,   //是否是有符号除法，1为有符号
    input  wire [31:0]  opdata1_i,
    input  wire [31:0]  opdata2_i,
    input  wire         start_i,        //是否开始除法运算
    input  wire         annul_i,        //是否取消除法运算，1为取消

    output reg [63:0]   result_o,       //除法运算结果
    output reg          ready_o         //除法运算是否结束
);

    wire [32:0]     div_temp;
    reg [5:0]       cnt;        //记录试商法进行了几轮，等于32时表示试商法结束
    reg [64:0]      dividend;
    reg [1:0]       state;      //div模块内部是一个有限状态机，这个用来指示状态，总共有四种状态
    reg [31:0]      divisor;
    reg [31:0]      temp_op1;
    reg [31:0]      temp_op2;


    //div_temp的高32位是每次迭代的被减数，此处进行的就是minuend-n运算
    assign div_temp = {1'b0, dividend[63:32]} - {1'b0, divisor};

    always @(posedge clk) begin
        if(rst == `RstEnable) begin
            state   <=  `DivFree;
            ready_o <=  `DivResultNotReady;
            result_o<=  {`ZeroWord, `ZeroWord};
        end else begin
            case (state)
                `DivFree: begin               //DivFree״̬
		  		    if(start_i == `DivStart && annul_i == 1'b0) begin
		  			    if(opdata2_i == `ZeroWord) begin    //如果除数是0
		  				    state <= `DivByZero;
		  			    end else begin
		  				    state <= `DivOn;
		  				    cnt <= 6'b000000;
		  				    if(signed_div_i == 1'b1 && opdata1_i[31] == 1'b1 ) begin
		  					    temp_op1 = ~opdata1_i + 1;      //被除数是负数，转补码
		  				    end else begin
		  					    temp_op1 = opdata1_i;
		  				    end
		  				    if(signed_div_i == 1'b1 && opdata2_i[31] == 1'b1 ) begin
		  				    	temp_op2 = ~opdata2_i + 1;
		  				    end else begin
		  				    	temp_op2 = opdata2_i;
		  				    end
		  				    dividend <= {`ZeroWord,`ZeroWord};
                            dividend[32:1] <= temp_op1;
                            divisor <= temp_op2;
                        end
                    end else begin
						ready_o <= `DivResultNotReady;
						result_o <= {`ZeroWord,`ZeroWord};
				    end          	
		  	    end
		  	    `DivByZero:	begin               //DivByZero״̬
         	        dividend <= {`ZeroWord,`ZeroWord};
                    state <= `DivEnd;		 		
		  	    end
		  	    `DivOn:	begin               //DivOn״̬
		  		    if(annul_i == 1'b0) begin
		  			    if(cnt != 6'b100000) begin
                            if(div_temp[32] == 1'b1) begin
                                dividend <= {dividend[63:0] , 1'b0};
                            end else begin
                                dividend <= {div_temp[31:0] , dividend[31:0] , 1'b1};
                            end
                            cnt <= cnt + 1;
                        end else begin
                            if((signed_div_i == 1'b1) && ((opdata1_i[31] ^ opdata2_i[31]) == 1'b1)) begin
                                dividend[31:0] <= (~dividend[31:0] + 1);
                            end
                            if((signed_div_i == 1'b1) && ((opdata1_i[31] ^ dividend[64]) == 1'b1)) begin              
                                dividend[64:33] <= (~dividend[64:33] + 1);
                            end
                            state <= `DivEnd;
                            cnt <= 6'b000000;            	
                        end
		  		    end else begin
		  			    state <= `DivFree;
		  		    end	
		  	    end
		  	    `DivEnd: begin               //DivEnd״̬
        	        result_o <= {dividend[64:33], dividend[31:0]}; //高位是余数，低位是商 
                    ready_o <= `DivResultReady;
                    if(start_i == `DivStop) begin
          	            state <= `DivFree;
					    ready_o <= `DivResultNotReady;
					    result_o <= {`ZeroWord,`ZeroWord};       	
                    end		  	
		  	    end
            endcase
        end 
    end



endmodule //div