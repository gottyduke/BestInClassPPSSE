#include "Events.h"

#include "Hooks.h"

#include "SKSE/RegistrationSet.h"


namespace Events
{
	MenuOpenHandler::EventResult MenuOpenHandler::ProcessEvent(const RE::MenuOpenCloseEvent* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource)
	{
		if (!a_event) {
			return EventResult::kContinue;
		}
		
		auto* const intfcStr = RE::InterfaceStrings::GetSingleton();
		
		if (a_event->menuName == intfcStr->barterMenu ||
			a_event->menuName == intfcStr->containerMenu ||
			a_event->menuName == intfcStr->inventoryMenu) {
			// skip first execution to avoid re-iterating the list
			if (a_event->opening) {
				CurrentMenu = a_event->menuName;

				Hooks::Hook_SetMemberIfBestInClass();
			} else {
				CurrentMenu = nullptr;
			}
		}
		
		return EventResult::kContinue;
	}


	decltype(MenuOpenHandler::CurrentMenu) MenuOpenHandler::CurrentMenu(nullptr);
}
