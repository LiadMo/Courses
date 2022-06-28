module HA (
    input  logic       a,
    input  logic       b,
    output logic      sum,
    output logic      carry
);

    xor(sum, a, b);
    and(carry, a, b);

endmodule
