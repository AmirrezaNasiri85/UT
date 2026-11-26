module adder_1_bit (
    input  logic a, b, carry_in, 
    output logic sum, carry_out
);
    assign sum = a ^ b ^ carry_in;
    assign carry_out = (a & b) | (carry_in & (a ^ b));
endmodule

module adder_4_bit (
    input  logic [3:0] a, b,
    input  logic carry_in,
    output logic [3:0] sum,
    output logic carry_out
);
    logic [4:0] carry_holders;
    assign carry_holders[0] = carry_in;
    assign carry_out = carry_holders[4];

    genvar i;
    generate
        for (i = 0; i < 4; i = i + 1) begin : 
            adder_1_bit u_fa (
                .a(a[i]),
                .b(b[i]),
                .carry_in(carry_holders[i]),
                .sum(sum[i]),
                .carry_out(carry_holders[i+1])
            );
        end
    endgenerate
endmodule

module adder_16_bit (
    input  logic [15:0] a, b,
    input  logic carry_in,
    output logic [15:0] sum,
    output logic carry_out
);
    logic [4:0] carry_holders;
    assign carry_holders[0] = carry_in;
    assign carry_out = carry_holders[4];

    genvar i;
    generate
        for (i = 0; i < 4; i = i + 1) begin : 
            logic [3:0] a_slice;
            logic [3:0] b_slice;
            logic [3:0] sum_slice;

            assign a_slice = a[4*i + 3 : 4*i];
            assign b_slice = b[4*i + 3 : 4*i];
            assign sum[4*i + 3 : 4*i] = sum_slice;

            adder_4_bit u_fa4 (
                .a(a_slice),
                .b(b_slice),
                .carry_in(carry_holders[i]),
                .sum(sum_slice),
                .carry_out(carry_holders[i+1])
            );
        end
    endgenerate
endmodule
