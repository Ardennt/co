// 4-bit up/down counter
module Count4(clk,rst,enable,upDown, count);
   input clk, rst, enable, upDown;
   output reg [3:0] count;

// insert code here 
always @(posedge clk) begin
      if (rst) begin
         count = 0;
      end
      else begin
         if (enable) begin
            if (upDown) begin
               if (count == 15) begin
                  count = 0;
               end
               else begin
                  count += 1;
               end
            end
            else begin
               if (count == 0) begin
                  count = 15;
               end
               else begin
                  count -= 1;
               end
            end
         end
      end
   end

endmodule  // Count4
