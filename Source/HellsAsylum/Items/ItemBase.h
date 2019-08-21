// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UENUM(BlueprintType)
enum EItemType
{
	IT_None UMETA(DisplayName = "None"),
	IT_Key UMETA(DisplayName = "Key"),
	IT_StoryKey UMETA(DisplayName = "Story Key"),
	IT_Health UMETA(DisplayName = "Health Recovery"),
	IT_Shield UMETA(DisplayName = "Shield Recovery"),
	IT_Aragon UMETA(DisplayName = "Aragon Recovery"),
	IT_PowerBoost UMETA(DisplayName = "Suit Cooldown Boost")

};

UCLASS()
class HELLSASYLUM_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
		TEnumAsByte<EItemType> ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
		int32 KeyItemNum = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|Properties")
		bool bIsKeyItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|Properties")
		bool bIsItemStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
		float HealthRecoverAmount = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
		float ShieldRecoverAmount = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
		float AragonRecoverAmount = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
		float CooldownModifierAmount = 0.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
