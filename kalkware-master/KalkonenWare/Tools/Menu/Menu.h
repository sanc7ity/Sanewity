#pragma once
#include "../../stdafx.h"
#include "Tools\IMGUI\imgui.h"
#include "Tools\IMGUI\DX9\imgui_impl_dx9.h"
#include "Tools\IMGUI\imgui_internal.h"
#include "Config.h"
#include "../Hacks/Parser.h"
#include <minwindef.h>

const char* keyNames[] =
{
	"Off",
	"Mouse 1",
	"Mouse 2",
	"Cancel",
	"Middle Mouse",
	"Mouse 4",
	"Mouse 5",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",

};


#define MENU_SIZE_X 700
#define MENU_SIZE_Y 600
#define TAB_COUNT 5
#define SUBTAB_COUNT 6

void Tab(const char* name, int* v, int tab_id) {

	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4 oldtext = style.Colors[ImGuiCol_Text];
	ImVec4 oldbutton = style.Colors[ImGuiCol_Button];
	ImVec4 oldbuttonhovered = style.Colors[ImGuiCol_ButtonHovered];
	ImVec4 oldbuttonactive = style.Colors[ImGuiCol_ButtonActive];
	if (tab_id != 0)
	{
		ImGui::SameLine();
	}
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(ClientVars.Styles.Colors.MainMenuButtons[0] * 0.9, ClientVars.Styles.Colors.MainMenuButtons[1] * 0.9, ClientVars.Styles.Colors.MainMenuButtons[2] * 0.9, ClientVars.Styles.Colors.MainMenuButtons[3] * 0.9);
	style.Colors[ImGuiCol_Button] = ImVec4(ClientVars.Styles.Colors.MainMenuButtons[0], ClientVars.Styles.Colors.MainMenuButtons[1], ClientVars.Styles.Colors.MainMenuButtons[2], ClientVars.Styles.Colors.MainMenuButtons[3]);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(ClientVars.Styles.Colors.MainMenuButtons[0] * 0.9, ClientVars.Styles.Colors.MainMenuButtons[1] * 0.9, ClientVars.Styles.Colors.MainMenuButtons[2] * 0.9, ClientVars.Styles.Colors.MainMenuButtons[3] * 0.9);

	style.Colors[ImGuiCol_Text] = ImVec4(ClientVars.Styles.Colors.Text[0] * 0.5, ClientVars.Styles.Colors.Text[1] * 0.5, ClientVars.Styles.Colors.Text[2] * 0.5, ClientVars.Styles.Colors.Text[3] * 0.5);
	if (*v == tab_id) {
		style.Colors[ImGuiCol_Text] = ImVec4(ClientVars.Styles.Colors.Text[0], ClientVars.Styles.Colors.Text[1], ClientVars.Styles.Colors.Text[2], ClientVars.Styles.Colors.Text[3]);
		style.Colors[ImGuiCol_Button] = ImVec4(ClientVars.Styles.Colors.MainMenuButtons[0] * 0.9, ClientVars.Styles.Colors.MainMenuButtons[1] * 0.9, ClientVars.Styles.Colors.MainMenuButtons[2] * 0.9, ClientVars.Styles.Colors.MainMenuButtons[3] * 0.9);
	}

	if (ImGui::Button(name, ImVec2((MENU_SIZE_X - 15) / TAB_COUNT, 25)))
	{
		*v = tab_id;
	}
	style.Colors[ImGuiCol_ButtonActive] = oldbuttonactive;
	style.Colors[ImGuiCol_ButtonHovered] = oldbuttonhovered;
	style.Colors[ImGuiCol_Button] = oldbutton;
	style.Colors[ImGuiCol_Text] = oldtext;

}
void SubTab(const char* name, int* v, int tab_id) {

	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4 oldtext = style.Colors[ImGuiCol_Text];
	ImVec4 oldbutton = style.Colors[ImGuiCol_Button];
	ImVec4 oldbuttonhovered = style.Colors[ImGuiCol_ButtonHovered];
	ImVec4 oldbuttonactive = style.Colors[ImGuiCol_ButtonActive];
	if (tab_id != 0)
	{
		ImGui::SameLine();
	}
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(ClientVars.Styles.Colors.GunMenuButtons[0] * 0.8, ClientVars.Styles.Colors.GunMenuButtons[1] * 0.8, ClientVars.Styles.Colors.GunMenuButtons[2] * 0.8, ClientVars.Styles.Colors.GunMenuButtons[3] * 0.8);
	style.Colors[ImGuiCol_Button] = ImVec4(ClientVars.Styles.Colors.GunMenuButtons[0], ClientVars.Styles.Colors.GunMenuButtons[1], ClientVars.Styles.Colors.GunMenuButtons[2], ClientVars.Styles.Colors.GunMenuButtons[3]);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(ClientVars.Styles.Colors.GunMenuButtons[0] * 0.8, ClientVars.Styles.Colors.GunMenuButtons[1] * 0.8, ClientVars.Styles.Colors.GunMenuButtons[2] * 0.8, ClientVars.Styles.Colors.GunMenuButtons[3] * 0.8);
	style.Colors[ImGuiCol_Text] = ImVec4(ClientVars.Styles.Colors.Text[0] * 0.5, ClientVars.Styles.Colors.Text[1] * 0.5, ClientVars.Styles.Colors.Text[2] * 0.5, ClientVars.Styles.Colors.Text[3] * 0.5);

	if (*v == tab_id) {
		style.Colors[ImGuiCol_Text] = ImVec4(ClientVars.Styles.Colors.Text[0], ClientVars.Styles.Colors.Text[1], ClientVars.Styles.Colors.Text[2], ClientVars.Styles.Colors.Text[3]);
	}
	if (ImGui::Button(name, ImVec2((MENU_SIZE_X - 25) / SUBTAB_COUNT, 35)))
	{
		*v = tab_id;
	}
	style.Colors[ImGuiCol_ButtonActive] = oldbuttonactive;
	style.Colors[ImGuiCol_ButtonHovered] = oldbuttonhovered;
	style.Colors[ImGuiCol_Button] = oldbutton;
	style.Colors[ImGuiCol_Text] = oldtext;

}

bool Contains(const std::string &word, const std::string &sentence) {
	if (word == "" || sentence == "")
		return true;

	return sentence.find(word) != std::string::npos;
}

std::string ToLower(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);

	return str;
}


namespace DXM
{
	int aatype = 0;
	int aatypelegit = 0;

	void FullUpdate()
	{
		ConVar* fullupdate = Interfaces.g_ICVars->FindVar("cl_fullupdate");
		fullupdate->nFlags &= ~FCVAR_CHEAT;
		Interfaces.pEngine->ClientCmd_Unrestricted("cl_fullupdate", 0);
	}

	void Menu()
	{
		POINT Mouse;
		POINT mp;
		GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x;
		Mouse.y = mp.y;
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos.x = (float)(mp.x);
		io.MousePos.y = (float)(mp.y);
		auto& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_WindowBg] = ImVec4(ClientVars.Styles.Colors.Menuborder[0], ClientVars.Styles.Colors.Menuborder[1], ClientVars.Styles.Colors.Menuborder[2], ClientVars.Styles.Colors.Menuborder[3]);

		style.Colors[ImGuiCol_PopupBg] = ImVec4(ClientVars.Styles.Colors.MenuBackground[0], ClientVars.Styles.Colors.MenuBackground[1], ClientVars.Styles.Colors.MenuBackground[2], ClientVars.Styles.Colors.MenuBackground[3]);

		style.Colors[ImGuiCol_Border] = ImVec4(ClientVars.Styles.Colors.Border[0], ClientVars.Styles.Colors.Border[1], ClientVars.Styles.Colors.Border[2], ClientVars.Styles.Colors.Border[3]);
		style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];

		style.Colors[ImGuiCol_ButtonActive] = ImVec4(ClientVars.Styles.Colors.Controls[0] * 0.9, ClientVars.Styles.Colors.Controls[1] * 0.9, ClientVars.Styles.Colors.Controls[2] * 0.9, ClientVars.Styles.Colors.Controls[3] * 0.9);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(ClientVars.Styles.Colors.Controls[0] * 0.8, ClientVars.Styles.Colors.Controls[1] * 0.8, ClientVars.Styles.Colors.Controls[2] * 0.8, ClientVars.Styles.Colors.Controls[3] * 0.8);
		style.Colors[ImGuiCol_Button] = ImVec4(ClientVars.Styles.Colors.Controls[0] * 0.6, ClientVars.Styles.Colors.Controls[1] * 0.6, ClientVars.Styles.Colors.Controls[2] * 0.6, ClientVars.Styles.Colors.Controls[3] * 0.6);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(ClientVars.Styles.Colors.Controls[0] * 0.8, ClientVars.Styles.Colors.Controls[1] * 0.8, ClientVars.Styles.Colors.Controls[2] * 0.8, ClientVars.Styles.Colors.Controls[3] * 0.8);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(ClientVars.Styles.Colors.Controls[0] * 0.8, ClientVars.Styles.Colors.Controls[1] * 0.8, ClientVars.Styles.Colors.Controls[2] * 0.8, ClientVars.Styles.Colors.Controls[3]);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(ClientVars.Styles.Colors.Controls[0], ClientVars.Styles.Colors.Controls[1], ClientVars.Styles.Colors.Controls[2], ClientVars.Styles.Colors.Controls[3]);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(ClientVars.Styles.Colors.Controls[0], ClientVars.Styles.Colors.Controls[1], ClientVars.Styles.Colors.Controls[2], ClientVars.Styles.Colors.Controls[3]);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(ClientVars.Styles.Colors.Controls[0] * 0.9, ClientVars.Styles.Colors.Controls[1] * 0.9, ClientVars.Styles.Colors.Controls[2] * 0.9, ClientVars.Styles.Colors.Controls[3]);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(ClientVars.Styles.Colors.Controls[0] * 0.8, ClientVars.Styles.Colors.Controls[1] * 0.8, ClientVars.Styles.Colors.Controls[2] * 0.8, ClientVars.Styles.Colors.Controls[3]);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(ClientVars.Styles.Colors.Controls[0] * 0.8, ClientVars.Styles.Colors.Controls[1] * 0.8, ClientVars.Styles.Colors.Controls[2] * 0.8, ClientVars.Styles.Colors.Controls[3]);
		style.Colors[ImGuiCol_CheckMarkBg] = ImVec4(ClientVars.Styles.Colors.Controls[0] * 0.8, ClientVars.Styles.Colors.Controls[1] * 0.8, ClientVars.Styles.Colors.Controls[2] * 0.8, ClientVars.Styles.Colors.Controls[3]);
		style.Colors[ImGuiCol_CheckMarkHover] = ImVec4(ClientVars.Styles.Colors.Controls[0] * 0.9, ClientVars.Styles.Colors.Controls[1] * 0.9, ClientVars.Styles.Colors.Controls[2] * 0.9, ClientVars.Styles.Colors.Controls[3] * 0.9);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(ClientVars.Styles.Colors.Controls[0] * 0.6, ClientVars.Styles.Colors.Controls[1] * 0.6, ClientVars.Styles.Colors.Controls[2] * 0.6, ClientVars.Styles.Colors.Controls[3] * 0.6);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(ClientVars.Styles.Colors.Controls[0] * 0.8, ClientVars.Styles.Colors.Controls[1] * 0.8, ClientVars.Styles.Colors.Controls[2] * 0.8, ClientVars.Styles.Colors.Controls[3] * 0.8);
		style.Colors[ImGuiCol_Header] = ImVec4(ClientVars.Styles.Colors.Controls[0] * 0.8, ClientVars.Styles.Colors.Controls[1] * 0.8, ClientVars.Styles.Colors.Controls[2] * 0.8, ClientVars.Styles.Colors.Controls[3] * 0.8);

		style.Colors[ImGuiCol_Text] = ImVec4(ClientVars.Styles.Colors.Text[0], ClientVars.Styles.Colors.Text[1], ClientVars.Styles.Colors.Text[2], ClientVars.Styles.Colors.Text[3]);
		style.Colors[ImGuiCol_CheckMark] = style.Colors[ImGuiCol_Text];

		bool open = true;
		ImVec4 defaultborder = style.Colors[ImGuiCol_Border];
		style.Colors[ImGuiCol_Border] = style.Colors[ImGuiCol_WindowBg];
		ImGui::PushFont(fontskek.tahoma);
		if (!ClientVars.Misc.Antiuntrustedproxy && !GVars.UTchecked)
		{
			ImGui::OpenPopup("Are you sure?");
			bool yeet = true;
			if (ImGui::BeginPopupModal("Are you sure?", &yeet, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar))
			{
				ImGui::Text("Are you sure that you want to disable anti untrusted?\nThis will get you untrusted banned if you are on vac secured servers.");
				if (ImGui::Button("Yes"))
				{
					GVars.UTchecked = true;
					ClientVars.Misc.Antiuntrusted = false;
					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if (ImGui::Button("No"))
				{
					GVars.UTchecked = false;
					ClientVars.Misc.Antiuntrustedproxy = true;
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
		}
		if (ClientVars.Misc.Antiuntrustedproxy)
		{
			ClientVars.Misc.Antiuntrusted = true;
			GVars.UTchecked = false;
		}

		static int current_tab = 0;
		ImGui::SetNextWindowPosCenter(ImGuiSetCond_Always);
		ImGui::Begin(charenc(u8"KalkonenWare"), &open, ImVec2(MENU_SIZE_X, MENU_SIZE_Y), 0.7f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
		style.WindowPadding = ImVec2(0.f, 0.f);
		style.Colors[ImGuiCol_Border] = defaultborder;
		ImGui::BeginChild(charenc("##tabs"), ImVec2(MENU_SIZE_X - 15, MENU_SIZE_Y - 15), true, ImGuiWindowFlags_AlwaysUseWindowPadding);

		style.FrameBorderSize = 0.f;
		ImVec2 defaultspacing = style.ItemSpacing;
		style.ItemSpacing = ImVec2(0.f, 0.f);


		ImGui::PushFont(fontskek.impact);
		Tab(charenc("RAGE"), &current_tab, 0);
		Tab(charenc("LEGIT"), &current_tab, 1);
		Tab(charenc("VISUALS"), &current_tab, 2);
		Tab(charenc("MISC"), &current_tab, 3);
		Tab(charenc("STYLE"), &current_tab, 4);
		ImGui::PopFont();
		style.WindowPadding = ImVec2(8.f, 8.f);
		style.ItemSpacing = defaultspacing;
		ImGui::BeginChild(charenc("##main"), ImVec2(-1, -1), false, ImGuiWindowFlags_AlwaysUseWindowPadding);
		if (current_tab == 0)
		{

			static int subtab0 = 0;
			style.WindowPadding = ImVec2(8.f, 8.f);
			ImGui::BeginChild(charenc("##0groupbox0"), ImVec2(655 / 3, ImGui::GetContentRegionAvail().y - 35), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Text(charenc("Ragebot ~ General"));
			ImGui::Separator();
			ImGui::Checkbox(charenc("Ragebot Enable"), &ClientVars.Ragebot.Enable);
			//	ImGui::Checkbox(charenc("Aimstep"), &ClientVars.Ragebot.aimstep);
			ImGui::SliderFloat(charenc("##FOV"), &ClientVars.Ragebot.FOV, 0, 180, "FOV: %.3f");
			ImGui::Checkbox(charenc("Autowall"), &ClientVars.Ragebot.Autowall);
			ImGui::Combo("Selection", &ClientVars.Ragebot.AimbotSelection, "FOV\0\rDistance\0\rCycle\0\rHealth\0\0", -1);
			ImGui::Checkbox(charenc("Autopistol"), &ClientVars.Ragebot.AutoPistol);
			ImGui::Checkbox(charenc("pSilent"), &ClientVars.Ragebot.pSilent);
			ImGui::Checkbox(charenc("Autoshoot"), &ClientVars.Ragebot.autofire);
			ImGui::Checkbox(charenc("NoRecoil"), &ClientVars.Ragebot.NoRecoil);
			ImGui::Checkbox(charenc("Position Adjustment"), &ClientVars.Ragebot.BackTrack); 
			ImGui::Checkbox(charenc("Autoscope"), &ClientVars.Ragebot.autoscope);
			ImGui::Combo("Yaw Resolver", &ClientVars.Ragebot.Resolver, "Off\0\rPrediction\0\Beta Resolver\0\rBruteforce\0\rBasic Test\0\0", -1);
			ImGui::Combo("Pitch Resolver", &ClientVars.Ragebot.ResolvePitch, "Off\0\rInverse real\0\rBruteforce\0\0", -1);
			ImGui::Separator();
			ImGui::Combo(charenc("Override Resolver"), &ClientVars.Ragebot.overrideresolver, keyNames, ARRAYSIZE(keyNames));
			ImGui::SliderInt(charenc("##overrideresolver"), &ClientVars.Ragebot.overrideradd, -180, 180, "Override Add: %0.f");
			style.FrameBorderSize = 0.f;
			ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(charenc("##0groupbox1"), ImVec2(655 / 3, ImGui::GetContentRegionAvail().y - 35), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			switch (subtab0) {
				case 0: {
					ImGui::Text(charenc("Pistol ~ Weapon config"));
					ImGui::Separator();
					ImGui::Combo("Hitbox", &ClientVars.Ragebot.Weapons.Pistol.Hitbox, "Head\0\rNeck\0\rChest\0\rPelvis\0\rStomach\0\0", -1);
					ImGui::Combo("Hitscan", &ClientVars.Ragebot.Weapons.Pistol.Hitscan.strength, "Disabled\0\rRegular\0\rMedium\0\rExtreme\0\0", -1);
					ImGui::SliderInt(charenc("##Hitchance"), &ClientVars.Ragebot.Weapons.Pistol.HitChance, 0, 100, "Hitchance: %0.f");
					ImGui::SliderInt(charenc("##Minimum Damage"), &ClientVars.Ragebot.Weapons.Pistol.MinDmg, 0, 100, "Minimum damage: %0.f");
					ImGui::SliderFloat(charenc("##headscale"), &ClientVars.Ragebot.Weapons.Pistol.Headscale, 0.f, 1.f, "Head Scale: %.2f");
					ImGui::SliderFloat(charenc("##bodyscale"), &ClientVars.Ragebot.Weapons.Pistol.Bodyscale, 0.f, 1.f, "Body Scale: %.2f");
					ImGui::Separator();
					ImGui::Text("Scan:");
					ImGui::Selectable(charenc("Head"), &ClientVars.Ragebot.Weapons.Pistol.Hitscan.head);
					ImGui::Selectable(charenc("Neck"), &ClientVars.Ragebot.Weapons.Pistol.Hitscan.neck);
					ImGui::Selectable(charenc("Arms"), &ClientVars.Ragebot.Weapons.Pistol.Hitscan.arms);
					ImGui::Selectable(charenc("Chest"), &ClientVars.Ragebot.Weapons.Pistol.Hitscan.chest);
					ImGui::Selectable(charenc("Stomach"), &ClientVars.Ragebot.Weapons.Pistol.Hitscan.stomach);
					ImGui::Selectable(charenc("Pelvis"), &ClientVars.Ragebot.Weapons.Pistol.Hitscan.pelvis);
					ImGui::Selectable(charenc("Legs"), &ClientVars.Ragebot.Weapons.Pistol.Hitscan.legs);
					ImGui::Selectable(charenc("Feet"), &ClientVars.Ragebot.Weapons.Pistol.Hitscan.feet);

					ImGui::Separator();
					ImGui::Checkbox(charenc("Prefer body if lethal"), &ClientVars.Ragebot.Weapons.Pistol.baimiflethal);


					break;
				}
				case 1: {
					ImGui::Text(charenc("Sniper ~ Weapon config"));
					ImGui::Separator();
					ImGui::Combo("Hitbox", &ClientVars.Ragebot.Weapons.Sniper.Hitbox, "Head\0\rNeck\0\rChest\0\rPelvis\0\rStomach\0\0", -1);
					ImGui::Combo("Hitscan", &ClientVars.Ragebot.Weapons.Sniper.Hitscan.strength, "Disabled\0\rRegular\0\rMedium\0\rExtreme\0\0", -1);
					ImGui::SliderInt(charenc("##Hitchance"), &ClientVars.Ragebot.Weapons.Sniper.HitChance, 0, 100, "Hitchance: %0.f");
					ImGui::SliderInt(charenc("##Minimum Damage"), &ClientVars.Ragebot.Weapons.Sniper.MinDmg, 0, 100, "Minimum damage: %0.f");
					ImGui::SliderFloat(charenc("##headscale"), &ClientVars.Ragebot.Weapons.Sniper.Headscale, 0.f, 1.f, "Head Scale: %.2f");
					ImGui::SliderFloat(charenc("##bodyscale"), &ClientVars.Ragebot.Weapons.Sniper.Bodyscale, 0.f, 1.f, "Body Scale: %.2f");
					ImGui::Separator();
					ImGui::Text("Scan:");
					ImGui::Selectable(charenc("Head"), &ClientVars.Ragebot.Weapons.Sniper.Hitscan.head);
					ImGui::Selectable(charenc("Neck"), &ClientVars.Ragebot.Weapons.Sniper.Hitscan.neck);
					ImGui::Selectable(charenc("Arms"), &ClientVars.Ragebot.Weapons.Sniper.Hitscan.arms);
					ImGui::Selectable(charenc("Chest"), &ClientVars.Ragebot.Weapons.Sniper.Hitscan.chest);
					ImGui::Selectable(charenc("Stomach"), &ClientVars.Ragebot.Weapons.Sniper.Hitscan.stomach);
					ImGui::Selectable(charenc("Pelvis"), &ClientVars.Ragebot.Weapons.Sniper.Hitscan.pelvis);
					ImGui::Selectable(charenc("Legs"), &ClientVars.Ragebot.Weapons.Sniper.Hitscan.legs);
					ImGui::Selectable(charenc("Feet"), &ClientVars.Ragebot.Weapons.Sniper.Hitscan.feet);

					ImGui::Separator();
					ImGui::Checkbox(charenc("Prefer body if lethal"), &ClientVars.Ragebot.Weapons.Sniper.baimiflethal);


					break;
				}
				case 2: {
					ImGui::Text(charenc("AutoSniper ~ Weapon config"));
					ImGui::Separator();
					ImGui::Combo("Hitbox", &ClientVars.Ragebot.Weapons.AutoSniper.Hitbox, "Head\0\rNeck\0\rChest\0\rPelvis\0\rStomach\0\0", -1);
					ImGui::Combo("Hitscan", &ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.strength, "Disabled\0\rRegular\0\rMedium\0\rExtreme\0\0", -1);
					ImGui::SliderInt(charenc("##Hitchance"), &ClientVars.Ragebot.Weapons.AutoSniper.HitChance, 0, 100, "Hitchance: %0.f");
					ImGui::SliderInt(charenc("##Minimum Damage"), &ClientVars.Ragebot.Weapons.AutoSniper.MinDmg, 0, 100, "Minimum damage: %0.f");
					ImGui::SliderFloat(charenc("##headscale"), &ClientVars.Ragebot.Weapons.AutoSniper.Headscale, 0.f, 1.f, "Head Scale: %.2f");
					ImGui::SliderFloat(charenc("##bodyscale"), &ClientVars.Ragebot.Weapons.AutoSniper.Bodyscale, 0.f, 1.f, "Body Scale: %.2f");
					ImGui::Separator();
					ImGui::Text("Scan:");
					ImGui::Selectable(charenc("Head"), &ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.head);
					ImGui::Selectable(charenc("Neck"), &ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.neck);
					ImGui::Selectable(charenc("Arms"), &ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.arms);
					ImGui::Selectable(charenc("Chest"), &ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.chest);
					ImGui::Selectable(charenc("Stomach"), &ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.stomach);
					ImGui::Selectable(charenc("Pelvis"), &ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.pelvis);
					ImGui::Selectable(charenc("Legs"), &ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.legs);
					ImGui::Selectable(charenc("Feet"), &ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.feet);

					ImGui::Separator();
					ImGui::Checkbox(charenc("Prefer body if lethal"), &ClientVars.Ragebot.Weapons.AutoSniper.baimiflethal);


					break;
				}
				case 3: {
					ImGui::Text(charenc("Rifle ~ Weapon config"));
					ImGui::Separator();
					ImGui::Combo("Hitbox", &ClientVars.Ragebot.Weapons.Rifle.Hitbox, "Head\0\rNeck\0\rChest\0\rPelvis\0\rStomach\0\0", -1);
					ImGui::Combo("Hitscan", &ClientVars.Ragebot.Weapons.Rifle.Hitscan.strength, "Disabled\0\rRegular\0\rMedium\0\rExtreme\0\0", -1);
					ImGui::SliderInt(charenc("##Hitchance"), &ClientVars.Ragebot.Weapons.Rifle.HitChance, 0, 100, "Hitchance: %0.f");
					ImGui::SliderInt(charenc("##Minimum Damage"), &ClientVars.Ragebot.Weapons.Rifle.MinDmg, 0, 100, "Minimum damage: %0.f");
					ImGui::SliderFloat(charenc("##headscale"), &ClientVars.Ragebot.Weapons.Rifle.Headscale, 0.f, 1.f, "Head Scale: %.2f");
					ImGui::SliderFloat(charenc("##bodyscale"), &ClientVars.Ragebot.Weapons.Rifle.Bodyscale, 0.f, 1.f, "Body Scale: %.2f");
					ImGui::Separator();
					ImGui::Text("Scan:");
					ImGui::Selectable(charenc("Head"), &ClientVars.Ragebot.Weapons.Rifle.Hitscan.head);
					ImGui::Selectable(charenc("Neck"), &ClientVars.Ragebot.Weapons.Rifle.Hitscan.neck);
					ImGui::Selectable(charenc("Arms"), &ClientVars.Ragebot.Weapons.Rifle.Hitscan.arms);
					ImGui::Selectable(charenc("Chest"), &ClientVars.Ragebot.Weapons.Rifle.Hitscan.chest);
					ImGui::Selectable(charenc("Stomach"), &ClientVars.Ragebot.Weapons.Rifle.Hitscan.stomach);
					ImGui::Selectable(charenc("Pelvis"), &ClientVars.Ragebot.Weapons.Rifle.Hitscan.pelvis);
					ImGui::Selectable(charenc("Legs"), &ClientVars.Ragebot.Weapons.Rifle.Hitscan.legs);
					ImGui::Selectable(charenc("Feet"), &ClientVars.Ragebot.Weapons.Rifle.Hitscan.feet);

					ImGui::Separator();
					ImGui::Checkbox(charenc("Prefer body if lethal"), &ClientVars.Ragebot.Weapons.Rifle.baimiflethal);


					break;
				}
				case 4: {
					ImGui::Text(charenc("SMG ~ Weapon config"));
					ImGui::Separator();
					ImGui::Combo("Hitbox", &ClientVars.Ragebot.Weapons.SMG.Hitbox, "Head\0\rNeck\0\rChest\0\rPelvis\0\rStomach\0\0", -1);
					ImGui::Combo("Hitscan", &ClientVars.Ragebot.Weapons.SMG.Hitscan.strength, "Disabled\0\rRegular\0\rMedium\0\rExtreme\0\0", -1);
					ImGui::SliderInt(charenc("##Hitchance"), &ClientVars.Ragebot.Weapons.SMG.HitChance, 0, 100, "Hitchance: %0.f");
					ImGui::SliderInt(charenc("##Minimum Damage"), &ClientVars.Ragebot.Weapons.SMG.MinDmg, 0, 100, "Minimum damage: %0.f");
					ImGui::SliderFloat(charenc("##headscale"), &ClientVars.Ragebot.Weapons.SMG.Headscale, 0.f, 1.f, "Head Scale: %.2f");
					ImGui::SliderFloat(charenc("##bodyscale"), &ClientVars.Ragebot.Weapons.SMG.Bodyscale, 0.f, 1.f, "Body Scale: %.2f");
					ImGui::Separator();
					ImGui::Text("Scan:");
					ImGui::Selectable(charenc("Head"), &ClientVars.Ragebot.Weapons.SMG.Hitscan.head);
					ImGui::Selectable(charenc("Neck"), &ClientVars.Ragebot.Weapons.SMG.Hitscan.neck);
					ImGui::Selectable(charenc("Arms"), &ClientVars.Ragebot.Weapons.SMG.Hitscan.arms);
					ImGui::Selectable(charenc("Chest"), &ClientVars.Ragebot.Weapons.SMG.Hitscan.chest);
					ImGui::Selectable(charenc("Stomach"), &ClientVars.Ragebot.Weapons.SMG.Hitscan.stomach);
					ImGui::Selectable(charenc("Pelvis"), &ClientVars.Ragebot.Weapons.SMG.Hitscan.pelvis);
					ImGui::Selectable(charenc("Legs"), &ClientVars.Ragebot.Weapons.SMG.Hitscan.legs);
					ImGui::Selectable(charenc("Feet"), &ClientVars.Ragebot.Weapons.SMG.Hitscan.feet);

					ImGui::Separator();
					ImGui::Checkbox(charenc("Prefer body if lethal"), &ClientVars.Ragebot.Weapons.SMG.baimiflethal);


					break;
				}
				case 5: {
					ImGui::Text(charenc("Shotgun ~ Weapon config"));
					ImGui::Separator();
					ImGui::Combo("Hitbox", &ClientVars.Ragebot.Weapons.Shotgun.Hitbox, "Head\0\rNeck\0\rChest\0\rPelvis\0\rStomach\0\0", -1);
					ImGui::Combo("Hitscan", &ClientVars.Ragebot.Weapons.Shotgun.Hitscan.strength, "Disabled\0\rRegular\0\rMedium\0\rExtreme\0\0", -1);
					ImGui::SliderInt(charenc("##Hitchance"), &ClientVars.Ragebot.Weapons.Shotgun.HitChance, 0, 100, "Hitchance: %0.f");
					ImGui::SliderInt(charenc("##Minimum Damage"), &ClientVars.Ragebot.Weapons.Shotgun.MinDmg, 0, 100, "Minimum damage: %0.f");
					ImGui::SliderFloat(charenc("##headscale"), &ClientVars.Ragebot.Weapons.Shotgun.Headscale, 0.f, 1.f, "Head Scale: %.2f");
					ImGui::SliderFloat(charenc("##bodyscale"), &ClientVars.Ragebot.Weapons.Shotgun.Bodyscale, 0.f, 1.f, "Body Scale: %.2f");
					ImGui::Separator();
					ImGui::Text("Scan:");
					ImGui::Selectable(charenc("Head"), &ClientVars.Ragebot.Weapons.Shotgun.Hitscan.head);
					ImGui::Selectable(charenc("Neck"), &ClientVars.Ragebot.Weapons.Shotgun.Hitscan.neck);
					ImGui::Selectable(charenc("Arms"), &ClientVars.Ragebot.Weapons.Shotgun.Hitscan.arms);
					ImGui::Selectable(charenc("Chest"), &ClientVars.Ragebot.Weapons.Shotgun.Hitscan.chest);
					ImGui::Selectable(charenc("Stomach"), &ClientVars.Ragebot.Weapons.Shotgun.Hitscan.stomach);
					ImGui::Selectable(charenc("Pelvis"), &ClientVars.Ragebot.Weapons.Shotgun.Hitscan.pelvis);
					ImGui::Selectable(charenc("Legs"), &ClientVars.Ragebot.Weapons.Shotgun.Hitscan.legs);
					ImGui::Selectable(charenc("Feet"), &ClientVars.Ragebot.Weapons.Shotgun.Hitscan.feet);

					ImGui::Separator();
					ImGui::Checkbox(charenc("Prefer body if lethal"), &ClientVars.Ragebot.Weapons.Shotgun.baimiflethal);


					break;
				}
			}
			style.FrameBorderSize = 0.f;
			
			ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(charenc("##1groupbox2"), ImVec2((655 / 3) - 1, ImGui::GetContentRegionAvail().y - 35), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Text(charenc("AntiAims ~ General"));
			ImGui::Separator();
			ImGui::Checkbox(charenc("AntiAim"), &ClientVars.AntiAim.enabled);

			if (ImGui::Button("Stand"))
				aatype = 0;

			ImGui::SameLine();

			if (ImGui::Button("Move"))
				aatype = 1;

			ImGui::SameLine();

			if (ImGui::Button("In Air"))
				aatype = 2;

			ImGui::SameLine();

			if (ImGui::Button("Misc"))
				aatype = 3;
			
			switch(aatype){
				case 0: {
					ImGui::Text(charenc("AntiAims ~ Stand"));
					ImGui::Separator();
					ImGui::Combo("Pitch", &ClientVars.AntiAim.Stand.Pitch, "Off\0\rEmotion\0\rUp\0\rFake Up\0\rFake Down\0\rFake Zero\0\rSwap\0\rCustom\0\0", -1);
					ImGui::SliderInt(charenc("##standrealpitch"), &ClientVars.AntiAim.Stand.PitchAdd, -89, 89, "Custom Pitch: %0.f");
					ImGui::Combo("Real Yaw", &ClientVars.AntiAim.Stand.Yaw, "Off\0\rRandom\0\rSpinbot\0\rManual LBY Switch\0\rJitter\0\rSwitch\0\rStatic\0\rLower Body\0\rFreestanding\0\0", -1);
					ImGui::SliderInt(charenc("##standrealyawadder"), &ClientVars.AntiAim.Stand.YawAdd, -180, 180, "Real Adder: %0.f");
					ImGui::Combo("Fake Yaw", &ClientVars.AntiAim.Stand.Fake, "Off\0\rRandom\0\rSpinbot\0\rManual Switch\0\rJitter\0\rSwitch\0\rStatic\0\rLower Body\0\rFreestanding\0\rInverse\0\0", -1);
					ImGui::SliderInt(charenc("##standfakeyawadder"), &ClientVars.AntiAim.Stand.FakeAdd, -180, 180, "Fake Adder: %0.f");
					break;
				}

				case 1: {
					ImGui::Text(charenc("AntiAims ~ Move"));
					ImGui::Separator();
					ImGui::Combo("Pitch", &ClientVars.AntiAim.Move.Pitch, "Off\0\rEmotion\0\rUp\0\rFake Up\0\rFake Down\0\rFake Zero\0\rSwap\0\rCustom\0\0", -1);
					ImGui::SliderInt(charenc("##moverealpitch"), &ClientVars.AntiAim.Move.PitchAdd, -89, 89, "Custom Pitch: %0.f");
					ImGui::Combo("Real Yaw", &ClientVars.AntiAim.Move.Yaw, "Off\0\rRandom\0\rSpinbot\0\rManual Switch\0\rJitter\0\rSwitch\0\rStatic\0\rLower Body\0\rFreestanding\0\0", -1);
					ImGui::SliderInt(charenc("##moverealyawadder"), &ClientVars.AntiAim.Move.YawAdd, -180, 180, "Real Adder: %0.f");
					ImGui::Combo("Fake Yaw", &ClientVars.AntiAim.Move.Fake, "Off\0\rRandom\0\rSpinbot\0\rManual Switch\0\rJitter\0\rSwitch\0\rStatic\0\rLower Body\0\rFreestanding\0\rInverse\0\0", -1);
					ImGui::SliderInt(charenc("##movefakeyawadder"), &ClientVars.AntiAim.Move.FakeAdd, -180, 180, "Fake Adder: %0.f");
					break;
				}

				case 2: {
					ImGui::Text(charenc("AntiAims ~ In Air"));
					ImGui::Separator();
					ImGui::Combo("Pitch", &ClientVars.AntiAim.Air.Pitch, "Off\0\rEmotion\0\rUp\0\rFake Up\0\rFake Down\0\rFake Zero\0\rSwap\0\rCustom\0\0", -1);
					ImGui::SliderInt(charenc("##inairrealpitch"), &ClientVars.AntiAim.Air.PitchAdd, -89, 89, "Custom Pitch: %0.f");
					ImGui::Combo("Real Yaw", &ClientVars.AntiAim.Air.Yaw, "Off\0\rRandom\0\rSpinbot\0\rManual Switch\0\rJitter\0\rSwitch\0\rStatic\0\rLower Body\0\rFreestanding\0\0", -1);
					ImGui::SliderInt(charenc("##inairrealyawadder"), &ClientVars.AntiAim.Air.YawAdd, -180, 180, "Real Adder: %0.f");
					ImGui::Combo("Fake Yaw", &ClientVars.AntiAim.Air.Fake, "Off\0\rRandom\0\rSpinbot\0\rManual Switch\0\rJitter\0\rSwitch\0\rStatic\0\rLower Body\0\rFreestanding\0\rInverse\0\0", -1);
					ImGui::SliderInt(charenc("##inairfakeyawadder"), &ClientVars.AntiAim.Air.FakeAdd, -180, 180, "Fake Adder: %0.f");
					break;
				}

				case 3: {
					ImGui::Text(charenc("AntiAims ~ Misc"));
					ImGui::Separator();
					ImGui::SliderInt(charenc("##lbydelta"), &ClientVars.AntiAim.Misc.lbyDelta, -180, 180, "LBY Delta: %0.f");
					ImGui::SliderFloat(charenc("##spinbotspeed"), &ClientVars.AntiAim.Misc.SpinbotSpeed, 0, 100, "Spinbot Speed: %0.f");
					ImGui::SliderFloat(charenc("##jitterspeed"), &ClientVars.AntiAim.Misc.JitterSpeed, 0, 100, "Jitter Speed: %0.f");
					ImGui::SliderInt(charenc("##jitterrange"), &ClientVars.AntiAim.Misc.JitterRange, -180, 180, "Jitter Range: %0.f");
					ImGui::SliderInt(charenc("##switchadd"), &ClientVars.AntiAim.Misc.SwitchAdd, -180, 180, "Switch Add: %0.f");
					ImGui::SliderFloat(charenc("##switchspeed"), &ClientVars.AntiAim.Misc.SwitchSpeed, 0, 100, "Switch Speed: %0.f");
					ImGui::Combo(charenc("FakeWalk"), &ClientVars.AntiAim.Misc.fakewalk, keyNames, ARRAYSIZE(keyNames));
					ImGui::Combo(charenc("Manual AA Left"), &ClientVars.AntiAim.Misc.leftAA, keyNames, ARRAYSIZE(keyNames));
					ImGui::Combo(charenc("Manual AA Right"), &ClientVars.AntiAim.Misc.rightAA, keyNames, ARRAYSIZE(keyNames));
					ImGui::Combo(charenc("Manual AA Down"), &ClientVars.AntiAim.Misc.downAA, keyNames, ARRAYSIZE(keyNames));
					//ImGui::Combo(charenc("Manual AA Up"), &ClientVars.AntiAim.Misc.upAA, keyNames, ARRAYSIZE(keyNames));
					ImGui::Checkbox(charenc("On grenades"), &ClientVars.AntiAim.OnGreandes);
					ImGui::Checkbox(charenc("On ladders"), &ClientVars.AntiAim.OnLadders);
					ImGui::Checkbox(charenc("On knife"), &ClientVars.AntiAim.OnKnife);
					break;
				}
			}
			style.FrameBorderSize = 0.f; ImGui::EndChild();

			style.ItemSpacing = ImVec2(0.f, 0.f);
			style.WindowPadding = ImVec2(0.f, 0.f);
			ImGui::BeginChild(charenc("##weaponcfg0"), ImVec2(670, 35), true);
			ImGui::PushFont(fontskek.icons);
			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.9f, 0.9f, 0.9f, 1.00f);
			SubTab(charenc(u8"\uE001"), &subtab0, 0);
			SubTab(charenc(u8"\uE009"), &subtab0, 1);
			SubTab(charenc(u8"\uE00B"), &subtab0, 2);
			SubTab(charenc(u8"\uE007"), &subtab0, 3);
			SubTab(charenc(u8"\uE011"), &subtab0, 4);
			SubTab(charenc(u8"\uE023"), &subtab0, 5);
			ImGui::PopFont();
			ImGui::EndChild();
			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(ClientVars.Styles.Colors.MenuBackground[0], ClientVars.Styles.Colors.MenuBackground[1], ClientVars.Styles.Colors.MenuBackground[2], ClientVars.Styles.Colors.MenuBackground[3]);
			style.WindowPadding = ImVec2(8.f, 8.f);
			style.ItemSpacing = defaultspacing;
		}
		if (current_tab == 1)
		{
			ImVec2 defaultspacing2 = style.ItemSpacing;
			static int subtab1 = 0;
			ImGui::BeginChild(charenc("##1groupbox0"), ImVec2(655 / 3, ImGui::GetContentRegionAvail().y - 35), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Text(charenc("Legitbot ~ General"));
			ImGui::Separator();
			ImGui::Checkbox(charenc("Enable"), &ClientVars.LegitBot.enable);
			ImGui::Checkbox(charenc("BackTrack"), &ClientVars.LegitBot.backtrack);
			ImGui::Separator();
			ImGui::Checkbox(charenc("Legit AntiAims"), &ClientVars.LegitBot.AntiAim.enabled);

			if (ImGui::Button("Stand"))
				aatypelegit = 0;

			ImGui::SameLine();

			if (ImGui::Button("Move"))
				aatypelegit = 1;

			ImGui::SameLine();

			if (ImGui::Button("In Air"))
				aatypelegit = 2;

			ImGui::SameLine();

			if (ImGui::Button("Misc"))
				aatypelegit = 3;

			switch (aatypelegit) {
			case 0: {
				ImGui::Text(charenc("AntiAims ~ Stand"));
				ImGui::Separator();
				ImGui::Combo("Real Yaw", &ClientVars.LegitBot.AntiAim.Stand.Yaw, "Off\0\rRandom\0\rSpinbot\0\rManual LBY Switch\0\rJitter\0\rSwitch\0\rStatic\0\rLower Body\0\rFreestanding\0\0", -1);
				ImGui::SliderInt(charenc("##moverealyawadder"), &ClientVars.LegitBot.AntiAim.Stand.YawAdd, -180, 180, "Real Adder: %0.f");
				break;
			}

			case 1: {
				ImGui::Text(charenc("AntiAims ~ Move"));
				ImGui::Separator();
				ImGui::Combo("Real Yaw", &ClientVars.LegitBot.AntiAim.Move.Yaw, "Off\0\rRandom\0\rSpinbot\0\rManual Switch\0\rJitter\0\rSwitch\0\rStatic\0\rLower Body\0\rFreestanding\0\0", -1);
				ImGui::SliderInt(charenc("##moverealyawadder"), &ClientVars.LegitBot.AntiAim.Move.YawAdd, -180, 180, "Real Adder: %0.f");
				break;
			}

			case 2: {
				ImGui::Text(charenc("AntiAims ~ In Air"));
				ImGui::Separator();
				ImGui::Combo("Real Yaw", &ClientVars.LegitBot.AntiAim.Air.Yaw, "Off\0\rRandom\0\rSpinbot\0\rManual Switch\0\rJitter\0\rSwitch\0\rStatic\0\rLower Body\0\rFreestanding\0\0", -1);
				ImGui::SliderInt(charenc("##moverealyawadder"), &ClientVars.LegitBot.AntiAim.Air.YawAdd, -180, 180, "Real Adder: %0.f");
				break;
			}

			case 3: {
				ImGui::Text(charenc("AntiAims ~ Misc"));
				ImGui::Separator();
				ImGui::SliderInt(charenc("##lbydelta"), &ClientVars.LegitBot.AntiAim.Misc.lbyDelta, -180, 180, "LBY Delta: %0.f");
				ImGui::SliderFloat(charenc("##spinbotspeed"), &ClientVars.LegitBot.AntiAim.Misc.SpinbotSpeed, 0, 100, "Spinbot Speed: %0.f");
				ImGui::SliderFloat(charenc("##jitterspeed"), &ClientVars.LegitBot.AntiAim.Misc.JitterSpeed, 0, 100, "Jitter Speed: %0.f");
				ImGui::SliderInt(charenc("##jitterrange"), &ClientVars.LegitBot.AntiAim.Misc.JitterRange, -180, 180, "Jitter Range: %0.f");
				ImGui::SliderInt(charenc("##switchadd"), &ClientVars.LegitBot.AntiAim.Misc.SwitchAdd, -180, 180, "Switch Add: %0.f");
				ImGui::SliderFloat(charenc("##switchspeed"), &ClientVars.LegitBot.AntiAim.Misc.SwitchSpeed, 0, 100, "Switch Speed: %0.f");
				ImGui::Combo(charenc("Manual AA Left"), &ClientVars.LegitBot.AntiAim.Misc.leftAA, keyNames, ARRAYSIZE(keyNames));
				ImGui::Combo(charenc("Manual AA Right"), &ClientVars.LegitBot.AntiAim.Misc.rightAA, keyNames, ARRAYSIZE(keyNames));
				ImGui::Combo(charenc("Manual AA Down"), &ClientVars.LegitBot.AntiAim.Misc.downAA, keyNames, ARRAYSIZE(keyNames));
				//ImGui::Combo(charenc("Manual AA Up"), &ClientVars.LegitBot.AntiAim.Misc.upAA, keyNames, ARRAYSIZE(keyNames));
				ImGui::Checkbox(charenc("On grenades"), &ClientVars.LegitBot.AntiAim.OnGreandes);
				ImGui::Checkbox(charenc("On ladders"), &ClientVars.LegitBot.AntiAim.OnLadders);
				ImGui::Checkbox(charenc("On knife"), &ClientVars.LegitBot.AntiAim.OnKnife);
				break;
			}
			}
			style.FrameBorderSize = 0.f; ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(charenc("##1groupbox1"), ImVec2(655 / 3, ImGui::GetContentRegionAvail().y - 35), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			switch (subtab1) {
			case 0: {
				ImGui::Text(charenc("Pistol ~ Aimbot"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Enable"), &ClientVars.LegitBot.Weapons.Pistol.enable);
				ImGui::Checkbox(charenc("On Key"), &ClientVars.LegitBot.Weapons.Pistol.onkey);
				ImGui::Combo(charenc("Key"), &ClientVars.LegitBot.Weapons.Pistol.key, keyNames, ARRAYSIZE(keyNames));
				ImGui::Combo("Hitbox", &ClientVars.LegitBot.Weapons.Pistol.hitbox, "Head\0\rNeck\0\rChest\0\rPelvis\0\rStomach\0\0", -1);
				ImGui::SliderFloat(charenc("##fov"), &ClientVars.LegitBot.Weapons.Pistol.fov, 0, 180, "FOV: %.3f");
				ImGui::SliderFloat(charenc("##smoothing"), &ClientVars.LegitBot.Weapons.Pistol.smoothing, 0, 100, "Smoothing: %.3f");
				ImGui::Checkbox(charenc("AutoWall"), &ClientVars.LegitBot.Weapons.Pistol.autowall);
				ImGui::Checkbox(charenc("Recoil Control"), &ClientVars.LegitBot.Weapons.Pistol.recoilcontrol);
				ImGui::Checkbox(charenc("Auto Pistol"), &ClientVars.LegitBot.Weapons.Pistol.autopistol);
				ImGui::Checkbox(charenc("Auto Revolver"), &ClientVars.LegitBot.Weapons.Pistol.autorevolver);
				break;
			}
			case 1: {
				ImGui::Text(charenc("Sniper ~ Aimbot"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Enable"), &ClientVars.LegitBot.Weapons.Sniper.enable);
				ImGui::Checkbox(charenc("On Key"), &ClientVars.LegitBot.Weapons.Sniper.onkey);
				ImGui::Combo(charenc("Key"), &ClientVars.LegitBot.Weapons.Sniper.key, keyNames, ARRAYSIZE(keyNames));
				ImGui::Combo("Hitbox", &ClientVars.LegitBot.Weapons.Sniper.hitbox, "Head\0\rNeck\0\rChest\0\rPelvis\0\rStomach\0\0", -1);
				ImGui::SliderFloat(charenc("##fov"), &ClientVars.LegitBot.Weapons.Sniper.fov, 0, 180, "FOV: %.3f");
				ImGui::SliderFloat(charenc("##smoothing"), &ClientVars.LegitBot.Weapons.Sniper.smoothing, 0, 100, "Smoothing: %.3f");
				ImGui::Checkbox(charenc("AutoWall"), &ClientVars.LegitBot.Weapons.Sniper.autowall);
				ImGui::Checkbox(charenc("Recoil Control"), &ClientVars.LegitBot.Weapons.Sniper.recoilcontrol);
				ImGui::Checkbox(charenc("AWP Baim"), &ClientVars.LegitBot.Weapons.Sniper.awpbaim);
				break;
			}
			case 2: {
				ImGui::Text(charenc("AutoSniper ~ Aimbot"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Enable"), &ClientVars.LegitBot.Weapons.AutoSniper.enable);
				ImGui::Checkbox(charenc("On Key"), &ClientVars.LegitBot.Weapons.AutoSniper.onkey);
				ImGui::Combo(charenc("Key"), &ClientVars.LegitBot.Weapons.AutoSniper.key, keyNames, ARRAYSIZE(keyNames));
				ImGui::Combo("Hitbox", &ClientVars.LegitBot.Weapons.AutoSniper.hitbox, "Head\0\rNeck\0\rChest\0\rPelvis\0\rStomach\0\0", -1);
				ImGui::SliderFloat(charenc("##fov"), &ClientVars.LegitBot.Weapons.AutoSniper.fov, 0, 180, "FOV: %.3f");
				ImGui::SliderFloat(charenc("##smoothing"), &ClientVars.LegitBot.Weapons.AutoSniper.smoothing, 0, 100, "Smoothing: %.3f");
				ImGui::Checkbox(charenc("AutoWall"), &ClientVars.LegitBot.Weapons.AutoSniper.autowall);
				ImGui::Checkbox(charenc("Recoil Control"), &ClientVars.LegitBot.Weapons.AutoSniper.recoilcontrol);
				break;
			}
			case 3: {
				ImGui::Text(charenc("Rifle ~ Aimbot"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Enable"), &ClientVars.LegitBot.Weapons.Rifle.enable);
				ImGui::Checkbox(charenc("On Key"), &ClientVars.LegitBot.Weapons.Rifle.onkey);
				ImGui::Combo(charenc("Key"), &ClientVars.LegitBot.Weapons.Rifle.key, keyNames, ARRAYSIZE(keyNames));
				ImGui::Combo("Hitbox", &ClientVars.LegitBot.Weapons.Rifle.hitbox, "Head\0\rNeck\0\rChest\0\rPelvis\0\rStomach\0\0", -1);
				ImGui::SliderFloat(charenc("##fov"), &ClientVars.LegitBot.Weapons.Rifle.fov, 0, 180, "FOV: %.3f");
				ImGui::SliderFloat(charenc("##smoothing"), &ClientVars.LegitBot.Weapons.Rifle.smoothing, 0, 100, "Smoothing: %.3f");
				ImGui::Checkbox(charenc("AutoWall"), &ClientVars.LegitBot.Weapons.Rifle.autowall);
				ImGui::Checkbox(charenc("Recoil Control"), &ClientVars.LegitBot.Weapons.Rifle.recoilcontrol);
				break;
			}
			case 4: {
				ImGui::Text(charenc("SMG ~ Aimbot"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Enable"), &ClientVars.LegitBot.Weapons.SMG.enable);
				ImGui::Checkbox(charenc("On Key"), &ClientVars.LegitBot.Weapons.SMG.onkey);
				ImGui::Combo(charenc("Key"), &ClientVars.LegitBot.Weapons.SMG.key, keyNames, ARRAYSIZE(keyNames));
				ImGui::Combo("Hitbox", &ClientVars.LegitBot.Weapons.SMG.hitbox, "Head\0\rNeck\0\rChest\0\rPelvis\0\rStomach\0\0", -1);
				ImGui::SliderFloat(charenc("##fov"), &ClientVars.LegitBot.Weapons.SMG.fov, 0, 180, "FOV: %.3f");
				ImGui::SliderFloat(charenc("##smoothing"), &ClientVars.LegitBot.Weapons.SMG.smoothing, 0, 100, "Smoothing: %.3f");
				ImGui::Checkbox(charenc("AutoWall"), &ClientVars.LegitBot.Weapons.SMG.autowall);
				ImGui::Checkbox(charenc("Recoil Control"), &ClientVars.LegitBot.Weapons.SMG.recoilcontrol);
				break;
			}
			case 5: {
				ImGui::Text(charenc("Shotgun ~ Aimbot"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Enable"), &ClientVars.LegitBot.Weapons.Shotgun.enable);
				ImGui::Checkbox(charenc("On Key"), &ClientVars.LegitBot.Weapons.Shotgun.onkey);
				ImGui::Combo(charenc("Key"), &ClientVars.LegitBot.Weapons.Shotgun.key, keyNames, ARRAYSIZE(keyNames));
				ImGui::Combo("Hitbox", &ClientVars.LegitBot.Weapons.Shotgun.hitbox, "Head\0\rNeck\0\rChest\0\rPelvis\0\rStomach\0\0", -1);
				ImGui::SliderFloat(charenc("##fov"), &ClientVars.LegitBot.Weapons.Shotgun.fov, 0, 180, "FOV: %.3f");
				ImGui::SliderFloat(charenc("##smoothing"), &ClientVars.LegitBot.Weapons.Shotgun.smoothing, 0, 100, "Smoothing: %.3f");
				ImGui::Checkbox(charenc("AutoWall"), &ClientVars.LegitBot.Weapons.Shotgun.autowall);
				ImGui::Checkbox(charenc("Recoil Control"), &ClientVars.LegitBot.Weapons.Shotgun.recoilcontrol);
				break;
			}
			}
			style.FrameBorderSize = 0.f; ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(charenc("##1groupbox2"), ImVec2((655 / 3) - 1, ImGui::GetContentRegionAvail().y - 35), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			switch (subtab1) {
			case 0: {
				ImGui::Text(charenc("Pistol ~ Triggerbot"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Enable"), &ClientVars.LegitBot.Weapons.Pistol.Triggerbot.enable);
				ImGui::Checkbox(charenc("On Key"), &ClientVars.LegitBot.Weapons.Pistol.Triggerbot.onkey);
				ImGui::Combo(charenc("Key"), &ClientVars.LegitBot.Weapons.Pistol.Triggerbot.key, keyNames, ARRAYSIZE(keyNames));
				ImGui::Combo("Hitbox", &ClientVars.LegitBot.Weapons.Pistol.Triggerbot.hitbox, "All\0\rHead\0\rChest\0\rStomach\0\0", -1);
				ImGui::SliderInt(charenc("##hitchance"), &ClientVars.LegitBot.Weapons.Pistol.Triggerbot.hitchance, 0, 100, "Hitchance: %.0f");
				ImGui::SliderInt(charenc("##delay"), &ClientVars.LegitBot.Weapons.Pistol.Triggerbot.delay, 0, 200, "Delay: %.0f");
				break;
			}
			case 1: {
				ImGui::Text(charenc("Sniper ~ Triggerbot"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Enable"), &ClientVars.LegitBot.Weapons.Sniper.Triggerbot.enable);
				ImGui::Checkbox(charenc("On Key"), &ClientVars.LegitBot.Weapons.Sniper.Triggerbot.onkey);
				ImGui::Combo(charenc("Key"), &ClientVars.LegitBot.Weapons.Sniper.Triggerbot.key, keyNames, ARRAYSIZE(keyNames));
				ImGui::Combo("Hitbox", &ClientVars.LegitBot.Weapons.Sniper.Triggerbot.hitbox, "All\0\rHead\0\rChest\0\rStomach\0\0", -1);
				ImGui::SliderInt(charenc("##hitchance"), &ClientVars.LegitBot.Weapons.Sniper.Triggerbot.hitchance, 0, 100, "Hitchance: %.0f");
				ImGui::SliderInt(charenc("##delay"), &ClientVars.LegitBot.Weapons.Sniper.Triggerbot.delay, 0, 200, "Delay: %.0f");
				break;
			}
			case 2: {
				ImGui::Text(charenc("AutoSniper ~ Triggerbot"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Enable"), &ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.enable);
				ImGui::Checkbox(charenc("On Key"), &ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.onkey);
				ImGui::Combo(charenc("Key"), &ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.key, keyNames, ARRAYSIZE(keyNames));
				ImGui::Combo("Hitbox", &ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.hitbox, "All\0\rHead\0\rChest\0\rStomach\0\0", -1);
				ImGui::SliderInt(charenc("##hitchance"), &ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.hitchance, 0, 100, "Hitchance: %.0f");
				ImGui::SliderInt(charenc("##delay"), &ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.delay, 0, 200, "Delay: %.0f");
				break;
			}
			case 3: {
				ImGui::Text(charenc("Rifle ~ Triggerbot"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Enable"), &ClientVars.LegitBot.Weapons.Rifle.Triggerbot.enable);
				ImGui::Checkbox(charenc("On Key"), &ClientVars.LegitBot.Weapons.Rifle.Triggerbot.onkey);
				ImGui::Combo(charenc("Key"), &ClientVars.LegitBot.Weapons.Rifle.Triggerbot.key, keyNames, ARRAYSIZE(keyNames));
				ImGui::Combo("Hitbox", &ClientVars.LegitBot.Weapons.Rifle.Triggerbot.hitbox, "All\0\rHead\0\rChest\0\rStomach\0\0", -1);
				ImGui::SliderInt(charenc("##hitchance"), &ClientVars.LegitBot.Weapons.Rifle.Triggerbot.hitchance, 0, 100, "Hitchance: %.0f");
				ImGui::SliderInt(charenc("##delay"), &ClientVars.LegitBot.Weapons.Rifle.Triggerbot.delay, 0, 200, "Delay: %.0f");
				break;
			}
			case 4: {
				ImGui::Text(charenc("SMG ~ Triggerbot"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Enable"), &ClientVars.LegitBot.Weapons.SMG.Triggerbot.enable);
				ImGui::Checkbox(charenc("On Key"), &ClientVars.LegitBot.Weapons.SMG.Triggerbot.onkey);
				ImGui::Combo(charenc("Key"), &ClientVars.LegitBot.Weapons.SMG.Triggerbot.key, keyNames, ARRAYSIZE(keyNames));
				ImGui::Combo("Hitbox", &ClientVars.LegitBot.Weapons.SMG.Triggerbot.hitbox, "All\0\rHead\0\rChest\0\rStomach\0\0", -1);
				ImGui::SliderInt(charenc("##hitchance"), &ClientVars.LegitBot.Weapons.SMG .Triggerbot.hitchance, 0, 100, "Hitchance: %.0f");
				ImGui::SliderInt(charenc("##delay"), &ClientVars.LegitBot.Weapons.SMG.Triggerbot.delay, 0, 200, "Delay: %.0f");
				break;
			}
			case 5: {
				ImGui::Text(charenc("Shotgun ~ Triggerbot"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Enable"), &ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.enable);
				ImGui::Checkbox(charenc("On Key"), &ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.onkey);
				ImGui::Combo(charenc("Key"), &ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.key, keyNames, ARRAYSIZE(keyNames));
				ImGui::Combo("Hitbox", &ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.hitbox, "All\0\rHead\0\rNeck\0\rChest\0\rPelvis\0\rStomach\0\0", -1);
				ImGui::SliderInt(charenc("##hitchance"), &ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.hitchance, 0, 100, "Hitchance: %.0f");
				ImGui::SliderInt(charenc("##delay"), &ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.delay, 0, 200, "Delay: %.0f");
				break;
			}
			}
			style.FrameBorderSize = 0.f; ImGui::EndChild();

			style.ItemSpacing = ImVec2(0.f, 0.f);
			style.WindowPadding = ImVec2(0.f, 0.f);
			ImGui::BeginChild(charenc("##weaponcfg1"), ImVec2(670, 35), true);
			ImGui::PushFont(fontskek.icons);
			SubTab(charenc(u8"\uE001 "), &subtab1, 0);
			SubTab(charenc(u8"\uE009 "), &subtab1, 1);
			SubTab(charenc(u8"\uE00B "), &subtab1, 2);
			SubTab(charenc(u8"\uE007 "), &subtab1, 3);
			SubTab(charenc(u8"\uE011 "), &subtab1, 4);
			SubTab(charenc(u8"\uE023"), &subtab1, 5);
			ImGui::PopFont();
			ImGui::EndChild();

			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(ClientVars.Styles.Colors.MenuBackground[0], ClientVars.Styles.Colors.MenuBackground[1], ClientVars.Styles.Colors.MenuBackground[2], ClientVars.Styles.Colors.MenuBackground[3]);
			style.WindowPadding = ImVec2(8.f, 8.f);
			style.ItemSpacing = defaultspacing2;
		}
		if (current_tab == 2)
		{

			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(ClientVars.Styles.Colors.MenuBackground[0], ClientVars.Styles.Colors.MenuBackground[1], ClientVars.Styles.Colors.MenuBackground[2], ClientVars.Styles.Colors.MenuBackground[3]);
			ImGui::BeginChild(charenc("##2groupbox0"), ImVec2(655 / 3, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Text(charenc("Visuals ~ Part 1"));
			ImGui::Separator();
			ImGui::Checkbox(charenc("ESP"), &ClientVars.Visual.BoundingBox);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##esp enemy", ClientVars.Col.EnemyESP, true, &ClientVars.Col.EnemyESPHB, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Checkbox(charenc("Team ESP"), &ClientVars.Visual.Showteam);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##esp team", ClientVars.Col.TeamESP, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview );
			ImGui::Checkbox(charenc("Aimlines"), &ClientVars.Visual.AimLine);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##esp aimlines", ClientVars.Col.Aimlines, true, &ClientVars.Col.EnemyAimlineHB, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Checkbox(charenc("Skeleton"), &ClientVars.Visual.Skeleton);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##esp skeleton", ClientVars.Col.Skeleton, true, &ClientVars.Col.EnemySkeletonHB, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			//ImGui::Checkbox(charenc("HeadBox"), &ClientVars.Visual.HeadBox);


			ImGui::Checkbox(charenc("Show Target"), &ClientVars.Visual.ShowTarget);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##ShowTarget", ClientVars.Col.ShowTarget, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);

			ImGui::Checkbox(charenc("Name"), &ClientVars.Visual.Name);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##Name", ClientVars.Col.NameESP, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Checkbox(charenc("Weapon"), &ClientVars.Visual.Weapon);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##Weapon", ClientVars.Col.WeaponESP, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Checkbox(charenc("Armor"), &ClientVars.Visual.Armor);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##Armor", ClientVars.Col.ArmorESP, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Checkbox(charenc("Vulnerabilities"), &ClientVars.Visual.Vulnerabilities);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##Vulnerabilities", ClientVars.Col.Vulnerabilities, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Checkbox(charenc("Health"), &ClientVars.Visual.Health);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##Health", ClientVars.Col.Health, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Checkbox(charenc("Money"), &ClientVars.Visual.Money);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##Money", ClientVars.Col.Money, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Checkbox(charenc("Callout"), &ClientVars.Visual.Callout);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##Callout", ClientVars.Col.Callout, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Checkbox(charenc("Ammo"), &ClientVars.Visual.Ammo);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##esp ammo", ClientVars.Col.Ammo, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Checkbox(charenc("Bullet Tracers"), &ClientVars.Visual.BulletTracers);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##Bullet Tracers", ClientVars.Col.BulletTracers, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Separator();
			ImGui::Checkbox(charenc("Angle Lines"), &ClientVars.Visual.AngleLines);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##Resolver ESP LBY", ClientVars.Col.AngleLinesLBY, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::SameLine(ImGui::GetWindowWidth() - 50);
			ImGui::ColorEdit3("##Resolver ESP REAL", ClientVars.Col.AngleLinesREAL, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::SameLine(ImGui::GetWindowWidth() - 75);
			ImGui::ColorEdit3("##Resolver ESP FAKE", ClientVars.Col.AngleLinesFAKE, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);

			ImGui::Checkbox(charenc("Resolver ESP"), &ClientVars.Visual.ResolverESP);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##Resolver ESP", ClientVars.Col.ResolverESP, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);

			ImGui::Checkbox(charenc("LBY Predictor"), &ClientVars.Visual.LBYPredictor);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##lbypred", ClientVars.Col.LbyPredictor, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Checkbox(charenc("Manual Arrows"), &ClientVars.Visual.ManualArrows);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##Manual Arrows Active", ClientVars.Col.ManualArrowsActive, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::SameLine(ImGui::GetWindowWidth() - 50);
			ImGui::ColorEdit3("##Manual Arrows Not", ClientVars.Col.ManualArrowsNotActive, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);

			ImGui::Checkbox(charenc("Ghost Chams"), &ClientVars.Visual.GhostChams);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##ghostchamscolors", ClientVars.Col.GhostChams, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Combo("Ghost Chams Mode", &ClientVars.Visual.GhostChamsMode, "Real\0\rFake\0\rLBY\0\0", -1);
			ImGui::Separator();
			ImGui::SliderFloat(charenc("##wallalpha"), &ClientVars.Visual.wallalpha, 0.f, 1.f, "Wall Alpha: %.2f");
			ImGui::SliderFloat(charenc("##proppalpha"), &ClientVars.Visual.propalpha, 0.f, 1.f, "Prop Alpha: %.2f");
			ImGui::SliderFloat(charenc("##modelpalpha"), &ClientVars.Visual.modelalpha, 0.f, 1.f, "Model Alpha: %.2f");


			ImGui::SliderFloat(charenc("##Nightmode"), &ClientVars.Visual.NightmodeVal, 0.f, 1.f, "Nightmode: %.2f");

			style.FrameBorderSize = 0.f; ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(charenc("##2groupbox1"), ImVec2(655 / 3, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Text(charenc("Visuals ~ Part 2"));
			ImGui::Separator();
			ImGui::Combo("Third Person Mode", &ClientVars.Visual.ThirdpersonMode, "Real\0\rFake\0\rLBY\0\0", -1);
			ImGui::SliderInt(charenc("##thirdpersondist"), &ClientVars.Visual.tpdist, 0, 500, "Third Person Dist: %0.f");
			ImGui::Combo(charenc("Third Person"), &ClientVars.Visual.Thirdperson, keyNames, ARRAYSIZE(keyNames));
			ImGui::Separator();
			ImGui::Checkbox(charenc("Dropped Weapons"), &ClientVars.Visual.Droppedguns);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##droppedweapons", ClientVars.Col.DroppedWeapons, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(charenc("Bomb ESP"), &ClientVars.Visual.Bomb);
			ImGui::Checkbox(charenc("Grenade ESP"), &ClientVars.Visual.Grenades);
			ImGui::Checkbox(charenc("Crosshair"), &ClientVars.Visual.Crosshair);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##esp crosshair", ClientVars.Col.Crosshair, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(charenc("Inaccuracy Crosshair"), &ClientVars.Visual.InaccuracyCrosshair);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##esp inaccuracycrosshair", ClientVars.Col.InaccuracyCrosshair, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(charenc("Spectators"), &ClientVars.Visual.speclist);
			ImGui::Checkbox(charenc("Hitmarker"), &ClientVars.Visual.Hitmarker);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##esp hitmarker", ClientVars.Col.Hitmarker, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Checkbox(charenc("Off-Screen ESP"), &ClientVars.Visual.Arrows);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##esp arrows", ClientVars.Col.Arrows, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Separator();
			ImGui::Checkbox(charenc("Glow Enemy"), &ClientVars.Visual.Glow.GlowEnemy);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##glow enemy", ClientVars.Col.EnemyGlow, true, &ClientVars.Col.EnemyGlowHB, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(charenc("Glow Team"), &ClientVars.Visual.Glow.GlowTeam);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##glow team", ClientVars.Col.TeamGlow, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(charenc("Glow Weapons"), &ClientVars.Visual.Glow.WeaponGlow);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##glow weapons", ClientVars.Col.WeaponGlow, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(charenc("Glow Bomb"), &ClientVars.Visual.Glow.BombGlow);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##glow bomb", ClientVars.Col.BombGlow, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(charenc("Glow Grenades"), &ClientVars.Visual.Glow.GrenadeGlow);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##glow nades", ClientVars.Col.GrenadeGlow, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);

			style.FrameBorderSize = 0.f; ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(charenc("##2groupbox2"), ImVec2((655 / 3) - 1, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Text(charenc("Visuals ~ Part 3"));
			ImGui::Separator();
			ImGui::Text("Removals:");
			ImGui::Selectable(charenc("Visual Recoil"), &ClientVars.Visual.NoVisRecoil);
			ImGui::Selectable(charenc("Smokes"), &ClientVars.Visual.NoSmoke);
			ImGui::Selectable(charenc("Flashbangs"), &ClientVars.Visual.NoFlash);
			ImGui::Selectable(charenc("Scope"), &ClientVars.Visual.NoScope);
			ImGui::Separator();
			ImGui::Checkbox(charenc("Chams"), &ClientVars.Visual.Chams.Enabled);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##cham enemy", ClientVars.Col.EnemyChams, true, &ClientVars.Col.EnemyChamsHB, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(charenc("Chams Team"), &ClientVars.Visual.Chams.Team);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##cham team", ClientVars.Col.TeamChams, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);

			ImGui::Checkbox(charenc("XQZ"), &ClientVars.Visual.Chams.XQZ);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##cham xqz", ClientVars.Col.EnemyChamsXQZ, true, &ClientVars.Col.EnemyChamsXQZHB, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(charenc("Gun Chams"), &ClientVars.Visual.weaponviewcham);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##gunchams", ClientVars.Col.WeaponViewCham, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(charenc("Hand Chams"), &ClientVars.Visual.handcham);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit4("##handchams", ClientVars.Col.HandCham, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);

			ImGui::Separator();
			ImGui::Combo("Hand Mat", &ClientVars.Visual.handmat, "Normal\0\rFlat\0\rWireframe\0\rGlass\0\rGold\0\rPlatinum\0\rCrystal\0\0", -1);
			ImGui::Combo("Player Mat", &ClientVars.Visual.Chams.Player_mat, "Normal\0\rFlat\0\rWireframe\0\rGlass\0\rGold\0\rPlatinum\0\rCrystal\0\0", -1);
			ImGui::Combo("Weapon Mat", &ClientVars.Visual.weaponmat, "Normal\0\rFlat\0\rWireframe\0\rGlass\0\rGold\0\rPlatinum\0\rCrystal\0\0", -1);
			ImGui::Combo("Ghost Chams Mat", &ClientVars.Visual.Chams.GhostChamsMat, "Normal\0\rFlat\0\rWireframe\0\rGlass\0\rGold\0\rPlatinum\0\rCrystal\0\0", -1);
			style.FrameBorderSize = 0.f; ImGui::EndChild();
			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(ClientVars.Styles.Colors.MenuBackground[0], ClientVars.Styles.Colors.MenuBackground[1], ClientVars.Styles.Colors.MenuBackground[2], ClientVars.Styles.Colors.MenuBackground[3]);
		}
		if (current_tab == 3)
		{
			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(ClientVars.Styles.Colors.MenuBackground[0], ClientVars.Styles.Colors.MenuBackground[1], ClientVars.Styles.Colors.MenuBackground[2], ClientVars.Styles.Colors.MenuBackground[3]);
			ImGui::BeginChild(charenc("##3groupbox0"), ImVec2(655 / 3, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Text(charenc("Misc ~ Part 1"));
			ImGui::Separator();
			ImGui::Checkbox(charenc("Anti Untrusted"), &ClientVars.Misc.Antiuntrustedproxy);
			static char buff[128];
			ImGui::InputText("##cfgname", buff, 20);

			if (ImGui::Button("Save CFG"))
				Config::Save(buff);

			ImGui::SameLine();

			if (ImGui::Button("Load CFG"))
				Config::Read(buff);
			ImGui::Checkbox(charenc("Rank Reveal"), &ClientVars.Misc.RankReveal);
			ImGui::Checkbox(charenc("Autoaccept"), &ClientVars.Misc.AutoAccept);

			ImGui::Checkbox("Animated Clan", &ClientVars.Misc.AnimClantag);
			ImGui::Checkbox("KnifeBot", &ClientVars.Misc.Knifebot);
			ImGui::Checkbox("AutoTaser", &ClientVars.Misc.zeusbot);

			style.FrameBorderSize = 0.f; ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(charenc("##3groupbox1"), ImVec2(655 / 3, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Text(charenc("Misc ~ Part 2"));
			ImGui::Separator();


			ImGui::Checkbox("Fake Latency", &ClientVars.Misc.fakelatency);
			ImGui::SliderInt(charenc("##fakelat"), &ClientVars.Misc.desiredlatency, 0, 1000, "Desired Latency: %0.f");
			ImGui::Separator();

			ImGui::Combo(charenc("Fakelag Mode"), &ClientVars.FakeLag.ChokeMode, "Off\0\rStatic\0\0", -1);
			ImGui::SliderInt(charenc("##choke"), &ClientVars.FakeLag.Choke, 1, 13, "Choke: %0.f");
			ImGui::Checkbox(charenc("While Shooting"), &ClientVars.FakeLag.WhileShooting);
			ImGui::Checkbox(charenc("While Still"), &ClientVars.FakeLag.WhileStill);
			ImGui::Checkbox(charenc("On Ground"), &ClientVars.FakeLag.Onground);
			ImGui::Separator();
			ImGui::Combo(charenc("Autoblock"), &ClientVars.Misc.autoblock, keyNames, ARRAYSIZE(keyNames));

			ImGui::Checkbox(charenc("Bunny Hop"), &ClientVars.Misc.Bhop);
			ImGui::Checkbox(charenc("Auto Strafe"), &ClientVars.Misc.Strafe);
			//ImGui::Combo(charenc("Circle Strafer"), &ClientVars.Misc.CircleStrafe, keyNames, ARRAYSIZE(keyNames));
			//ImGui::SliderFloat(charenc("##retrackspeed"), &ClientVars.Misc.RetrackSpeed, 0, 8, "Choke: %0.1f");
			ImGui::Checkbox(charenc("Strafe on ground"), &ClientVars.Misc.GroundStrafe);



			style.FrameBorderSize = 0.f; ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(charenc("##3groupbox2"), ImVec2((655 / 3) - 1, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Text(charenc("Misc ~ Part 3"));
			ImGui::Separator();
			if (ImGui::Button("Unhook"))
			{
				GVars.MenuOpened = false;
				Unhook();
			}
			ImGui::Separator();

			static char textbuff[128];
			ImGui::InputText("##inputtext", textbuff, 20);

			if (ImGui::Button("Set name"))
				Misc::setName(textbuff);
			ImGui::SameLine();
			if (ImGui::Button("Set clan"))
				Misc::SetClanTag(textbuff, textbuff);

			ImGui::Separator();
			if (ImGui::Button("AYYWARE name crasher"))
				Misc::setName(u8"------------------------------------------------------------AYYWARE PASTES OWNED BY KALKONENWARE-------------------------------------------------------------");
			if (ImGui::Button("Release Name"))
				Misc::setName("\n\xAD\xAD\xAD���");
			ImGui::Separator();
			//ImGui::Checkbox(charenc("Insta Explode"), &ClientVars.Misc.InstaExplode);
			//ImGui::SliderInt(charenc("##instaexplode-amount"), &ClientVars.Misc.instaexplodeamount, 1, 100, "InstaExplode Amount: %0.f");
			//ImGui::Checkbox(charenc("Insta Defuse"), &ClientVars.Misc.InstaDefuse);
			//vImGui::Separator();
			ImGui::Text("BETA Features");
			//ImGui::Combo(charenc("KalkWalk"), &ClientVars.Misc.crimwalk, keyNames, ARRAYSIZE(keyNames));
			ImGui::Checkbox("Synced FarESP", &ClientVars.Misc.faresp);

			//ImGui::Combo(charenc("Lag Exploit"), &ClientVars.Misc.Lagexploit, keyNames, ARRAYSIZE(keyNames));
			//ImGui::SliderFloat(charenc("##lagamt"), &ClientVars.Misc.lagamount, 0, 1000, "Lag Amt: %.0f");

			style.FrameBorderSize = 0.f; ImGui::EndChild();
			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(ClientVars.Styles.Colors.MenuBackground[0], ClientVars.Styles.Colors.MenuBackground[1], ClientVars.Styles.Colors.MenuBackground[2], ClientVars.Styles.Colors.MenuBackground[3]);
		}
		if (current_tab == 4)
		{
			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(ClientVars.Styles.Colors.MenuBackground[0], ClientVars.Styles.Colors.MenuBackground[1], ClientVars.Styles.Colors.MenuBackground[2], ClientVars.Styles.Colors.MenuBackground[3]);
			ImGui::BeginChild(charenc("##3groupbox0"), ImVec2(655 / 3, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Text(charenc("Styles ~ Colors"));
			ImGui::Separator();
			ImGui::Text("Menu border");
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##menuborders", ClientVars.Styles.Colors.Menuborder, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Text("Menu background");
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##menubackground", ClientVars.Styles.Colors.MenuBackground, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Text("Borders");
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##borders", ClientVars.Styles.Colors.Border, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Text("Controls");
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##controls", ClientVars.Styles.Colors.Controls, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Text("Text");
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##text", ClientVars.Styles.Colors.Text, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Text("Main menu buttons");
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##mainmenubuttons", ClientVars.Styles.Colors.MainMenuButtons, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Text("Gun menu buttons");
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			ImGui::ColorEdit3("##gunmenubuttons", ClientVars.Styles.Colors.GunMenuButtons, false, nullptr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);

			style.FrameBorderSize = 0.f; ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(charenc("##3groupbox1"), ImVec2(655 / 3, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Text(charenc("Styles ~ Visuals"));
			ImGui::Separator();
			ImGui::SliderFloat(charenc("##espfadein"), &ClientVars.Styles.espFadeIn, 0.f, 5.f, "ESP Fade in: %.2f");
			ImGui::SliderFloat(charenc("##espfadeout"), &ClientVars.Styles.espFadeOut, 0.f, 5.f, "ESP Fade out: %.2f");
			ImGui::SliderInt(charenc("##manualarrowrounding"), &ClientVars.Styles.ManualArrowRounding, -10, 11, "Manual arrow rounding: %0.f");


			style.FrameBorderSize = 0.f; ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(charenc("##3groupbox2"), ImVec2((655 / 3) - 1, -1), true); style.FrameBorderSize = 1.f; ImGui::PushItemWidth(-1);
			ImGui::Text(charenc("Styles ~ Misc"));
			ImGui::Separator();

			style.FrameBorderSize = 0.f; ImGui::EndChild();
			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(ClientVars.Styles.Colors.MenuBackground[0], ClientVars.Styles.Colors.MenuBackground[1], ClientVars.Styles.Colors.MenuBackground[2], ClientVars.Styles.Colors.MenuBackground[3]);
		}

		ImGui::EndChild();

		ImGui::EndChild();

		ImGui::End();
		ImGui::PopFont();

	}

	
	void DrawRadar()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec2 oldPadding = style.WindowPadding;
		float oldAlpha = style.Colors[ImGuiCol_WindowBg].w;
		float oldmainalpha = style.Alpha;
		style.Alpha = 1.0f;
		style.WindowPadding = ImVec2(0, 0);
		style.Colors[ImGuiCol_WindowBg].w = (float)ClientVars.Visual.radralpha / 255.0f;
		if (ImGui::Begin(charenc("Radar"), &GVars.MenuOpened, ImVec2(200, 200), 0.4F, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
		{
			ImVec2 siz = ImGui::GetWindowSize();
			ImVec2 pos = ImGui::GetWindowPos();

			ImGui::GetWindowDrawList()->AddRect(ImVec2(pos.x - 6, pos.y - 6), ImVec2(pos.x + siz.x + 6, pos.y + siz.y + 6), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), 0.0F, -1, 1.5f);

			
			ImGui::SetWindowSize(ImVec2(ClientVars.Visual.radrsize, ClientVars.Visual.radrsize));
		

			ImDrawList* windowDrawList = ImGui::GetWindowDrawList();
			windowDrawList->AddLine(ImVec2(pos.x + (siz.x / 2), pos.y + 0), ImVec2(pos.x + (siz.x / 2), pos.y + siz.y), ImGui::GetColorU32(ImVec4(50, 50, 150, 100)), 1.f);
			windowDrawList->AddLine(ImVec2(pos.x + 0, pos.y + (siz.y / 2)), ImVec2(pos.x + siz.x, pos.y + (siz.y / 2)), ImGui::GetColorU32(ImVec4(50, 50, 150, 100)), 1.f);

			// Rendering players

			if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
			{
				
				if (Hacks.LocalPlayer)
				{
					Vector LocalPos = Hacks.LocalPlayer->GetEyePosition();
					Vector ang;
					Interfaces.pEngine->GetViewAngles(ang);
					for (int i = 0; i < Interfaces.pEngine->GetMaxClients(); i++) {
						CBaseEntity* pBaseEntity = Interfaces.pEntList->GetClientEntity(i);

						if (!pBaseEntity)
							continue;
						if (pBaseEntity->IsDormant())
							continue;
						if (!pBaseEntity->GetHealth() > 0)
							continue;
						if (pBaseEntity == Hacks.LocalPlayer)
							continue;

						bool bIsEnemy = Hacks.LocalPlayer->GetTeam() != pBaseEntity->GetTeam();
						bool isVisibled = Esp::IsVisible(LocalPos, pBaseEntity->GetEyePosition(), Hacks.LocalPlayer, pBaseEntity, ClientVars.Visual.smokecheckradr);

						if (ClientVars.Visual.enemyonlyradr && !bIsEnemy)
							continue;

						bool viewCheck = false;
						Vector EntityPos = Misc::RotatePoint(pBaseEntity->GetVecOrigin(), LocalPos, pos.x, pos.y, siz.x, siz.y, ang.y, ClientVars.Visual.radrzoom, &viewCheck);

						
						ImU32 clr = (bIsEnemy ? (isVisibled ? ImGui::GetColorU32(ImVec4(255, 0, 0, 255)) : ImGui::GetColorU32(ImVec4(0, 255, 0, 255))) : ImGui::GetColorU32(ImVec4(0, 0, 255, 255)));

						if (ClientVars.Visual.visibleonlyradr && !isVisibled)
							continue;

						int s = 4;
						switch (ClientVars.Visual.radrtype) // 0 - Box; 1 - Filled box; 2 - Circle; 3 - Filled circle;
						{
						case 0:
						{
							windowDrawList->AddRect(ImVec2(EntityPos.x - s, EntityPos.y - s),
								ImVec2(EntityPos.x + s, EntityPos.y + s),
								clr);
							break;
						}
						case 1:
						{
							windowDrawList->AddRectFilled(ImVec2(EntityPos.x - s, EntityPos.y - s),
								ImVec2(EntityPos.x + s, EntityPos.y + s),
								clr);
							break;
						}
						case 2:
						{
							windowDrawList->AddCircle(ImVec2(EntityPos.x, EntityPos.y), s, clr);
							break;
						}
						case 3:
						{
							windowDrawList->AddCircleFilled(ImVec2(EntityPos.x, EntityPos.y), s, clr);
							break;
						}
						default:
							break;
						}
					}
				}
			}
		}
		ImGui::End();
		style.WindowPadding = oldPadding;
		style.Colors[ImGuiCol_WindowBg].w = oldAlpha;
		style.Alpha = oldmainalpha;
	}

	std::list<int> GetObservervators(int playerId)
	{
		std::list<int> list;

		if (!Interfaces.pEngine->IsInGame())
			return list;

		CBaseEntity* player = Interfaces.pEntList->GetClientEntity(playerId);
		if (!player)
			return list;

		if (!player->isAlive())
		{
			CBaseEntity* observerTarget = Interfaces.pEntList->GetClientEntityFromHandle(player->GetObserverTargetHandle());
			if (!observerTarget)
				return list;

			player = observerTarget;
		}

		for (int i = 1; i < Interfaces.pEngine->GetMaxClients(); i++)
		{
			CBaseEntity* pPlayer = Interfaces.pEntList->GetClientEntity(i);
			if (!pPlayer)
				continue;

			if (pPlayer->IsDormant() || pPlayer->isAlive())
				continue;

			CBaseEntity* target = Interfaces.pEntList->GetClientEntityFromHandle(pPlayer->GetObserverTargetHandle());
			if (player != target)
				continue;

			list.push_back(i);
		}

		return list;
	}

	void SpecList()
	{
		if (!ClientVars.Visual.speclist)
			return;

		if (!Interfaces.pEngine->IsInGame())
			return;
		ImGuiStyle& style = ImGui::GetStyle();
		float oldmainalpha = style.Alpha;
		style.Alpha = 1.0f;
		if (ImGui::Begin(charenc("Spectators"), &ClientVars.Visual.speclist, ImVec2(200, 150), 0.f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar ))
		{
			for (int playerId : GetObservervators(Interfaces.pEngine->GetLocalPlayer()))
			{
				CBaseEntity* player = Interfaces.pEntList->GetClientEntity(playerId);

				player_info_t entityInformation;
				Interfaces.pEngine->GetPlayerInfo(playerId, &entityInformation);

				char buf[255]; sprintf_s(buf, u8"%s", entityInformation.m_szPlayerName);
				ImGui::Text((u8"%s"), buf);
			}
			ImGui::End();
		}
		style.Alpha = oldmainalpha;
	}

	void OpenMenu()
	{
		if (GVars.unhooked)
			return;

		static bool is_down = false;
		static bool is_clicked = false;
		static bool lastCursor = false;
		static bool firsttime = true;

		if (firsttime)
		{
			firsttime = !firsttime;
		}

		if (GVars.PressedKeys[VK_INSERT])
		{
			is_clicked = false;
			is_down = true;
		}
		else if (!GVars.PressedKeys[VK_INSERT] && is_down)
		{
			is_clicked = true;
			is_down = false;
		}
		else
		{
			is_clicked = false;
			is_down = false;
		}

		if (is_clicked)
		{
			GVars.MenuOpened = !GVars.MenuOpened;
			std::string msg = strenc("cl_mouseenable ") + std::to_string(!GVars.MenuOpened);
			Interfaces.pEngine->ClientCmd_Unrestricted(msg.c_str(), 0);
		}
	}
}