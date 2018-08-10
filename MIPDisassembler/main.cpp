/********************************************************************
MIPS Disassembler Project No 1
Author: Rattikarn Dudley
*********************************************************************
*********************************************************************/


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "disassembler.h"

int main()
{
	Disassembler result;
	std::ofstream outFile("hexOut.txt");

	//32 bits of data(instruction)
	unsigned int instruction[11] = { 0x032BA020, 0x8CE90014, 0x12A90003, 0x022DA822, 0xADB30020, 0x02697824,
		0xAE8FFFF4, 0x018C6020, 0x02A4A825, 0x158FFFF7, 0x8ECDFFF0 };
	//32 bit of memory adderss
	unsigned int  address[11] = {0x0009A040, 0x0009A044, 0x0009A048, 0x0009A04C, 
		0x0009A050, 0x0009A054, 0x0009A058, 0x0009A05C, 0x0009A060, 0x0009A064, 0x0009A068 };

	int choice = 0;

	while (choice != 9)
	{
		std::cout << std::endl;
		std::cout << "***************************************************************" << std::endl;
		std::cout << "                                                               " << std::endl;
		std::cout << "        A MIPS Disassembler Stimulation Program                " << std::endl;
		std::cout << "													             " << std::endl;
		std::cout << "                                                               " << std::endl;
		std::cout << "***************************************************************" << std::endl;
		std::cout << std::endl;
		std::cout << " Press 1 Display addresses input" << std::endl;
		std::cout << " Press 2 Excecute a program" << std::endl;
		std::cout << " Press 9 to exit a pregram " << std::endl << std::endl;

		std::cout << "Enter: ";  std::cin >> choice;

		switch (choice)
		{
		case 1:
			for (unsigned int i = 0; i < sizeof(instruction) / sizeof(instruction[0]); i++)
			{
				std::cout << "0x" << std::setfill('0') << std::setw(8) << std::hex << std::uppercase << instruction[i] << std::endl;
			}
			break;
		case 2:
			for (unsigned int i = 0; i < sizeof(instruction) / sizeof(instruction[0]); i++)
			{
				result.display(instruction[i], address[i], outFile);
			}
		}


	}
	outFile.close();

	return 0;
}
