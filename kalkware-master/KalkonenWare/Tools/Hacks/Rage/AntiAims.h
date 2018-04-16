#pragma once
#include "stdafx.h"
#include "../Misc.h"

static int ticksxd;
static bool switchxd;

static int ticks;
static bool jitter;

static QAngle latestFake;
static QAngle latestReal;
static float spin;

//LBY
static float LastLBYUpdateTime = 0.f;
static float lbyTimer = 0.f;
//AA
	float lastJitterStandReal;
	float lastJitterMoveReal;
	float lastJitterAirReal;
	float lastJitterStandFake;
	float lastJitterMoveFake;
	float lastJitterAirFake;

class AntiAims
{
public:
	static QAngle getRealAngle() {
		if (ClientVars.AntiAim.enabled || ClientVars.LegitBot.AntiAim.enabled)
			return latestReal;
		else if(Hacks.LocalPlayer)
			return *Hacks.LocalPlayer->GetEyeAnglesPointer();
	}

	static QAngle getFakeAngle() {
		if (ClientVars.AntiAim.enabled || ClientVars.LegitBot.AntiAim.enabled)
			return latestFake;
		else if (Hacks.LocalPlayer)
			return *Hacks.LocalPlayer->GetEyeAnglesPointer();
	}

	static QAngle getLowerBodyAngle() {
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
		if (!pLocal)
			return QAngle();

		return QAngle(0, pLocal->pelvisangs(), 0);
	}

	static bool shouldBreakLby()
	{
		//xD?
		return false;
	}


	static float GetDamage(Vector ang, Vector Target)
	{
		FireBulletData Bullet_Data = FireBulletData(ang);
		Bullet_Data.filter.pSkip = Hacks.LocalPlayer;
		Vector Angle = Vector(0, 0, 0);
		Misc::CalcAngle(Bullet_Data.src, Target, Angle);
		g_Math.angleVectors(Angle, Bullet_Data.direction);

		if (Autowall::FireSimulatedBullet(Bullet_Data, Hacks.LocalPlayer, Hacks.LocalWeapon))
			return Bullet_Data.current_damage;
		return 0;
	}
	static float freestanding()
	{
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
		if (pLocal) {
			float best_damage = 1000;
			float best_fov = 180;
			CBaseEntity* client = nullptr;
			for (int i = 0; i < 64; ++i)
			{
				CBaseEntity* entity = Interfaces.pEntList->GetClientEntity(i);

				if (!entity || entity == pLocal || !entity->isAlive() || entity->IsDormant())
					continue;

				Vector Angles;
				Interfaces.pEngine->GetViewAngles(Angles);
				float FOV = Misc::GetFOV(Angles, pLocal->GetEyePosition(), entity->GetEyePosition(), false);
				if (FOV < best_fov && entity->GetActiveBaseCombatWeapon() && !entity->GetActiveBaseCombatWeapon()->IsMiscWeapon() && !entity->GetActiveBaseCombatWeapon()->IsKnife()) {
					best_fov = FOV;
					client = entity;
				}
			}

			bool updated = false;
			float yaw = 0.0f;
			if(client != nullptr && client){
				int strength = 16;
				float add = 360 / strength;

				Vector hitboxPos = Misc::GetHitboxPosition(client, 0);
				for (int i = 1; i <= strength; i++)
				{
					CBaseCombatWeapon* wep = client->GetActiveBaseCombatWeapon();
					
					if (!wep)
						continue;

					Vector modifiedVec = pLocal->GetEyePosition();
					
					modifiedVec.y = i * add;
						
					while (modifiedVec.y < -180.0f)
						modifiedVec.y += 360.0f;
					while (modifiedVec.y > 180.0f)
						modifiedVec.y -= 360.0f;
						
					float damage = GetDamage(modifiedVec, hitboxPos);
					//char temp[255];
					//sprintf_s(temp, "echo \"DMG: %f | Angle: %f\"", damage, modifiedVec.y);
					//Interfaces.pEngine->ClientCmd_Unrestricted(temp, 0);

					if (damage < best_damage)
					{
						best_damage = damage;
						yaw = modifiedVec.y;
						updated = true;
					}
				}
			}
			if (updated) {
				return yaw;
			}
			else
				return pLocal->GetEyeAnglesPointer()->y + 180;
		}
	}

	static void SetLegitAntiAim(CInput::CUserCmd* cmd)
	{
		if (ClientVars.LegitBot.AntiAim.Misc.rightAA != 0 && GetAsyncKeyState(ClientVars.LegitBot.AntiAim.Misc.rightAA))
			ClientVars.AntiAim.type = 0;
		else if (ClientVars.LegitBot.AntiAim.Misc.leftAA != 0 && GetAsyncKeyState(ClientVars.LegitBot.AntiAim.Misc.leftAA))
			ClientVars.AntiAim.type = 1;
		else if (ClientVars.LegitBot.AntiAim.Misc.downAA != 0 && GetAsyncKeyState(ClientVars.LegitBot.AntiAim.Misc.downAA))
			ClientVars.AntiAim.type = 2;
		//else if (ClientVars.LegitBot.AntiAim.Misc.upAA != 0 && GetAsyncKeyState(ClientVars.LegitBot.AntiAim.Misc.upAA))
		//	ClientVars.AntiAim.type = 3;

		if (ticksxd >= ClientVars.LegitBot.AntiAim.Misc.SwitchSpeed) {
			switchxd = !switchxd;
			ticksxd = 0;
		}
		else {
			ticksxd++;
		}

		if (ticks >= ClientVars.LegitBot.AntiAim.Misc.JitterSpeed) {
			jitter = !jitter;
			ticks = 0;
		}
		else {
			ticks++;
		}

	if(Hacks.SendPacket){
		cmd->viewangles.y += 0;
		latestFake = cmd->viewangles;
	} else {
		if (Hacks.LocalPlayer->GetVecVelocity().Length2D() < 0.1f && Hacks.LocalPlayer->GetFlags() & FL_ONGROUND) { //Real - Yaw - Stand
			bool custom = false;
			switch (ClientVars.LegitBot.AntiAim.Stand.Yaw) {
			case 1: { //Random
				cmd->viewangles.y = (rand() % 360) - 180;
				break;
			}

			case 2: { //Spinbot
				if (spin >= 180)
					spin = -180;

				spin += ClientVars.LegitBot.AntiAim.Misc.SpinbotSpeed;
				cmd->viewangles.y = spin;
				break;
			}

			case 3: { //Manual LBY Switch
				if (ClientVars.AntiAim.type == 0) {
					if (switchxd)
						cmd->viewangles.y += 60;
					else
						cmd->viewangles.y += 120;

					if (shouldBreakLby())
						cmd->viewangles.y += ClientVars.LegitBot.AntiAim.Misc.lbyDelta;
				}
				else if(ClientVars.AntiAim.type == 1){
					if (switchxd)
						cmd->viewangles.y -= 60;
					else
						cmd->viewangles.y -= 120;

					if (shouldBreakLby())
						cmd->viewangles.y -= ClientVars.LegitBot.AntiAim.Misc.lbyDelta;
				}else if (ClientVars.AntiAim.type == 2) {
					cmd->viewangles.y += 180;
				}
				break;
			}

			case 4: { //Jitter
				custom = true;
				if (jitter && ClientVars.LegitBot.AntiAim.Misc.JitterRange != 0) {
					float lastJitterxd = ClientVars.LegitBot.AntiAim.Stand.YawAdd + rand() % ClientVars.LegitBot.AntiAim.Misc.JitterRange;
					lastJitterStandReal = lastJitterxd;
					cmd->viewangles.y += lastJitterxd;
				}
				else {
					cmd->viewangles.y += lastJitterStandReal;
				}
				break;
			}

			case 5: { //Switch
				custom = true;
				if (switchxd)
					cmd->viewangles.y += ClientVars.LegitBot.AntiAim.Stand.YawAdd;
				else if (ClientVars.LegitBot.AntiAim.Misc.SwitchAdd != 0)
					cmd->viewangles.y += ClientVars.LegitBot.AntiAim.Stand.YawAdd + ClientVars.LegitBot.AntiAim.Misc.SwitchAdd;
				break;
			}

			case 6: { //Static
				custom = true;
				cmd->viewangles.y += ClientVars.LegitBot.AntiAim.Stand.YawAdd;
				break;
			}

			case 7: { //Lower Body
				cmd->viewangles.y += ClientVars.LegitBot.AntiAim.Stand.YawAdd;
				if (shouldBreakLby())
					cmd->viewangles.y += ClientVars.LegitBot.AntiAim.Misc.lbyDelta;
				break;
			}

			case 8: { //Freestanding
				cmd->viewangles.y = freestanding();
				break;
			}
			}
			if (!custom)
				cmd->viewangles.y += ClientVars.LegitBot.AntiAim.Stand.YawAdd;
		}
		else if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 0.1f && Hacks.LocalPlayer->GetFlags() & FL_ONGROUND) { //Real - Yaw - Move
			bool custom = false;
			switch (ClientVars.LegitBot.AntiAim.Move.Yaw) {
			case 1: { //Random
				cmd->viewangles.y = (rand() % 360) - 180;
				break;
			}

			case 2: { //Spinbot
				if (spin >= 180)
					spin = -180;

				spin += ClientVars.LegitBot.AntiAim.Misc.SpinbotSpeed;
				cmd->viewangles.y = spin;
				break;
			}

			case 3: { //Manual Switch
				if (ClientVars.AntiAim.type == 0) {
					if (switchxd)
						cmd->viewangles.y += 60;
					else
						cmd->viewangles.y += 120;
				}
				else if(ClientVars.AntiAim.type == 1){
					if (switchxd)
						cmd->viewangles.y -= 60;
					else
						cmd->viewangles.y -= 120;
				}
				else if (ClientVars.AntiAim.type == 2) {
					cmd->viewangles.y += 180;
				}
				break;
			}

			case 4: { //Jitter
				custom = true;
				if (jitter && ClientVars.LegitBot.AntiAim.Misc.JitterRange != 0) {
					float lastJitterxd = ClientVars.LegitBot.AntiAim.Move.YawAdd + rand() % ClientVars.LegitBot.AntiAim.Misc.JitterRange;
					lastJitterMoveReal = lastJitterxd;
					cmd->viewangles.y += lastJitterxd;
				}
				else {
					cmd->viewangles.y += lastJitterMoveReal;
				}
				break;
			}

			case 5: { //Switch
				custom = true;
				if (switchxd)
					cmd->viewangles.y += ClientVars.LegitBot.AntiAim.Move.YawAdd;
				else if (ClientVars.LegitBot.AntiAim.Misc.SwitchAdd != 0)
					cmd->viewangles.y += ClientVars.LegitBot.AntiAim.Move.YawAdd + ClientVars.LegitBot.AntiAim.Misc.SwitchAdd;
				break;
			}


			case 6: { //Static
				custom = true;
				cmd->viewangles.y += ClientVars.LegitBot.AntiAim.Move.YawAdd;
				break;
			}

			case 7: { //Lower Body
				cmd->viewangles.y += ClientVars.LegitBot.AntiAim.Move.YawAdd;
				if (shouldBreakLby())
					cmd->viewangles.y += ClientVars.LegitBot.AntiAim.Misc.lbyDelta;
				break;
			}

			case 8: { //Freestanding
				cmd->viewangles.y = freestanding();
				break;
			}
			}
			if (!custom)
				cmd->viewangles.y += ClientVars.LegitBot.AntiAim.Move.YawAdd;
		}
		else if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND)) { //Real - Yaw - In Air
			bool custom = false;
			switch (ClientVars.LegitBot.AntiAim.Air.Yaw) {
			case 1: { //Random
				cmd->viewangles.y = (rand() % 360) - 180;
				break;
			}

			case 2: { //Spinbot
				if (spin >= 180)
					spin = -180;

				spin += ClientVars.LegitBot.AntiAim.Misc.SpinbotSpeed;
				cmd->viewangles.y = spin;
				break;
			}

			case 3: { //Manual Switch
				if (ClientVars.AntiAim.type == 0) {
					if (switchxd)
						cmd->viewangles.y += 60;
					else
						cmd->viewangles.y += 120;
				}
				else if (ClientVars.AntiAim.type == 1) {
					if (switchxd)
						cmd->viewangles.y -= 60;
					else
						cmd->viewangles.y -= 120;
				}
				else if (ClientVars.AntiAim.type == 2) {
					cmd->viewangles.y += 180;
				}
				break;
			}

			case 4: { //Jitter
				custom = true;
				if (jitter && ClientVars.LegitBot.AntiAim.Misc.JitterRange != 0) {
					float lastJitterxd = ClientVars.LegitBot.AntiAim.Air.YawAdd + rand() % ClientVars.LegitBot.AntiAim.Misc.JitterRange;
					lastJitterAirReal = lastJitterxd;
					cmd->viewangles.y += lastJitterxd;
				}
				else {
					cmd->viewangles.y += lastJitterAirReal;
				}
				break;
			}

			case 5: { //Switch
				custom = true;
				if (switchxd)
					cmd->viewangles.y += ClientVars.LegitBot.AntiAim.Air.YawAdd;
				else if (ClientVars.LegitBot.AntiAim.Misc.SwitchAdd != 0)
					cmd->viewangles.y += ClientVars.LegitBot.AntiAim.Air.YawAdd + ClientVars.LegitBot.AntiAim.Misc.SwitchAdd;
				break;
			}

			case 6: { //Static
				custom = true;
				cmd->viewangles.y += ClientVars.LegitBot.AntiAim.Air.YawAdd;
				break;
			}

			case 7: { //Lower Body
				cmd->viewangles.y += ClientVars.LegitBot.AntiAim.Air.YawAdd;
				if (shouldBreakLby())
					cmd->viewangles.y += ClientVars.LegitBot.AntiAim.Misc.lbyDelta;
				break;
			}

			case 8: { //Freestanding
				cmd->viewangles.y = freestanding();
				break;
			}
			}
			if (!custom)
				cmd->viewangles.y += ClientVars.LegitBot.AntiAim.Air.YawAdd;
		}
		latestReal = cmd->viewangles;
	}
	}

	static void SetAntiAim(CInput::CUserCmd* cmd)
	{
		if (ClientVars.AntiAim.Misc.rightAA != 0 && GetAsyncKeyState(ClientVars.AntiAim.Misc.rightAA))
			ClientVars.AntiAim.type = 0;
		else if (ClientVars.AntiAim.Misc.leftAA != 0 && GetAsyncKeyState(ClientVars.AntiAim.Misc.leftAA))
			ClientVars.AntiAim.type = 1;
		else if (ClientVars.AntiAim.Misc.downAA != 0 && GetAsyncKeyState(ClientVars.AntiAim.Misc.downAA))
			ClientVars.AntiAim.type = 2;
		//else if (ClientVars.LegitBot.AntiAim.Misc.upAA != 0 && GetAsyncKeyState(ClientVars.LegitBot.AntiAim.Misc.upAA))
		//	ClientVars.AntiAim.type = 3;

		if (ticksxd >= ClientVars.AntiAim.Misc.SwitchSpeed) {
			switchxd = !switchxd;
			ticksxd = 0;
		}
		else {
			ticksxd++;
		}

		if (ticks >= ClientVars.AntiAim.Misc.JitterSpeed){
			jitter = !jitter;
			ticks = 0;
		} else {
			ticks++;
		}

		//Pitch
		if (Hacks.LocalPlayer->GetVecVelocity().Length2D() < 0.1f && Hacks.LocalPlayer->GetFlags() & FL_ONGROUND) { //Real - Pitch - Stand
			switch (ClientVars.AntiAim.Stand.Pitch) {
				case 1: { //Emotion
					cmd->viewangles.x = 89;
					break;
				}

				case 2: { //Up
					cmd->viewangles.x = -89;
					break;
				}

				case 3: { //Fake Up
					cmd->viewangles.x = -180;
					break;
				}

				case 4: { //Fake Down
					cmd->viewangles.x = 180;
					break;
				}

				case 5: { //Fake Zero
					cmd->viewangles.x = 1080;
					break;
				}

				case 6: { //Swap
					if (ClientVars.AntiAim.SwapShots)
						cmd->viewangles.x = -89;
					else
						cmd->viewangles.x = 89;
					break;
				}

				case 7: { //Custom
					cmd->viewangles.x = ClientVars.AntiAim.Stand.PitchAdd;
					break;
				}
			}
		} else if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 0.1f && Hacks.LocalPlayer->GetFlags() & FL_ONGROUND) { //Real - Pitch - Move
			switch (ClientVars.AntiAim.Move.Pitch) {
				case 1: { //Emotion
					cmd->viewangles.x = 89;
					break;
				}

				case 2: { //Up
					cmd->viewangles.x = -89;
					break;
				}

				case 3: { //Fake Up
					cmd->viewangles.x = -180;
					break;
				}

				case 4: { //Fake Down
					cmd->viewangles.x = 180;
					break;
				}

				case 5: { //Fake Zero
					cmd->viewangles.x = 1080;
					break;
				}

				case 6: { //Swap
					if (ClientVars.AntiAim.SwapShots)
						cmd->viewangles.x = -89;
					else
						cmd->viewangles.x = 89;
					break;
				}

				case 7: { //Custom
					cmd->viewangles.x = ClientVars.AntiAim.Move.PitchAdd;
					break;
				}
			}
		} else if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND)) { //Real - Pitch - In Air
			switch (ClientVars.AntiAim.Air.Pitch) {
				case 1: { //Emotion
					cmd->viewangles.x = 89;
					break;
				}

				case 2: { //Up
					cmd->viewangles.x = -89;
					break;
				}

				case 3: { //Fake Up
					cmd->viewangles.x = -180;
					break;
				}

				case 4: { //Fake Down
					cmd->viewangles.x = 180;
					break;
				}

				case 5: { //Fake Zero
					cmd->viewangles.x = 1080;
					break;
				}

				case 6: { //Swap
					if (ClientVars.AntiAim.SwapShots)
						cmd->viewangles.x = -89;
					else
						cmd->viewangles.x = 89;
					break;
				}

				case 7: { //Custom
					cmd->viewangles.x = ClientVars.AntiAim.Air.PitchAdd;
					break;
				}
			}
		}
		

		//Yaws
		if (Hacks.SendPacket) {
			if (Hacks.LocalPlayer->GetVecVelocity().Length2D() < 0.1f && Hacks.LocalPlayer->GetFlags() & FL_ONGROUND) { //Fake - Yaw - Stand 
				bool custom = false;
				switch (ClientVars.AntiAim.Stand.Fake) {
					case 1: { //Random
						cmd->viewangles.y = (rand() % 360) - 180;
						break;
					}

					case 2: { //Spinbot
						if (spin >= 180)
							spin = -180;

						spin += ClientVars.AntiAim.Misc.SpinbotSpeed;
						cmd->viewangles.y = spin;
						break;
					}

					case 3: { //Manual Switch
						if (ClientVars.AntiAim.type == 0) {
							if (switchxd)
								cmd->viewangles.y += 120;
							else
								cmd->viewangles.y += 60;
						}
						else if (ClientVars.AntiAim.type == 1) {
							if (switchxd)
								cmd->viewangles.y -= 120;
							else
								cmd->viewangles.y -= 60;
						}
						else if (ClientVars.AntiAim.type == 2) {
							cmd->viewangles.y += 180;
						}
						break;
					}

					case 4: { //Jitter
						custom = true;
						if (jitter && ClientVars.AntiAim.Misc.JitterRange != 0) {
							float lastJitterxd = ClientVars.AntiAim.Stand.FakeAdd + rand() % ClientVars.AntiAim.Misc.JitterRange;
							lastJitterStandFake = lastJitterxd;
							cmd->viewangles.y += lastJitterxd;
						}
						else {
							cmd->viewangles.y += lastJitterStandFake;
						}
						break;
					}

					case 5: { //Switch
						custom = true;
						if (switchxd)
							cmd->viewangles.y += ClientVars.AntiAim.Stand.FakeAdd;
						else if (ClientVars.AntiAim.Misc.SwitchAdd != 0)
							cmd->viewangles.y += ClientVars.AntiAim.Stand.FakeAdd + ClientVars.AntiAim.Misc.SwitchAdd;
						break;
					}

					case 6: { //Static
						custom = true;
						cmd->viewangles.y += ClientVars.AntiAim.Stand.FakeAdd;
						break;
					}

					case 7: { //Lower Body
						cmd->viewangles.y += ClientVars.AntiAim.Stand.FakeAdd;
						if (shouldBreakLby())
							cmd->viewangles.y += ClientVars.AntiAim.Misc.lbyDelta;
						break;
					}

					case 8: { //Freestanding
						cmd->viewangles.y = freestanding();
						break;
					}

					case 9: { //Inverse
						cmd->viewangles.y = latestReal.y - 180;
						break;
					}
				}
				if(!custom)
					cmd->viewangles.y += ClientVars.AntiAim.Stand.FakeAdd;

			}
			else if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 0.1f && Hacks.LocalPlayer->GetFlags() & FL_ONGROUND) { //Fake - Yaw - Move
				bool custom = false;
				switch (ClientVars.AntiAim.Move.Fake) {
					case 1: { //Random
						cmd->viewangles.y = (rand() % 360) - 180;
						break;
					}

					case 2: { //Spinbot
						if (spin >= 180)
							spin = -180;

						spin += ClientVars.AntiAim.Misc.SpinbotSpeed;
						cmd->viewangles.y = spin;
						break;
					}

					case 3: { //Manual Switch
						if (ClientVars.AntiAim.type == 0) {
							if (switchxd)
								cmd->viewangles.y += 120;
							else
								cmd->viewangles.y += 60;
						}
						else if (ClientVars.AntiAim.type == 1) {
							if (switchxd)
								cmd->viewangles.y -= 120;
							else
								cmd->viewangles.y -= 60;
						}
						else if (ClientVars.AntiAim.type == 2) {
							cmd->viewangles.y += 180;
						}
						break;
					}

					case 4: { //Jitter
						custom = true;
						if (jitter && ClientVars.AntiAim.Misc.JitterRange != 0) {
							float lastJitterxd = ClientVars.AntiAim.Move.FakeAdd + rand() % ClientVars.AntiAim.Misc.JitterRange;
							lastJitterMoveFake = lastJitterxd;
							cmd->viewangles.y += lastJitterxd;
						}
						else {
							cmd->viewangles.y += lastJitterMoveFake;
						}
						break;
					}

					case 5: { //Switch
						custom = true;
						if (switchxd)
							cmd->viewangles.y += ClientVars.AntiAim.Move.FakeAdd;
						else if (ClientVars.AntiAim.Misc.SwitchAdd != 0)
							cmd->viewangles.y += ClientVars.AntiAim.Move.FakeAdd + ClientVars.AntiAim.Misc.SwitchAdd;
						break;
					}

					case 6: { //Static
						custom = true;
						cmd->viewangles.y += ClientVars.AntiAim.Move.FakeAdd;
						break;
					}

					case 7: { //Lower Body
						cmd->viewangles.y += ClientVars.AntiAim.Move.FakeAdd;
						if (shouldBreakLby())
							cmd->viewangles.y += ClientVars.AntiAim.Misc.lbyDelta;
						break;
					}

					case 8: { //Freestanding
						cmd->viewangles.y = freestanding();
						break;
					}

					case 9: { //Inverse
						cmd->viewangles.y = latestReal.y - 180;
						break;
					}
				}
				if (!custom)
					cmd->viewangles.y += ClientVars.AntiAim.Move.FakeAdd;
			}
			else if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND)) { //Fake - Yaw - In Air
				bool custom = false;
					switch (ClientVars.AntiAim.Air.Fake) {
					case 1: { //Random
						cmd->viewangles.y = (rand() % 360) - 180;
						break;
					}

					case 2: { //Spinbot
						if (spin >= 180)
							spin = -180;

						spin += ClientVars.AntiAim.Misc.SpinbotSpeed;
						cmd->viewangles.y = spin;
						break;
					}

					case 3: { //Manual Switch
						if (ClientVars.AntiAim.type == 0) {
							if (switchxd)
								cmd->viewangles.y += 120;
							else
								cmd->viewangles.y += 60;
						}
						else if (ClientVars.AntiAim.type == 1) {
							if (switchxd)
								cmd->viewangles.y -= 120;
							else
								cmd->viewangles.y -= 60;
						}
						else if (ClientVars.AntiAim.type == 2) {
							cmd->viewangles.y += 180;
						}
						break;
					}

					case 4: { //Jitter
						custom = true;
						if (jitter && ClientVars.AntiAim.Misc.JitterRange != 0) {
							float lastJitterxd = ClientVars.AntiAim.Air.FakeAdd + rand() % ClientVars.AntiAim.Misc.JitterRange;
							lastJitterAirFake = lastJitterxd;
							cmd->viewangles.y += lastJitterxd;
						}
						else {
							cmd->viewangles.y += lastJitterAirFake;
						}
						break;
					}

					case 5: { //Switch
						custom = true;
						if (switchxd)
							cmd->viewangles.y += ClientVars.AntiAim.Air.FakeAdd;
						else if (ClientVars.AntiAim.Misc.SwitchAdd != 0)
							cmd->viewangles.y += ClientVars.AntiAim.Air.FakeAdd + ClientVars.AntiAim.Misc.SwitchAdd;
						break;
					}

					case 6: { //Static
						custom = true;
						cmd->viewangles.y += ClientVars.AntiAim.Air.FakeAdd;
						break;
					}

					case 7: { //Lower Body
						cmd->viewangles.y += ClientVars.AntiAim.Air.FakeAdd;
						if (shouldBreakLby())
							cmd->viewangles.y += ClientVars.AntiAim.Misc.lbyDelta;
						break;
					}

					case 8: { //Freestanding
						cmd->viewangles.y = freestanding();
						break;
					}

					case 9: { //Inverse
						cmd->viewangles.y = latestReal.y - 180;
						break;
					}
				}
				if (!custom)
					cmd->viewangles.y += ClientVars.AntiAim.Air.FakeAdd;
			}
			latestFake = cmd->viewangles;
		} else {
			if (Hacks.LocalPlayer->GetVecVelocity().Length2D() < 0.01f && Hacks.LocalPlayer->GetFlags() & FL_ONGROUND) { //Real - Yaw - Stand
				bool custom = false;
				switch (ClientVars.AntiAim.Stand.Yaw) {
					case 1: { //Random
						cmd->viewangles.y = (rand() % 360) - 180;
						break;
					}

					case 2: { //Spinbot
						if (spin >= 180)
							spin = -180;

						spin += ClientVars.AntiAim.Misc.SpinbotSpeed;
						cmd->viewangles.y = spin;
						break;
					}

					case 3: { //Manual LBY Switch
						if (ClientVars.AntiAim.type == 1) {
							if (switchxd)
								cmd->viewangles.y += 120;
							else
								cmd->viewangles.y += 60;

							if (shouldBreakLby())
								cmd->viewangles.y += ClientVars.AntiAim.Misc.lbyDelta;
						}
						else if(ClientVars.AntiAim.type == 0){
							if (switchxd)
								cmd->viewangles.y -= 120;
							else
								cmd->viewangles.y -= 60;

							if (shouldBreakLby())
								cmd->viewangles.y -= ClientVars.AntiAim.Misc.lbyDelta;
						} else if (ClientVars.AntiAim.type == 2) {
							cmd->viewangles.y += 180;
						}
						break;
					}

					case 4: { //Jitter
						custom = true;
						if (jitter && ClientVars.AntiAim.Misc.JitterRange != 0) {
							float lastJitterxd = ClientVars.AntiAim.Stand.YawAdd + rand() % ClientVars.AntiAim.Misc.JitterRange;
							lastJitterStandReal = lastJitterxd;
							cmd->viewangles.y += lastJitterxd;
						}
						else {
							cmd->viewangles.y += lastJitterStandReal;
						}
						break;
					}

					case 5: { //Switch
						custom = true;
						if (switchxd)
							cmd->viewangles.y += ClientVars.AntiAim.Stand.YawAdd;
						else if (ClientVars.AntiAim.Misc.SwitchAdd != 0)
							cmd->viewangles.y += ClientVars.AntiAim.Stand.YawAdd + ClientVars.AntiAim.Misc.SwitchAdd;
						break;
					}

					case 6: { //Static
						custom = true;
						cmd->viewangles.y += ClientVars.AntiAim.Stand.YawAdd;
						break;
					}

					case 7: { //Lower Body
						cmd->viewangles.y += ClientVars.AntiAim.Stand.YawAdd;
						if (shouldBreakLby())
							cmd->viewangles.y += ClientVars.AntiAim.Misc.lbyDelta;
						break;
					}

					case 8: { //Freestanding
						cmd->viewangles.y = freestanding();
						break;
					}
				}
				if (!custom)
					cmd->viewangles.y += ClientVars.AntiAim.Stand.YawAdd;
			}
			else if (Hacks.LocalPlayer->GetVecVelocity().Length2D() != 0.f && Hacks.LocalPlayer->GetFlags() & FL_ONGROUND) { //Real - Yaw - Move
				bool custom = false;
				switch (ClientVars.AntiAim.Move.Yaw) {
					case 1: { //Random
						cmd->viewangles.y = (rand() % 360) - 180;
						break;
					}

					case 2: { //Spinbot
						if (spin >= 180)
							spin = -180;

						spin += ClientVars.AntiAim.Misc.SpinbotSpeed;
						cmd->viewangles.y = spin;
						break;
					}

					case 3: { //Manual Switch
						if (ClientVars.AntiAim.type == 1) {
							if (switchxd)
								cmd->viewangles.y += 120;
							else
								cmd->viewangles.y += 60;
						}
						else if (ClientVars.AntiAim.type == 0) {
							if (switchxd)
								cmd->viewangles.y -= 120;
							else
								cmd->viewangles.y -= 60;
						}
						else if (ClientVars.AntiAim.type == 2) {
							cmd->viewangles.y += 180;
						}
						break;
					}

					case 4: { //Jitter
						custom = true;
						if (jitter && ClientVars.AntiAim.Misc.JitterRange != 0) {
							float lastJitterxd = ClientVars.AntiAim.Move.YawAdd + rand() % ClientVars.AntiAim.Misc.JitterRange;
							lastJitterMoveReal = lastJitterxd;
							cmd->viewangles.y += lastJitterxd;
						}
						else {
							cmd->viewangles.y += lastJitterMoveReal;
						}
						break;
					}

					case 5: { //Switch
						custom = true;
						if (switchxd)
							cmd->viewangles.y += ClientVars.AntiAim.Move.YawAdd;
						else if (ClientVars.AntiAim.Misc.SwitchAdd != 0)
							cmd->viewangles.y += ClientVars.AntiAim.Move.YawAdd + ClientVars.AntiAim.Misc.SwitchAdd;
						break;
					}


					case 6: { //Static
						custom = true;
						cmd->viewangles.y += ClientVars.AntiAim.Move.YawAdd;
						break;
					}

					case 7: { //Lower Body
						cmd->viewangles.y += ClientVars.AntiAim.Move.YawAdd;
						if (shouldBreakLby())
							cmd->viewangles.y += ClientVars.AntiAim.Misc.lbyDelta;
						break;
					}

					case 8: { //Freestanding
						cmd->viewangles.y = freestanding();
						break;
					}
				}
				if (!custom)
					cmd->viewangles.y += ClientVars.AntiAim.Move.YawAdd;
			}
			else if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND)) { //Real - Yaw - In Air
				bool custom = false;
				switch (ClientVars.AntiAim.Air.Yaw) {
					case 1: { //Random
						cmd->viewangles.y = (rand() % 360) - 180;
						break;
					}

					case 2: { //Spinbot
						if (spin >= 180)
							spin = -180;

						spin += ClientVars.AntiAim.Misc.SpinbotSpeed;
						cmd->viewangles.y = spin;
						break;
					}

					case 3: { //Manual Switch
						if (ClientVars.AntiAim.type == 1) {
							if (switchxd)
								cmd->viewangles.y += 120;
							else
								cmd->viewangles.y += 60;
						}
						else if (ClientVars.AntiAim.type == 0) {
							if (switchxd)
								cmd->viewangles.y -= 120;
							else
								cmd->viewangles.y -= 60;
						}
						else if (ClientVars.AntiAim.type == 2) {
							cmd->viewangles.y += 180;
						}
						break;
					}

					case 4: { //Jitter
						custom = true;
						if (jitter && ClientVars.AntiAim.Misc.JitterRange != 0) {
							float lastJitterxd = ClientVars.AntiAim.Air.YawAdd + rand() % ClientVars.AntiAim.Misc.JitterRange;
							lastJitterAirReal = lastJitterxd;
							cmd->viewangles.y += lastJitterxd;
						} else {
							cmd->viewangles.y += lastJitterAirReal;
						}
						break;
					}

					case 5: { //Switch
						custom = true;
						if (switchxd)
							cmd->viewangles.y += ClientVars.AntiAim.Air.YawAdd;
						else if (ClientVars.AntiAim.Misc.SwitchAdd != 0)
							cmd->viewangles.y += ClientVars.AntiAim.Air.YawAdd + ClientVars.AntiAim.Misc.SwitchAdd;
						break;
					}

					case 6: { //Static
						custom = true;
						cmd->viewangles.y += ClientVars.AntiAim.Air.YawAdd;
						break;
					}

					case 7: { //Lower Body
						cmd->viewangles.y += ClientVars.AntiAim.Air.YawAdd;
						if (shouldBreakLby())
							cmd->viewangles.y += ClientVars.AntiAim.Misc.lbyDelta;
						break;
					}

					case 8: { //Freestanding
						cmd->viewangles.y = freestanding();
						break;
					}
				}
				if (!custom)
					cmd->viewangles.y += ClientVars.AntiAim.Air.YawAdd;
			}
			latestReal = cmd->viewangles;
		}
	}
};

