#include "stdafx.h"
#include "Tools/Hacks/Misc.h"

bool Unhook_Cheat = false;

auto ExitCheat() -> bool;

void Unhook()
{
	Unhook_Cheat = true;
}

bool ExitCheat()
{
	if( !Unhook_Cheat )
		return false;

	GVars.unhooked = true;


	Interfaces.pEngine->ClientCmd_Unrestricted( "clear", 0 );
	Interfaces.pEngine->ClientCmd_Unrestricted( "echo KalkonenWare has been successfully unhooked!", 0 );

	Interfaces.pEngine->ClientCmd_Unrestricted( "cl_mouseenable 1", 0 );
	Sleep( 100 );
	Interfaces.pEngine->ClientCmd_Unrestricted( "crosshair 1", 0 );
	Sleep( 100 );
	Interfaces.pEngine->ClientCmd_Unrestricted( "firstperson", 0 );
	Sleep( 100 );
	Interfaces.pEngine->ClientCmd_Unrestricted( "cl_drawhud 1", 0 );
	Sleep( 100 );

	if( Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected() )
	{
		Misc::SetClanTag( "", Hacks.LocalPlayer->GetName().c_str() );
		Sleep( 100 );
	}

	Hacks.UnHook();
	Sleep( 200 );

	SetWindowLongPtr( INIT::Window, GWL_WNDPROC, reinterpret_cast< LONG_PTR >( INIT::OldWindow ) );
	Sleep( 200 );

	GVars.MenuOpened = false;
	FreeLibraryAndExitThread( INIT::Dll, 0 );
}


DWORD WINAPI CheatMain(LPVOID lpThreadParameter)
{
	Interfaces.InitialiseSDK();
	
	CNetvarManager::Instance()->CreateDatabase();
	//CNetvarManager::Instance()->Dump("C:\\dab\\netvars.txt");
	
	Hacks.CallHooks();

	Interfaces.pEngine->ClientCmd_Unrestricted( "echo KalkonenWare loaded successfully!", 0 );
		
	while( !Unhook_Cheat )
	{
		Misc::ServerRankReveal();
		Sleep( 15 );
	}
	ExitCheat();
	return 0;
}
