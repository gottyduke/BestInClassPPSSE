#pragma once

#include "RE/Skyrim.h"


class ItemListVisitor
{
public:
	explicit ItemListVisitor(RE::ItemList* a_itemList);
	~ItemListVisitor() = default;


	void Visit();

private:
	void ForEachItem(RE::InventoryEntryData* a_item);
	
	RE::ItemList* _list;
};