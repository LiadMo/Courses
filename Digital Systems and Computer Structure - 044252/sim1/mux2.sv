// 2->1 multiplexer template
module mux2 (
    input logic d0,          // Data input 0
    input logic d1,          // Data input 1
    input logic sel,         // Select input
    output logic z     // Output
  
    
);

    logic notsel, g2tog4, notg2tog4, g3tog5, g5tog6;
    
// Put your code here
// ------------------

  
    // Gate instantiations
    // For this gate we override the default delays with: Tpdlh=10 and Tpdhl=7
    NAND2 #(
        .Tpdlh(10),
        .Tpdhl(10)
    ) nand2_instg1 (
        .Z(notsel),
        .A(sel),
        .B(sel)
    );
    
     NAND2 #(
        .Tpdlh(10),
        .Tpdhl(10)
    ) nand2_instg2 (
        .Z(g2tog4),
        .A(notsel),
        .B(d0)
    );
    
     NAND2 #(
        .Tpdlh(10),
        .Tpdhl(10)
    ) nand2_instg4 (
        .Z(notg2tog4),
        .A(g2tog4),
        .B(g2tog4)
    );
    
  
    NAND2 #(
        .Tpdlh(10),
        .Tpdhl(10)
    ) nand2_instg3 (
        .Z(g3tog5),
        .A(sel),
        .B(d1)
    );
    
     NAND2 #(
        .Tpdlh(10),
        .Tpdhl(10)
    ) nand2_instg5 (
        .Z(g5tog6),
        .A(g3tog5),
        .B(g3tog5)
    );
    
      OR2 #(
        .Tpdlh(7),
        .Tpdhl(7)
    ) exit_or (
        .Z(z),
        .A(g5tog6),
        .B(notg2tog4)
    );
  
  
  
// End of your code

endmodule
