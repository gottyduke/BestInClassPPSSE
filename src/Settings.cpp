#include "Settings.h"


bool Settings::LoadSettings(const bool a_dumpParse)
{
	auto [log, success] = J2S::load_settings(FILE_NAME, a_dumpParse);

	if (!log.empty()) {
		_ERROR("%s", log.c_str());
	}

	return success;
}


decltype(Settings::compareAmmoBy) Settings::compareAmmoBy("compareAmmoBy", "damage");
decltype(Settings::compareArmorBy) Settings::compareArmorBy("compareArmorBy", "rating");
decltype(Settings::compareWeaponBy) Settings::compareWeaponBy("compareWeaponBy", "damage");