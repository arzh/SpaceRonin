
#include "os\file.h"
#include "simpleDataFormat.h"

namespace sdf {

	void Parse(const char* content, Data& data) {
		enum STATE {
			MARK = 0,
			KEY,
			VALUE,
			LIST,
			CLOSE_LIST
		};

		struct substr {
			const char* c;
			unsigned len;
		};

		substr _key;
		substr _value;

		unsigned mark = 0, loc = 0;
		unsigned len = strlen(content);

		STATE state = MARK;
		STATE nextState = KEY;

		auto set = [content, &mark, &loc](substr& ss) {
			unsigned len = 0;
			for (unsigned e = loc - 1; e >= 0; --e) {
				if (!isspace(content[e])) {
					len = e - mark;
					break;
				}
			}

			ss.c = &content[mark];
			ss.len = len + 1;
		};

		auto yank = [&data, &_key, &_value]() {
			data.Insert(std::string(_key.c, _key.len),
						std::string(_value.c, _value.len));
		};

		auto findMark = [&state, &nextState](STATE next) {
			state = MARK;
			nextState = next;
		};

		for (loc = 0; loc < len; ++loc) {
			char c = content[loc];

			switch (state) {
			case MARK:
				if (!isspace(c)) {
					mark = loc;
					--loc;
					state = nextState;
				}
				break;
			case KEY:
				if (c == ':') {
					set(_key);
					findMark(VALUE);
				}
				break;
			case VALUE:
				if (c == '[') {
					findMark(LIST);
				} else if (c == ',') {
					set(_value);
					yank();
					findMark(KEY);
				}
				break;
			case LIST:
				if (c == ']') {
					set(_value);
					state = CLOSE_LIST;
				}
				break;
			case CLOSE_LIST:
				if (c == ',') {
					yank();
					findMark(KEY);
				}
				break;
			}
		}

		if (state == VALUE) {
			set(_value);
			yank();
		} else if (state == CLOSE_LIST) {
			yank();
		}
	};

	void ParseFile(const char* fn, Data& data) {
		std::string fc;
		os::ReadFile(fn, fc);

		return Parse(fc.c_str(), data);
	}
}