`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:53:41 04/03/2011 
// Design Name: 
// Module Name:    ac97audio 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module ac97audio (clock_100mhz, reset, volume,
                  audio_in_data, audio_out_data, ready,
	          audio_reset_b, ac97_sdata_out, ac97_sdata_in,
                  ac97_synch, ac97_bit_clock);

   input clock_100mhz;
   input reset;
   input [4:0] volume;
   output [7:0] audio_in_data;
   input [7:0] audio_out_data;
   output ready;

   //ac97 interface signals
   output audio_reset_b;
   output ac97_sdata_out;
   input ac97_sdata_in;
   output ac97_synch;
   input ac97_bit_clock;

   wire [2:0] source;
   assign source = 3'b000;	   //mic GS, will need to assign this to 

   wire [7:0] command_address;
   wire [15:0] command_data;
   wire command_valid;
   wire [19:0] left_in_data, right_in_data;
   wire [19:0] left_out_data, right_out_data;

   reg audio_reset_b;
   reg [9:0] reset_count;

   //wait a little before enabling the AC97 codec
   always @(posedge clock_100mhz) begin
      if (reset) begin
         audio_reset_b = 1'b0;
         reset_count = 0;
      end else if (reset_count == 1023)
        audio_reset_b = 1'b1;
      else
        reset_count = reset_count+1;
   end

   wire ac97_ready;
   
   // instantiate ac97 component
	ac97 ourac97 (
				.ready(ac97_ready),
				.command_address(command_address),
				.command_data(command_data),
				.command_valid(command_valid),
				.left_data(left_out_data),
				.left_valid(1'b1), //will always be valid GS
				.right_data(right_out_data),
				.right_valid(1'b1), //will always be valid GS
				.left_in_data(left_in_data),
				.right_in_data(right_in_data),
				.ac97_sdata_out(ac97_sdata_out),
				.ac97_sdata_in(ac97_sdata_in),
				.ac97_synch(ac97_synch),
				.ac97_bit_clock(ac97_bit_clock)
	);
	
	//loopback for testing, GS
	//assign left_out_data = {audio_in_data, 12'b000000000000};		
	
	
   // ready: one cycle pulse synchronous with clock_100mhz
   reg [2:0] ready_sync;
   always @ (posedge clock_100mhz) begin
     ready_sync <= {ready_sync[1:0], ac97_ready};
   end
   assign ready = ready_sync[1] & ~ready_sync[2];

   reg [7:0] out_data;
   always @ (posedge clock_100mhz)
     if (ready) out_data <= audio_out_data;
   assign audio_in_data = left_in_data[19:12];
   assign left_out_data = {out_data, 12'b000000000000};
   assign right_out_data = left_out_data;

   // generate repeating sequence of read/writes to AC97 registers
   // instantiate ac97commands component
	ac97commands ourac97commands( //GS instantiation
						.clock(clock_100mhz),
						.ready(ready),
						.command_address(command_address),
						.command_data(command_data),
						.command_valid(command_valid),
						.volume(volume), //change to 4'b1111 if need full volume GS
						.source(3'b000) //mic GS, I think
		
	);
	
endmodule
