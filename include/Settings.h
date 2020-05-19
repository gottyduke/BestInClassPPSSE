#pragma once

#include "Json2Settings.h"


namespace J2S = Json2Settings;

class Settings
{
public:
	Settings() = delete;

	static bool LoadSettings(bool a_dumpParse = false);


	static J2S::sSetting compareAmmoBy;
	static J2S::sSetting compareArmorBy;
	static J2S::sSetting compareWeaponBy;

	
private:
	static constexpr auto FILE_NAME = R"(Data\SKSE\Plugins\BestInClassPPSSE.json)";
};