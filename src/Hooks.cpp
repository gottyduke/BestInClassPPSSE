#include "Hooks.h"
#include "Settings.h"

#include "DKUtil/Hook.h"

namespace
{
	constexpr auto FUNC_ID = 50987;
	constexpr auto START = 0x10D; // lea rcx, ptr [ rsp + 0x30 ] <- rcx : ItemList*
	constexpr auto END = 0x117; // call skyrimse.7FF7C688C620 <- SetMemberIfBestInClass( rcx( std::uintptr_t ) ) : rax( void )
}


namespace Hooks
{
	void Hook_SetMemberIfBestInClass(RE::BSTArray<RE::ItemList::Item*> a_list)
	{
		_DMESSAGE(a_list[0]->data.GetName());
	}
	

	bool InstallHooks()
	{ 
		auto success = true;

		// completely substitute skyrimse.7FF7C688C620 function with our own
		success &= DKUtil::Hook::BranchToFunction<FUNC_ID, START, END>(reinterpret_cast<std::uintptr_t>(&Hook_SetMemberIfBestInClass), "\x48\x8B\x4C\x24\x30", 5);
		return success;
	}
}
