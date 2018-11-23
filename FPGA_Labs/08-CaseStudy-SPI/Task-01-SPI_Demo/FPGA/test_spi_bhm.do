quit -sim
vsim work.spi_bhm
add wave -position insertpoint  \
sim:/spi_bhm/sclk \
sim:/spi_bhm/cs \
sim:/spi_bhm/mosi \
sim:/spi_bhm/miso \
sim:/spi_bhm/reset \
sim:/spi_bhm/data_tx \
sim:/spi_bhm/data_rx \
sim:/spi_bhm/busyrx \
sim:/spi_bhm/busytx \
sim:/spi_bhm/sregin \
sim:/spi_bhm/sof \
sim:/spi_bhm/sregout

force -freeze sim:/spi_bhm/sclk 0 0
force -freeze sim:/spi_bhm/cs 1 0
force -freeze sim:/spi_bhm/mosi 0 0
force -freeze sim:/spi_bhm/reset 0 0
force -freeze sim:/spi_bhm/data_tx 10101111 0
run 40 ns
force -freeze sim:/spi_bhm/reset 1 0
run 40 ns
force -freeze sim:/spi_bhm/cs 0 0
run 40 ns
force -freeze sim:/spi_bhm/sclk 1 0, 0 {20000 ps} -r {40 ns} -can {640 ns}
run 150 ns
force -freeze sim:/spi_bhm/data_tx 10110010 0
run 150 ns
run 320 ns
noforce sim:/spi_bhm/sclk
force -freeze sim:/spi_bhm/sclk 0 0
run 20 ns
force -freeze sim:/spi_bhm/cs 1 0
run 20 ns