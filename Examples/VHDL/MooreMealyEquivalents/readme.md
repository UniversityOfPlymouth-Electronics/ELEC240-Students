# Moore Mealy Equivalents

This is a simple state machine for bit pattern detection, where both Moore and Mealy implementations are compared and shown to be equivilent.

You can open the Quartus project in this folder. The top level entity implements a component `OneZeroOne` which is defined in the file [OneZeroOne.vhd](./OneZeroOne.vhd). This is a state machine written in VHDL that detects the sequence 1 - 0 - 1. 

The Moore machine state diagram is as follows:

![alt text](https://github.com/UniversityOfPlymouth-Electronics/ELEC240/blob/master/Examples/VHDL/MooreMealyEquivalents/img/fsm_moore.png "FSM for the Moore Machine")

This can be converted to a Mealy Machine. Furthermore, state minimisation can be performed (see lecture).

![alt text](https://github.com/UniversityOfPlymouth-Electronics/ELEC240/blob/master/Examples/VHDL/MooreMealyEquivalents/img/fsm_mealy.png "FSM for the Mealy Machine")

Look carefully at the [OneZeroOne.vhd](./OneZeroOne.vhd) file. You will there is a single entity, and two architectures. These architectures model the two finite state diagrams above.

A difficulty with Quartus schematics is that you place a component with the last defined architecture. Therefore, this example is best examined using ModelSim and a VHDL test bench.

* Ensure that ModelSim is configured correctly.
  * Tools->Options->EDA Tool Options
  
