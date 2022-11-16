//  Two-way arbiter FSM/HLSM.  
//   Similar to the example in the HLSM chapter, but eliminates extra state ("Arbitrate") and uses meaningful signal names  
module Arbiter(
   input clk,rst,ra,rb, // ra = request from requestor a, rb = request from requestor b, which are level (not pulse) signals
   input [1:0] PA, PB,  // priority values for requestor a and requestor b, unsigned, higher number is higher priority
   output reg ga,gb     // ga = grant to a, gb = grant to b
);
   // insert code here
   localparam [1:0] WaitReq = 0, GrantA = 1, GrantB = 2;
   reg [1:0] FSMState;

   always @(posedge clk) begin
      if (rst == 1) begin
         FSMState = WaitReq;
         ga = 0;
         gb = 0;
      end

      else if (ra & !rb) begin
         FSMState = GrantA;
         ga = 1;
         gb = 0;
      end

      else if (!ra & rb) begin
         FSMState = GrantB;
         gb = 1;
         ga = 0;
      end

      else if (ra & rb) begin
         if (PB > PA) begin
            FSMState = GrantB;
            gb = 1;
            ga = 0;
         end
         else begin
            FSMState = GrantA;
            ga = 1;
            gb = 0;
         end
      end

      else begin
         ga = 0;
         gb = 0;
      end
   end
endmodule