#pragma once

#include <string>
#include <vector>
#include <unordered_map>

// The Data class is a simple wrapper to a string[string] map (current implementation uses a std::unordered_map)
// with string -> type and string -> typed vector methods
//
// This should not only be used for internal data storage, a struct is the correct option
// The Data class should only be used when as a common interface to the system to read and write from an external source
class Data {
public:
	Data();
	~Data();

	// int type look up / conversion
	// Will return false if the key is not found or if the value failed to convert to an int
	bool Int   (const std::string& key, int&         value);
	// double type look up / conversion
	// Will return false if the key is not found or if the value failed to convert to an double
	// WARNING: It is not a good idea to convert the double to a float due to poor rounding errors
	bool Double(const std::string& key, double&      value);
	// std::string type loop up, no conversion is made
	// Will return false ONLY is the key is not found
	bool String(const std::string& key, std::string& value);
	// Flag look up
	// Will return true if the value of the key is convertible to a bool and is in the true value list (["1", "t", "yes", "true"] case insensitive)
	// If the key is not found or the value of the key is anything other then the true list false will be returned
	bool Flag  (const std::string& key);

	// int list parser
	// parses a comma (',') delimited list of the value and tries to convert the sub-values to int
	// if the value is convertible it is appended to the given list
	// if a value fails to convert all the following values will not be attempted
	// will return false if the key is not found or if one of the values failed to convert to an int
	bool IntList   (const std::string& key, std::vector<int>&         list);
	// int list parser
	// parses a comma (',') delimited list of the value and tries to convert the sub-values to double
	// if the value is convertible it is appended to the given list
	// if a value fails to convert all the following values will not be attempted
	// will return false if the key is not found or if one of the values failed to convert to an double
	bool DoubleList(const std::string& key, std::vector<double>&      list);
	// string list parser
	// parses a comma (',') delimited list of the value and appends them to the given list
	bool StringList(const std::string& key, std::vector<std::string>& list);

	// Added a key[value] pair to the dataset.
	// the value of a given key can protected if the 'dontOverwrite' flag is set to true, it is defaulted to false
	// otherwise the value will be overwritten the key already exists
	// will return false if the dontOverwrite flag is set and the key already exists, otherwise returns true
	// since the common case is to not use dontOverwrite it is generally safe to ignore the return value
	bool Insert(const std::string& key, const std::string& value, bool dontOverwrite = false);

protected:
	std::unordered_map<std::string, std::string> _map;
};