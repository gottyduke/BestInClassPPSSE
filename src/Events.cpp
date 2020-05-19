#include "Events.h"

#include "Hooks.h"

#include "ItemListVisitor.h"
#include "SKSE/RegistrationSet.h"

namespace Events
{
	MenuOpenHandler::EventResult MenuOpenHandler::ProcessEvent(const RE::MenuOpenCloseEvent* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource)
	{
		if (!a_event || !a_event->opening) {
			return EventResult::kContinue;
		}

		CurrentMenu = a_event->menuName;
		
		auto* const ui = RE::UI::GetSingleton();
		auto* const intfcStr = RE::InterfaceStrings::GetSingleton();
		
		const auto* task = SKSE::GetTaskInterface();

		if (CurrentMenu != intfcStr->barterMenu || 
			CurrentMenu != intfcStr->containerMenu ||
			CurrentMenu != intfcStr->inventoryMenu) {
			return EventResult::kContinue;
		}

		_MESSAGE("Event");
		Hooks::Hook_SetMemberIfBestInClass(nullptr);
		
		return EventResult::kContinue;
	}


	decltype(MenuOpenHandler::CurrentMenu) MenuOpenHandler::CurrentMenu(nullptr);
}
