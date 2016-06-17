// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ItemBase.h"
#include "InventoryContainer.generated.h"

struct ItemDistributor {
	int Slot;
	int QuantityToFill;
	bool CreateNewSlot;
};

UCLASS()
class RPG_API AInventoryContainer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryContainer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Item Data")
	TArray<FItemData> Items;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	bool HasItem(TSubclassOf<AItemBase> Item);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	int GetSlot(TSubclassOf<AItemBase> Item);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	int GetItemCount(TSubclassOf<AItemBase> Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(TSubclassOf<AItemBase> Item, int Quantity);

	//UPROPERTY(BlueprintNativeEvent)
};
