`include "ALU.sv"

`timescale 1ns/1ps

module ALU_test_bench;

    logic [15:0]M;
    logic [15:0]N;
    logic [2:0]opcodes;
    logic carry_in;

    logic [15:0]W;
    logic zer;
    logic neg;
    logic ovf;
    logic grt;
    logic carry_out;
    
    ALU simulation_ALU(
        .M(M),
        .N(N),
        .carry_in(carry_in),
        .opcodes(opcodes),
        .W(W),
        .zer(zer),
        .neg(neg),
        .ovf(ovf),
        .carry_out(carry_out),
        .grt(grt)
    );

    initial begin
        $display("Time | Opcode |      M |      N | Cin |      W | Z N G V Cout");
        $display("---------------------------------------------------------------");


        M = 16'h0000;
        N = 16'h0000;
        carry_in = 1'b0;
        opcodes  = 3'b000;
        #10;

        repeat (20) begin
            M = $random();            
            N = $random();
            carry_in = $random % 2;
            opcodes  = $random % 8;

            #10;
            $display("%4t |    %3b | %6d | %6d |   %1b | %6d | %1b %1b %1b %1b    %1b", 
                    $time, opcodes, M, N, carry_in, W, zer, neg, grt, ovf, carry_out);
        end

        #20;
        $display("Simulation Finished.");
        $finish;
    end

endmodule