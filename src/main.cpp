#include "main.h"

#include <iostream>
#include <rcon.h>

#include "config.h"

int main(int argc, char *argv[]) {
	config::init("config.json");

	std::this_thread::sleep_for(std::chrono::minutes(config::get("start_delay")));

    rconpp::rcon rcon_client(config::get("rcon_ip").dump(), std::stoi(config::get("rcon_port").dump()), config::get("rcon_password").dump());

    dpp::cluster bot(config::get("bot_token"), dpp::i_default_intents | dpp::i_message_content | dpp::i_guild_members, 0, 0, 1, true, dpp::cache_policy::cpol_none);

	VDR::botRef = &bot;

	/* Output simple log messages to stdout */
	bot.on_log(dpp::utility::cout_logger());

	bot.on_message_create([&rcon_client](const dpp::message_create_t& event) {
		if (event.msg.author.is_bot()) {
			return;
		}

		if (event.msg.channel_id == dpp::snowflake(config::get("channel_id"))) {
			rcon_client.send_data("s " + event.msg.author.username + ": " + event.msg.content, 999, rconpp::data_type::SERVERDATA_EXECCOMMAND);
		}
	});

	/*
	bot.on_slashcommand([&bot, &rcon_client](const dpp::slashcommand_t& event) {

	});
	*/

	/* Register slash command here in on_ready */
	bot.on_ready([&bot, &rcon_client](const dpp::ready_t& event) {
		/* Wrap command registration in run_once to make sure it doesn't run on every full reconnection */
		//if (dpp::run_once<struct register_bot_commands>()) {
		//}

		bot.start_timer([](const dpp::timer& timer) {
				VDR::read_console();
		}, 1);

		bot.message_create(dpp::message(dpp::snowflake(config::get("channel_id")), "Valheim-Discord-Relay (VDR) has loaded!"), [&rcon_client](const dpp::confirmation_callback_t& callback) {
			rcon_client.send_data("say Valheim-Discord-Relay (VDR) has loaded!", 999, rconpp::data_type::SERVERDATA_EXECCOMMAND);
		});
	});

    bot.start(dpp::st_wait);
    return 0;
}

void VDR::read_console() {
	std::ifstream console_file(config::get("log_file_path"));

	if (last_char_read != 0) {
		console_file.seekg(last_char_read);
	}

	std::vector<std::string> strings;
	std::string str;
	while (std::getline(console_file, str)) {
		strings.emplace_back(std::move(str));
	}
	console_file.clear();

	if (last_char_read == 0) {
		last_char_read = console_file.tellg();
		console_file.close();
		return;
	}

	for (const std::string& log : strings) {
		// Check if message first so we can process that first, ensuring everything else is most likely not coming from a player.
		if (log.find(" s ") != std::string::npos) {
			if(users.contains(get_id_from_chat_log(log))) {
				if(users.at(get_id_from_chat_log(log)) == "n/a") {
					users.erase(get_id_from_chat_log(log));
					users.emplace(get_id_from_chat_log(log), get_user_from_chat_log(log));
				}
			}

			std::string msg = "**" + get_user_from_chat_log(log) + ": " + get_message_from_chat_log(log) + "**";

			std::cout << get_user_from_chat_log(log) << " said: " << get_message_from_chat_log(log) << "\n";

			botRef->message_create(dpp::message(dpp::snowflake(config::get("channel_id")), msg));

		} else if (log.find(": Got connection SteamID") != std::string::npos) {
			users.emplace(get_id_from_join_log(log), "n/a");
			std::cout << "A player under the ID " << get_id_from_join_log(log) << " has joined." << "\n";

		} else if (log.find("I HAVE ARRIVED!") != std::string::npos) {
			std::string msg = std::string("**" + get_user_from_generic_log(log) + " joined the server!**");

			botRef->message_create(dpp::message(dpp::snowflake(config::get("channel_id")), msg));

		} else if (log.find("Closing socket") != std::string::npos) {
			std::string msg{};
			const uint64_t id = get_id_from_leave_log(log);
			if(users.contains(id)) {
				msg = "**" + users.at(id) + " left the server!**";
			} else {
				msg = "**" + std::to_string(id) + " (Name not filled as user never chatted) left the server!**";
			}

			botRef->message_create(dpp::message(dpp::snowflake(config::get("channel_id")), msg));

			users.erase(id);
		}
	}

	last_char_read = console_file.tellg();

	console_file.close();
}
