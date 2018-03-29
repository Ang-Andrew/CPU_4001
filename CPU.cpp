#include "CPU.h"

namespace CPU_4001{

	CPU::CPU(Memory* p_TheMemory)
		:
		m_ProgramCounter(0),
		m_Register0(0),
		m_Register1(0),
		m_OverflowError(false),
		m_UnderflowError(false),
		m_SignedMode(false),
		m_TheMemory(p_TheMemory)
	{
	}
	
	CPU::~CPU(){
		m_TheMemory = nullptr;
	}

	void CPU::Reset(){
		m_ProgramCounter = 0;
		m_OverflowError = false;
		m_UnderflowError = false;
		m_SignedMode = false;
		
	}
	
	void CPU::Run(){
		
	}


}
