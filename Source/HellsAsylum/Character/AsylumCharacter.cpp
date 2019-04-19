// Fill out your copyright notice in the Description page of Project Settings.


#include "AsylumCharacter.h"
#include "Player/AsylumPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AAsylumCharacter::AAsylumCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LockOnActorsToIgnore.Add(this);
	//TValidLockOnObjects.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
}

// Called when the game starts or when spawned
void AAsylumCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAsylumCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAsylumCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AAsylumCharacter::IsInCombat() const
{
	AAsylumPlayerController* PCon = Cast<AAsylumPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (IsValid(CurrentEquippedWeapon))
	{
		if (bIsInCombat)
		{
			//bIsInCombat = true;
			return true;
		}
		else
		{
			return false;
		}

	}
	
		return false;
	
}

bool AAsylumCharacter::IsSelectingTarget() const
{
	return false;
}

AActor * AAsylumCharacter::GetCurrentTarget() const
{
	return nullptr;
}

FVector2D AAsylumCharacter::GetCurrentTargetSelectionInput() const
{
	return FVector2D();
}

void AAsylumCharacter::LockOn()
{
	FVector StartLocation = FollowCamera->GetComponentLocation();
	FVector ForwardVectorMod = FollowCamera->GetForwardVector() * fMaxLockOnDistance;
	FVector EndLocation = StartLocation + ForwardVectorMod;
	FHitResult LockOnHitResult;
	AActor* HitActor = LockOnHitResult.GetActor();

	if (UKismetSystemLibrary::SphereTraceSingleForObjects(this, StartLocation, EndLocation, fLockOnRadius, TValidLockOnObjects, true, LockOnActorsToIgnore, EDrawDebugTrace::ForDuration, LockOnHitResult, true, FLinearColor::Blue, FLinearColor::Yellow, 5.0f))
	{
		if (LockOnHitResult.bBlockingHit && IsValid(HitActor))
		{
			GLog->Log("Lock on target hit!");
		}
	}
}

