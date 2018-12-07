library ieee;
use ieee.std_logic_1164.all;

-- This is a VHDL testbench. The entity has no inputs or outputs and it is not intended to be synthesised. 
-- It is only to be run in simulation.
entity OneZeroOne_tb is
end entity;

architecture v1 of OneZeroOne_tb is
	--Internal signals that will be asserted and monitored during tests
	signal clk, ip, reset, y_moore, y_mealy : std_logic;	

begin
	-- **********************************************************************
	-- Instantiate components using structural VHDL
	-- This is equivalent to placing and connecting components in a schematic 
	-- **********************************************************************


	-- Instantiate a component with the Moore architecture
	moore:	entity work.OneZeroOne(moore_type) 
	-- Connect input/output ports to local signals
	port map(
		clk=>clk,
		input=>ip,
		reset=>reset,
		output=>y_moore
	);

	-- Instantiate a component with the Mealy architecture
	mealy:	entity work.OneZeroOne(mealy_type) 
	port map(
		clk=>clk,
		input=>ip,
		reset=>reset,
		output=>y_mealy
	);	

	-- *************************************************
	-- *************** Sequential blocks *************** 
	-- *************************************************

	-- ************
	-- Reset signal 
	-- ************
rst:
	process
	begin
		reset <= '0';
		wait for 50 ns;
		reset <= '1';
		wait for 50 ns;
		-- Always finished with a wait
		wait;
	end process;
	

	-- ************
	-- Clock signal 
	-- ************
clock:
	process
	begin
		clk <= '0';
		wait for 100 ns;
		for n in 1 to 10 loop
			clk <= '0';
			wait for 50 ns;
			clk <= '1';
			wait for 50 ns;
		end loop;
		wait;
	end process;
	
	-- ********************************************************************************************************
	--  Perform Tests - assert intput signal and check outputs
	--  Note how these use the clock to synchronise the changes the input signals and testing of output signals
	-- ********************************************************************************************************
test:
	process
		-- This is the sequence of bits to be applied to both devices
		constant testsig : std_logic_vector(9 downto 0) := "0110010100";
	begin
		-- Initial input is zero at start of simulation
		ip <= '0';
		for n in testsig'range loop
			wait until rising_edge(clk);
			-- Add a small time epoch to ensure outputs are updated
			wait for 1 ps;
			-- Check that the outputs of both architectures agree
			assert(y_moore=y_mealy)
				report "Moore and Mealy machines do not match"
				severity error;
			wait until falling_edge(clk);
			--Apply next test input value on the falling edge so that it is always stable before the rising
			ip <= testsig(n);
		end loop;
		wait;
	end process;
end v1;
