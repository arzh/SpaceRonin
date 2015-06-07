
#include "Data.h"

static void parseList(const std::string& str, std::vector<std::string>& list) {

	// Added this local for now, will likely be pulled out into a str utility method
	auto trim = [](const char* raw) {
		unsigned begin = 0, end = 0;
		unsigned len = strlen(raw);

		for (unsigned i = 0; i < len; ++i) {
			char c = raw[i];
			if (c != ' ' && c != '\t' && c != '\r' && c != '\n') {
				begin = i;
				break;
			}
		}

		for (unsigned j = len - 1; j > 0; --j) {
			char c = raw[j];
			if (c != ' ' && c != '\t' && c != '\r' && c != '\n') {
				end = j;
				break;
			}
		}

		len = (end - begin) + 1;
		char* trimmed = new char[len + 1]();
		memcpy(trimmed, &raw[begin], len);
		return trimmed;
	};

#pragma warning(push)
#pragma warning(disable: 4996)
	std::string s = str;
	char *c_str = const_cast<char*>(s.c_str());
	char *tok = std::strtok(c_str, ",");
	char *trimmed = trim(tok);
	while (trimmed != 0) {
		list.push_back(trimmed);
		delete[] trimmed; trimmed = 0;
		tok = std::strtok(NULL, ",");
		if (tok == 0) break;
		trimmed = trim(tok);
	}

	if (trimmed)
		delete[] trimmed;
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