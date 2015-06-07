
#include <fstream>
#include "file.h"

namespace os {

	FileStatus ReadFile(const char* fn, std::string& contents) {
		std::ifstream in(fn, std::ios::ate);
		if (in.fail()) {
			return FILE_NOT_FOUND;
		}

		contents.reserve(in.tellg());
		in.seekg(0, std::ios::beg);
		std::copy((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>(), std::back_inserter(contents));
		in.close();

		return SUCCESS;
	}

}