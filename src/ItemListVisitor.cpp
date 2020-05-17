#include "ItemListVisitor.h"


ItemListVisitor::ItemListVisitor(RE::ItemList* a_itemList) :
	_list(a_itemList)
{
}


void ItemListVisitor::Visit()
{
	for (auto& item : _list->items) {
		item->obj.SetMember("bestInClass", true);
	}
}


void ItemListVisitor::ForEachItem(RE::InventoryEntryData* a_item)
{
	
}
