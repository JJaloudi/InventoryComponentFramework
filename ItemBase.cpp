// Fill out your copyright notice in the Description page of Project Settings.

#include "rpg.h"
#include "ItemBase.h"


// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
}

FItemData AItemBase::Initialize(int amt, FText UName) {
	FItemData LocalizedData;
	LocalizedData.Quantity = amt;
	LocalizedData.UniqueName = UName;
	LocalizedData.Reference = StaticClass();

	return LocalizedData;
}

void AItemBase::OnItemUse_Implementation(AInventoryContainer* Container, int Slot, int ActionIndex, FItemData Data) {

}

// Called every frame
void AItemBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
