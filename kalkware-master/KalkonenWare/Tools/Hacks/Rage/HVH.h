#pragma once
#include "../../stdafx.h"
#include "../Misc.h"
#include "Aimbot.h"
#include "AntiAims.h"
#include "../../Utils/LocalInfo.h"

static int choked = 0;

class Fakelag
{
private:
	void Choke()
	{
		if (choked > 13)
			choked = 0;
		
		/**
		if (Interfaces.pGlobalVars->choke) {
			if (ClientVars.FakeLag.Choke > 0)
				choked = ClientVars.FakeLag.Choke - 1;
			Hacks.SendPacket = true;
			return;
		}
		*/
		int chokeMode = ClientVars.FakeLag.ChokeMode;

		if (!ClientVars.FakeLag.WhileStill && Hacks.LocalPlayer->GetVecVelocity().Length2D() <= 0.1f)
			chokeMode = 0;

		if (!ClientVars.FakeLag.WhileShooting && Misc::Shooting())
			chokeMode = 0;

		if (!ClientVars.FakeLag.Onground && Hacks.LocalPlayer->GetFlags() & FL_ONGROUND)
			chokeMode = 0;


		switch (chokeMode)
		{
		case 0:
			Hacks.SendPacket = (Interfaces.pGlobalVars->tickcount % 2) == 1;
			return;
		case 1:
			ClientVars.FakeLag.Choke <= choked ? choked = 0 : choked++;
			break;
		}

		Hacks.SendPacket = choked == 0;
	}
public:
	void Run(CInput::CUserCmd* cmd)
	{
		Choke();
	}
} FakeLag;


class AntiAim
{
private:

public:
	void Run(CInput::CUserCmd* cmd)
	{
		CBaseCombatWeapon* pWeapon = Hacks.LocalWeapon;

		if (!ClientVars.AntiAim.enabled)
			return;
		if (Misc::Shooting())
			return;
		if (cmd->buttons & IN_USE)
			return;
		if (!ClientVars.AntiAim.OnLadders && Hacks.LocalPlayer->GetMoveType() == MOVETYPE_LADDER)
			return;

		if (Hacks.LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP)
			return;
		if (!ClientVars.AntiAim.OnKnife && pWeapon->IsKnife())
			return;
		if (!ClientVars.AntiAim.OnGreandes && pWeapon->IsGrenade())
			return;

		AntiAims::SetAntiAim(cmd);

	}
} AntiAim;
