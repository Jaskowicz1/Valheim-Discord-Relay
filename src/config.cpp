#include "config.h"
#include <dpp/dpp.h>
#include <fstream>

namespace config {

	static nlohmann::json configdocument;

	void init(const std::string& config_file) {
		/* Set up the bot cluster and read the configuration json */
		std::ifstream configfile(config_file);
		configfile >> configdocument;
	}

	bool exists(const std::string& key) {
		return configdocument.contains(key);
	}

	nlohmann::json& get(const std::string& key) {
		if (key.empty()) {
			return configdocument;
		}
		return configdocument.at(key);
	}

};

