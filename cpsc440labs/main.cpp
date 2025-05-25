#include <iostream>
#include "labRunner.h"
using namespace std;

int main() {
	// easy lab runner
	cout << "Type the number of the assignment to run: \n";
	cout << "1. Lab 1 \n2. Lab 2 \n3. Lab 3 \n4. Programming Assignment 1 \n\n";
	int a;
	cin >> a;

	while (1) {
		if (a == 1 || a == 2 || a == 3 || a == 4) {
			break;
		}
		else {
			cout << "Enter a valid assignment number: \n";
			cout << "1. Lab 1 \n2. Lab 2 \n3. Lab 3 \n4. Programming Assignment 1 \n\n";
			cin >> a;
		}
	}

	if (a == 1) {
		lab1();
	}
	else if (a == 2) {
		lab2();
	}
	else if (a == 3) {
		lab3();
	}
	else if (a == 4) {
		pa1();
	}
}