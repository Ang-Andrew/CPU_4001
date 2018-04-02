#ifndef CPU_PROCESSOR
#define CPU_PROCESSOR

#include "Memory.h"

namespace CPU_4001{
	
	class CPU{
		
		public:
			const byte c_BaseAddress;
			const byte c_ReservedAddress;
			const byte c_AddressCeiling;
			const byte c_JumpToAddress;

		private:
			byte m_ProgramCounter;
			byte m_Register0;
			byte m_Register1;
			bool m_OverflowError;
			bool m_UnderflowError;
			bool m_SignedMode;
			bool m_Halt;
			
			Memory* m_TheMemory;



		public:
			CPU(Memory* p_TheMemory);	
			~CPU();
			void Reset();
			void Run();
			const byte Fetch();
			void Decode(const byte& p_OpCode);
			void Add();
			void Beep();
			void Store();
			void Print();
			void Halt();
			void ClearRegister0();
			void ClearRegister1();
			void JumpTo();
	};
}

#endif
