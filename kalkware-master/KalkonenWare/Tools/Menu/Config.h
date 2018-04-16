#include "../../stdafx.h"
#include "IniReader.h"
#include "IniWriter.h"

namespace Config
{
	char* colornames(int col)
	{
		switch (col)
		{
		case 0:
			return "R";
			break;
		case 1:
			return "G";
			break;
		case 2:
			return "B";
			break;
		case 3:
			return "A";
			break;
		}
	}
	void Read(char* name)
	{
		static TCHAR path[MAX_PATH];
		std::string folder, file;
		if (strlen(name) > 0)
		{
			if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
			{
				folder = std::string(path) + strenc("\\KalkonenWare\\");
				file = std::string(path) + strenc("\\KalkonenWare\\") + std::string(name) + strenc(".cfg");
			}
		}
		else
		{
			if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
			{
				folder = std::string(path) + strenc("\\KalkonenWare\\");
				file = std::string(path) + strenc("\\KalkonenWare\\config.cfg");
			}
		}

		CIniReader reader(file.c_str());

		ClientVars.Ragebot.Enable = reader.ReadBoolean("Ragebot", "Enable", ClientVars.Ragebot.Enable);
		ClientVars.Ragebot.FOV = reader.ReadFloat("Ragebot", "FOV", ClientVars.Ragebot.FOV);
		ClientVars.Ragebot.Autowall = reader.ReadBoolean("Ragebot", "Autowall", ClientVars.Ragebot.Autowall);
		ClientVars.Ragebot.AimbotSelection = reader.ReadInteger("Ragebot", "Selection", ClientVars.Ragebot.AimbotSelection);
		ClientVars.Ragebot.AutoPistol = reader.ReadBoolean("Ragebot", "Autopistol", ClientVars.Ragebot.AutoPistol);
		ClientVars.Ragebot.pSilent = reader.ReadBoolean("Ragebot", "pSilent", ClientVars.Ragebot.pSilent);
		ClientVars.Ragebot.autofire = reader.ReadBoolean("Ragebot", "Autoshoot", ClientVars.Ragebot.autofire);
		ClientVars.Ragebot.autoscope = reader.ReadBoolean("Ragebot", "Autoscope", ClientVars.Ragebot.autoscope);
		ClientVars.Ragebot.NoRecoil = reader.ReadBoolean("Ragebot", "NoRecoil", ClientVars.Ragebot.NoRecoil);
		ClientVars.Ragebot.BackTrack = reader.ReadBoolean("Ragebot", "Position-Adjustment", ClientVars.Ragebot.BackTrack);
		ClientVars.Ragebot.Resolver = reader.ReadInteger("Ragebot", "Resolver", ClientVars.Ragebot.Resolver);
		ClientVars.Ragebot.ResolvePitch = reader.ReadInteger("Ragebot", "Pitch-Resolver", ClientVars.Ragebot.ResolvePitch);
		ClientVars.Ragebot.overrideresolver = reader.ReadInteger("Ragebot", "Override-Key", ClientVars.Ragebot.overrideresolver);
		ClientVars.Ragebot.overrideradd = reader.ReadInteger("Ragebot", "Override-Add", ClientVars.Ragebot.overrideradd);

		ClientVars.Ragebot.Weapons.Pistol.Hitbox = reader.ReadInteger("Ragebot-Pistol", "Hitbox", ClientVars.Ragebot.Weapons.Pistol.Hitbox);
		ClientVars.Ragebot.Weapons.Pistol.Hitscan.strength = reader.ReadInteger("Ragebot-Pistol", "Hitscan", ClientVars.Ragebot.Weapons.Pistol.Hitscan.strength);
		ClientVars.Ragebot.Weapons.Pistol.HitChance = reader.ReadInteger("Ragebot-Pistol", "Hitchance", ClientVars.Ragebot.Weapons.Pistol.HitChance);
		ClientVars.Ragebot.Weapons.Pistol.MinDmg = reader.ReadInteger("Ragebot-Pistol", "MinDMG", ClientVars.Ragebot.Weapons.Pistol.MinDmg);
		ClientVars.Ragebot.Weapons.Pistol.Headscale = reader.ReadFloat("Ragebot-Pistol", "Headscale", ClientVars.Ragebot.Weapons.Pistol.Headscale);
		ClientVars.Ragebot.Weapons.Pistol.Bodyscale = reader.ReadFloat("Ragebot-Pistol", "Bodyscale", ClientVars.Ragebot.Weapons.Pistol.Bodyscale);
		ClientVars.Ragebot.Weapons.Pistol.Hitscan.head = reader.ReadBoolean("Ragebot-Pistol-Hitscan", "Head", ClientVars.Ragebot.Weapons.Pistol.Hitscan.head);
		ClientVars.Ragebot.Weapons.Pistol.Hitscan.neck = reader.ReadBoolean("Ragebot-Pistol-Hitscan", "Neck", ClientVars.Ragebot.Weapons.Pistol.Hitscan.neck);
		ClientVars.Ragebot.Weapons.Pistol.Hitscan.arms = reader.ReadBoolean("Ragebot-Pistol-Hitscan", "Arms", ClientVars.Ragebot.Weapons.Pistol.Hitscan.arms);
		ClientVars.Ragebot.Weapons.Pistol.Hitscan.chest = reader.ReadBoolean("Ragebot-Pistol-Hitscan", "Chest", ClientVars.Ragebot.Weapons.Pistol.Hitscan.chest);
		ClientVars.Ragebot.Weapons.Pistol.Hitscan.stomach = reader.ReadBoolean("Ragebot-Pistol-Hitscan", "Stomach", ClientVars.Ragebot.Weapons.Pistol.Hitscan.stomach);
		ClientVars.Ragebot.Weapons.Pistol.Hitscan.pelvis = reader.ReadBoolean("Ragebot-Pistol-Hitscan", "Pelvis", ClientVars.Ragebot.Weapons.Pistol.Hitscan.pelvis);
		ClientVars.Ragebot.Weapons.Pistol.Hitscan.legs = reader.ReadBoolean("Ragebot-Pistol-Hitscan", "Legs", ClientVars.Ragebot.Weapons.Pistol.Hitscan.legs);
		ClientVars.Ragebot.Weapons.Pistol.Hitscan.feet = reader.ReadBoolean("Ragebot-Pistol-Hitscan", "Feet", ClientVars.Ragebot.Weapons.Pistol.Hitscan.feet);

		ClientVars.Ragebot.Weapons.Pistol.baimiflethal = reader.ReadBoolean("Ragebot-Pistol", "BaimIFLethal", ClientVars.Ragebot.Weapons.Pistol.baimiflethal);



		ClientVars.Ragebot.Weapons.Sniper.Hitbox = reader.ReadInteger("Ragebot-Sniper", "Hitbox", ClientVars.Ragebot.Weapons.Sniper.Hitbox);
		ClientVars.Ragebot.Weapons.Sniper.Hitscan.strength = reader.ReadInteger("Ragebot-Sniper", "Hitscan", ClientVars.Ragebot.Weapons.Sniper.Hitscan.strength);
		ClientVars.Ragebot.Weapons.Sniper.HitChance = reader.ReadInteger("Ragebot-Sniper", "Hitchance", ClientVars.Ragebot.Weapons.Sniper.HitChance);
		ClientVars.Ragebot.Weapons.Sniper.MinDmg = reader.ReadInteger("Ragebot-Sniper", "MinDMG", ClientVars.Ragebot.Weapons.Sniper.MinDmg);
		ClientVars.Ragebot.Weapons.Sniper.Headscale = reader.ReadFloat("Ragebot-Sniper", "Headscale", ClientVars.Ragebot.Weapons.Sniper.Headscale);
		ClientVars.Ragebot.Weapons.Sniper.Bodyscale = reader.ReadFloat("Ragebot-Sniper", "Bodyscale", ClientVars.Ragebot.Weapons.Sniper.Bodyscale);
		ClientVars.Ragebot.Weapons.Sniper.Hitscan.head = reader.ReadBoolean("Ragebot-Sniper-Hitscan", "Head", ClientVars.Ragebot.Weapons.Sniper.Hitscan.head);
		ClientVars.Ragebot.Weapons.Sniper.Hitscan.neck = reader.ReadBoolean("Ragebot-Sniper-Hitscan", "Neck", ClientVars.Ragebot.Weapons.Sniper.Hitscan.neck);
		ClientVars.Ragebot.Weapons.Sniper.Hitscan.arms = reader.ReadBoolean("Ragebot-Sniper-Hitscan", "Arms", ClientVars.Ragebot.Weapons.Sniper.Hitscan.arms);
		ClientVars.Ragebot.Weapons.Sniper.Hitscan.chest = reader.ReadBoolean("Ragebot-Sniper-Hitscan", "Chest", ClientVars.Ragebot.Weapons.Sniper.Hitscan.chest);
		ClientVars.Ragebot.Weapons.Sniper.Hitscan.stomach = reader.ReadBoolean("Ragebot-Sniper-Hitscan", "Stomach", ClientVars.Ragebot.Weapons.Sniper.Hitscan.stomach);
		ClientVars.Ragebot.Weapons.Sniper.Hitscan.pelvis = reader.ReadBoolean("Ragebot-Sniper-Hitscan", "Pelvis", ClientVars.Ragebot.Weapons.Sniper.Hitscan.pelvis);
		ClientVars.Ragebot.Weapons.Sniper.Hitscan.legs = reader.ReadBoolean("Ragebot-Sniper-Hitscan", "Legs", ClientVars.Ragebot.Weapons.Sniper.Hitscan.legs);
		ClientVars.Ragebot.Weapons.Sniper.Hitscan.feet = reader.ReadBoolean("Ragebot-Sniper-Hitscan", "Feet", ClientVars.Ragebot.Weapons.Sniper.Hitscan.feet);

		ClientVars.Ragebot.Weapons.Sniper.baimiflethal = reader.ReadBoolean("Ragebot-Sniper", "BaimIFLethal", ClientVars.Ragebot.Weapons.Sniper.baimiflethal);



		ClientVars.Ragebot.Weapons.AutoSniper.Hitbox = reader.ReadInteger("Ragebot-AutoSniper", "Hitbox", ClientVars.Ragebot.Weapons.AutoSniper.Hitbox);
		ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.strength = reader.ReadInteger("Ragebot-AutoSniper", "Hitscan", ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.strength);
		ClientVars.Ragebot.Weapons.AutoSniper.HitChance = reader.ReadInteger("Ragebot-AutoSniper", "Hitchance", ClientVars.Ragebot.Weapons.AutoSniper.HitChance);
		ClientVars.Ragebot.Weapons.AutoSniper.MinDmg = reader.ReadInteger("Ragebot-AutoSniper", "MinDMG", ClientVars.Ragebot.Weapons.AutoSniper.MinDmg);
		ClientVars.Ragebot.Weapons.AutoSniper.Headscale = reader.ReadFloat("Ragebot-AutoSniper", "Headscale", ClientVars.Ragebot.Weapons.AutoSniper.Headscale);
		ClientVars.Ragebot.Weapons.AutoSniper.Bodyscale = reader.ReadFloat("Ragebot-AutoSniper", "Bodyscale", ClientVars.Ragebot.Weapons.AutoSniper.Bodyscale);
		ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.head = reader.ReadBoolean("Ragebot-AutoSniper-Hitscan", "Head", ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.head);
		ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.neck = reader.ReadBoolean("Ragebot-AutoSniper-Hitscan", "Neck", ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.neck);
		ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.arms = reader.ReadBoolean("Ragebot-AutoSniper-Hitscan", "Arms", ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.arms);
		ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.chest = reader.ReadBoolean("Ragebot-AutoSniper-Hitscan", "Chest", ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.chest);
		ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.stomach = reader.ReadBoolean("Ragebot-AutoSniper-Hitscan", "Stomach", ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.stomach);
		ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.pelvis = reader.ReadBoolean("Ragebot-AutoSniper-Hitscan", "Pelvis", ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.pelvis);
		ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.legs = reader.ReadBoolean("Ragebot-AutoSniper-Hitscan", "Legs", ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.legs);
		ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.feet = reader.ReadBoolean("Ragebot-AutoSniper-Hitscan", "Feet", ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.feet);

		ClientVars.Ragebot.Weapons.AutoSniper.baimiflethal = reader.ReadBoolean("Ragebot-AutoSniper", "BaimIFLethal", ClientVars.Ragebot.Weapons.AutoSniper.baimiflethal);



		ClientVars.Ragebot.Weapons.Rifle.Hitbox = reader.ReadInteger("Ragebot-Rifle", "Hitbox", ClientVars.Ragebot.Weapons.Rifle.Hitbox);
		ClientVars.Ragebot.Weapons.Rifle.Hitscan.strength = reader.ReadInteger("Ragebot-Rifle", "Hitscan", ClientVars.Ragebot.Weapons.Rifle.Hitscan.strength);
		ClientVars.Ragebot.Weapons.Rifle.HitChance = reader.ReadInteger("Ragebot-Rifle", "Hitchance", ClientVars.Ragebot.Weapons.Rifle.HitChance);
		ClientVars.Ragebot.Weapons.Rifle.MinDmg = reader.ReadInteger("Ragebot-Rifle", "MinDMG", ClientVars.Ragebot.Weapons.Rifle.MinDmg);
		ClientVars.Ragebot.Weapons.Rifle.Headscale = reader.ReadFloat("Ragebot-Rifle", "Headscale", ClientVars.Ragebot.Weapons.Rifle.Headscale);
		ClientVars.Ragebot.Weapons.Rifle.Bodyscale = reader.ReadFloat("Ragebot-Rifle", "Bodyscale", ClientVars.Ragebot.Weapons.Rifle.Bodyscale);
		ClientVars.Ragebot.Weapons.Rifle.Hitscan.head = reader.ReadBoolean("Ragebot-Rifle-Hitscan", "Head", ClientVars.Ragebot.Weapons.Rifle.Hitscan.head);
		ClientVars.Ragebot.Weapons.Rifle.Hitscan.neck = reader.ReadBoolean("Ragebot-Rifle-Hitscan", "Neck", ClientVars.Ragebot.Weapons.Rifle.Hitscan.neck);
		ClientVars.Ragebot.Weapons.Rifle.Hitscan.arms = reader.ReadBoolean("Ragebot-Rifle-Hitscan", "Arms", ClientVars.Ragebot.Weapons.Rifle.Hitscan.arms);
		ClientVars.Ragebot.Weapons.Rifle.Hitscan.chest = reader.ReadBoolean("Ragebot-Rifle-Hitscan", "Chest", ClientVars.Ragebot.Weapons.Rifle.Hitscan.chest);
		ClientVars.Ragebot.Weapons.Rifle.Hitscan.stomach = reader.ReadBoolean("Ragebot-Rifle-Hitscan", "Stomach", ClientVars.Ragebot.Weapons.Rifle.Hitscan.stomach);
		ClientVars.Ragebot.Weapons.Rifle.Hitscan.pelvis = reader.ReadBoolean("Ragebot-Rifle-Hitscan", "Pelvis", ClientVars.Ragebot.Weapons.Rifle.Hitscan.pelvis);
		ClientVars.Ragebot.Weapons.Rifle.Hitscan.legs = reader.ReadBoolean("Ragebot-Rifle-Hitscan", "Legs", ClientVars.Ragebot.Weapons.Rifle.Hitscan.legs);
		ClientVars.Ragebot.Weapons.Rifle.Hitscan.feet = reader.ReadBoolean("Ragebot-Rifle-Hitscan", "Feet", ClientVars.Ragebot.Weapons.Rifle.Hitscan.feet);

		ClientVars.Ragebot.Weapons.Rifle.baimiflethal = reader.ReadBoolean("Ragebot-Rifle", "BaimIFLethal", ClientVars.Ragebot.Weapons.Rifle.baimiflethal);



		ClientVars.Ragebot.Weapons.SMG.Hitbox = reader.ReadInteger("Ragebot-SMG", "Hitbox", ClientVars.Ragebot.Weapons.SMG.Hitbox);
		ClientVars.Ragebot.Weapons.SMG.Hitscan.strength = reader.ReadInteger("Ragebot-SMG", "Hitscan", ClientVars.Ragebot.Weapons.SMG.Hitscan.strength);
		ClientVars.Ragebot.Weapons.SMG.HitChance = reader.ReadInteger("Ragebot-SMG", "Hitchance", ClientVars.Ragebot.Weapons.SMG.HitChance);
		ClientVars.Ragebot.Weapons.SMG.MinDmg = reader.ReadInteger("Ragebot-SMG", "MinDMG", ClientVars.Ragebot.Weapons.SMG.MinDmg);
		ClientVars.Ragebot.Weapons.SMG.Headscale = reader.ReadFloat("Ragebot-SMG", "Headscale", ClientVars.Ragebot.Weapons.SMG.Headscale);
		ClientVars.Ragebot.Weapons.SMG.Bodyscale = reader.ReadFloat("Ragebot-SMG", "Bodyscale", ClientVars.Ragebot.Weapons.SMG.Bodyscale);
		ClientVars.Ragebot.Weapons.SMG.Hitscan.head = reader.ReadBoolean("Ragebot-SMG-Hitscan", "Head", ClientVars.Ragebot.Weapons.SMG.Hitscan.head);
		ClientVars.Ragebot.Weapons.SMG.Hitscan.neck = reader.ReadBoolean("Ragebot-SMG-Hitscan", "Neck", ClientVars.Ragebot.Weapons.SMG.Hitscan.neck);
		ClientVars.Ragebot.Weapons.SMG.Hitscan.arms = reader.ReadBoolean("Ragebot-SMG-Hitscan", "Arms", ClientVars.Ragebot.Weapons.SMG.Hitscan.arms);
		ClientVars.Ragebot.Weapons.SMG.Hitscan.chest = reader.ReadBoolean("Ragebot-SMG-Hitscan", "Chest", ClientVars.Ragebot.Weapons.SMG.Hitscan.chest);
		ClientVars.Ragebot.Weapons.SMG.Hitscan.stomach = reader.ReadBoolean("Ragebot-SMG-Hitscan", "Stomach", ClientVars.Ragebot.Weapons.SMG.Hitscan.stomach);
		ClientVars.Ragebot.Weapons.SMG.Hitscan.pelvis = reader.ReadBoolean("Ragebot-SMG-Hitscan", "Pelvis", ClientVars.Ragebot.Weapons.SMG.Hitscan.pelvis);
		ClientVars.Ragebot.Weapons.SMG.Hitscan.legs = reader.ReadBoolean("Ragebot-SMG-Hitscan", "Legs", ClientVars.Ragebot.Weapons.SMG.Hitscan.legs);
		ClientVars.Ragebot.Weapons.SMG.Hitscan.feet = reader.ReadBoolean("Ragebot-SMG-Hitscan", "Feet", ClientVars.Ragebot.Weapons.SMG.Hitscan.feet);

		ClientVars.Ragebot.Weapons.SMG.baimiflethal = reader.ReadBoolean("Ragebot-SMG", "BaimIFLethal", ClientVars.Ragebot.Weapons.SMG.baimiflethal);



		ClientVars.Ragebot.Weapons.Shotgun.Hitbox = reader.ReadInteger("Ragebot-Shotgun", "Hitbox", ClientVars.Ragebot.Weapons.Shotgun.Hitbox);
		ClientVars.Ragebot.Weapons.Shotgun.Hitscan.strength = reader.ReadInteger("Ragebot-Shotgun", "Hitscan", ClientVars.Ragebot.Weapons.Shotgun.Hitscan.strength);
		ClientVars.Ragebot.Weapons.Shotgun.HitChance = reader.ReadInteger("Ragebot-Shotgun", "Hitchance", ClientVars.Ragebot.Weapons.Shotgun.HitChance);
		ClientVars.Ragebot.Weapons.Shotgun.MinDmg = reader.ReadInteger("Ragebot-Shotgun", "MinDMG", ClientVars.Ragebot.Weapons.Shotgun.MinDmg);
		ClientVars.Ragebot.Weapons.Shotgun.Headscale = reader.ReadFloat("Ragebot-Shotgun", "Headscale", ClientVars.Ragebot.Weapons.Shotgun.Headscale);
		ClientVars.Ragebot.Weapons.Shotgun.Bodyscale = reader.ReadFloat("Ragebot-Shotgun", "Bodyscale", ClientVars.Ragebot.Weapons.Shotgun.Bodyscale);
		ClientVars.Ragebot.Weapons.Shotgun.Hitscan.head = reader.ReadBoolean("Ragebot-Shotgun-Hitscan", "Head", ClientVars.Ragebot.Weapons.Shotgun.Hitscan.head);
		ClientVars.Ragebot.Weapons.Shotgun.Hitscan.neck = reader.ReadBoolean("Ragebot-Shotgun-Hitscan", "Neck", ClientVars.Ragebot.Weapons.Shotgun.Hitscan.neck);
		ClientVars.Ragebot.Weapons.Shotgun.Hitscan.arms = reader.ReadBoolean("Ragebot-Shotgun-Hitscan", "Arms", ClientVars.Ragebot.Weapons.Shotgun.Hitscan.arms);
		ClientVars.Ragebot.Weapons.Shotgun.Hitscan.chest = reader.ReadBoolean("Ragebot-Shotgun-Hitscan", "Chest", ClientVars.Ragebot.Weapons.Shotgun.Hitscan.chest);
		ClientVars.Ragebot.Weapons.Shotgun.Hitscan.stomach = reader.ReadBoolean("Ragebot-Shotgun-Hitscan", "Stomach", ClientVars.Ragebot.Weapons.Shotgun.Hitscan.stomach);
		ClientVars.Ragebot.Weapons.Shotgun.Hitscan.pelvis = reader.ReadBoolean("Ragebot-Shotgun-Hitscan", "Pelvis", ClientVars.Ragebot.Weapons.Shotgun.Hitscan.pelvis);
		ClientVars.Ragebot.Weapons.Shotgun.Hitscan.legs = reader.ReadBoolean("Ragebot-Shotgun-Hitscan", "Legs", ClientVars.Ragebot.Weapons.Shotgun.Hitscan.legs);
		ClientVars.Ragebot.Weapons.Shotgun.Hitscan.feet = reader.ReadBoolean("Ragebot-Shotgun-Hitscan", "Feet", ClientVars.Ragebot.Weapons.Shotgun.Hitscan.feet);

		ClientVars.Ragebot.Weapons.Shotgun.baimiflethal = reader.ReadBoolean("Ragebot-Shotgun", "BaimIFLethal", ClientVars.Ragebot.Weapons.Shotgun.baimiflethal);



		ClientVars.AntiAim.enabled = reader.ReadBoolean("Ragebot-AA", "Enable", ClientVars.AntiAim.enabled);

		ClientVars.AntiAim.Stand.Pitch = reader.ReadInteger("Ragebot-AA-Stand", "Pitch", ClientVars.AntiAim.Stand.Pitch);
		ClientVars.AntiAim.Stand.PitchAdd = reader.ReadInteger("Ragebot-AA-Stand", "Custom-Pitch", ClientVars.AntiAim.Stand.PitchAdd);
		ClientVars.AntiAim.Stand.Yaw = reader.ReadInteger("Ragebot-AA-Stand", "Yaw", ClientVars.AntiAim.Stand.Yaw);
		ClientVars.AntiAim.Stand.YawAdd = reader.ReadInteger("Ragebot-AA-Stand", "Yaw-Adder", ClientVars.AntiAim.Stand.YawAdd);
		ClientVars.AntiAim.Stand.Fake = reader.ReadInteger("Ragebot-AA-Stand", "Fake-Yaw", ClientVars.AntiAim.Stand.Fake);
		ClientVars.AntiAim.Stand.FakeAdd = reader.ReadInteger("Ragebot-AA-Stand", "Fake-Yaw-Adder", ClientVars.AntiAim.Stand.FakeAdd);

		ClientVars.AntiAim.Move.Pitch = reader.ReadInteger("Ragebot-AA-Move", "Pitch", ClientVars.AntiAim.Move.Pitch);
		ClientVars.AntiAim.Move.PitchAdd = reader.ReadInteger("Ragebot-AA-Move", "Custom-Pitch", ClientVars.AntiAim.Move.PitchAdd);
		ClientVars.AntiAim.Move.Yaw = reader.ReadInteger("Ragebot-AA-Move", "Yaw", ClientVars.AntiAim.Move.Yaw);
		ClientVars.AntiAim.Move.YawAdd = reader.ReadInteger("Ragebot-AA-Move", "Yaw-Adder", ClientVars.AntiAim.Move.YawAdd);
		ClientVars.AntiAim.Move.Fake = reader.ReadInteger("Ragebot-AA-Move", "Fake-Yaw", ClientVars.AntiAim.Move.Fake);
		ClientVars.AntiAim.Move.FakeAdd = reader.ReadInteger("Ragebot-AA-Move", "Fake-Yaw-Adder", ClientVars.AntiAim.Move.FakeAdd);

		ClientVars.AntiAim.Air.Pitch = reader.ReadInteger("Ragebot-AA-InAir", "Pitch", ClientVars.AntiAim.Air.Pitch);
		ClientVars.AntiAim.Air.PitchAdd = reader.ReadInteger("Ragebot-AA-InAir", "Custom-Pitch", ClientVars.AntiAim.Air.PitchAdd);
		ClientVars.AntiAim.Air.Yaw = reader.ReadInteger("Ragebot-AA-InAir", "Yaw", ClientVars.AntiAim.Air.Yaw);
		ClientVars.AntiAim.Air.YawAdd = reader.ReadInteger("Ragebot-AA-InAir", "Yaw-Adder", ClientVars.AntiAim.Air.YawAdd);
		ClientVars.AntiAim.Air.Fake = reader.ReadInteger("Ragebot-AA-InAir", "Fake-Yaw", ClientVars.AntiAim.Air.Fake);
		ClientVars.AntiAim.Air.FakeAdd = reader.ReadInteger("Ragebot-AA-InAir", "Fake-Yaw-Adder", ClientVars.AntiAim.Air.FakeAdd);

		ClientVars.AntiAim.Misc.lbyDelta = reader.ReadInteger("Ragebot-AA-Misc", "LBY-Delta", ClientVars.AntiAim.Misc.lbyDelta);
		ClientVars.AntiAim.Misc.SpinbotSpeed = reader.ReadFloat("Ragebot-AA-Misc", "Spinbot-Speed", ClientVars.AntiAim.Misc.SpinbotSpeed);
		ClientVars.AntiAim.Misc.JitterSpeed = reader.ReadFloat("Ragebot-AA-Misc", "Jitter-Speed", ClientVars.AntiAim.Misc.JitterSpeed);
		ClientVars.AntiAim.Misc.JitterRange = reader.ReadInteger("Ragebot-AA-Misc", "Jitter-Range", ClientVars.AntiAim.Misc.JitterRange);
		ClientVars.AntiAim.Misc.JitterSpeed = reader.ReadFloat("Ragebot-AA-Misc", "Jitter-Speed", ClientVars.AntiAim.Misc.JitterSpeed);
		ClientVars.AntiAim.Misc.SwitchAdd = reader.ReadInteger("Ragebot-AA-Misc", "Switch-Add", ClientVars.AntiAim.Misc.SwitchAdd);
		ClientVars.AntiAim.Misc.SwitchSpeed = reader.ReadFloat("Ragebot-AA-Misc", "Switch-Speed", ClientVars.AntiAim.Misc.SwitchSpeed);
		ClientVars.AntiAim.Misc.fakewalk = reader.ReadInteger("Ragebot-AA-Misc", "FakeWalk", ClientVars.AntiAim.Misc.fakewalk);
		ClientVars.AntiAim.Misc.leftAA = reader.ReadInteger("Ragebot-AA-Misc", "Manual-Left", ClientVars.AntiAim.Misc.leftAA);
		ClientVars.AntiAim.Misc.rightAA = reader.ReadInteger("Ragebot-AA-Misc", "Manual-Right", ClientVars.AntiAim.Misc.rightAA);
		ClientVars.AntiAim.Misc.downAA = reader.ReadInteger("Ragebot-AA-Misc", "Manual-Down", ClientVars.AntiAim.Misc.downAA);
		//ClientVars.AntiAim.Misc.upAA = reader.ReadInteger("Ragebot-AA-Misc", "Manual-Up", ClientVars.AntiAim.Misc.upAA);
		ClientVars.AntiAim.OnGreandes = reader.ReadBoolean("Ragebot-AA-Misc", "On-grenades", ClientVars.AntiAim.OnGreandes);
		ClientVars.AntiAim.OnLadders = reader.ReadBoolean("Ragebot-AA-Misc", "On-ladders", ClientVars.AntiAim.OnLadders);
		ClientVars.AntiAim.OnKnife = reader.ReadBoolean("Ragebot-AA-Misc", "On-knife", ClientVars.AntiAim.OnKnife);

		ClientVars.LegitBot.enable = reader.ReadBoolean("Legitbot", "Enable", ClientVars.LegitBot.enable);
		ClientVars.LegitBot.backtrack = reader.ReadBoolean("Legitbot", "BackTrack", ClientVars.LegitBot.backtrack);
		ClientVars.LegitBot.AntiAim.enabled = reader.ReadBoolean("Legitbot-AA", "Enable", ClientVars.LegitBot.AntiAim.enabled);

		ClientVars.LegitBot.AntiAim.Stand.Yaw = reader.ReadInteger("Legitbot-AA-Stand", "Yaw", ClientVars.LegitBot.AntiAim.Stand.Yaw);
		ClientVars.LegitBot.AntiAim.Stand.YawAdd = reader.ReadInteger("Legitbot-AA-Stand", "Yaw-Adder", ClientVars.LegitBot.AntiAim.Stand.YawAdd);

		ClientVars.LegitBot.AntiAim.Move.Yaw = reader.ReadInteger("Legitbot-AA-Move", "Yaw", ClientVars.LegitBot.AntiAim.Move.Yaw);
		ClientVars.LegitBot.AntiAim.Move.YawAdd = reader.ReadInteger("Legitbot-AA-Move", "Yaw-Adder", ClientVars.LegitBot.AntiAim.Move.YawAdd);

		ClientVars.LegitBot.AntiAim.Air.Yaw = reader.ReadInteger("Legitbot-AA-InAir", "Yaw", ClientVars.LegitBot.AntiAim.Air.Yaw);
		ClientVars.LegitBot.AntiAim.Air.YawAdd = reader.ReadInteger("Legitbot-AA-InAir", "Yaw-Adder", ClientVars.LegitBot.AntiAim.Air.YawAdd);

		ClientVars.LegitBot.AntiAim.Misc.lbyDelta = reader.ReadInteger("Legitbot-AA-Misc", "LBY-Delta", ClientVars.LegitBot.AntiAim.Misc.lbyDelta);
		ClientVars.LegitBot.AntiAim.Misc.SpinbotSpeed = reader.ReadFloat("Legitbot-AA-Misc", "Spinbot-Speed", ClientVars.LegitBot.AntiAim.Misc.SpinbotSpeed);
		ClientVars.LegitBot.AntiAim.Misc.JitterSpeed = reader.ReadFloat("Legitbot-AA-Misc", "Jitter-Speed", ClientVars.LegitBot.AntiAim.Misc.JitterSpeed);
		ClientVars.LegitBot.AntiAim.Misc.JitterRange = reader.ReadInteger("Legitbot-AA-Misc", "Jitter-Range", ClientVars.LegitBot.AntiAim.Misc.JitterRange);
		ClientVars.LegitBot.AntiAim.Misc.JitterSpeed = reader.ReadFloat("Legitbot-AA-Misc", "Jitter-Speed", ClientVars.LegitBot.AntiAim.Misc.JitterSpeed);
		ClientVars.LegitBot.AntiAim.Misc.SwitchAdd = reader.ReadInteger("Legitbot-AA-Misc", "Switch-Add", ClientVars.LegitBot.AntiAim.Misc.SwitchAdd);
		ClientVars.LegitBot.AntiAim.Misc.SwitchSpeed = reader.ReadFloat("Legitbot-AA-Misc", "Switch-Speed", ClientVars.LegitBot.AntiAim.Misc.SwitchSpeed);
		ClientVars.LegitBot.AntiAim.Misc.leftAA = reader.ReadInteger("Legitbot-AA-Misc", "Manual-Left", ClientVars.LegitBot.AntiAim.Misc.leftAA);
		ClientVars.LegitBot.AntiAim.Misc.rightAA = reader.ReadInteger("Legitbot-AA-Misc", "Manual-Right", ClientVars.LegitBot.AntiAim.Misc.rightAA);
		ClientVars.LegitBot.AntiAim.Misc.downAA = reader.ReadInteger("Legitbot-AA-Misc", "Manual-Down", ClientVars.LegitBot.AntiAim.Misc.downAA);
		//ClientVars.LegitBot.AntiAim.Misc.upAA = reader.ReadInteger("Legitbot-AA-Misc", "Manual-Up", ClientVars.LegitBot.AntiAim.Misc.upAA);
		ClientVars.LegitBot.AntiAim.OnGreandes = reader.ReadBoolean("Legitbot-AA-Misc", "On-grenades", ClientVars.LegitBot.AntiAim.OnGreandes);
		ClientVars.LegitBot.AntiAim.OnLadders = reader.ReadBoolean("Legitbot-AA-Misc", "On-ladders", ClientVars.LegitBot.AntiAim.OnLadders);
		ClientVars.LegitBot.AntiAim.OnKnife = reader.ReadBoolean("Legitbot-AA-Misc", "On-knife", ClientVars.LegitBot.AntiAim.OnKnife);

		ClientVars.LegitBot.Weapons.Pistol.enable = reader.ReadBoolean("Legitbot-Pistol-Aimbot", "Enable", ClientVars.LegitBot.Weapons.Pistol.enable);
		ClientVars.LegitBot.Weapons.Pistol.onkey = reader.ReadBoolean("Legitbot-Pistol-Aimbot", "OnKey", ClientVars.LegitBot.Weapons.Pistol.onkey);
		ClientVars.LegitBot.Weapons.Pistol.key = reader.ReadInteger("Legitbot-Pistol-Aimbot", "Key", ClientVars.LegitBot.Weapons.Pistol.key);
		ClientVars.LegitBot.Weapons.Pistol.hitbox = reader.ReadInteger("Legitbot-Pistol-Aimbot", "Hitbox", ClientVars.LegitBot.Weapons.Pistol.hitbox);
		ClientVars.LegitBot.Weapons.Pistol.fov = reader.ReadFloat("Legitbot-Pistol-Aimbot", "FOV", ClientVars.LegitBot.Weapons.Pistol.fov);
		ClientVars.LegitBot.Weapons.Pistol.smoothing = reader.ReadFloat("Legitbot-Pistol-Aimbot", "Smoothing", ClientVars.LegitBot.Weapons.Pistol.smoothing);
		ClientVars.LegitBot.Weapons.Pistol.autowall = reader.ReadBoolean("Legitbot-Pistol-Aimbot", "AutoWall", ClientVars.LegitBot.Weapons.Pistol.autowall);
		ClientVars.LegitBot.Weapons.Pistol.recoilcontrol = reader.ReadBoolean("Legitbot-Pistol-Aimbot", "RecoilControl", ClientVars.LegitBot.Weapons.Pistol.recoilcontrol);
		ClientVars.LegitBot.Weapons.Pistol.autopistol = reader.ReadBoolean("Legitbot-Pistol", "AutoPistol", ClientVars.LegitBot.Weapons.Pistol.autopistol);
		ClientVars.LegitBot.Weapons.Pistol.autorevolver = reader.ReadBoolean("Legitbot-Pistol", "AutoRevolver", ClientVars.LegitBot.Weapons.Pistol.autorevolver);
		ClientVars.LegitBot.Weapons.Pistol.Triggerbot.enable = reader.ReadBoolean("Legitbot-Pistol-Triggerbot", "Enable", ClientVars.LegitBot.Weapons.Pistol.Triggerbot.enable);
		ClientVars.LegitBot.Weapons.Pistol.Triggerbot.onkey = reader.ReadBoolean("Legitbot-Pistol-Triggerbot", "OnKey", ClientVars.LegitBot.Weapons.Pistol.Triggerbot.onkey);
		ClientVars.LegitBot.Weapons.Pistol.Triggerbot.key = reader.ReadInteger("Legitbot-Pistol-Triggerbot", "Key", ClientVars.LegitBot.Weapons.Pistol.Triggerbot.key);
		ClientVars.LegitBot.Weapons.Pistol.Triggerbot.hitbox = reader.ReadInteger("Legitbot-Pistol-Triggerbot", "Hitbox", ClientVars.LegitBot.Weapons.Pistol.Triggerbot.hitbox);
		ClientVars.LegitBot.Weapons.Pistol.Triggerbot.hitchance = reader.ReadInteger("Legitbot-Pistol-Triggerbot", "Hitchance", ClientVars.LegitBot.Weapons.Pistol.Triggerbot.hitchance);
		ClientVars.LegitBot.Weapons.Pistol.Triggerbot.delay = reader.ReadInteger("Legitbot-Pistol-Triggerbot", "Delay", ClientVars.LegitBot.Weapons.Pistol.Triggerbot.delay);

		ClientVars.LegitBot.Weapons.Sniper.enable = reader.ReadBoolean("Legitbot-Sniper-Aimbot", "Enable", ClientVars.LegitBot.Weapons.Sniper.enable);
		ClientVars.LegitBot.Weapons.Sniper.onkey = reader.ReadBoolean("Legitbot-Sniper-Aimbot", "OnKey", ClientVars.LegitBot.Weapons.Sniper.onkey);
		ClientVars.LegitBot.Weapons.Sniper.key = reader.ReadInteger("Legitbot-Sniper-Aimbot", "Key", ClientVars.LegitBot.Weapons.Sniper.key);
		ClientVars.LegitBot.Weapons.Sniper.hitbox = reader.ReadInteger("Legitbot-Sniper-Aimbot", "Hitbox", ClientVars.LegitBot.Weapons.Sniper.hitbox);
		ClientVars.LegitBot.Weapons.Sniper.fov = reader.ReadFloat("Legitbot-Sniper-Aimbot", "FOV", ClientVars.LegitBot.Weapons.Sniper.fov);
		ClientVars.LegitBot.Weapons.Sniper.smoothing = reader.ReadFloat("Legitbot-Sniper-Aimbot", "Smoothing", ClientVars.LegitBot.Weapons.Sniper.smoothing);
		ClientVars.LegitBot.Weapons.Sniper.autowall = reader.ReadBoolean("Legitbot-Sniper-Aimbot", "AutoWall", ClientVars.LegitBot.Weapons.Sniper.autowall);
		ClientVars.LegitBot.Weapons.Sniper.recoilcontrol = reader.ReadBoolean("Legitbot-Sniper-Aimbot", "RecoilControl", ClientVars.LegitBot.Weapons.Sniper.recoilcontrol);
		ClientVars.LegitBot.Weapons.Sniper.awpbaim = reader.ReadBoolean("Legitbot-Sniper", "AWPBaim", ClientVars.LegitBot.Weapons.Sniper.awpbaim);
		ClientVars.LegitBot.Weapons.Sniper.Triggerbot.enable = reader.ReadBoolean("Legitbot-Sniper-Triggerbot", "Enable", ClientVars.LegitBot.Weapons.Sniper.Triggerbot.enable);
		ClientVars.LegitBot.Weapons.Sniper.Triggerbot.onkey = reader.ReadBoolean("Legitbot-Sniper-Triggerbot", "OnKey", ClientVars.LegitBot.Weapons.Sniper.Triggerbot.onkey);
		ClientVars.LegitBot.Weapons.Sniper.Triggerbot.key = reader.ReadInteger("Legitbot-Sniper-Triggerbot", "Key", ClientVars.LegitBot.Weapons.Sniper.Triggerbot.key);
		ClientVars.LegitBot.Weapons.Sniper.Triggerbot.hitbox = reader.ReadInteger("Legitbot-Sniper-Triggerbot", "Hitbox", ClientVars.LegitBot.Weapons.Sniper.Triggerbot.hitbox);
		ClientVars.LegitBot.Weapons.Sniper.Triggerbot.hitchance = reader.ReadInteger("Legitbot-Sniper-Triggerbot", "Hitchance", ClientVars.LegitBot.Weapons.Sniper.Triggerbot.hitchance);
		ClientVars.LegitBot.Weapons.Sniper.Triggerbot.delay = reader.ReadInteger("Legitbot-Sniper-Triggerbot", "Delay", ClientVars.LegitBot.Weapons.Sniper.Triggerbot.delay);

		ClientVars.LegitBot.Weapons.AutoSniper.enable = reader.ReadBoolean("Legitbot-AutoSniper-Aimbot", "Enable", ClientVars.LegitBot.Weapons.AutoSniper.enable);
		ClientVars.LegitBot.Weapons.AutoSniper.onkey = reader.ReadBoolean("Legitbot-AutoSniper-Aimbot", "OnKey", ClientVars.LegitBot.Weapons.AutoSniper.onkey);
		ClientVars.LegitBot.Weapons.AutoSniper.key = reader.ReadInteger("Legitbot-AutoSniper-Aimbot", "Key", ClientVars.LegitBot.Weapons.AutoSniper.key);
		ClientVars.LegitBot.Weapons.AutoSniper.hitbox = reader.ReadInteger("Legitbot-AutoSniper-Aimbot", "Hitbox", ClientVars.LegitBot.Weapons.AutoSniper.hitbox);
		ClientVars.LegitBot.Weapons.AutoSniper.fov = reader.ReadFloat("Legitbot-AutoSniper-Aimbot", "FOV", ClientVars.LegitBot.Weapons.AutoSniper.fov);
		ClientVars.LegitBot.Weapons.AutoSniper.smoothing = reader.ReadFloat("Legitbot-AutoSniper-Aimbot", "Smoothing", ClientVars.LegitBot.Weapons.AutoSniper.smoothing);
		ClientVars.LegitBot.Weapons.AutoSniper.autowall = reader.ReadBoolean("Legitbot-AutoSniper-Aimbot", "AutoWall", ClientVars.LegitBot.Weapons.AutoSniper.autowall);
		ClientVars.LegitBot.Weapons.AutoSniper.recoilcontrol = reader.ReadBoolean("Legitbot-AutoSniper-Aimbot", "RecoilControl", ClientVars.LegitBot.Weapons.AutoSniper.recoilcontrol);
		ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.enable = reader.ReadBoolean("Legitbot-AutoSniper-Triggerbot", "Enable", ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.enable);
		ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.onkey = reader.ReadBoolean("Legitbot-AutoSniper-Triggerbot", "OnKey", ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.onkey);
		ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.key = reader.ReadInteger("Legitbot-AutoSniper-Triggerbot", "Key", ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.key);
		ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.hitbox = reader.ReadInteger("Legitbot-AutoSniper-Triggerbot", "Hitbox", ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.hitbox);
		ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.hitchance = reader.ReadInteger("Legitbot-AutoSniper-Triggerbot", "Hitchance", ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.hitchance);
		ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.delay = reader.ReadInteger("Legitbot-AutoSniper-Triggerbot", "Delay", ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.delay);

		ClientVars.LegitBot.Weapons.Rifle.enable = reader.ReadBoolean("Legitbot-Rifle-Aimbot", "Enable", ClientVars.LegitBot.Weapons.Rifle.enable);
		ClientVars.LegitBot.Weapons.Rifle.onkey = reader.ReadBoolean("Legitbot-Rifle-Aimbot", "OnKey", ClientVars.LegitBot.Weapons.Rifle.onkey);
		ClientVars.LegitBot.Weapons.Rifle.key = reader.ReadInteger("Legitbot-Rifle-Aimbot", "Key", ClientVars.LegitBot.Weapons.Rifle.key);
		ClientVars.LegitBot.Weapons.Rifle.hitbox = reader.ReadInteger("Legitbot-Rifle-Aimbot", "Hitbox", ClientVars.LegitBot.Weapons.Rifle.hitbox);
		ClientVars.LegitBot.Weapons.Rifle.fov = reader.ReadFloat("Legitbot-Rifle-Aimbot", "FOV", ClientVars.LegitBot.Weapons.Rifle.fov);
		ClientVars.LegitBot.Weapons.Rifle.smoothing = reader.ReadFloat("Legitbot-Rifle-Aimbot", "Smoothing", ClientVars.LegitBot.Weapons.Rifle.smoothing);
		ClientVars.LegitBot.Weapons.Rifle.autowall = reader.ReadBoolean("Legitbot-Rifle-Aimbot", "AutoWall", ClientVars.LegitBot.Weapons.Rifle.autowall);
		ClientVars.LegitBot.Weapons.Rifle.recoilcontrol = reader.ReadBoolean("Legitbot-Rifle-Aimbot", "RecoilControl", ClientVars.LegitBot.Weapons.Rifle.recoilcontrol);
		ClientVars.LegitBot.Weapons.Rifle.Triggerbot.enable = reader.ReadBoolean("Legitbot-Rifle-Triggerbot", "Enable", ClientVars.LegitBot.Weapons.Rifle.Triggerbot.enable);
		ClientVars.LegitBot.Weapons.Rifle.Triggerbot.onkey = reader.ReadBoolean("Legitbot-Rifle-Triggerbot", "OnKey", ClientVars.LegitBot.Weapons.Rifle.Triggerbot.onkey);
		ClientVars.LegitBot.Weapons.Rifle.Triggerbot.key = reader.ReadInteger("Legitbot-Rifle-Triggerbot", "Key", ClientVars.LegitBot.Weapons.Rifle.Triggerbot.key);
		ClientVars.LegitBot.Weapons.Rifle.Triggerbot.hitbox = reader.ReadInteger("Legitbot-Rifle-Triggerbot", "Hitbox", ClientVars.LegitBot.Weapons.Rifle.Triggerbot.hitbox);
		ClientVars.LegitBot.Weapons.Rifle.Triggerbot.hitchance = reader.ReadInteger("Legitbot-Rifle-Triggerbot", "Hitchance", ClientVars.LegitBot.Weapons.Rifle.Triggerbot.hitchance);
		ClientVars.LegitBot.Weapons.Rifle.Triggerbot.delay = reader.ReadInteger("Legitbot-Rifle-Triggerbot", "Delay", ClientVars.LegitBot.Weapons.Rifle.Triggerbot.delay);

		ClientVars.LegitBot.Weapons.SMG.enable = reader.ReadBoolean("Legitbot-SMG-Aimbot", "Enable", ClientVars.LegitBot.Weapons.SMG.enable);
		ClientVars.LegitBot.Weapons.SMG.onkey = reader.ReadBoolean("Legitbot-SMG-Aimbot", "OnKey", ClientVars.LegitBot.Weapons.SMG.onkey);
		ClientVars.LegitBot.Weapons.SMG.key = reader.ReadInteger("Legitbot-SMG-Aimbot", "Key", ClientVars.LegitBot.Weapons.SMG.key);
		ClientVars.LegitBot.Weapons.SMG.hitbox = reader.ReadInteger("Legitbot-SMG-Aimbot", "Hitbox", ClientVars.LegitBot.Weapons.SMG.hitbox);
		ClientVars.LegitBot.Weapons.SMG.fov = reader.ReadFloat("Legitbot-SMG-Aimbot", "FOV", ClientVars.LegitBot.Weapons.SMG.fov);
		ClientVars.LegitBot.Weapons.SMG.smoothing = reader.ReadFloat("Legitbot-SMG-Aimbot", "Smoothing", ClientVars.LegitBot.Weapons.SMG.smoothing);
		ClientVars.LegitBot.Weapons.SMG.autowall = reader.ReadBoolean("Legitbot-SMG-Aimbot", "AutoWall", ClientVars.LegitBot.Weapons.SMG.autowall);
		ClientVars.LegitBot.Weapons.SMG.recoilcontrol = reader.ReadBoolean("Legitbot-SMG-Aimbot", "RecoilControl", ClientVars.LegitBot.Weapons.SMG.recoilcontrol);
		ClientVars.LegitBot.Weapons.SMG.Triggerbot.enable = reader.ReadBoolean("Legitbot-SMG-Triggerbot", "Enable", ClientVars.LegitBot.Weapons.SMG.Triggerbot.enable);
		ClientVars.LegitBot.Weapons.SMG.Triggerbot.onkey = reader.ReadBoolean("Legitbot-SMG-Triggerbot", "OnKey", ClientVars.LegitBot.Weapons.SMG.Triggerbot.onkey);
		ClientVars.LegitBot.Weapons.SMG.Triggerbot.key = reader.ReadInteger("Legitbot-SMG-Triggerbot", "Key", ClientVars.LegitBot.Weapons.SMG.Triggerbot.key);
		ClientVars.LegitBot.Weapons.SMG.Triggerbot.hitbox = reader.ReadInteger("Legitbot-SMG-Triggerbot", "Hitbox", ClientVars.LegitBot.Weapons.SMG.Triggerbot.hitbox);
		ClientVars.LegitBot.Weapons.SMG.Triggerbot.hitchance = reader.ReadInteger("Legitbot-SMG-Triggerbot", "Hitchance", ClientVars.LegitBot.Weapons.SMG.Triggerbot.hitchance);
		ClientVars.LegitBot.Weapons.SMG.Triggerbot.delay = reader.ReadInteger("Legitbot-SMG-Triggerbot", "Delay", ClientVars.LegitBot.Weapons.SMG.Triggerbot.delay);

		ClientVars.LegitBot.Weapons.Shotgun.enable = reader.ReadBoolean("Legitbot-Shotgun-Aimbot", "Enable", ClientVars.LegitBot.Weapons.Shotgun.enable);
		ClientVars.LegitBot.Weapons.Shotgun.onkey = reader.ReadBoolean("Legitbot-Shotgun-Aimbot", "OnKey", ClientVars.LegitBot.Weapons.Shotgun.onkey);
		ClientVars.LegitBot.Weapons.Shotgun.key = reader.ReadInteger("Legitbot-Shotgun-Aimbot", "Key", ClientVars.LegitBot.Weapons.Shotgun.key);
		ClientVars.LegitBot.Weapons.Shotgun.hitbox = reader.ReadInteger("Legitbot-Shotgun-Aimbot", "Hitbox", ClientVars.LegitBot.Weapons.Shotgun.hitbox);
		ClientVars.LegitBot.Weapons.Shotgun.fov = reader.ReadFloat("Legitbot-Shotgun-Aimbot", "FOV", ClientVars.LegitBot.Weapons.Shotgun.fov);
		ClientVars.LegitBot.Weapons.Shotgun.smoothing = reader.ReadFloat("Legitbot-Shotgun-Aimbot", "Smoothing", ClientVars.LegitBot.Weapons.Shotgun.smoothing);
		ClientVars.LegitBot.Weapons.Shotgun.autowall = reader.ReadBoolean("Legitbot-Shotgun-Aimbot", "AutoWall", ClientVars.LegitBot.Weapons.Shotgun.autowall);
		ClientVars.LegitBot.Weapons.Shotgun.recoilcontrol = reader.ReadBoolean("Legitbot-Shotgun-Aimbot", "RecoilControl", ClientVars.LegitBot.Weapons.Shotgun.recoilcontrol);
		ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.enable = reader.ReadBoolean("Legitbot-Shotgun-Triggerbot", "Enable", ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.enable);
		ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.onkey = reader.ReadBoolean("Legitbot-Shotgun-Triggerbot", "OnKey", ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.onkey);
		ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.key = reader.ReadInteger("Legitbot-Shotgun-Triggerbot", "Key", ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.key);
		ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.hitbox = reader.ReadInteger("Legitbot-Shotgun-Triggerbot", "Hitbox", ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.hitbox);
		ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.hitchance = reader.ReadInteger("Legitbot-Shotgun-Triggerbot", "Hitchance", ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.hitchance);
		ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.delay = reader.ReadInteger("Legitbot-Shotgun-Triggerbot", "Delay", ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.delay);


		ClientVars.Visual.Showteam = reader.ReadBoolean("Visuals", "Team-ESP", ClientVars.Visual.Showteam);
		ClientVars.Visual.BoundingBox = reader.ReadBoolean("Visuals", "Enemy-ESP", ClientVars.Visual.BoundingBox);
		ClientVars.Visual.AimLine = reader.ReadBoolean("Visuals", "Aimlines", ClientVars.Visual.AimLine);
		ClientVars.Visual.Skeleton = reader.ReadBoolean("Visuals", "Skeleton", ClientVars.Visual.Skeleton);
		ClientVars.Visual.Name = reader.ReadBoolean("Visuals", "Name", ClientVars.Visual.Name);
		ClientVars.Visual.Weapon = reader.ReadBoolean("Visuals", "Weapon", ClientVars.Visual.Weapon);
		ClientVars.Visual.Armor = reader.ReadBoolean("Visuals", "Armor", ClientVars.Visual.Armor);
		ClientVars.Visual.Vulnerabilities = reader.ReadBoolean("Visuals", "Vulnerabilities", ClientVars.Visual.Vulnerabilities);
		ClientVars.Visual.Health = reader.ReadBoolean("Visuals", "Health", ClientVars.Visual.Health);
		ClientVars.Visual.Money = reader.ReadBoolean("Visuals", "Money", ClientVars.Visual.Money);
		ClientVars.Visual.Callout = reader.ReadBoolean("Visuals", "Callout", ClientVars.Visual.Callout);
		ClientVars.Visual.Ammo = reader.ReadBoolean("Visuals", "Ammo", ClientVars.Visual.Ammo);
		ClientVars.Visual.BulletTracers = reader.ReadBoolean("Visuals", "Bullet-Tracers", ClientVars.Visual.BulletTracers);
		ClientVars.Visual.AngleLines = reader.ReadBoolean("Visuals", "Angle-Lines", ClientVars.Visual.AngleLines);
		ClientVars.Visual.ResolverESP = reader.ReadBoolean("Visuals", "Resolver-ESP", ClientVars.Visual.ResolverESP);
		ClientVars.Visual.ManualArrows = reader.ReadBoolean("Visuals", "Manual-Arrows", ClientVars.Visual.ManualArrows);

		ClientVars.Visual.LBYPredictor = reader.ReadBoolean("Visuals", "LBY-Predictor", ClientVars.Visual.LBYPredictor);


		ClientVars.Visual.Thirdperson = reader.ReadInteger("Visuals", "Third-Person", ClientVars.Visual.Thirdperson);
		ClientVars.Visual.tpdist = reader.ReadInteger("Visuals", "Third-Person-Dist", ClientVars.Visual.tpdist);
		ClientVars.Visual.ThirdpersonMode = reader.ReadInteger("Visuals", "Third-Person-Mode", ClientVars.Visual.ThirdpersonMode);
		ClientVars.Visual.GhostChams = reader.ReadBoolean("Visuals", "Ghost-Chams", ClientVars.Visual.GhostChams);
		ClientVars.Visual.GhostChamsMode = reader.ReadInteger("Visuals", "Ghost-Chams-Mode", ClientVars.Visual.GhostChamsMode);
		ClientVars.Visual.wallalpha = reader.ReadFloat("Visuals", "Wall-Alpha", ClientVars.Visual.wallalpha);
		ClientVars.Visual.propalpha = reader.ReadFloat("Visuals", "Prop-Alpha", ClientVars.Visual.propalpha);
		ClientVars.Visual.modelalpha = reader.ReadFloat("Visuals", "Model-Alpha", ClientVars.Visual.modelalpha);


		ClientVars.Visual.NightmodeVal = reader.ReadFloat("Visuals", "Nightmode-Value", ClientVars.Visual.NightmodeVal);

		ClientVars.Visual.Droppedguns = reader.ReadBoolean("Visuals", "Dropped-Weapons", ClientVars.Visual.Droppedguns);
		ClientVars.Visual.Bomb = reader.ReadBoolean("Visuals", "Bomb-ESP", ClientVars.Visual.Bomb);
		ClientVars.Visual.Grenades = reader.ReadBoolean("Visuals", "Grenade-ESP", ClientVars.Visual.Grenades);
		ClientVars.Visual.Crosshair = reader.ReadBoolean("Visuals", "Crosshair", ClientVars.Visual.Crosshair);
		ClientVars.Visual.InaccuracyCrosshair = reader.ReadBoolean("Visuals", "Inaccuracy-Crosshair", ClientVars.Visual.InaccuracyCrosshair);
		ClientVars.Visual.speclist = reader.ReadBoolean("Visuals", "Spectators", ClientVars.Visual.speclist);
		ClientVars.Visual.Hitmarker = reader.ReadBoolean("Visuals", "Hitmarker", ClientVars.Visual.Hitmarker);
		ClientVars.Visual.Arrows = reader.ReadBoolean("Visuals", "Off-Screen-ESP", ClientVars.Visual.Arrows);


		ClientVars.Visual.ShowTarget = reader.ReadBoolean("Visuals", "ShowTarget", ClientVars.Visual.ShowTarget);


		ClientVars.Visual.Glow.GlowEnemy = reader.ReadBoolean("Visuals", "Glow-Enemy", ClientVars.Visual.Glow.GlowEnemy);
		ClientVars.Visual.Glow.GlowTeam = reader.ReadBoolean("Visuals", "Glow-Team", ClientVars.Visual.Glow.GlowTeam);
		ClientVars.Visual.Glow.WeaponGlow = reader.ReadBoolean("Visuals", "Glow-Weapons", ClientVars.Visual.Glow.WeaponGlow);
		ClientVars.Visual.Glow.BombGlow = reader.ReadBoolean("Visuals", "Glow-Bomb", ClientVars.Visual.Glow.BombGlow);
		ClientVars.Visual.Glow.GrenadeGlow = reader.ReadBoolean("Visuals", "Glow-Grenades", ClientVars.Visual.Glow.GrenadeGlow);

		ClientVars.Visual.NoVisRecoil = reader.ReadBoolean("Visuals", "Visual-Recoil", ClientVars.Visual.NoVisRecoil);
		ClientVars.Visual.NoSmoke = reader.ReadBoolean("Visuals", "Smokes", ClientVars.Visual.NoSmoke);
		ClientVars.Visual.NoFlash = reader.ReadBoolean("Visuals", "Flashbangs", ClientVars.Visual.NoFlash);
		ClientVars.Visual.NoScope = reader.ReadBoolean("Visuals", "Scope", ClientVars.Visual.NoScope);

		ClientVars.Visual.Chams.Enabled = reader.ReadBoolean("Visuals", "Chams-Enemy", ClientVars.Visual.Chams.Enabled);
		ClientVars.Visual.Chams.Team = reader.ReadBoolean("Visuals", "Chams-Team", ClientVars.Visual.Chams.Team);
		ClientVars.Visual.Chams.XQZ = reader.ReadBoolean("Visuals", "Chams-XQZ", ClientVars.Visual.Chams.XQZ);
		ClientVars.Visual.handcham = reader.ReadBoolean("Visuals", "Chams-Hand", ClientVars.Visual.handcham);
		ClientVars.Visual.weaponviewcham = reader.ReadBoolean("Visuals", "Chams-Gun", ClientVars.Visual.weaponviewcham);

		ClientVars.Visual.Chams.Player_mat = reader.ReadInteger("Visuals", "Player-Mat", ClientVars.Visual.Chams.Player_mat);
		ClientVars.Visual.handmat = reader.ReadInteger("Visuals", "Arm-Mat", ClientVars.Visual.handmat);
		ClientVars.Visual.weaponmat = reader.ReadInteger("Visuals", "Weapon-Mat", ClientVars.Visual.weaponmat);
		ClientVars.Visual.Chams.GhostChamsMat = reader.ReadInteger("Visuals", "Ghost-Chams-Mat", ClientVars.Visual.Chams.GhostChamsMat);

		ClientVars.Misc.Antiuntrustedproxy = reader.ReadBoolean("Misc", "Anti-Untrusted", ClientVars.Misc.Antiuntrustedproxy);
		ClientVars.Misc.RankReveal = reader.ReadBoolean("Misc", "Rank-Reveal", ClientVars.Misc.RankReveal);
		ClientVars.Misc.AutoAccept = reader.ReadBoolean("Misc", "Auto-Accept", ClientVars.Misc.AutoAccept);
		ClientVars.Misc.Bhop = reader.ReadBoolean("Misc", "Bunny-Hop", ClientVars.Misc.Bhop);
		ClientVars.Misc.Strafe = reader.ReadBoolean("Misc", "Auto-Strafe", ClientVars.Misc.Strafe);
		ClientVars.Misc.AnimClantag = reader.ReadBoolean("Misc", "Animated-Clan", ClientVars.Misc.AnimClantag);
		ClientVars.Misc.Knifebot = reader.ReadBoolean("Misc", "KnifeBot", ClientVars.Misc.Knifebot);
		ClientVars.Misc.zeusbot = reader.ReadBoolean("Misc", "AutoTaser", ClientVars.Misc.zeusbot);



		ClientVars.Misc.fakelatency = reader.ReadBoolean("Misc", "FakeLatency", ClientVars.Misc.fakelatency);
		ClientVars.Misc.desiredlatency = reader.ReadInteger("Misc", "FakeLatency-Desire", ClientVars.Misc.desiredlatency);


		ClientVars.FakeLag.Choke = reader.ReadInteger("Misc", "FakeLag-Choke", ClientVars.FakeLag.Choke);
		ClientVars.FakeLag.ChokeMode = reader.ReadInteger("Misc", "FakeLag-Mode", ClientVars.FakeLag.ChokeMode);
		ClientVars.FakeLag.WhileShooting = reader.ReadBoolean("Misc", "FakeLag-While-Shooting", ClientVars.FakeLag.WhileShooting);
		ClientVars.FakeLag.WhileStill = reader.ReadBoolean("Misc", "FakeLag-While-Still", ClientVars.FakeLag.WhileStill);
		ClientVars.FakeLag.Onground = reader.ReadBoolean("Misc", "FakeLag-On-Ground", ClientVars.FakeLag.Onground);


		//ClientVars.Misc.crimwalk = reader.ReadInteger("Misc", "KalkWalk", ClientVars.Misc.crimwalk);
		//ClientVars.Misc.InstaExplode = reader.ReadBoolean("Misc", "Insta-Explode", ClientVars.Misc.InstaExplode);
		//ClientVars.Misc.InstaDefuse = reader.ReadBoolean("Misc", "Insta-Defuse", ClientVars.Misc.InstaDefuse);

		ClientVars.Misc.fakelatency = reader.ReadBoolean("Misc", "FakeLatency", ClientVars.Misc.fakelatency);
		ClientVars.Misc.desiredlatency = reader.ReadInteger("Misc", "FakeLatency-Desire", ClientVars.Misc.desiredlatency);

		ClientVars.Misc.autoblock = reader.ReadInteger("Misc", "Autoblock", ClientVars.Misc.autoblock);

		ClientVars.Misc.faresp = reader.ReadBoolean("Misc", "FarESP", ClientVars.Misc.faresp);


		ClientVars.Styles.espFadeIn = reader.ReadInteger("Style", "ESP-Fade-In", ClientVars.Styles.espFadeIn);
		ClientVars.Styles.espFadeOut = reader.ReadInteger("Style", "ESP-Fade-Out", ClientVars.Styles.espFadeOut);
		ClientVars.Styles.ManualArrowRounding = reader.ReadInteger("Style", "Manual-Arrow-Rounding", ClientVars.Styles.ManualArrowRounding);



		ClientVars.Col.EnemyESPHB = reader.ReadBoolean("Colors", "EnemyESPHB", ClientVars.Col.EnemyESPHB);
		ClientVars.Col.EnemyAimlineHB = reader.ReadBoolean("Colors", "AimlinesHB", ClientVars.Col.EnemyAimlineHB);
		ClientVars.Col.EnemySkeletonHB = reader.ReadBoolean("Colors", "SkeletonHB", ClientVars.Col.EnemySkeletonHB);
		ClientVars.Col.EnemyGlowHB = reader.ReadBoolean("Colors", "GlowHB", ClientVars.Col.EnemyGlowHB);
		ClientVars.Col.EnemyChamsHB = reader.ReadBoolean("Colors", "ChamsHB", ClientVars.Col.EnemyChamsHB);
		ClientVars.Col.EnemyChamsXQZHB = reader.ReadBoolean("Colors", "ChamsXQZHB", ClientVars.Col.EnemyChamsXQZHB);

		for (int i = 0; i < 4; i++)
		{
			char* section = colornames(i);
			ClientVars.Col.TeamESP[i] = reader.ReadFloat(section, "Team-ESP", ClientVars.Col.TeamESP[i]);
			ClientVars.Col.EnemyESP[i] = reader.ReadFloat(section, "Enemy-ESP", ClientVars.Col.EnemyESP[i]);
			ClientVars.Col.Aimlines[i] = reader.ReadFloat(section, "Aimlines", ClientVars.Col.Aimlines[i]);
			ClientVars.Col.Skeleton[i] = reader.ReadFloat(section, "Skeleton", ClientVars.Col.Skeleton[i]);
			ClientVars.Col.Ammo[i] = reader.ReadFloat(section, "Ammo", ClientVars.Col.Ammo[i]);
			ClientVars.Col.Crosshair[i] = reader.ReadFloat(section, "Crosshair", ClientVars.Col.Crosshair[i]);
			ClientVars.Col.InaccuracyCrosshair[i] = reader.ReadFloat(section, "Inaccuracy-Crosshair", ClientVars.Col.InaccuracyCrosshair[i]);
			ClientVars.Col.Hitmarker[i] = reader.ReadFloat(section, "Hitmarker", ClientVars.Col.Hitmarker[i]);
			ClientVars.Col.Arrows[i] = reader.ReadFloat(section, "Off-Screen-ESP", ClientVars.Col.Arrows[i]);


			ClientVars.Col.ShowTarget[i] = reader.ReadFloat(section, "ShowTarget", ClientVars.Col.ShowTarget[i]);


			ClientVars.Col.NameESP[i] = reader.ReadFloat(section, "Name", ClientVars.Col.NameESP[i]);
			ClientVars.Col.WeaponESP[i] = reader.ReadFloat(section, "Weapon", ClientVars.Col.WeaponESP[i]);
			ClientVars.Col.ArmorESP[i] = reader.ReadFloat(section, "Armor", ClientVars.Col.ArmorESP[i]);
			ClientVars.Col.ResolverESP[i] = reader.ReadFloat(section, "ResolverESP", ClientVars.Col.ResolverESP[i]);
			ClientVars.Col.BulletTracers[i] = reader.ReadFloat(section, "BulletTracers", ClientVars.Col.BulletTracers[i]);
			ClientVars.Col.Callout[i] = reader.ReadFloat(section, "Callout", ClientVars.Col.Callout[i]);
			ClientVars.Col.Health[i] = reader.ReadFloat(section, "Health", ClientVars.Col.Health[i]);
			ClientVars.Col.Money[i] = reader.ReadFloat(section, "Money", ClientVars.Col.Money[i]);
			ClientVars.Col.Vulnerabilities[i] = reader.ReadFloat(section, "Vulnerabilities", ClientVars.Col.Vulnerabilities[i]);
			ClientVars.Col.AngleLinesLBY[i] = reader.ReadFloat(section, "AngleLines-LBY", ClientVars.Col.AngleLinesLBY[i]);
			ClientVars.Col.AngleLinesREAL[i] = reader.ReadFloat(section, "AngleLines-REAL", ClientVars.Col.AngleLinesREAL[i]);
			ClientVars.Col.AngleLinesFAKE[i] = reader.ReadFloat(section, "AngleLines-FAKE", ClientVars.Col.AngleLinesFAKE[i]);
			ClientVars.Col.DroppedWeapons[i] = reader.ReadFloat(section, "DroppedWeapons", ClientVars.Col.DroppedWeapons[i]);
			ClientVars.Col.DroppedWeapons[i] = reader.ReadFloat(section, "Manual-Arrows-Active", ClientVars.Col.ManualArrowsActive[i]);
			ClientVars.Col.DroppedWeapons[i] = reader.ReadFloat(section, "Manual-Arrows-Not-Active", ClientVars.Col.ManualArrowsNotActive[i]);

			ClientVars.Col.GhostChams[i] = reader.ReadFloat(section, "Ghost-Chams", ClientVars.Col.GhostChams[i]);

			ClientVars.Col.EnemyGlow[i] = reader.ReadFloat(section, "Glow-Enemy", ClientVars.Col.EnemyGlow[i]);
			ClientVars.Col.TeamGlow[i] = reader.ReadFloat(section, "Glow-Team", ClientVars.Col.TeamGlow[i]);
			ClientVars.Col.WeaponGlow[i] = reader.ReadFloat(section, "Glow-Weapons", ClientVars.Col.WeaponGlow[i]);
			ClientVars.Col.BombGlow[i] = reader.ReadFloat(section, "Glow-Bomb", ClientVars.Col.BombGlow[i]);
			ClientVars.Col.GrenadeGlow[i] = reader.ReadFloat(section, "Glow-Grenades", ClientVars.Col.GrenadeGlow[i]);

			ClientVars.Col.EnemyChams[i] = reader.ReadFloat(section, "Enemy-Chams", ClientVars.Col.EnemyChams[i]);
			ClientVars.Col.TeamChams[i] = reader.ReadFloat(section, "Team-Chams", ClientVars.Col.TeamChams[i]);
			ClientVars.Col.EnemyChamsXQZ[i] = reader.ReadFloat(section, "Chams-XQZ", ClientVars.Col.EnemyChamsXQZ[i]);
			ClientVars.Col.HandCham[i] = reader.ReadFloat(section, "Chams-Hand", ClientVars.Col.HandCham[i]);
			ClientVars.Col.WeaponViewCham[i] = reader.ReadFloat(section, "Chams-Gun", ClientVars.Col.WeaponViewCham[i]);


			ClientVars.Styles.Colors.Menuborder[i] = reader.ReadFloat(section, "Menu-Border", ClientVars.Styles.Colors.Menuborder[i]);
			ClientVars.Styles.Colors.MenuBackground[i] = reader.ReadFloat(section, "Menu-Background", ClientVars.Styles.Colors.MenuBackground[i]);
			ClientVars.Styles.Colors.Border[i] = reader.ReadFloat(section, "Borders", ClientVars.Styles.Colors.Border[i]);
			ClientVars.Styles.Colors.Controls[i] = reader.ReadFloat(section, "Controls", ClientVars.Styles.Colors.Controls[i]);
			ClientVars.Styles.Colors.Text[i] = reader.ReadFloat(section, "Text", ClientVars.Styles.Colors.Text[i]);
			ClientVars.Styles.Colors.MainMenuButtons[i] = reader.ReadFloat(section, "Main-Menu-Buttons", ClientVars.Styles.Colors.MainMenuButtons[i]);
			ClientVars.Styles.Colors.GunMenuButtons[i] = reader.ReadFloat(section, "Gun-Menu-Buttons", ClientVars.Styles.Colors.GunMenuButtons[i]);
		}
	}

	void Save(char* name)
	{
		static TCHAR path[MAX_PATH];
		std::string folder, file;
		if (strlen(name) > 0)
		{
			if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
			{
				folder = std::string(path) + strenc("\\KalkonenWare\\");
				file = std::string(path) + strenc("\\KalkonenWare\\") + std::string(name) + strenc(".cfg");
			}
		}
		else
		{
			if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
			{
				folder = std::string(path) + strenc("\\KalkonenWare\\");
				file = std::string(path) + strenc("\\KalkonenWare\\config.cfg");
			}
		}

		CreateDirectory(folder.c_str(), NULL);

		CIniWriter writer(file.c_str());


		writer.WriteBoolean("Ragebot", "Enable", ClientVars.Ragebot.Enable);
		writer.WriteFloat("Ragebot", "FOV", ClientVars.Ragebot.FOV);
		writer.WriteBoolean("Ragebot", "Autowall", ClientVars.Ragebot.Autowall);
		writer.WriteInteger("Ragebot", "Selection", ClientVars.Ragebot.AimbotSelection);
		writer.WriteBoolean("Ragebot", "Autopistol", ClientVars.Ragebot.AutoPistol);
		writer.WriteBoolean("Ragebot", "pSilent", ClientVars.Ragebot.pSilent);
		writer.WriteBoolean("Ragebot", "Autoshoot", ClientVars.Ragebot.autofire);
		writer.WriteBoolean("Ragebot", "Autoscope", ClientVars.Ragebot.autoscope);
		writer.WriteBoolean("Ragebot", "NoRecoil", ClientVars.Ragebot.NoRecoil);
		writer.WriteBoolean("Ragebot", "Position-Adjustment", ClientVars.Ragebot.BackTrack);
		writer.WriteInteger("Ragebot", "Resolver", ClientVars.Ragebot.Resolver);
		writer.WriteInteger("Ragebot", "Pitch-Resolver", ClientVars.Ragebot.ResolvePitch);
		writer.WriteInteger("Ragebot", "Override-Key", ClientVars.Ragebot.overrideresolver);
		writer.WriteInteger("Ragebot", "Override-Add", ClientVars.Ragebot.overrideradd);

		writer.WriteInteger("Ragebot-Pistol", "Hitbox", ClientVars.Ragebot.Weapons.Pistol.Hitbox);
		writer.WriteInteger("Ragebot-Pistol", "Hitscan", ClientVars.Ragebot.Weapons.Pistol.Hitscan.strength);
		writer.WriteInteger("Ragebot-Pistol", "Hitchance", ClientVars.Ragebot.Weapons.Pistol.HitChance);
		writer.WriteInteger("Ragebot-Pistol", "MinDMG", ClientVars.Ragebot.Weapons.Pistol.MinDmg);
		writer.WriteFloat("Ragebot-Pistol", "Headscale", ClientVars.Ragebot.Weapons.Pistol.Headscale);
		writer.WriteFloat("Ragebot-Pistol", "Bodyscale", ClientVars.Ragebot.Weapons.Pistol.Bodyscale);
		writer.WriteBoolean("Ragebot-Pistol-Hitscan", "Head", ClientVars.Ragebot.Weapons.Pistol.Hitscan.head);
		writer.WriteBoolean("Ragebot-Pistol-Hitscan", "Neck", ClientVars.Ragebot.Weapons.Pistol.Hitscan.neck);
		writer.WriteBoolean("Ragebot-Pistol-Hitscan", "Arms", ClientVars.Ragebot.Weapons.Pistol.Hitscan.arms);
		writer.WriteBoolean("Ragebot-Pistol-Hitscan", "Chest", ClientVars.Ragebot.Weapons.Pistol.Hitscan.chest);
		writer.WriteBoolean("Ragebot-Pistol-Hitscan", "Stomach", ClientVars.Ragebot.Weapons.Pistol.Hitscan.stomach);
		writer.WriteBoolean("Ragebot-Pistol-Hitscan", "Pelvis", ClientVars.Ragebot.Weapons.Pistol.Hitscan.pelvis);
		writer.WriteBoolean("Ragebot-Pistol-Hitscan", "Legs", ClientVars.Ragebot.Weapons.Pistol.Hitscan.legs);
		writer.WriteBoolean("Ragebot-Pistol-Hitscan", "Feet", ClientVars.Ragebot.Weapons.Pistol.Hitscan.feet);

		writer.WriteBoolean("Ragebot-Pistol", "BaimIFLethal", ClientVars.Ragebot.Weapons.Pistol.baimiflethal);



		writer.WriteInteger("Ragebot-Sniper", "Hitbox", ClientVars.Ragebot.Weapons.Sniper.Hitbox);
		writer.WriteInteger("Ragebot-Sniper", "Hitscan", ClientVars.Ragebot.Weapons.Sniper.Hitscan.strength);
		writer.WriteInteger("Ragebot-Sniper", "Hitchance", ClientVars.Ragebot.Weapons.Sniper.HitChance);
		writer.WriteInteger("Ragebot-Sniper", "MinDMG", ClientVars.Ragebot.Weapons.Sniper.MinDmg);
		writer.WriteFloat("Ragebot-Sniper", "Headscale", ClientVars.Ragebot.Weapons.Sniper.Headscale);
		writer.WriteFloat("Ragebot-Sniper", "Bodyscale", ClientVars.Ragebot.Weapons.Sniper.Bodyscale);
		writer.WriteBoolean("Ragebot-Sniper-Hitscan", "Head", ClientVars.Ragebot.Weapons.Sniper.Hitscan.head);
		writer.WriteBoolean("Ragebot-Sniper-Hitscan", "Neck", ClientVars.Ragebot.Weapons.Sniper.Hitscan.neck);
		writer.WriteBoolean("Ragebot-Sniper-Hitscan", "Arms", ClientVars.Ragebot.Weapons.Sniper.Hitscan.arms);
		writer.WriteBoolean("Ragebot-Sniper-Hitscan", "Chest", ClientVars.Ragebot.Weapons.Sniper.Hitscan.chest);
		writer.WriteBoolean("Ragebot-Sniper-Hitscan", "Stomach", ClientVars.Ragebot.Weapons.Sniper.Hitscan.stomach);
		writer.WriteBoolean("Ragebot-Sniper-Hitscan", "Pelvis", ClientVars.Ragebot.Weapons.Sniper.Hitscan.pelvis);
		writer.WriteBoolean("Ragebot-Sniper-Hitscan", "Legs", ClientVars.Ragebot.Weapons.Sniper.Hitscan.legs);
		writer.WriteBoolean("Ragebot-Sniper-Hitscan", "Feet", ClientVars.Ragebot.Weapons.Sniper.Hitscan.feet);

		writer.WriteBoolean("Ragebot-Sniper", "BaimIFLethal", ClientVars.Ragebot.Weapons.Sniper.baimiflethal);



		writer.WriteInteger("Ragebot-AutoSniper", "Hitbox", ClientVars.Ragebot.Weapons.AutoSniper.Hitbox);
		writer.WriteInteger("Ragebot-AutoSniper", "Hitscan", ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.strength);
		writer.WriteInteger("Ragebot-AutoSniper", "Hitchance", ClientVars.Ragebot.Weapons.AutoSniper.HitChance);
		writer.WriteInteger("Ragebot-AutoSniper", "MinDMG", ClientVars.Ragebot.Weapons.AutoSniper.MinDmg);
		writer.WriteFloat("Ragebot-AutoSniper", "Headscale", ClientVars.Ragebot.Weapons.AutoSniper.Headscale);
		writer.WriteFloat("Ragebot-AutoSniper", "Bodyscale", ClientVars.Ragebot.Weapons.AutoSniper.Bodyscale);
		writer.WriteBoolean("Ragebot-AutoSniper-Hitscan", "Head", ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.head);
		writer.WriteBoolean("Ragebot-AutoSniper-Hitscan", "Neck", ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.neck);
		writer.WriteBoolean("Ragebot-AutoSniper-Hitscan", "Arms", ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.arms);
		writer.WriteBoolean("Ragebot-AutoSniper-Hitscan", "Chest", ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.chest);
		writer.WriteBoolean("Ragebot-AutoSniper-Hitscan", "Stomach", ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.stomach);
		writer.WriteBoolean("Ragebot-AutoSniper-Hitscan", "Pelvis", ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.pelvis);
		writer.WriteBoolean("Ragebot-AutoSniper-Hitscan", "Legs", ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.legs);
		writer.WriteBoolean("Ragebot-AutoSniper-Hitscan", "Feet", ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.feet);

		writer.WriteBoolean("Ragebot-AutoSniper", "BaimIFLethal", ClientVars.Ragebot.Weapons.AutoSniper.baimiflethal);



		writer.WriteInteger("Ragebot-Rifle", "Hitbox", ClientVars.Ragebot.Weapons.Rifle.Hitbox);
		writer.WriteInteger("Ragebot-Rifle", "Hitscan", ClientVars.Ragebot.Weapons.Rifle.Hitscan.strength);
		writer.WriteInteger("Ragebot-Rifle", "Hitchance", ClientVars.Ragebot.Weapons.Rifle.HitChance);
		writer.WriteInteger("Ragebot-Rifle", "MinDMG", ClientVars.Ragebot.Weapons.Rifle.MinDmg);
		writer.WriteFloat("Ragebot-Rifle", "Headscale", ClientVars.Ragebot.Weapons.Rifle.Headscale);
		writer.WriteFloat("Ragebot-Rifle", "Bodyscale", ClientVars.Ragebot.Weapons.Rifle.Bodyscale);
		writer.WriteBoolean("Ragebot-Rifle-Hitscan", "Head", ClientVars.Ragebot.Weapons.Rifle.Hitscan.head);
		writer.WriteBoolean("Ragebot-Rifle-Hitscan", "Neck", ClientVars.Ragebot.Weapons.Rifle.Hitscan.neck);
		writer.WriteBoolean("Ragebot-Rifle-Hitscan", "Arms", ClientVars.Ragebot.Weapons.Rifle.Hitscan.arms);
		writer.WriteBoolean("Ragebot-Rifle-Hitscan", "Chest", ClientVars.Ragebot.Weapons.Rifle.Hitscan.chest);
		writer.WriteBoolean("Ragebot-Rifle-Hitscan", "Stomach", ClientVars.Ragebot.Weapons.Rifle.Hitscan.stomach);
		writer.WriteBoolean("Ragebot-Rifle-Hitscan", "Pelvis", ClientVars.Ragebot.Weapons.Rifle.Hitscan.pelvis);
		writer.WriteBoolean("Ragebot-Rifle-Hitscan", "Legs", ClientVars.Ragebot.Weapons.Rifle.Hitscan.legs);
		writer.WriteBoolean("Ragebot-Rifle-Hitscan", "Feet", ClientVars.Ragebot.Weapons.Rifle.Hitscan.feet);

		writer.WriteBoolean("Ragebot-Rifle", "BaimIFLethal", ClientVars.Ragebot.Weapons.Rifle.baimiflethal);



		writer.WriteInteger("Ragebot-SMG", "Hitbox", ClientVars.Ragebot.Weapons.SMG.Hitbox);
		writer.WriteInteger("Ragebot-SMG", "Hitscan", ClientVars.Ragebot.Weapons.SMG.Hitscan.strength);
		writer.WriteInteger("Ragebot-SMG", "Hitchance", ClientVars.Ragebot.Weapons.SMG.HitChance);
		writer.WriteInteger("Ragebot-SMG", "MinDMG", ClientVars.Ragebot.Weapons.SMG.MinDmg);
		writer.WriteFloat("Ragebot-SMG", "Headscale", ClientVars.Ragebot.Weapons.SMG.Headscale);
		writer.WriteFloat("Ragebot-SMG", "Bodyscale", ClientVars.Ragebot.Weapons.SMG.Bodyscale);
		writer.WriteBoolean("Ragebot-SMG-Hitscan", "Head", ClientVars.Ragebot.Weapons.SMG.Hitscan.head);
		writer.WriteBoolean("Ragebot-SMG-Hitscan", "Neck", ClientVars.Ragebot.Weapons.SMG.Hitscan.neck);
		writer.WriteBoolean("Ragebot-SMG-Hitscan", "Arms", ClientVars.Ragebot.Weapons.SMG.Hitscan.arms);
		writer.WriteBoolean("Ragebot-SMG-Hitscan", "Chest", ClientVars.Ragebot.Weapons.SMG.Hitscan.chest);
		writer.WriteBoolean("Ragebot-SMG-Hitscan", "Stomach", ClientVars.Ragebot.Weapons.SMG.Hitscan.stomach);
		writer.WriteBoolean("Ragebot-SMG-Hitscan", "Pelvis", ClientVars.Ragebot.Weapons.SMG.Hitscan.pelvis);
		writer.WriteBoolean("Ragebot-SMG-Hitscan", "Legs", ClientVars.Ragebot.Weapons.SMG.Hitscan.legs);
		writer.WriteBoolean("Ragebot-SMG-Hitscan", "Feet", ClientVars.Ragebot.Weapons.SMG.Hitscan.feet);

		writer.WriteBoolean("Ragebot-SMG", "BaimIFLethal", ClientVars.Ragebot.Weapons.SMG.baimiflethal);



		writer.WriteInteger("Ragebot-Shotgun", "Hitbox", ClientVars.Ragebot.Weapons.Shotgun.Hitbox);
		writer.WriteInteger("Ragebot-Shotgun", "Hitscan", ClientVars.Ragebot.Weapons.Shotgun.Hitscan.strength);
		writer.WriteInteger("Ragebot-Shotgun", "Hitchance", ClientVars.Ragebot.Weapons.Shotgun.HitChance);
		writer.WriteInteger("Ragebot-Shotgun", "MinDMG", ClientVars.Ragebot.Weapons.Shotgun.MinDmg);
		writer.WriteFloat("Ragebot-Shotgun", "Headscale", ClientVars.Ragebot.Weapons.Shotgun.Headscale);
		writer.WriteFloat("Ragebot-Shotgun", "Bodyscale", ClientVars.Ragebot.Weapons.Shotgun.Bodyscale);
		writer.WriteBoolean("Ragebot-Shotgun-Hitscan", "Head", ClientVars.Ragebot.Weapons.Shotgun.Hitscan.head);
		writer.WriteBoolean("Ragebot-Shotgun-Hitscan", "Neck", ClientVars.Ragebot.Weapons.Shotgun.Hitscan.neck);
		writer.WriteBoolean("Ragebot-Shotgun-Hitscan", "Arms", ClientVars.Ragebot.Weapons.Shotgun.Hitscan.arms);
		writer.WriteBoolean("Ragebot-Shotgun-Hitscan", "Chest", ClientVars.Ragebot.Weapons.Shotgun.Hitscan.chest);
		writer.WriteBoolean("Ragebot-Shotgun-Hitscan", "Stomach", ClientVars.Ragebot.Weapons.Shotgun.Hitscan.stomach);
		writer.WriteBoolean("Ragebot-Shotgun-Hitscan", "Pelvis", ClientVars.Ragebot.Weapons.Shotgun.Hitscan.pelvis);
		writer.WriteBoolean("Ragebot-Shotgun-Hitscan", "Legs", ClientVars.Ragebot.Weapons.Shotgun.Hitscan.legs);
		writer.WriteBoolean("Ragebot-Shotgun-Hitscan", "Feet", ClientVars.Ragebot.Weapons.Shotgun.Hitscan.feet);

		writer.WriteBoolean("Ragebot-Shotgun", "BaimIFLethal", ClientVars.Ragebot.Weapons.Shotgun.baimiflethal);



		writer.WriteBoolean("Ragebot-AA", "Enable", ClientVars.AntiAim.enabled);

		writer.WriteInteger("Ragebot-AA-Stand", "Pitch", ClientVars.AntiAim.Stand.Pitch);
		writer.WriteInteger("Ragebot-AA-Stand", "Custom-Pitch", ClientVars.AntiAim.Stand.PitchAdd);
		writer.WriteInteger("Ragebot-AA-Stand", "Yaw", ClientVars.AntiAim.Stand.Yaw);
		writer.WriteInteger("Ragebot-AA-Stand", "Yaw-Adder", ClientVars.AntiAim.Stand.YawAdd);
		writer.WriteInteger("Ragebot-AA-Stand", "Fake-Yaw", ClientVars.AntiAim.Stand.Fake);
		writer.WriteInteger("Ragebot-AA-Stand", "Fake-Yaw-Adder", ClientVars.AntiAim.Stand.FakeAdd);

		writer.WriteInteger("Ragebot-AA-Move", "Pitch", ClientVars.AntiAim.Move.Pitch);
		writer.WriteInteger("Ragebot-AA-Move", "Custom-Pitch", ClientVars.AntiAim.Move.PitchAdd);
		writer.WriteInteger("Ragebot-AA-Move", "Yaw", ClientVars.AntiAim.Move.Yaw);
		writer.WriteInteger("Ragebot-AA-Move", "Yaw-Adder", ClientVars.AntiAim.Move.YawAdd);
		writer.WriteInteger("Ragebot-AA-Move", "Fake-Yaw", ClientVars.AntiAim.Move.Fake);
		writer.WriteInteger("Ragebot-AA-Move", "Fake-Yaw-Adder", ClientVars.AntiAim.Move.FakeAdd);

		writer.WriteInteger("Ragebot-AA-InAir", "Pitch", ClientVars.AntiAim.Air.Pitch);
		writer.WriteInteger("Ragebot-AA-InAir", "Custom-Pitch", ClientVars.AntiAim.Air.PitchAdd);
		writer.WriteInteger("Ragebot-AA-InAir", "Yaw", ClientVars.AntiAim.Air.Yaw);
		writer.WriteInteger("Ragebot-AA-InAir", "Yaw-Adder", ClientVars.AntiAim.Air.YawAdd);
		writer.WriteInteger("Ragebot-AA-InAir", "Fake-Yaw", ClientVars.AntiAim.Air.Fake);
		writer.WriteInteger("Ragebot-AA-InAir", "Fake-Yaw-Adder", ClientVars.AntiAim.Air.FakeAdd);

		writer.WriteInteger("Ragebot-AA-Misc", "LBY-Delta", ClientVars.AntiAim.Misc.lbyDelta);
		writer.WriteFloat("Ragebot-AA-Misc", "Spinbot-Speed", ClientVars.AntiAim.Misc.SpinbotSpeed);
		writer.WriteFloat("Ragebot-AA-Misc", "Jitter-Speed", ClientVars.AntiAim.Misc.JitterSpeed);
		writer.WriteInteger("Ragebot-AA-Misc", "Jitter-Range", ClientVars.AntiAim.Misc.JitterRange);
		writer.WriteInteger("Ragebot-AA-Misc", "Switch-Add", ClientVars.AntiAim.Misc.SwitchAdd);
		writer.WriteFloat("Ragebot-AA-Misc", "Switch-Speed", ClientVars.AntiAim.Misc.SwitchSpeed);
		writer.WriteInteger("Ragebot-AA-Misc", "FakeWalk", ClientVars.AntiAim.Misc.fakewalk);
		writer.WriteInteger("Ragebot-AA-Misc", "Manual-Left", ClientVars.AntiAim.Misc.leftAA);
		writer.WriteInteger("Ragebot-AA-Misc", "Manual-Right", ClientVars.AntiAim.Misc.rightAA);
		writer.WriteInteger("Ragebot-AA-Misc", "Manual-Down", ClientVars.AntiAim.Misc.downAA);
		//writer.WriteInteger("Ragebot-AA-Misc", "Manual-Up", ClientVars.AntiAim.Misc.uppAA);
		writer.WriteBoolean("Ragebot-AA-Misc", "On-grenades", ClientVars.AntiAim.OnGreandes);
		writer.WriteBoolean("Ragebot-AA-Misc", "On-ladders", ClientVars.AntiAim.OnLadders);
		writer.WriteBoolean("Ragebot-AA-Misc", "On-knife", ClientVars.AntiAim.OnKnife);

		writer.WriteBoolean("Legitbot", "Enable", ClientVars.LegitBot.enable);
		writer.WriteBoolean("Legitbot", "BackTrack", ClientVars.LegitBot.backtrack);
		writer.WriteBoolean("Legitbot-AA", "Enable", ClientVars.LegitBot.AntiAim.enabled);

		writer.WriteInteger("Legitbot-AA-Stand", "Yaw", ClientVars.LegitBot.AntiAim.Stand.Yaw);
		writer.WriteInteger("Legitbot-AA-Stand", "Yaw-Adder", ClientVars.LegitBot.AntiAim.Stand.YawAdd);

		writer.WriteInteger("Legitbot-AA-Move", "Yaw", ClientVars.LegitBot.AntiAim.Move.Yaw);
		writer.WriteInteger("Legitbot-AA-Move", "Yaw-Adder", ClientVars.LegitBot.AntiAim.Move.YawAdd);

		writer.WriteInteger("Legitbot-AA-InAir", "Yaw", ClientVars.LegitBot.AntiAim.Air.Yaw);
		writer.WriteInteger("Legitbot-AA-InAir", "Yaw-Adder", ClientVars.LegitBot.AntiAim.Air.YawAdd);

		writer.WriteInteger("Legitbot-AA-Misc", "LBY-Delta", ClientVars.LegitBot.AntiAim.Misc.lbyDelta);
		writer.WriteFloat("Legitbot-AA-Misc", "Spinbot-Speed", ClientVars.LegitBot.AntiAim.Misc.SpinbotSpeed);
		writer.WriteFloat("Legitbot-AA-Misc", "Jitter-Speed", ClientVars.LegitBot.AntiAim.Misc.JitterSpeed);
		writer.WriteInteger("Legitbot-AA-Misc", "Jitter-Range", ClientVars.LegitBot.AntiAim.Misc.JitterRange);
		writer.WriteInteger("Legitbot-AA-Misc", "Switch-Add", ClientVars.LegitBot.AntiAim.Misc.SwitchAdd);
		writer.WriteFloat("Legitbot-AA-Misc", "Switch-Speed", ClientVars.LegitBot.AntiAim.Misc.SwitchSpeed);
		writer.WriteInteger("Legitbot-AA-Misc", "Manual-Left", ClientVars.LegitBot.AntiAim.Misc.leftAA);
		writer.WriteInteger("Legitbot-AA-Misc", "Manual-Right", ClientVars.LegitBot.AntiAim.Misc.rightAA);
		writer.WriteInteger("Legitbot-AA-Misc", "Manual-Down", ClientVars.LegitBot.AntiAim.Misc.downAA);
		//writer.WriteInteger("Legitbot-AA-Misc", "Manual-Up", ClientVars.LegitBot.AntiAim.Misc.upAA);
		writer.WriteBoolean("Legitbot-AA-Misc", "On-grenades", ClientVars.LegitBot.AntiAim.OnGreandes);
		writer.WriteBoolean("Legitbot-AA-Misc", "On-ladders", ClientVars.LegitBot.AntiAim.OnLadders);
		writer.WriteBoolean("Legitbot-AA-Misc", "On-knife", ClientVars.LegitBot.AntiAim.OnKnife);

		writer.WriteBoolean("Legitbot-Pistol-Aimbot", "Enable", ClientVars.LegitBot.Weapons.Pistol.enable);
		writer.WriteBoolean("Legitbot-Pistol-Aimbot", "OnKey", ClientVars.LegitBot.Weapons.Pistol.onkey);
		writer.WriteInteger("Legitbot-Pistol-Aimbot", "Key", ClientVars.LegitBot.Weapons.Pistol.key);
		writer.WriteInteger("Legitbot-Pistol-Aimbot", "Hitbox", ClientVars.LegitBot.Weapons.Pistol.hitbox);
		writer.WriteFloat("Legitbot-Pistol-Aimbot", "FOV", ClientVars.LegitBot.Weapons.Pistol.fov);
		writer.WriteFloat("Legitbot-Pistol-Aimbot", "Smoothing", ClientVars.LegitBot.Weapons.Pistol.smoothing);
		writer.WriteBoolean("Legitbot-Pistol-Aimbot", "AutoWall", ClientVars.LegitBot.Weapons.Pistol.autowall);
		writer.WriteBoolean("Legitbot-Pistol-Aimbot", "RecoilControl", ClientVars.LegitBot.Weapons.Pistol.recoilcontrol);
		writer.WriteBoolean("Legitbot-Pistol", "AutoPistol", ClientVars.LegitBot.Weapons.Pistol.autopistol);
		writer.WriteBoolean("Legitbot-Pistol", "AutoRevolver", ClientVars.LegitBot.Weapons.Pistol.autorevolver);
		writer.WriteBoolean("Legitbot-Pistol-Triggerbot", "Enable", ClientVars.LegitBot.Weapons.Pistol.Triggerbot.enable);
		writer.WriteBoolean("Legitbot-Pistol-Triggerbot", "OnKey", ClientVars.LegitBot.Weapons.Pistol.Triggerbot.onkey);
		writer.WriteInteger("Legitbot-Pistol-Triggerbot", "Key", ClientVars.LegitBot.Weapons.Pistol.Triggerbot.key);
		writer.WriteInteger("Legitbot-Pistol-Triggerbot", "Hitbox", ClientVars.LegitBot.Weapons.Pistol.Triggerbot.hitbox);
		writer.WriteInteger("Legitbot-Pistol-Triggerbot", "Hitchance", ClientVars.LegitBot.Weapons.Pistol.Triggerbot.hitchance);
		writer.WriteInteger("Legitbot-Pistol-Triggerbot", "Delay", ClientVars.LegitBot.Weapons.Pistol.Triggerbot.delay);

		writer.WriteBoolean("Legitbot-Sniper-Aimbot", "Enable", ClientVars.LegitBot.Weapons.Sniper.enable);
		writer.WriteBoolean("Legitbot-Sniper-Aimbot", "OnKey", ClientVars.LegitBot.Weapons.Sniper.onkey);
		writer.WriteInteger("Legitbot-Sniper-Aimbot", "Key", ClientVars.LegitBot.Weapons.Sniper.key);
		writer.WriteInteger("Legitbot-Sniper-Aimbot", "Hitbox", ClientVars.LegitBot.Weapons.Sniper.hitbox);
		writer.WriteFloat("Legitbot-Sniper-Aimbot", "FOV", ClientVars.LegitBot.Weapons.Sniper.fov);
		writer.WriteFloat("Legitbot-Sniper-Aimbot", "Smoothing", ClientVars.LegitBot.Weapons.Sniper.smoothing);
		writer.WriteBoolean("Legitbot-Sniper-Aimbot", "AutoWall", ClientVars.LegitBot.Weapons.Sniper.autowall);
		writer.WriteBoolean("Legitbot-Sniper-Aimbot", "RecoilControl", ClientVars.LegitBot.Weapons.Sniper.recoilcontrol);
		writer.WriteBoolean("Legitbot-Sniper", "AWPBaim", ClientVars.LegitBot.Weapons.Sniper.awpbaim);
		writer.WriteBoolean("Legitbot-Sniper-Triggerbot", "Enable", ClientVars.LegitBot.Weapons.Sniper.Triggerbot.enable);
		writer.WriteBoolean("Legitbot-Sniper-Triggerbot", "OnKey", ClientVars.LegitBot.Weapons.Sniper.Triggerbot.onkey);
		writer.WriteInteger("Legitbot-Sniper-Triggerbot", "Key", ClientVars.LegitBot.Weapons.Sniper.Triggerbot.key);
		writer.WriteInteger("Legitbot-Sniper-Triggerbot", "Hitbox", ClientVars.LegitBot.Weapons.Sniper.Triggerbot.hitbox);
		writer.WriteInteger("Legitbot-Sniper-Triggerbot", "Hitchance", ClientVars.LegitBot.Weapons.Sniper.Triggerbot.hitchance);
		writer.WriteInteger("Legitbot-Sniper-Triggerbot", "Delay", ClientVars.LegitBot.Weapons.Sniper.Triggerbot.delay);

		writer.WriteBoolean("Legitbot-AutoSniper-Aimbot", "Enable", ClientVars.LegitBot.Weapons.AutoSniper.enable);
		writer.WriteBoolean("Legitbot-AutoSniper-Aimbot", "OnKey", ClientVars.LegitBot.Weapons.AutoSniper.onkey);
		writer.WriteInteger("Legitbot-AutoSniper-Aimbot", "Key", ClientVars.LegitBot.Weapons.AutoSniper.key);
		writer.WriteInteger("Legitbot-AutoSniper-Aimbot", "Hitbox", ClientVars.LegitBot.Weapons.AutoSniper.hitbox);
		writer.WriteFloat("Legitbot-AutoSniper-Aimbot", "FOV", ClientVars.LegitBot.Weapons.AutoSniper.fov);
		writer.WriteFloat("Legitbot-AutoSniper-Aimbot", "Smoothing", ClientVars.LegitBot.Weapons.AutoSniper.smoothing);
		writer.WriteBoolean("Legitbot-AutoSniper-Aimbot", "AutoWall", ClientVars.LegitBot.Weapons.AutoSniper.autowall);
		writer.WriteBoolean("Legitbot-AutoSniper-Aimbot", "RecoilControl", ClientVars.LegitBot.Weapons.AutoSniper.recoilcontrol);
		writer.WriteBoolean("Legitbot-AutoSniper-Triggerbot", "Enable", ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.enable);
		writer.WriteBoolean("Legitbot-AutoSniper-Triggerbot", "OnKey", ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.onkey);
		writer.WriteInteger("Legitbot-AutoSniper-Triggerbot", "Key", ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.key);
		writer.WriteInteger("Legitbot-AutoSniper-Triggerbot", "Hitbox", ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.hitbox);
		writer.WriteInteger("Legitbot-AutoSniper-Triggerbot", "Hitchance", ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.hitchance);
		writer.WriteInteger("Legitbot-AutoSniper-Triggerbot", "Delay", ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.delay);

		writer.WriteBoolean("Legitbot-Rifle-Aimbot", "Enable", ClientVars.LegitBot.Weapons.Rifle.enable);
		writer.WriteBoolean("Legitbot-Rifle-Aimbot", "OnKey", ClientVars.LegitBot.Weapons.Rifle.onkey);
		writer.WriteInteger("Legitbot-Rifle-Aimbot", "Key", ClientVars.LegitBot.Weapons.Rifle.key);
		writer.WriteInteger("Legitbot-Rifle-Aimbot", "Hitbox", ClientVars.LegitBot.Weapons.Rifle.hitbox);
		writer.WriteFloat("Legitbot-Rifle-Aimbot", "FOV", ClientVars.LegitBot.Weapons.Rifle.fov);
		writer.WriteFloat("Legitbot-Rifle-Aimbot", "Smoothing", ClientVars.LegitBot.Weapons.Rifle.smoothing);
		writer.WriteBoolean("Legitbot-Rifle-Aimbot", "AutoWall", ClientVars.LegitBot.Weapons.Rifle.autowall);
		writer.WriteBoolean("Legitbot-Rifle-Aimbot", "RecoilControl", ClientVars.LegitBot.Weapons.Rifle.recoilcontrol);
		writer.WriteBoolean("Legitbot-Rifle-Triggerbot", "Enable", ClientVars.LegitBot.Weapons.Rifle.Triggerbot.enable);
		writer.WriteBoolean("Legitbot-Rifle-Triggerbot", "OnKey", ClientVars.LegitBot.Weapons.Rifle.Triggerbot.onkey);
		writer.WriteInteger("Legitbot-Rifle-Triggerbot", "Key", ClientVars.LegitBot.Weapons.Rifle.Triggerbot.key);
		writer.WriteInteger("Legitbot-Rifle-Triggerbot", "Hitbox", ClientVars.LegitBot.Weapons.Rifle.Triggerbot.hitbox);
		writer.WriteInteger("Legitbot-Rifle-Triggerbot", "Hitchance", ClientVars.LegitBot.Weapons.Rifle.Triggerbot.hitchance);
		writer.WriteInteger("Legitbot-Rifle-Triggerbot", "Delay", ClientVars.LegitBot.Weapons.Rifle.Triggerbot.delay);

		writer.WriteBoolean("Legitbot-SMG-Aimbot", "Enable", ClientVars.LegitBot.Weapons.SMG.enable);
		writer.WriteBoolean("Legitbot-SMG-Aimbot", "OnKey", ClientVars.LegitBot.Weapons.SMG.onkey);
		writer.WriteInteger("Legitbot-SMG-Aimbot", "Key", ClientVars.LegitBot.Weapons.SMG.key);
		writer.WriteInteger("Legitbot-SMG-Aimbot", "Hitbox", ClientVars.LegitBot.Weapons.SMG.hitbox);
		writer.WriteFloat("Legitbot-SMG-Aimbot", "FOV", ClientVars.LegitBot.Weapons.SMG.fov);
		writer.WriteFloat("Legitbot-SMG-Aimbot", "Smoothing", ClientVars.LegitBot.Weapons.SMG.smoothing);
		writer.WriteBoolean("Legitbot-SMG-Aimbot", "AutoWall", ClientVars.LegitBot.Weapons.SMG.autowall);
		writer.WriteBoolean("Legitbot-SMG-Aimbot", "RecoilControl", ClientVars.LegitBot.Weapons.SMG.recoilcontrol);
		writer.WriteBoolean("Legitbot-SMG-Triggerbot", "Enable", ClientVars.LegitBot.Weapons.SMG.Triggerbot.enable);
		writer.WriteBoolean("Legitbot-SMG-Triggerbot", "OnKey", ClientVars.LegitBot.Weapons.SMG.Triggerbot.onkey);
		writer.WriteInteger("Legitbot-SMG-Triggerbot", "Key", ClientVars.LegitBot.Weapons.SMG.Triggerbot.key);
		writer.WriteInteger("Legitbot-SMG-Triggerbot", "Hitbox", ClientVars.LegitBot.Weapons.SMG.Triggerbot.hitbox);
		writer.WriteInteger("Legitbot-SMG-Triggerbot", "Hitchance", ClientVars.LegitBot.Weapons.SMG.Triggerbot.hitchance);
		writer.WriteInteger("Legitbot-SMG-Triggerbot", "Delay", ClientVars.LegitBot.Weapons.SMG.Triggerbot.delay);

		writer.WriteBoolean("Legitbot-Shotgun-Aimbot", "Enable", ClientVars.LegitBot.Weapons.Shotgun.enable);
		writer.WriteBoolean("Legitbot-Shotgun-Aimbot", "OnKey", ClientVars.LegitBot.Weapons.Shotgun.onkey);
		writer.WriteInteger("Legitbot-Shotgun-Aimbot", "Key", ClientVars.LegitBot.Weapons.Shotgun.key);
		writer.WriteInteger("Legitbot-Shotgun-Aimbot", "Hitbox", ClientVars.LegitBot.Weapons.Shotgun.hitbox);
		writer.WriteFloat("Legitbot-Shotgun-Aimbot", "FOV", ClientVars.LegitBot.Weapons.Shotgun.fov);
		writer.WriteFloat("Legitbot-Shotgun-Aimbot", "Smoothing", ClientVars.LegitBot.Weapons.Shotgun.smoothing);
		writer.WriteBoolean("Legitbot-Shotgun-Aimbot", "AutoWall", ClientVars.LegitBot.Weapons.Shotgun.autowall);
		writer.WriteBoolean("Legitbot-Shotgun-Aimbot", "RecoilControl", ClientVars.LegitBot.Weapons.Shotgun.recoilcontrol);
		writer.WriteBoolean("Legitbot-Shotgun-Triggerbot", "Enable", ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.enable);
		writer.WriteBoolean("Legitbot-Shotgun-Triggerbot", "OnKey", ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.onkey);
		writer.WriteInteger("Legitbot-Shotgun-Triggerbot", "Key", ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.key);
		writer.WriteInteger("Legitbot-Shotgun-Triggerbot", "Hitbox", ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.hitbox);
		writer.WriteInteger("Legitbot-Shotgun-Triggerbot", "Hitchance", ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.hitchance);
		writer.WriteInteger("Legitbot-Shotgun-Triggerbot", "Delay", ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.delay);

		writer.WriteBoolean("Visuals", "Team-ESP", ClientVars.Visual.Showteam);
		writer.WriteBoolean("Visuals", "Enemy-ESP", ClientVars.Visual.BoundingBox);
		writer.WriteBoolean("Visuals", "Aimlines", ClientVars.Visual.AimLine);
		writer.WriteBoolean("Visuals", "Skeleton", ClientVars.Visual.Skeleton);
		writer.WriteBoolean("Visuals", "Name", ClientVars.Visual.Name);
		writer.WriteBoolean("Visuals", "Weapon", ClientVars.Visual.Weapon);
		writer.WriteBoolean("Visuals", "Armor", ClientVars.Visual.Armor);
		writer.WriteBoolean("Visuals", "Vulnerabilities", ClientVars.Visual.Vulnerabilities);
		writer.WriteBoolean("Visuals", "Health", ClientVars.Visual.Health);
		writer.WriteBoolean("Visuals", "Money", ClientVars.Visual.Money);
		writer.WriteBoolean("Visuals", "Callout", ClientVars.Visual.Callout);
		writer.WriteBoolean("Visuals", "Ammo", ClientVars.Visual.Ammo);
		writer.WriteBoolean("Visuals", "Bullet-Tracers", ClientVars.Visual.BulletTracers);
		writer.WriteBoolean("Visuals", "Angle-Lines", ClientVars.Visual.AngleLines);
		writer.WriteBoolean("Visuals", "Resolver-ESP", ClientVars.Visual.ResolverESP);

		writer.WriteBoolean("Visuals", "Manual-Arrows", ClientVars.Visual.ManualArrows);

		writer.WriteBoolean("Visuals", "LBY-Predictor", ClientVars.Visual.LBYPredictor);



		writer.WriteInteger("Visuals", "Third-Person", ClientVars.Visual.Thirdperson);
		writer.WriteInteger("Visuals", "Third-Person-Dist", ClientVars.Visual.tpdist);
		writer.WriteInteger("Visuals", "Third-Person-Mode", ClientVars.Visual.ThirdpersonMode);
		writer.WriteBoolean("Visuals", "Ghost-Chams", ClientVars.Visual.GhostChams);
		writer.WriteInteger("Visuals", "Ghost-Chams-Mode", ClientVars.Visual.GhostChamsMode);
		writer.WriteFloat("Visuals", "Wall-Alpha", ClientVars.Visual.wallalpha);
		writer.WriteFloat("Visuals", "Prop-Alpha", ClientVars.Visual.propalpha);
		writer.WriteFloat("Visuals", "Model-Alpha", ClientVars.Visual.modelalpha);


		writer.WriteFloat("Visuals", "Nightmode-Value", ClientVars.Visual.NightmodeVal);
		writer.WriteBoolean("Visuals", "ShowTarget", ClientVars.Visual.ShowTarget);


		writer.WriteBoolean("Visuals", "Dropped-Weapons", ClientVars.Visual.Droppedguns);
		writer.WriteBoolean("Visuals", "Bomb-ESP", ClientVars.Visual.Bomb);
		writer.WriteBoolean("Visuals", "Grenade-ESP", ClientVars.Visual.Grenades);
		writer.WriteBoolean("Visuals", "Crosshair", ClientVars.Visual.Crosshair);
		writer.WriteBoolean("Visuals", "Inaccuracy-Crosshair", ClientVars.Visual.InaccuracyCrosshair);
		writer.WriteBoolean("Visuals", "Spectators", ClientVars.Visual.speclist);
		writer.WriteBoolean("Visuals", "Hitmarker", ClientVars.Visual.Hitmarker);
		writer.WriteBoolean("Visuals", "Off-Screen-ESP", ClientVars.Visual.Arrows);

		writer.WriteBoolean("Visuals", "Glow-Enemy", ClientVars.Visual.Glow.GlowEnemy);
		writer.WriteBoolean("Visuals", "Glow-Team", ClientVars.Visual.Glow.GlowTeam);
		writer.WriteBoolean("Visuals", "Glow-Weapons", ClientVars.Visual.Glow.WeaponGlow);
		writer.WriteBoolean("Visuals", "Glow-Bomb", ClientVars.Visual.Glow.BombGlow);
		writer.WriteBoolean("Visuals", "Glow-Grenades", ClientVars.Visual.Glow.GrenadeGlow);

		writer.WriteBoolean("Visuals", "Visual-Recoil", ClientVars.Visual.NoVisRecoil);
		writer.WriteBoolean("Visuals", "Smokes", ClientVars.Visual.NoSmoke);
		writer.WriteBoolean("Visuals", "Flashbangs", ClientVars.Visual.NoFlash);
		writer.WriteBoolean("Visuals", "Scope", ClientVars.Visual.NoScope);

		writer.WriteBoolean("Visuals", "Chams-Enemy", ClientVars.Visual.Chams.Enabled);
		writer.WriteBoolean("Visuals", "Chams-Team", ClientVars.Visual.Chams.Team);
		writer.WriteBoolean("Visuals", "Chams-XQZ", ClientVars.Visual.Chams.XQZ);
		writer.WriteBoolean("Visuals", "Chams-Hand", ClientVars.Visual.handcham);
		writer.WriteBoolean("Visuals", "Chams-Gun", ClientVars.Visual.weaponviewcham);

		writer.WriteInteger("Visuals", "Player-Mat", ClientVars.Visual.Chams.Player_mat);
		writer.WriteInteger("Visuals", "Arm-Mat", ClientVars.Visual.handmat);
		writer.WriteInteger("Visuals", "Weapon-Mat", ClientVars.Visual.weaponmat);
		writer.WriteInteger("Visuals", "Ghost-Chams-Mat", ClientVars.Visual.Chams.GhostChamsMat);

		writer.WriteBoolean("Misc", "Anti-Untrusted", ClientVars.Misc.Antiuntrustedproxy);
		writer.WriteBoolean("Misc", "Rank-Reveal", ClientVars.Misc.RankReveal);
		writer.WriteBoolean("Misc", "Auto-Accept", ClientVars.Misc.AutoAccept);
		writer.WriteBoolean("Misc", "Bunny-Hop", ClientVars.Misc.Bhop);
		writer.WriteBoolean("Misc", "Auto-Strafe", ClientVars.Misc.Strafe);
		writer.WriteBoolean("Misc", "Animated-Clan", ClientVars.Misc.AnimClantag);
		writer.WriteInteger("Misc", "KnifeBot", ClientVars.Misc.Knifebot);
		writer.WriteInteger("Misc", "AutoTaser", ClientVars.Misc.zeusbot);



		writer.WriteBoolean("Misc", "FakeLatency", ClientVars.Misc.fakelatency);
		writer.WriteInteger("Misc", "FakeLatency-Desire", ClientVars.Misc.desiredlatency);

		writer.WriteBoolean("Misc", "FarESP", ClientVars.Misc.faresp);


		writer.WriteInteger("Misc", "FakeLag-Choke", ClientVars.FakeLag.Choke);
		writer.WriteInteger("Misc", "FakeLag-Mode", ClientVars.FakeLag.ChokeMode);
		writer.WriteBoolean("Misc", "FakeLag-While-Shooting", ClientVars.FakeLag.WhileShooting);
		writer.WriteBoolean("Misc", "FakeLag-While-Still", ClientVars.FakeLag.WhileStill);
		writer.WriteBoolean("Misc", "FakeLag-On-Ground", ClientVars.FakeLag.Onground);

		writer.WriteInteger("Misc", "Autoblock", ClientVars.Misc.autoblock);


		//writer.WriteInteger("Misc", "KalkWalk", ClientVars.Misc.crimwalk);
		//writer.WriteBoolean("Misc", "Insta-Explode", ClientVars.Misc.InstaExplode);
		//writer.WriteBoolean("Misc", "Insta-Defuse", ClientVars.Misc.InstaDefuse);

		writer.WriteBoolean("Misc", "FakeLatency", ClientVars.Misc.fakelatency);
		writer.WriteInteger("Misc", "FakeLatency-Desire", ClientVars.Misc.desiredlatency);


		writer.WriteInteger("Style", "ESP-Fade-In", ClientVars.Styles.espFadeIn);
		writer.WriteInteger("Style", "ESP-Fade-Out", ClientVars.Styles.espFadeOut);
		writer.WriteInteger("Style", "Manual-Arrow-Rounding", ClientVars.Styles.ManualArrowRounding);


		writer.WriteBoolean("Colors", "EnemyESPHB", ClientVars.Col.EnemyESPHB);
		writer.WriteBoolean("Colors", "AimlinesHB", ClientVars.Col.EnemyAimlineHB);
		writer.WriteBoolean("Colors", "SkeletonHB", ClientVars.Col.EnemySkeletonHB);
		writer.WriteBoolean("Colors", "GlowHB", ClientVars.Col.EnemyGlowHB);
		writer.WriteBoolean("Colors", "ChamsHB", ClientVars.Col.EnemyChamsHB);
		writer.WriteBoolean("Colors", "ChamsXQZHB", ClientVars.Col.EnemyChamsXQZHB);

		for (int i = 0; i < 4; i++)
		{
			char* section = colornames(i);
			writer.WriteFloat(section, "Team-ESP", ClientVars.Col.TeamESP[i]);
			writer.WriteFloat(section, "Enemy-ESP", ClientVars.Col.EnemyESP[i]);
			writer.WriteFloat(section, "Aimlines", ClientVars.Col.Aimlines[i]);
			writer.WriteFloat(section, "Skeleton", ClientVars.Col.Skeleton[i]);
			writer.WriteFloat(section, "Name", ClientVars.Col.NameESP[i]);
			writer.WriteFloat(section, "Weapon", ClientVars.Col.WeaponESP[i]);
			writer.WriteFloat(section, "Armor", ClientVars.Col.ArmorESP[i]);
			writer.WriteFloat(section, "ResolverESP", ClientVars.Col.ResolverESP[i]);
			writer.WriteFloat(section, "BulletTracers", ClientVars.Col.BulletTracers[i]);
			writer.WriteFloat(section, "Callout", ClientVars.Col.Callout[i]);
			writer.WriteFloat(section, "Health", ClientVars.Col.Health[i]);
			writer.WriteFloat(section, "Money", ClientVars.Col.Money[i]);
			writer.WriteFloat(section, "Vulnerabilities", ClientVars.Col.Vulnerabilities[i]);
			writer.WriteFloat(section, "AngleLines-LBY", ClientVars.Col.AngleLinesLBY[i]);
			writer.WriteFloat(section, "AngleLines-REAL", ClientVars.Col.AngleLinesREAL[i]);
			writer.WriteFloat(section, "AngleLines-FAKE", ClientVars.Col.AngleLinesFAKE[i]);
			writer.WriteFloat(section, "DroppedWeapons", ClientVars.Col.DroppedWeapons[i]);

			writer.WriteFloat(section, "Manual-Arrows-Active", ClientVars.Col.ManualArrowsActive[i]);
			writer.WriteFloat(section, "Manual-Arrows-Not-Active", ClientVars.Col.ManualArrowsNotActive[i]);

			writer.WriteFloat(section, "Ammo", ClientVars.Col.Ammo[i]);
			writer.WriteFloat(section, "Crosshair", ClientVars.Col.Crosshair[i]);
			writer.WriteFloat(section, "Inaccuracy-Crosshair", ClientVars.Col.InaccuracyCrosshair[i]);
			writer.WriteFloat(section, "Hitmarker", ClientVars.Col.Hitmarker[i]);
			writer.WriteFloat(section, "Off-Screen-ESP", ClientVars.Col.Arrows[i]);
			writer.WriteFloat(section, "Ghost-Chams", ClientVars.Col.GhostChams[i]);


			writer.WriteFloat(section, "ShowTarget", ClientVars.Col.ShowTarget[i]);



			writer.WriteFloat(section, "Glow-Enemy", ClientVars.Col.EnemyGlow[i]);
			writer.WriteFloat(section, "Glow-Team", ClientVars.Col.TeamGlow[i]);
			writer.WriteFloat(section, "Glow-Weapons", ClientVars.Col.WeaponGlow[i]);
			writer.WriteFloat(section, "Glow-Bomb", ClientVars.Col.BombGlow[i]);
			writer.WriteFloat(section, "Glow-Grenades", ClientVars.Col.GrenadeGlow[i]);

			writer.WriteFloat(section, "Enemy-Chams", ClientVars.Col.EnemyChams[i]);
			writer.WriteFloat(section, "Team-Chams", ClientVars.Col.TeamChams[i]);
			writer.WriteFloat(section, "Chams-XQZ", ClientVars.Col.EnemyChamsXQZ[i]);
			writer.WriteFloat(section, "Chams-Hand", ClientVars.Col.HandCham[i]);
			writer.WriteFloat(section, "Chams-Gun", ClientVars.Col.WeaponViewCham[i]);



			writer.WriteFloat(section, "Menu-Border", ClientVars.Styles.Colors.Menuborder[i]);
			writer.WriteFloat(section, "Menu-Background", ClientVars.Styles.Colors.MenuBackground[i]);
			writer.WriteFloat(section, "Borders", ClientVars.Styles.Colors.Border[i]);
			writer.WriteFloat(section, "Controls", ClientVars.Styles.Colors.Controls[i]);
			writer.WriteFloat(section, "Text", ClientVars.Styles.Colors.Text[i]);
			writer.WriteFloat(section, "Main-Menu-Buttons", ClientVars.Styles.Colors.MainMenuButtons[i]);
			writer.WriteFloat(section, "Gun-Menu-Buttons", ClientVars.Styles.Colors.GunMenuButtons[i]);
		}
	}
}