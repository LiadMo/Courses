// 1-bit ALU template
module alu1bit (
    input logic a,           // Input bit a
    input logic b,           // Input bit b
    input logic cin,         // Carry in
    input logic [1:0] op,    // Operation
    output logic s,          // Output S
    output logic cout        // Carry out
);

// Put your code here
// ------------------

    logic w0,w1,w2,w3,w4,w5;
// Put your code here
// ------------------

OR2 #(
        .Tpdlh(7),
        .Tpdhl(7)
    ) or1 (
        .Z(w0),
        .A(b),
        .B(a)
    );
    
     NAND2 #(
        .Tpdlh(10),
        .Tpdhl(10)
    ) nand1 (
        .Z(w1),
        .A(w0),
        .B(w0)
    );
    
    
XNOR2 #(
        .Tpdlh(7),
        .Tpdhl(7)
    ) xnor1 (
        .Z(w2),
        .A(b),
        .B(a)
    );
    
    NAND2 #(
        .Tpdlh(10),
        .Tpdhl(10)
    ) nand2 (
        .Z(w3),
        .A(w2),
        .B(w2)
    );
      
    NAND2 #(
        .Tpdlh(10),
        .Tpdhl(10)
    ) nand3 (
        .Z(w5),
        .A(op[0]),
        .B(op[0])
    );
    
    	fas fasfas(
		.a(a),
		.b(b),
		.cin(cin),
		.a_ns(w5),
		.cout(cout),
		.s(w4)
	);
 
 
	mux4 finmux(
		.d0(w1),
		.d1(w3),
		.d2(w4),
		.d3(w4),
		.sel(op),
		.z(s)
	);

// End of your code

endmodule
