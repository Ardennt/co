module Top(clk, rst, enable, upDown, count, seg7);
// count[3:0] output included for convenience in debug and testbenches
	input clk, rst, enable, upDown;
	output [3:0] count;
	output [6:0] seg7;
	
   wire clkCounter;  // divided clock for Counter module
	
	// Add code here to instantiate and connect the three modules together structurally
	ClkDiv upperlink (
		.clk(clk), // clk takes in an input
		.clkOut(clkCounter)
	);

	Count4 lowerlink (
		.clk(clkCounter),
		.rst(rst),
		.enable(enable),
		.upDown(upDown),
		.count(count)
	);

	Seg7decode out (
		.bin(count),
		.seg7(seg7)
	);

	
endmodule
