#include "Hooks.h"
#include "Settings.h"
#include "version.h"

#include "SKSE/API.h"


namespace
{
	void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
	{
		switch (a_msg->type) {
		case SKSE::MessagingInterface::kDataLoaded:
			{
				break;
			}
		default:;
		}
	}
}


extern "C"
{
	bool SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
	{
		SKSE::Logger::OpenRelative(FOLDERID_Documents, L"\\My Games\\Skyrim Special Edition\\SKSE\\BestInClassPPSSE.log");
		SKSE::Logger::SetPrintLevel(SKSE::Logger::Level::kDebugMessage);
		SKSE::Logger::SetFlushLevel(SKSE::Logger::Level::kDebugMessage);
		SKSE::Logger::UseLogStamp(true);
		SKSE::Logger::TrackTrampolineStats(true);

		_MESSAGE("BestInClassPPSSE v%s", BICS_VERSION_VERSTRING);

		a_info->infoVersion = SKSE::PluginInfo::kVersion;
		a_info->name = "BestInClassPPSSE";
		a_info->version = BICS_VERSION_MAJOR;

		if (a_skse->IsEditor()) {
			_FATALERROR("Loaded in editor, marking as incompatible!\n");
			return false;
		}

		const auto ver = a_skse->RuntimeVersion();
		if (ver <= SKSE::RUNTIME_1_5_39) {
			_FATALERROR("Unsupported runtime version %s!", ver.GetString().c_str());
			return false;
		}

		return true;
	}


	bool SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
	{
		_MESSAGE("BestInClassPPSSE loaded");

		if (!Init(a_skse)) {
			return false;
		}
		
		if (Settings::LoadSettings()) {
			_MESSAGE("Settings loaded successully");
		} else {
			_FATALERROR("Failed to load settings\n");
			return false;
		}
		
		const auto* const messaging = SKSE::GetMessagingInterface();
		if (messaging->RegisterListener("SKSE", MessageHandler)) {
			_MESSAGE("Messaging interface registration successful");
		} else {
			_FATALERROR("Messaging interface registration failed!\n");
			return false;
		}

		if (!SKSE::AllocTrampoline(1 << 5)) {
			_FATALERROR("Failed to allocate trampoline");
			return false;
		}
		
		if (Hooks::InstallHooks()) {
			_MESSAGE("Hooks installed successfully");
		} else {
			_FATALERROR("Failed to install hooks!\n");
			return false;
		}
		
		return true;
	}
};
