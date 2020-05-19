#pragma once

#include "DKUtil/SDM.h"
#include "RE/Skyrim.h"


namespace Events
{
	class MenuOpenHandler final :
		public DKUtil::SDM<MenuOpenHandler>,
		public RE::BSTEventSink<RE::MenuOpenCloseEvent>
	{
	public:
		static RE::BSFixedString CurrentMenu;
		
		using EventResult = RE::BSEventNotifyControl;

		EventResult ProcessEvent(const RE::MenuOpenCloseEvent* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;
	};
}
