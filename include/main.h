#pragma once
#include <regex>
#include <string>
#include <dpp/dpp.h>

namespace VDR {

	void read_console();

	inline dpp::cluster* botRef{nullptr};

	inline std::map<uint64_t, std::string> users{};

	inline long long last_char_read{0};

	static std::string get_user_from_chat_log(const std::string& log_line) {
		std::smatch match{};
		std::regex_search(log_line.begin(), log_line.end(), match, std::regex(R"(([/][A-Z])\w+)"));
		return match[0].str().erase(0, 1);
	}

	static std::string get_message_from_chat_log(const std::string& log_line) {
		std::smatch match{};
		std::regex_search(log_line.begin(), log_line.end(), match, std::regex(R"(([s]\s[A-Z])\w+)"));
		const std::string temp = match[0].str();
		return temp.substr(2, temp.size());
	}

	static std::string get_user_from_generic_log(const std::string& log_line) {
		std::smatch match{};
		std::regex_search(log_line.begin(), log_line.end(), match, std::regex(R"(([>][A-Z])\w+)"));
		return match[0].str().erase(0, 1);
	}

	static uint64_t get_id_from_join_log(const std::string& log_line) {
		std::smatch match{};
		std::regex_search(log_line.begin(), log_line.end(), match, std::regex(R"(([D][ ])\w+)"));
		const std::string temp = match[0].str();
		return std::stoull(temp.substr(2, temp.size()));
	}

	static uint64_t get_id_from_leave_log(const std::string& log_line) {
		std::smatch match{};
		std::regex_search(log_line.begin(), log_line.end(), match, std::regex(R"(([t][ ])\w+)"));
		const std::string temp = match[0].str();
		return std::stoull(temp.substr(2, temp.size()));
	}

	static uint64_t get_id_from_chat_log(const std::string& log_line) {
		std::smatch match{};
		std::regex_search(log_line.begin(), log_line.end(), match, std::regex(R"(([:][ ][0-9])\w+)"));
		const std::string temp = match[0].str();
		return std::stoull(temp.substr(2, temp.size()));
	}

	static std::string get_user_from_leave_log(const std::string& log_line) {
		std::smatch match{};
		std::regex_search(log_line.begin(), log_line.end(), match, std::regex(R"(([>][A-Z])\w+)"));
		return match[0].str().erase(0, 1);
	}

}
