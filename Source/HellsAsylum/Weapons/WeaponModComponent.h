// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponModComponent.generated.h"


UENUM(BlueprintType)
enum EWeaponOffenseModType
{
	WOM_None UMETA(DisplayName = "No Mod"),
	WOM_FireAmmo UMETA(DisplayName = "Fire Ammo"),
	WOM_IceAmmo UMETA(DisplayName = "Ice Ammo"),
	WOM_Explosive UMETA(DisplayName = "Charged Reload"),
	WOM_Corosivve UMETA(DisplayName = "Poison Ammo"),
};

UENUM(BlueprintType)
enum EWeaponSupportModType
{
	WSM_None UMETA(DisplayName = "No Mod"),
	WSM_Regen UMETA(DisplayName = "Regenerative Magazine"),

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
		TEnumAsByte<EWeaponOffenseModType> ModSlotOne = WOM_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Mod Slots")
		TEnumAsByte<EWeaponSupportModType> ModSlotTwo = WSM_None;

		
};
