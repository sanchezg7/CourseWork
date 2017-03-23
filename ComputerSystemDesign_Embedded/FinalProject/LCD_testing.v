`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:51:48 04/19/2015 
// Design Name: 
// Module Name:    LCD_testing 
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
module LCD_testing( switches, leds, LCD_DATA, RS, RW, E, up, down, center, rs232_tx, rs232_rx, reset, clk );

	// Top-level Inputs and Outputs
	// These connect directly to FPGA pins via the pin map
	//
	// Control - clk, rst, etc
	input	reset;			// Remember: ACTIVE LOW!!!
	input	clk;			// 100 MHz
	
	// GPIO
	input	[7:0]	switches;
	output[7:0]	leds;
	output reg[3:0] LCD_DATA;
	output reg RS;
	output reg RW;
	output reg E;
	input up;
	input down;
	input center;
	
	//LCD buffers 
	reg [3:0] lcdreg;
	reg lcdRWreg; //RW_CONTROL
	reg lcdDrreg; //LCD ENABLE DRIVE
	
	
	// RS232 Lines
	input		rs232_rx;
	output	rs232_tx;
	
	// Wires and Register Declarations
	// PicoBlaze Data Lines
	wire	[7:0]	pb_port_id;
	wire	[7:0]	pb_out_port;
	reg	[7:0]	pb_in_port;
	wire			pb_read_strobe;
	wire			pb_write_strobe;
	
	// PicoBlaze CPU Control Wires
	wire			pb_reset;
	wire			pb_interrupt;
	wire			pb_int_ack;
	
	// UART wires
	wire			write_to_uart;
	wire			uart_buffer_full;
	wire			uart_data_present;
	reg			read_from_uart;
	wire			uart_reset;
	
	
	// UART Data Lines
	// TX does not need a wire, as it is fed directly by pb_out_port
	wire	[7:0]	uart_rx_data;
	
	// LED wires
	wire write_to_leds;
	wire led_reset;
	
	
	//assignment
	assign real_reset =  ~reset;
	wire write_enable;
	
	/*
	lcd_driver mylcddriver(
			.data_value(pb_out_port), //comes from pico
			.LCD_DATA(LCD_DATA),
			.enable(EN),
			.rw(RW),
			.rs(RS),
			.write_to_lcds(lcdwire),
			.clk(clk),
			.reset(~reset)
	);*/

/*
	// LED Driver and control logic
	//
	// LED driver expects ACTIVE-HIGH reset
	
	// LED driver instantiation
	*/
	led_driver_wrapper led_driver (
		.led_value(pb_out_port),
		.leds(leds),
		.write_to_leds(write_to_leds),
		.reset(real_reset),
		.clk(clk)
	);


	ac97audio audio(
				.clock_100mhz(clk),
				.reset(real_reset),
				.volume(),//will decide later
				.audio_in_data(mic),
				.audio_out_data(h_out),
				.ready(rdy),
				.audio_reset_b(rst),
				.ac97_sdata_out(sd_out),
				.ac97_sdata_in(sd_in),
				.ac97_synch(sync),
				.ac97_bit_clock(bit_clk)
	);

	
	// UART and control logic
	// UART expects ACTIVE-HIGH reset	
	// PicoBlaze and control logic
	//
	// PB expects ACTIVE-HIGH reset
	assign pb_reset = ~reset;
	// Disable interrupt by assigning 0 to interrupt
	assign pb_interrupt = 1'b0;
	// PB CPU instantiation
	//
	// Within the PicoBlaze Module (picoblaze.v), make sure you fill in the
	// appropriate sections.
	picoblaze CPU (
		.port_id(pb_port_id),
		.read_strobe(pb_read_strobe),
		.in_port(pb_in_port),
		.write_strobe(pb_write_strobe),
		.out_port(pb_out_port),
		.interrupt(pb_interrupt),
		.interrupt_ack(),
		.reset(pb_reset),
		.clk(clk)
	);	
/*
	// PB I/O selection/routing
	//
	// Handle PicoBlaze Output Port Logic
	// Output Ports:
	// * leds_out : port 01
	// * uart_data_tx : port 03
	//
	// These signals are effectively "write enable" lines for the UART and LED
	// Driver modules. They must be asserted when PB is outputting to the
	// corresponding port
	assign write_to_leds = pb_write_strobe & (pb_port_id == 8'h01);
	assign write_to_uart = pb_write_strobe & (pb_port_id == 8'h03);
	//
	// Handle PicoBlaze Input Port Logic
	// Input Ports:
	// * switches_in : port 00
	// * uart_data_rx : port 02
	// * uart_data_present : port 04 (1-bit, assigned to LSB)
	// * uart_buffer_full: port 05 (1-bit, assigned to LSB)
	//
	// This process block gets the value of the requested input port device
	// and passes it to PBs in_port. When PB is not requestng data from
	// a valid input port, set the input to static 0.
*/

	//assign write_to_leds = pb_write_strobe & (pb_port_id == 8'h01);
	//assign write_enable = pb_write_strobe & (pb_port_id == 8'h04);
	//assign write_reg_select = pb_write_strobe & (pb_port_id == 8'h05);
	//assign write_read_write = pb_write_strobe & (pb_port_id == 8'h06);
	
	always @(clk) begin 
		RW <= (lcdDrreg && lcdRWreg);
		if(~lcdRWreg && lcdDrreg) begin
			LCD_DATA = lcdreg;
		end else begin
			LCD_DATA = 4'bzzzz;
		end
	end
	
	always @(posedge clk) begin
		if(pb_write_strobe) begin 
			if(pb_port_id[6]) begin //writes to LCD if id is 0100_0000
				lcdreg <= pb_out_port[7:4];
				lcdDrreg <= pb_out_port[3];
				RS <= pb_out_port[2];
				lcdRWreg <= pb_out_port[1];
				E <= pb_out_port[0];
			end
			
			/*if(pb_port_id[7]) begin
				leds = pb_out_port;
			end
			*/
		end
	end
endmodule

module lcd_driver(data_value, LCD_DATA, write_to_lcds, enable, rw, rs, clk, reset );
	input [7:0] data_value;
	output reg [3:0] LCD_DATA;
	output reg enable;
	output reg rw;
	output reg rs;
	input write_to_lcds;
	input clk;
	input reset;
	
	always @(posedge clk or posedge reset) begin
		if(reset) begin 
			LCD_DATA <= 0;
			rs <= 0;
			rw <= 0;
			enable <= 0;
		end else if(write_to_lcds) begin
			LCD_DATA <= data_value[7:4];
			rs <= data_value[2];
			rw <= data_value[1];
			enable <= data_value[0];
		end
	end
endmodule

//led module for testing 
module led_driver_wrapper( led_value, leds, write_to_leds, clk, reset );
	input [7:0] led_value;
	output reg [7:0] leds;
	input write_to_leds;
	input clk;
	input reset;
	
	always @(posedge clk or posedge reset) begin
		if(reset) leds <= 0;
		else if(write_to_leds) leds <= led_value;
	end

endmodule


/********************************************************************************
/
/							ac97 audio module
/
/
/********************************************************************************/

module ac97audio (clk, reset, volume,
                  audio_in_data, audio_out_data, ready,
	          audio_reset_b, ac97_sdata_out, ac97_sdata_in,
                  ac97_synch, ac97_bit_clock);

   input clk;
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
   always @(posedge clk) begin
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
   always @ (posedge clk) begin
     ready_sync <= {ready_sync[1:0], ac97_ready};
   end
   assign ready = ready_sync[1] & ~ready_sync[2];

   reg [7:0] out_data;
   always @ (posedge clk)
     if (ready) out_data <= audio_out_data;
   assign audio_in_data = left_in_data[19:12];
   assign left_out_data = {out_data, 12'b000000000000};
   assign right_out_data = left_out_data;

   // generate repeating sequence of read/writes to AC97 registers
   // instantiate ac97commands component
	ac97commands ourac97commands( //GS instantiation
						.clock(clk),
						.ready(ready),
						.command_address(command_address),
						.command_data(command_data),
						.command_valid(command_valid),
						.volume(volume), //change to 4'b1111 if need full volume GS
						.source(3'b000) //mic GS, I think
		
	);
	
endmodule





/********************************************************************************
/
/							ac97 codec module
/
/
/********************************************************************************/
module ac97 (ready,
             command_address, command_data, command_valid,
             left_data, left_valid,
             right_data, right_valid,
             left_in_data, right_in_data,
             ac97_sdata_out, ac97_sdata_in, ac97_synch, ac97_bit_clock);

   output ready;
   input [7:0] command_address;
   input [15:0] command_data;
   input command_valid;
   input [19:0] left_data, right_data;
   input left_valid, right_valid;
   output [19:0] left_in_data, right_in_data;

   input ac97_sdata_in;
   input ac97_bit_clock;
   output ac97_sdata_out;
   output ac97_synch;

   reg ready;

   reg ac97_sdata_out;
   reg ac97_synch;

   reg [7:0] bit_count;

   reg [19:0] l_cmd_addr;
   reg [19:0] l_cmd_data;
   reg [19:0] l_left_data, l_right_data;
   reg l_cmd_v, l_left_v, l_right_v;
   reg [19:0] left_in_data, right_in_data;

   initial begin
      ready <= 1'b0;
      // synthesis attribute init of ready is "0";
      ac97_sdata_out <= 1'b0;
      // synthesis attribute init of ac97_sdata_out is "0";
      ac97_synch <= 1'b0;
      // synthesis attribute init of ac97_synch is "0";

      bit_count <= 8'h00;
      // synthesis attribute init of bit_count is "0000";
      l_cmd_v <= 1'b0;
      // synthesis attribute init of l_cmd_v is "0";
      l_left_v <= 1'b0;
      // synthesis attribute init of l_left_v is "0";
      l_right_v <= 1'b0;
      // synthesis attribute init of l_right_v is "0";

      left_in_data <= 20'h00000;
      // synthesis attribute init of left_in_data is "00000";
      right_in_data <= 20'h00000;
      // synthesis attribute init of right_in_data is "00000";
   end

   always @(posedge ac97_bit_clock) begin
      // Generate the sync signal 
		if(bit_count == 255) begin
			ac97_synch <= 1'b1;
		end
		if(bit_count == 15) begin
			ac97_synch <= 1'b1;
		end
	
      // Generate the ready signal
      if (bit_count == 255) // this 255 bit count is end of frame changed to 1 GS 
        ready <= 1'b1;
      if (bit_count == 2) //should go low after first bit position 
        ready <= 1'b0;

      // Latch user data at the end of each frame. This ensures that the
      // first frame after reset will be empty.
      if (bit_count == 255) //each frame has 256 bits GS
        begin
           l_cmd_addr <= {command_address, 12'h000};
           l_cmd_data <= {command_data, 4'h0};
           l_cmd_v <= command_valid;
           l_left_data <= left_data;
           l_left_v <= left_valid;
           l_right_data <= right_data;
           l_right_v <= right_valid;
        end

      if ((bit_count >= 0) && (bit_count <= 15))
        // Slot 0: Tags
        case (bit_count[3:0])
          4'h0: ac97_sdata_out <= 1'b1;      // Frame valid GS 4'h0
          4'h1: ac97_sdata_out <= l_cmd_v;   // Command address valid 4'h1
          4'h2: ac97_sdata_out <= l_cmd_v;   // Command data valid 4'h2
          4'h3: ac97_sdata_out <= l_left_v;  // Left data valid 4'h3
		  4'h4: ac97_sdata_out <= l_right_v; // Right data valid 4'h4
          default: ac97_sdata_out <= 1'b0;
        endcase

      else if ((bit_count >= 16) && (bit_count <= 35)) //slot 1 is 20 bits, bits 16 - 35 GS
        // Slot 1: Command address (8-bits, left justified)
        ac97_sdata_out <= l_cmd_v ? l_cmd_addr[35-bit_count] : 1'b0; //GS 35 minus bit_count

      else if ((bit_count >= 36) && (bit_count <= 55)) //20 bits for slot 2, bits 36 - 55 GS
        // Slot 2: Command data (16-bits, left justified)
        ac97_sdata_out <= l_cmd_v ? l_cmd_data[55-bit_count] : 1'b0; //GS 55 minus bit_count

      else if ((bit_count >= 56) && (bit_count <= 75)) //56 through 75 is 20 bits GS
        begin
           // Slot 3: Left channel
           ac97_sdata_out <= l_left_v ? l_left_data[19] : 1'b0;
           l_left_data <= { l_left_data[18:0], l_left_data[19] };
        end
      else if ((bit_count >= 76) && (bit_count <= 95))
        // Slot 4: Right channel
           ac97_sdata_out <= l_right_v ? l_right_data[95-bit_count] : 1'b0; //95 marks the end of this slot, 95 minus bit_count 
      else
        ac97_sdata_out <= 1'b0;

      bit_count <= bit_count+1;

   end // always @ (posedge ac97_bit_clock)

   always @(negedge ac97_bit_clock) begin
      if ((bit_count >= 57) && (bit_count <= 76)) //57 
        // Slot 3: Left channel
        left_in_data <= {left_in_data[18:0], ac97_sdata_in};
      else if ((bit_count >= 77) && (bit_count <= 96))
        // Slot 4: Right channel
        right_in_data <= {right_in_data[18:0], ac97_sdata_in}; //GS
   end

endmodule



/********************************************************************************
/
/							ac97 commands module
/
/
/********************************************************************************/

module ac97commands (clock, ready, command_address, command_data,
                     command_valid, volume, source);

   input clock;
   input ready;
   output [7:0] command_address;
   output [15:0] command_data;
   output command_valid;
   input [4:0] volume;
   input [2:0] source;

   reg [23:0] command;
   reg command_valid;

   reg [3:0] state;

   initial begin
      command <= 4'h0;
      // synthesis attribute init of command is "0";
      command_valid <= 1'b0;
      // synthesis attribute init of command_valid is "0";
      state <= 16'h0000;
      // synthesis attribute init of state is "0000";
   end

   assign command_address = command[23:16];
   assign command_data = command[15:0];

   wire [4:0] vol;
   assign vol = 31-volume;  // convert to attenuation

   always @(posedge clock) begin
      if (ready) state <= state+1;

      case (state)
        4'h0: // Read ID
          begin
             command <= 24'h80_0000;
             command_valid <= 1'b1;
          end
        4'h1: // Read ID
          command <= 24'h80_0000;
        4'h3: // headphone volume
          command <= { 8'h04, 3'b000, vol, 3'b000, vol }; //GS 1:00AM
        4'h5: // PCM volume
          command <= 24'h18_0808; //GS
        4'h6: // Record source select
          command <= { 8'h1A, 5'b00000, source, 5'b00000, source}; //GS 1:00AM
        4'h7: // Record gain = max
			 command <= 24'h1C_0F0F; //GS 1:00AM
        4'h9: // set +20db mic gain
          command <= 24'h0E_8048; //GS 1:00AM
        4'hA: // Set beep volume
          command <= 24'h0A_0000;
        4'hB: // PCM out bypass mix1
          command <= 24'h20_8000;
        default:
          command <= 24'h80_0000;
      endcase // case(state)
   end // always @ (posedge clock)
endmodule // ac97commands

