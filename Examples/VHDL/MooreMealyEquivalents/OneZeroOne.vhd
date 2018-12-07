library ieee;
use ieee.std_logic_1164.all;

entity OneZeroOne is
	port(
		clk	 : in	std_logic;
		input	 : in	std_logic;
		reset	 : in	std_logic;
		output : out std_logic
	);
end entity;

-- ***************************************************************************************
-- ******************************** v1. MOORE MACHINE ************************************ 
-- ***************************************************************************************


architecture moore_type of OneZeroOne is

	-- Build an enumerated type for the state machine
	type state_type is (A, B, C, D);

	-- Register to hold the current state
	signal state   : state_type;

begin

moore_next_state:
	process (clk, reset)
	begin
		if reset = '0' then
			state <= A;
		elsif (rising_edge(clk)) then
			case state is
				when A=>
					if input = '1' then
						state <= B;
					else
						state <= A;
					end if;
				when B=>
					if input = '1' then
						state <= B;
					else
						state <= C;
					end if;
				
				when C=>
						if input = '1' then
							state <= D;
						else
							state <= A;
						end if;
				when D =>
						if input = '1' then
							state <= B;
						else
							state <= C;
						end if;
				end case;
		end if;
	end process;

moore_output:
	process (state)
	begin
		case state is
			when A =>
				output <= '0';
			when B =>
				output <= '0';
			when C =>
				output <= '0';
			when D =>
				output <= '1';
		end case;
	end process;
	
	
end moore_type;

-- ***************************************************************************************
-- ********************************* v2 MEALY MACHINE ************************************ 
-- ***************************************************************************************

architecture mealy_type of OneZeroOne is

	-- Build an enumerated type for the state machine
	type state_type is (A, B, C);

	-- Register to hold the current state
	signal state   : state_type;

begin

mealy_update:
	process (clk, reset)
	begin
		if reset = '0' then
			state <= A;
		elsif (rising_edge(clk)) then
			case state is
				when A=>
					if input = '1' then
						state <= B;
						output <= '0';
					else
						state <= A;
						output <= '0';
					end if;
				when B=>
					if input = '1' then
						state <= B;
						output <= '0';
					else
						state <= C;
						output <= '0';
					end if;
				when C=>
					if input = '1' then
						state <= B;
						output <= '1';				
					else
						state <= A;
						output <= '0';
					end if;
			end case;
		end if;
	end process;


end mealy_type;
