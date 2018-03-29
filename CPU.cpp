#include "CPU.h"
#include <iostream>

namespace CPU_4001{

	CPU::CPU(Memory* p_TheMemory)
		:
		c_BaseAddress(1),
		c_ReservedAddress(0),
		c_AddressCeiling(253),
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

		}
	}

	const byte CPU::Fetch(){
		byte l_opCode = 0;
		l_opCode = m_TheMemory->Read(m_ProgramCounter);
		++m_ProgramCounter;
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
				++m_ProgramCounter; //skip past the data
				break;
			case 2: //load 1
				m_Register1 = m_TheMemory->Read(m_ProgramCounter);
				++m_ProgramCounter; //skip past the data
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
		++m_ProgramCounter;
		m_TheMemory->Write(m_Register1,m_Register0);
	}
	
	void CPU::Print(){
		m_Register1 = m_TheMemory->Read(m_ProgramCounter);
		++m_ProgramCounter;
		m_Register0 = m_TheMemory->Read(m_Register1);
		std::cout << (int)m_Register0 << std::endl;
	}



}
