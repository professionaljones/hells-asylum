// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponModComponent.generated.h"


UENUM(BlueprintType)
enum EWeaponModType
{
	WM_None UMETA(DisplayName = "No Mod"),
	WM_FireAmmo UMETA(DisplayName = "Fire Ammo"),
	WM_IceAmmo UMETA(DisplayName = "Ice Ammo"),
	WM_Explosive UMETA(DisplayName = "Charged Reload"),
	WM_Corosivve UMETA(DisplayName = "Poison Ammo"),
	WM_Regen UMETA(DisplayName = "Regenerative Magazine")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELLSASYLUM_API UWeaponModComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponModComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Mods")
		bool bIsSlotOneEnabled = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Mods")
		bool bIsSlotTwoEnabled = false;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Mod Slots")
		TEnumAsByte<EWeaponModType> ModSlotOne = WM_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Mod Slots")
		TEnumAsByte<EWeaponModType> ModSlotTwo = WM_None;

		
};
