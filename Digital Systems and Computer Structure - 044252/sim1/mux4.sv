// 4->1 multiplexer template
module mux4 (
    input logic d0,          // Data input 0
    input logic d1,          // Data input 1
    input logic d2,          // Data input 2
    input logic d3,          // Data input 3
    input logic [1:0] sel,   // Select input
    output logic z           // Output
);

// Put your code here
// ------------------


logic ONES_CARRY;
logic TENS_CARRY;

mux2 DIG_ONES (.d0(d0),.d1(d1),.sel(sel[0]),.z(ONES_CARRY));
mux2 DIG_TENS (.d0(d2),.d1(d3),.sel(sel[0]),.z(TENS_CARRY));
mux2 MUX (.d0(ONES_CARRY),.d1(TENS_CARRY),.sel(sel[1]),.z(z));

// End of your code

endmodule
