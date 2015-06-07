#pragma once

#ifdef TESTING
#include <ostream>
#include "test\util\test_data.h"
#include "test\util\test_sdf.h"

void RunUnitTests(std::ostream& out) {
	
	out << "Testing Util\\Data class\n";
	TestDataClass(out);
	out << "Finished Util\\Data class\n";

	out << "Testing SDFLexer\n";
	TestSDFLexer(out);
	out << "Finished SDFLexer\n";
}

#endif