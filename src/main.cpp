
#include <stdio.h>
#include <iostream>

#ifdef TESTING
#include "test\testRunner.h"
#endif

int main(int argc, char** argv) {

	// TODO: Add this once we get the addData stuff setup
	//if (appData.Flag("RunTesting")) {
#ifdef TESTING
		RunUnitTests(std::cout);
#else
		std::cerr << "Testing framework is not built into this version";
#endif
	//}

	return 0;
}