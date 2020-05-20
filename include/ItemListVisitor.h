#pragma once

#include "RE/Skyrim.h"
#include "skse64/gamethreads.h"


class ItemListVisitor final : public TaskDelegate
{
public:
	explicit ItemListVisitor(RE::BSTArray<RE::ItemList::Item*> a_itemList);
	~ItemListVisitor() = default;


	void Run() override;
	void Dispose() override;


private:
	struct BestValueStorage
	{
		// shifted masks to unroll the combined equipment slots
		// also refer to https://github.com/Dakraid/BestInClassPP/issues/1
		enum class MaskedArmorSlot : UInt32
		{
			kHelmet = 1,
			kBody = 2,
			kHand = 3,
			kFeet = 7,
			kShield = 9
		};

		// light 5; heavy 5; cloth 4
		std::pair<RE::ItemList::Item*, float> Armor[14];
		// animation type 10
		std::pair<RE::ItemList::Item*, SInt32> Weapon[10];
		// arrow 1; bolt 1
		std::pair<RE::ItemList::Item*, float> Ammo[2];
	};

	using Slot = BestValueStorage::MaskedArmorSlot;


	void Visit();

	void CompareArmor(RE::ItemList::Item* a_item);
	void CompareWeapon(RE::ItemList::Item* a_item);
	void CompareAmmo(RE::ItemList::Item* a_item);

	Slot UnmaskToLowest(UInt32 a_slot);

	void SetBest();

	RE::BSTArray<RE::ItemList::Item*> _list{};
	BestValueStorage _bestStore;
};
