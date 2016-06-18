// Fill out your copyright notice in the Description page of Project Settings.

#include "rpg.h"
#include "UnrealNetwork.h"
#include "InventoryContainer.h"

// Sets default values
AInventoryContainer::AInventoryContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInventoryContainer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInventoryContainer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

//Our network replication here.
void AInventoryContainer::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInventoryContainer, Items);
}

//The system allows for an auto stack creation method.
bool AInventoryContainer::AddItem(TSubclassOf<AItemBase> Item, int Quantity) {
	auto obj = Item.GetDefaultObject();
	bool CreatedNewStack = false;

	if (obj->Stackable && GetItemCount(Item) > 0) {
		TArray<ItemDistributor> AvailableSlots;
		int QuantityRemaining = Quantity;
		int MaxStack = obj->MaxStack;

		for (int i = 0; i < Items.Num(); i++) {
			if (Items[i].Reference == Item && QuantityRemaining > 0) {
				if (Items[i].Quantity + QuantityRemaining <= MaxStack) {
					ItemDistributor Ref;
					Ref.Slot = i;
					Ref.QuantityToFill = Items[i].Quantity + QuantityRemaining;
					AvailableSlots.Add(Ref);

					QuantityRemaining = 0;

					break;
				}
				else
				{
					ItemDistributor Ref;
					Ref.Slot = i;
					Ref.QuantityToFill = MaxStack;
					AvailableSlots.Add(Ref);

					QuantityRemaining = QuantityRemaining - (MaxStack - Items[i].Quantity);
				}
			}
			else { break; }
		}

		if (QuantityRemaining > 0) {
			while (QuantityRemaining > 0) {
				ItemDistributor Ref;
				Ref.CreateNewSlot = true;

				if (QuantityRemaining - MaxStack <= 0) {
					Ref.QuantityToFill = QuantityRemaining - MaxStack;
					QuantityRemaining = 0;

					break;
				}
				else {
					Ref.QuantityToFill = MaxStack;
					QuantityRemaining = QuantityRemaining - MaxStack;
				}

				AvailableSlots.Add(Ref);
			}
		}

		for (ItemDistributor Dist : AvailableSlots) {
			if (!Dist.CreateNewSlot) {
				Items[Dist.Slot].Quantity = Dist.QuantityToFill;
			}
			else {
				FItemData LocalizedData;
				LocalizedData = obj->Initialize(Dist.QuantityToFill, obj->Name);
				LocalizedData.Reference = Item;

				Items.Add(LocalizedData);

				CreatedNewStack = true;
			}
		}
	}
	else 
	{
		FItemData LocalizedData;
		LocalizedData = obj->Initialize(Quantity, obj->Name);
		LocalizedData.Reference = Item;

		Items.Add(LocalizedData);

		CreatedNewStack = true;
	}

	return CreatedNewStack;
}

//Simple function primarily used internally.
int AInventoryContainer::GetSlot(TSubclassOf<AItemBase> Item) {
	for (int i = 0; i < Items.Num(); i++) {
		if (Items[i].Reference == Item) {
			return i;
		}
	}

	return -1;
}

int AInventoryContainer::GetItemCount(TSubclassOf<AItemBase> Item) {
	if (GetSlot(Item) != -1) {
		int Count = 0;

		for (int i = 0; i < Items.Num(); i++) {
			if (Items[i].Reference == Item) {
				Count = Count + Items[i].Quantity;
			}
		}

		return Count;
	}
	else { return 0; }
}

bool AInventoryContainer::HasItem(TSubclassOf<AItemBase> Item) {
	return GetItemCount(Item) > 0;
}
