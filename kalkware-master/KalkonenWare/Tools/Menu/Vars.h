#pragma once
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>
#include "../IMGUI/imgui.h"

struct MenuVars
{
	MenuVars()
	{ }

	struct Styles
	{
		struct Colors
		{
			float Menuborder[4] = { 1.f, 1.f , 1.f , 0.65f };
			float MenuBackground[4] = { 0.9f, 0.9f, 0.9f, 0.9f };
			float Border[4] = { 0.70f, 0.70f, 0.70f, 0.65f };
			float Controls[4] = { 1.f, 1.f, 1.f, 1.00f };
			float Text[4] = { 0.2f, 0.2f, 0.2f, 1.00f };
			float MainMenuButtons[4] = { 1.f, 1.f, 1.f, 1.00f };
			float GunMenuButtons[4] = { 1.f, 1.f, 1.f, 1.00f };
		}Colors;
		int ManualArrowRounding = 0;
		float espFadeIn = 1.f;
		float espFadeOut = 5.f;
	}Styles;
	struct Ragebot
	{
		struct Weapons
		{
			struct Pistol
			{
				struct Hitscan
				{
					int strength;

					bool head;
					bool neck;
					bool arms;
					bool chest;
					bool stomach;
					bool pelvis;
					bool legs;
					bool feet;
				}Hitscan;

				int MinDmg;
				int HitChance;
				float Headscale;
				float Bodyscale;
				int Hitbox;

				bool baimiflethal;



			}Pistol;

			struct Sniper
			{
				struct Hitscan
				{
					int strength;

					bool head;
					bool neck;
					bool arms;
					bool chest;
					bool stomach;
					bool pelvis;
					bool legs;
					bool feet;
				}Hitscan;

				int MinDmg;
				int HitChance;
				float Headscale;
				float Bodyscale;
				int Hitbox;

				bool baimiflethal;



			}Sniper;

			struct AutoSniper
			{
				struct Hitscan
				{
					int strength;

					bool head;
					bool neck;
					bool arms;
					bool chest;
					bool stomach;
					bool pelvis;
					bool legs;
					bool feet;
				}Hitscan;

				int MinDmg;
				int HitChance;
				float Headscale;
				float Bodyscale;
				int Hitbox;

				bool baimiflethal;



			}AutoSniper;

			struct Rifle
			{
				struct Hitscan
				{
					int strength;

					bool head;
					bool neck;
					bool arms;
					bool chest;
					bool stomach;
					bool pelvis;
					bool legs;
					bool feet;
				}Hitscan;

				int MinDmg;
				int HitChance;
				float Headscale;
				float Bodyscale;
				int Hitbox;

				bool baimiflethal;



			}Rifle;

			struct SMG
			{
				struct Hitscan
				{
					int strength;

					bool head;
					bool neck;
					bool arms;
					bool chest;
					bool stomach;
					bool pelvis;
					bool legs;
					bool feet;
				}Hitscan;

				int MinDmg;
				int HitChance;
				float Headscale;
				float Bodyscale;
				int Hitbox;

				bool baimiflethal;
			}SMG;

			struct Shotgun
			{
				struct Hitscan
				{
					int strength;

					bool head;
					bool neck;
					bool arms;
					bool chest;
					bool stomach;
					bool pelvis;
					bool legs;
					bool feet;
				}Hitscan;

				int MinDmg;
				int HitChance;
				float Headscale;
				float Bodyscale;
				int Hitbox;

				bool baimiflethal;

			}Shotgun;
		}Weapons;

		bool Enable;
		float FOV = 180.f;
		bool pSilent;
		bool Autowall;
		bool AutoPistol;
		int AimbotSelection;

		int Resolver;
		int ResolvePitch;

		bool autofire;
		bool autoscope;

		bool on;
		bool NoRecoil;
		bool BackTrack;
		int overrideresolver;
		int overrideradd;
	}Ragebot;

	struct AntiAim
	{
		bool enabled;
				
		bool OnGreandes;
		bool OnLadders;
		bool OnKnife;

		bool SwapShots;
		int type;
		struct StandAA
		{
			int Pitch;
			int PitchAdd;
			int Yaw;
			int YawAdd;
			int Fake;
			int FakeAdd;
		}Stand;

		struct MoveAA
		{
			int Pitch;
			int PitchAdd;
			int Yaw;
			int YawAdd;
			int Fake;
			int FakeAdd;
		}Move;

		struct AirAA
		{
			int Pitch;
			int PitchAdd;
			int Yaw;
			int YawAdd;
			int Fake;
			int FakeAdd;
		}Air;


		struct Misc
		{
			int lbyDelta = 75;
			int leftAA;
			int rightAA;
			int downAA;
			//int upAA;
			float SpinbotSpeed = 5;
			float JitterSpeed = 5;
			int JitterRange = 90;
			float SwitchSpeed = 5;
			int SwitchAdd = 90;
			int fakewalk;
		}Misc;

	}AntiAim;

	struct FakeLag
	{
		int Choke;
		int ChokeMode;

		bool WhileShooting;
		bool Onground;
		bool WhileStill;

	}FakeLag;


	struct LegitBot{
		struct AntiAim
		{
			bool enabled;

			bool OnGreandes;
			bool OnLadders;
			bool OnKnife;

			struct StandAA
			{
				int Yaw;
				int YawAdd;
			}Stand;

			struct MoveAA
			{
				int Yaw;
				int YawAdd;
			}Move;

			struct AirAA
			{
				int Yaw;
				int YawAdd;
			}Air;

			struct Misc
			{
				int lbyDelta = 75;
				int leftAA;
				int rightAA;
				int downAA;
				//int upAA;
				float SpinbotSpeed = 5;
				float JitterSpeed = 5;
				int JitterRange = 90;
				float SwitchSpeed = 5;
				int SwitchAdd = 90;
			}Misc;
		}AntiAim;

		struct Weapons
		{
			struct Pistol
			{
				struct Triggerbot
				{
					bool enable;
					bool onkey;
					int key;
					int hitbox;
					int delay;
					int hitchance;
				}Triggerbot;
				bool enable;
				bool onkey;
				float fov;
				float smoothing;
				int key;
				int hitbox;
				bool recoilcontrol;
				bool autowall;
				bool autopistol;
				bool autorevolver;
			}Pistol;

			struct Sniper
			{
				struct Triggerbot
				{
					bool enable;
					bool onkey;
					int key;
					int hitbox;
					int delay;
					int hitchance;
				}Triggerbot;
				bool enable;
				bool onkey;
				float fov;
				float smoothing;
				int key;
				int hitbox;
				bool recoilcontrol;
				bool autowall;
				bool awpbaim;
			}Sniper;

			struct AutoSniper
			{
				struct Triggerbot
				{
					bool enable;
					bool onkey;
					int key;
					int hitbox;
					int delay;
					int hitchance;
				}Triggerbot;
				bool enable;
				bool onkey;
				float fov;
				float smoothing;
				int key;
				int hitbox;
				bool recoilcontrol;
				bool autowall;
			}AutoSniper;

			struct Rifle
			{
				struct Triggerbot
				{
					bool enable;
					bool onkey;
					int key;
					int hitbox;
					int delay;
					int hitchance;
				}Triggerbot;
				bool enable;
				bool onkey;
				float fov;
				float smoothing;
				int key;
				int hitbox;
				bool recoilcontrol;
				bool autowall;
			}Rifle;

			struct SMG
			{
				struct Triggerbot
				{
					bool enable;
					bool onkey;
					int key;
					int hitbox;
					int delay;
					int hitchance;
				}Triggerbot;
				bool enable;
				bool onkey;
				float fov;
				float smoothing;
				int key;
				int hitbox;
				bool recoilcontrol;
				bool autowall;
			}SMG;

			struct Shotgun
			{
				struct Triggerbot
				{
					bool enable;
					bool onkey;
					int key;
					int hitbox;
					int delay;
					int hitchance;
				}Triggerbot;
				bool enable;
				bool onkey;
				float fov;
				float smoothing;
				int key;
				int hitbox;
				bool recoilcontrol;
				bool autowall;
			}Shotgun;
		}Weapons;

		bool enable;
		bool backtrack;
		int AimbotSelection;
	}LegitBot;

	struct Visuals
	{
		bool BoundingBox;
		int Box;
		bool Showteam;
		bool Health;
		bool Ammo;
		bool BulletTracers;
		bool Armor;
		bool Money;
		bool Name;
		bool Callout;
		bool Weapon;
		int wpnmode;
		bool Vulnerabilities;
		bool AimLine;
		bool Skeleton;

		bool AngleLines;

		bool Arrows;

		bool SpreadCircle;
		bool Hitmarker;

		bool Droppedguns;
		bool Grenades;
		bool Crosshair;
		bool InaccuracyCrosshair;

		bool Bomb;
		bool NadePred;
		bool soundesp;

		bool speclist;

		struct Chams
		{
			bool Enabled;
			int Player_mat;
			bool Team;
			bool Player_weapon;
			int GhostChamsMat;
			bool XQZ;
		}Chams;

		bool handcham;
		bool weaponviewcham;
		int weaponmat;
		int handmat;

		bool NoVisRecoil;
		bool NoFlash;
		bool NoSmoke;
		bool LBYIndicator;
		int Thirdperson;
		int ThirdpersonMode;
		int tpdist = 150;
		int tpkey;
		bool NoScope;
		bool DrawScope;
		int FOV;
		bool engineradar;
		bool DLight;
		bool DLightteam;
		bool ELight;


		bool ShowTarget;


		struct Glow
		{
			bool GlowEnemy;
			bool GlowTeam;

			bool WeaponGlow;

			bool BombGlow;

			bool GrenadeGlow;
		}Glow;
		

		bool radrenable;
		bool enemyonlyradr;
		bool visibleonlyradr;
		bool smokecheckradr;
		int radrsize = 200;
		int radralpha = 100;
		float radrzoom = 200;
		int radrtype = 3;
		bool ResolverESP;
		bool GhostChams;
		int GhostChamsMode;
		float wallalpha = 1.f;
		float propalpha = 1.f;
		float modelalpha = 1.f;


		float NightmodeVal = 0.f;

		bool ManualArrows;
		bool LBYPredictor;

	}Visual;

	struct Misc
	{
		bool faresp;
		bool Enabled;
		bool Bhop;
		bool RankReveal;
		bool Strafe;
		int slomokey;
		bool slomo;
		int Strafetype;

		int CircleStrafe;

		int CStrafeKey;

		bool zStrafe;
		int Crashmode;
		int FakeLagAmt;
		bool inairfl;
		int FakeLagType;
		bool AutoAccept;
		bool Clantag;
		int ClanType;
		bool AnimClantag;
		bool AnimName;
		bool largespam;
		bool Knifebot;
		bool walkbot;
		int walkbotdist;
		int walkbotturn;
		int autoblock;
		bool zeusbot;

		int Lagexploit;
		float lagamount;

		bool fakelatency;
		int desiredlatency;

		bool Antiuntrusted = true;
		bool Antiuntrustedproxy = true;

		bool InstaSwap;
		bool InstaExplode;
		bool InstaDefuse;
		int crimwalk;
		int spacex;
		int spacexamt;
		int kalkwalkamount;
		int aimstep;
		int instaexplodeamount;
		float RetrackSpeed = 4.4;
		bool GroundStrafe;


	}Misc;

	struct Colors
	{
		float TeamESP[4] = { 0, 1.f, 0, 1.f };
		float EnemyESP[4] = { 1.f, 0.f, 0.f , 1.f };
		float NameESP[4] = { 1.f, 1.f, 1.f , 1.f };
		float WeaponESP[4] = { 1.f, 1.f, 1.f , 1.f };
		float ArmorESP[4] = { 1.f, 1.f , 1.f , 1.f };
		float ResolverESP[4] = { 1.f, 0.f , 1.f , 1.f };
		float BulletTracers[4] = { 0.f, 1.f , 1.f , 1.f };
		float Callout[4] = { 0.f, 1.f , 1.f , 1.f };
		float Health[4] = { 1.f, 1.f , 1.f , 1.f };
		float Money[4] = { 0.f, 1.f , 0.f , 1.f };

		float ShowTarget[4] = { 1.f, 0.f, 0.f, 1.f };

		float Vulnerabilities[4] = { 1.f, 1.f , 0.f , 1.f };
		float AngleLinesLBY[4] = { 1.f, 1.f , 0.f , 1.f };
		float AngleLinesREAL[4] = { 0.f, 1.f , 0.f , 1.f };
		float AngleLinesFAKE[4] = { 1.f, 0.f , 0.f , 1.f };
		float DroppedWeapons[4] = { 1.f, 1.f, 1.f , 1.f };

		bool EnemyESPHB = false;

		float Aimlines[4] = { 1.f, 0.f, 1.f , 1.f };
		bool EnemyAimlineHB = false;

		float Skeleton[4] = { 1.f, 1.f, 1.f , 1.f };
		bool EnemySkeletonHB = false;

		float Ammo[4] = { 1.f, 1.f, 1.f , 1.f };
		float Hitmarker[4] = { 1.f, 1.f, 1.f , 1.f };

		float Arrows[4] = { 1.f, 1.f, 1.f , 1.f };

		float Crosshair[4] = { 1.f, 1.f, 1.f, 1.f };
		float InaccuracyCrosshair[4] = {1.f, 1.f, 1.f, 1.f };

		float TeamDLights[4] = { 0, 1.f, 0 , 1.f };
		float EnemyDLights[4] = { 1.f, 0, 0 , 1.f };

		float EnemyGlow[4] = { 1.f, 1.f, 1.f, 1.f };
		bool EnemyGlowHB = false;

		float TeamGlow[4] = { 1.f, 1.f, 1.f, 1.f };
		float WeaponGlow[4] = { 1.f, 1.f, 1.f, 1.f  };
		float BombGlow[4] = { 1.f, 1.f, 1.f, 1.f };
		float GrenadeGlow[4] = { 1.f, 1.f, 1.f, 1.f  };

		float EnemyChams[4] = { 1.f, 1.f, 1.f, 1.f };
		bool EnemyChamsHB = false;

		float EnemyChamsXQZ[4] = { 1.f, 0, 0, 1.f };
		bool EnemyChamsXQZHB = false;

		float TeamChams[4] = { 0.f, 1.f, 0.f, 1.f };

		float WeaponCham[4] = { 1.f, 1.f, 1.f , 1.f };
		float HandCham[4] = { 1.f, 1.f, 1.f , 1.f };
		float WeaponViewCham[4] = { 1.f, 1.f, 1.f, 1.f };
		float GhostChams[4] = { 1.f, 1.f, 1.f, 1.f };

		float LbyPredictor[4] = { 1.f, 0.f, 1.f, 1.f };

		float ManualArrowsActive[4] = { 0.f, 1.f, 0.f, 1.f };
		float ManualArrowsNotActive[4] = { 1.f, 0.f, 0.f, 1.f };
	}Col;


};
extern MenuVars ClientVars;

struct resolverInfo {
	resolverInfo()
	{ }
	struct Information {
		float lby;
		float simTime;
		bool isLegit;
	};
	std::string reason[255];
	Information oldPlayers[255][64];	//Oldest
	Information players[255][64];		//Old
	Information currentInfo[255][64];	//Newest

	float lbyData[255];
	float savedLBY[64];
	int missedShots;
};
extern resolverInfo ResolverInfo;

struct playerInfo {
	playerInfo()
	{ }
	struct Information {
		Vector lastPos;
		int lastWep;
		long time = 0;
		bool valid;
	};
	int latestByMessage = -1;
	Information players[512][128];
};
extern playerInfo PlayerInfo;


struct GlobalVariables
{
	GlobalVariables()
	{ }

	bool PressedKeys[256] = {};
	float hitmarkeralpha;
	bool MenuOpened = false;
	bool UTchecked = false;
	bool unhooked = false;
};

extern GlobalVariables GVars;