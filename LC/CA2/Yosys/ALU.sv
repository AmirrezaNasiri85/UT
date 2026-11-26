`include "adder.sv"

module ALU (
    input  logic [15:0] M, N,
    input  logic carry_in,
    input  logic [2:0]  opcodes,
    output logic [15:0] W,
    output logic zer, neg, grt, ovf, carry_out 
);

    logic [15:0] adder_op_a;
    logic [15:0] adder_op_b;
    logic adder_cin;
    logic [15:0] adder_sum;
    logic adder_cout;

    adder_16_bit alu_adder (
        .a(adder_op_a),
        .b(adder_op_b),
        .carry_in(adder_cin),
        .sum(adder_sum),
        .carry_out(adder_cout)
    );

    always @(*) begin
        adder_op_a = 16'b0;
        adder_op_b = 16'b0;
        adder_cin  = 1'b0;
        W = 16'b0;
        carry_out  = 1'b0;

        case (opcodes)
            3'b000: begin
                adder_op_a = M;
                adder_op_b = N;
                adder_cin  = carry_in;
                W = adder_sum;
                carry_out  = adder_cout;
            end
            3'b001: begin
                W = M >> 2;
                carry_out  = 1'b0;
            end
            3'b010: begin
                adder_op_a = M;
                adder_op_b = 16'd0;
                adder_cin  = 1'b1;
                W = adder_sum;
                carry_out  = adder_cout;
            end
            3'b011: begin
                adder_op_a = M << 1;
                adder_op_b = M;
                adder_cin  = 1'b0;
                W = adder_sum;
                carry_out  = adder_cout;
            end
            3'b100: begin
                W = M & N;
                carry_out  = 1'b0;
            end
            3'b101: begin
                W = M | N;
                carry_out  = 1'b0;
            end
            3'b110: begin
                W = ~M;
                carry_out  = 1'b0;
            end
            3'b111: begin
                W = 16'b0;
                carry_out  = 1'b0;
            end
            default: begin
                W = 16'b0;
                carry_out  = 1'b0;
            end
        endcase

        zer = (W == 16'b0);
        neg = W[15];
        grt = (M > N);
        ovf = (opcodes[2] == 1'b0) ? ((adder_op_a[15] == adder_op_b[15]) && (W[15] != adder_op_a[15])) : 1'b0;
    end

endmodule
