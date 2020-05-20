#include "Hooks.h"

#include "Events.h"
#include "ItemListVisitor.h"

#include "DKUtil/Hook.h"
#include "SKSE/RegistrationSet.h"


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
	// triggered when menu is opened and when any item is updated
	void __fastcall Hook_SetMemberIfBestInClass(void* a_this)
	{
		using Event = Events::MenuOpenHandler;

		// skip first execution to avoid re-iterating the list
		// also refer to https://github.com/Dakraid/BestInClassPP/issues/3
		if (Event::CurrentMenu.empty()) {
			return;
		}

		auto* ui = RE::UI::GetSingleton();
		auto* intfcStr = RE::InterfaceStrings::GetSingleton();
		const auto* task = SKSE::GetTaskInterface();

		if (Event::CurrentMenu == intfcStr->barterMenu) {
			const auto menu = static_cast<RE::BarterMenu*>(ui->GetMenu(Event::CurrentMenu).get());
			task->AddTask(new ItemListVisitor(menu->itemList->items));
		}
		if (Event::CurrentMenu == intfcStr->containerMenu) {
			const auto menu = static_cast<RE::ContainerMenu*>(ui->GetMenu(Event::CurrentMenu).get());
			task->AddTask(new ItemListVisitor(menu->itemList->items));
		}
		if (Event::CurrentMenu == intfcStr->inventoryMenu) {
			const auto menu = static_cast<RE::InventoryMenu*>(ui->GetMenu(Event::CurrentMenu).get());
			task->AddTask(new ItemListVisitor(menu->itemList->items));
		}
	}


	bool InstallHooks()
	{
		auto success = true;

		// completely substitute call skyrimse.7FF7C688C620 <- SetMemberIfBestInClass( rcx( void* : this ) ) : rax( void )
		success &= DKUtil::Hook::BranchToFunction
			<BARTER_ID, BARTER_OFFSET, BARTER_OFFSET + SKIP_SIZE>
			(reinterpret_cast<std::uintptr_t>(&Hook_SetMemberIfBestInClass));
		_DMESSAGE("Patched BarterMenu");

		success &= DKUtil::Hook::BranchToFunction
			<CONTAINER_ID, CONTAINER_OFFSET, CONTAINER_OFFSET + SKIP_SIZE>
			(reinterpret_cast<std::uintptr_t>(&Hook_SetMemberIfBestInClass));
		_DMESSAGE("Patched ContainerMenu");

		success &= DKUtil::Hook::BranchToFunction
			<INVENTORY_ID, INVENTORY_OFFSET, INVENTORY_OFFSET + SKIP_SIZE>
			(reinterpret_cast<std::uintptr_t>(&Hook_SetMemberIfBestInClass));
		_DMESSAGE("Patched InventoryMenu");

		return success;
	}
}
