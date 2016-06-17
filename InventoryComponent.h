// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemBase.h"
#include "GameFramework/Actor.h"
#include "InventoryComponent.generated.h"

UCLASS()
class STICKRPG_API AInventoryComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	AInventoryComponent();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItem(TSubclassOf<AItemBase> Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int GetSlot(TSubclassOf<AItemBase> Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int GetItemCount(TSubclassOf<AItemBase> Item);

private:
	TArray<AItemBase> Items;

};
