#include "ItemListVisitor.h"


ItemListVisitor::ItemListVisitor(const RE::BSTArray<RE::ItemList::Item*> a_itemList) :
	_list(a_itemList)
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
	
	for (auto& item : _list) {
		if (!item) {
			continue;
		}
		
		_DMESSAGE("item is %s", item->data.GetName());
		item->obj.SetMember("bestInClass", true);
		
		switch (item->data.objDesc->GetObject()->GetFormType()) {
		case RE::FormType::Armor:
			{
				CompareArmor(item);
				break;
			}
		case RE::FormType::Weapon:
			{
				const auto var = static_cast<RE::TESObjectWEAP*>(item->data.objDesc->GetObject());
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


void ItemListVisitor::CompareArmor(const RE::ItemList::Item* a_bound)
{
	
}


void ItemListVisitor::CompareWeapon(const RE::ItemList::Item* a_bound)
{
	
}


void ItemListVisitor::CompareAmmo(const RE::ItemList::Item* a_bound)
{
	
}


void ItemListVisitor::SetBest()
{
	
}
