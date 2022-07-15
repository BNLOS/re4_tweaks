#include <iostream>
#include "dllmain.h"
#include "Patches.h"
#include "Game.h"
#include "Settings.h"

bool bIsUltrawide;
bool bIs16by10;

float fDefaultEngineWidthScale = 1280.0f;
float fDefaultEngineAspectRatio = 1.777777791f;
float fDefaultAspectRatio = 1.333333373f;
float fDefaultEsp18Height = 0.375f;
float fDefaultHudPosX = 217.0f;

float fGameWidth;
float fGameHeight;
float fGameDisplayAspectRatio;

static uint32_t* ptrEngineWidthScale;
static uint32_t* ptrEngineTextWidthScale;
static uint32_t* ptrAspectRatio;
static uint32_t* ptrEsp18Height;

void __cdecl C_MTXOrtho_messageTrans_hook(Mtx44 mtx, float PosY, float NegY, float NegX, float PosX, float unk1, float unk2)
{
	// I think this should be 1.777777791f, but 1.666667f looks better for some reason?
	float fNewAspectRatio = (fGameDisplayAspectRatio / 1.666667f);

	float fUIPosOffset = (((480.0f * fNewAspectRatio) - 512.0f) / 2.0f);

	PosX += fUIPosOffset;
	NegX -= fUIPosOffset;

	return game_C_MTXOrtho(mtx, PosY, NegY, NegX, PosX, unk1, unk2);
}

void __cdecl C_MTXOrtho_sub_1484C50_hook(Mtx44 mtx, float PosY, float NegY, float NegX, float PosX, float unk1, float unk2)
{
	float fUIPosOffset = (fGameWidth - fGameHeight * (16.0f / 9.0f)) / 2.0f;

	PosX += fUIPosOffset;
	NegX -= fUIPosOffset;

	return game_C_MTXOrtho(mtx, PosY, NegY, NegX, PosX, unk1, unk2);
}

void __cdecl C_MTXOrtho_DrawTexture_hook(Mtx44 mtx, float PosY, float NegY, float NegX, float PosX, float unk1, float unk2)
{
	// Game's default behavior is stretching, so we simply return
	if (pConfig->bStretchFullscreenImages)
		return game_C_MTXOrtho(mtx, PosY, NegY, NegX, PosX, unk1, unk2);

	float fNewAspectRatio = (fGameDisplayAspectRatio / 1.6666f);

	float fUIPosOffset = (((480.0f * fNewAspectRatio) - 512.0f) / 2.0f);

	PosX += fUIPosOffset;
	NegX -= fUIPosOffset;

	return game_C_MTXOrtho(mtx, PosY, NegY, NegX, PosX, unk1, unk2);
}

void __cdecl C_MTXOrtho_cSofdec_hook(Mtx44 mtx, float PosY, float NegY, float NegX, float PosX, float unk1, float unk2)
{
	// Game's default behavior is stretching, so we simply return
	if (pConfig->bStretchVideos)
		return game_C_MTXOrtho(mtx, PosY, NegY, NegX, PosX, unk1, unk2);

	float fNewAspectRatio = (fGameDisplayAspectRatio / 1.6666f);

	float fUIPosOffset = (((480.0f * fNewAspectRatio) - 512.0f) / 2.0f);

	PosX += fUIPosOffset;
	NegX -= fUIPosOffset;

	return game_C_MTXOrtho(mtx, PosY, NegY, NegX, PosX, unk1, unk2);
}

void Init_AspectRatioTweaks()
{
	// Get original C_MTXOrtho
	auto pattern = hook::pattern("E8 ? ? ? ? 8D 4D BC 6A 01 51 E8 ? ? ? ? 8D 55 98 52 8D 45 B0 50 8D 4D A4 51 56 E8 ? ? ? ? 8B 4D FC 83 C4 34");
	ReadCall(injector::GetBranchDestination(pattern.count(1).get(0).get<uint32_t>(0)).as_int(), game_C_MTXOrtho);

	// messageTrans_messageCamera -> Used in most (all?) text drawn in the user interface
	pattern = hook::pattern("E8 ? ? ? ? 8D 4D ? 6A ? 51 E8 ? ? ? ? 8D 55 ? 52 E8 ? ? ? ? 8D 45 ? 6A ? 50 E8 ? ? ? ? 6A ? E8 ? ? ? ? 8B 4D");
	InjectHook(pattern.count(2).get(1).get<uint32_t>(0), C_MTXOrtho_messageTrans_hook);

	// sub_1146150 -> Only used the scale the mouse cursor area, afaik. Same logic as before, so lets just reuse that func
	InjectHook(pattern.count(2).get(0).get<uint32_t>(0), C_MTXOrtho_messageTrans_hook);

	// sub_1484C50 -> Used to scale some textures that are drawn in the user interface (main menu only?)
	pattern = hook::pattern("E8 ? ? ? ? 8D 4D ? 6A ? 51 E8 ? ? ? ? 8D 55 ? 52 8D 45 ? 50 8D 4D ? 51 56 E8 ? ? ? ? 8B 4D ? 83 C4");
	InjectHook(pattern.count(1).get(0).get<uint32_t>(0), C_MTXOrtho_sub_1484C50_hook);

	// DrawTexture -> Used for fullscreen images, such as those that show up when you're reading Files
	pattern = hook::pattern("E8 ? ? ? ? 8D 4D ? 6A ? 51 E8 ? ? ? ? 8D 95 ? ? ? ? 52");
	InjectHook(pattern.count(1).get(0).get<uint32_t>(0), C_MTXOrtho_DrawTexture_hook);
	
	// cSofdec::setCamera -> Used for Sofdec videos
	pattern = hook::pattern("E8 ? ? ? ? 8D 4D ? 6A ? 51 E8 ? ? ? ? 8D 55 ? 52 8D 45 ? 50 8D 4D ? 51 56 E8 ? ? ? ? 8B 4D ? 33 CD");
	InjectHook(pattern.count(1).get(0).get<uint32_t>(0), C_MTXOrtho_cSofdec_hook);

	// Hook LifeMeter::roomInit so we can override the initial HUD pos
	pattern = hook::pattern("8B 48 ? 8B 51 ? 6A ? 6A ? 03 D1 68 ? ? ? ? 52 B9 ? ? ? ? E8 ? ? ? ? 6A");
	struct LMroomInit_Hook
	{
		void operator()(injector::reg_pack& regs)
		{
			regs.ecx = *(uint32_t*)(regs.eax + 0x48);
			regs.edx = *(uint32_t*)(regs.ecx + 0x7C);

			if ((pConfig->bUltraWideAspectSupport && bIsUltrawide && pConfig->bSideAlignHUD) ||
				(pConfig->bRemove16by10BlackBars && bIs16by10))
			{
				// I honestly don't understand this pointer and/or the data structure it points to
				float* fInitialHudPosX = (float*)(regs.ecx + regs.edx + 0x1C);

				float fHudPosOffset = 0.25f * (fGameWidth - (fDefaultEngineAspectRatio * fGameHeight));

				*fInitialHudPosX = fDefaultHudPosX + fHudPosOffset;

				#ifdef VERBOSE
				con.AddConcatLog("fInitialHudPosX: ", *fInitialHudPosX);
				#endif
			}
		}
	}; injector::MakeInline<LMroomInit_Hook>(pattern.count(1).get(0).get<uint32_t>(0), pattern.count(1).get(0).get<uint32_t>(6));

	// Hook function that sets the BG color (bio4_AddBgColor), so we can make sure it is black when playing videos
	pattern = hook::pattern("F6 82 ? ? ? ? ? 75 ? B9 ? ? ? ? E8 ? ? ? ? 8B 48");
	struct AddBgColor_hook
	{
		void operator()(injector::reg_pack& regs)
		{
			// Game was originally checking for this flag
			bool origFlagSet = FlagIsSet(GlobalPtr()->flags_STATUS_501C, uint32_t(Flags_STATUS::STA_SET_BG_COLOR));

			bool isPlayingSofdec = (FlagIsSet(GlobalPtr()->flags_STATUS_501C, uint32_t(Flags_STATUS::STA_MOVIE_ON)) ||
				FlagIsSet(GlobalPtr()->flags_STATUS_501C, uint32_t(Flags_STATUS::STA_MOVIE2_ON)));

			if ((origFlagSet || isPlayingSofdec))
				regs.ef &= ~(1 << regs.zero_flag);
			else
				regs.ef |= (1 << regs.zero_flag);
		}
	}; injector::MakeInline<AddBgColor_hook>(pattern.count(1).get(0).get<uint32_t>(0), pattern.count(1).get(0).get<uint32_t>(7));

	pattern = hook::pattern("DC 0D ? ? ? ? DE F9 D9 5D F8 8B 10 8B 92 ? ? ? ? FF D2 EB 22 8B 0D ? ? ? ? 8D 70 04");
	ptrEngineWidthScale = *pattern.count(1).get(0).get<uint32_t*>(2);

	pattern = hook::pattern("D9 05 ? ? ? ? D9 5C 24 04 D9 80 ? ? ? ? D9 1C 24 E8 ? ? ? ? 8B CE E8 ? ? ? ? 8B 46 04");
	ptrAspectRatio = *pattern.count(1).get(0).get<uint32_t*>(2);

	pattern = hook::pattern("DC 0D ? ? ? ? D9 9D ? ? ? ? D9 85 ? ? ? ? D9 5C 24 ? D9 5C 24");
	ptrEsp18Height = *pattern.count(1).get(0).get<uint32_t*>(2);

	// Hook D3D_SetupPresentationGlobals so we can calculate and write the new aspect ratio values
	pattern = hook::pattern("A3 ? ? ? ? 89 0D ? ? ? ? 5E 5B 8B E5 5D C3");
	static uintptr_t* ptrResMovAddr = *pattern.count(1).get(0).get<uint32_t*>(1);
	struct ResChange
	{
		void operator()(injector::reg_pack& regs)
		{
			spd::log()->info("Changing game resolution to: {0}x{1} {2}Hz", (int)regs.eax, (int)regs.ecx, (int)regs.esi);

			#ifdef VERBOSE
			con.AddConcatLog("ResX = ", (int)regs.eax);
			con.AddConcatLog("ResY = ", (int)regs.ecx);
			con.AddConcatLog("Refrash rate = ", (int)regs.esi);
			#endif

			fGameWidth = (float)regs.eax;
			fGameHeight = (float)regs.ecx;
			fGameDisplayAspectRatio = fGameWidth / fGameHeight;

			bIsUltrawide = fGameDisplayAspectRatio > 2.2f;
			bIs16by10 = fGameDisplayAspectRatio == 1.6f;

			float fNewEngineAspectRatio = fGameDisplayAspectRatio / fDefaultEngineAspectRatio;
			float fNewAspectRatio = fGameDisplayAspectRatio / fDefaultAspectRatio;
			float fNewEngineWidthScale = fNewEngineAspectRatio * fDefaultEngineWidthScale;

			// Fix Esp18 height
			double fNewEsp18Height = 0.50068 / fNewAspectRatio;

			con.AddLogFloat(fGameDisplayAspectRatio);

			// if ultrawide/super ultrawide or 16:10
			if ((bIsUltrawide && pConfig->bUltraWideAspectSupport) ||
				(bIs16by10 && pConfig->bRemove16by10BlackBars))
			{
				#ifdef VERBOSE
				con.AddConcatLog("fNewEngineWidthScale = ", fNewEngineWidthScale);
				con.AddConcatLog("fNewAspectRatio = ", fNewAspectRatio);
				con.AddConcatLog("fNewEsp18Height = ", fNewEsp18Height);
				#endif

				injector::WriteMemory(ptrEsp18Height, static_cast<double>(-fNewEsp18Height), true);
				injector::WriteMemory(ptrEngineWidthScale, static_cast<double>(fNewEngineWidthScale), true);
				injector::WriteMemory(ptrAspectRatio, static_cast<float>(fNewAspectRatio), true);
			}
			else
			{
				#ifdef VERBOSE
				con.AddLogChar("Wrote default aspect ratio values");
				#endif

				injector::WriteMemory(ptrEsp18Height, static_cast<double>(-fDefaultEsp18Height), true);
				injector::WriteMemory(ptrEngineWidthScale, static_cast<double>(fDefaultEngineWidthScale), true);
				injector::WriteMemory(ptrAspectRatio, static_cast<float>(fDefaultAspectRatio), true);
			}

			*(int32_t*)(ptrResMovAddr) = regs.eax;
		}
	}; injector::MakeInline<ResChange>(pattern.count(1).get(0).get<uint32_t>(0), pattern.count(1).get(0).get<uint32_t>(4));

	spd::log()->info("{} -> Aspect ratio tweaks applied", __FUNCTION__);
}