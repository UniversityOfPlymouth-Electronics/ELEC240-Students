library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity MyClockDivider is
	generic
	(
		NSTATES	: integer  :=	10
	);


	port
	(
		-- Input ports
		CLK	: in  std_logic;

		-- Output ports
		Y	: out std_logic
	);
	
end MyClockDivider;



architecture v1 of MyClockDivider is

	-- Declarations (optional)
	signal op : std_logic := '0';

begin

	process(CLK)
	variable counter : integer := 0;
	begin
		if rising_edge(CLK) then
			counter := counter + 1;
			if counter = NSTATES then
				counter := 0;
				op <= not op;
			end if;
		end if;
	end process;
	
	Y <= op;
end v1;
