# Valheim Discord Relay (VDR)
A program that can connect your Valheim server to Discord, allowing cross-communication!

Valheim Discord Relay (VDR) is NOT a mod and is installed separately to Valheim. This programs requires your server to have the following installed:

- [BepInEx](https://thunderstore.io/c/valheim/p/denikson/BepInExPack_Valheim/)
- [RCON](https://thunderstore.io/c/valheim/p/AviiNL/rcon/)
- [RCON Commands](https://thunderstore.io/c/valheim/p/JereKuusela/Rcon_Commands/)

This project won't be constantly updated as this was created for a friend. I might update it time to time, however, don't expect features to constantly be added.

### Note: This only currently works on Linux.

## Installation

Download the latest version of ValheimRelay, drop it to whatever folder you want, give it executable permissions (`chmod +x ValheimRelay`), and then create a `config.json` file in the same folder as your `ValheimRelay` file.

Your `config.json` file should look something like this:
```json
{
  "rcon_ip": "IP HERE",
  "rcon_port": "25575",
  "rcon_password": "PASSWORD",
  "bot_token": "BOT TOKEN GOES HERE",
  "channel_id": "CHANNEL ID GOES HERE",
  "log_file_path": "PATH TO BEPINEX LOG OUTPUT HERE"
}
```

The `log_file_path` should point to your server's `BepInEx` folder, to a file called `LogOutput.log`, something like `/home/vhserver/MainServer/BepInEx/LogOutput.log`.

You can gather a bot token by creating a Discord bot [here](https://discord.com/developers/applications).

The `channel_id` is the ID of the channel that you want all the chat messages to go to.

