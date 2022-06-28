// 32X32 Multiplier arithmetic unit template
module mult32x32_arith (
    input logic clk,             // Clock
    input logic reset,           // Reset
    input logic [31:0] a,        // Input a
    input logic [31:0] b,        // Input b
    input logic [1:0] a_sel,     // Select one byte from A
    input logic b_sel,           // Select one 2-byte word from B
    input logic [2:0] shift_sel, // Select output from shifters
    input logic upd_prod,        // Update the product register
    input logic clr_prod,        // Clear the product register
    output logic [63:0] product  // Miltiplication product
);

// Put your code here
// ------------------

logic [7:0] a_out;
logic [15:0] b_out;
logic [23:0] mult_16x8_out;
logic [63:0] shifter_to_adder;
logic [63:0] adder;


// mux A (select 8 bits of a input) mux 4->1
always_comb begin
    case (a_sel)
        2'b00: a_out = a[7:0]; 
        2'b01: a_out = a[15:8]; 
        2'b10: a_out = a[23:16];
        2'b11: a_out = a[31:24]; 
    endcase
end

// mux B (select 16 bits of a input) mux 2->1
always_comb begin
    case (b_sel)
        1'b0: b_out = b[15:0]; 
        1'b1: b_out = b[31:16]; 
    endcase
end


always_comb begin 
mult_16x8_out = a_out * b_out;
end

always_comb begin // Shifting the result
    shifter_to_adder = {64{1'b0}};
    case (shift_sel)
        3'b000:  shifter_to_adder = { {40{1'b0}} ,mult_16x8_out[23:0] }; // no shift
        3'b001:  shifter_to_adder = { {32{1'b0}} ,mult_16x8_out[23:0],{8{1'b0}} } ; // shift by 8
        3'b010:  shifter_to_adder = { {24{1'b0} } ,mult_16x8_out[23:0],{16{1'b0}} }; // shift by 16
        3'b011:  shifter_to_adder = { {16{1'b0}} ,mult_16x8_out[23:0],{24{1'b0}} } ; // shift by 24
        3'b100:  shifter_to_adder = { {8{1'b0}} , mult_16x8_out[23:0] , {32{1'b0}} } ; // shift by 32
        3'b101:  shifter_to_adder = { mult_16x8_out[23:0] ,{40{1'b0}} } ; // shift by 40
    endcase
    adder = product + shifter_to_adder;
end 


// add 
always_ff @(posedge clk, posedge reset) begin
    if (reset == 1'b1) begin
       product <= 64'b0;
    end
    else begin
        if(clr_prod == 1'b1) begin
            product <= 64'b0;
        end 
        else if(upd_prod == 1'b1) begin
            product <= adder;  
        end
    end
end


// End of your code

endmodule
