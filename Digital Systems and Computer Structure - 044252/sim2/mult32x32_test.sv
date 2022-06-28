// 32X32 Multiplier test template
module mult32x32_test;

    logic clk;            // Clock
    logic reset;          // Reset
    logic start;          // Start signal
    logic [31:0] a;       // Input a
    logic [31:0] b;       // Input b
    logic busy;           // Multiplier busy indication
    logic [63:0] product; // Miltiplication product

// Put your code here
// ------------------
mult32x32 uut(.clk(clk), .reset(reset), .start(start), .busy(busy) ,.a(a), .b(b), .product(product) );


always begin
	#5 
	clk=~clk;
end


initial begin 
	start = 1'b0;
	reset = 1'b1; 
    clk = 1'b1;
	repeat (4) begin
	@(posedge clk);
	end 
	
    
    reset=1'b0;
    a=32'd316225523;
    b=32'd207477738;
    @(posedge clk);


    start=1'b1;
    @(posedge clk);

    start=1'b0;
    @(negedge busy);


end 


// End of your code

endmodule
