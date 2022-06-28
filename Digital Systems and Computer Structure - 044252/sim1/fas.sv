// Full Adder/Subtractor template
module fas (
    input logic a,           // Input bit a
    input logic b,           // Input bit b
    input logic cin,         // Carry in
    input logic a_ns,        // A_nS (add/not subtract) control
    output logic s,          // Output S
    output logic cout        // Carry out
);

    logic w0,w1,w2,w3,w4,w5,w6;
// Put your code here
// ------------------

XNOR2 #(
        .Tpdlh(7),
        .Tpdhl(7)
    ) xnor1 (
        .Z(w0),
        .A(b),
        .B(cin)
    );
    
XNOR2 #(
        .Tpdlh(7),
        .Tpdhl(7)
    ) xnorouts (
        .Z(s),
        .A(w0),
        .B(a)
    );
    
    NAND2 #(
        .Tpdlh(10),
        .Tpdhl(10)
    ) nand1 (
        .Z(w1),
        .A(cin),
        .B(b)
    );
      
    NAND2 #(
        .Tpdlh(10),
        .Tpdhl(10)
    ) nand2 (
        .Z(w2),
        .A(w1),
        .B(w1)
    );
    
XNOR2 #(
        .Tpdlh(7),
        .Tpdhl(7)
    ) xnor3 (
        .Z(w3),
        .A(a),
        .B(a_ns)
    );
    
      OR2 #(
        .Tpdlh(7),
        .Tpdhl(7)
    ) or1 (
        .Z(w4),
        .A(w2),
        .B(w3)
    );
    
       OR2 #(
        .Tpdlh(7),
        .Tpdhl(7)
    ) or2 (
        .Z(w5),
        .A(cin),
        .B(b)
    );
    
    NAND2 #(
        .Tpdlh(10),
        .Tpdhl(10)
    ) nand3 (
        .Z(w6),
        .A(w5),
        .B(w4)
    );
    
    NAND2 #(
        .Tpdlh(10),
        .Tpdhl(10)
    ) nand4 (
        .Z(cout),
        .A(w6),
        .B(w6)
    );
    
// End of your code

endmodule
