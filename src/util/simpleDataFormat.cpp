
#include "simpleDataFormat.h"

SDFLexer::SDFLexer(const char* content) : raw(content) {}
SDFLexer::~SDFLexer() {}

void SDFLexer::Parse(Data& data) {
	enum STATE {
		MARK = 0,
		KEY,
		VALUE,
		LIST,
		CLOSE_LIST
	};

	const char *key = 0, *value = 0;
	unsigned klen = 0, vlen = 0, len = 0, mark = 0;

	auto lastChar = [this](unsigned end) {
		for (unsigned e = end-1; e >= 0; --e) {
			if (!isspace(raw[e]))
				return e;
		}
		return (unsigned)0;
	};

	auto yank = [&data, &key, &klen, &value, &vlen]() {
		std::string k(key, klen);
		std::string v(value, vlen);
		data.Insert(std::string(key, klen), std::string(value, vlen));
		key = 0; klen = 0; value = 0; vlen = 0;
	};

	len = strlen(raw);

	STATE state = MARK;
	STATE nextState = KEY;
	
	for ( unsigned loc = 0; loc < len; ++loc) {
		char c = raw[loc];

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
				key = &raw[mark];
				klen = (lastChar(loc) - mark) + 1;
				state = MARK;
				nextState = VALUE;
			}
			break;
		case VALUE:
			if (c == '[') {
				state = MARK;
				nextState = LIST;
			} else if (c == ',') {
				value = &raw[mark];
				vlen = (lastChar(loc) - mark) + 1;
				yank();
				state = MARK;
				nextState = KEY;
			}
			break;
		case LIST:
			if (c == ']') {
				value = &raw[mark];
				vlen = (lastChar(loc) - mark) + 1;
				state = CLOSE_LIST;
			}
			break;
		case CLOSE_LIST:
			if (c == ',') {
				yank();
				state = MARK;
				nextState = KEY;
			}
			break;
		default:
			break;
		}
	}

	if (state == VALUE) {
		value = &raw[mark];
		vlen = (lastChar(len) - mark) + 1;
		yank();
	} else if (state == CLOSE_LIST) {
		yank();
	}
};