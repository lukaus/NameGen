// Luke Stanley
// BC4000 Driver/test/util file
// Copyright Terminus Software 2017

#include <fstream>
#include <string>
#include <iostream>
#include "nameGen.h"
#include <time.h>

using namespace std;

int main(int argc, char **argv)
{

	NameGen* test;
	string temp;
	srand((unsigned int) time(NULL));

	if (argc > 1)
	{
		cout << "Seeding random with: " << atoi(argv[1]) << endl;
		srand(atoi(argv[1]));
	}
	test = new NameGen();

	string option = "a";

	cout << "\t" << "pho: " << test->getInfo() << "\n";
	while(true)
	{	

		cout << test->getName() << "\t";
		getline(cin, option);
		if (option == "s")
		{
			test->reshuffle();
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
			cout << "\t" << "This set: " << test->getInfo() << "\n";
		}

	}
	return 0;
}

