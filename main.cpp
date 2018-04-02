#include <iostream>
#include "Memory.h"
#include "CPU.h"
#include <exception>

using namespace std;
using namespace CPU_4001;

void DefaultProgram(Memory*);
void ReportMemory(Memory*);
void ClearMemory(Memory*);
void ShowMenu();

const bool ChooseFromMenu(const char&, Memory*);
const bool IsExitOption(const char& selection);

void ProgramEntry(Memory*);

int main() {
	cout << "Initialising memory...";

	Memory* theMemory = new Memory();

	cout << "Ready" << endl;

	cout << "Memory Size: " << (int)theMemory->c_MaxAddress << endl;

	bool quitAll = false;
	char selectedOption = ' ';
	do{
		ShowMenu();
		cin >> selectedOption;

		if(!IsExitOption(selectedOption)){
			if(ChooseFromMenu(selectedOption,theMemory)){
				cout << "Creating the CPU instance" << endl;
				CPU* theCPU = new CPU(theMemory);
				cout << "Ready" << endl;

				cout << "Starting" << endl;
				theCPU->Run();
				cout << "Done" << endl;

				delete theCPU;

			}
		} else {
			quitAll = true;
		}

	}
	while(!quitAll);
	
	delete theMemory;
}

void ShowMenu(){
 cout << endl << "===== Menu =====" << endl;
 cout << "1. Load Default Program" << endl;
 cout << "2. Clear the Memory" << endl;
 cout << "3. Report Memory" << endl;
 cout << "R. Run the current memory state through the CPU" << endl;
 cout << "E. Enter the program editor" << endl;
 cout << endl;
 cout << "X. Exit Interpter" << endl;
 cout << endl;
 cout << "Selection: ";
}

const bool IsExitOption(const char& selection){
	return (selection == 'x' || selection == 'X');
}

const bool ChooseFromMenu(const char& selection, Memory* theMemory){

	bool l_RunThroughCPU = false;

	switch(selection){
		case '1':
			DefaultProgram(theMemory);
			break;
		case '2':
			ClearMemory(theMemory);
			break;
		case '3':
			ReportMemory(theMemory);
			break;
		case 'r':
		case 'R':
			l_RunThroughCPU = true;
			break;
		case 'e':
		case 'E':
			ProgramEntry(theMemory);
			break;

	}

	return l_RunThroughCPU;
}

void DefaultProgram(Memory* theMemory){

	if(theMemory != nullptr){
		ClearMemory(theMemory);

		cout << "Adding default machine code program" << endl;

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
	}
}

void ClearMemory(Memory* theMemory){
	if(theMemory != nullptr){
		cout << "Clearing memory" << endl;
		theMemory->Clear();
		cout << "Clearing memory complete" << endl;

	}
}

void ReportMemory(Memory* theMemory){
	cout << "Do you want to list the memory?";
	char answer;
	cin >> answer;

	if (answer == 'Y' || answer == 'y') {
		for (byte currentAddress = 0; currentAddress < theMemory->c_MaxAddress; ++currentAddress){
			cout << "Address [" << (int)currentAddress << "] = " << (int)theMemory->Read(currentAddress) << endl;
		}
	}
	
}

void ProgramEntry(Memory* p_Memory){

	cout<< "Entering program entry" << endl;
	cout << "N : Next address" << endl;
	cout << "B : Previous address" << endl;
	cout << "<BYTE> changes current address + increment address" << endl;

	if(p_Memory != nullptr){
		byte currentAddress = 2;
		bool exitEditor = false;
		std::string input;
		byte value;
		do{
			cout << "[" << (int)currentAddress << "] (" << (int)p_Memory->Read(currentAddress) << ") > " << endl;
			cin >> input;

			try{
				if(input == "x" || input == "X"){
					exitEditor = true;
				} 
				else if(input == "b" || input == "B" || input == "back"){
					--currentAddress;
				}
				else if(input == "n" || input == "N" || input == "next"){
					++currentAddress;
				}
				else{
					
					int temp = atoi(input.c_str());
					value = (byte)temp;

					p_Memory->Write(currentAddress, value);
					++currentAddress;

				}
			}
			catch(std::exception& ex){

			}

		}
		while(!exitEditor);
		 
	}
}