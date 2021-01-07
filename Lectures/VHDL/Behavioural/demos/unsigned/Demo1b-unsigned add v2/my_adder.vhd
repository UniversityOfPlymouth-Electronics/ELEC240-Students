library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity my_adder is

	generic (Nbits	: integer  :=	8);

	port (
		-- Input ports
		A	: in  std_logic_vector(Nbits-1 downto 0);
		B	: in  std_logic_vector(Nbits-1 downto 0);
		Y	: out std_logic_vector(Nbits downto 0)
		);

end my_adder;


architecture my_adder_v2 of my_adder is

	-- Declarations (optional)
	signal P : unsigned(Nbits downto 0);
	signal Q : unsigned(Nbits downto 0);

begin

	P <= '0' & unsigned(A);	--Pad an extra zero
	Q <= '0' & unsigned(B); --Pad an exter zero
	Y <= std_logic_vector(P + Q);

end my_adder_v2;

