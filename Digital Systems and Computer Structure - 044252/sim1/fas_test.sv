// Full Adder/Subtractor test bench template
module fas_test;

// Put your code here
// ------------------
logic a;
logic b;
logic cin;
logic a_ns;
logic cout;
logic s;
fas fas_inst(.a(a) , .b(b) , .cin(cin), .a_ns(a_ns) , .cout(cout), .s(s) );
initial
	begin
		a = 0;
		b = 0;
		cin = 0;
		a_ns = 0;
		
	
		#100;
		a = 1;
		b = 0;
		cin = 0;
		a_ns = 0;
		
		#100;
		a = 0;
		b = 0;
		cin = 0;
		a_ns = 0;
	end

// End of your code

endmodule
