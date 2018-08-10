/********************************************************************
MIPS Disassembler Project No 1
Author: Rattikarn Dudley
*********************************************************************
*********************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "disassembler.h"


Disassembler::Disassembler()
{
	SRCREG1;
	SRCREG2;
	SRCDESTREG3;
	OPCODE;
	FUNC;
	OFFSETS;
};

std::string Disassembler::operation(unsigned int ins)
{
	unsigned int val = opCode(ins);
	unsigned int funcNo = funcCode(ins);
	std::string tempOp = "";

	switch (val)
	{
	case 0: // R-Type
	{
		switch (funcNo)
		{
		case 0x20: tempOp = "add"; return tempOp; break;
		case 0x22: tempOp = "sub"; return tempOp; break;
		case 0x24: tempOp = "and"; return tempOp; break;
		case 0x25: tempOp = "or"; return tempOp; break;
		case 0x2A: tempOp = "slt"; return tempOp; break;
		}
	}
	if (val != 0) // I type
	{
	case 0x23: tempOp = "lw"; return tempOp; break;
	case 0x2B: tempOp = "sw"; return tempOp; break;
	case 0x04: tempOp = "beq"; return tempOp; break;
	case 0x05: tempOp = "bne"; return tempOp; break;
	}
	default:
		std::cout << " Not valid operation code" << std::endl;
		break;
	}

	return tempOp;
}

unsigned int Disassembler::opCode(unsigned int ins)
{
	//shift right to 26 bits 32 - 6 = 26 
	// 6 is the first 6 bits for opcode position in 32 bits 
	unsigned int val = (ins & OPCODE) >> 26;

	return val;

}

unsigned int Disassembler::rs(unsigned int ins)
{
	//shift right to 32 - 11 = 21 
	//opcode 6 bits + source1 5 bits = 11 
	unsigned int srcR1 = (ins & SRCREG1) >> 21;
	return srcR1;
}

unsigned int Disassembler::rt(unsigned int ins)
{
	//shift right to 32-16 = 16
	//opcode 6 bits + source1 5 bit + source2 5 bit = 16
	unsigned int srcR2 = (ins & SRCREG2) >> 16;
	return srcR2;
}

unsigned int Disassembler::rd(unsigned int ins)
{
	//shift right to 32-21 = 11
	//op 6 + sr1 5 + sr2 5 + dest 5 = 21
	unsigned int desR3 = (ins & SRCDESTREG3) >> 11;
	return desR3;
}
unsigned int Disassembler::funcCode(unsigned int ins)
{
	//no shift right is necessary
	//the last 6 bits funtion is the last bit in 32
	unsigned int func = (ins & FUNC);
	return func;
}

signed short int Disassembler::iOff(int ins)
{
	//singed short int for store negative integer 
	signed short int i = (ins & OFFSETS);
	return i;
}

unsigned int Disassembler:: pcAdress(unsigned int addre, short int imm)
{
	unsigned int pc = 0;
	//1. shift left offset for 2 positions
	//2. instruction + 4 bits or 1 byte 
	//3. add sum 1 and 2 
	pc = addre + 4 + (imm << 2);
	return pc;
}

void Disassembler:: display(int ins, int addr, std::ofstream& writeFile)
{
	unsigned int val = opCode(ins);
	unsigned int r1 = rs(ins);
	unsigned int r2 = rt(ins);
	unsigned int r3 = rd(ins);
	signed short int os = iOff(ins);
	unsigned int targetA = pcAdress(addr, os);

	// Type I 
	if (val != 0)
	{	//function lw and sw
		if (val == 0x23 || val == 0x2B)
		{
			std::cout << std::setfill('0') << std::setw(5) << std::hex << std::uppercase << addr
				<< std::setfill(' ') << std::setw(20)
				<< operation(ins) <<std::dec << "  $"  << r2 << ", " << std::dec << os << "($" << r1 << ")" << std::endl;
			writeFile << std::setfill('0') << std::setw(5) << std::hex << std::uppercase << addr
				<< std::setfill(' ') <<std::setw(20)
				<< operation(ins) << std::dec << "  $" << r2 << ", " << std::dec << os << "($" << r1 << ")" << std::endl;
		}
		// function beq and bne 
		else if (val == 0x04 || val == 0x05)
		{

			std::cout << std::setfill('0') << std::setw(5)<<std::hex << std::uppercase << addr
				<< std::setfill(' ') << std::setw(20)
				<< operation(ins) << std::dec << "  $" << r2 << ", $" << r1 << ", "
				<< "address " << std::setw(4) << std::hex << targetA << std::endl;

			writeFile << std::setfill('0') << std::setw(5) << std::hex << std::uppercase << addr
				<< std::setfill(' ') << std::setw(20)
				<< operation(ins) << std::dec << "  $" << r2 << ", $" << r1 << ", "
				<< "address "  << std::setw(4) << std::hex << targetA << std::endl;

		}
	}
	else // Type R which are add, sub, and , or , slt 
		// order ---> function, destination, source 1,source 2
	{
		std::cout <<std::setfill('0')<< std::setw(5) << std::hex << std::uppercase << addr
			<< std::setfill(' ') << std::setw(20)
			<< operation(ins) << std::dec << "  $" << r3 << ", $" << r1 << ", $" << r2
			<< std::endl;
		writeFile << std::setfill('0') << std::setw(5) << std::hex << std::uppercase << addr
			<< std::setfill(' ') << std::setw(20)
			<< operation(ins) << std::dec << "  $" << r3 << ", $" << r1 << ", $" << r2
			<< std::endl;
	}

}

