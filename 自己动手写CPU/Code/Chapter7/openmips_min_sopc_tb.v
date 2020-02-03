//TestBench程序
`include "defines.v"
`timescale 1ns/1ps  //时间单位是1ns，精度是1ps

module openmips_min_sopc_tb();

    reg     CLOCK_50;
    reg     rst;
  
    //每隔10ns,CLOCK_50信号翻转一次，所以一个周期是20ns，对应50MHz
    initial begin
        CLOCK_50 = 1'b0;
        forever #10 CLOCK_50 = ~CLOCK_50;
    end
      
    initial begin
        rst = `RstEnable;
        #195 rst= `RstDisable;
        #4100 $stop;
    end
       
    openmips_min_sopc openmips_min_sopc0(
		    .clk(CLOCK_50),
		    .rst(rst)	
	  );

endmodule