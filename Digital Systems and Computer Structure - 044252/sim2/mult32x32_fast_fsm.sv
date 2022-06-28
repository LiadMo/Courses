module mult32x32_fast_fsm (
    input logic clk,              
    input logic reset,            
    input logic start,            
    input logic a_msb_is_0,      
    input logic b_msw_is_0,       
    output logic busy,            
    output logic [1:0] a_sel,    
    output logic b_sel,           
    output logic [2:0] shift_sel, 
    output logic upd_prod,        
    output logic clr_prod         
);

// Put your code here
// ------------------

typedef enum {
    idle_st,
    ONE_TREE,
    ONE_FOUR,
    ONE_FIVE,
    ONE_SIX,
    TOW_TREE,
    TOW_FOUR,
    TOW_FIVE,
    TOW_SIX
  } sm_type;

sm_type current_state;
sm_type next_state;

always_ff @(posedge clk, posedge reset) begin
    if (reset == 1'b1) begin
        current_state <= idle_st;
    end
    else begin
        current_state <= next_state;
    end
end


always_comb begin
    a_sel = 2'd0;
    b_sel = 1'b0;
    shift_sel = 3'b000;
    upd_prod = 1'b0;
    clr_prod = 1'b0;
    busy = 1'b0;
    //next_state = current_state;

    case(current_state)
        idle_st: begin
            if(start == 1'b1) begin
                next_state = ONE_TREE;
                clr_prod = 1'b1;  
                end 
        end  

        ONE_TREE: begin
            busy = 1'b1;
            upd_prod = 1'b1;
            next_state = ONE_FOUR;
        end

        ONE_FOUR: begin
            a_sel = 2'b01;
            shift_sel = 3'b001;
            busy = 1'b1;
            upd_prod = 1'b1;
            next_state = ONE_FIVE;
        end

        ONE_FIVE: begin
			    if (a_msb_is_0 == 1'b1 && b_msw_is_0 == 1'b1) begin
					a_sel = 2'b10;
					b_sel = 1'b0;
					shift_sel = 3'b010;
                    upd_prod = 1'b1;
					next_state = idle_st;
                    busy = 1'b1;
			    end
			    else if (a_msb_is_0 == 1 && b_msw_is_0 == 0) begin
				    	a_sel = 2'b10;
					    b_sel = 1'b0;
					    shift_sel = 3'b010;
                        upd_prod = 1'b1;
					    next_state = TOW_TREE;
                        busy = 1'b1;
			    end
			    else begin
				      next_state = ONE_SIX;
				      a_sel = 2'b10;
				      shift_sel = 3'b010;
                      upd_prod = 1'b1;
                      busy = 1'b1;
			        end
        end

        ONE_SIX: begin
            a_sel = 2'b11;
            shift_sel = 3'b011;
            upd_prod = 1'b1;
            if(a_msb_is_0 == 0 && b_msw_is_0 == 1) begin
                next_state = idle_st;
                end
            else begin
            busy = 1'b1;
            next_state = TOW_TREE;
            end
        end

        TOW_TREE: begin
            b_sel = 1'b1;
            shift_sel = 3'b010;
            busy = 1'b1;
            upd_prod = 1'b1;
            next_state = TOW_FOUR;
        end

        TOW_FOUR: begin
            a_sel = 2'b01;
            b_sel = 1'b1;
            shift_sel = 3'b011;
            busy = 1'b1;
            upd_prod = 1'b1;
            next_state = TOW_FIVE;
        end
        
        TOW_FIVE: begin
            a_sel = 2'b10;
            b_sel = 1'b1;
            shift_sel = 3'b100;
            upd_prod = 1'b1;
            if(a_msb_is_0 == 1)begin
                next_state = idle_st;
                end
            else begin
                busy = 1'b1;
                next_state = TOW_SIX;
                end
        end

        TOW_SIX: begin
            a_sel = 2'b11;
            b_sel = 1'b1;
            shift_sel = 3'b101;
            // busy = 1'b1;
            upd_prod = 1'b1;
            next_state = idle_st;
        end
    endcase
end


// End of your code

endmodule