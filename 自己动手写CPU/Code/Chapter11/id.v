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

	input wire [`AluOpBus]		ex_aluop_i,		//当前处于执行阶段指令的运算子类型

	input wire	 				is_in_delayslot_i,	//当前位于译码阶段的指令是否位于延迟槽

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
    output reg              wreg_o,     //是否有要写入的目的寄存器

	output reg 				next_inst_in_delayslot_o,
	output reg 				branch_flag_o,
	output reg [`RegBus]	branch_target_address_o,
	output reg [`RegBus]	link_addr_o,			//返回地址
	output reg 				is_in_delayslot_o,		//当前位于译码阶段的指令是否位于延迟槽

	output wire [`RegBus] 	inst_o,		//位于译码阶段的指令

	output wire 			stallreq
);

  	wire[5:0] op = inst_i[31:26];
  	wire[4:0] op2 = inst_i[10:6];
  	wire[5:0] op3 = inst_i[5:0];
  	wire[4:0] op4 = inst_i[20:16];
  	reg[`RegBus]	imm;
  	reg 			instvalid;

	reg  stallreq_for_reg1_loadrelate;	//表示读取寄存器1是否与上一条指令存在load相关
	reg  stallreq_for_reg2_loadrelate;	//表示。。。。。2。。。。。。。。。。。。。。。
	wire pre_inst_is_load;				//上一条指令是否是加载指令

	assign stallreq = stallreq_for_reg1_loadrelate | stallreq_for_reg2_loadrelate;		//id阶段暂时都不用发出暂停请求，实现加载、存储指令的时候会用到

	wire [`RegBus]		pc_plus_8;
	wire [`RegBus]		pc_plus_4;

	wire [`RegBus]		imm_sll2_signedext;

	assign pc_plus_8 = pc_i + 8;
	assign pc_plus_4 = pc_i + 4;

	//imm_sll2_signedext对应分支指令众多的offset左移两位
	assign imm_sll2_signedext = {{14{inst_i[15]}}, inst_i[15:0], 2'b00};

	assign inst_o = inst_i;

	assign pre_inst_is_load =  ((ex_aluop_i == `EXE_LB_OP) || 
  								(ex_aluop_i == `EXE_LBU_OP)||
  								(ex_aluop_i == `EXE_LH_OP) ||
  								(ex_aluop_i == `EXE_LHU_OP)||
  								(ex_aluop_i == `EXE_LW_OP) ||
  								(ex_aluop_i == `EXE_LWR_OP)||
  								(ex_aluop_i == `EXE_LWL_OP)||
  								(ex_aluop_i == `EXE_LL_OP) ||
  								(ex_aluop_i == `EXE_SC_OP)) ? 1'b1 : 1'b0;

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
			reg1_addr_o <= inst_i[25:21];	//默认操作数1所在的寄存器地址
			reg2_addr_o <= inst_i[20:16];	//默认操作数2所在的寄存器地址
			imm <= `ZeroWord;
			link_addr_o	<=	`ZeroWord;
			branch_target_address_o	<=	`ZeroWord;
			branch_flag_o			<=	`NotBranch;
			next_inst_in_delayslot_o<=	`NotInDelaySlot;

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
								`EXE_SLT: begin		//有符号比较指令
									wreg_o <= `WriteEnable;		
									aluop_o <= `EXE_SLT_OP;
		  							alusel_o <= `EXE_RES_ARITHMETIC;		
								  	reg1_read_o <= 1'b1;	
									reg2_read_o <= 1'b1;
		  							instvalid <= `InstValid;	
								end
								`EXE_SLTU: begin	//无符号比较指令
									wreg_o <= `WriteEnable;		
									aluop_o <= `EXE_SLTU_OP;
		  							alusel_o <= `EXE_RES_ARITHMETIC;		
									reg1_read_o <= 1'b1;	
									reg2_read_o <= 1'b1;
		  							instvalid <= `InstValid;	
								end
								`EXE_ADD: begin
									wreg_o <= `WriteEnable;		
									aluop_o <= `EXE_ADD_OP;
		  							alusel_o <= `EXE_RES_ARITHMETIC;		
									reg1_read_o <= 1'b1;
									reg2_read_o <= 1'b1;
		  							instvalid <= `InstValid;	
								end
								`EXE_ADDU: begin
									wreg_o <= `WriteEnable;	
									aluop_o <= `EXE_ADDU_OP;
		  							alusel_o <= `EXE_RES_ARITHMETIC;
									reg1_read_o <= 1'b1;
									reg2_read_o <= 1'b1;
		  							instvalid <= `InstValid;	
								end
								`EXE_SUB: begin
									wreg_o <= `WriteEnable;		
									aluop_o <= `EXE_SUB_OP;
		  							alusel_o <= `EXE_RES_ARITHMETIC;
									reg1_read_o <= 1'b1;
									reg2_read_o <= 1'b1;
		  							instvalid <= `InstValid;	
								end
								`EXE_SUBU: begin
									wreg_o <= `WriteEnable;
									aluop_o <= `EXE_SUBU_OP;
		  							alusel_o <= `EXE_RES_ARITHMETIC;
									reg1_read_o <= 1'b1;
									reg2_read_o <= 1'b1;
		  							instvalid <= `InstValid;	
								end
								`EXE_MULT: begin
									wreg_o <= `WriteDisable;
									aluop_o <= `EXE_MULT_OP;
		  							reg1_read_o <= 1'b1;
									reg2_read_o <= 1'b1; 
									instvalid <= `InstValid;	
								end
								`EXE_MULTU: begin
									wreg_o <= `WriteDisable;		
									aluop_o <= `EXE_MULTU_OP;
		  							reg1_read_o <= 1'b1;
									reg2_read_o <= 1'b1;
									instvalid <= `InstValid;	
								end
								`EXE_DIV: begin
									wreg_o <= `WriteDisable;	//div指令并不写通用寄存器，写的是HILO	
									aluop_o <= `EXE_DIV_OP;
		  							reg1_read_o <= 1'b1;
									reg2_read_o <= 1'b1;
									instvalid <= `InstValid;
								end
								`EXE_DIVU: begin
									wreg_o <= `WriteDisable;		
									aluop_o <= `EXE_DIVU_OP;
		  							reg1_read_o <= 1'b1;
									reg2_read_o <= 1'b1;
									instvalid <= `InstValid;
								end
								`EXE_JR: begin
									wreg_o <= `WriteDisable;
									aluop_o <= `EXE_JR_OP;
		  							alusel_o <= `EXE_RES_JUMP_BRANCH;
									reg1_read_o <= 1'b1;
									reg2_read_o <= 1'b0;
		  							link_addr_o <= `ZeroWord;
			            			branch_target_address_o <= reg1_o;
			            			branch_flag_o <= `Branch;
			            			next_inst_in_delayslot_o <= `InDelaySlot;
			            			instvalid <= `InstValid;	
								end
								`EXE_JALR: begin
									wreg_o <= `WriteEnable;
									aluop_o <= `EXE_JALR_OP;
		  							alusel_o <= `EXE_RES_JUMP_BRANCH;   
								  	reg1_read_o <= 1'b1;
									reg2_read_o <= 1'b0;
		  							wd_o <= inst_i[15:11];
		  							link_addr_o <= pc_plus_8;
			            			branch_target_address_o <= reg1_o;
			            			branch_flag_o <= `Branch;
			            			next_inst_in_delayslot_o <= `InDelaySlot;
			            			instvalid <= `InstValid;	
								end
						        default: begin
						        end
						    endcase   //case(op3)
						end
						default: begin
						end
					endcase	    //case(op2)
				end			
				//以下是R型的SPECIAL2型
				`EXE_SPECIAL2_INST: begin
					case ( op3 )
						`EXE_CLZ: begin
							wreg_o <= `WriteEnable;	
							aluop_o <= `EXE_CLZ_OP;
		  					alusel_o <= `EXE_RES_ARITHMETIC; 
							reg1_read_o <= 1'b1;	
							reg2_read_o <= 1'b0;	  	
							instvalid <= `InstValid;	
						end
						`EXE_CLO: begin
							wreg_o <= `WriteEnable;	
							aluop_o <= `EXE_CLO_OP;
		  					alusel_o <= `EXE_RES_ARITHMETIC; 
							reg1_read_o <= 1'b1;
							reg2_read_o <= 1'b0;	  	
							instvalid <= `InstValid;	
						end
						`EXE_MUL: begin
							wreg_o <= `WriteEnable;	
							aluop_o <= `EXE_MUL_OP;
		  					alusel_o <= `EXE_RES_MUL; 
							reg1_read_o <= 1'b1;
							reg2_read_o <= 1'b1;	
		  					instvalid <= `InstValid;	  			
						end
						`EXE_MADD:	begin
							wreg_o		<=	`WriteDisable;	//以下四个指令都不写通用寄存器
							aluop_o		<=	`EXE_MADD_OP;
							alusel_o	<=	`EXE_RES_MUL;
							reg1_read_o	<=	1'b1;
							reg2_read_o	<=	1'b1;
							instvalid	<=	`InstValid;
						end
						`EXE_MADDU: begin
							wreg_o 		<= `WriteDisable;
							aluop_o 	<= `EXE_MADDU_OP;
		  					alusel_o	<= `EXE_RES_MUL; 
							reg1_read_o <= 1'b1;
							reg2_read_o <= 1'b1;	  			
		  					instvalid 	<= `InstValid;	
						end
						`EXE_MSUB: begin
							wreg_o		<= `WriteDisable;
							aluop_o		<= `EXE_MSUB_OP;
		  					alusel_o	<= `EXE_RES_MUL; 
							reg1_read_o	<= 1'b1;
							reg2_read_o <= 1'b1;	  			
		  					instvalid 	<= `InstValid;	
						end
						`EXE_MSUBU:		begin
							wreg_o 		<= `WriteDisable;
							aluop_o 	<= `EXE_MSUBU_OP;
		  					alusel_o 	<= `EXE_RES_MUL;
							reg1_read_o <= 1'b1;
							reg2_read_o <= 1'b1;	  			
		  					instvalid 	<= `InstValid;	
						end	
						default: begin
						end
					endcase	//special2 的 case(op3)
				end
				//以下是I型的指令
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
				`EXE_SLTI: begin
		  			wreg_o <= `WriteEnable;
					aluop_o <= `EXE_SLT_OP;
		  			alusel_o <= `EXE_RES_ARITHMETIC; 
					reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b0;	  	
					imm <= {{16{inst_i[15]}}, inst_i[15:0]};	//符号扩展
					wd_o <= inst_i[20:16];		  	
					instvalid <= `InstValid;	
				end
				`EXE_SLTIU: begin
		  			wreg_o <= `WriteEnable;
					aluop_o <= `EXE_SLTU_OP;
		  			alusel_o <= `EXE_RES_ARITHMETIC;
					reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b0;	  	
					imm <= {{16{inst_i[15]}}, inst_i[15:0]};	//符号扩展
					wd_o <= inst_i[20:16];		  	
					instvalid <= `InstValid;	
				end
				`EXE_ADDI: begin
		  			wreg_o <= `WriteEnable;
					aluop_o <= `EXE_ADDI_OP;
		  			alusel_o <= `EXE_RES_ARITHMETIC;
					reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b0;	  	
					imm <= {{16{inst_i[15]}}, inst_i[15:0]};
					wd_o <= inst_i[20:16];		  	
					instvalid <= `InstValid;	
				end
				`EXE_ADDIU:	begin
		  			wreg_o <= `WriteEnable;
					aluop_o <= `EXE_ADDIU_OP;
		  			alusel_o <= `EXE_RES_ARITHMETIC; 
					reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b0;	  	
					imm <= {{16{inst_i[15]}}, inst_i[15:0]};
					wd_o <= inst_i[20:16];		  	
					instvalid <= `InstValid;	
				end
				`EXE_J: begin
					wreg_o			<=	`WriteDisable;
					aluop_o			<=	`EXE_J_OP;
					alusel_o		<=	`EXE_RES_JUMP_BRANCH;
					reg1_read_o		<=	1'b0;
					reg2_read_o		<=	1'b0;
					link_addr_o		<=	`ZeroWord;
					branch_flag_o	<=	`Branch;
					next_inst_in_delayslot_o	<=	`InDelaySlot;
					instvalid		<=	`InstValid;
					branch_target_address_o	<=	{pc_plus_4[31:28], inst_i[25:0], 2'b00};
				end
				`EXE_JAL: begin
		  			wreg_o <= `WriteEnable;
					aluop_o <= `EXE_JAL_OP;
		  			alusel_o <= `EXE_RES_JUMP_BRANCH;
					reg1_read_o <= 1'b0;
					reg2_read_o <= 1'b0;
		  			wd_o <= 5'b11111;	
		  			link_addr_o <= pc_plus_8 ;
			    	branch_target_address_o <= {pc_plus_4[31:28], inst_i[25:0], 2'b00};
			    	branch_flag_o <= `Branch;
			    	next_inst_in_delayslot_o <= `InDelaySlot;		  	
			    	instvalid <= `InstValid;	
				end
				`EXE_BEQ: begin
		  			wreg_o <= `WriteDisable;
					aluop_o <= `EXE_BEQ_OP;
		  			alusel_o <= `EXE_RES_JUMP_BRANCH; 
					reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b1;
		  			instvalid <= `InstValid;	
		  			if(reg1_o == reg2_o) begin
			   		 	branch_target_address_o <= pc_plus_4 + imm_sll2_signedext;
			    		branch_flag_o <= `Branch;
			    		next_inst_in_delayslot_o <= `InDelaySlot;		  	
			    	end
				end
				`EXE_BGTZ: begin
		  			wreg_o <= `WriteDisable;
					aluop_o <= `EXE_BGTZ_OP;
		  			alusel_o <= `EXE_RES_JUMP_BRANCH; 
					reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b0;
		  			instvalid <= `InstValid;	
		  			if((reg1_o[31] == 1'b0) && (reg1_o != `ZeroWord)) begin
			    		branch_target_address_o <= pc_plus_4 + imm_sll2_signedext;
			    		branch_flag_o <= `Branch;
			    		next_inst_in_delayslot_o <= `InDelaySlot;		  	
			    	end
				end
				`EXE_BLEZ: begin
		  			wreg_o <= `WriteDisable;
					aluop_o <= `EXE_BLEZ_OP;
		  			alusel_o <= `EXE_RES_JUMP_BRANCH; 
					reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b0;
		  			instvalid <= `InstValid;	
		  			if((reg1_o[31] == 1'b1) || (reg1_o == `ZeroWord)) begin
			    		branch_target_address_o <= pc_plus_4 + imm_sll2_signedext;
			    		branch_flag_o <= `Branch;
			    		next_inst_in_delayslot_o <= `InDelaySlot;		  	
			    	end
				end
				`EXE_BNE: begin
		  			wreg_o <= `WriteDisable;
					aluop_o <= `EXE_BLEZ_OP;
		  			alusel_o <= `EXE_RES_JUMP_BRANCH; 
					reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b1;
		  			instvalid <= `InstValid;	
		  			if(reg1_o != reg2_o) begin
			   		 	branch_target_address_o <= pc_plus_4 + imm_sll2_signedext;
			   		 	branch_flag_o <= `Branch;
			   		 	next_inst_in_delayslot_o <= `InDelaySlot;		  	
			   		end
				end
				//以下是加载/存储指令
				`EXE_LB: begin
		  			wreg_o <= `WriteEnable;	
					aluop_o <= `EXE_LB_OP;
		  			alusel_o <= `EXE_RES_LOAD_STORE;
					reg1_read_o <= 1'b1;		//该寄存器的数据用于加载地址的计算，所以要读取
					reg2_read_o <= 1'b0;	  	
					wd_o <= inst_i[20:16];
					instvalid <= `InstValid;	
				end
				`EXE_LBU: begin
		  			wreg_o <= `WriteEnable;
					aluop_o <= `EXE_LBU_OP;
		  			alusel_o <= `EXE_RES_LOAD_STORE; 
					reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b0;	  	
					wd_o <= inst_i[20:16];
					instvalid <= `InstValid;	
				end
				`EXE_LH: begin
		  			wreg_o <= `WriteEnable;	
					aluop_o <= `EXE_LH_OP;
		  			alusel_o <= `EXE_RES_LOAD_STORE;
					reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b0;	  	
					wd_o <= inst_i[20:16]; 
					instvalid <= `InstValid;	
				end
				`EXE_LHU: begin
		  			wreg_o <= `WriteEnable;	
					aluop_o <= `EXE_LHU_OP;
		  			alusel_o <= `EXE_RES_LOAD_STORE; 
					reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b0;	  	
					wd_o <= inst_i[20:16];
					instvalid <= `InstValid;	
				end
				`EXE_LW: begin
		  			wreg_o <= `WriteEnable;	
					aluop_o <= `EXE_LW_OP;
		  			alusel_o <= `EXE_RES_LOAD_STORE; 
					reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b0;	  	
					wd_o <= inst_i[20:16];
					instvalid <= `InstValid;	
				end
				`EXE_LL: begin
		  			wreg_o <= `WriteEnable;	
					aluop_o <= `EXE_LL_OP;
		  			alusel_o <= `EXE_RES_LOAD_STORE;
					reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b0;	  	
					wd_o <= inst_i[20:16];
					instvalid <= `InstValid;	
				end
				`EXE_LWL: begin
		  			wreg_o <= `WriteEnable;	
					aluop_o <= `EXE_LWL_OP;
		  			alusel_o <= `EXE_RES_LOAD_STORE; 
					reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b1;	  	
					wd_o <= inst_i[20:16]; 
					instvalid <= `InstValid;	
				end
				`EXE_LWR: begin
		  			wreg_o <= `WriteEnable;	
					aluop_o <= `EXE_LWR_OP;
		  			alusel_o <= `EXE_RES_LOAD_STORE;
					reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b1;	  	
					wd_o <= inst_i[20:16]; 
					instvalid <= `InstValid;	
				end
				`EXE_SB: begin
		  			wreg_o <= `WriteDisable;
					aluop_o <= `EXE_SB_OP;
		  			reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b1;
					instvalid <= `InstValid;	
		  			alusel_o <= `EXE_RES_LOAD_STORE; 
				end
				`EXE_SH: begin
		  			wreg_o <= `WriteDisable;
					aluop_o <= `EXE_SH_OP;
		  			reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b1; 
					instvalid <= `InstValid;	
		  			alusel_o <= `EXE_RES_LOAD_STORE; 
				end
				`EXE_SW: begin
		  			wreg_o <= `WriteDisable;
					aluop_o <= `EXE_SW_OP;
		  			reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b1; 
					instvalid <= `InstValid;	
		  			alusel_o <= `EXE_RES_LOAD_STORE; 
				end
				`EXE_SWL: begin
		  			wreg_o <= `WriteDisable;
					aluop_o <= `EXE_SWL_OP;
		  			reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b1; 
					instvalid <= `InstValid;	
		  			alusel_o <= `EXE_RES_LOAD_STORE; 
				end
				`EXE_SWR: begin
		  			wreg_o <= `WriteDisable;
					aluop_o <= `EXE_SWR_OP;
		  			reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b1; 
					instvalid <= `InstValid;	
		  			alusel_o <= `EXE_RES_LOAD_STORE; 
				end
				`EXE_SC: begin
		  			wreg_o <= `WriteEnable;
					aluop_o <= `EXE_SC_OP;
		  			alusel_o <= `EXE_RES_LOAD_STORE; 
					reg1_read_o <= 1'b1;
					reg2_read_o <= 1'b1;	  	
					wd_o <= inst_i[20:16]; 
					instvalid <= `InstValid;	
					alusel_o <= `EXE_RES_LOAD_STORE; 
				end	

				`EXE_REGIMM_INST:begin
					case (op4)
						`EXE_BGEZ: begin
							wreg_o <= `WriteDisable;
							aluop_o <= `EXE_BGEZ_OP;
		  					alusel_o <= `EXE_RES_JUMP_BRANCH; 
							reg1_read_o <= 1'b1;
							reg2_read_o <= 1'b0;
		  					instvalid <= `InstValid;	
		  					if(reg1_o[31] == 1'b0) begin
			    				branch_target_address_o <= pc_plus_4 + imm_sll2_signedext;
			    				branch_flag_o <= `Branch;
			    				next_inst_in_delayslot_o <= `InDelaySlot;		  	
			   				end
						end
						`EXE_BGEZAL: begin
							wreg_o <= `WriteEnable;
							aluop_o <= `EXE_BGEZAL_OP;
		  					alusel_o <= `EXE_RES_JUMP_BRANCH;
							reg1_read_o <= 1'b1;
							reg2_read_o <= 1'b0;
		  					link_addr_o <= pc_plus_8; 
		  					wd_o <= 5'b11111;  
							instvalid <= `InstValid;
		  					if(reg1_o[31] == 1'b0) begin
			    				branch_target_address_o <= pc_plus_4 + imm_sll2_signedext;
			    				branch_flag_o <= `Branch;
			    				next_inst_in_delayslot_o <= `InDelaySlot;
			   				end
						end
						`EXE_BLTZ: begin
						  	wreg_o <= `WriteDisable;
							aluop_o <= `EXE_BGEZAL_OP;
		  					alusel_o <= `EXE_RES_JUMP_BRANCH;
							reg1_read_o <= 1'b1;
							reg2_read_o <= 1'b0;
		  					instvalid <= `InstValid;	
		  					if(reg1_o[31] == 1'b1) begin
			    				branch_target_address_o <= pc_plus_4 + imm_sll2_signedext;
			    				branch_flag_o <= `Branch;
			    				next_inst_in_delayslot_o <= `InDelaySlot;		  	
			   				end
						end
						`EXE_BLTZAL: begin
							wreg_o <= `WriteEnable;	
							aluop_o <= `EXE_BGEZAL_OP;
		  					alusel_o <= `EXE_RES_JUMP_BRANCH;
							reg1_read_o <= 1'b1;
							reg2_read_o <= 1'b0;
		  					link_addr_o <= pc_plus_8;	
		  					wd_o <= 5'b11111; instvalid <= `InstValid;
		  					if(reg1_o[31] == 1'b1) begin
			    				branch_target_address_o <= pc_plus_4 + imm_sll2_signedext;
			    				branch_flag_o <= `Branch;
			    				next_inst_in_delayslot_o <= `InDelaySlot;
			   				end
						end
						default:begin
						end
					endcase
				end		//end EXE_REGIMM_INST	
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
		  
		  	if((inst_i[31:21] == 11'b01000000000 && 
				inst_i[10:0] == 11'b00000000000)) begin
				aluop_o <= `EXE_MFC0_OP;
				alusel_o <= `EXE_RES_MOVE;
				wd_o <= inst_i[20:16];
				wreg_o <= `WriteEnable;
				instvalid <= `InstValid;	   
				reg1_read_o <= 1'b0;
				reg2_read_o <= 1'b0;		
			end else if((inst_i[31:21] == 11'b01000000100 && 
				inst_i[10:0] == 11'b00000000000)) begin
				aluop_o <= `EXE_MTC0_OP;
				alusel_o <= `EXE_RES_NOP;
				wreg_o <= `WriteDisable;
				instvalid <= `InstValid;	   
				reg1_read_o <= 1'b1;
				reg1_addr_o <= inst_i[20:16];
				reg2_read_o <= 1'b0;					
			end
		end       //else
	end         //always
	
	always @(*) begin
		if (rst == `RstEnable) begin
			is_in_delayslot_o	<=	`NotInDelaySlot;
		end else begin
			is_in_delayslot_o	<=	is_in_delayslot_i;	
		end
	end


	always @ (*) begin			//MUX
		stallreq_for_reg1_loadrelate	<=	`NoStop;
		if(rst == `RstEnable) begin
			reg1_o <= `ZeroWord;		
		end else if((pre_inst_is_load == 1'b1) && (ex_wd_i == reg1_addr_o)
								&& (reg1_read_o == 1'b1)) begin
			stallreq_for_reg1_loadrelate	<=	`Stop;
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
		stallreq_for_reg2_loadrelate	<=	`NoStop;
		if(rst == `RstEnable) begin
			reg2_o <= `ZeroWord;
		end else if((pre_inst_is_load == 1'b1) && (ex_wd_i == reg2_addr_o)
								&& (reg2_read_o == 1'b1)) begin
			stallreq_for_reg2_loadrelate	<=	`Stop;
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