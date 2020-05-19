#include "ItemListVisitor.h"


ItemListVisitor::ItemListVisitor(const RE::BSTArray<RE::ItemList::Item*> a_itemList) :
	_list(a_itemList),
	_bestStore()
{
}


void ItemListVisitor::Run()
{
	Visit();
}


void ItemListVisitor::Dispose()
{
	delete this;
}


void ItemListVisitor::Visit()
{
	if (!_list.data()) {
		return;
	}
	
	for (auto item : _list) {
		if (!item) {
			continue;
		}
		
		switch (item->data.objDesc->GetObject()->GetFormType()) {
		case RE::FormType::Armor:
			{
				CompareArmor(item);
				break;
			}
		case RE::FormType::Weapon:
			{
				CompareWeapon(item);
				break;
			}
		case RE::FormType::Ammo:
			{
				CompareAmmo(item);
				break;
			}
		default:;
		}
	}
	
	SetBest();
}


void ItemListVisitor::CompareArmor(RE::ItemList::Item* a_item)
{
	using Slot = BestValueStorage::MaskedArmorSlot;
	
	auto* const armor = static_cast<RE::TESObjectARMO*>(a_item->data.objDesc->GetObject());
	const auto type = std::underlying_type_t<RE::BIPED_MODEL::ArmorType>(armor->GetArmorType()) * 5;
	const auto slotMask = std::underlying_type_t<RE::BIPED_MODEL::BipedObjectSlot>(armor->GetSlotMask());
	UInt32 typeMask;
	
	switch (static_cast<Slot>(slotMask)) {
	case Slot::kBody:
		{
			typeMask = type + 0;
			break;
		}
	case Slot::kHand:
		{
			typeMask = type + 1;
			break;
		}
	case Slot::kFeet:
		{
			typeMask = type + 2;
			break;
		}
	case Slot::kShield:
		{
			typeMask = type + 3;
			break;
		}
	case Slot::kHelmet1:
	case Slot::kHelmet2:
		{
			typeMask = type + 4;
			break;
		}
	default:
		{
			typeMask = -1;
			break;
		}
	}

	// discard the rest and ClothingShield, because there's no ClothingShield
	if (typeMask >= 0 && typeMask < 14) {
		auto& [item, value] = _bestStore.Armor[typeMask];

		// compare armor by rating, compare clothing by amount of enchantments
		const auto rhsCompare = typeMask < 10 ? armor->GetArmorRating() : armor->amountofEnchantment;
		
		if (value < rhsCompare) {
			item = a_item;
			value = rhsCompare;
		}	
	}
}


void ItemListVisitor::CompareWeapon(RE::ItemList::Item* a_item)
{
	auto* const weapon = static_cast<RE::TESObjectWEAP*>(a_item->data.objDesc->GetObject());
	const auto typeMask = std::underlying_type_t<RE::WEAPON_TYPE>(weapon->GetWeaponType());

	auto& [item, value] = _bestStore.Weapon[typeMask];

	if (value < weapon->GetAttackDamage()) {
		item = a_item;
		value = weapon->GetAttackDamage();
	}
}


void ItemListVisitor::CompareAmmo(RE::ItemList::Item* a_item)
{
	auto* const ammo = static_cast<RE::TESAmmo*>(a_item->data.objDesc->GetObject());
	const auto typeMask = ammo->IsBolt() ? 0 : 1;
	auto& [item, value] = _bestStore.Ammo[typeMask];

	if (value < ammo->data.damage) {
		item = a_item;
		value = ammo->data.damage;
	}
}


void ItemListVisitor::SetBest()
{
	for (auto [item, value] : _bestStore.Armor) {
		if (item) {
			item->obj.SetMember("bestInClass", true);
		}
	}
	
	for (auto [item, value] : _bestStore.Weapon) {
		if (item) {
			item->obj.SetMember("bestInClass", true);
		}
	}
	
	for (auto [item, value] : _bestStore.Ammo) {
		if (item) {
			item->obj.SetMember("bestInClass", true);
		}
	}
}