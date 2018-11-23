-- SPI Slave (behavioural model) test bench 1
-- v1.0
-- Nicholas Outram (University of Plymouth)
--
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

--Entity object
entity spi_bhm_tb is
	generic ( N : natural := 8	);

end entity;

architecture v1 of spi_bhm_tb is

component spi_bhm	
	generic ( N : natural := 8	);

	port (
		sclk   : in std_logic;     --SPI Clock
		cs     : in std_logic;     --Chip select
		mosi   : in std_logic;	   --Master Out Slave In  (MOSI)
		miso   : out std_logic;	   --Master In  Slave Out (MISO)
	        reset  : in std_logic;     --Asynchronous Reset
		
		data_tx  : in  std_logic_vector(N-1 downto 0);	--Parallel N-bit data to return back to the master
		data_rx : out std_logic_vector(N-1 downto 0);   --Parallel N-bit data recevied from the master
		busyrx   : out std_logic;								--Do not read data_rx while high
		busytx   : out std_logic                        --Do not write data_tx while high
	);
end component;

signal sclk   :  std_logic;     
signal cs     :  std_logic;    
signal mosi   :  std_logic;	 
signal miso   :  std_logic;	
signal reset  :  std_logic;    
signal data_tx  :  std_logic_vector(N-1 downto 0);
signal data_rx  :  std_logic_vector(N-1 downto 0);
signal busyrx   :  std_logic;
signal busytx   :  std_logic;

--Data being returned back to the MCU
constant fpga_tx1 : std_logic_vector(N-1 downto 0) := "10011100";
constant fpga_tx2 : std_logic_vector(N-1 downto 0) := "11110000";

begin

-- ******************************************************
-- INSTANTIATE A COMPONENT FOR 8 BIT TRANSMIT AND RECEIVE
-- ******************************************************
u1 : spi_bhm 
	generic map ( N => 8)
	port map  (
		sclk => sclk, cs => cs, mosi => mosi, miso => miso,
		reset => reset, data_tx=>data_tx, data_rx=>data_rx, busyrx=>busyrx, busytx=>busytx
	);	

-- ************************
-- INITIALISATION AND CLOCK
-- ************************
ck:	process
		
	begin
		sclk  <= '0';
		cs    <= '1';
		reset <= '0';
		wait for 500 ns;
		reset <= '1';
		wait for 500 ns;
		cs <= '0';
		wait for 500 ns;
		for n in 1 to 8 loop
			sclk <= '1';
			wait for 500 ns;
			sclk <= '0';
			wait for 500 ns;
		end loop;
		cs <= '1';
		wait for 500 ns;
		wait;
	end process;	


-- ******************************************************************
-- TEST THE RECEIVE PROCESS - MCU SENDS AN 8-BIT VALUE; FPGA RECEIVES
-- ******************************************************************
rec:	process
		constant mcu_tx : std_logic_vector(N-1 downto 0) := "11011110";
	begin
		-- Simulate transmission of MCU SPI data and observe the read
		wait until cs = '0';
		wait for 20 ns;
		for n in N-1 downto 0 loop
			mosi <= mcu_tx(n);
			wait until falling_edge(sclk);
			if (n=1) then
				assert(busyrx='0') report "busyrx set prematurely" severity error;
				wait for 1 ps;
				assert(busyrx='1') report "busyrx not set" severity error;
			elsif (n=0) then
				assert(busyrx='1') report "busyrx not set" severity error; 
				wait for 1 ps;
				assert(busyrx='0') report "busyrx held on too long" severity error;
			end if;
		end loop;		
		assert(data_rx = mcu_tx)
			report "Incorrect data received"
			severity error;
		wait;
	end process;


-- ***************************************************************************
-- TEST THE TRANSMIT PROCESS - FPGA RETURNS AN 8-BIT VALUE IN FULL DUPLEX MODE
-- ***************************************************************************
transmit:
	process

	begin
		-- The first signal to return to the MCU is already presented before CS is pulled low
		wait until reset = '1';
		data_tx <= fpga_tx1;
		-- This is the FPGA lining up the next data to return
		wait until falling_edge(busytx);
		data_tx <= fpga_tx2;
		wait;
	end process;
checktx:
	process
		constant fpga_tx : std_logic_vector(N-1 downto 0) := "10011100";
	begin
		wait until reset = '1';
		--data_tx <= fpga_tx;
		wait until falling_edge(cs);
		assert(busytx='0') report "busytx set prematurely" severity error;
		wait for 1 ps;
		assert(busytx='1') report "busytx not set" severity error;

		for n in N-1 downto 0 loop
			wait until rising_edge(sclk);
			-- Check MISO
			assert(miso = fpga_tx1(n)) report "Incorrect bit returned on miso" severity error;
			-- Check the busy flag edges
			if n = 0 or n = (N-2) then
				assert(busytx='0') report "busytx incorrectly set" severity error;
				wait for 1 ps;
				assert(busytx='1') report "busytx incorrectly reset" severity error;
			elsif n = (N-1) then
				assert(busytx='1') report "busytx reset prematurely" severity error;
				wait for 1 ps;
				assert(busytx='0') report "busytx held on for too long" severity error;
			end if;
		end loop;
		wait;
	end process;



end v1;