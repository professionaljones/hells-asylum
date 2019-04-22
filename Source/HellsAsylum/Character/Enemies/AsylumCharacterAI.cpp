// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED


#include "AsylumCharacterAI.h"

AAsylumCharacterAI::AAsylumCharacterAI()
{
	EnemyStatsComponent = CreateDefaultSubobject<UAsylumStatsComponent>(TEXT("EnemyStatsComponent"));
	RaycastLocationComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RaycastLocationComponent"));
	RaycastLocationComponent->SetupAttachment(RootComponent);
}

void AAsylumCharacterAI::EnemyWeaponFire()
{

	////Collision parameters
	//FCollisionQueryParams CollisionParameters;
	//
	//if (IsValid(CurrentEquippedWeapon))
	//{
	//	AActor* HitActor = CurrentEquippedWeapon->SingleHit.GetActor();
	//	//Length of the ray in Unreal units
	//	float WeaponRange = CurrentEquippedWeapon->WeaponStatsData.WeaponDistanceRange;
	//	if (!CurrentEquippedWeapon->bIsReloading && CurrentEquippedWeapon->bCanWeaponFire)
	//	{
	//		if (CurrentEquippedWeapon->WeaponFireSound != NULL)
	//		{
	//			CurrentEquippedWeapon->WeaponAudioComponent->SetSound(CurrentEquippedWeapon->WeaponFireSound);
	//			CurrentEquippedWeapon->WeaponAudioComponent->Play();
	//		}
	//		CurrentEquippedWeapon->StartLocation = RaycastLocationComponent->GetComponentLocation();
	//		CurrentEquippedWeapon->EndLocation = CurrentEquippedWeapon->StartLocation + RaycastLocationComponent->GetForwardVector() * WeaponRange;
	//		//Single line trace
	//		if (GetWorld()->LineTraceSingleByObjectType(CurrentEquippedWeapon->SingleHit, CurrentEquippedWeapon->StartLocation, CurrentEquippedWeapon->EndLocation, CurrentEquippedWeapon->ObjectsToTarget, CollisionParameters))
	//		{

	//			//If we hit something and said target is what we are looking for
	//			if (CurrentEquippedWeapon->SingleHit.bBlockingHit && IsValid(HitActor))
	//			{
	//				//Apply damage
	//				UGameplayStatics::ApplyPointDamage(HitActor, CurrentEquippedWeapon->WeaponStatsData.DamageAmountSum, CurrentEquippedWeapon->SingleHit.ImpactPoint, CurrentEquippedWeapon->SingleHit, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, CurrentEquippedWeapon->WeaponStatsData.WeaponDamageType);
	//				
	//			}
	//		}
	//	}
	//}
}

float AAsylumCharacterAI::GetAIHealthPercentage()
{
	float StatPercentage = EnemyStatsComponent->CharacterStatsDataStruct.fCurrentHealth / EnemyStatsComponent->CharacterStatsDataStruct.fMaxHealth;
	return StatPercentage;
}

float AAsylumCharacterAI::GetAIShieldPercentage()
{
	float StatPercentage = EnemyStatsComponent->CharacterStatsDataStruct.fCurrentShield / EnemyStatsComponent->CharacterStatsDataStruct.fMaxShield;
	return StatPercentage;
}

float AAsylumCharacterAI::GetAIAragonPercentage()
{
	return 0.0f;
}
