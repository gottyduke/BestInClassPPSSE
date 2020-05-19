#include "Hooks.h"

#include "DKUtil/Hook.h"


namespace
{
	constexpr std::uintptr_t SKIP_SIZE = 5;

	
	constexpr std::uint64_t BARTER_ID = 50014;
	constexpr std::uintptr_t BARTER_OFFSET = 0x120;
	
	constexpr std::uint64_t CONTAINER_ID = 50215;
	constexpr std::uintptr_t CONTAINER_OFFSET = 0x1D6;

	constexpr std::uint64_t INVENTORY_ID = 50987;
	constexpr std::uintptr_t INVENTORY_OFFSET = 0x112;
}


namespace Hooks
{
	void __fastcall Hook_SetMemberIfBestInClass(void* a_this)
	{
		_MESSAGE("Hook");
	}


	bool InstallHooks()
	{
		auto success = true;
		
		// completely substitute call skyrimse.7FF7C688C620 <- SetMemberIfBestInClass( rcx( void* : this ) ) : rax( void )
		success &= DKUtil::Hook::BranchToFunction
		<BARTER_ID, BARTER_OFFSET, BARTER_OFFSET + SKIP_SIZE>
		(reinterpret_cast<std::uintptr_t>(&Hook_SetMemberIfBestInClass));
		
		success &= DKUtil::Hook::BranchToFunction
		<CONTAINER_ID, CONTAINER_OFFSET, CONTAINER_OFFSET + SKIP_SIZE>
		(reinterpret_cast<std::uintptr_t>(&Hook_SetMemberIfBestInClass));
		
		success &= DKUtil::Hook::BranchToFunction
		<INVENTORY_ID, INVENTORY_OFFSET, INVENTORY_OFFSET + SKIP_SIZE>
		(reinterpret_cast<std::uintptr_t>(&Hook_SetMemberIfBestInClass));

		return success;
	}
}
