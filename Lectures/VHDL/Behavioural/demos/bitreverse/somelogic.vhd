library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity somelogic is

	generic (Nbits	: integer  :=	4);

	port (
		-- Input ports
		A	: in  std_logic_vector(Nbits-1 downto 0);
		B	: in  std_logic_vector(Nbits-1 downto 0);
		Y	: out std_logic_vector(Nbits-1 downto 0)
		);

end entity;

architecture v1 of somelogic is
begin

	process(A,B) is
		-- NO SIGNALS HERE!
		variable Q : std_logic_vector((Nbits-1)downto 0);
	begin

		for n in (Nbits/2 - 1) downto 0 loop
			Q(n)         := ( A(n) and B(n+Nbits/2) );
			Q(n+Nbits/2) := ( A(n) or  B(n+Nbits/2) ); 
		end loop;	
		
		Y <= Q;
		
	end process;	

end v1;
