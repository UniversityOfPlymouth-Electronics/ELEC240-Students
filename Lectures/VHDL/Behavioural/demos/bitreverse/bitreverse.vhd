library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity bit_reverse is

	generic (Nbits	: integer  :=	4);

	port (
		-- Input ports
		A	: in  std_logic_vector(Nbits-1 downto 0);
		Y	: out std_logic_vector(Nbits-1 downto 0)
		);

end bit_reverse;

architecture v1 of bit_reverse is
begin

	process(A) is
		-- NO SIGNALS HERE!
		variable P : integer;
		variable Q : std_logic_vector((Nbits-1)downto 0);
	begin
		-- Sequential Statement(s)
		P := 0;
		Y <= Q;
		for n in (Nbits-1) downto 0 loop
			Q(n) := A(P);     -- integer used as an array index
			P    := P + 1;    -- integer can be used for arithmetic
		end loop;	
		--Y <= Q;
		
	end process;	

end v1;


