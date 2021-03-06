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

    //HILO模块给出的HI、LO寄存器的值，这里是已经写入了的值
    input  wire [`RegBus]       hi_i,
    input  wire [`RegBus]       lo_i,

    //回写阶段的指令是否要写HI、LO，用于检测HI、LO寄存器带来的数据相关问题
    input  wire [`RegBus]       wb_hi_i,    //将要写入HI的值
    input  wire [`RegBus]       wb_lo_i,    //将要写入LO的值
    input  wire                 wb_whilo_i, //是否要写入HI、LO寄存器

    //访存阶段的指令是否要写HI、LO，具体类比上面的
    input  wire [`RegBus]       mem_hi_i,
    input  wire [`RegBus]       mem_lo_i,
    input  wire                 mem_whilo_i,

    //访存阶段指令是否要写cp0中的寄存器
    input  wire                 mem_cp0_reg_we,
    input  wire [4:0]           mem_cp0_reg_write_addr,
    input  wire [`RegBus]       mem_cp0_reg_data,

    //回写阶段。。。。。。。。。。。。。
    input  wire                 wb_cp0_reg_we,
    input  wire [4:0]           wb_cp0_reg_write_addr,
    input  wire [`RegBus]       wb_cp0_reg_data,
    

    input  wire [`DoubleRegBus] hilo_temp_i,    //第一个执行周期得到的乘法结果
    input  wire [1:0]           cnt_i,          //当前处于执行阶段的第几个时钟周期

    input  wire [`DoubleRegBus] div_result_i,
    input  wire                 div_ready_i,

    //处于执行阶段的转移指令要保存的返回地址
    input  wire [`RegBus]       link_address_i,
    //当前执行阶段的指令是否位于延迟槽
    input  wire                 is_in_delayslot_i,

    input  wire [`RegBus]       inst_i,

    input  wire [31:0]          excepttype_i,
    input  wire [`RegBus]       current_inst_address_i,

    //与cp0直接相连，用于读取当前cp0中寄存器的值
    input  wire [`RegBus]       cp0_reg_data_i,
    output reg [4:0]            cp0_reg_read_addr_o,

    //执行结果
    output reg [`RegAddrBus]    wd_o,
    output reg                  wreg_o,
    output reg [`RegBus]        wdata_o,

    //处于执行阶段的指令对HI、LO寄存器的写请求操作
    output reg [`RegBus]        hi_o,
    output reg [`RegBus]        lo_o,
    output reg                  whilo_o,        //是否要写的标志
    output reg [`DoubleRegBus]  hilo_temp_o,    //第一个执行周期得到的乘法结果
    output reg [1:0]            cnt_o,          //下一个时钟周期处于执行阶段的第几个时钟周期

    //新增的到除法模块的输出
    output reg [`RegBus]        div_opdata1_o,
    output reg [`RegBus]        div_opdata2_o,
    output reg                  div_start_o,
    output reg                  signed_div_o,

    //以下几个输出是为加载、存储指令准备的，且这三个输出都是wire型，说明它们随着输入的变化而立即变化，连续赋值
    output wire [`AluOpBus]     aluop_o,
    output wire [`RegBus]       mem_addr_o,
    output wire [`RegBus]       reg2_o,

    output reg                  cp0_reg_we_o,
    output reg [4:0]            cp0_reg_write_addr_o,
    output reg [`RegBus]        cp0_reg_data_o,    

    output wire [31:0]          excepttype_o,
    output wire                 is_in_delayslot_o,
    output wire [`RegBus]       current_inst_address_o,            

    output reg                  stallreq
);
    //保存逻辑运算的结果
    reg[`RegBus]    logicout;
    reg[`RegBus]    shiftres;   //保存移位运算结果
    reg[`RegBus]    moveres;    //移动操作的结果
    reg[`RegBus]    HI;         //保存HI寄存器的最新值
    reg[`RegBus]    LO;         //保存LO寄存器的最新值

    //新定义了一些变量
    reg [`RegBus]           arithmeticres;  //保存算术运算的结果
    reg [`DoubleRegBus]     mulres;     //保存乘法结果，宽度位64位
    wire                    ov_sum; //保存溢出情况
    wire                    reg1_eq_reg2;   //第一个操作数是否等于第二个操作数
    wire                    reg1_lt_reg2;   //第一个操作数是否小于第二个操作数
    wire [`RegBus]          reg2_i_mux;     //保存输入的第二个操作数reg2_i的补码
    wire [`RegBus]          reg1_i_not;     //..................reg1_i取反后的值
    wire [`RegBus]          result_sum;     //保存加法结果
    wire [`RegBus]          opdata1_mult;   //乘法操作中的被乘数
    wire [`RegBus]          opdata2_mult;   //乘法操作中的乘数
    wire [`DoubleRegBus]    hilo_temp;  //临时保存乘法结果，宽度为64位
    reg [`DoubleRegBus]     hilo_temp1;
    reg                     stallreq_for_madd_msub;
    reg                     stallreq_for_div;

    reg trapassert;     //自陷异常
    reg ovassert;       //溢出异常

    assign excepttype_o = {excepttype_i[31:12], ovassert, trapassert,
                            excepttype_i[9:8],8'h00};

    assign is_in_delayslot_o = is_in_delayslot_i;
    assign current_inst_address_o = current_inst_address_i;


    assign reg2_i_mux = ((aluop_i == `EXE_SUB_OP) ||
                         (aluop_i == `EXE_SUBU_OP)||
                         (aluop_i == `EXE_SLT_OP) ||
                         (aluop_i == `EXE_TLT_OP) ||
	                     (aluop_i == `EXE_TLTI_OP)|| 
                         (aluop_i == `EXE_TGE_OP) ||
	                     (aluop_i == `EXE_TGEI_OP)) ?
                         (~reg2_i)+1 : reg2_i;  //如果是减法或有符号比较运算，则存reg2的补码
                        //这里全部取反再加1的话就相当于是 得到了原来的数的相反数的补码，也就有了下面相减的结果
    assign result_sum = reg1_i + reg2_i_mux;    //如果reg2_i_mux是补码，那么result_sum就是reg1-reg2的结果了


    //判断是否有溢出
    assign ov_sum = ((!reg1_i[31] && !reg2_i_mux[31]) && result_sum[31])
                    || ((reg1_i[31] && reg2_i_mux[31]) && (!result_sum[31]));
    
    //判断操作数1是否小于操作数2
    assign reg1_lt_reg2 = ((aluop_i == `EXE_SLT_OP) || (aluop_i == `EXE_TLT_OP) ||
	                       (aluop_i == `EXE_TLTI_OP)|| (aluop_i == `EXE_TGE_OP) ||
	                       (aluop_i == `EXE_TGEI_OP)) ?
                          ((reg1_i[31] && !reg2_i[31]) ||   //1为负，2为正
                          (!reg1_i[31] && !reg2_i[31] && result_sum[31]) || //1，2都为正，数1减数2为负
                          (reg1_i[31] && reg2_i[31] && result_sum[31])) //1、2都为负，数1减数2为负
                          :(reg1_i < reg2_i);

    assign reg1_i_not = ~reg1_i;

    assign aluop_o  =   aluop_i;  //将传递给访存阶段
    assign mem_addr_o   =   reg1_i + {{16{inst_i[15]}}, inst_i[15:0]};  //计算后的要加载或存储的地址
    assign reg2_o   =   reg2_i;     //reg2_i是存储指令要存储的数据，或者lwl、lwr要加载到的目的寄存器的原始值

    //*************判断是否发生自陷异常*************
    always @ (*) begin
		if(rst == `RstEnable) begin
			trapassert <= `TrapNotAssert;
		end else begin
			trapassert <= `TrapNotAssert;
			case (aluop_i)
				`EXE_TEQ_OP, `EXE_TEQI_OP:	begin
					if( reg1_i == reg2_i ) begin
						trapassert <= `TrapAssert;
					end
				end
				`EXE_TGE_OP, `EXE_TGEI_OP, `EXE_TGEIU_OP, `EXE_TGEU_OP:	begin
					if( ~reg1_lt_reg2 ) begin
						trapassert <= `TrapAssert;
					end
				end
				`EXE_TLT_OP, `EXE_TLTI_OP, `EXE_TLTIU_OP, `EXE_TLTU_OP:	begin
					if( reg1_lt_reg2 ) begin
						trapassert <= `TrapAssert;
					end
				end
				`EXE_TNE_OP, `EXE_TNEI_OP:	begin
					if( reg1_i != reg2_i ) begin
						trapassert <= `TrapAssert;
					end
				end
				default: begin
					trapassert <= `TrapNotAssert;
				end
			endcase
		end
	end


    
    /**************第一段：得到最新的HI、LO的值，此处要解决数据相关的问题******************/
    always @(*) begin
        if (rst==`RstEnable) begin
            {HI, LO}    <=  {`ZeroWord,`ZeroWord};
        end else if(mem_whilo_i == `WriteEnable) begin
            {HI, LO}    <=  {mem_hi_i, mem_lo_i};       //以离得最近的一条指令要写入的数据为准，所以要把mem_whilo_i的判断放在wb的前面
        end else if(wb_whilo_i == `WriteEnable) begin
            {HI, LO}    <=  {wb_hi_i, wb_lo_i};
        end else begin
            {HI, LO}    <=  {hi_i, lo_i};
        end
    end

    /**************第二段：依据aluop_i指示的运算子类型进行运算,不包括MTHI和MTLO***************/
    always @(*) begin
        if (rst == `RstEnable) begin
            moveres <=  `ZeroWord;
        end else begin
            moveres <=  `ZeroWord;
            case (aluop_i)
                `EXE_MFHI_OP: begin //如果是mfhi指令，那么将HI的值作为移动操作的结果，下面的指令类比
                    moveres <=  HI;
                end 
                `EXE_MFLO_OP: begin
	   		        moveres <= LO;
	   	        end
	   	        `EXE_MOVZ_OP: begin
	   	        	moveres <= reg1_i;
	   	        end
	   	        `EXE_MOVN_OP: begin
	   	        	moveres <= reg1_i;
	   	        end
                `EXE_MFC0_OP: begin
	   	            cp0_reg_read_addr_o <= inst_i[15:11];
	   		        moveres <= cp0_reg_data_i;
	   		        if( mem_cp0_reg_we == `WriteEnable &&       //解决数据相关问题
	   		    		mem_cp0_reg_write_addr == inst_i[15:11] ) begin
	   				    moveres <= mem_cp0_reg_data;
	   		        end else if( wb_cp0_reg_we == `WriteEnable &&
	   				    wb_cp0_reg_write_addr == inst_i[15:11] ) begin
	   				    moveres <= wb_cp0_reg_data;
	   		        end
	   	        end
                default: begin
                end
            endcase
        end
    end

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

    //***********************算术运算操作*************************
    always @(*) begin
        if(rst == `RstEnable) begin
            arithmeticres   <=  `ZeroWord;
        end else begin
            case(aluop_i)
                `EXE_SLT_OP, `EXE_SLTU_OP: begin
                    arithmeticres   <=  reg1_lt_reg2;   //比较运算
                end
                `EXE_ADD_OP, `EXE_ADDU_OP, `EXE_ADDI_OP, `EXE_ADDIU_OP: begin
                    arithmeticres   <=  result_sum;     //加法运算
                end
                `EXE_SUB_OP, `EXE_SUBU_OP: begin
                    arithmeticres   <=  result_sum;     //减法运算
                end
                `EXE_CLZ_OP:begin   //计数运算clz
					arithmeticres <=reg1_i[31] ? 0 : reg1_i[30] ? 1 : reg1_i[29] ? 2 :
									reg1_i[28] ? 3 : reg1_i[27] ? 4 : reg1_i[26] ? 5 :
									reg1_i[25] ? 6 : reg1_i[24] ? 7 : reg1_i[23] ? 8 : 
									reg1_i[22] ? 9 : reg1_i[21] ? 10 : reg1_i[20] ? 11 :
									reg1_i[19] ? 12 : reg1_i[18] ? 13 : reg1_i[17] ? 14 : 
									reg1_i[16] ? 15 : reg1_i[15] ? 16 : reg1_i[14] ? 17 : 
									reg1_i[13] ? 18 : reg1_i[12] ? 19 : reg1_i[11] ? 20 :
									reg1_i[10] ? 21 : reg1_i[9] ? 22 : reg1_i[8] ? 23 : 
									reg1_i[7] ? 24 : reg1_i[6] ? 25 : reg1_i[5] ? 26 : 
									reg1_i[4] ? 27 : reg1_i[3] ? 28 : reg1_i[2] ? 29 : 
									reg1_i[1] ? 30 : reg1_i[0] ? 31 : 32 ;
				end
				`EXE_CLO_OP:begin   //计数运算clo
					arithmeticres <= (reg1_i_not[31] ? 0 : reg1_i_not[30] ? 1 : reg1_i_not[29] ? 2 :
									reg1_i_not[28] ? 3 : reg1_i_not[27] ? 4 : reg1_i_not[26] ? 5 :
									reg1_i_not[25] ? 6 : reg1_i_not[24] ? 7 : reg1_i_not[23] ? 8 : 
									reg1_i_not[22] ? 9 : reg1_i_not[21] ? 10 : reg1_i_not[20] ? 11 :
									reg1_i_not[19] ? 12 : reg1_i_not[18] ? 13 : reg1_i_not[17] ? 14 : 
									reg1_i_not[16] ? 15 : reg1_i_not[15] ? 16 : reg1_i_not[14] ? 17 : 
									reg1_i_not[13] ? 18 : reg1_i_not[12] ? 19 : reg1_i_not[11] ? 20 :
									reg1_i_not[10] ? 21 : reg1_i_not[9] ? 22 : reg1_i_not[8] ? 23 : 
									reg1_i_not[7] ? 24 : reg1_i_not[6] ? 25 : reg1_i_not[5] ? 26 : 
									reg1_i_not[4] ? 27 : reg1_i_not[3] ? 28 : reg1_i_not[2] ? 29 : 
									reg1_i_not[1] ? 30 : reg1_i_not[0] ? 31 : 32) ;
				end
				default:begin
					arithmeticres <= `ZeroWord;
				end
            endcase //aluop_i
        end //else
    end //always

    /*******************************乘法运算*****************************/
    //先把两个操作数都转成正数，之后再根据具体的指令判断是否有符号
    assign opdata1_mult = (((aluop_i == `EXE_MUL_OP)    ||
                            (aluop_i == `EXE_MULT_OP)   ||
                            (aluop_i == `EXE_MADD_OP)   ||
                            (aluop_i == `EXE_MSUB_OP))
                            &&(reg1_i[31] == 1'b1)) ? (~reg1_i+1):reg1_i;

    assign opdata2_mult = (((aluop_i == `EXE_MUL_OP)    || 
                            (aluop_i==`EXE_MULT_OP)     ||
                            (aluop_i == `EXE_MADD_OP)   ||
                            (aluop_i == `EXE_MSUB_OP))
                            &&(reg2_i[31] == 1'b1)) ? (~reg2_i+1):reg2_i;

    assign hilo_temp = opdata1_mult*opdata2_mult;   //得到临时的乘法结果

    //对乘法结果进行修正
    //如果是有符号乘法指令mult、mul，且源操作数一正一负，那么结果取补码，其他的均直接赋值
    always @(*) begin
        if(rst == `RstEnable) begin
            mulres  <=  {`ZeroWord, `ZeroWord};
        end else if((aluop_i == `EXE_MULT_OP)   ||
                    (aluop_i == `EXE_MUL_OP)    ||
                    (aluop_i == `EXE_MADD_OP)   ||
                    (aluop_i == `EXE_MSUB_OP)) begin
            if (reg1_i[31]^reg2_i[31] == 1'b1) begin
                mulres  <=  ~hilo_temp + 1;
            end else begin
                mulres  <=  hilo_temp;
            end
        end else begin
            mulres  <=  hilo_temp;
        end
    end

    //MADD、MADDU、MSUB、MSUBU指令
    always @(*) begin
        if (rst == `RstEnable) begin
            hilo_temp_o     <=  {`ZeroWord, `ZeroWord};
            cnt_o           <=  2'b00;
            stallreq_for_madd_msub  <=  `NoStop;
        end else begin
            case(aluop_i)
                `EXE_MADD_OP, `EXE_MADDU_OP: begin  
                    if (cnt_i == 2'b00) begin   //执行阶段第一个时钟周期
                        hilo_temp_o <=  mulres;
                        cnt_o       <=  2'b01;
                        hilo_temp1  <=  {`ZeroWord, `ZeroWord};
                        stallreq_for_madd_msub  <=  `Stop;
                    end else if (cnt_i == 2'b01) begin  //执行阶段第二个时钟周期
                        hilo_temp_o <=  {`ZeroWord, `ZeroWord};
                        cnt_o       <=  2'b10;
                        hilo_temp1  <=  hilo_temp_i + {HI, LO};
                        stallreq_for_madd_msub  <=  `NoStop;
                    end
                end
                `EXE_MSUB_OP, `EXE_MSUBU_OP: begin
					if(cnt_i == 2'b00) begin
						hilo_temp_o <=  ~mulres + 1 ;       //因为乘法结果是减数，所以要取补码
						cnt_o <= 2'b01;
						stallreq_for_madd_msub <= `Stop;
					end else if(cnt_i == 2'b01)begin
						hilo_temp_o <= {`ZeroWord,`ZeroWord};						
						cnt_o <= 2'b10;
						hilo_temp1 <= hilo_temp_i + {HI,LO};
						stallreq_for_madd_msub <= `NoStop;
					end	
				end
                default : begin
                    hilo_temp_o <= {`ZeroWord,`ZeroWord};
					cnt_o <= 2'b00;
					stallreq_for_madd_msub <= `NoStop;
                end
            endcase
        end
    end

    /**********************暂停流水线**********************/
    //目前只有madd,maddu,msub,msubu,div,divu指令会导致流水线暂停
    always @(*) begin
        stallreq = stallreq_for_madd_msub || stallreq_for_div;
    end

    /************************除法运算，输出给div模块的信息，以及获取div模块的结果*********************/
    always @(*) begin
        if (rst == `RstEnable) begin
            stallreq_for_div    <=  `NoStop;
            div_opdata1_o       <=  `ZeroWord;
            div_opdata2_o       <=  `ZeroWord;
            div_start_o         <=  `DivStop;
            signed_div_o        <=  1'b0;
        end else begin
            stallreq_for_div    <=  `NoStop;    //以下都是默认值
            div_opdata1_o       <=  `ZeroWord;
            div_opdata2_o       <=  `ZeroWord;
            div_start_o         <=  `DivStop;
            signed_div_o        <=  1'b0;
            case (aluop_i)
                `EXE_DIV_OP: begin
                    if (div_ready_i == `DivResultNotReady) begin
                        div_opdata1_o   <=  reg1_i;
                        div_opdata2_o   <=  reg2_i;
                        div_start_o     <=  `DivStart;
                        signed_div_o    <=  1'b1;
                        stallreq_for_div<=  `Stop;
                    end else if(div_ready_i == `DivResultReady) begin
                        div_opdata1_o   <=  reg1_i;
                        div_opdata2_o   <=  reg2_i;
                        div_start_o     <=  `DivStop;
                        signed_div_o    <=  1'b1;
                        stallreq_for_div<=  `NoStop;
                    end else begin
                        div_opdata1_o   <=  `ZeroWord;
                        div_opdata2_o   <=  `ZeroWord;
                        div_start_o     <=  `DivStop;
                        signed_div_o    <=  1'b0;
                        stallreq_for_div<=  `NoStop;
                    end
                end
                `EXE_DIVU_OP: begin
                    if (div_ready_i == `DivResultNotReady) begin
                        div_opdata1_o   <=  reg1_i;
                        div_opdata2_o   <=  reg2_i;
                        div_start_o     <=  `DivStart;
                        signed_div_o    <=  1'b0;
                        stallreq_for_div<=  `Stop;
                    end else if(div_ready_i == `DivResultReady) begin
                        div_opdata1_o   <=  reg1_i;
                        div_opdata2_o   <=  reg2_i;
                        div_start_o     <=  `DivStop;
                        signed_div_o    <=  1'b0;
                        stallreq_for_div<=  `NoStop;
                    end else begin
                        div_opdata1_o   <=  `ZeroWord;
                        div_opdata2_o   <=  `ZeroWord;
                        div_start_o     <=  `DivStop;
                        signed_div_o    <=  1'b0;
                        stallreq_for_div<=  `NoStop;
                    end
                end
                default: begin
                end
            endcase 
        end
    end



    //*****************第三段:依据alusel_i指示的运算类型，选择一个运算结果作为最终结果 *************/
    always @(*) begin
        wd_o    <=  wd_i;
        //是add、addi、sub、subi指令，且发生溢出，那么wreg_o就设置为WriteDisable
        if (((aluop_i == `EXE_ADD_OP) || (aluop_i == `EXE_ADDI_OP) ||
            (aluop_i == `EXE_SUB_OP)) && (ov_sum == 1'b1)) begin    //这里曾经有一个 括号位置引发的惨剧。。。注意&&的优先级比||高
            wreg_o  <=  `WriteDisable;
            ovassert <= 1'b1;
        end else begin
            wreg_o  <=  wreg_i;
            ovassert <= 1'b0;
        end

        case (alusel_i)
            `EXE_RES_LOGIC: begin
                wdata_o <=  logicout;   //选择逻辑运算结果为最终运算结果
            end 
            `EXE_RES_SHIFT: begin
                wdata_o <=  shiftres;   //选择移位运算结果为最终运算结果
            end
            `EXE_RES_MOVE: begin
                wdata_o <=  moveres;
            end
            `EXE_RES_ARITHMETIC: begin
                wdata_o <=  arithmeticres;
            end
            `EXE_RES_MUL: begin
                wdata_o <=  mulres[31:0];
            end
            `EXE_RES_JUMP_BRANCH: begin
                wdata_o <=  link_address_i;
            end
            default: begin
                wdata_o <=  `ZeroWord;
            end
        endcase
    end

    /*****************第四段:如果是MULT、MULTU、MTHI、MTLO指令，那么需要给出whilo_o,hi_o,lo_i的值**************/
    //如果是MTC0，则给出cp0相关的输出
    always @(*) begin
        if (rst==`RstEnable) begin
            whilo_o <=  `WriteDisable;
            hi_o    <=  `ZeroWord;
            lo_o    <=  `ZeroWord;
        end else if((aluop_i == `EXE_MSUB_OP)   ||
                    (aluop_i == `EXE_MSUBU_OP)) begin
            whilo_o <=  `WriteEnable;
            hi_o    <=  hilo_temp1[63:32];
            lo_o    <=  hilo_temp1[31:0];
        end else if((aluop_i == `EXE_MADD_OP)   ||
                    (aluop_i == `EXE_MADDU_OP)) begin
            whilo_o <=  `WriteEnable;
            hi_o    <=  hilo_temp1[63:32];
            lo_o    <=  hilo_temp1[31:0];
        end else if((aluop_i == `EXE_MULT_OP) ||        //在这里曾经有着 一个全角空格引发的惨剧。。。。
                    (aluop_i == `EXE_MULTU_OP)) begin
            whilo_o <=  `WriteEnable;
            hi_o    <=  mulres[63:32];
            lo_o    <=  mulres[31:0];
        end else if(aluop_i == `EXE_MTHI_OP) begin
            whilo_o <=  `WriteEnable;
            hi_o    <=  reg1_i;
            lo_o    <=  LO;     //写HI寄存器，所以LO不变
        end else if(aluop_i == `EXE_MTLO_OP) begin
            whilo_o <=  `WriteEnable;
            hi_o    <=  HI;
            lo_o    <=  reg1_i;
        end else if((aluop_i == `EXE_DIV_OP) || (aluop_i == `EXE_DIVU_OP)) begin
            whilo_o <=  `WriteEnable;
            hi_o    <=  div_result_i[63:32];    //高位是余数
            lo_o    <=  div_result_i[31:0];     //低位是商
        end else begin
            whilo_o <=  `WriteDisable;
            hi_o    <=  `ZeroWord;
            lo_o    <=  `ZeroWord;
        end
    end

    always @ (*) begin
		if(rst == `RstEnable) begin
			cp0_reg_write_addr_o <= 5'b00000;
			cp0_reg_we_o <= `WriteDisable;
			cp0_reg_data_o <= `ZeroWord;
		end else if(aluop_i == `EXE_MTC0_OP) begin
			cp0_reg_write_addr_o <= inst_i[15:11];
			cp0_reg_we_o <= `WriteEnable;
			cp0_reg_data_o <= reg1_i;
	    end else begin
			cp0_reg_write_addr_o <= 5'b00000;
			cp0_reg_we_o <= `WriteDisable;
			cp0_reg_data_o <= `ZeroWord;
		end				
	end	


endmodule // ex