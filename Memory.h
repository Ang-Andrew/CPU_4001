#ifndef CPU_MEMORY
#define CPU_MEMORY

namespace CPU_4001 {
	typedef unsigned char byte;

	class Memory {
	public:

		const byte c_MaxAddress; //constant for max address we can read or write from

	private:
		
		byte * m_MemorySpace; //memory space that is going to be used

	public:

		Memory(); //construct Memory class instance

		~Memory(); //delete the memory class, releasing the allocated memory space

		void Clear(); //function to clear memory values to zero

		const byte& Read(const byte& p_Address); //function to read the given address value

		void Write(const byte& p_Address, const byte& p_Value); //function to write to given address
	};

}

#endif
