// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

class AItemBase;

USTRUCT(BlueprintType)
struct FItemData {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FText UniqueName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<AItemBase> Reference;
};

UCLASS()
class RPG_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "On Item Used"), Category = "Item Events")
	void OnItemUse( AInventoryContainer* Container, int Slot, int ActionIndex, FItemData Data);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	int UID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	int MaxStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	bool Stackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Defaults")
	int DefaultStack = 1;

	FItemData Initialize(int Stack, FText UName);
};
