// 5-stage MIPS pipelined datapath
module ALUcontrol();
    
endmodule

module MIPSALU (ALUct1, A, B, ALUOut, Zero);
    input [3:0] ALUct1;
    input [31:0] A,B;
    output reg [31:0] ALUOut;
    output Zero; 
    assign Zero = (ALUOut == 0); // Zero is true if ALUOut is 0; goes anywhere
    always @(ALUct1, A, B) begin// reevaluate if these change 
        case (ALUct1) 
            0: ALUOut <= A & B;
            1: ALUOut <= A | B;
            2: ALUOut <= A + B;
            6: ALUOut <= A - B;
            7: ALUOut <= A < B ? 1:0;
            12: ALUOut <= ~(A | B); // result is nor
            default: ALUOut <= 0; //default to 0, should not happen; 
        endcase
    end 
endmodule

// do this jose
module Mult4to1 (In1, In2, In3, In4, Sel, Out);
    input [31:0] In1, In2, In3, In4; // four 32-bit inputs
    input [1:0] Sel; // selector signal
    output reg [31:0] Out; // 32-bit output
    always @(In1, In2, In3, In4, Sel)
        case (Sel) //a 4->1 multiplexor
        0: Out <= In1;
        1: Out <= In2;
        2: Out <= In3;
        default: Out <= In4;
    endcase
endmodule

module Mult3to1 (In1, In2, In3, Sel, Out);
    input [31:0] In1, In2, In3; // four 32-bit inputs
    input [1:0] Sel; // selector signal
    output reg [31:0] Out; // 32-bit output
    always @(In1, In2, In3, Sel) begin
        case (Sel) //a 4->1 multiplexor
        0: Out <= In1;
        1: Out <= In2;
        default: Out <= In3;
     endcase
    end
endmodule

module ALUControl (ALUOp, IR[5:0], ALUCtl);
reg [3:0] dSig;
always @(*)
begin
	case(IR[5:0]) // R-type
		6'b100000 : dSig <= 4'b0010; // add
	 	default : dSig <= 4'b1111;
	endcase 
	case(ALUOp) // I-type
		6'b000000 : ALUCntl <= dSig; 
		6'b001000 : ALUCntl <= 4'b0010; // addi
		6'b001001 : ALUCntl <= 4'b0010; // addiu
		6'b001100 : ALUCntl <= 4'b0010; // andi
		6'b001101 : ALUCntl <= 4'b0001; // ori
		6'b100011 : ALUCntl <= 4'b0010; // lw
		6'b101011 : ALUCntl <= 4'b0010; // sw
		6'b000100 : ALUCntl <= 4'b0110; // beq
		6'b000101 : ALUCntl <= 4'b0111; // bne
		6'b001010 : ALUCntl <= 4'b1101; // slti
		6'b001011 : ALUCntl <= 4'b1110; // sltiu
	 	default : ALUCntl <= 4'b1111;
	endcase 
end
endmodule

module Datapath (ALUOp, RegDst, MemtoReg, MemRead, MemWrite, IorD, RegWrite, IRWrite,
                 PCWrite, PCWriteCond, ALUSrcA, ALUSrcB, PCSource, opcode, clock); // the control inputs + clock

   input [1:0]  ALUOp, ALUSrcB, PCSource;                   // 2-bit control signals
   input        RegDst, MemtoReg, MemRead, MemWrite, IorD,
                RegWrite, IRWrite, PCWrite, PCWriteCond,
                ALUSrcA, clock;                             // 1-bit control signals
   output [5:0] opcode;                                     // opcode is needed as an output by control
   reg [31:0]   PC, Memory [0:1023], MDR, IR, ALUOut;       // CPU state + some temporaries
   wire [31:0]  A, B, SignExtendOffset, PCOffset,
                ALUResultOut, PCValue, JumpAddr,
                Writedata, ALUAin, ALUBin, MemOut;          // these are signals derived from registers
   wire [3:0]   ALUCtl;                                     // the ALU control lines
   wire         Zero;                                       // the Zero out signal from the ALU
   wire[4:0]    Writereg;                                   // the signal used to communicate the destination register
 
   initial PC = 0; //start the PC at 0
 
   // Combinational signals used in the datapath
   // Read using word address with either ALUOut or PC as the address source
   assign MemOut = MemRead ? Memory[(IorD ? ALUOut : PC) >> 2]:0;
   assign opcode = IR[31:26];                             // opcode shortcut
 
   // Get the write register address from one of two fields depending on RegDst
   assign Writereg = RegDst ? IR[15:11] : IR[20:16];
 
   // Get the write register data either from the ALUOut or from the MDR
   assign Writedata = MemtoReg ? MDR : ALUOut;
 
   // Sign-extend the lower half of the IR from load/store/branch offsets
   assign SignExtendOffset = {{16{IR[15]}}, IR[15:0]};    // sign-extend lower 16 bits;
 
   // The branch offset is also shifted to make it a word offset
   assign PCOffset = SignExtendOffset << 2;
 
   // The A input to the ALU is either the rs register or the PC
   assign ALUAin = ALUSrcA ? A : PC;                      // ALU input is PC or A
 
   // Compose the Jump address
   assign JumpAddr = {PC[31:28], IR[25:0], 2'b00};        // The jump address
 
   // Creates an instance of the ALU control unit (see the module defined in
   // COD Figure B.5.16 (The MIPS ALU Control: a simple piece of combinational logic)
         // Input ALUOp is control-unit set and used to describe the instruction class
         // as in COD Chapter 4 (The Processor)
         // Input IR[5:0] is the function code field for an ALU instruction
         // Output ALUCtl are the actual ALU control bits as in Chapter 4
   ALUControl alucontroller (ALUOp, IR[5:0], ALUCtl); //ALU control unit
 
   // Creates a 3-to-1 multiplexor used to select the source of the next PC
         // Inputs are ALUResultOut (the incremented PC) , ALUOut (the branch address), the jump target address
         // PCSource is the selector input and PCValue is the multiplexor output
   Mult3to1 PCdatasrc (ALUResultOut, ALUOut, JumpAddr, PCSource, PCValue);
 
   // Creates a 4-to-1 multiplexor used to select the B input of the ALU
         // Inputs are register B,constant 4, sign-extended lower half of IR, sign-extended lower half of IR << 2
         // ALUSrcB is the selector input
         // ALUBin is the multiplexor output
   Mult4to1 ALUBinput (B, 32'd4, SignExtendOffset, PCOffset, ALUSrcB, ALUBin);
 
   // Creates a MIPS ALU
         // Inputs are ALUCtl (the ALU control), ALU value inputs (ALUAin, ALUBin)
         // Outputs are ALUResultOut (the 32-bit output) and Zero (zero detection output)
   MIPSALU ALU (ALUCtl, ALUAin, ALUBin, ALUResultOut, Zero); // the ALU
 
   // Creates a MIPS register file
         // Inputs are
         // the rs and rt fields of the IR used to specify which registers to read,
         // Writereg (the write register number), Writedata (the data to be written), RegWrite (indicates a write), the clock
         // Outputs are A and B, the registers read
   registerfile regs (IR[25:21], IR[20:16], Writereg, Writedata, RegWrite, A, B, clock); //Register file
 
   // The clock-triggered actions of the datapath
   always @(posedge clock) begin  
      if (MemWrite)
         Memory[ALUOut >> 2] <= B;        // Write memory--must be a store
 
      ALUOut <= ALUResultOut;             // Save the ALU result for use on a later clock cycle
 
      if (IRWrite)                   // Write the IR if an instruction fetch
         IR <= MemOut;
 
      MDR <= MemOut;                 // Always save the memory read value
 
      // The PC is written both conditionally (controlled by PCWrite) and unconditionally
      if (PCWrite || (PCWriteCond & Zero))
         PC <= PCValue;
   end
endmodule


// ===================================================
module testbench():
      /* Datapath (ALUOp, RegDst, MemtoReg, MemRead, MemWrite, IorD, RegWrite, IRWrite,
                 PCWrite, PCWriteCond, ALUSrcA, ALUSrcB, PCSource, opcode, clock); */

      //ALUOp = 10 for add
      
      Datapath random (
            10, /* ALUOp */
            0, /* RegDst */
            0, /* MemtoReg */
            0, /* MemRead */
            0, /* MemWrite */
            0, /* IorD */
            1, /* RegWrite */
            0, /* IRWrite */
            0, /* PCWrite */
            0, /* PCWriteCond */
            0, /* ALUSrcA */
            11, /* ALUSrcB */
            0, /* PCSource */
            000000, /* opcode */
            0 /* clock */
      
      )
      initial begin

      end
endmodule 

// add $s1,$s2,$s3
// add $s4,$s1,$s3
// j dest

/* RegDst, MemtoReg, MemRead, MemWrite, IorD,
                RegWrite, IRWrite, PCWrite, PCWriteCond,
                ALUSrcA, clock;  */

// ADD

//  ALUOp = 10
//  Funct = 100000
//  MemWrite = 0
//  MemRead = 0 
//  RegWrite = 1
//  MemtoReg = 0; 
//  RegDst = 1; 
//  clock = X; 
//  opcode = 000000

//  IRWrite = 0 
//  IorD = X
//  PCWrite = 0  
//  PCWriteCond = 
//  ALUSrcA = 0
//  ALUSrcB = 11
//  PCSource = X

