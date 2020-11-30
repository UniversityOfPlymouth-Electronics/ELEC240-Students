library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- Declare entity - 2 inputs, 1 output
--
--    A1---|---------|
--         | LOGIC   |------Y
--    A2---|---------|

Entity AND_OR is

 port( A1, A2 : in std_logic; Y: out std_logic);

End entity;

-- structural style
architecture myLogic of AND_OR is
	
	-- Component declarations (of existing component we're going to use in our design)
	component \NOT\			-- The backslash is needed in Quartus. Books often show this as just not 
		port (IN1: in std_logic; \OUT\: out std_logic);
	end component;
	
	component AND2
		port (IN1, IN2: in std_logic; \OUT\ : out std_logic);
	end component;

	component OR2
		port (IN1, IN2: in std_logic; \OUT\: out std_logic);
	end component;

	-- Signals (nodes in the circuit)
	signal I1, I2, S1, S2 : std_logic;
		
begin

	U1: \NOT\ port map (A1, I1);	-- inverter
	U2: \NOT\ port map (A2, I2);  -- inverter
	U3: AND2 port map (A1, I2, S1); -- connects to an internal signal S1
	U4: AND2 port map (I1, A2, S2); -- connects to an internal signal S2
	U5: OR2 port map (S1, S2, Y); -- connect internal signals S1 and S2 to the output Y

end architecture myLogic;


--architecture myLogic_v2 of AND_OR is
--
--begin
--	Y <= A1 xor A2;
--end architecture myLogic_v2;



