module adder_1_bit (
    input a, b, carry_in, 
    output logic sum, carry_out
);
    assign sum = a ^ b ^ carry_in;
    assign carry_out = (a & b) | (carry_in & (a ^ b));
endmodule

module adder_4_bit (
    input [3:0] a, b,
    input carry_in,
    output logic [3:0] sum,
    output logic carry_out
);
    logic [4:0] carry_holders;
    assign carry_holders[0] = carry_in;
    assign carry_out = carry_holders[4];

    genvar i;
    generate
        for (i = 0; i < 4; i += 1) begin : gen_fa
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
    input [15:0] a, b,
    input carry_in,
    output logic [15:0] sum,
    output logic carry_out
);
    logic [4:0] carry_holders;
    assign carry_holders[0] = carry_in;
    assign carry_out = carry_holders[4];

    genvar i;
    generate
        for (i = 0; i < 4; i += 1) begin : gen_fa4
            adder_4_bit u_fa4 (
                .a(a[4*i +: 4]),
                .b(b[4*i +: 4]),
                .carry_in(carry_holders[i]),
                .sum(sum[4*i +: 4]),
                .carry_out(carry_holders[i+1])
            );
        end
    endgenerate
endmodule


