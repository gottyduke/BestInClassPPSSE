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
		enum class ArmorType : UInt32
		{
			kHead = 1 << 0,
			kHair = 1 << 1,
			kBody = 1 << 2,
			kHands = 1 << 3,
			kAmulet = 1 << 5,
			kRing = 1 << 6,
			kFeet = 1 << 7,
			kShield = 1 << 9,
			kCirclet = 1 << 12,
		};
		
		enum class WeaponType : UInt8
		{
			kHandToHandMelee = 0,
			kOneHandSword = 1,
			kOneHandDagger = 2,
			kOneHandAxe = 3,
			kOneHandMace = 4,
			kTwoHandSword = 5,
			kTwoHandAxe = 6,
			kBow = 7,
			kStaff = 8,
			kCrossbow = 9
		};

		enum class AmmoType : UInt8
		{
			kArrow,
			kBolt
		};

		
		std::pair<ArmorType, std::pair<RE::ItemList::Item*, std::ptrdiff_t>> bestArmorStore[9];
		std::pair<WeaponType, std::pair<RE::ItemList::Item*, std::ptrdiff_t>> bestWeaponStore[10];
		std::pair<AmmoType, std::pair<RE::ItemList::Item*, std::ptrdiff_t>> bestAmmoStore[2];
	};

	
	void Visit();
	
	void CompareArmor(const RE::ItemList::Item* a_bound);
	void CompareWeapon(const RE::ItemList::Item* a_bound);
	void CompareAmmo(const RE::ItemList::Item* a_bound);

	void SetBest();

	
	RE::BSTArray<RE::ItemList::Item*> _list{};
	static BestValueStorage _bestStore;
};
