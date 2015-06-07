#pragma once

// The Simple Data Formet (.sdf)
// This is a simple text format that can be directly parsed into a Data format
//
// The format is a simple key value pair seperated by a colon ':'
//      x: 24
// multiple enteries are sperated by a comma ','
//      x: 24, y: 32
// list values are wrapped in square brakets '[' and ']' and list enteries are sperated by a comma
//      point: [24, 32]
// any white space between surranding the keys and values are trimmed

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
