// Fill out your copyright notice in the Description page of Project Settings.

#include "StickRPG.h"
#include "ItemBase.h"
#include "InventoryComponent.h"


// Sets default values
AInventoryComponent::AInventoryComponent() : Super()
{

}

// Called when the game starts or when spawned
void AInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

int AInventoryComponent::GetSlot(TSubclassOf<AItemBase> Item) {
	for (int i = 0; i < Items.Num(); i++) {
		if (Items[i].IsA(Item->GetClass())) {
			return i;
		}
	}

	return -1;
}

int AInventoryComponent::GetItemCount(TSubclassOf<AItemBase> Item) {
	if (GetSlot(Item) != -1) {
		return 0;
	}
	else { return -1; }
}

bool AInventoryComponent::HasItem(TSubclassOf<AItemBase> Item) {
	return GetItemCount(Item) > 0;
}

