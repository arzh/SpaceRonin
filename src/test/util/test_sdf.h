#pragma once

#include "util\data.h"
#include "util\simpleDataFormat.h"

void TestSDFParser(std::ostream& log) {
	char *test = "\t\nTest1:NOSPACES,\tTest2 : SPACES, test3: MORE spaces  ,IntTest\n:\n234,\nListTest : [a, list, of, values, no trim needed], ListTest2: [ \t well, need, to, trim, this, though \n]";

	Data d;
	sdf::Parse(test, d);

	std::string s;
	if (!d.String("Test1", s)) {
		log << "Failed to find key Test1 after parsing\n";
	} else if (s != "NOSPACES") {
		log << "key Test1 after parsing was not as expected (NOSPACES): " << s << "\n";
	}

	std::vector<std::string> ss;
	if (!d.StringList("ListTest2", ss)) {
		log << "Failed to parse ListTest2 value\n";
	} else if (ss.size() != 6) {
		log << "Size of ListTest2 is not what is expected (6): " << ss.size() << "\n";
	} else if (ss[5] != "though") {
		log << "Parsing of trailing whitespace failed expected (though): " << ss[5] << "\n";
	}

	int i;
	if (!d.Int("IntTest", i)) {
		log << "Failed to convert IntTest when parsed\n";
	} else if (i != 234) {
		log << "IntTest returned an unexpected value (234): " << i << "\n";
	}
}