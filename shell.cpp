#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

int main()
{
	string command;
	
	while (command != "exit") {
		if( command =="pw" )
			system("pwd");
		else if( command == "ifc")
			system("ifconfig");
		else if( command == "dt" ) 	
			system("date");
		else if( command == "vm" )
			system("vim");
		else if( command == "clrscrn" )
			system("clear");
		else if( command != "\0")
			cout << "Error: unknown command!\n";

		cout << "[SAMS_SHELL] ";
		cin >> command;
	}
    return 0;
}
