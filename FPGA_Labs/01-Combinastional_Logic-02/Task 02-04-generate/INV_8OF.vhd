library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

Entity INV_8OF is

 port(  X: in  std_logic_vector(7 downto 0); 
		Y: out std_logic_vector(7 downto 0) );

End entity;

--data flow method
architecture myInvArray of INV_8OF is
	
	-- Component declarations
	component \NOT\ 
		port (IN1: in std_logic; \OUT\: out std_logic);
	end component;
			
begin

	g1: for b in 7 downto 0 generate
		u1: \NOT\ port map (X(b), Y(b));
	end generate; 

end architecture myInvArray;






