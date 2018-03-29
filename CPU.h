#ifndef CPU_PROCESSOR
#define CPU_PROCESSOR

#include "Memory.h"

namespace CPU_4001{
	
	class CPU{
		
		private:
			byte m_ProgramCounter;
			byte m_Register0;
			byte m_Register1;
			bool m_OverflowError;
			bool m_UnderflowError;
			bool m_SignedMode;
			
			Memory* m_TheMemory;
		public:
			CPU(Memory* p_TheMemory);	
			~CPU();
			void Reset();
			void Run();
	};
}

#endif
