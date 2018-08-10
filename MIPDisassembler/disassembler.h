/********************************************************************
MIPS Disassembler Project No 1
Author: Rattikarn Dudley
*********************************************************************
*********************************************************************/

#ifndef Disassembler_H
#define Disassembler_H

class Disassembler
{
public:
	Disassembler();
	// a function to idetify opcode and return as a string
	std::string operation(unsigned int numIns);
	// a function to identify an opcode number
	unsigned int opCode(unsigned int numIns);
	// a function to identify register source 1
	unsigned int rs(unsigned int numIns);
	// a function to identify register source 2
	unsigned int rt(unsigned int numIns);
	// a function to identify register source 3
	unsigned int rd(unsigned int numIns);
	// a function to identify a function code
	unsigned int funcCode(unsigned int numIns);
	// a function to identify an offset 16 bits
	signed short int iOff(int numIns);
	// a function to display and write a file 
	void display(int num, int addr, std::ofstream& out);
	// a function to identify an pc relative address on a branch instruction
	unsigned int pcAdress(unsigned int num, short int immOff);

private:
	// bitwise source register number 1 
	const unsigned int SRCREG1 = 0x3E00000;
	// bitwise source register number 2 
	const unsigned int SRCREG2 = 0x01F0000;
	// bitwise destination register number 3 
	const unsigned int SRCDESTREG3 = 0x0000F800;
	// bitwise opcode 
	const unsigned int OPCODE = 0xFC000000;
	// bitwise for function 
	const unsigned int FUNC = 0x0000003F;
	// bitwise for imm offset 
	const unsigned int OFFSETS = 0x0000FFFF;
};

#endif