`include "defines.v"

module id(
    input  wire  rst,
    input  wire[`InstAddrBus]   pc_i,     //所要译码的指令对应的地址
    input  wire[`InstBus]       inst_i,

	//读取的Regfile的值
    input  wire[`RegBus]        reg1_data_i,
    input  wire[`RegBus]        reg2_data_i,

	//处于执行阶段的指令要写入的目的寄存器信息
	input wire					ex_wreg_i,
	input wire[`RegBus]			ex_wdata_i,
	input wire[`RegAddrBus]     ex_wd_i,
	
	//处于访存阶段的指令要写入的目的寄存器信息
	input wire					mem_wreg_i,
	input wire[`RegBus]			mem_wdata_i,
	input wire[`RegAddrBus]     mem_wd_i,

    //输出给Regfile的信息（为了读取Regfile里的数据
    output reg              reg1_read_o,    //接读端口1的使能信号
    output reg              reg2_read_o,    //接读端口2的使能信号
    output reg[`RegAddrBus] reg1_addr_o,
    output reg[`RegAddrBus] reg2_addr_o,

    //送到执行阶段的信息
    output reg[`AluOpBus]   aluop_o,    //指令要进行的运算的子类型
    output reg[`AluSelBus]  alusel_o,   //指令要进行的运算的类型
    output reg[`RegBus]     reg1_o,     //从寄存器取得的源操作数1
    output reg[`RegBus]     reg2_o,     //源操作数2
    output reg[`RegAddrBus] wd_o,       //指令要写入的目的寄存器的地址
    output reg              wreg_o      //是否有要写入的目的寄存器
);

  wire[5:0] op = inst_i[31:26];
  wire[4:0] op2 = inst_i[10:6];
  wire[5:0] op3 = inst_i[5:0];
  wire[4:0] op4 = inst_i[20:16];
  reg[`RegBus]	imm;
  reg instvalid;
  
	always @ (*) begin	
		if (rst == `RstEnable) begin
			aluop_o <= `EXE_NOP_OP;
			alusel_o <= `EXE_RES_NOP;
			wd_o <= `NOPRegAddr;
			wreg_o <= `WriteDisable;
			instvalid <= `InstValid;
			reg1_read_o <= 1'b0;
			reg2_read_o <= 1'b0;
			reg1_addr_o <= `NOPRegAddr;
			reg2_addr_o <= `NOPRegAddr;
			imm <= 32'h0;			
	    end else begin		//这一部分都是默认赋值
			aluop_o <= `EXE_NOP_OP;
			alusel_o <= `EXE_RES_NOP;
			wd_o <= inst_i[15:11];		//默认目的寄存器地址wd_o
			wreg_o <= `WriteDisable;
			instvalid <= `InstInvalid;	   
			reg1_read_o <= 1'b0;
			reg2_read_o <= 1'b0;
			reg1_addr_o <= inst_i[25:21];
			reg2_addr_o <= inst_i[20:16];		
			imm <= `ZeroWord;
		    case (op)
		        `EXE_SPECIAL_INST:begin     //指令码是SPECIAL
		    	    case (op2)
		    		    5'b00000:begin
		    			    case (op3)
		    				    `EXE_OR:begin   //or指令
		    					    wreg_o <= `WriteEnable;
                              		aluop_o <= `EXE_OR_OP;
		  						    alusel_o <= `EXE_RES_LOGIC; 	
                                    reg1_read_o <= 1'b1;
                                    reg2_read_o <= 1'b1;
		  						    instvalid <= `InstValid;	
								end  
		    				    `EXE_AND:begin  //and指令
		    					    wreg_o <= `WriteEnable;
                                    aluop_o <= `EXE_AND_OP;
		  						    alusel_o <= `EXE_RES_LOGIC;
                                    reg1_read_o <= 1'b1;
                                    reg2_read_o <= 1'b1;	
		  						    instvalid <= `InstValid;	
								end  	
		    				    `EXE_XOR:begin
                                    wreg_o <= `WriteEnable;
                                    aluop_o <= `EXE_XOR_OP;
                                    alusel_o <= `EXE_RES_LOGIC;
                                    reg1_read_o <= 1'b1;
                                    reg2_read_o <= 1'b1;	
                                    instvalid <= `InstValid;	
								end  				
		    				    `EXE_NOR:begin
                                    wreg_o <= `WriteEnable;
                                    aluop_o <= `EXE_NOR_OP;
                                    alusel_o <= `EXE_RES_LOGIC;
                                    reg1_read_o <= 1'b1;
                                    reg2_read_o <= 1'b1;	
                                    instvalid <= `InstValid;	
								end 
								`EXE_SLLV: begin
									wreg_o <= `WriteEnable;		
                                    aluop_o <= `EXE_SLL_OP;
		  						    alusel_o <= `EXE_RES_SHIFT;
                               		reg1_read_o <= 1'b1;
                                    reg2_read_o <= 1'b1;
		  						    instvalid <= `InstValid;	
								end 
								`EXE_SRLV: begin
									wreg_o <= `WriteEnable;
                                    aluop_o <= `EXE_SRL_OP;
		  						    alusel_o <= `EXE_RES_SHIFT;
                                    reg1_read_o <= 1'b1;
                                    reg2_read_o <= 1'b1;
		  						    instvalid <= `InstValid;	
								end 					
								`EXE_SRAV: begin
									wreg_o <= `WriteEnable;	
                                    aluop_o <= `EXE_SRA_OP;
		  						    alusel_o <= `EXE_RES_SHIFT;	
                                    reg1_read_o <= 1'b1;
                                    reg2_read_o <= 1'b1;
		  						    instvalid <= `InstValid;			
		  						end			
								`EXE_SYNC: begin
									wreg_o <= `WriteDisable;
                                    aluop_o <= `EXE_NOP_OP;
		  						    alusel_o <= `EXE_RES_NOP;
                                    reg1_read_o <= 1'b0;
                                    reg2_read_o <= 1'b1;
		  						    instvalid <= `InstValid;	
								end
								`EXE_MFHI: begin
									wreg_o		<=	`WriteEnable;
									aluop_o		<=	`EXE_MFHI_OP;
									alusel_o	<=	`EXE_RES_MOVE;
									reg1_read_o	<=	1'b0;
									reg2_read_o	<=	1'b0;
									instvalid	<=	`InstValid;
								end
								`EXE_MFLO: begin
									wreg_o		<=	`WriteEnable;
									aluop_o		<=	`EXE_MFLO_OP;
									alusel_o	<=	`EXE_RES_MOVE;
									reg1_read_o	<=	1'b0;
									reg2_read_o	<=	1'b0;
									instvalid	<=	`InstValid;
								end									  									
								`EXE_MTHI: begin
									wreg_o		<=	`WriteDisable;	//mthi/mtlo指令并不是要写入普通寄存器，所以这里为disable
									aluop_o		<=	`EXE_MTHI_OP;
									reg1_read_o	<=	1'b1;			//mthi/mtlo指令需要读取一个寄存器的值写入HI或LO
									reg2_read_o	<=	1'b0;
									instvalid	<=	`InstValid;
								end		
								`EXE_MTLO: begin
									wreg_o		<=	`WriteDisable;
									aluop_o		<=	`EXE_MTLO_OP;
									reg1_read_o	<=	1'b1;
									reg2_read_o	<=	1'b0;
									instvalid	<=	`InstValid;
								end									  									
								`EXE_MOVN: begin
									aluop_o		<=	`EXE_MOVN_OP;
									alusel_o	<=	`EXE_RES_MOVE;
									reg1_read_o	<=	1'b1;
									reg2_read_o	<=	1'b1;
									instvalid	<=	`InstValid;
									//reg2_o的值就是地址为rt的通用寄存器的值
									if (reg2_o!=`ZeroWord) begin
										wreg_o	<=	`WriteEnable;
									end else begin
										wreg_o	<=	`WriteDisable;
									end
								end	
								`EXE_MOVZ: begin
									aluop_o		<=	`EXE_MOVZ_OP;
									alusel_o	<=	`EXE_RES_MOVE;
									reg1_read_o	<=	1'b1;
									reg2_read_o	<=	1'b1;
									instvalid	<=	`InstValid;
									//reg2_o的值就是地址为rt的通用寄存器的值
									if (reg2_o==`ZeroWord) begin
										wreg_o	<=	`WriteEnable;
									end else begin
										wreg_o	<=	`WriteDisable;
									end
								end
						        default: begin
						        end
						    endcase   //case(op3)
						end
						default: begin
						end
					endcase	    //case(op2)
					end									  
		  	    `EXE_ORI:begin                        //ORI指令
		  		    wreg_o <= `WriteEnable;
                    aluop_o <= `EXE_OR_OP;
		  		    alusel_o <= `EXE_RES_LOGIC;
                    reg1_read_o <= 1'b1;
                    reg2_read_o <= 1'b0;	  	
					imm <= {16'h0, inst_i[15:0]};
                    wd_o <= inst_i[20:16];
					instvalid <= `InstValid;	
		  	    end
		  	    `EXE_ANDI:begin
		  		    wreg_o <= `WriteEnable;
                    aluop_o <= `EXE_AND_OP;
		  		    alusel_o <= `EXE_RES_LOGIC;
                    reg1_read_o <= 1'b1;
                    reg2_read_o <= 1'b0;	  	
					imm <= {16'h0, inst_i[15:0]};
                    wd_o <= inst_i[20:16];		  	
					instvalid <= `InstValid;	
				end	 	
		  	    `EXE_XORI:begin
		  		    wreg_o <= `WriteEnable;
                    aluop_o <= `EXE_XOR_OP;
		  		    alusel_o <= `EXE_RES_LOGIC;
                    reg1_read_o <= 1'b1;
                    reg2_read_o <= 1'b0;	  	
					imm <= {16'h0, inst_i[15:0]};
                    wd_o <= inst_i[20:16];		  	
					instvalid <= `InstValid;	
				end	 		
		  	    `EXE_LUI:begin
		  		    wreg_o <= `WriteEnable;
                    aluop_o <= `EXE_OR_OP;
		  		    alusel_o <= `EXE_RES_LOGIC;
                    reg1_read_o <= 1'b1;
                    reg2_read_o <= 1'b0;	  	
					imm <= {inst_i[15:0], 16'h0};
                    wd_o <= inst_i[20:16];		  	
					instvalid <= `InstValid;	
				end		
				`EXE_PREF:begin
		  		    wreg_o <= `WriteDisable;
                    aluop_o <= `EXE_NOP_OP;
		  		    alusel_o <= `EXE_RES_NOP; 
                    reg1_read_o <= 1'b0;
                    reg2_read_o <= 1'b0;	  	  	
					instvalid <= `InstValid;	
				end
		        default:begin
		        end
		    endcase		  //case op
		  
		    if (inst_i[31:21] == 11'b00000000000) begin
		  	    if (op3 == `EXE_SLL) begin
		  		    wreg_o <= `WriteEnable;
                    aluop_o <= `EXE_SLL_OP;
		  		    alusel_o <= `EXE_RES_SHIFT;
                    reg1_read_o <= 1'b0;
                    reg2_read_o <= 1'b1;	  	
					imm[4:0] <= inst_i[10:6];
                    wd_o <= inst_i[15:11];
					instvalid <= `InstValid;	
				end else if ( op3 == `EXE_SRL ) begin
		  		    wreg_o <= `WriteEnable;	
                    aluop_o <= `EXE_SRL_OP;
		  		    alusel_o <= `EXE_RES_SHIFT;
                    reg1_read_o <= 1'b0;
                    reg2_read_o <= 1'b1;	  	
					imm[4:0] <= inst_i[10:6];
                    wd_o <= inst_i[15:11];
					instvalid <= `InstValid;	
				end else if ( op3 == `EXE_SRA ) begin
		  		    wreg_o <= `WriteEnable;
                    aluop_o <= `EXE_SRA_OP;
		  		    alusel_o <= `EXE_RES_SHIFT;
                    reg1_read_o <= 1'b0;
                    reg2_read_o <= 1'b1;	  	
					imm[4:0] <= inst_i[10:6];
                    wd_o <= inst_i[15:11];
					instvalid <= `InstValid;	
				end
			end //endif		  
		  
		end       //else
	end         //always
	

	always @ (*) begin			//MUX
		if(rst == `RstEnable) begin
			reg1_o <= `ZeroWord;		
		end else if((reg1_read_o == 1'b1) && (ex_wreg_i == 1'b1) 
								&& (ex_wd_i == reg1_addr_o)) begin
			reg1_o <= ex_wdata_i; 
		end else if((reg1_read_o == 1'b1) && (mem_wreg_i == 1'b1) 
								&& (mem_wd_i == reg1_addr_o)) begin
			reg1_o <= mem_wdata_i; 			
	    end else if(reg1_read_o == 1'b1) begin
	  	    reg1_o <= reg1_data_i;
	    end else if(reg1_read_o == 1'b0) begin
	  	    reg1_o <= imm;
	    end else begin
	        reg1_o <= `ZeroWord;
	    end
	end
	
	always @ (*) begin			//MUX
		if(rst == `RstEnable) begin
			reg2_o <= `ZeroWord;
		end else if((reg2_read_o == 1'b1) && (ex_wreg_i == 1'b1) 
								&& (ex_wd_i == reg2_addr_o)) begin
			reg2_o <= ex_wdata_i; 
		end else if((reg2_read_o == 1'b1) && (mem_wreg_i == 1'b1) 
								&& (mem_wd_i == reg2_addr_o)) begin
			reg2_o <= mem_wdata_i;			
	    end else if(reg2_read_o == 1'b1) begin
	  	    reg2_o <= reg2_data_i;
	    end else if(reg2_read_o == 1'b0) begin
	  	    reg2_o <= imm;
	    end else begin
	        reg2_o <= `ZeroWord;
	    end
	end

endmodule