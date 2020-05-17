#pragma once
#include "RE/ItemList.h"


namespace Hooks
{
	void Hook_SetIfBestInClass(RE::ItemList* a_list);
	
	bool InstallHooks();
}
