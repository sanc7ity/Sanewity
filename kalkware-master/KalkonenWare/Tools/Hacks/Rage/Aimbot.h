#pragma once
#include "../../../stdafx.h"
#include "../../Utils/Hitbox.h"
#include "../../Utils/Playerlist.h"
#include "../../Utils/HitboxLists.h"


#define TICK_INTERVAL			( Interfaces.pGlobalVars->interval_per_tick )
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t )		( TICK_INTERVAL *( t ) )

template<class T, class U>
inline T clamp(T in, U low, U high)
{
	if (in <= low)
		return low;
	else if (in >= high)
		return high;
	else
		return in;
}

class Ragebot
{
private:

	int target_index = -1;
	float best_distance = 8192.f;
	bool aimbotted_in_current_tick;
	bool fired_in_that_tick;
	float current_aim_simulationtime;
	int current_minusticks;
	Vector current_aim_position;
	Vector current_aim_player_origin;
	Vector Angles;

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
			if (weapon->isAWP() || weapon->isScout())
				return ClientVars.Ragebot.Weapons.Sniper.Hitbox;

			if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper())
				return ClientVars.Ragebot.Weapons.AutoSniper.Hitbox;

			if (weapon->isPistol())
				return ClientVars.Ragebot.Weapons.Pistol.Hitbox;

			if (weapon->isRifle() || weapon->isMachineW())
				return ClientVars.Ragebot.Weapons.Rifle.Hitbox;

			if (weapon->isSmgW())
				return ClientVars.Ragebot.Weapons.SMG.Hitbox;

			if (weapon->isShotgun())
				return ClientVars.Ragebot.Weapons.Shotgun.Hitbox;
		}
	}

	static int GetHitscan() {
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		CBaseCombatWeapon* weapon = pLocal->GetActiveBaseCombatWeapon();
		if (weapon)
		{
			if (weapon->isAWP() || weapon->isScout())
				return ClientVars.Ragebot.Weapons.Sniper.Hitscan.strength;

			if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper())
				return ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.strength;

			if (weapon->isPistol())
				return ClientVars.Ragebot.Weapons.Pistol.Hitscan.strength;

			if (weapon->isRifle() || weapon->isMachineW())
				return ClientVars.Ragebot.Weapons.Rifle.Hitscan.strength;

			if (weapon->isSmgW())
				return ClientVars.Ragebot.Weapons.SMG.Hitscan.strength;

			if (weapon->isShotgun())
				return ClientVars.Ragebot.Weapons.Shotgun.Hitscan.strength;
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



	std::vector<int> GetHitboxesToScanBaim(CBaseEntity* pTarget)
	{
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
		CBaseCombatWeapon * weapon = pLocal->GetActiveBaseCombatWeapon();
		std::vector<int> HitBoxesToScan;
		int HitScanMode = GetHitscan();

		if (weapon)
		{

			switch (HitScanMode) {
			case 0:
				break;
			case 1: //Regular
				if (weapon->isAWP() || weapon->isScout()) {
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}

				}

				if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper()) {
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}

				}

				if (weapon->isPistol()) {
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}

				}

				if (weapon->isRifle() || weapon->isMachineW()) {
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}

				}

				if (weapon->isSmgW()) {
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}

				}

				if (weapon->isShotgun()) {
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}

				}

				break;
			case 2: //Medium
				if (weapon->isAWP() || weapon->isScout()) {
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}

				}

				if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper()) {
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}

				}

				if (weapon->isPistol()) {
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}

				}

				if (weapon->isRifle() || weapon->isMachineW()) {
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}

					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}

				}

				if (weapon->isSmgW()) {
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}

					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}
				}

				if (weapon->isShotgun()) {
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}

					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}
				}
			case 3: //Extreme
				if (weapon->isAWP() || weapon->isScout()) {
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LowerChest);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}

					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightHand);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftHand);
					}

				}
				if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper()) {
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LowerChest);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}

					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightHand);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftHand);
					}

				}

				if (weapon->isPistol()) {
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LowerChest);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}

					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightHand);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftHand);
					}
				}

				if (weapon->isRifle() || weapon->isMachineW()) {
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LowerChest);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}

					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightHand);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftHand);
					}
				}

				if (weapon->isSmgW()) {

					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LowerChest);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}

					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightHand);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftHand);
					}
				}

				if (weapon->isShotgun()) {
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LowerChest);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}

					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightHand);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftHand);
					}

				}
			}
			return HitBoxesToScan;
		}
	}




	std::vector<int> GetHitboxesToScan(CBaseEntity* pTarget)
	{
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
		CBaseCombatWeapon * weapon = pLocal->GetActiveBaseCombatWeapon();
		std::vector<int> HitBoxesToScan;
		int HitScanMode = GetHitscan();

		if (weapon)
		{

			switch (HitScanMode) {
			case 0:
				break;
			case 1: //Regular
				if (weapon->isAWP() || weapon->isScout()) {
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
					}
				}

				if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper()) {
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
					}
				}

				if (weapon->isPistol()) {
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
					}
				}

				if (weapon->isRifle() || weapon->isMachineW()) {
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
					}
				}

				if (weapon->isSmgW()) {
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
					}
				}

				if (weapon->isShotgun()) {
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
					}
				}

				break;
			case 2: //Medium
				if (weapon->isAWP() || weapon->isScout()) {
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}
				}

				if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper()) {
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}
				}

				if (weapon->isPistol()) {
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}
				}

				if (weapon->isRifle() || weapon->isMachineW()) {
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}
				}

				if (weapon->isSmgW()) {
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}
				}

				if (weapon->isShotgun()) {
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}
				}
			case 3: //Extreme
				if (weapon->isAWP() || weapon->isScout()) {
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightHand);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftHand);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LowerChest);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Sniper.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}
				}
				if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper()) {
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightHand);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftHand);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LowerChest);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.AutoSniper.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}
				}

				if (weapon->isPistol()) {
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightHand);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftHand);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LowerChest);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Pistol.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}
				}

				if (weapon->isRifle() || weapon->isMachineW()) {
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightHand);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftHand);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LowerChest);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Rifle.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}
				}

				if (weapon->isSmgW()) {
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightHand);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftHand);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LowerChest);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.SMG.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}
				}

				if (weapon->isShotgun()) {
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.head) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.neck) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
						HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.arms) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightHand);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftHand);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.chest) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LowerChest);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.stomach) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.pelvis) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.legs) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
					}
					if (ClientVars.Ragebot.Weapons.Shotgun.Hitscan.feet) {
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
						HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
						HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
					}
				}
			}
			return HitBoxesToScan;
		}
	}


	static int GetMinDmg() {
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		CBaseCombatWeapon* weapon = pLocal->GetActiveBaseCombatWeapon();
		if (weapon)
		{
			if (weapon->isAWP() || weapon->isScout())
				return ClientVars.Ragebot.Weapons.Sniper.MinDmg;

			if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper())
				return ClientVars.Ragebot.Weapons.AutoSniper.MinDmg;

			if (weapon->isPistol())
				return ClientVars.Ragebot.Weapons.Pistol.MinDmg;

			if (weapon->isRifle() || weapon->isMachineW())
				return ClientVars.Ragebot.Weapons.Rifle.MinDmg;

			if (weapon->isSmgW())
				return ClientVars.Ragebot.Weapons.SMG.MinDmg;

			if (weapon->isShotgun())
				return ClientVars.Ragebot.Weapons.Shotgun.MinDmg;
		}
	}


	static bool canBaim() {
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		CBaseCombatWeapon* weapon = pLocal->GetActiveBaseCombatWeapon();
		if (weapon)
		{
			if (weapon->isAWP() || weapon->isScout())
				return ClientVars.Ragebot.Weapons.Sniper.baimiflethal;

			if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper())
				return ClientVars.Ragebot.Weapons.AutoSniper.baimiflethal;

			if (weapon->isPistol())
				return ClientVars.Ragebot.Weapons.Pistol.baimiflethal;

			if (weapon->isRifle() || weapon->isMachineW())
				return ClientVars.Ragebot.Weapons.Rifle.baimiflethal;

			if (weapon->isSmgW())
				return ClientVars.Ragebot.Weapons.SMG.baimiflethal;

			if (weapon->isShotgun())
				return ClientVars.Ragebot.Weapons.Shotgun.baimiflethal;
		}
	}





	static int GetHitchance() {
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		CBaseCombatWeapon* weapon = pLocal->GetActiveBaseCombatWeapon();
		if (weapon)
		{
			if (weapon->isAWP() || weapon->isScout())
				return ClientVars.Ragebot.Weapons.Sniper.HitChance;

			if (!weapon->isAWP() && !weapon->isScout() && weapon->isSniper())
				return ClientVars.Ragebot.Weapons.AutoSniper.HitChance;

			if (weapon->isPistol())
				return ClientVars.Ragebot.Weapons.Pistol.HitChance;

			if (weapon->isRifle() || weapon->isMachineW())
				return ClientVars.Ragebot.Weapons.Rifle.HitChance;

			if (weapon->isSmgW())
				return ClientVars.Ragebot.Weapons.SMG.HitChance;

			if (weapon->isShotgun())
				return ClientVars.Ragebot.Weapons.Shotgun.HitChance;
		}
	}

	Vector RunAimScan(CBaseEntity* pTarget, float &simtime, Vector& origin)
	{
		Vector vEyePos = Hacks.LocalPlayer->GetEyePosition();
		auto wpn_data = Hacks.LocalWeapon->GetCSWpnData();
		static float minimum_damage = 1.f;

		minimum_damage = GetMinDmg();

		bool found = false;

		matrix3x4 BoneMatrix[128];

		/*if (Clientvariables->Ragebot.PositionAdjustment)
		{
			std::vector<tick_record> lby_records, trash_records;




			

			float latest_time = 0.0f;
			tick_record latest_record;

			//do it that way to use the latest nonfakelagging record
			for (int j = g_BacktrackHelper->PlayerRecord[pTarget->Index()].records.size() - 1; j >= 0; j--) //works pretty good for nospread
			{
				tick_record record = g_BacktrackHelper->PlayerRecord[pTarget->Index()].records.at(j);

				float lerptime = g_BacktrackHelper->GetLerpTime();
				float desired_time = record.m_flSimulationTime + lerptime;
				float estimated_time = g_BacktrackHelper->GetEstimateServerTime();
				float SV_MAXUNLAG = 1.0f;
				float latency = g_BacktrackHelper->GetNetworkLatency();
				float m_flLerpTime = g_BacktrackHelper->GetLerpTime();
				float correct = clamp<float>(latency + m_flLerpTime, 0.0f, SV_MAXUNLAG);
				float deltaTime = correct - (estimated_time + lerptime - desired_time);

				if (fabs(deltaTime) > 0.2f)
					continue;

				if (record.m_flSimulationTime == g_BacktrackHelper->PlayerRecord[pTarget->Index()].records.back().m_flSimulationTime) {
					latest_time = g_BacktrackHelper->PlayerRecord[pTarget->Index()].records.at(j).m_flSimulationTime;
					latest_record = g_BacktrackHelper->PlayerRecord[pTarget->Index()].records.at(j);
				}

				if (record.needs_extrapolation)
					continue;

				if (record.bLowerBodyYawUpdated)
					lby_records.emplace_back(record);
				else if (j != g_BacktrackHelper->PlayerRecord[pTarget->Index()].records.size() - 1)
					trash_records.emplace_back(record);
			}

			//std::reverse(lby_records.begin(), lby_records.end());




		


			//check if we need to extrapolate, and just fucking do it, as nothing gets extrapoalted otherwise

			bool was_latest_checked_in_lby = false;

			for (int i = 0; i < lby_records.size(); i++) {
				tick_record record = lby_records.at(i);//total_valid_records.at(j);

				if (record.needs_extrapolation)
					continue;

				simtime = record.m_flSimulationTime;
				origin = record.m_vecOrigin;

				bool is_latest_record = record.m_flSimulationTime == latest_record.m_flSimulationTime;

				if (is_latest_record)
					was_latest_checked_in_lby = true;

				for (auto HitBox : MainHitbox(pTarget, record.boneMatrix)) {
					int hitgroup = -1;

					//fix that only latest record gets multipointed OR use the center of the hitbox to do this when using backtrack records
					if (is_latest_record) {

						if (g_pEngineTrace->IsVisible(G::LocalPlayer, vEyePos, HitBox, pTarget, hitgroup)) {
							float modified_damage = wpn_data->iDamage * (float)pow(wpn_data->flRangeModifier, wpn_data->flRange * 0.002);

							ScaleDamage(hitgroup, pTarget, wpn_data->flArmorRatio, modified_damage);

							if (HitBox != Vector(0, 0, 0) && modified_damage >= minimum_damage)
								return HitBox;
						}
					}

					if (is_latest_record) //neded to comment it, as i can't backtrack autowall atm
					{
						static float damage_given = 0.f;

						if (Clientvariables->Ragebot.Autowall && g_Autowall->CanHit(pTarget, HitBox, &damage_given)) {
							if (damage_given >= minimum_damage) {
								if (HitBox != Vector(0, 0, 0))
									return HitBox;
							}
						}
					}
				}
			}

			//only do autowall & hitscan for the latest lagrecord, but do that before we use other records that ain't good
			if (!was_latest_checked_in_lby && !latest_record.needs_extrapolation) {

				was_latest_checked_in_lby = true;

				simtime = latest_record.m_flSimulationTime;
				origin = latest_record.m_vecOrigin;

				for (auto HitBox : MainHitbox(pTarget, latest_record.boneMatrix)) {
					int hitgroup = -1;

					//fix that only latest record gets multipointed OR use the center of the hitbox to do this when using backtrack records

					if (g_pEngineTrace->IsVisible(G::LocalPlayer, vEyePos, HitBox, pTarget, hitgroup)) {
						float modified_damage = wpn_data->iDamage * (float)pow(wpn_data->flRangeModifier, wpn_data->flRange * 0.002);

						ScaleDamage(hitgroup, pTarget, wpn_data->flArmorRatio, modified_damage);

						if (HitBox != Vector(0, 0, 0) && modified_damage >= minimum_damage)
							return HitBox;
					}

					static float damage_given = 0.f;

					if (Clientvariables->Ragebot.Autowall && g_Autowall->CanHit(pTarget, HitBox, &damage_given)) {
						if (damage_given >= minimum_damage) {
							if (HitBox != Vector(0, 0, 0))
								return HitBox;
						}
					}
				}
			}

			//hitscan and autowall only for latest record before trashrecords
			if (!latest_record.needs_extrapolation) {
				Vector vPoint;
				simtime = latest_record.m_flSimulationTime;
				origin = latest_record.m_vecOrigin;
				for (auto HitboxID : GetHitboxesToScan(pTarget)) {
					std::vector<Vector> Points = GameUtils::GetMultiplePointsForHitbox(pTarget, HitboxID, latest_record.boneMatrix);
					for (int k = 0; k < Points.size(); k++) {

						vPoint = Points.at(k);
						float damage = 0.f;

						int hitgroup = -1;
						if (g_pEngineTrace->IsVisible(G::LocalPlayer, vEyePos, vPoint, pTarget, hitgroup)) {
							float modified_damage = wpn_data->iDamage * (float)pow(wpn_data->flRangeModifier, wpn_data->flRange * 0.002);

							ScaleDamage(hitgroup, pTarget, wpn_data->flArmorRatio, modified_damage);



							if (vPoint != Vector(0, 0, 0) && modified_damage >= minimum_damage)
								return vPoint;
						}

						if (k == 0) //fixes that only the center gets autowall
						{
							static float damage_given = 0.f;

							if (Clientvariables->Ragebot.Autowall && Clientvariables->Ragebot.AutowallHitscan && g_Autowall->CanHit(pTarget, vPoint, &damage_given)) {
								if (damage_given >= minimum_damage) {
									if (vPoint != Vector(0, 0, 0))
										return vPoint;
								}
							}
						}
					}
				}
			}


			//check for other records
			for (int j = 0; j < trash_records.size(); j++) {
				tick_record record = trash_records.at(j);//total_valid_records.at(j);

				if (record.needs_extrapolation)
					continue;

				//*(Vector*)((DWORD)pTarget + 0x110) = record.m_vecVelocity;


				simtime = record.m_flSimulationTime;
				origin = record.m_vecOrigin;

				int count = 0; //fix that only center gets autowalled

							   //don't aim at lby records, as we tested for them before

				for (auto HitBox : MainHitbox(pTarget, record.boneMatrix)) {
					int hitgroup = -1;

					//fix that only latest record gets multipointed OR use the center of the hitbox to do this when using backtrack records
					if (g_pEngineTrace->IsVisible(G::LocalPlayer, vEyePos, HitBox, pTarget, hitgroup)) {
						float modified_damage = wpn_data->iDamage * (float)pow(wpn_data->flRangeModifier, wpn_data->flRange * 0.002);

						ScaleDamage(hitgroup, pTarget, wpn_data->flArmorRatio, modified_damage);

						if (HitBox != Vector(0, 0, 0) && modified_damage >= minimum_damage)
							return HitBox;
					}
				}
			}

			if (latest_record.needs_extrapolation) {
				Vector position = latest_record.m_vecOrigin;
				float old_simtime = latest_record.m_flSimulationTime;;
				Vector extr_position = position;
				simtime = latest_record.m_flSimulationTime;
				g_BacktrackHelper->ExtrapolatePosition(pTarget, extr_position, simtime, latest_record.m_vecVelocity);

				Msg("Extrapolating... OldVec(%f, %f, %f) - NewVec(%f, %f, %f)\n", position.x, position.y, position.z, extr_position.x, extr_position.y, extr_position.z);

				for (auto HitBox : MainHitbox(pTarget, latest_record.boneMatrix)) {
					int hitgroup = -1;

					HitBox -= position;
					HitBox += extr_position;

					if (g_pEngineTrace->IsVisible(G::LocalPlayer, vEyePos, HitBox, pTarget, hitgroup)) {
						if (HitBox != Vector(0, 0, 0))
							return HitBox;
					}

				}
			}
		}
		else {*/

		//int* array = reinterpret_cast<int*>(offys.dwOcclusionArray);
		//*(int*)((uintptr_t)pTarget + offys.nWriteableBones) = 0;
		//*(int*)((uintptr_t)pTarget + offys.bDidCheckForOcclusion) = array[1];


		pTarget->SetupBones(BoneMatrix, 128, 0x100, Interfaces.pGlobalVars->curtime);
		simtime = pTarget->GetSimulationTime();

		origin = pTarget->GetVecOrigin();

		if (canBaim()){
			struct BAIM {
				static Vector search(std::vector<Vector> Points, Vector eyePos, CBaseEntity* pTarget) {
					Vector vPoint;
					for (int k = 0; k < Points.size(); k++) {
						vPoint = Points.at(k);
						int damage_given = Autowall::GetDamage(vPoint);

						if (vPoint == Vector(0, 0, 0))
							continue;
						
						if (damage_given <= 0)
							continue;

						if (damage_given < pTarget->GetHealth())
							continue;

						return vPoint;
					}
					return Vector(0, 0, 0);
				}
			}BAIM;
			Vector found;
			if ((found = BAIM::search(Misc::GetMultiplePointsForHitbox(pTarget, 3, BoneMatrix), vEyePos, pTarget)) != Vector(0, 0, 0))
				return found;	
			else if ((found = BAIM::search(Misc::GetMultiplePointsForHitbox(pTarget, 6, BoneMatrix), vEyePos, pTarget)) != Vector(0, 0, 0))
				return found;
		}
		for (auto HitBox : MainHitbox(pTarget, BoneMatrix)) {

			if (IsVisible(vEyePos, HitBox, Hacks.LocalPlayer, pTarget, false)) {
				if (HitBox != Vector(0, 0, 0))
					return HitBox;
			}

			int damage_given = Autowall::GetDamage(HitBox);
			if (ClientVars.Ragebot.Autowall && damage_given > 0) {
				if (damage_given >= minimum_damage) {
					if (HitBox != Vector(0, 0, 0))
						return HitBox;
				}
			}
		}
			
		for (auto HitboxID : GetHitboxesToScan(pTarget)) {
			Vector vPoint;
			std::vector<Vector> Points = Misc::GetMultiplePointsForHitbox(pTarget, HitboxID, BoneMatrix);
			for (int k = 0; k < Points.size(); k++) {

				vPoint = Points.at(k);

				int hitgroup = -1;
				if (IsVisible( vEyePos, vPoint, Hacks.LocalPlayer, pTarget, false)) {
					if (vPoint != Vector(0, 0, 0))
						return vPoint;
				}
				int damage_given = Autowall::GetDamage(vPoint);
				if (ClientVars.Ragebot.Autowall && damage_given > 0) {
					if (damage_given >= minimum_damage) {
						if (vPoint != Vector(0, 0, 0))
							return vPoint;
					}
				}
			}
		}

			//int* array = reinterpret_cast<int*>(offys.dwOcclusionArray);
			//*(int*)((uintptr_t)pTarget + offys.nWriteableBones) = 0;
			//*(int*)((uintptr_t)pTarget + offys.bDidCheckForOcclusion) = array[1];


			pTarget->SetupBones(BoneMatrix, 128, 0x100, Interfaces.pGlobalVars->curtime);
			simtime = pTarget->GetSimulationTime();

			origin = pTarget->GetVecOrigin();

			for (auto HitBox : MainHitbox(pTarget, BoneMatrix)) {
				if (IsVisible(vEyePos, HitBox, Hacks.LocalPlayer, pTarget, false)) {
					if (HitBox != Vector(0, 0, 0))
						return HitBox;
				}
				int damage_given = Autowall::GetDamage(HitBox);
				if (ClientVars.Ragebot.Autowall && damage_given > 0) {
					if (damage_given >= minimum_damage) {
						if (HitBox != Vector(0, 0, 0))
							return HitBox;
					}
				}
			}
			for (auto HitboxID : GetHitboxesToScan(pTarget)) {

				Vector vPoint;

				std::vector<Vector> Points = Misc::GetMultiplePointsForHitbox(pTarget, HitboxID, BoneMatrix);
				for (int k = 0; k < Points.size(); k++) {

					vPoint = Points.at(k);
					float damage = 0.f;

					int hitgroup = -1;
					if (IsVisible( vEyePos, vPoint, Hacks.LocalPlayer, pTarget, false)) {
						if (vPoint != Vector(0, 0, 0))
							return vPoint;
					}

					int damage_given = Autowall::GetDamage(vPoint);
					if (ClientVars.Ragebot.Autowall && damage_given > 0) {
						if (damage_given >= minimum_damage) {
							if (vPoint != Vector(0, 0, 0))
								return vPoint;
						}
					}
				}
			}

	
		return Vector(0, 0, 0);
	}


public:

	CBaseEntity* pTarget;

	void DropTarget()
	{
		target_index = -1;
		best_distance = 99999.f;
		aimbotted_in_current_tick = false;
		fired_in_that_tick = false;
		current_aim_position = Vector();
		pTarget = nullptr;
		Interfaces.pGlobalVars->rageTarget = nullptr;
	}

	inline Vector angle_vector(Vector meme)
	{
		auto sy = sin(meme.y / 180.f * static_cast<float>(PI));
		auto cy = cos(meme.y / 180.f * static_cast<float>(PI));

		auto sp = sin(meme.x / 180.f * static_cast<float>(PI));
		auto cp = cos(meme.x / 180.f* static_cast<float>(PI));

		return Vector(cp*cy, cp*sy, -sp);
	}

	float GetLerpTime()
	{
		int ud_rate = Interfaces.g_ICVars->FindVar("cl_updaterate")->GetFloat();
		ConVar *min_ud_rate = Interfaces.g_ICVars->FindVar("sv_minupdaterate");
		ConVar *max_ud_rate = Interfaces.g_ICVars->FindVar("sv_maxupdaterate");

		if (min_ud_rate && max_ud_rate)
			ud_rate = max_ud_rate->GetFloat();

		float ratio = Interfaces.g_ICVars->FindVar("cl_interp_ratio")->GetFloat();

		if (ratio == 0)
			ratio = 1.0f;

		float lerp = Interfaces.g_ICVars->FindVar("cl_interp")->GetFloat();
		ConVar *c_min_ratio = Interfaces.g_ICVars->FindVar("sv_client_min_interp_ratio");
		ConVar *c_max_ratio = Interfaces.g_ICVars->FindVar("sv_client_max_interp_ratio");

		if (c_min_ratio && c_max_ratio && c_min_ratio->GetFloat() != 1)
			ratio = clamp(ratio, c_min_ratio->GetFloat(), c_max_ratio->GetFloat());

		return max(lerp, (ratio / ud_rate));
	}
	float getHitchance() {
		CBaseCombatWeapon* weapon = Hacks.LocalPlayer->GetActiveBaseCombatWeapon();
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



	void NormaliseViewAngle(Vector &angle)
	{
		while (angle.y <= -180) angle.y += 360;
		while (angle.y > 180) angle.y -= 360;
		while (angle.x <= -180) angle.x += 360;
		while (angle.x > 180) angle.x -= 360;


		if (angle.x > 89.0f)
			angle.x = 89.0f;
		else if (angle.x < -89.0f)
			angle.x = -89.0f;

		if (angle.y > 179.99999f)
			angle.y = 179.99999f;
		else if (angle.y < -179.99999f)
			angle.y = -179.99999f;

		angle.z = 0;
	}


	#define XM_2PI              6.283185307f

	void AngleVectors(const Vector &angles, Vector *forward)
	{
		Assert(s_bMathlibInitialized);
		Assert(forward);

		float	sp, sy, cp, cy;

		sy = sin(DEG2RAD(angles[1]));
		cy = cos(DEG2RAD(angles[1]));

		sp = sin(DEG2RAD(angles[0]));
		cp = cos(DEG2RAD(angles[0]));

		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	void VectorAngles(Vector forward, Vector &angles)
	{
		float tmp, yaw, pitch;

		yaw = (atan2(forward[1], forward[0]) * 180 / PI);
		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / PI);


		while (yaw <= -180) yaw += 360;
		while (yaw > 180) yaw -= 360;
		while (pitch <= -180) pitch += 360;
		while (pitch > 180) pitch -= 360;


		if (pitch > 89.0f)
			pitch = 89.0f;
		else if (pitch < -89.0f)
			pitch = -89.0f;

		if (yaw > 179.99999f)
			yaw = 179.99999f;
		else if (yaw < -179.99999f)
			yaw = -179.99999f;

		angles[0] = pitch;
		angles[1] = yaw;
		angles[2] = 0;
	}

	bool hit_chance(CInput::CUserCmd* userCMD, CBaseEntity* pLocal, CBaseEntity* target, int hitchance)
	{
		Vector forward, right, up;

		constexpr auto max_traces = 256;

		AngleVectors(userCMD->viewangles, &forward, &right, &up);

		int total_hits = 0;
		int needed_hits = static_cast<int>(max_traces * (hitchance / 100.f));

		pLocal->GetActiveBaseCombatWeapon()->UpdateAccuracyPenalty();

		auto eyes = pLocal->GetEyePosition();
		auto flRange = pLocal->GetActiveBaseCombatWeapon()->GetCSWpnData()->GetRange();

		for (int i = 0; i < max_traces; i++) {
			RandomSeed(i + 1);

			float fRand1 = g_Math.RandomFloat(0.f, 1.f);
			float fRandPi1 = g_Math.RandomFloat(0.f, XM_2PI);
			float fRand2 = g_Math.RandomFloat(0.f, 1.f);
			float fRandPi2 = g_Math.RandomFloat(0.f, XM_2PI);

			float fRandInaccuracy = fRand1 * pLocal->GetActiveBaseCombatWeapon()->GetInaccuracy();
			float fRandSpread = fRand2 * pLocal->GetActiveBaseCombatWeapon()->GetSpread();

			float fSpreadX = cos(fRandPi1) * fRandInaccuracy + cos(fRandPi2) * fRandSpread;
			float fSpreadY = sin(fRandPi1) * fRandInaccuracy + sin(fRandPi2) * fRandSpread;

			Vector viewSpreadForward = Vector(forward + fSpreadX * right + fSpreadY * up).Normalized();

			Vector viewAnglesSpread;
			VectorAngles(viewSpreadForward, viewAnglesSpread);
			NormaliseViewAngle(viewAnglesSpread);

			Vector viewForward;
			AngleVectors(viewAnglesSpread, &viewForward);
			viewForward.NormalizeInPlace();

			viewForward = eyes + (viewForward * flRange);

			trace_t tr;
			Ray_t ray;
			ray.Init(eyes, viewForward);

			Interfaces.pTrace->ClipRayToEntity_(ray, MASK_SHOT | CONTENTS_GRATE, target, &tr);


			if (tr.m_pEnt == target)
				total_hits++;

			if (total_hits >= needed_hits)
				return true;

			if ((max_traces - i + total_hits) < needed_hits)
				return false;
		}

		return false;

	}
	void Aim( CInput::CUserCmd* cmd )
	{

		if (!ClientVars.Ragebot.Enable) return;
		
		if (ClientVars.Misc.crimwalk > 0 && GetAsyncKeyState(ClientVars.Misc.crimwalk)) return;

		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		if (!pLocal) return;

		pTarget = nullptr;

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

			float FOV = Misc::GetFOV(Angles, Hacks.LocalPlayer->GetEyePosition(), target->GetEyePosition(), false);

			if (FOV > ClientVars.Ragebot.FOV) continue;

			pTarget = target;
			
			float simtime = 0;
			Vector minus_origin = Vector(0, 0, 0);
			Vector aim_position = RunAimScan(target, simtime, minus_origin);

			if (aim_position == Vector(0, 0, 0))
				continue;


			float selection_value = 0;
			switch (ClientVars.Ragebot.AimbotSelection) {
			case 0:
				selection_value = FOV;
				break;
			case 2:
				selection_value = g_Math.RandomFloat(0, 100);
				break;
			case 3:
				selection_value = target->GetVecVelocity().Length();
				break;
			case 4:
				selection_value = target->GetHealth();
				break;

			default:
				break;
			}

			if (best_distance >= selection_value && aim_position != Vector(0, 0, 0)) {
				best_distance = selection_value;


				Interfaces.pGlobalVars->rageTarget = pTarget;
				target_index = i;
				current_aim_position = aim_position;
				pTarget = target;
				current_aim_simulationtime = simtime;
				current_aim_player_origin = minus_origin;
			}
		}
		if (target_index != -1 && current_aim_position != Vector(0, 0, 0) && pTarget) {
			aimbotted_in_current_tick = true;
			QAngle aim = g_Math.CalcAngle(Hacks.LocalPlayer->GetEyePosition(), current_aim_position);
			
			if (ClientVars.Ragebot.pSilent && cmd->buttons & IN_ATTACK)
				cmd->viewangles = aim;

			if (!ClientVars.Ragebot.pSilent){
				cmd->viewangles = aim;
				Interfaces.pEngine->SetViewAngles(cmd->viewangles);
			}

			if (ClientVars.Ragebot.autofire)
			{

				if (ClientVars.Ragebot.autoscope && pWeapon->isSniper() && !Hacks.LocalPlayer->m_bIsScoped())
					cmd->buttons |= IN_ATTACK2;
				else
				{
					if (ClientVars.Ragebot.pSilent)
						cmd->viewangles = aim;

					if (pWeapon->IsTaser(pWeapon->SafeWeaponID()))
						return;

					if (GetHitchance() == 0 || hit_chance(cmd, Hacks.LocalPlayer, Interfaces.pEntList->GetClientEntity(target_index), GetHitchance()))
					{

						cmd->buttons |= IN_ATTACK;
						this->fired_in_that_tick = true;
					}

				}
			}




			if (ClientVars.Ragebot.BackTrack)
				cmd->tick_count = TIME_TO_TICKS(current_aim_simulationtime) + TIME_TO_TICKS(GetLerpTime());// for backtracking
		}
	}
} Ragebot;
