#pragma once

// The Simple Data Format (.sdf)
// This is a simple text format that can be directly parsed into a Data format
//
// The format is a simple key value pair separated by a colon ':'
//      x: 24
// multiple entries are separated by a comma ','
//      x: 24, y: 32
// list values are wrapped in square brackets '[' and ']' and list entries are separated by a comma
//      point: [24, 32]
// any white space between surrounding the keys and values are trimmed

//TODO: Figure out an error handling method

#include "util\data.h"

class SDFLexer {
public:
	SDFLexer(const char* content);
	~SDFLexer();

	void Parse(Data& data);

private:
	const char* raw;
};

void ParseSDFFile(const char* fn, Data& data);
