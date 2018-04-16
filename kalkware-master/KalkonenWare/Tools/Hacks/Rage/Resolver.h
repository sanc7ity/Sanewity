#pragma once
#include "stdafx.h"
#include "../Misc.h"
#include "../CreateMoveETC.h"
#include "../../Utils/LagComp.h"

class Resolver
{
public:
	static void BruteForceY(CBaseEntity* pEntity) {
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		int num = ResolverInfo.missedShots % 5;

		switch (num) {
			case 0:
				pEntity->GetEyeAnglesPointer()->y = pEntity->pelvisangs() + 160;
				break;
			case 1:
				pEntity->GetEyeAnglesPointer()->y = pEntity->pelvisangs() - 160;
				break;
			case 2:
				pEntity->GetEyeAnglesPointer()->y = pEntity->pelvisangs() - 180;
				break;
			case 3:
				pEntity->GetEyeAnglesPointer()->y = pEntity->pelvisangs() + 90;
				break;
			case 4:
				pEntity->GetEyeAnglesPointer()->y = pEntity->pelvisangs() - 90;
				break;
		}
	}

	static void BruteForceP(CBaseEntity* pEntity) {
		CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		int num = ResolverInfo.missedShots % 3;

		switch (num) {
		case 0:
			pEntity->GetEyeAnglesPointer()->x = -90;
			break;
		case 1:
			pEntity->GetEyeAnglesPointer()->x = 90;
			break;
		case 2:
			pEntity->GetEyeAnglesPointer()->x = 0;
			break;
		}
	}

	static void ResolvePitch()
	{
		if (Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame())
		{
			CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
			if (pLocal) {
				for (auto i = 0; i < Interfaces.pEntList->GetHighestEntityIndex(); i++)
				{
					CBaseEntity* pEntity = Interfaces.pEntList->GetClientEntity(i);

					if (pEntity && pEntity->isValidPlayer() && pEntity->GetTeam() != pLocal->GetTeam() && pLocal->isAlive())
					{
						if (ClientVars.Ragebot.ResolvePitch == 1) {
							pEntity->GetEyeAnglesPointer()->x = -pEntity->GetEyeAnglesPointer()->x;
						} else if (ClientVars.Ragebot.ResolvePitch == 2) {
							BruteForceP(pEntity);
						}
					}
				}
			}
		}
	}

	static void Resolve()
	{
	}
};
