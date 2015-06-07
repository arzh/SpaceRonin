
#include <stdio.h>
#include <iostream>

#include "util\data.h"
#include "util\app.h"
#include "util\simpleDataFormat.h"

#ifdef TESTING
#include "test\testRunner.h"
#endif

int main(int argc, char** argv) {

	AppSettings settings;
	Data conf;

	sdf::ParseFile("app.sdff", conf);
	settings.Apply(conf);

	if (settings.runTesting) {
#ifdef TESTING
		RunUnitTests(std::cout);
#else
		std::cerr << "Testing framework is not built into this version";
#endif
	}

	return 0;
}