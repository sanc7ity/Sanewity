#pragma once
#include "../../stdafx.h"
int lastUser = 1;
long lastUpdate = -1;

class FarESP
{
private:
	static void split(std::string str, std::string splitBy, std::vector<std::string>& tokens)
	{
		tokens.push_back(str);

		size_t splitAt;
		size_t splitLen = splitBy.size();
		std::string frag;
		while (true)
		{
			frag = tokens.back();
			splitAt = frag.find(splitBy);
			if (splitAt == string::npos)
			{
				break;
			}
			tokens.back() = frag.substr(0, splitAt);
			tokens.push_back(frag.substr(splitAt + splitLen, frag.size() - (splitAt + splitLen)));
		}
	}

	static void replaceAll(std::string& str, const std::string& from, const std::string& to) {
		if (from.empty())
			return;
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length();
		}
	}

	static bool Contains(const std::string &word, const std::string &sentence) {
		if (word == "" || sentence == "")
			return true;

		return sentence.find(word) != std::string::npos;
	}

	static bool isInteger(const std::string & s)
	{
		if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

		char * p;
		strtol(s.c_str(), &p, 10);

		return (*p == 0);
	}

	static bool isFloat(string s) {
		istringstream iss(s);
		float dummy;
		iss >> noskipws >> dummy;
		return iss && iss.eof();
	}
public:
	static void addFarEspMessage(int target, float x, float y, float z, int weapon) {
		int time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		if (time >= PlayerInfo.players[target]->time || PlayerInfo.players[target]->time == 0) {
			PlayerInfo.latestByMessage = target;
			PlayerInfo.players[target]->lastPos.x = x;
			PlayerInfo.players[target]->lastPos.y = y;
			PlayerInfo.players[target]->lastPos.z = z;
			PlayerInfo.players[target]->lastWep = weapon;
			PlayerInfo.players[target]->time = time;
			PlayerInfo.players[target]->valid = true;
		}
	}


	static std::string string_to_hex(const std::string& input)
	{
		static const char* const lut = "0123456789ABCDEF";
		size_t len = input.length();

		std::string output;
		output.reserve(2 * len);
		for (size_t i = 0; i < len; ++i)
		{
			const unsigned char c = input[i];
			output.push_back(lut[c >> 4]);
			output.push_back(lut[c & 15]);
		}
		return output;
	}

	static std::string hex_to_string(const std::string& input)
	{
		static const char* const lut = "0123456789ABCDEF";
		size_t len = input.length();
		if (len & 1) return "";

		std::string output;
		output.reserve(len / 2);
		for (size_t i = 0; i < len; i += 2)
		{
			char a = input[i];
			const char* p = std::lower_bound(lut, lut + 16, a);
			if (*p != a) return "";

			char b = input[i + 1];
			const char* q = std::lower_bound(lut, lut + 16, b);
			if (*q != b) return "";

			output.push_back(((p - lut) << 4) | (q - lut));
		}
		return output;
	}

	int FromHex(const string &s) { return strtoul(s.c_str(), NULL, 16); }

	static void FarESPIngoing(IGameEvent* event)
	{
		if (GVars.unhooked)
			return;

		if (!ClientVars.Misc.faresp)
			return;

		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		if (pLocal) {
			CBaseEntity* sender = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetPlayerForUserID(event->GetInt("userid")));
			std::string message = event->GetString("text");

			std::string prefix = "[KalkWare-Packet]";
			std::string splitter = "{";
			std::string splitter2 = "}";

			std::string splitter3 = ":";
			std::string splitter4 = ",";
			if (sender) {
				if (sender->GetTeam() == pLocal->GetTeam() && sender != pLocal) {
					if (Contains(prefix, message)) {
						std::string messageFormatted = message;
						replaceAll(messageFormatted, prefix, "");
						messageFormatted = hex_to_string(messageFormatted);
						if (Contains(splitter, messageFormatted) && Contains(splitter2, messageFormatted) && Contains(splitter3, messageFormatted)) {
							replaceAll(messageFormatted, splitter, "");
							replaceAll(messageFormatted, splitter2, "");
							std::vector<std::string> user;
							split(messageFormatted, splitter3, user);
							if (user.size() == 2 && isInteger(user[0]) && Contains(splitter4, messageFormatted)) {
								std::vector<std::string> info;
								split(user[1], splitter4, info);
								if (info.size() == 4 && isFloat(info[0]) && isFloat(info[1]) && isFloat(info[2]) && isInteger(info[3])) {
									int targetID = std::stoi(user[0]);
									CBaseEntity* target = Interfaces.pEntList->GetClientEntity(targetID);
									if (target) {
										if (target->isAlive() && target->IsDormant() && target->GetTeam() != pLocal->GetTeam()) {
											float x = std::atof(info[0].c_str());
											float y = std::atof(info[1].c_str());
											float z = std::atof(info[2].c_str());
											int wep = std::stoi(info[3]);
											addFarEspMessage(targetID, x, y, z, wep);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	static void FarESPOutgoing() {
		long time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		if (time - lastUpdate > 750 || lastUpdate == -1) {
			lastUpdate = time;
		}
		else {
			return;
		}
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
		if (pLocal) {
			for (int i = lastUser; i < Interfaces.pEngine->GetMaxClients(); i++)
			{
				CBaseEntity* pEntity = Interfaces.pEntList->GetClientEntity(i);

				lastUser += 1;
				if (Interfaces.pEngine->GetMaxClients() == lastUser)
					lastUser = 1;

				if (!pEntity->IsPlayerESP() || !pEntity->isAlive())
					continue;

				if (pEntity->GetTeam() == pLocal->GetTeam())
					continue;

				if (pEntity->GetIndex() == PlayerInfo.latestByMessage && time - PlayerInfo.players[pEntity->GetIndex()]->time < 2000)
					continue;

				if (!pEntity->IsDormant()) {
					int wep;
					if (pEntity->GetActiveBaseCombatWeapon())
						wep = pEntity->GetActiveBaseCombatWeapon()->SafeWeaponID();
					char temp[512];
					sprintf_s(temp, "%i:{%f,%f,%f,%i}", pEntity->GetIndex(), pEntity->GetVecOrigin().x, pEntity->GetVecOrigin().y, pEntity->GetVecOrigin().z, wep);
					std::string data = temp;
					data = string_to_hex(data);
					data = "say_team \"[KalkWare-Packet]" + data + "\"";
					Interfaces.pEngine->ClientCmd_Unrestricted(data.c_str(), 0);
					break;
				}
			}
		}
	}
};