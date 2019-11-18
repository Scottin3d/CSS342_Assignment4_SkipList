//
// Created by Yusuf Pisan on 4/26/18.
// Modified and edited by Scott Shirley 0760484 Novemeber 2019
//

#include "skiplist.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int TotalPassed = 0;
int TotalTests = 0;

template <typename T> std::string isOK(const T &got, const T &expected) {
	++TotalTests;
	if (got == expected) {
		++TotalPassed;
		return "OK: ";
	}
	else { //clang tidy complained but will not alter driver
		cout << "    Got   " << got << "\n expected " << expected << endl;
		return "ERR: ";
	}
}

void test02() {
	SkipList Skip(3);
	stringstream Ss;
	Ss << Skip;
	cout << isOK(Ss.str(), "Level: 2 -- -2147483648, 2147483647, \n"s +
		"Level: 1 -- -2147483648, 2147483647, \n"s +
		"Level: 0 -- -2147483648, 2147483647, \n"s)
		<< "Empty SkipList of Depth=3" << endl;

	/*
	/main.cpp:35:2: warning: random number generator seeded with a constant 
	value will generate a predictable sequence of values [cert-msc32-c]
	*/
	srand(100); //clang tidy complained but will not alter driver
	Skip.add(10);
	Skip.add(30);
	Skip.add(5);
	Skip.add(25);
	Ss.str("");
	Ss << Skip;
	cout << isOK(Ss.str(),
		"Level: 2 -- -2147483648, 25, 2147483647, \n"s +
		"Level: 1 -- -2147483648, 5, 10, 25, 30, 2147483647, \n"s +
		"Level: 0 -- -2147483648, 5, 10, 25, 30, 2147483647, \n"s)
		<< "SkipList of Depth=3 with 10, 30, 5, 25" << endl;
	cout << isOK(Skip.contains(10), true) << "Contains 10" << endl;
	cout << isOK(Skip.contains(30), true) << "Contains 30" << endl;
	cout << isOK(Skip.contains(71), false) << "Does not contain 71" << endl;
}

void test01() {
	SkipList Skip;
	stringstream Ss;
	Ss << Skip;
	cout << isOK(Ss.str(), "Level: 0 -- -2147483648, 2147483647, \n"s)
		<< "Empty SkipList" << endl;
	Skip.add(10);
	Skip.add(30);
	Skip.add(5);
	Skip.add(25);
	Ss.str("");
	Ss << Skip;
	cout << isOK(Ss.str(),
		"Level: 0 -- -2147483648, 5, 10, 25, 30, 2147483647, \n"s)
		<< "Added 10, 30, 5, 25," << endl;
}

void test3() {
	std::cout << "Creating a Skiplist with 3 levels \n";
	SkipList Skip3(3);
	std::cout << Skip3;
	std::cout << "--------------------------------" << "\n";
	Skip3.add(10);
	Skip3.add(40);
	Skip3.add(40);
	Skip3.add(5);
	Skip3.add(65);
	Skip3.add(19854);
	Skip3.add(-991);
	Skip3.add(550);
	Skip3.add(05);
	Skip3.add(INT_MAX);
	std::cout << "--------------------------------" << "\n";
	std::cout << Skip3;

	Skip3.contains(40);

	Skip3.remove(5);

	std::cout << Skip3;

}

int main() {
	cout << "Because of the random nature of SkipList, "
		<< "the skip list levels may not match" << endl;
	// Set the random seed for easy debugging
	// NOLINTNEXTLINE
	srand(424242);
	test01();
	test02();
	cout << "Passed: " << TotalPassed << "/" << TotalTests << endl;

	//my own tests
	test3();

	//for VS debugging
	std::cin.get();
	return 0;
}