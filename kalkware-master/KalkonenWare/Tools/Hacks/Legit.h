#pragma once
#include "../../stdafx.h"
#include "../Utils/Hitbox.h"
#include "../Utils/Playerlist.h"
#include "../Utils/HitboxLists.h"

static bool LineGoesThroughSmoke(Vector pos1, Vector pos2) throw()
{
	typedef bool(*LineGoesThroughSmokeFn)(float, float, float, float, float, float, short);

	LineGoesThroughSmokeFn LineGoesThroughSmokeEx;
	LineGoesThroughSmokeEx = (LineGoesThroughSmokeFn)(Utils.PFindPattern("client.dll", "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0"));
	return LineGoesThroughSmokeEx(pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z, 1);
}

static bool IsVisible(Vector& vecAbsStart, Vector& vecAbsEnd, CBaseEntity* pLocal, CBaseEntity* pBaseEnt, bool smokeCheck) throw()
{
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;

	filter.pSkip = pLocal;

	ray.Init(vecAbsStart, vecAbsEnd);

	Interfaces.pTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);

	bool visible = (tr.m_pEnt == pBaseEnt || tr.fraction >= 0.96f);

	if (visible && smokeCheck)
		visible = !LineGoesThroughSmoke(vecAbsStart, vecAbsEnd);

	return visible;
}


static int GetHitbox() {
	CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

	CBaseCombatWeapon* weapon = pLocal->GetActiveBaseCombatWeapon();
	if (weapon)
	{
		if (weapon->isAWP() && ClientVars.LegitBot.Weapons.Sniper.awpbaim)
			return 2;

		if (weapon->isAWP() || weapon->isScout())
			return ClientVars.LegitBot.Weapons.Sniper.hitbox;

		if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper())
			return ClientVars.LegitBot.Weapons.AutoSniper.hitbox;

		if (weapon->isPistol())
			return ClientVars.LegitBot.Weapons.Pistol.hitbox;

		if (weapon->isRifle() || weapon->isMachineW())
			return ClientVars.LegitBot.Weapons.Rifle.hitbox;

		if (weapon->isSmgW())
			return ClientVars.LegitBot.Weapons.SMG.hitbox;

		if (weapon->isShotgun())
			return ClientVars.LegitBot.Weapons.Shotgun.hitbox;
	}
}

static bool shouldAutoWall() {
	CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

	CBaseCombatWeapon* weapon = pLocal->GetActiveBaseCombatWeapon();
	if (weapon)
	{
		if (weapon->isAWP() || weapon->isScout())
			return ClientVars.LegitBot.Weapons.Sniper.autowall;

		if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper())
			return ClientVars.LegitBot.Weapons.AutoSniper.autowall;

		if (weapon->isPistol())
			return ClientVars.LegitBot.Weapons.Pistol.autowall;

		if (weapon->isRifle() || weapon->isMachineW())
			return ClientVars.LegitBot.Weapons.Rifle.autowall;

		if (weapon->isSmgW())
			return ClientVars.LegitBot.Weapons.SMG.autowall;

		if (weapon->isShotgun())
			return ClientVars.LegitBot.Weapons.Shotgun.autowall;
	}
}

std::vector<Vector> MainHitbox(CBaseEntity* pTarget, matrix3x4 BoneMatrix[128])
{
	std::vector<Vector> Points;
	int Aimspot = GetHitbox();

	switch (Aimspot) {
	case 0:
		Points = Misc::GetMultiplePointsForHitbox(pTarget, 0, BoneMatrix);
		break;
	case 1:
		Points = Misc::GetMultiplePointsForHitbox(pTarget, 1, BoneMatrix);
		break;
	case 2:
		Points = Misc::GetMultiplePointsForHitbox(pTarget, 6, BoneMatrix);
		break;
	case 3:
		Points = Misc::GetMultiplePointsForHitbox(pTarget, 3, BoneMatrix);//pelvis
		break;
	case 4:
		Points = Misc::GetMultiplePointsForHitbox(pTarget, 4, BoneMatrix);//stomach
		break;
	case 5:
		Points = Misc::GetMultiplePointsForHitbox(pTarget, 0, BoneMatrix);
		break;
	}
	return Points;
}


Vector RunAimScan(CBaseEntity* pTarget, float &simtime, Vector& origin)
{
	Vector vEyePos = Hacks.LocalPlayer->GetEyePosition();
	auto wpn_data = Hacks.LocalWeapon->GetCSWpnData();

	bool found = false;

	matrix3x4 BoneMatrix[128];

	pTarget->SetupBones(BoneMatrix, 128, 0x100, Interfaces.pGlobalVars->curtime);
	simtime = pTarget->GetSimulationTime();

	origin = pTarget->GetVecOrigin();

	for (auto HitBox : MainHitbox(pTarget, BoneMatrix)) {
		if (IsVisible(vEyePos, HitBox, Hacks.LocalPlayer, pTarget, false)) {
			if (HitBox != Vector(0, 0, 0))
				return HitBox;
		}
		int damage_given = Autowall::GetDamage(HitBox);
		if (shouldAutoWall() && damage_given > 0) {
			if (HitBox != Vector(0, 0, 0))
				return HitBox;
		}
	}

	return Vector(0, 0, 0);
}
class Legitbot
{
private:

public:
	bool shouldTriggerbot() {
		if (!ClientVars.LegitBot.enable)
			return false;
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		CBaseCombatWeapon* weapon = pLocal->GetActiveBaseCombatWeapon();
		if (weapon)
		{
			if (weapon->isAWP() || weapon->isScout())
				return (ClientVars.LegitBot.Weapons.Sniper.Triggerbot.enable && ClientVars.LegitBot.Weapons.Sniper.recoilcontrol && ((ClientVars.LegitBot.Weapons.Sniper.Triggerbot.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.Sniper.Triggerbot.key) && ClientVars.LegitBot.Weapons.Sniper.Triggerbot.key > 0) || !ClientVars.LegitBot.Weapons.Sniper.Triggerbot.onkey));

			if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper())
				return (ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.enable && ClientVars.LegitBot.Weapons.AutoSniper.recoilcontrol) && ((ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.key) && ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.key > 0) || !ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.onkey);

			if (weapon->isPistol())
				return (ClientVars.LegitBot.Weapons.Pistol.Triggerbot.enable && ClientVars.LegitBot.Weapons.Pistol.recoilcontrol && ((ClientVars.LegitBot.Weapons.Pistol.Triggerbot.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.Pistol.Triggerbot.key) && ClientVars.LegitBot.Weapons.Pistol.Triggerbot.key > 0) || !ClientVars.LegitBot.Weapons.Pistol.Triggerbot.onkey));

			if (weapon->isRifle() || weapon->isMachineW())
				return (ClientVars.LegitBot.Weapons.Rifle.Triggerbot.enable && ClientVars.LegitBot.Weapons.Rifle.recoilcontrol && ((ClientVars.LegitBot.Weapons.Rifle.Triggerbot.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.Rifle.Triggerbot.key) && ClientVars.LegitBot.Weapons.Rifle.Triggerbot.key > 0) || !ClientVars.LegitBot.Weapons.Rifle.Triggerbot.onkey));

			if (weapon->isSmgW())
				return (ClientVars.LegitBot.Weapons.SMG.Triggerbot.enable && ClientVars.LegitBot.Weapons.SMG.recoilcontrol && ((ClientVars.LegitBot.Weapons.SMG.Triggerbot.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.SMG.Triggerbot.key) && ClientVars.LegitBot.Weapons.SMG.Triggerbot.key > 0) || !ClientVars.LegitBot.Weapons.SMG.Triggerbot.onkey));

			if (weapon->isShotgun())
				return (ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.enable && ClientVars.LegitBot.Weapons.Shotgun.recoilcontrol && ((ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.key) && ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.key > 0) || !ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.onkey));
		}
	}

	bool canAimbot() {
		if (!ClientVars.LegitBot.enable)
			return false;
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		CBaseCombatWeapon* weapon = pLocal->GetActiveBaseCombatWeapon();
		if (weapon)
		{
			if (weapon->isAWP() || weapon->isScout())
				return (ClientVars.LegitBot.Weapons.Sniper.enable && ((ClientVars.LegitBot.Weapons.Sniper.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.Sniper.key) && ClientVars.LegitBot.Weapons.Sniper.key > 0) || !ClientVars.LegitBot.Weapons.Sniper.onkey));

			if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper())
				return (ClientVars.LegitBot.Weapons.AutoSniper.enable && ((ClientVars.LegitBot.Weapons.AutoSniper.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.AutoSniper.key) && ClientVars.LegitBot.Weapons.AutoSniper.key > 0) || !ClientVars.LegitBot.Weapons.AutoSniper.onkey));

			if (weapon->isPistol())
				return (ClientVars.LegitBot.Weapons.Pistol.enable && ((ClientVars.LegitBot.Weapons.Pistol.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.Pistol.key) && ClientVars.LegitBot.Weapons.Pistol.key > 0) || !ClientVars.LegitBot.Weapons.Pistol.onkey));

			if (weapon->isRifle() || weapon->isMachineW())
				return (ClientVars.LegitBot.Weapons.Rifle.enable && ((ClientVars.LegitBot.Weapons.Rifle.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.Rifle.key) && ClientVars.LegitBot.Weapons.Rifle.key > 0) || !ClientVars.LegitBot.Weapons.Rifle.onkey));

			if (weapon->isSmgW())
				return (ClientVars.LegitBot.Weapons.SMG.enable && ((ClientVars.LegitBot.Weapons.SMG.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.SMG.key) && ClientVars.LegitBot.Weapons.SMG.key > 0) || !ClientVars.LegitBot.Weapons.SMG.onkey));

			if (weapon->isShotgun())
				return (ClientVars.LegitBot.Weapons.Shotgun.enable && ((ClientVars.LegitBot.Weapons.Shotgun.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.Shotgun.key) && ClientVars.LegitBot.Weapons.Shotgun.key > 0) || !ClientVars.LegitBot.Weapons.Shotgun.onkey));
		}
	}

	bool canTriggerbot() {
		if (!ClientVars.LegitBot.enable)
			return false;
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		CBaseCombatWeapon* weapon = pLocal->GetActiveBaseCombatWeapon();
		if (weapon)
		{
			if (weapon->isAWP() || weapon->isScout())
				return (ClientVars.LegitBot.Weapons.Sniper.enable && ((ClientVars.LegitBot.Weapons.Sniper.Triggerbot.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.Sniper.Triggerbot.key) && ClientVars.LegitBot.Weapons.Sniper.Triggerbot.key > 0) || !ClientVars.LegitBot.Weapons.Sniper.Triggerbot.onkey));

			if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper())
				return (ClientVars.LegitBot.Weapons.AutoSniper.enable && ((ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.key) && ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.key > 0) || !ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.onkey));

			if (weapon->isPistol())
				return (ClientVars.LegitBot.Weapons.Pistol.enable && ((ClientVars.LegitBot.Weapons.Pistol.Triggerbot.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.Pistol.Triggerbot.key) && ClientVars.LegitBot.Weapons.Pistol.Triggerbot.key > 0) || !ClientVars.LegitBot.Weapons.Pistol.Triggerbot.onkey));

			if (weapon->isRifle() || weapon->isMachineW())
				return (ClientVars.LegitBot.Weapons.Rifle.enable && ((ClientVars.LegitBot.Weapons.Rifle.Triggerbot.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.Rifle.Triggerbot.key) && ClientVars.LegitBot.Weapons.Rifle.Triggerbot.key > 0) || !ClientVars.LegitBot.Weapons.Rifle.Triggerbot.onkey));

			if (weapon->isSmgW())
				return (ClientVars.LegitBot.Weapons.SMG.enable && ((ClientVars.LegitBot.Weapons.SMG.Triggerbot.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.SMG.Triggerbot.key) && ClientVars.LegitBot.Weapons.SMG.Triggerbot.key > 0) || !ClientVars.LegitBot.Weapons.SMG.Triggerbot.onkey));

			if (weapon->isShotgun())
				return (ClientVars.LegitBot.Weapons.Shotgun.enable && ((ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.key) && ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.key > 0) || !ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.onkey));
		}
	}

	bool shouldControlRecoil() {
		if(!ClientVars.LegitBot.enable)
			return false;
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		CBaseCombatWeapon* weapon = pLocal->GetActiveBaseCombatWeapon();
		if (weapon)
		{
			if (weapon->isAWP() || weapon->isScout())
				return (ClientVars.LegitBot.Weapons.Sniper.enable && ClientVars.LegitBot.Weapons.Sniper.recoilcontrol && ((ClientVars.LegitBot.Weapons.Sniper.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.Sniper.key) && ClientVars.LegitBot.Weapons.Sniper.key > 0) || !ClientVars.LegitBot.Weapons.Sniper.onkey));

			if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper())
				return (ClientVars.LegitBot.Weapons.AutoSniper.enable && ClientVars.LegitBot.Weapons.AutoSniper.recoilcontrol) && ((ClientVars.LegitBot.Weapons.AutoSniper.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.AutoSniper.key) && ClientVars.LegitBot.Weapons.AutoSniper.key > 0) || !ClientVars.LegitBot.Weapons.AutoSniper.onkey);

			if (weapon->isPistol())
				return (ClientVars.LegitBot.Weapons.Pistol.enable && ClientVars.LegitBot.Weapons.Pistol.recoilcontrol && ((ClientVars.LegitBot.Weapons.Pistol.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.Pistol.key) && ClientVars.LegitBot.Weapons.Pistol.key > 0) || !ClientVars.LegitBot.Weapons.Pistol.onkey));

			if (weapon->isRifle() || weapon->isMachineW())
				return (ClientVars.LegitBot.Weapons.Rifle.enable && ClientVars.LegitBot.Weapons.Rifle.recoilcontrol && ((ClientVars.LegitBot.Weapons.Rifle.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.Rifle.key) && ClientVars.LegitBot.Weapons.Rifle.key > 0) || !ClientVars.LegitBot.Weapons.Rifle.onkey));

			if (weapon->isSmgW())
				return (ClientVars.LegitBot.Weapons.SMG.enable && ClientVars.LegitBot.Weapons.SMG.recoilcontrol && ((ClientVars.LegitBot.Weapons.SMG.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.SMG.key) && ClientVars.LegitBot.Weapons.SMG.key > 0) || !ClientVars.LegitBot.Weapons.SMG.onkey));

			if (weapon->isShotgun())
				return (ClientVars.LegitBot.Weapons.Shotgun.enable && ClientVars.LegitBot.Weapons.Shotgun.recoilcontrol && ((ClientVars.LegitBot.Weapons.Shotgun.onkey && GetAsyncKeyState(ClientVars.LegitBot.Weapons.Shotgun.key) && ClientVars.LegitBot.Weapons.Shotgun.key > 0) || !ClientVars.LegitBot.Weapons.Shotgun.onkey));
		}
	}

	float getWeaponFOV() {
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		CBaseCombatWeapon* weapon = pLocal->GetActiveBaseCombatWeapon();
		if (weapon)
		{
			if (weapon->isAWP() || weapon->isScout())
				return ClientVars.LegitBot.Weapons.Sniper.fov;

			if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper())
				return ClientVars.LegitBot.Weapons.AutoSniper.fov;

			if (weapon->isPistol())
				return ClientVars.LegitBot.Weapons.Pistol.fov;

			if (weapon->isRifle() || weapon->isMachineW())
				return ClientVars.LegitBot.Weapons.Rifle.fov;

			if (weapon->isSmgW())
				return ClientVars.LegitBot.Weapons.SMG.fov;

			if (weapon->isShotgun())
				return ClientVars.LegitBot.Weapons.Shotgun.fov;
		}
	}


	float getHitchance() {
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		CBaseCombatWeapon* weapon = pLocal->GetActiveBaseCombatWeapon();
		if (weapon)
		{
			if (weapon->isAWP() || weapon->isScout())
				return ClientVars.LegitBot.Weapons.Sniper.Triggerbot.hitchance;

			if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper())
				return ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.hitchance;

			if (weapon->isPistol())
				return ClientVars.LegitBot.Weapons.Pistol.Triggerbot.hitchance;

			if (weapon->isRifle() || weapon->isMachineW())
				return ClientVars.LegitBot.Weapons.Rifle.Triggerbot.hitchance;

			if (weapon->isSmgW())
				return ClientVars.LegitBot.Weapons.SMG.Triggerbot.hitchance;

			if (weapon->isShotgun())
				return ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.hitchance;
		}

	}

	float getTriggerbotHitbox() {
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		CBaseCombatWeapon* weapon = pLocal->GetActiveBaseCombatWeapon();
		if (weapon)
		{
			if (weapon->isAWP() || weapon->isScout())
				return ClientVars.LegitBot.Weapons.Sniper.Triggerbot.hitbox;

			if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper())
				return ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.hitbox;

			if (weapon->isPistol())
				return ClientVars.LegitBot.Weapons.Pistol.Triggerbot.hitbox;

			if (weapon->isRifle() || weapon->isMachineW())
				return ClientVars.LegitBot.Weapons.Rifle.Triggerbot.hitbox;

			if (weapon->isSmgW())
				return ClientVars.LegitBot.Weapons.SMG.Triggerbot.hitbox;

			if (weapon->isShotgun())
				return ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.hitbox;
		}

	}


	float getTriggerbotDelay() {
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		CBaseCombatWeapon* weapon = pLocal->GetActiveBaseCombatWeapon();
		if (weapon)
		{
			if (weapon->isAWP() || weapon->isScout())
				return ClientVars.LegitBot.Weapons.Sniper.Triggerbot.delay;

			if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper())
				return ClientVars.LegitBot.Weapons.AutoSniper.Triggerbot.delay;

			if (weapon->isPistol())
				return ClientVars.LegitBot.Weapons.Pistol.Triggerbot.delay;

			if (weapon->isRifle() || weapon->isMachineW())
				return ClientVars.LegitBot.Weapons.Rifle.Triggerbot.delay;

			if (weapon->isSmgW())
				return ClientVars.LegitBot.Weapons.SMG.Triggerbot.delay;

			if (weapon->isShotgun())
				return ClientVars.LegitBot.Weapons.Shotgun.Triggerbot.delay;
		}

	}


	float getWeaponSmoothing() {
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		CBaseCombatWeapon* weapon = pLocal->GetActiveBaseCombatWeapon();
		if (weapon)
		{
			if (weapon->isAWP() || weapon->isScout())
				return ClientVars.LegitBot.Weapons.Sniper.smoothing;

			if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper())
				return ClientVars.LegitBot.Weapons.AutoSniper.smoothing;

			if (weapon->isPistol())
				return ClientVars.LegitBot.Weapons.Pistol.smoothing;

			if (weapon->isRifle() || weapon->isMachineW())
				return ClientVars.LegitBot.Weapons.Rifle.smoothing;

			if (weapon->isSmgW())
				return ClientVars.LegitBot.Weapons.SMG.smoothing;

			if (weapon->isShotgun())
				return ClientVars.LegitBot.Weapons.Shotgun.smoothing;
		}

	}

	inline void normalize_angles(QAngle& angles)
	{
		for (auto i = 0; i < 3; i++) {
			while (angles[i] < -180.0f) angles[i] += 360.0f;
			while (angles[i] >  180.0f) angles[i] -= 360.0f;
		}
	}

	inline void clamp_angles(QAngle& angles)
	{
		if (angles.x > 89.0f) angles.x = 89.0f;
		else if (angles.x < -89.0f) angles.x = -89.0f;

		if (angles.y > 180.0f) angles.y = 180.0f;
		else if (angles.y < -180.0f) angles.y = -180.0f;

		angles.z = 0;
	}
	inline bool sanitize_angles(QAngle &angles)
	{
		QAngle temp = angles;
		normalize_angles(temp);
		clamp_angles(temp);

		if (!isfinite(temp.x) ||
			!isfinite(temp.y) ||
			!isfinite(temp.z))
			return false;

		angles = temp;

		return true;
	}



	Vector Target;
	CBaseEntity* pTarget;
	Vector Angles;

	QAngle delta_angle = QAngle(0.0f, 0.0f, 0.0f);
	QAngle final_angle = QAngle(0.0f, 0.0f, 0.0f);


	void Aim(CInput::CUserCmd* cmd)
	{
		if (!ClientVars.LegitBot.enable) return;

		if (!canAimbot()) return;

		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		if (!pLocal) return;

		Interfaces.pEngine->GetViewAngles(Angles);
		CBaseCombatWeapon* pWeapon = Hacks.LocalPlayer->GetActiveBaseCombatWeapon();

		for (int i = 1; i < Interfaces.pEngine->GetMaxClients(); i++)
		{

			if (i == Interfaces.pEngine->GetLocalPlayer()) continue;

			CBaseEntity* target = Interfaces.pEntList->GetClientEntity(i);

			if (!target->IsPlayer()) continue;
			if (target->GetTeam() == Hacks.LocalPlayer->GetTeam()) continue;
			if (target->IsDormant()) continue;
			if (!target->isAlive()) continue;
			if (target->HasGunGameImmunity()) continue;

			float simtime = 0;
			Vector minus_origin = Vector(0, 0, 0);
			Vector aim_position = RunAimScan(target, simtime, minus_origin);

			if (aim_position == Vector(0, 0, 0))
				continue;

			float FOV = Misc::GetFOV(Angles, Hacks.LocalPlayer->GetEyePosition(), aim_position, true);

			if (FOV > getWeaponFOV()) continue;

			QAngle aim = g_Math.CalcAngle(Hacks.LocalPlayer->GetEyePosition(), aim_position);

			delta_angle = Angles - aim;
			sanitize_angles(delta_angle);

			final_angle = Angles - delta_angle / getWeaponSmoothing();
			sanitize_angles(final_angle);

			if (!sanitize_angles(final_angle))
				continue;

			cmd->viewangles = final_angle;
			Interfaces.pEngine->SetViewAngles(cmd->viewangles);
			break;
		}
	}
	void SinCos(float a, float* s, float*c)
	{
		*s = sin(a);
		*c = cos(a);
	}


	void AngleVectors(const Vector angles, Vector *forward, Vector *right, Vector *up)
	{
		float sr, sp, sy, cr, cp, cy;

		SinCos(DEG2RAD(angles[1]), &sy, &cy);
		SinCos(DEG2RAD(angles[0]), &sp, &cp);
		SinCos(DEG2RAD(angles[2]), &sr, &cr);

		if (forward)
		{
			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}

		if (right)
		{
			right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
			right->y = (-1 * sr*sp*sy + -1 * cr*cy);
			right->z = -1 * sr*cp;
		}

		if (up)
		{
			up->x = (cr*sp*cy + -sr * -sy);
			up->y = (cr*sp*sy + -sr * cy);
			up->z = cr * cp;
		}
	}



	void RandomSeed(UINT seed)
	{
		typedef void(*RandomSeed_t)(UINT);
		static RandomSeed_t m_RandomSeed = (RandomSeed_t)GetProcAddress(GetModuleHandle("vstdlib.dll"), "RandomSeed");
		m_RandomSeed(seed);
		return;
	}

	inline float FastSqrt(float x)
	{
		auto root = _mm_sqrt_ss(_mm_load_ss(&x));
		return *(reinterpret_cast<float *>(&root));
	}



	bool hit_chance(CInput::CUserCmd* userCMD, CBaseEntity* pLocal, CBaseEntity* target, int hitchance)
	{
		if (pLocal) {
			CBaseCombatWeapon* weapon = pLocal->GetActiveBaseCombatWeapon();
			if (weapon) {
				Vector forward, right, up;

				constexpr auto max_traces = 256;

				AngleVectors(userCMD->viewangles, &forward, &right, &up);

				int total_hits = 0;
				int needed_hits = static_cast<int>(max_traces * (hitchance / 100.f));

				weapon->UpdateAccuracyPenalty();

				auto eyes = pLocal->GetEyePosition();
				auto flRange = weapon->GetCSWpnData()->GetRange();

				for (int i = 0; i < max_traces; i++) {
					RandomSeed(i + 1);

					float fRand1 = g_Math.RandomFloat(0.f, 1.f);
					float fRandPi1 = g_Math.RandomFloat(0.f, 6.283185307f);
					float fRand2 = g_Math.RandomFloat(0.f, 1.f);
					float fRandPi2 = g_Math.RandomFloat(0.f, 6.283185307f);

					float fRandInaccuracy = fRand1 * weapon->GetInaccuracy();
					float fRandSpread = fRand2 * weapon->GetSpread();

					float fSpreadX = cos(fRandPi1) * fRandInaccuracy + cos(fRandPi2) * fRandSpread;
					float fSpreadY = sin(fRandPi1) * fRandInaccuracy + sin(fRandPi2) * fRandSpread;
					Vector viewSpreadForward = Vector(forward + fSpreadX * right + fSpreadY * up).Normalized();
					Vector viewAnglesSpread;
					g_Math.vectorAnglesVec(viewSpreadForward, viewAnglesSpread);
					g_Math.Normalize2(viewAnglesSpread);

					Vector viewForward;
					g_Math.angleVectors(viewAnglesSpread, viewForward);
					viewForward.NormalizeInPlace();

					viewForward = eyes + (viewForward * flRange);

					trace_t tr;
					Ray_t ray;
					ray.Init(eyes, viewForward);



					if (tr.m_pEnt == target)
						total_hits++;

					if (total_hits >= needed_hits)
						return true;

					if ((max_traces - i + total_hits) < needed_hits)
						return false;
				}
			}
		}
		return false;
	}
	void Triggerbot(CInput::CUserCmd* cmd) {
		static int custom_delay;
		CBaseCombatWeapon* pWeapon = Hacks.LocalWeapon;
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		if (!shouldTriggerbot()) return;
		if (!pLocal) return;
		if (!pWeapon) return;
		if (!pLocal->isAlive()) return;
		if (pWeapon->IsMiscWeapon()) return;
		if (pWeapon->ammo() == 0) return;

		QAngle ViewAngles = cmd->viewangles + pLocal->localPlayerExclusive()->GetAimPunchAngle();


		Vector CrosshairForward;
		g_Math.angleVectors(ViewAngles, CrosshairForward);
		CrosshairForward *= pWeapon->GetCSWpnData()->GetRange();


		Vector TraceSource = pLocal->GetEyePosition();
		Vector TraceDestination = TraceSource + CrosshairForward;

		Ray_t Ray;
		trace_t Trace;
		CTraceFilter Filter;

		Filter.pSkip = pLocal;

		Ray.Init(TraceSource, TraceDestination);
		Interfaces.pTrace->TraceRay_(Ray, MASK_SHOT, &Filter, &Trace);

		if (!Trace.m_pEnt)
			return;
		if (!Trace.m_pEnt->isAlive())
			return;
		if (Trace.m_pEnt->HasGunGameImmunity())
			return;


		if (pLocal->GetTeam() == Trace.m_pEnt->GetTeam())
			return;

		if (getHitchance() == 0 || hit_chance(cmd, Hacks.LocalPlayer, Trace.m_pEnt, getHitchance())) {

			bool didHit = false;
			if ((getTriggerbotHitbox() == 0)
				|| (getTriggerbotHitbox() == 1 && Trace.hitgroup == HITGROUP_HEAD)
				|| (getTriggerbotHitbox() == 2 && Trace.hitgroup == HITGROUP_CHEST)
				|| (getTriggerbotHitbox() == 3 && Trace.hitgroup == HITGROUP_STOMACH))
				didHit = true;

			if (getTriggerbotDelay() >= 1)
			{
				if (custom_delay >= getTriggerbotDelay() / 30)
				{
					if (didHit)
					{
						custom_delay = 0;
						cmd->buttons |= IN_ATTACK;
					}
				}
				else
				{
					custom_delay++;
				}
			}
			else {
				cmd->buttons |= IN_ATTACK;
			}
		}
	}
} Legitbot;

class AntiAimLegit
{
private:

public:
	void Run(CInput::CUserCmd* cmd)
	{
		CBaseCombatWeapon* pWeapon = Hacks.LocalWeapon;

		if (!ClientVars.LegitBot.AntiAim.enabled)
			return;
		if (Misc::Shooting())
			return;
		if (cmd->buttons & IN_USE)
			return;
		if (!ClientVars.LegitBot.AntiAim.OnLadders && Hacks.LocalPlayer->GetMoveType() == MOVETYPE_LADDER)
			return;
		if (!ClientVars.LegitBot.AntiAim.OnKnife && pWeapon->IsKnife())
			return;
		if (!ClientVars.LegitBot.AntiAim.OnGreandes && pWeapon->IsGrenade())
			return;

		AntiAims::SetLegitAntiAim(cmd);

	}
} AntiAimLegit;
