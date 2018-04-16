#pragma once
#include "../../stdafx.h"
#include "../Hacks/Parser.h"

struct lbyRecords
{
	int tick_count;
	float lby;
};
struct backtrackData
{
	float simtime;
	Vector hitboxPos;
};
struct CIncomingSequence
{
	CIncomingSequence::CIncomingSequence(int instate, int outstate, int seqnr, float time)
	{
		inreliablestate = instate;
		outreliablestate = outstate;
		sequencenr = seqnr;
		curtime = time;
	}
	int inreliablestate;
	int outreliablestate;
	int sequencenr;
	float curtime;
};

namespace Hooks {
	extern int __fastcall hookedDatagram(INetChannel* netchan, void*, bf_write* datagram);
}




class BackTrack
{
	int latest_tick;
	bool IsTickValid(int tick);
	void UpdateRecord(int i);
	int lastincomingsequencenumber;

	std::deque<CIncomingSequence> sequences;

public:
	lbyRecords records[64];
	bool RunLBYBackTrack(int i, CInput::CUserCmd* cmd, CBaseEntity* pEntity);
	void Update(int tick_count);
	void legitBackTrack(CInput::CUserCmd* cmd, CBaseEntity* pLocal);

	void AddLatencyToNetchan(INetChannel *netchan);
	void ClearIncomingSequences();
	void UpdateIncomingSequences();
};

extern backtrackData headPositions[64][12];

extern BackTrack* backtracking;


