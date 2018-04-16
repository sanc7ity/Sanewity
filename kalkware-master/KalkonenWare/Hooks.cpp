#include "stdafx.h"
#include "Tools/Hacks/Misc.h"
#include "Tools/Utils/Playerlist.h"
#include "Tools/Hacks/Esp.h"
#include "Tools/Hacks/FarESP.h"
#include "Tools/Hacks/Rage/HVH.h"
#include "Tools/Hacks/Rage/Aimbot.h"
#include "Tools/Hacks/Rage/Resolver.h"
#include "Tools/Hacks/Legit.h"
#include "Tools/Hacks/CreateMoveETC.h"
#include "Tools/Hacks/KnifeBot.h"
#include "Tools/Hacks/ZeusBot.h"
#include "Tools/IMGUI/imgui.h"
#include "Tools/IMGUI/DX9/imgui_impl_dx9.h"
#include "Tools/IMGUI/imgui_internal.h"
#include "Tools/Menu/Menu.h"

#include <stdio.h>  
#include <intrin.h> 

#define DEV

#define PI_2 PI/2
#define PI_4 PI/4
#define INVALID_EHANDLE_INDEX 0xFFFFFFFF

#define MAX_USERCMD_LOSS 10
#define MAX_USERCMDS_SEND 62

static bool directinit = false;

FontsXD fontskek;
CHackManager Hacks;
VTHookManager VMTPanel;
VTHookManager VMTClient;
VTHookManager VMTEngine;
VTHookManager VMTModelRender;
VTHookManager VMTClientMode;
VTHookManager VMTGameEvent;
VTHookManager VMTSurface;
VTHookManager VMTD3D;
VTHookManager VMTSOUND;
VTHookManager VMTMDL;
VTHookManager VMTViewRender;
VTHookManager VMTNetChan;
VTHookManager VMTSendMove;

MenuVars ClientVars;
GlobalVariables GVars;

resolverInfo ResolverInfo;

playerInfo PlayerInfo;


class Hitbox;

std::vector< const char* > smoke_materials =
{
	"particle/beam_smoke_01",
	"particle/particle_smokegrenade",
	"particle/particle_smokegrenade1",
	"particle/particle_smokegrenade2",
	"particle/particle_smokegrenade3",
	"particle/particle_smokegrenade_sc",
	"particle/smoke1/smoke1",
	"particle/smoke1/smoke1_ash",
	"particle/smoke1/smoke1_nearcull",
	"particle/smoke1/smoke1_nearcull2",
	"particle/smoke1/smoke1_snow",
	"particle/smokesprites_0001",
	"particle/smokestack",
	"particle/vistasmokev1/vistasmokev1",
	"particle/vistasmokev1/vistasmokev1_emods",
	"particle/vistasmokev1/vistasmokev1_emods_impactdust",
	"particle/vistasmokev1/vistasmokev1_fire",
	"particle/vistasmokev1/vistasmokev1_nearcull",
	"particle/vistasmokev1/vistasmokev1_nearcull_fog",
	"particle/vistasmokev1/vistasmokev1_nearcull_nodepth",
	"particle/vistasmokev1/vistasmokev1_smokegrenade",
	"particle/vistasmokev1/vistasmokev4_emods_nocull",
	"particle/vistasmokev1/vistasmokev4_nearcull",
	"particle/vistasmokev1/vistasmokev4_nocull"
};

typedef void(*Fucntion)(IGameEvent* event);

RecvVarProxyFn oRecvnModelIndex;

struct BulletImpactLog
{
	BulletImpactLog(int userid, Vector FirePos, Vector ImpactPos, float ImpactTime)
	{
		this->m_iUserID = userid;
		this->m_vFirePosition = FirePos;
		this->m_vImpactPosition = ImpactPos;
		this->m_flImpactTime = ImpactTime;
	}

	int m_iUserID;
	Vector m_vFirePosition;
	Vector m_vImpactPosition;
	float m_flImpactTime;
};

vector<BulletImpactLog> BulletLogs;

void FnRoundStart(IGameEvent* event)
{
	if (GVars.unhooked)
		return;

	ResolverInfo.missedShots = 0;

}

void FnHurt(IGameEvent* event)
{
	if (GVars.unhooked)
		return;

	if (event->GetInt("headshot") == 1) {
		if (Interfaces.pEntList->GetClientEntity(event->GetInt("attacker"))->GetTeam() == Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer())->GetTeam()) {
			if (Interfaces.pEntList->GetClientEntity(event->GetInt("userid"))->GetFlags() & FL_ONGROUND  && Interfaces.pEntList->GetClientEntity(event->GetInt("userid"))->GetVecVelocity().Length2D() == 0) {

				ResolverInfo.savedLBY[event->GetInt("userid")] = Interfaces.pEntList->GetClientEntity(event->GetInt("userid"))->pelvisangs();

			}
		}
	}
	
	if (Interfaces.pEngine->GetPlayerForUserID(event->GetInt("attacker")) == Interfaces.pEngine->GetLocalPlayer())
	{

		ResolverInfo.missedShots -= 1;

	}

	if (ClientVars.Visual.Hitmarker)
	{
		if (Interfaces.pEngine->GetPlayerForUserID(event->GetInt("attacker")) == Interfaces.pEngine->GetLocalPlayer())
		{
			GVars.hitmarkeralpha = 1.f;
			Interfaces.pEngine->ClientCmd_Unrestricted("play buttons\\arena_switch_press_02.wav", 0);
		}
	}
	//if (Interfaces.pEngine->GetPlayerForUserID(event->GetInt("attacker")) == Interfaces.pEngine->GetLocalPlayer())
		//cout << "[Player Hurt]" << event->GetInt("attacker") << " : " << Interfaces.pGlobalVars->curtime << " Hitgroup: " << event->GetInt("hitgroup") << endl;
}

void FnDeath(IGameEvent* event)
{
	//if (Interfaces.pEngine->GetPlayerForUserID(event->GetInt("attacker")) == Interfaces.pEngine->GetLocalPlayer())
		//cout << "[Player Death]" << event->GetInt("attacker") << " : " << Interfaces.pGlobalVars->curtime << " Headshot?: " << event->GetInt("headshot") << endl;
}

void FnWpnFire(IGameEvent* event)
{
	if (GVars.unhooked)
		return;

	ClientVars.AntiAim.SwapShots = !ClientVars.AntiAim.SwapShots;

	CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

	if (pLocal) {
		if (Interfaces.pEngine->GetPlayerForUserID(event->GetInt("userid")) == Interfaces.pEngine->GetLocalPlayer())
		{
			CBaseCombatWeapon* weapon = pLocal->GetActiveBaseCombatWeapon();
			if (weapon)
			{
				if (!weapon->IsGrenade() && !weapon->IsKnife() && !weapon->IsBomb(weapon->GetId()))
				{

					ResolverInfo.missedShots += 1;
				}
			}
		}
	}
	//if (Interfaces.pEngine->GetPlayerForUserID(event->GetInt("userid")) == Interfaces.pEngine->GetLocalPlayer())
	//	cout << "[Weapon Fired]" << event->GetInt("userid") << " : " << Interfaces.pGlobalVars->curtime << endl;
}


void FnImpact(IGameEvent* event)
{
	auto shooter = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetPlayerForUserID(event->GetInt("userid")));

	Vector position(event->GetFloat("x"), event->GetFloat("y"), event->GetFloat("z"));
	if (shooter)
		BulletLogs.push_back(BulletImpactLog(event->GetInt("userid"), shooter->GetEyePosition(), position, Interfaces.pGlobalVars->curtime));

}

class CGameEventListener : public IGameEventListener2
{
private:
	std::string eventName;
	Fucntion Call;
	bool server;
public:
	CGameEventListener() : eventName(""), Call(nullptr), server(false)
	{
	}

	CGameEventListener(const std::string& gameEventName, const Fucntion Func, bool Server) : eventName(gameEventName), Call(Func), server(Server)
	{
		this->RegListener();
	}

	virtual void FireGameEvent(IGameEvent* event)
	{
		this->Call(event);
	}

	virtual int IndicateEventHandling(void)
	{
		return 0x2A;
	}

	void RegListener(void)
	{
		static bool first = true;
		if (!first)
			return;
		if (Interfaces.g_GameEventMgr->AddListener(this, this->eventName.c_str(), server))
			Hacks.listeners.push_back(this);
	}
};

#define REG_EVENT_LISTENER(p, e, n, s) p = new CGameEventListener(n, e, s)
CGameEventListener* ge_Deaths;
CGameEventListener* ge_Hurts;
CGameEventListener* ge_roundStart;
CGameEventListener* ge_Impacts;
CGameEventListener* ge_WpnFires;
CGameEventListener* ge_PlayerSay;

void Init()
{
	REG_EVENT_LISTENER(ge_Deaths, &FnDeath, "player_death", false);
	REG_EVENT_LISTENER(ge_Hurts, &FnHurt, "player_hurt", false);
	REG_EVENT_LISTENER(ge_roundStart, &FnRoundStart, "round_start", false);
	REG_EVENT_LISTENER(ge_Impacts, &FnImpact, "bullet_impact", false);
	REG_EVENT_LISTENER(ge_WpnFires, &FnWpnFire, "weapon_fire", false);
	REG_EVENT_LISTENER(ge_PlayerSay, &FarESP::FarESPIngoing, "player_say", false);
}

void DrawBeam(Vector src, Vector end, CColor color)
{
	int r, g, b, a;
	color.GetColor(r, g, b, a);
	BeamInfo_t beamInfo;
	beamInfo.m_nType = TE_BEAMPOINTS;
	beamInfo.m_pszModelName = "sprites/physbeam.vmt";
	beamInfo.m_nModelIndex = -1; // will be set by CreateBeamPoints if its -1
	beamInfo.m_flHaloScale = 0.0f;
	beamInfo.m_flLife = 1.5f;
	beamInfo.m_flWidth = 1.0f;
	beamInfo.m_flEndWidth = 1.0f;
	beamInfo.m_flFadeLength = 0.0f;
	beamInfo.m_flAmplitude = 2.0f;
	beamInfo.m_flBrightness = a;
	beamInfo.m_flSpeed = 0.2f;
	beamInfo.m_nStartFrame = 0;
	beamInfo.m_flFrameRate = 0.f;
	beamInfo.m_flRed = r;
	beamInfo.m_flGreen = g;
	beamInfo.m_flBlue = b;
	beamInfo.m_nSegments = 2;
	beamInfo.m_bRenderable = true;
	beamInfo.m_nFlags = 0;

	beamInfo.m_vecStart = src;
	beamInfo.m_vecEnd = end;

	Beam_t* myBeam = Interfaces.g_pViewRenderBeams->CreateBeamPoints(beamInfo);

	if (myBeam)
		Interfaces.g_pViewRenderBeams->DrawBeam(myBeam);
}


void __stdcall Hooked_PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	if (GVars.unhooked)
		return;

	if (ClientVars.Visual.NoScope)
	{
		if (!strcmp(Interfaces.pPanel->GetName(vguiPanel), "HudZoom"))
			return;
	}
	Hacks.oPaintTraverse(Interfaces.pPanel, vguiPanel, forceRepaint, allowForce);

	if (strcmp("FocusOverlayPanel", Interfaces.pPanel->GetName(vguiPanel)))
	{
		return;
	}

	if (Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame())
	{
		Hacks.LocalPlayer = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
		Hacks.LocalWeapon = Hacks.LocalPlayer->GetActiveBaseCombatWeapon();

		if (Hacks.LocalPlayer)
		{
			Esp::DoEsp();
			if (ClientVars.Visual.NoScope)
				Esp::DrawScope();
		}
	}	
	Esp::Watermark();
	Esp::UTCheck();
}

int __stdcall Hooked_DoPostScreenEffects(int a1)
{
	if (Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame()) {
		if (Hacks.LocalPlayer) {
			Esp::CallGlow();
		}
	}

	return Hacks.oDoPostScreenEffects(Interfaces.pClientMode, a1);
}

/*
int tickBaseShift = 0;
bool inSendMove = false;
bool firstSendMovePack = false;

bool __fastcall WriteUsercmdDeltaToBuffer_hook(void* ecx, void* edx, int nSlot, void* buf, int from, int to, bool isNewCmd)
{
	static DWORD WriteUsercmdDeltaToBufferReturn = (DWORD)Utils.PFindPattern("engine.dll", "84 C0 74 04 B0 01 EB 02 32 C0 8B FE 46 3B F3 7E C9 84 C0 0F 84 ?? ?? ?? ??");
	//"84 DB 0F 84 ?? ?? ?? ?? 8B 8F ?? ?? ?? ?? 8B 01 8B 40 1C FF D0" <- pretty sure this pattern is wrong, but i'll save it down here just in case lol


	if (tickBaseShift > 0)
		Interfaces.pGlobalVars->choke = true;
	else if (tickBaseShift <= 0)
		Interfaces.pGlobalVars->choke = false;

	if (tickBaseShift <= 0 || (DWORD)_ReturnAddress() != WriteUsercmdDeltaToBufferReturn)
		return Hacks.oWriteUsercmdDeltaToBuffer(ecx, nSlot, buf, from, to, isNewCmd);
	if (from != -1)
		return true;

	int* pBackupCommands = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(buf) - 0x30);
	int* pNewCommands = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(buf) - 0x2C);

	DWORD ClientState = (DWORD)*(DWORD*)Interfaces.g_ClientStateTest; //this is aids i know sorry
	uintptr_t framePtr;
	__asm mov framePtr, ebp;

	if (ClientState)
	{
		INetChannel* NetChannel = *reinterpret_cast< INetChannel** >(ClientState + 0x9C);

		if (NetChannel)
		{
			if (!inSendMove)
			{
				if (*pNewCommands <= 0)
					return false;

				inSendMove = true;
				firstSendMovePack = true;
				tickBaseShift += *pNewCommands;

				while (tickBaseShift > 0)
				{
					Misc::CL_SendMove();
					NetChannel->Transmit(false);
					firstSendMovePack = false;
				}
				inSendMove = false;
				return false;
			}

			if (!firstSendMovePack)
			{
				int32_t loss = min(tickBaseShift, 10);

				tickBaseShift -= loss;
				NetChannel->m_nOutSequenceNr += loss;
			}

			int32_t next_cmdnr = *(int*)(ClientState + 0x4CAC) + *(int*)(ClientState + 0x4CB0) + 1;
			int32_t total_new_commands = min(tickBaseShift, 62);
			tickBaseShift -= total_new_commands;

			from = -1;
			*pNewCommands = total_new_commands;
			*pBackupCommands = 0;

			for (to = next_cmdnr - *pNewCommands + 1; to <= next_cmdnr; to++)
			{
				if (!Hacks.oWriteUsercmdDeltaToBuffer(ecx, nSlot, buf, from, to, true))
					return false;

				from = to;
			}

			CInput::CUserCmd *last_realCmd = (CInput::CUserCmd*)Interfaces.pInput->GetUserCmd(nSlot, from);
			CInput::CUserCmd fromCmd;

			if (last_realCmd)
				fromCmd = *last_realCmd;

			CInput::CUserCmd toCmd = fromCmd;
			toCmd.command_number++;
			toCmd.tick_count += 200;

			for (int i = *pNewCommands; i <= total_new_commands; i++)
			{
				Misc::WriteUsercmd(buf, &toCmd, &fromCmd);
				fromCmd = toCmd;
				toCmd.command_number++;
				toCmd.tick_count++;
			}
			return true;
		}
	}
}
*/

inline void clamp_angles(QAngle& angles)
{
	if (angles.x > 89.0f) angles.x = 89.0f;
	else if (angles.x < -89.0f) angles.x = -89.0f;

	if (angles.y > 180.0f) angles.y = 180.0f;
	else if (angles.y < -180.0f) angles.y = -180.0f;

	angles.z = 0;
}

template<class T, class U>
inline T clampangle(T in, U low, U high)
{
	if (in <= low)
		return low;
	else if (in >= high)
		return high;
	else
		return in;
}

static void AutoHop(CInput::CUserCmd* pCmd)
{
	if (Hacks.LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP || Hacks.LocalPlayer->GetMoveType() == MOVETYPE_LADDER) return;
	if (pCmd->buttons & IN_JUMP && !(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND)) {
		pCmd->buttons &= ~IN_JUMP;
	}
}



float GetTraceFractionWorldProps(Vector start, Vector end)
{
	Ray_t ray;
	CGameTrace tr;
	CTraceFilter filter;

	filter.pSkip = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	ray.Init(start, end);
	Interfaces.pTrace->TraceRay(ray, MASK_SOLID, &filter, &tr);

	return tr.fraction;
}

/*
float RightMovement;
bool IsActive;
float StrafeAngle;

void Strafe(CInput::CUserCmd* pCmd)
{
	CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	Vector Velocity = pLocal->GetVecVelocity();
	Velocity.z = 0;
	float Speed = Velocity.Length2D();
	if (Speed < 45) Speed = 45;

	float FinalPath = GetTraceFractionWorldProps(pLocal->GetAbsOrigin() + Vector(0, 0, 10), pLocal->GetAbsOrigin() + Vector(0, 0, 10) + Velocity / 2.0f);
	float DeltaAngle = RightMovement * fmax((275.0f / Speed) * (2.0f / FinalPath) * (128.0f / (1.7f / Interfaces.pGlobalVars->interval_per_tick)) * ClientVars.Misc.RetrackSpeed, 2.0f);
	StrafeAngle += DeltaAngle;

	if (fabs(StrafeAngle) >= 360.0f)
	{
		StrafeAngle = 0.0f;
		IsActive = false;
		RightMovement = 0;
	}
	else
	{
		pCmd->forwardmove = cos((StrafeAngle + 90 * RightMovement) * (M_PI / 180.0f)) * 450.f;
		pCmd->sidemove = sin((StrafeAngle + 90 * RightMovement) * (M_PI / 180.0f)) * 450.f;
	}
}
void Start(CInput::CUserCmd* pCmd)
{
	CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

	StrafeAngle = 0;
	IsActive = true;

	QAngle CurrentAngles;
	Interfaces.pEngine->GetViewAngles(CurrentAngles);
	CurrentAngles.x = 0;
	Vector Forward = CurrentAngles.Direction();
	Vector Right = Forward.Cross(Vector(0, 0, 1));
	Vector Left = Vector(Right.x * -1.0f, Right.y * -1.0f, Right.z);

	float LeftPath = GetTraceFractionWorldProps(pLocal->GetAbsOrigin() + Vector(0, 0, 10), pLocal->GetAbsOrigin() + Left * 450.f + Vector(0, 0, 10));
	float RightPath = GetTraceFractionWorldProps(pLocal->GetAbsOrigin() + Vector(0, 0, 10), pLocal->GetAbsOrigin() + Right * 450.f + Vector(0, 0, 10));
	if (LeftPath > RightPath)
		RightMovement = -1;
	else
		RightMovement = 1;
}
*/


static void AutoStrafer(CInput::CUserCmd* userCMD)
{
	if (Hacks.LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP || Hacks.LocalPlayer->GetMoveType() == MOVETYPE_LADDER || !Hacks.LocalPlayer->isAlive()) return;


	if ((!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND) || ClientVars.Misc.GroundStrafe)) {
		if (userCMD->mousedx >= 1 || userCMD->mousedx <= -1) {
			userCMD->sidemove = clampangle(userCMD->mousedx < 0.f ? -400.f : 400.f, -400, 400);
		}
		else {
			if (Hacks.LocalPlayer->GetVecVelocity().Length2D() == 0 || Hacks.LocalPlayer->GetVecVelocity().Length2D() == NAN || Hacks.LocalPlayer->GetVecVelocity().Length2D() == INFINITE)
			{
				userCMD->forwardmove = 400;
				return;
			}
			userCMD->forwardmove = clampangle(5850.f / Hacks.LocalPlayer->GetVecVelocity().Length2D(), -400, 400);
			if (userCMD->forwardmove < -400 || userCMD->forwardmove > 400)
				userCMD->forwardmove = 0;
			userCMD->sidemove = clampangle((userCMD->command_number % 2) == 0 ? -400.f : 400.f, -400, 400);
			if (userCMD->sidemove < -400 || userCMD->sidemove > 400)
				userCMD->sidemove = 0;
		}
	}
}

void doFakeWalk(CInput::CUserCmd* pCmd, bool& bSendPacket)
{
	CBaseEntity* pLocal = Hacks.LocalPlayer;
	if (pLocal->GetFlags() & FL_ONGROUND && ClientVars.AntiAim.Misc.fakewalk > 0 && GetAsyncKeyState(ClientVars.AntiAim.Misc.fakewalk))
	{
		static int iChoked = -1;
		iChoked++;

		if (iChoked < 1)
		{
			bSendPacket = false;

			pCmd->tick_count += 10;
			pCmd->command_number += 7 + pCmd->tick_count % 2 ? 0 : 1;

			pCmd->buttons |= pLocal->GetMoveType() == IN_BACK;
			pCmd->forwardmove = pCmd->sidemove = 0.f;
		}
		else
		{
			bSendPacket = true;
			iChoked = -1;

			Interfaces.pGlobalVars->frametime *= (pLocal->GetVecVelocity().Length2D()) / 1.f;
			pCmd->buttons |= pLocal->GetMoveType() == IN_FORWARD;
		}
	}
}

int SpaceXindex;

void SpaceX()
{
	DWORD ClientState = *(DWORD*)(Interfaces.g_ClientStateTest);
	if (ClientState)
	{
		INetChannel *netchan = (INetChannel*)*(DWORD*)(ClientState + 0x9C);
		if (netchan)
		{
			netchan->m_nOutSequenceNr += SpaceXindex ? 1 : 0;
			if (SpaceXindex > 1)
				SpaceXindex = 0;
			else
				SpaceXindex++;
		}
	}
}

void New_CreateMove(CInput* thisptr, void* _EAX, int sequence_number, float input_sample_frametime, bool active)
{
	CInput::CVerifiedUserCmd* VerifiedCmd;
	CreateMoveETC::GetCmds(sequence_number, Hacks.CurrentCmd, VerifiedCmd);
	Ragebot.DropTarget();

	Misc::ServerRankReveal();
	
	if (!Interfaces.pEngine->IsInGame())
		backtracking->ClearIncomingSequences();

	if (Hacks.CurrentCmd && VerifiedCmd && Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame() && Hacks.LocalPlayer)
	{
		MEMCHECK;
		Hacks.LocalWeapon = Hacks.LocalPlayer->GetActiveBaseCombatWeapon();
	
		if (ClientVars.Misc.Bhop)
			AutoHop(Hacks.CurrentCmd);
		if (ClientVars.Misc.Strafe)
			AutoStrafer(Hacks.CurrentCmd);

		/*
		if (ClientVars.Misc.CircleStrafe > 0 && GetAsyncKeyState(ClientVars.Misc.CircleStrafe)) {
			if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND)) 
				Hacks.CurrentCmd->buttons &= ~IN_JUMP;
			else
				Hacks.CurrentCmd->buttons |= IN_JUMP;
			Start(Hacks.CurrentCmd);
			Strafe(Hacks.CurrentCmd);
		}
		*/

		backtracking->legitBackTrack(Hacks.CurrentCmd, Hacks.LocalPlayer);

		doFakeWalk(Hacks.CurrentCmd, Hacks.SendPacket);
		
		Vector OrigAng = Hacks.CurrentCmd->viewangles;
		Misc::Normalize(OrigAng);

		Misc::AnimCT();

		if (Hacks.LocalWeapon)
		{
			if (Hacks.LocalPlayer->isAlive())
			{


				CreateMoveETC::pred::PredictionStart();
				


				if (ClientVars.Misc.fakelatency)
				{
					MEMCHECK;
					/*
					CClientState*** ClientState = reinterpret_cast<CClientState***>(getvfunc<uintptr_t>(Interfaces.pEngine, 12) + 0x10);;
					if (ClientState)
					{
						INetChannel* netchan = *reinterpret_cast< INetChannel** >((ClientState) + 0x9C);
						if (netchan)
						{
						*/
					DWORD ClientState = *(DWORD*)(Interfaces.g_ClientStateTest);
					if (ClientState)
					{
						INetChannel *netchan = (INetChannel*)*(DWORD*)(ClientState + 0x9C);
						if (netchan)
						{

							VMTNetChan.bInitialize(reinterpret_cast<DWORD**>(netchan));
							Hacks.oSendDatagram = reinterpret_cast<CHackManager::SendDatagramFn>(VMTNetChan.dwHookMethod(reinterpret_cast<DWORD>(&Hooks::hookedDatagram), 48));
						}
					}
				}

				//if (ClientVars.Misc.Lagexploit > 0 && GetAsyncKeyState(ClientVars.Misc.Lagexploit))
				//	tickBaseShift = TIME_TO_TICKS(ClientVars.Misc.lagamount); //u don't need the else statement for it to go back to 0 lol

				//static int delay = 0;
				//if (tickBaseShift <= 0) {
				//	if (ClientVars.Misc.InstaExplode && Hacks.CurrentCmd->buttons & IN_USE && Hacks.LocalPlayer->GetTeam() == 2) {
				//		tickBaseShift = TIME_TO_TICKS(75);
				//	}
				//	else if (ClientVars.Misc.InstaDefuse && Hacks.LocalPlayer->GetTeam() == 3 && Hacks.CurrentCmd->buttons & IN_USE) {
				//		tickBaseShift = TIME_TO_TICKS(30);
				//	}
				//}
				CreateMoveETC::pred::PredictionStart();


				if ( ClientVars.Misc.Knifebot )
					KnifeBot::Run();

				if (ClientVars.Misc.zeusbot)
					ZeusBot::Run();

				if (ClientVars.Misc.autoblock != 0)
					Misc::autoblock(Hacks.CurrentCmd);

				if (Hacks.LocalWeapon->HasAmmo())
				{
					Legitbot.Aim(Hacks.CurrentCmd);

					Ragebot.Aim(Hacks.CurrentCmd);

					Legitbot.Triggerbot(Hacks.CurrentCmd);

					if (Misc::Shooting() && LocalInfo.Choked < 13)
					{
						if (ClientVars.Ragebot.Enable && ClientVars.Ragebot.pSilent && !Hacks.LocalWeapon->IsMiscWeapon())
							Hacks.SendPacket = false;

						if (!ClientVars.Ragebot.pSilent && ClientVars.Ragebot.Enable)
							Interfaces.pEngine->SetViewAngles(Hacks.CurrentCmd->viewangles);

						if ((ClientVars.Ragebot.Enable && ClientVars.Ragebot.NoRecoil) || Legitbot.shouldControlRecoil())
							Hacks.CurrentCmd->viewangles -= Hacks.LocalPlayer->GetPunchAngle() * 2.f;

					}
					else if (((ClientVars.LegitBot.enable && ClientVars.LegitBot.Weapons.Pistol.enable && ClientVars.LegitBot.Weapons.Pistol.autopistol) || (ClientVars.Ragebot.AutoPistol)) && !Hacks.LocalWeapon->IsNonAutopistolWeapon())
						Hacks.CurrentCmd->buttons &= ~IN_ATTACK;

					if (*Hacks.LocalWeapon->GetItemDefinitionIndex() == weapon_revolver && ((ClientVars.Ragebot.Enable) || (ClientVars.LegitBot.enable && ClientVars.LegitBot.Weapons.Pistol.enable && ClientVars.LegitBot.Weapons.Pistol.autorevolver)))
					{
						if (Hacks.LocalWeapon->GetPostponeFireReadyTime() - Misc::GetServerTime() > 0.05)
							Hacks.CurrentCmd->buttons |= IN_ATTACK;
					}
				}
				FakeLag.Run(Hacks.CurrentCmd);
				if (ClientVars.Ragebot.Enable)
					AntiAim.Run(Hacks.CurrentCmd);
				else if(ClientVars.LegitBot.enable)
					AntiAimLegit.Run(Hacks.CurrentCmd);

			}
		}

		CreateMoveETC::CleanUp(OrigAng);
		LocalInfo.Choked = Hacks.SendPacket ? 0 : LocalInfo.Choked + 1;
		CreateMoveETC::VerifyCmd(VerifiedCmd);
	}
}

void __declspec(naked) __fastcall Hooked_Createmove(CInput* thisptr, void* _EAX, int sequence_number, float input_sample_frametime, bool active)
{
	Hacks.SendPacket = true;
	__asm
	{
		MOV Hacks.SendPacket, BL
		PUSH EBP
		MOV EBP, ESP
		SUB ESP, 8
		PUSHAD
		PUSH active
		PUSH input_sample_frametime
		PUSH sequence_number
		CALL Hacks.oCreateMove
	}
	Hacks.LocalPlayer = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	New_CreateMove(thisptr, _EAX, sequence_number, input_sample_frametime, active);
	__asm
	{
		POPAD
		MOV BL, Hacks.SendPacket
		MOV ESP, EBP
		POP EBP
		RETN 0x0C
	}
}

void __stdcall Hooked_OverrideView(CViewSetup* pSetup)
{
	if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected() && ClientVars.Visual.FOV > 0)
	{
		pSetup->fov = ClientVars.Visual.FOV;
		CHECKMEM;
	}
	Hacks.FOV = pSetup->fov;
	Hacks.oOverrideView(pSetup);
}

void __stdcall Hooked_PlaySound(const char* pSample)
{
	Hacks.oPlaySound(pSample);
	if (strstr(pSample, "inposition02.wav"))
	{
		if (!ClientVars.Misc.AutoAccept)
			return;
		Interfaces.pEngine->ClientCmd_Unrestricted("echo SOUND_FILE_FOUND", 0);
		static auto dwIsReady = (void(__cdecl*)(void))Utils.PFindPattern("client.dll", "55 8B EC 83 E4 F8 83 EC 08 56 8B 35 ?? ?? ?? ?? 57 83 BE");
		dwIsReady();
	}
}

void OnPlaySound(const Vector* pOrigin, const char* pszSoundName)
{
	//if (!pszSoundName || !Interfaces.pEngine->IsInGame())
		return;
}

int __stdcall Hook_EmitSound1(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample, float flVolume, soundlevel_t iSoundlevel, int nSeed, int iFlags, int iPitch, const Vector *pOrigin, const Vector *pDirection, CUtlVector< Vector >* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity)
{

	if (pSample)
		OnPlaySound(pOrigin, pSample);

	VMTSOUND.UnHook();

	int ret = Interfaces.pSound->EmitSound1(filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample,
		flVolume, iSoundlevel, nSeed, iFlags, iPitch,
		pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity);

	VMTSOUND.ReHook();

	return ret;
}

int __stdcall Hook_EmitSound2(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample, float flVolume, float flAttenuation, int nSeed, int iFlags, int iPitch, const Vector *pOrigin, const Vector *pDirection, CUtlVector< Vector >* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity)
{
	if (pSample)
		OnPlaySound(pOrigin, pSample);

	VMTSOUND.UnHook();

	int ret = Interfaces.pSound->EmitSound2(filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample,
		flVolume, flAttenuation, nSeed, iFlags, iPitch,
		pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity);

	VMTSOUND.ReHook();

	return ret;
}

HRESULT __stdcall hkEndScene(IDirect3DDevice9* thisptr)
{
	/*This is used because the game calls endscene twice each frame, one for ending the scene and one for finishing textures, this makes it just get called once*/
		static auto wanted_ret_address = _ReturnAddress();
		if (_ReturnAddress() == wanted_ret_address)
		{

			//backup render states
			DWORD colorwrite, srgbwrite;
			thisptr->GetRenderState(D3DRS_COLORWRITEENABLE, &colorwrite);
			thisptr->GetRenderState(D3DRS_SRGBWRITEENABLE, &srgbwrite);
			
			//fix drawing without calling engine functons/cl_showpos
			thisptr->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
			//removes the source engine color correction
			thisptr->SetRenderState(D3DRS_SRGBWRITEENABLE, false);

			auto& style = ImGui::GetStyle();

			VMTD3D.ReHook();

			if (!directinit) {
				GUI_Init(thisptr);
				style.Alpha = 0.f;
			}

			ImGui_ImplDX9_NewFrame();

			ImGui::GetIO().MouseDrawCursor = (GVars.MenuOpened && (style.Alpha > 0.01f));

			if (ClientVars.Visual.radrenable)
				DXM::DrawRadar();
			if (ClientVars.Visual.speclist)
				DXM::SpecList();

			if (GVars.MenuOpened && style.Alpha < 1.f) {
				style.Alpha += 0.01f;
			}
			if ((!GVars.MenuOpened) && style.Alpha > 0.f) {
				style.Alpha -= 0.01f;
			}

			if (GVars.MenuOpened || (style.Alpha > 0.01f)) {
				DXM::Menu();

			}

			ImGui::Render();

			//restore these
			thisptr->SetRenderState(D3DRS_COLORWRITEENABLE, colorwrite);
			thisptr->SetRenderState(D3DRS_SRGBWRITEENABLE, srgbwrite);

		}
	Hacks.oEndScene(thisptr);
	return 0;
}

HRESULT __stdcall hkReset(IDirect3DDevice9* thisptr, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	if (!directinit)
		Hacks.oReset(thisptr, pPresentationParameters);

	ImGui_ImplDX9_InvalidateDeviceObjects();

	Hacks.oReset(thisptr, pPresentationParameters);

	ImGui_ImplDX9_CreateDeviceObjects();
	
	return 0;
}

void GUI_Init(IDirect3DDevice9* thisptr)
{
	if (ImGui_ImplDX9_Init(INIT::Window, thisptr))
		directinit = true;
	{
		
		auto& style = ImGui::GetStyle();

		style.Colors[ImGuiCol_Text] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(7.0f, 7.0f, 7.0f, 0.65f);
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(1.f, 1.f, 1.f, 0.90f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.21f, 0.21f, 0.21f, 0.15f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.70f, 0.70f, 0.70f, 0.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.70f, 0.70f, 0.70f, 0.00f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.70f, 0.70f, 0.70f, 0.00f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.40f, 0.40f, 0.55f, 0.80f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(1.f, 1.f, 1.f, 0.10f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.7f, 0.7f, 0.7f, 0.30f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.7f, 0.7f, 0.7f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.20f, 0.20f, 0.20f, 0.80f);
		style.Colors[ImGuiCol_CheckMarkHover] = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
		style.Colors[ImGuiCol_CheckMarkBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.00f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.8f, 0.8f, 0.8f, 0.80f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.25f, 0.25f, 0.30f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.7f, 0.7f, 0.7f, 0.60f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 0.10f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.70f, 0.70f, 0.70f, 0.60f);
		style.Colors[ImGuiCol_Column] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.25f, 0.25f, 0.25f, 0.10f);
		style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
		style.Colors[ImGuiCol_CloseButton] = ImVec4(0.50f, 0.50f, 0.90f, 0.50f);
		style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.5f, 0.5f, 0.5f, 0.7f);
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);


		style.WindowTitleAlign.x = 0.50f;
		style.WindowTitleAlign.y = 0.90f;
		style.FrameBorderSize = 1.0f;
		style.WindowRounding = 0.f;
		style.FramePadding.y = 2.f;
		style.FrameRounding = 0.f;
		

		ImFontConfig config;
		ImGuiIO& io = ImGui::GetIO();

		config.PixelSnapH = true;
		config.OversampleH = 1;
		config.OversampleV = 1;
		config.GlyphExtraSpacing.x = 1.0f;
		fontskek.tahoma = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\Tahoma.ttf", 13.0f, &config, io.Fonts->GetGlyphRangesDefault());
		fontskek.impact = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\Tahoma.ttf", 16.0f, &config, io.Fonts->GetGlyphRangesDefault());
		static const ImWchar icon_ranges[] = { 0xE000, 0xF000, 0 };
		fontskek.icons = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\csgo_icons_outline.ttf", 22.0f, &config, icon_ranges);
	}
}

float wallAlpha;
float modelalpha;
float propAlpha;
float nightmode;
bool prepared;

void doAlphaMethods() {
	if (!prepared) {
		ConVar* r_drawspecificstaticprop = Interfaces.g_ICVars->FindVar("r_drawspecificstaticprop");
		SpoofedConvar* r_drawspecificstaticprop_s = new SpoofedConvar(r_drawspecificstaticprop);
		r_drawspecificstaticprop_s->SetInt(0);
		prepared = true;
	}

	if (ClientVars.Visual.wallalpha != wallAlpha) {
		for (MaterialHandle_t i = Interfaces.pMaterialSystem->FirstMaterial(); i != Interfaces.pMaterialSystem->InvalidMaterial(); i = Interfaces.pMaterialSystem->NextMaterial(i))
		{
			IMaterial *pMaterial = Interfaces.pMaterialSystem->GetMaterial(i);

			if (!pMaterial)
				continue;

			if (strstr(pMaterial->GetTextureGroupName(), "World textures"))
				pMaterial->AlphaModulate(ClientVars.Visual.wallalpha);
		}
		wallAlpha = ClientVars.Visual.wallalpha;
	}

	if (ClientVars.Visual.propalpha != propAlpha) {
		for (MaterialHandle_t i = Interfaces.pMaterialSystem->FirstMaterial(); i != Interfaces.pMaterialSystem->InvalidMaterial(); i = Interfaces.pMaterialSystem->NextMaterial(i))
		{
			IMaterial *pMaterial = Interfaces.pMaterialSystem->GetMaterial(i);

			if (!pMaterial)
				continue;

			if (strstr(pMaterial->GetTextureGroupName(), "StaticProp textures")) {
				pMaterial->AlphaModulate(ClientVars.Visual.propalpha);
			}
		}
		propAlpha = ClientVars.Visual.propalpha;
	}

	if (ClientVars.Visual.modelalpha != modelalpha) {
		for (MaterialHandle_t i = Interfaces.pMaterialSystem->FirstMaterial(); i != Interfaces.pMaterialSystem->InvalidMaterial(); i = Interfaces.pMaterialSystem->NextMaterial(i))
		{
			IMaterial *pMaterial = Interfaces.pMaterialSystem->GetMaterial(i);

			if (!pMaterial)
				continue;

			if (strstr(pMaterial->GetTextureGroupName(), "Model textures"))
				pMaterial->AlphaModulate(ClientVars.Visual.modelalpha);
		}
		modelalpha = ClientVars.Visual.modelalpha;
	}

	if (ClientVars.Visual.NightmodeVal != nightmode) {
		for (MaterialHandle_t i = Interfaces.pMaterialSystem->FirstMaterial(); i != Interfaces.pMaterialSystem->InvalidMaterial(); i = Interfaces.pMaterialSystem->NextMaterial(i))
		{
			IMaterial *pMaterial = Interfaces.pMaterialSystem->GetMaterial(i);

			if (!pMaterial)
				continue;
			
			if (strstr(pMaterial->GetTextureGroupName(), "StaticProp textures")
				|| strstr(pMaterial->GetTextureGroupName(), "World textures")
				|| strstr(pMaterial->GetTextureGroupName(), "SkyBox textures")) {

				if (ClientVars.Visual.NightmodeVal != 0.0f)
					pMaterial->ColorModulate(1.f - (ClientVars.Visual.NightmodeVal * 0.9f), 0.f, 1.f - (ClientVars.Visual.NightmodeVal * 0.6f));
			}
			else if (strstr(pMaterial->GetTextureGroupName(), "Model textures")) {
				if (ClientVars.Visual.NightmodeVal != 0.0f)
					pMaterial->ColorModulate(1.f - (ClientVars.Visual.NightmodeVal * 0.4f), 0.f, 1.f - (ClientVars.Visual.NightmodeVal * 0.1f));
			}
			if (ClientVars.Visual.NightmodeVal == 0.0f)
				pMaterial->ColorModulate(1.f, 1.f, 1.f);
		}
		nightmode = ClientVars.Visual.NightmodeVal;
	}
}


inline Vector angle_vector(Vector meme)
{
	auto sy = sin(meme.y / 180.f * static_cast<float>(PI));
	auto cy = cos(meme.y / 180.f * static_cast<float>(PI));

	auto sp = sin(meme.x / 180.f * static_cast<float>(PI));
	auto cp = cos(meme.x / 180.f* static_cast<float>(PI));

	return Vector(cp*cy, cp*sy, -sp);
}

void overrideResolver() {
	if(ClientVars.Ragebot.overrideresolver > 0 && GetAsyncKeyState(ClientVars.Ragebot.overrideresolver)){
		if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected()){
			CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
			if (pLocal)
			{
				if (Interfaces.pGlobalVars->rageTarget != nullptr)
				{
					CBaseEntity* target = Interfaces.pGlobalVars->rageTarget;
					if (target) {
						target->GetEyeAnglesPointer()->y = target->pelvisangs() +  ClientVars.Ragebot.overrideradd;
					}

				}
			}
		}
	}
}


bool wep1;


void __stdcall Hooked_Frame_Stage_Notify(ClientFrameStage_t curStage)
{
	Hacks.LocalPlayer = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	if (Hacks.LocalPlayer)
	{
		LocalInfo.PunchAns = *Hacks.LocalPlayer->GetPunchAnglePtr();
		LocalInfo.Flags = Hacks.LocalPlayer->GetFlags();
	}

	Vector*pPunchAngle = nullptr, *pViewPunchAngle = nullptr, vPunchAngle, vViewPunchAngle;

	if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
	{
		if (Hacks.LocalPlayer)
		{
			for (int i = 1; i <= Interfaces.pGlobalVars->maxClients; i++)
			{
				CBaseEntity* player = Interfaces.pEntList->GetClientEntity(i);

				if (!player)
					continue;

				if (player == Hacks.LocalPlayer)
					continue;

				*(int*)((uintptr_t)player + 0xA30) = Interfaces.pGlobalVars->framecount; //we'll skip occlusion checks now
				*(int*)((uintptr_t)player + 0xA28) = 0; //clear occlusion flags
			}

			Hacks.LocalWeapon = Hacks.LocalPlayer->GetActiveBaseCombatWeapon();
			if (curStage == FRAME_RENDER_START)
			{
				MEMCHECK;




				doAlphaMethods();
				if (ClientVars.Visual.NoVisRecoil)
				{
					pPunchAngle = Hacks.LocalPlayer->GetPunchAnglePtr();
					pViewPunchAngle = Hacks.LocalPlayer->GetViewPunchAnglePtr();

					if (pPunchAngle && pViewPunchAngle)
					{
						vPunchAngle = *pPunchAngle;
						pPunchAngle->Init();
						vViewPunchAngle = *pViewPunchAngle;
						pViewPunchAngle->Init();
					}
				}
				for (auto matName : smoke_materials)
				{
					IMaterial* mat = Interfaces.pMaterialSystem->FindMaterial(matName, "Other textures");
					mat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, ClientVars.Visual.NoSmoke);
				}

				if (ClientVars.Visual.NoSmoke) {
					static int* smokecount = *(int**)(Utils.PFindPattern("client.dll", "A3 ?? ?? ?? ?? 57 8B CB") + 0x1);
					*smokecount = 0;
				}

				IMaterial* Flash = Interfaces.pMaterialSystem->FindMaterial("effects\\flashbang", "ClientEffect textures");
				IMaterial* FlashWhite = Interfaces.pMaterialSystem->FindMaterial("effects\\flashbang_white", "ClientEffect textures");
				Flash->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, ClientVars.Visual.NoFlash);
				FlashWhite->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, ClientVars.Visual.NoFlash);


				QAngle tpAngle;

				if (ClientVars.Visual.ThirdpersonMode == 0)
					tpAngle = AntiAims::getRealAngle();
				else if (ClientVars.Visual.ThirdpersonMode == 1)
					tpAngle = AntiAims::getFakeAngle();
				else if (ClientVars.Visual.ThirdpersonMode == 2)
					tpAngle = AntiAims::getLowerBodyAngle();

				if (*reinterpret_cast<bool* >(reinterpret_cast<DWORD >(Interfaces.pInput) + 0xA5))
					*reinterpret_cast<QAngle* >(reinterpret_cast<DWORD >(Hacks.LocalPlayer) + 0x31C8) = tpAngle;
			}

			if (curStage == FRAME_NET_UPDATE_START)
			{

				/*
				if (tickBaseShift <= 0) {
					if (ClientVars.Misc.crimwalk > 0 && GetAsyncKeyState(ClientVars.Misc.crimwalk)) {
						SpaceX();
						if (wep1) {
							Hacks.CurrentCmd->buttons |= IN_WEAPON1;
							wep1 = false;
						}
						else {
							Hacks.CurrentCmd->buttons |= IN_WEAPON2;
							wep1 = true;
						}
						tickBaseShift = TIME_TO_TICKS(1);
					}
				}

				//if (Hacks.CurrentCmd->weaponselect != 0)
				//	tickBaseShift = TIME_TO_TICKS(1);
				*/



				if (ClientVars.Visual.BulletTracers) {
					for (unsigned int i = 0; i < BulletLogs.size(); i++) {
						auto shooter = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetPlayerForUserID(BulletLogs[i].m_iUserID));
						if (!shooter) return;

							DrawBeam(BulletLogs[i].m_vFirePosition, BulletLogs[i].m_vImpactPosition, CColor(ClientVars.Col.BulletTracers));

						BulletLogs.erase(BulletLogs.begin() + i);
					}
				}
			}
		}

		plist.Update();

		if (curStage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		{




			backtracking->UpdateIncomingSequences();

			if (ClientVars.Ragebot.Resolver > 0)
			{
				Resolver::Resolve();
			}

			if (ClientVars.Ragebot.ResolvePitch > 0)
			{
				Resolver::ResolvePitch();
			}


			overrideResolver();
			backtracking->Update(GetTickCount64());
		}
	}

	if (!Interfaces.pEngine->IsInGame() || !Interfaces.pEngine->IsConnected()) {
		wallAlpha = -1;
		modelalpha = -1;
		propAlpha = -1;
		prepared = false;
	}

	Hacks.oFrameStageNotify(curStage);

	if (pPunchAngle && pViewPunchAngle)
	{
		*pPunchAngle = vPunchAngle;
		*pViewPunchAngle = vViewPunchAngle;
	}
	
}

void InitKeyValues(KeyValues* keyValues, char* name)
{
	DWORD dwFunction = (DWORD)Utils.PatternSearch("client.dll", (PBYTE)"\x68\x00\x00\x00\x00\x8B\xC8\xE8\x00\x00\x00\x00\x89\x45\xFC\xEB\x07\xC7\x45\x00\x00\x00\x00\x00\x8B\x03\x56", "x????xxx????xxxxxxx?????xxx", NULL, NULL);
	dwFunction += 7;
	dwFunction = dwFunction + *reinterpret_cast< PDWORD_PTR >(dwFunction + 1) + 5;
	__asm
	{
		push name
		mov ecx, keyValues
		call dwFunction
	}
}

void LoadFromBuffer(KeyValues* pKeyValues, const char* resourceName, const char* pBuffer)
{
	DWORD dwFunction = Utils.PFindPattern("client.dll","55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04");
	using LoadFromBufferFn = void(__thiscall*)(void* thisptr, const char* resourceName, const char* pBuffer, void* pFileSystem, const char* pPathID, void* pfnEvaluateSymbolProc);
	LoadFromBufferFn LoadFromBufferEx;
	LoadFromBufferEx = (LoadFromBufferFn)(dwFunction);
	LoadFromBufferEx(pKeyValues, resourceName, pBuffer, nullptr, NULL, nullptr);

}

IMaterial* Create_Material(bool Ignore, bool Lit, bool Wireframe)
{
	static int created = 0;
	static const char tmp[] =
	{
		"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"vgui/white_additive\"\
		\n\t\"$envmap\" \"\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$flat\" \"1\"\
		\n\t\"$nocull\"  \"0\"\
		\n\t\"$selfillum\" \"1\"\
		\n\t\"$halflambert\" \"1\"\
		\n\t\"$nofog\"  \"0\"\
		\n\t\"$znearer\" \"0\"\
		\n\t\"$wireframe\" \"%i\"\
        \n}\n"
	};
	char* baseType = (Lit == true ? "VertexLitGeneric" : "UnlitGeneric");
	char material[512];
	char name[512];
	sprintf_s(material, sizeof(material), tmp, baseType, (Ignore) ? 1 : 0, (Wireframe) ? 1 : 0);
	sprintf_s(name, sizeof(name), "#Aimpulse_Chams_%i.vmt", created);
	++created;
	KeyValues* keyValues = static_cast< KeyValues* >(malloc(sizeof(KeyValues)));
	InitKeyValues(keyValues, baseType);
	LoadFromBuffer(keyValues, name, material);
	IMaterial* createdMaterial = Interfaces.pMaterialSystem->CreateMaterial(name, keyValues);
	createdMaterial->IncrementReferenceCount();
	return createdMaterial;
}

MDLHandle_t __fastcall FindMDL(void* thisptr, void* edx, char* path)
{
	return Hacks.oFindMDL(thisptr, edx, path);
}

bool Do_Chams(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld)
{

	CBaseEntity* Model_Entity = Interfaces.pEntList->GetClientEntity(pInfo.entity_index);
	const char* Model_Name = Interfaces.g_pModelInfo->GetModelName(const_cast<model_t*>(pInfo.pModel));

	if (Model_Entity){

		if (Model_Name && strstr(Model_Name, "models/player")){
			if (Model_Entity->isAlive() || Model_Entity->GetHealth() > 0){
				if (Model_Entity == Hacks.LocalPlayer)
					return false;

				IMaterial* Matierial;

				switch (ClientVars.Visual.Chams.Player_mat)
				{
				case 0:
					Matierial = Hacks.mat_Lit;
					break;
				case 1:
					Matierial = Hacks.mat_Flat;
					break;
				case 2:
					Matierial = Hacks.mat_Wire;
					break;
				case 3:
					Matierial = Hacks.mat_Glass;
					break;
				case 4:
					Matierial = Hacks.mat_Gold;
					break;
				case 5:
					Matierial = Hacks.mat_Plat;
					break;
				case 6:
					Matierial = Hacks.mat_Crystal;
					break;
				}
				if (Model_Entity == Hacks.LocalPlayer && Hacks.LocalPlayer->m_bIsScoped()){

					Interfaces.g_pRenderView->SetBlend(0.3f);
					Interfaces.g_pModelRender->ForcedMaterialOverride(nullptr);
					Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
					return true;
				}

				if (Model_Entity->GetTeam() == Hacks.LocalPlayer->GetTeam() && !ClientVars.Visual.Chams.Team)
					return false;

				if (ClientVars.Visual.Chams.Enabled)          
				{
					if (ClientVars.Visual.Chams.XQZ)
					{
						Matierial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
						float* colorHB = (ClientVars.Col.EnemyChamsXQZHB ? Model_Entity->flGetHealthColor(ClientVars.Col.EnemyChamsXQZ[3]) : ClientVars.Col.EnemyChamsXQZ);
						float* color = (Model_Entity->GetTeam() == Hacks.LocalPlayer->GetTeam() ? ClientVars.Col.TeamChams : colorHB);

						Interfaces.g_pRenderView->SetColorModulation(color);
						Interfaces.g_pRenderView->SetBlend(color[3]);
						Interfaces.g_pModelRender->ForcedMaterialOverride(Matierial);
						Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
					}
					Matierial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
					float* colorHB = (ClientVars.Col.EnemyChamsHB ? Model_Entity->flGetHealthColor(ClientVars.Col.EnemyChams[3]) : ClientVars.Col.EnemyChams);
					float* color = (Model_Entity->GetTeam() == Hacks.LocalPlayer->GetTeam() ? ClientVars.Col.TeamChams : colorHB);

					Interfaces.g_pRenderView->SetColorModulation(color);
					Interfaces.g_pRenderView->SetBlend(color[3]);
					Interfaces.g_pModelRender->ForcedMaterialOverride(Matierial);
					Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
					return true;
				}
			}
		}else if (Model_Name && strstr(Model_Name, "weapon")) {
			if (Model_Entity->isAlive() || Model_Entity->GetHealth() > 0) {
				if (ClientVars.Visual.weaponviewcham) {
					IMaterial* Matierial;

					switch (ClientVars.Visual.weaponmat)
					{
					case 0:
						Matierial = Hacks.mat_Lit;
						break;
					case 1:
						Matierial = Hacks.mat_Flat;
						break;
					case 2:
						Matierial = Hacks.mat_Wire;
						break;
					case 3:
						Matierial = Hacks.mat_Glass;
						break;
					case 4:
						Matierial = Hacks.mat_Gold;
						break;
					case 5:
						Matierial = Hacks.mat_Plat;
						break;
					case 6:
						Matierial = Hacks.mat_Crystal;
						break;
					}
					Interfaces.g_pRenderView->SetColorModulation(ClientVars.Col.WeaponViewCham);
					Interfaces.g_pRenderView->SetBlend(ClientVars.Col.WeaponViewCham[3]);
					Interfaces.g_pModelRender->ForcedMaterialOverride(Matierial);
					Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
					return true;
				}
			}
		}
	}else if (Model_Name && strstr(Model_Name, "arms")) {
		if (ClientVars.Visual.handcham) {
			IMaterial* Matierial;
			switch (ClientVars.Visual.handmat)
			{
			case 0:
				Matierial = Hacks.mat_Lit;
				break;
			case 1:
				Matierial = Hacks.mat_Flat;
				break;
			case 2:
				Matierial = Hacks.mat_Wire;
				break;
			case 3:
				Matierial = Hacks.mat_Glass;
				break;
			case 4:
				Matierial = Hacks.mat_Gold;
				break;
			case 5:
				Matierial = Hacks.mat_Plat;
				break;
			case 6:
				Matierial = Hacks.mat_Crystal;
				break;
			}

			Interfaces.g_pRenderView->SetColorModulation(ClientVars.Col.HandCham);
			Interfaces.g_pRenderView->SetBlend(ClientVars.Col.HandCham[3]);
			Interfaces.g_pModelRender->ForcedMaterialOverride(Matierial);
			Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
			return true;
		}
	}
	return false;
}

void __fastcall Hooked_SceneEnd(void* thisptr, void* edx) {
	Hacks.oSceneEnd(thisptr);

	if (GVars.unhooked)
		return;

	if (Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame())
	{
		if (ClientVars.Visual.GhostChams) {
			CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
			if (pLocal)
			{
				static IMaterial* mat;

				switch (ClientVars.Visual.Chams.GhostChamsMat)
				{
				case 0:
					mat = Hacks.mat_Lit;
					break;
				case 1:
					mat = Hacks.mat_Flat;
					break;
				case 2:
					mat = Hacks.mat_Wire;
					break;
				case 3:
					mat = Hacks.mat_Glass;
					break;
				case 4:
					mat = Hacks.mat_Gold;
					break;
				case 5:
					mat = Hacks.mat_Plat;
					break;
				case 6:
					mat = Hacks.mat_Crystal;
					break;
				}

				Vector Chamsang;

				if (ClientVars.Visual.GhostChamsMode == 0)
					Chamsang = AntiAims::getRealAngle();
				else if (ClientVars.Visual.GhostChamsMode == 1)
					Chamsang = AntiAims::getFakeAngle();
				else if (ClientVars.Visual.GhostChamsMode == 2)
					Chamsang = AntiAims::getLowerBodyAngle();


				if (mat)
				{
					Vector OrigAng;
					OrigAng = pLocal->GetEyeAngles();
					pLocal->SetAngle2(Vector(0, Chamsang.y, 0));
					Interfaces.g_pRenderView->SetColorModulation(ClientVars.Col.GhostChams);
					Interfaces.g_pModelRender->ForcedMaterialOverride(mat);
					pLocal->DrawModel(1, 255);
					Interfaces.g_pModelRender->ForcedMaterialOverride(nullptr);
					pLocal->SetAngle2(OrigAng);
				}
			}
		}
	}
}

void __fastcall Hooked_DrawModelExecute(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld)
{
	if (!Do_Chams(thisptr, edx, ctx, state, pInfo, pCustomBoneToWorld))
		Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

	Interfaces.g_pModelRender->ForcedMaterialOverride(nullptr, OVERRIDE_NORMAL);
}

void __stdcall Hooked_ClientCmdUnrestricted(const char* szCmdString, char flag)
{
	string str(szCmdString);
	std::string prefix;
	if (!str.compare(0, string("Clantag ").size(), "Clantag "))
	{
		str.replace(0, string("Clantag ").size(), "");
		prefix = string("\\n");
		std::size_t found = str.find(prefix);
		if (found != std::string::npos)
			str.replace(found, found + prefix.size(), "\n");
		Misc::SetClanTag(str.c_str(), "");
	}
	else if (!str.compare(0, string("ReleaseName").size(), "ReleaseName"))
	{
		Misc::setName("\n\xAD\xAD\xAD­­­");
	}
	else if (!str.compare(0, string("Name ").size(), "Name "))
	{
		str.replace(0, string("Name ").size(), "");
		prefix = string("\\n");
		std::size_t found = str.find(prefix);
		if (found != std::string::npos)
			str.replace(found, found + prefix.size(), "\n");
		Misc::setName(str.c_str());
	}
	
	else
		Hacks.oClientCmdUnresticted(szCmdString, flag);
}

extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall Hooked_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_LBUTTONDOWN:
		GVars.PressedKeys[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		GVars.PressedKeys[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		GVars.PressedKeys[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		GVars.PressedKeys[VK_RBUTTON] = false;
		break;
	case WM_MBUTTONDOWN:
		GVars.PressedKeys[VK_MBUTTON] = true;
		break;
	case WM_MBUTTONUP:
		GVars.PressedKeys[VK_MBUTTON] = false;
		break;
	case WM_XBUTTONDOWN:
	{
		UINT button = GET_XBUTTON_WPARAM(wParam);
		if (button == XBUTTON1)
		{
			GVars.PressedKeys[VK_XBUTTON1] = true;
		}
		else if (button == XBUTTON2)
		{
			GVars.PressedKeys[VK_XBUTTON2] = true;
		}
		break;
	}
	case WM_XBUTTONUP:
	{
		UINT button = GET_XBUTTON_WPARAM(wParam);
		if (button == XBUTTON1)
		{
			GVars.PressedKeys[VK_XBUTTON1] = false;
		}
		else if (button == XBUTTON2)
		{
			GVars.PressedKeys[VK_XBUTTON2] = false;
		}
		break;
	}
	case WM_KEYDOWN:
		GVars.PressedKeys[wParam] = true;
		break;
	case WM_KEYUP:
		GVars.PressedKeys[wParam] = false;
		break;
	default: break;
	}

	DXM::OpenMenu();
	if (directinit && GVars.MenuOpened && ImGui_ImplDX9_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(INIT::OldWindow, hWnd, uMsg, wParam, lParam);
}