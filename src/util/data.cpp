
#include "Data.h"

static void parseList(const std::string& str, std::vector<std::string>& list) {

	// Added this local for now, will likely be pulled out into a str utility method
	auto trim = []( char* raw) {
		if (raw) {
			unsigned len = strlen(raw);

			for (unsigned i = 0; i < len; ++i) {
				char c = raw[i];
				if (c != ' ' && c != '\t' && c != '\r' && c != '\n') {
					raw = &raw[i];
					len -= i;
					break;
				}
			}

			for (unsigned j = len - 1; j > 0; --j) {
				char c = raw[j];
				if (c != ' ' && c != '\t' && c != '\r' && c != '\n') {
					raw[j + 1] = '\0';
					break;
				}
			}
		}

		return raw;
	};

#pragma warning(push)
#pragma warning(disable: 4996)
	auto slen = str.length();
	void* mem = malloc((slen * sizeof(char)) + 1);
	memcpy(mem, str.c_str(), slen+1);

	char *c_str = (char*)(mem);
	char *tok = trim(std::strtok(c_str, ","));

	while (tok != 0) {
		list.push_back(tok);
		tok = trim(std::strtok(NULL, ","));
	}

	free(mem);
#pragma warning(pop)
}

// This is very limiting, which is why it is not called strtob or something similar.
#include <algorithm>
static bool isStrTrue(const std::string& str) {
	static const char* const true_values[] = { "1", "t", "yes", "true" };
	std::string test;
	std::transform(str.begin(), str.end(), std::back_inserter(test), ::tolower);

	for (int i = 0; i < 4; ++i) {
		if (strcmp(test.c_str(), true_values[i]) == 0) {
			return true;
		}
	}

	return false;
}

Data::Data() {

}

Data::~Data() {
	_map.clear();
}

bool Data::Int(const std::string& key, int& value) {
	auto& t = _map.find(key);

	if (t == _map.end())
		return false;

	try {
		value = std::stoi(t->second);
	} catch (...) {
		return false;
	}

	return true;
}

bool Data::Double(const std::string& key, double& value) {
	auto& t = _map.find(key);

	if (t == _map.end())
		return false;

	try {
		value = std::stod(t->second);
	} catch (...) {
		return false;
	}

	return true;
}

bool Data::String(const std::string& key, std::string& value) {
	auto& t = _map.find(key);

	if (t == _map.end())
		return false;

	value = t->second;

	return true;
}

bool Data::IntList(const std::string& key, std::vector<int>& list) {
	auto& t = _map.find(key);

	if (t == _map.end())
		return false;

	std::vector<std::string> strlist;
	parseList(t->second, strlist);

	try {
		for (auto&& s : strlist) {
			list.push_back(std::stoi(s));
		}
	} catch (...) {
		return false;
	}


	return true;
}

bool Data::DoubleList(const std::string& key, std::vector<double>& list) {
	auto& t = _map.find(key);

	if (t == _map.end())
		return false;

	std::vector<std::string> strlist;
	parseList(t->second, strlist);

	try {
		for (auto&& s : strlist) {
			list.push_back(std::stod(s));
		}
	} catch (...) {
		return false;
	}

	return true;
}

bool Data::StringList(const std::string& key, std::vector<std::string>& list) {
	auto& t = _map.find(key);

	if (t == _map.end())
		return false;

	parseList(t->second, list);

	return true;
}

bool Data::Insert(const std::string& key, const std::string& value, bool dontOverwrite) {
	auto& t = _map.find(key);

	if (t != _map.end()) {
		if (dontOverwrite)
			return false;
		t->second = value;
	} else {
		_map.insert({ key, value });
	}

	return true;
}

bool Data::Flag(const std::string& key) {
	auto& t = _map.find(key);

	if (t == _map.end())
		return false;

	return isStrTrue(t->second);
}