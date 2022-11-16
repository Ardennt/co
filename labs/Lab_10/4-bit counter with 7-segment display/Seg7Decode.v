module Seg7decode(         // convert to 7-segment display code
   input [3:0] bin,     
   output reg [6:0] seg7   // assumes common anode LEDs. Not actually registers. 
   );
   always @(bin)
   begin
      case(bin)
       //  bit order is segments ABCDEFG
       //////////// insert code here for input patterns 4'b001 through 4'b1111 
         
         // binary   // seg7
         
         // 0
         4'b0000:    seg7 = 7'b0000001;
         // 1
         4'b0001:    seg7 = 7'b1001111;
         // 2
         4'b0010:    seg7 = 7'b0010010;
         // 3
         4'b0011:    seg7 = 7'b0000110;
         // 4
         4'b0100:    seg7 = 7'b1001100;
         // 5
         4'b0101:    seg7 = 7'b0100100;
         // 6
         4'b0110:    seg7 = 7'b0100000;
         // 7
         4'b0111:    seg7 = 7'b0001111;
         // 8
         4'b1000:    seg7 = 7'b0000000;
         // 9
         4'b1001:    seg7 = 7'b0000100;
         // A
         4'b1010:    seg7 = 7'b0001000;
         // B
         4'b1011:    seg7 = 7'b1100000;
         // C
         4'b1100:    seg7 = 7'b0110001;
         // D
         4'b1101:    seg7 = 7'b1000010;
         // E
         4'b1110:    seg7 = 7'b0110000;
         // F
         4'b1111:    seg7 = 7'b0111000;
      endcase
   end
endmodule