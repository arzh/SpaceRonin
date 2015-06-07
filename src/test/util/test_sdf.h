#pragma once

#include "util\data.h"
#include "util\simpleDataFormat.h"

void TestSDFLexer(std::ostream& log) {
	char *test = "\t\nTest1:NOSPACES,\tTest2 : SPACES, test3: MORE spaces  ,\nTest4 : [a, list, of, values, no trim needed], Test5: [ \t well, need, to, trim, this, though \n]";

	Data d;
	SDFLexer lex(test);
	lex.Parse(d);

}