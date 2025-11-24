#include "fraction.h"

int main() {
	try {
		fraction drob1(15, -5);
		fraction drob2(3, 3);
		fraction rez = drob1--;
		rez.print();
		drob1.print();
	}
	catch (const char* msg) {
		std::cout << msg;
	}
	return 0;
}