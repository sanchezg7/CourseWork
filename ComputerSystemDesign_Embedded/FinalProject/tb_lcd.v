`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   19:27:23 04/24/2015
// Design Name:   LCD_testing
// Module Name:   E:/Computer System Design Lab/Final Lab/Final-Project/FinalProject/tb_lcd.v
// Project Name:  FinalProject
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: LCD_testing
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module tb_lcd;

	// Inputs
	reg [7:0] switches;
	reg up;
	reg down;
	reg center;
	reg rs232_rx;
	reg reset;
	reg clk;

	// Outputs
	wire [7:0] leds;
	wire [3:0] LCD_DATA;
	wire RS;
	wire RW;
	wire E;
	wire rs232_tx;

	// Instantiate the Unit Under Test (UUT)
	LCD_testing uut (
		.switches(switches), 
		.leds(leds), 
		.LCD_DATA(LCD_DATA), 
		.RS(RS), 
		.RW(RW), 
		.E(E), 
		.up(up), 
		.down(down), 
		.center(center), 
		.rs232_tx(rs232_tx), 
		.rs232_rx(rs232_rx), 
		.reset(reset), 
		.clk(clk)
	);
	
	always begin
		#5;
		clk =0;
		#5;
		clk =1;
	end

	initial begin
		// Initialize Inputs
		switches = 0;
		up = 0;
		down = 0;
		center = 0;
		rs232_rx = 0;
		reset = 0;
		clk = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here

	end
      
endmodule

