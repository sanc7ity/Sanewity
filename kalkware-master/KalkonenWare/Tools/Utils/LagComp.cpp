#pragma once
#include "../../stdafx.h"
#include "LagComp.h"
#include "../Hacks/Misc.h"
#include "../Hacks/Parser.h"
#define MAX_BACKTRACKABLE_TICKS 12





void BackTrack::Update(int tick_count)
{
	if (!ClientVars.Ragebot.BackTrack)
		return;

	latest_tick = tick_count;
	for (int i = 0; i < 64; i++)
	{
		UpdateRecord(i);
	}
}

bool BackTrack::IsTickValid(int tick)
{
	int delta = latest_tick - tick;
	float deltaTime = delta * Interfaces.pGlobalVars->interval_per_tick;
	return (fabs(deltaTime) <= 0.2f);
}

void BackTrack::UpdateRecord(int i)
{
	CBaseEntity* pEntity = Interfaces.pEntList->GetClientEntity(i);
	if (pEntity && pEntity->isAlive() && !pEntity->IsDormant())
	{
		float lby = pEntity->pelvisangs();
		if (lby != records[i].lby)
		{
			records[i].tick_count = latest_tick;
			records[i].lby = lby;
		}
	}
	else
	{
		records[i].tick_count = 0;
	}
}

bool BackTrack::RunLBYBackTrack(int i, CInput::CUserCmd* cmd, CBaseEntity* pEntity)
{
	if (IsTickValid(records[i].tick_count))
	{
		pEntity->GetEyeAnglesPointer()->y = records[i].lby;
		cmd->tick_count = records[i].tick_count;
		return true;
	}
	return false;
}

inline Vector angle_vector(Vector meme)
{
	auto sy = sin(meme.y / 180.f * static_cast<float>(PI));
	auto cy = cos(meme.y / 180.f * static_cast<float>(PI));

	auto sp = sin(meme.x / 180.f * static_cast<float>(PI));
	auto cp = cos(meme.x / 180.f* static_cast<float>(PI));

	return Vector(cp*cy, cp*sy, -sp);
}


void BackTrack::legitBackTrack(CInput::CUserCmd* cmd, CBaseEntity* pLocal)
{
	if (ClientVars.LegitBot.backtrack)
	{
		int bestTargetIndex = -1;
		float bestFov = FLT_MAX;
		player_info_t info;
		if (!pLocal->isAlive())
			return;

		for (int i = 0; i < Interfaces.pEngine->GetMaxClients(); i++)
		{
			auto entity = (CBaseEntity*)Interfaces.pEntList->GetClientEntity(i);

			if (!entity || !pLocal)
				continue;

			if (entity == pLocal)
				continue;

			if (!Interfaces.pEngine->GetPlayerInfo(i, &info))
				continue;

			if (entity->IsDormant())
				continue;

			if (entity->GetTeam() == pLocal->GetTeam())
				continue;

			if (entity->isAlive())
			{

				float simtime = entity->GetSimulationTime();
				Vector hitboxPos = Misc::GetHitboxPosition(entity, 0);

				headPositions[i][cmd->command_number % MAX_BACKTRACKABLE_TICKS] = backtrackData{ simtime, hitboxPos };
				Vector ViewDir = angle_vector(cmd->viewangles + (pLocal->localPlayerExclusive()->GetAimPunchAngle() * 2.f));
				float FOVDistance = Misc::GetFOV(hitboxPos, pLocal->GetEyePosition(), ViewDir, false);

				if (bestFov > FOVDistance)
				{
					bestFov = FOVDistance;
					bestTargetIndex = i;
				}
			}
		}

		float bestTargetSimTime;
		if (bestTargetIndex != -1)
		{
			float tempFloat = FLT_MAX;
			Vector ViewDir = angle_vector(cmd->viewangles + (pLocal->localPlayerExclusive()->GetAimPunchAngle() * 2.f));
			for (int t = 0; t < MAX_BACKTRACKABLE_TICKS; ++t)
			{
				float tempFOVDistance = Misc::GetFOV(headPositions[bestTargetIndex][t].hitboxPos, pLocal->GetEyePosition(), ViewDir, false);
				if (tempFloat > tempFOVDistance && headPositions[bestTargetIndex][t].simtime > pLocal->GetSimulationTime() - 1)
				{
					tempFloat = tempFOVDistance;
					bestTargetSimTime = headPositions[bestTargetIndex][t].simtime;
				}
			}
			if (cmd->buttons & IN_ATTACK)
			{
				cmd->tick_count = Misc::TIME_TO_TICKS(bestTargetSimTime);
			}
		}
	}
}

void BackTrack::AddLatencyToNetchan(INetChannel *netchan)
{
	for (auto& seq : sequences)
	{
		if (Interfaces.pGlobalVars->realtime - seq.curtime >= 0.046875f)
		{
			netchan->m_nInReliableState = seq.inreliablestate;
			netchan->m_nInSequenceNr = seq.sequencenr;
			break;
		}
	}
}

void BackTrack::ClearIncomingSequences()
{
	Interfaces.pGlobalVars->Real_m_nInSequencenumber = 0;
	sequences.clear();
}

void BackTrack::UpdateIncomingSequences()
{
	DWORD ClientState = Interfaces.g_ClientStateTest;
	if (ClientState)
	{
		INetChannel *netchan = *(INetChannel**)(ClientState + 0x9C);
		if (netchan)
		{
			if (Interfaces.pGlobalVars->Real_m_nInSequencenumber == 0)
			{
				Interfaces.pGlobalVars->Real_m_nInSequencenumber = netchan->m_nInSequenceNr;
				lastincomingsequencenumber = netchan->m_nInSequenceNr;
			}

			if (netchan->m_nInSequenceNr > lastincomingsequencenumber) {
				lastincomingsequencenumber = netchan->m_nInSequenceNr;
				sequences.push_front(CIncomingSequence(netchan->m_nInReliableState, netchan->m_nOutReliableState, netchan->m_nInSequenceNr, Interfaces.pGlobalVars->realtime));
			}

			if (sequences.size() > 2048)
				sequences.pop_back();
		}
	}
}


int __fastcall Hooks::hookedDatagram(INetChannel* netchan, void*, bf_write* datagram)
{
	if (!ClientVars.Misc.fakelatency && datagram)
	{
		return Hacks.oSendDatagram(netchan, datagram);
	}

	int instate = netchan->m_nInReliableState;
	int insequencenr = netchan->m_nInSequenceNr;

	backtracking->AddLatencyToNetchan(netchan);

	int ret = Hacks.oSendDatagram(netchan, datagram);

	netchan->m_nInReliableState = instate;
	netchan->m_nInSequenceNr = insequencenr;
	return ret;
}





BackTrack* backtracking = new BackTrack();
backtrackData headPositions[64][12];