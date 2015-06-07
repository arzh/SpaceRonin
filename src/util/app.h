#pragma once

#include "util\data.h"

struct AppSettings {

	int winWidth = 1920;
	int winHeight = 1080;

	bool runTesting = false;
	bool spawnConsole = false;

	int logLevel = 0;

	void Apply(const Data& data) {
		data.Int("winWidth", winWidth);
		data.Int("winHeight", winHeight);

		runTesting = data.Flag("runTesting");
		spawnConsole = data.Flag("spawnConsole");

		data.Int("logLevel", logLevel);
	}
};

