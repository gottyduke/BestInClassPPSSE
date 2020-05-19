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
		enum class MaskedArmorSlot : UInt32
		{
			kBody = 1 << 2,
			kHand = 1 << 3,
			kFeet = 1 << 7,
			kShield = 1 << 9,
			kHelmet1 = (1 << 12) + (1 << 1),
			kHelmet2 = (1 << 13) + (1 << 12) + (1 << 1) + (1 << 0)
		};
		
		std::pair<RE::ItemList::Item*, float> Armor[14];
		std::pair<RE::ItemList::Item*, SInt32> Weapon[9];
		std::pair<RE::ItemList::Item*, float> Ammo[2];
	};
	
	void Visit();
	
	void CompareArmor(RE::ItemList::Item* a_item);
	void CompareWeapon(RE::ItemList::Item* a_item);
	void CompareAmmo(RE::ItemList::Item* a_item);

	void SetBest();
	
	RE::BSTArray<RE::ItemList::Item*> _list{};
	BestValueStorage _bestStore;
};
