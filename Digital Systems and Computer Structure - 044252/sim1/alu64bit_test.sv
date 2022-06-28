// 64-bit ALU test bench template
module alu64bit_test;

// Put your code here
// ------------------
logic [63:0] a;
logic [63:0] b;
logic [63:0] s;
logic  cin;
logic cout;
logic [1:0] op; 

alu64bit alu64_inst(.a(a), .b(b), .cin(cin), .cout(cout), .op(op),  .s(s));
initial
	begin
		a = {64{1'b1}};
		b = {64{1'b1}};
		cin = 0'b0;
		op = 2'b11;
		
	
		#4000
		cin = 1;
		
		#4000
		cin = 0;
	end

// End of your code

endmodule
