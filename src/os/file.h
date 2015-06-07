#pragma once

#include <string>

namespace os {
	static enum FileStatus {
		SUCCESS = 0,
		FILE_NOT_FOUND,
	};

	FileStatus ReadFile(const char* filename, std::string& contents);

}