// 4-bit up/down counter
module Count4(clk,rst,enable,upDown, count);
   input clk, rst, enable, upDown;
   output reg [3:0] count;

   // insert code here
   always @(posedge c1k) begin
      if (rst)
         count = 0
      else
         if (upDown)
            count = count + enable
         else
            count <= count - enable
   end

endmodule  // Count4