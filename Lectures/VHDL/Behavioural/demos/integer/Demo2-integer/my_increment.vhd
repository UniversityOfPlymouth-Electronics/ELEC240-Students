library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity my_increment is

	generic (Nbits	: integer  :=	8);

	port (
		-- Input ports
		A	: in  std_logic_vector(Nbits-1 downto 0);
		Y	: out std_logic_vector(Nbits downto 0));

end my_increment;


architecture my_increment_v1 of my_increment is

	-- Declarations (optional)
	signal P : integer;

begin

	P <= to_integer( unsigned(A)) + 1;
	Y <= std_logic_vector( to_unsigned(P,Nbits+1) );

end my_increment_v1;

