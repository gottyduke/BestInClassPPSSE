#include "Events.h"
#include "ItemListVisitor.h"

namespace Events
{
	auto MenuOpenHandler::ProcessEvent(const RE::MenuOpenCloseEvent* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource)
	-> EventResult
	{
		if (!a_event || !a_event->opening) {
			return EventResult::kContinue;
		}

		auto* const intfcStr = RE::InterfaceStrings::GetSingleton();
		auto* const ui = RE::UI::GetSingleton();
		RE::ItemList* itemList = nullptr;
		
		if (a_event->menuName == intfcStr->barterMenu) {
			const auto menu = static_cast<RE::BarterMenu*>(ui->GetMenu(a_event->menuName).get());
			itemList = menu ? menu->itemList : nullptr;
		} else if (a_event->menuName == intfcStr->containerMenu) {
			const auto menu = static_cast<RE::ContainerMenu*>(ui->GetMenu(a_event->menuName).get());
			itemList = menu ? menu->itemList : nullptr;
		} else if (a_event->menuName == intfcStr->inventoryMenu) {
			const auto menu = static_cast<RE::InventoryMenu*>(ui->GetMenu(a_event->menuName).get());
			itemList = menu ? menu->itemList : nullptr;
		} else {
			return EventResult::kContinue;
		}

		if (!itemList) {
			return EventResult::kContinue;
		}

		auto visitor = ItemListVisitor(itemList);
		visitor.Visit();
		
		return EventResult::kContinue;
	}


	void RegisterEvent()
	{
		auto* ui = RE::UI::GetSingleton();
		ui->AddEventSink(MenuOpenHandler::GetSingleton());
		_MESSAGE("Registered %s", typeid(MenuOpenHandler).name());
	}
}