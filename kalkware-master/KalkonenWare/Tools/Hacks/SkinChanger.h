#pragma once
#include "../../stdafx.h"
#include "Parser.h"

#define INVALID_EHANDLE_INDEX 0xFFFFFFFF

class Skinchanger
{
private:
	void RunSkins()
	{
		player_info_t info;
		if (!Interfaces.pEngine->GetPlayerInfo(Interfaces.pEngine->GetLocalPlayer(), &info))
			return;

		auto* weapons = Hacks.LocalPlayer->m_hMyWeapons();

		for (auto i = 0; weapons[i] != INVALID_EHANDLE_INDEX; i++) {

			CBaseEntity* pEnt = Interfaces.pEntList->GetClientEntityFromHandle_(weapons[i]);
			if (!pEnt) continue;

			CBaseCombatWeapon* pWep = (CBaseCombatWeapon*)pEnt; 
			if (!pWep) continue;

			int weapon = *pWep->GetItemDefinitionIndex(); 
			if (weapon < 1 || weapon > 520)
				continue;
			if (weapon)
			{
				if (strstr(pEnt->GetClientClass()->m_pNetworkName, "CKnife") && ClientVars.Skinchanger.KnifeModel > 0)
				{
					auto hworldmodel = pWep->m_hWeaponWorldModel();
					CBaseCombatWeapon* worldmodel;
					if (hworldmodel)
						worldmodel = (CBaseCombatWeapon*)Interfaces.pEntList->GetClientEntityFromHandle(hworldmodel);

					*pWep->GetEntityQuality() = 3; 

					*pWep->GetModelIndex() = GetCurrentKnifeModel(ClientVars.Skinchanger.KnifeModel);

					*pWep->GetViewmodelindex() = GetCurrentKnifeModel(ClientVars.Skinchanger.KnifeModel);

					if (worldmodel) 
						*worldmodel->GetModelIndex() = GetCurrentKnifeModel(ClientVars.Skinchanger.KnifeModel) + 1;

					*pWep->GetItemDefinitionIndex() = ClientVars.Skinchanger.KnifeModel;

				}
				if (ClientVars.W[weapon].Skn.skinID != 0)
				{
					*pWep->GetOriginalOwnerXuidLow() = info.m_nXuidLow;
					*pWep->GetOriginalOwnerXuidHigh() = info.m_nXuidHigh;

					*pWep->GetFallbackPaintKit() = ClientVars.W[weapon].Skn.skinID;
					*pWep->GetFallbackWear() = ClientVars.W[weapon].Skn.Wear;
					*pWep->GetFallbackStatTrak() = ClientVars.W[weapon].Skn.StatTrak; 
					snprintf(pWep->GetCustomName(), 32, ClientVars.W[weapon].Skn.name);

					*pWep->GetItemIDHigh() = 1; 
				}
			}
		}
	}
public:
	int ParseSkins()
	{
		valve_parser::Document doc;
		auto r = doc.Load(".\\csgo\\scripts\\items\\items_game.txt", valve_parser::ENCODING::UTF8);
		if (!r)
			return 1;

		valve_parser::Document english;
		r = english.Load(".\\csgo\\resource\\csgo_english.txt", valve_parser::ENCODING::UTF16_LE);
		if (!r)
			return 2;

		auto weaponSkinCombo = doc.BreadthFirstSearch("weapon_icons");
		if (!weaponSkinCombo || !weaponSkinCombo->ToObject())
			return 3;

		auto skinDataVec = doc.BreadthFirstSearchMultiple("paint_kits");
		if (!skinDataVec.size())
			return 4;

		auto PaintKitNames = english.BreadthFirstSearch("Tokens");
		if (!PaintKitNames || !PaintKitNames->ToObject())
			return 5;

		std::vector<std::string> weaponNames = {
			"deagle",
			"elite",
			"fiveseven",
			"glock",
			"ak47",
			"aug",
			"awp",
			"famas",
			"g3sg1",
			"galilar",
			"m249",
			"m4a1_silencer",
			"m4a1",
			"mac10",
			"p90",
			"ump45",
			"xm1014",
			"bizon",
			"mag7",
			"negev",
			"sawedoff",
			"tec9",
			"hkp2000",
			"mp7",
			"mp9",
			"nova",
			"p250",
			"scar20",
			"sg556",
			"ssg08",
			"usp_silencer",
			"cz75a",
			"revolver",
			"knife_m9_bayonet",
			"bayonet",
			"knife_flip",
			"knife_gut",
			"knife_karambit",
			"knife_tactical",
			"knife_falchion",
			"knife_survival_bowie",
			"knife_butterfly",
			"knife_push",
			"studded_bloodhound_gloves",
			"sporty_gloves",
			"slick_gloves",
			"leather_handwraps",
			"motorcycle_gloves",
			"specialist_gloves"

		};

		for (auto child : weaponSkinCombo->children)
		{
			if (child->ToObject())
			{
				for (auto weapon : weaponNames)
				{
					auto skinName = child->ToObject()->GetKeyByName("icon_path")->ToKeyValue()->Value.toString();
					auto pos = skinName.find(weapon);
					if (pos != std::string::npos)
					{
						auto pos2 = skinName.find_last_of('_');
						ClientVars.Skinchanger.weaponSkins[weapon].insert(
							skinName.substr(pos + weapon.length() + 1,
								pos2 - pos - weapon.length() - 1)
						);
						break;
					}
				}
			}
		}

		for (auto skinData : skinDataVec)
		{
			if (skinData->ToObject())
			{
				for (auto skin : skinData->children)
				{
					if (skin->ToObject())
					{
						skinInfo si;
						si.paintkit = skin->ToObject()->name.toInt();

						auto skinName = skin->ToObject()->GetKeyByName("name")->ToKeyValue()->Value.toString();
						auto tagNode = skin->ToObject()->GetKeyByName("description_tag");
						if (tagNode)
						{
							std::string tag = tagNode->ToKeyValue()->Value.toString();
							tag = tag.substr(1, std::string::npos);
							std::transform(tag.begin(), tag.end(), tag.begin(), towlower);
							si.tagName = tag;
						}

						auto keyVal = skin->ToObject()->GetKeyByName("seed");
						if (keyVal != nullptr)
							si.seed = keyVal->ToKeyValue()->Value.toInt();

						ClientVars.Skinchanger.skinMap[skinName] = si;
					}
				}
			}
		}

		for (auto child : PaintKitNames->children)
		{
			if (child->ToKeyValue())
			{
				std::string key = child->ToKeyValue()->Key.toString();
				std::transform(key.begin(), key.end(), key.begin(), towlower);
				if (key.find("paintkit") != std::string::npos &&
					key.find("tag") != std::string::npos)
				{
					ClientVars.Skinchanger.skinNames[key] = child->ToKeyValue()->Value.toString();
				}
			}
		}

		return 0;
	}

	int GetCurrentKnifeModel(int idx)
	{
		switch (idx)
		{
		case 500:
			return Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_bayonet.mdl"); 
		case 505:
			return Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_flip.mdl"); 
		case 506:
			return Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_gut.mdl"); 
		case 507:
			return Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_karam.mdl");
		case 508:
			return Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl"); 
		case 509:
			return Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_tactical.mdl");
		case 512:
			return Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_falchion_advanced.mdl"); 
		case 514:
			return Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_survival_bowie.mdl");
		case 515:
			return Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_butterfly.mdl");
		case 516:
			return Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_push.mdl");
		default:
			return 0;
		}
	}

	void Run()
	{
		if (!ClientVars.Skinchanger.Enabled)
			return;

		RunSkins();
	}
}Skins;