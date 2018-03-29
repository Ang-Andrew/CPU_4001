#include <iostream>
#include "Memory.h"
#include "CPU.h"

using namespace std;
using namespace CPU_4001;

int main() {
	cout << "Initialising memory...";

	Memory* theMemory = new Memory();

	cout << "Ready" << endl;

	cout << "Memory Size: " << (int)theMemory->c_MaxAddress << endl;

	// Add the program
	cout << "Adding default machine code program" << endl;
	// Load0 value 1
	theMemory->Write(1,1);
	theMemory->Write(2,5);
	
	//Load1 Value 2
	theMemory->Write(3,2);
	theMemory->Write(4,3);
	
	//Add
	theMemory->Write(5,3);
	
	//Store to 12
	theMemory->Write(6,5);
	theMemory->Write(7,12);

	//print from 12
	theMemory->Write(8,6);
	theMemory->Write(9,12);

	//beep
	theMemory->Write(10,4);

	//halt
	theMemory->Write(11,0);

	cout << "Do you want to list the memory?";
	char answer;
	cin >> answer;

	if (answer == 'Y' || answer == 'y') {
		for (byte currentAddress = 0; currentAddress < theMemory->c_MaxAddress; ++currentAddress){
			cout << "Address [" << (int)currentAddress << "] = " << (int)theMemory->Read(currentAddress) << endl;
		}
	}
	
	cout << "Creating the CPU instance" << endl;
	CPU* theCPU = new CPU(theMemory);
	cout << "Ready" << endl;

	cout << "Starting" << endl;
	theCPU->Run();
	cout << "Done" << endl;

	delete theCPU;

	delete theMemory;
}
