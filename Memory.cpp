#include "Memory.h"

namespace CPU_4001 {

	Memory::Memory()
		:
		c_MaxAddress(255),	// the max constant
		m_MemorySpace(new byte[c_MaxAddress]) //the memory
	{
		Clear(); //clears the memory
	}

	Memory::~Memory() {
		if (m_MemorySpace != nullptr) {
			delete[] m_MemorySpace;
			m_MemorySpace = nullptr;
		}
	}

	void Memory::Clear() {
		
		for (byte i = 0; i < c_MaxAddress; i++) {
			m_MemorySpace[i] = 0;
		}

	}

	const byte& Memory::Read(const byte& p_Address) {
		return m_MemorySpace[p_Address];
	}

	void Memory::Write(const byte& p_Address, const byte& p_Value){
		m_MemorySpace[p_Address] = p_Value;
	}
}