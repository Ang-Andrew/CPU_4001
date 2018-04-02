#include "CPU.h"
#include <iostream>

namespace CPU_4001{

	CPU::CPU(Memory* p_TheMemory)
		:
		c_BaseAddress(2),
		c_ReservedAddress(0),
		c_AddressCeiling(253),
		c_JumpToAddress(1),
		m_ProgramCounter(c_BaseAddress),
		m_Register0(0),
		m_Register1(0),
		m_OverflowError(false),
		m_UnderflowError(false),
		m_SignedMode(false),
		m_TheMemory(p_TheMemory),
		m_Halt(false)
	{
	}
	
	CPU::~CPU(){
		m_TheMemory = nullptr;
	}

	void CPU::Reset(){
		m_ProgramCounter = c_BaseAddress;
		m_OverflowError = false;
		m_UnderflowError = false;
		m_SignedMode = false;
		m_Halt = false;
		
	}
	
	void CPU::Run(){
		while(!m_Halt){
			m_TheMemory->Write(c_ReservedAddress,Fetch());
			Decode(m_TheMemory->Read(c_ReservedAddress));
			std::cout << int(m_ProgramCounter) << std::endl;

		}
	}

	const byte CPU::Fetch(){
		byte l_opCode = 0;
		l_opCode = m_TheMemory->Read(m_ProgramCounter);
		std::cout << int(m_ProgramCounter) << std::endl;
		++m_ProgramCounter;
		std::cout << int(m_ProgramCounter) << std::endl;
		if(m_ProgramCounter > c_AddressCeiling){
			Halt();
		}
		return l_opCode;
	}

	void CPU::Decode(const byte& p_OpCode){
		
		if(m_Halt) return;

		switch(p_OpCode){
			case 0: //halt command
				Halt();
				break;
			case 1: //load 0
				m_Register0 = m_TheMemory->Read(m_ProgramCounter);
				std::cout << int(m_ProgramCounter) << std::endl;
				++m_ProgramCounter; //skip past the data
				std::cout << int(m_ProgramCounter) << std::endl;
				break;
			case 2: //load 1
				m_Register1 = m_TheMemory->Read(m_ProgramCounter);
				std::cout << int(m_ProgramCounter) << std::endl;
				++m_ProgramCounter; //skip past the data
				std::cout << int(m_ProgramCounter) << std::endl;
				break;
			case 3: //load 2
				Add();
				break;
			case 4: //beep
				Beep();
				break;
			case 5: //store operation
				Store();
				break;
			case 6: //print operation
				Print();
				break;
			case 7:
				ClearRegister0();
				break;
			case 8:
				ClearRegister1();
				break;
			case 9:
				JumpTo();
				break;

		}
	}

	void CPU::Halt(){
		m_Halt = true;
	}

	void CPU::Add(){
		m_Register0 = m_Register0 + m_Register1;
	}

	void CPU::Beep(){
		std::cout << '\a';

	}

	void CPU::Store(){
		m_Register1 = m_TheMemory->Read(m_ProgramCounter);
		std::cout << int(m_ProgramCounter) << std::endl;
		++m_ProgramCounter;
		std::cout << int(m_ProgramCounter) << std::endl;
		m_TheMemory->Write(m_Register1,m_Register0);
	}
	
	void CPU::Print(){
		m_Register1 = m_TheMemory->Read(m_ProgramCounter);
		std::cout << int(m_ProgramCounter) << std::endl;
		++m_ProgramCounter;
		std::cout << int(m_ProgramCounter) << std::endl;
		m_Register0 = m_TheMemory->Read(m_Register1);
		std::cout << (int)m_Register0 << std::endl;
	}
	void CPU::ClearRegister0(){
		m_Register0 = 0;
		std::cout << "Cleared register 0" << std::endl;
	}
	void CPU::ClearRegister1(){
		m_Register1 = 0;
		std::cout << "Cleared register 1" << std::endl;
	}
	void CPU::JumpTo(){
		m_TheMemory->Write(c_JumpToAddress,m_TheMemory->Read(m_ProgramCounter));
		std::cout << int(m_ProgramCounter) << std::endl;
		++m_ProgramCounter;
		std::cout << int(m_ProgramCounter) << std::endl;
		m_ProgramCounter = m_TheMemory->Read(c_JumpToAddress);
	}

}
