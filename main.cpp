#include <iostream>
#include "Memory.h"

using namespace std;
using namespace CPU_4001;

int main() {
	cout << "Initialising memory...";

	Memory* theMemory = new Memory();

	cout << "Ready" << endl;

	cout << "Memory Size: " << (int)theMemory->c_MaxAddress << endl;

	cout << "Do you want to list the memory?";
	char answer;
	cin >> answer;

	if (answer == 'Y' || answer == 'y') {
		for (byte currentAddress = 0; currentAddress < theMemory->c_MaxAddress; ++currentAddress){
			cout << "Address [" << (int)currentAddress << "] = " << (int)theMemory->Read(currentAddress) << endl;
		}
	}

	delete theMemory;
}
