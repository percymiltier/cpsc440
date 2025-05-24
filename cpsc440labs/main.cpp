#include <iostream>
#include "labRunner.h"
using namespace std;

int main() {
	// easy lab runner
	cout << "Type the number of the lab to run: \n";
	cout << "1 2 3 \n\n";
	int a;
	cin >> a;

	while (1) {
		if (a == 1 || a == 2 || a == 3) {
			break;
		}
		else {
			cout << "Enter a valid lab number: \n";
			cout << "1 2 3 \n\n";
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
}