#include <iostream>
#include "..\includes\stdafx.h"
#include "dllmain.h"
#include "ConsoleWnd.h"
#include "Settings.h"
#include "settings_string.h"
#include "tool_menu.h"

Settings cfg;

struct key_type {
	int vk;
	int dik;
};

std::unordered_map<std::string, key_type> key_map
{
	{ "ESCAPE", { 0x1B, 0x01 } },    // Esc
	{ "ESC", { 0x1B, 0x01 } },    // Esc
	{ "0", { 0x30, 0x0B } },    // 0
	{ "1", { 0x31, 0x02 } },    // 1
	{ "2", { 0x32, 0x03 } },    // 2
	{ "3", { 0x33, 0x04 } },    // 3
	{ "4", { 0x34, 0x05 } },    // 4
	{ "5", { 0x35, 0x06 } },    // 5
	{ "6", { 0x36, 0x07 } },    // 6
	{ "7", { 0x37, 0x08 } },    // 7
	{ "8", { 0x38, 0x09 } },    // 8
	{ "9", { 0x39, 0x0A } },    // 9
	{ "A", { 0x41, 0x1E } },    // A
	{ "B", { 0x42, 0x30 } },    // B
	{ "C", { 0x43, 0x2E } },    // C
	{ "D", { 0x44, 0x20 } },    // D
	{ "E", { 0x45, 0x12 } },    // E
	{ "F", { 0x46, 0x21 } },    // F
	{ "G", { 0x47, 0x22 } },    // G
	{ "H", { 0x48, 0x23 } },    // H
	{ "I", { 0x49, 0x17 } },    // I
	{ "J", { 0x4A, 0x24 } },    // J
	{ "K", { 0x4B, 0x25 } },    // K
	{ "L", { 0x4C, 0x26 } },    // L
	{ "M", { 0x4D, 0x32 } },    // M
	{ "N", { 0x4E, 0x31 } },    // N
	{ "O", { 0x4F, 0x18 } },    // O
	{ "P", { 0x50, 0x19 } },    // P
	{ "Q", { 0x51, 0x10 } },    // Q
	{ "R", { 0x52, 0x13 } },    // R
	{ "S", { 0x53, 0x1F } },    // S
	{ "T", { 0x54, 0x14 } },    // T
	{ "U", { 0x55, 0x16 } },    // U
	{ "V", { 0x56, 0x2F } },    // V
	{ "W", { 0x57, 0x11 } },    // W
	{ "X", { 0x58, 0x2D } },    // X
	{ "Y", { 0x59, 0x15 } },    // Y
	{ "Z", { 0x5A, 0x2C } },    // Z
	{ "BACK", { 0x08, 0x0E } },    // Backspace
	{ "BACKSPACE", { 0x08, 0x0E } },    // Backspace
	{ "BKSP", { 0x08, 0x0E } },    // Backspace
	{ "ADD", { 0x6B, 0x4E } },    // Numpad +
	{ "NUM+", { 0x6B, 0x4E } },    // Numpad +
	{ "DECIMAL", { 0x6E, 0x53 } },    // Numpad .
	{ "NUM.", { 0x6E, 0x53 } },    // Numpad .
	{ "DIVIDE", { 0x6F, 0xB5 } },    // Numpad /
	{ "NUM/", { 0x6F, 0xB5 } },    // Numpad /
	{ "MULTIPLY", { 0x6A, 0x37 } },    // Numpad *
	{ "NUM*", { 0x6A, 0x37 } },    // Numpad *
	{ "SUBTRACT", { 0x6D, 0x4A } },    // Numpad -
	{ "NUM-", { 0x6D, 0x4A } },    // Numpad -
	{ "NUMPAD0", { 0x60, 0x52 } },    // Numpad 0
	{ "NUMPAD1", { 0x61, 0x4F } },    // Numpad 1
	{ "NUMPAD2", { 0x62, 0x50 } },    // Numpad 2
	{ "NUMPAD3", { 0x63, 0x51 } },    // Numpad 3
	{ "NUMPAD4", { 0x64, 0x4B } },    // Numpad 4
	{ "NUMPAD5", { 0x65, 0x4C } },    // Numpad 5
	{ "NUMPAD6", { 0x66, 0x4D } },    // Numpad 6
	{ "NUMPAD7", { 0x67, 0x47 } },    // Numpad 7
	{ "NUMPAD8", { 0x68, 0x48 } },    // Numpad 8
	{ "NUMPAD9", { 0x69, 0x49 } },    // Numpad 9
	{ "NUM0", { 0x60, 0x52 } },    // Numpad 0
	{ "NUM1", { 0x61, 0x4F } },    // Numpad 1
	{ "NUM2", { 0x62, 0x50 } },    // Numpad 2
	{ "NUM3", { 0x63, 0x51 } },    // Numpad 3
	{ "NUM4", { 0x64, 0x4B } },    // Numpad 4
	{ "NUM5", { 0x65, 0x4C } },    // Numpad 5
	{ "NUM6", { 0x66, 0x4D } },    // Numpad 6
	{ "NUM7", { 0x67, 0x47 } },    // Numpad 7
	{ "NUM8", { 0x68, 0x48 } },    // Numpad 8
	{ "NUM9", { 0x69, 0x49 } },    // Numpad 9
	{ "OEM_COMMA", { 0xBC, 0x33 } },    // OEM_COMMA (< ,)
	{ "OEM_MINUS", { 0xBD, 0x0C } },    // OEM_MINUS (_ -)
	{ "OEM_PERIOD", { 0xBE, 0x34 } },    // OEM_PERIOD (> .)
	{ "OEM_PLUS", { 0xBB, 0x0D } },    // OEM_PLUS (+ =)
	{ "<", { 0xBC, 0x33 } },    // OEM_COMMA (< ,)
	{ ",", { 0xBC, 0x33 } },    // OEM_COMMA (< ,)
	{ "_", { 0xBD, 0x0C } },    // OEM_MINUS (_ -)
	{ "-", { 0xBD, 0x0C } },    // OEM_MINUS (_ -)
	{ ">", { 0xBE, 0x34 } },    // OEM_PERIOD (> .)
	{ ".", { 0xBE, 0x34 } },    // OEM_PERIOD (> .)
	{ "+", { 0xBB, 0x0D } },    // OEM_PLUS (+ =)
	{ "=", { 0xBB, 0x0D } },    // OEM_PLUS (+ =)
	{ "RETURN", { 0x0D, 0x1C } },    // Enter
	{ "ENTER", { 0x0D, 0x1C } },    // Enter
	{ "RENTER", { 0x6C, 0 } },    // Right/Numpad Enter
	{ "SPACE", { 0x20, 0x39 } },    // Space
	{ "TAB", { 0x09, 0x0F } },    // Tab
	{ "APPS", { 0x5D, 0xDD } },    // Context Menu
	{ "CAPSLOCK", { 0x14, 0x3A } },    // Caps Lock
	{ "CONVERT", { 0x1C, 0x79 } },    // Convert
	{ "UP", { 0x26, 0xC8 } },    // Arrow Up
	{ "DOWN", { 0x28, 0xD0 } },    // Arrow Down
	{ "LEFT", { 0x25, 0xCB } },    // Arrow Left
	{ "RIGHT", { 0x27, 0xCD } },    // Arrow Right
	{ "F1", { 0x70, 0x3B } },    // F1
	{ "F2", { 0x71, 0x3C } },    // F2
	{ "F3", { 0x72, 0x3D } },    // F3
	{ "F4", { 0x73, 0x3E } },    // F4
	{ "F5", { 0x74, 0x3F } },    // F5
	{ "F6", { 0x75, 0x40 } },    // F6
	{ "F7", { 0x76, 0x41 } },    // F7
	{ "F8", { 0x77, 0x42 } },    // F8
	{ "F9", { 0x78, 0x43 } },    // F9
	{ "F10", { 0x79, 0x44 } },    // F10
	{ "F11", { 0x7A, 0x57 } },    // F11
	{ "F12", { 0x7B, 0x58 } },    // F12
	{ "F13", { 0x7C, 0x64 } },    // F13
	{ "F14", { 0x7D, 0x65 } },    // F14
	{ "F15", { 0x7E, 0x66 } },    // F15
	{ "HOME", { 0x24, 0xC7 } },    // Home
	{ "INSERT", { 0x2D, 0xD2 } },    // Insert
	{ "DELETE", { 0x2E, 0xD3 } },    // Delete
	{ "DEL", { 0x2E, 0xD3 } },    // Delete
	{ "END", { 0x23, 0xCF } },    // End
	{ "PAGEUP", { 0x21, 0xC9 } },    // Page Up
	{ "PAGEDOWN", { 0x22, 0xD1 } },    // Page Down
	{ "PGUP", { 0x21, 0xC9 } },    // Page Up
	{ "PGDOWN", { 0x22, 0xD1 } },    // Page Down
	{ "KANA", { 0x15, 0x70 } },    // Kana
	{ "KANJI", { 0x19, 0x94 } },    // Kanji
	{ "LCONTROL", { 0xA2, 0x1D } },    // Left Ctrl
	{ "CONTROL", { 0xA2, 0x1D } },  // Left Ctrl
	{ "CTRL", { 0xA2, 0x1D } },  // Left Ctrl
	{ "LCTRL", { 0xA2, 0x1D } },  // Left Ctrl
	{ "LMENU", { 0xA4, 0x38 } },    // Left Alt
	{ "ALT", { 0xA4, 0x38 } },  // Left Alt
	{ "LALT", { 0xA4, 0x38 } },  // Left Alt
	{ "LSHIFT", { 0xA0, 0x2A } },    // Left Shift
	{ "SHIFT", { 0xA0, 0x2A } },    // Left Shift
	{ "LWIN", { 0x5B, 0xDB } },    // Left Win
	{ "NONCONVERT", { 0x1D, 0x7B } },    // Non Convert
	{ "NUMLOCK", { 0x90, 0x45 } },    // Num Lock
	{ "PAUSE", { 0x13, 0xC5 } },    // Pause
	{ "RCONTROL", { 0xA3, 0x9D } },    // Right Ctrl
	{ "RCTRL", { 0xA3, 0x9D } },  // Right Ctrl
	{ "RMENU", { 0xA5, 0xB8 } },    // Right Alt
	{ "ALTGR", { 0xA5, 0xB8 } },  // Right Alt
	{ "RALT", { 0xA5, 0xB8 } },  // Right Alt
	{ "RSHIFT", { 0xA1, 0x36 } },    // Right Shift
	{ "RWIN", { 0x5C, 0xDC } },    // Right Win
	{ "SCROLL", { 0x91, 0x46 } },    // Scrol Lock
	{ "SLEEP", { 0x5F, 0xDF } },    // Sleep
	{ "PRINTSCR", { 0x2C, 0xB7 } },    // Print Screen

	// VKs for localised keyboards
	{ ";", { VK_OEM_1, 0x27 } },
	{ ":", { VK_OEM_1, 0x27 } },
	{ "/", { VK_OEM_2, 0x35 } },
	{ "?", { VK_OEM_2, 0x35 } },
	{ "'", { VK_OEM_3, 0 } }, // UK keyboard
	{ "@", { VK_OEM_3, 0 } }, // UK keyboard
	{ "[", { VK_OEM_4, 0x1A } },
	{ "{", { VK_OEM_4, 0x1A } },
	{ "\\", { VK_OEM_5, 0x2B } },
	{ "|", { VK_OEM_5, 0x2B } },
	{ "]", { VK_OEM_6, 0x1B } },
	{ "}", { VK_OEM_6, 0x1B } },
	{ "#", { VK_OEM_7, 0 } },  // UK keyboard
	{ "\"", { VK_OEM_7, 0 } }, // UK keyboard
	{ "`", { VK_OEM_8, 0 } },  // UK keyboard
};

int Settings::KeyMap(const char* key, bool get_vk)
{
	if (!key_map.count(key))
		return 0;

	if (get_vk)
		return key_map[key].vk;

	return key_map[key].dik;
}

void Settings::ReadSettings()
{
	CIniReader iniReader("");

	#ifdef VERBOSE
	con.AddLogChar("Reading settings");
	#endif

	cfg.HasUnsavedChanges = false;

	cfg.fFOVAdditional = iniReader.ReadFloat("DISPLAY", "FOVAdditional", 0.0f);
	if (cfg.fFOVAdditional > 0.0f)
		bEnableFOV = true;
	else
		bEnableFOV = false;

	cfg.bFixUltraWideAspectRatio = iniReader.ReadBoolean("DISPLAY", "FixUltraWideAspectRatio", true);
	cfg.bDisableVsync = iniReader.ReadBoolean("DISPLAY", "DisableVsync", false);
	cfg.bFixDisplayMode = iniReader.ReadBoolean("DISPLAY", "FixDisplayMode", true);
	cfg.iCustomRefreshRate = iniReader.ReadInteger("DISPLAY", "CustomRefreshRate", -1);
	cfg.bRestorePickupTransparency = iniReader.ReadBoolean("DISPLAY", "RestorePickupTransparency", true);
	cfg.bDisableBrokenFilter03 = iniReader.ReadBoolean("DISPLAY", "DisableBrokenFilter03", true);
	cfg.bFixBlurryImage = iniReader.ReadBoolean("DISPLAY", "FixBlurryImage", true);
	cfg.bDisableFilmGrain = iniReader.ReadBoolean("DISPLAY", "DisableFilmGrain", true);
	cfg.bEnableGCBlur = iniReader.ReadBoolean("DISPLAY", "EnableGCBlur", true);
	cfg.bEnableGCScopeBlur = iniReader.ReadBoolean("DISPLAY", "EnableGCScopeBlur", true);
	cfg.bWindowBorderless = iniReader.ReadBoolean("DISPLAY", "WindowBorderless", false);
	cfg.iWindowPositionX = iniReader.ReadInteger("DISPLAY", "WindowPositionX", -1);
	cfg.iWindowPositionY = iniReader.ReadInteger("DISPLAY", "WindowPositionY", -1);
	cfg.bRememberWindowPos = iniReader.ReadBoolean("DISPLAY", "RememberWindowPos", false);
	cfg.b60fpsFixes = iniReader.ReadBoolean("MISC", "60fpsFixes", true);
	cfg.bFixQTE = iniReader.ReadBoolean("MISC", "FixQTE", true);
	cfg.bAshleyJPCameraAngles = iniReader.ReadBoolean("MISC", "AshleyJPCameraAngles", false);
	cfg.bSkipIntroLogos = iniReader.ReadBoolean("MISC", "SkipIntroLogos", false);
	cfg.bEnableDebugMenu = iniReader.ReadBoolean("MISC", "EnableDebugMenu", false);
	cfg.sDebugMenuKeyCombo = iniReader.ReadString("MISC", "DebugMenuKeyCombination", "CTRL+F3"); // if default changed, make sure to edit tool_menu.cpp!toolMenuKeyCombo vector!
	cfg.bUseMouseTurning = iniReader.ReadBoolean("MOUSE", "UseMouseTurning", true);
	cfg.fTurnSensitivity = iniReader.ReadFloat("MOUSE", "TurnSensitivity", 1.0f);
	cfg.bFixSniperZoom = iniReader.ReadBoolean("MOUSE", "FixSniperZoom", true);
	cfg.bFixRetryLoadMouseSelector = iniReader.ReadBoolean("MOUSE", "FixRetryLoadMouseSelector", true);
	cfg.flip_item_up = iniReader.ReadString("KEYBOARD", "flip_item_up", "HOME");
	cfg.flip_item_down = iniReader.ReadString("KEYBOARD", "flip_item_down", "END");
	cfg.flip_item_left = iniReader.ReadString("KEYBOARD", "flip_item_left", "INSERT");
	cfg.flip_item_right = iniReader.ReadString("KEYBOARD", "flip_item_right", "PAGEUP");
	cfg.QTE_key_1 = iniReader.ReadString("KEYBOARD", "QTE_key_1", "D");
	cfg.QTE_key_2 = iniReader.ReadString("KEYBOARD", "QTE_key_2", "A");
	cfg.bAllowHighResolutionSFD = iniReader.ReadBoolean("MOVIE", "AllowHighResolutionSFD", true);
	cfg.bRaiseVertexAlloc = iniReader.ReadBoolean("MEMORY", "RaiseVertexAlloc", true);
	cfg.bRaiseInventoryAlloc = iniReader.ReadBoolean("MEMORY", "RaiseInventoryAlloc", true);
	cfg.bUseMemcpy = iniReader.ReadBoolean("MEMORY", "UseMemcpy", true);
	cfg.bIgnoreFPSWarning = iniReader.ReadBoolean("FRAME RATE", "IgnoreFPSWarning", false);
	
	cfg.fFontSize = iniReader.ReadFloat("IMGUI", "FontSize", 1.0f);
	if (cfg.fFontSize < 1.0f)
		cfg.fFontSize = 1.0f;

	if (cfg.fFontSize > 1.3f)
		cfg.fFontSize = 1.3f;

	if (cfg.sDebugMenuKeyCombo.length())
		ParseToolMenuKeyCombo(cfg.sDebugMenuKeyCombo);
}

void Settings::WriteSettings()
{
	CIniReader iniReader("");

	std::string iniPath = rootPath + WrapperName.substr(0, WrapperName.find_last_of('.')) + ".ini";

	#ifdef VERBOSE
	con.AddConcatLog("Writing settings to: ", iniPath.data());
	#endif

	// Copy the default .ini to folder if one doesn't exist, just so we can keep comments and descriptions intact.
	const char* filename = iniPath.c_str();
	if (!std::filesystem::exists(filename)) {
		#ifdef VERBOSE
		con.AddLogChar("ini file doesn't exist in folder. Creating new one.");
		#endif
		std::ofstream iniFile(iniPath);
		iniFile << defaultSettings;
		iniFile.close();
	}

	iniReader.WriteFloat("DISPLAY", "FOVAdditional", cfg.fFOVAdditional);
	iniReader.WriteBoolean("DISPLAY", "FixUltraWideAspectRatio", cfg.bFixUltraWideAspectRatio);
	iniReader.WriteBoolean("DISPLAY", "DisableVsync", cfg.bDisableVsync);
	iniReader.WriteBoolean("DISPLAY", "FixDisplayMode", cfg.bFixDisplayMode);
	iniReader.WriteInteger("DISPLAY", "CustomRefreshRate", cfg.iCustomRefreshRate);
	iniReader.WriteBoolean("DISPLAY", "RestorePickupTransparency", cfg.bRestorePickupTransparency);
	iniReader.WriteBoolean("DISPLAY", "DisableBrokenFilter03", cfg.bDisableBrokenFilter03);
	iniReader.WriteBoolean("DISPLAY", "FixBlurryImage", cfg.bFixBlurryImage);
	iniReader.WriteBoolean("DISPLAY", "DisableFilmGrain", cfg.bDisableFilmGrain);
	iniReader.WriteBoolean("DISPLAY", "EnableGCBlur", cfg.bEnableGCBlur);
	iniReader.WriteBoolean("DISPLAY", "EnableGCScopeBlur", cfg.bEnableGCScopeBlur);
	iniReader.WriteBoolean("DISPLAY", "WindowBorderless", cfg.bWindowBorderless);
	iniReader.WriteInteger("DISPLAY", "WindowPositionX", cfg.iWindowPositionX);
	iniReader.WriteInteger("DISPLAY", "WindowPositionY", cfg.iWindowPositionY);
	iniReader.WriteBoolean("DISPLAY", "RememberWindowPos", cfg.bRememberWindowPos);
	iniReader.WriteBoolean("MISC", "FixQTE", cfg.bFixQTE);
	iniReader.WriteBoolean("MISC", "AshleyJPCameraAngles", cfg.bAshleyJPCameraAngles);
	iniReader.WriteBoolean("MISC", "SkipIntroLogos", cfg.bSkipIntroLogos);
	iniReader.WriteBoolean("MISC", "EnableDebugMenu", cfg.bEnableDebugMenu);
	iniReader.WriteString("MISC", "DebugMenuKeyCombination", cfg.sDebugMenuKeyCombo);
	iniReader.WriteBoolean("MOUSE", "FixSniperZoom", cfg.bFixSniperZoom);
	iniReader.WriteBoolean("MOUSE", "FixRetryLoadMouseSelector", cfg.bFixRetryLoadMouseSelector);
	iniReader.WriteString("KEYBOARD", "flip_item_up", " " + cfg.flip_item_up);
	iniReader.WriteString("KEYBOARD", "flip_item_down", " " + cfg.flip_item_down);
	iniReader.WriteString("KEYBOARD", "flip_item_left", " " + cfg.flip_item_left);
	iniReader.WriteString("KEYBOARD", "flip_item_right", " " + cfg.flip_item_right);
	iniReader.WriteString("KEYBOARD", "QTE_key_1", " " + cfg.QTE_key_1);
	iniReader.WriteString("KEYBOARD", "QTE_key_2", " " + cfg.QTE_key_2);
	iniReader.WriteBoolean("MOVIE", "AllowHighResolutionSFD", cfg.bAllowHighResolutionSFD);
	iniReader.WriteBoolean("MEMORY", "RaiseVertexAlloc", cfg.bRaiseVertexAlloc);
	iniReader.WriteBoolean("MEMORY", "RaiseInventoryAlloc", cfg.bRaiseInventoryAlloc);
	iniReader.WriteBoolean("MEMORY", "UseMemcpy", cfg.bUseMemcpy);
	iniReader.WriteFloat("IMGUI", "FontSize", cfg.fFontSize);

	cfg.HasUnsavedChanges = false;
}
