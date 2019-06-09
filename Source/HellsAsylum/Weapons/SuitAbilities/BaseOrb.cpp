// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED


#include "BaseOrb.h"
#include "Character/Player/AsylumPlayerCharacter.h"


// Sets default values
ABaseOrb::ABaseOrb()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OrbRoot = CreateDefaultSubobject<USceneComponent>(TEXT("OrbRoot"));
	RootComponent = OrbRoot;
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	SphereMesh->SetupAttachment(RootComponent);
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSystem->SetupAttachment(SphereMesh);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(SphereMesh);
	ProjMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjMovementComponent"));

	ProjMovementComponent->InitialSpeed = OrbInitialSpeed;
	ProjMovementComponent->MaxSpeed = OrbMaxSpeed;
	ProjMovementComponent->bRotationFollowsVelocity = true;
	ProjMovementComponent->ProjectileGravityScale = 0.0f;
	//ProjMovementComponent->Velocity = OrbVelocity;

	EndLocation = GetActorLocation() + (GetActorLocation() * ForwardVectorMod);
}

// Called when the game starts or when spawned
void ABaseOrb::BeginPlay()
{
	Super::BeginPlay();
	/*UGameplayStatics::GetAllActorsWithInterface(this, AECInterface, HarmonyActorsToIgnore);
	UGameplayStatics::GetAllActorsWithInterface(this, APInterface, DespairActorsToIgnore);*/

	//GetWorldTimerManager().SetTimer(QuickSilverHandle, this, &AAsylumPlayerCharacter::OnQuicksilverConsumption, 0.01f, true);

	if (bIsDespair)
	{
		SearchForEnemies();
		GetWorldTimerManager().SetTimer(DespairOrbTimer, this, &ABaseOrb::SearchForEnemies, DespairDamageRate, true);
	}
	else
	{
		SearchForPlayer();
		GetWorldTimerManager().SetTimer(HarmonyOrbTimer, this, &ABaseOrb::SearchForPlayer, HarmonyHealRate, true);
	}

}

// Called every frame
void ABaseOrb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseOrb::SearchForEnemies()
{

	AActor* HitActor = DespairHitResult.GetActor();

	if (UKismetSystemLibrary::SphereTraceSingleForObjects(this, GetActorLocation(), EndLocation, DespairTraceRadius, DespairTargets, false, HarmonyActorsToIgnore, EDrawDebugTrace::None, DespairHitResult, true, FLinearColor::Red, FLinearColor::Green, 5.0f))
	{
		if (DespairHitResult.bBlockingHit && IsValid(HitActor))
		{
			if (bShouldAttractEnemies)
			{
				if (this->SetActorLocation(UKismetMathLibrary::VInterpTo(GetActorLocation(), HitActor->GetActorLocation(), UGameplayStatics::GetWorldDeltaSeconds(this), 5.0f), false, nullptr, ETeleportType::None))
				{
					UGameplayStatics::ApplyDamage(HitActor, DamageAmount, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, NULL);
				}

			}
			else
			{
				UGameplayStatics::ApplyDamage(HitActor, DamageAmount, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, NULL);
			}
			if (ProjMovementComponent)
			{
				ProjMovementComponent->Velocity = (GetActorLocation() * ProjMovementComponent->InitialSpeed);
				ProjMovementComponent->UpdateComponentVelocity();
			}
			
		}
	}
}

void ABaseOrb::SearchForPlayer()
{
	AActor* HitActor = HarmonyHitResult.GetActor();
	AAsylumPlayerCharacter* PC = Cast<AAsylumPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (UKismetSystemLibrary::SphereTraceSingleForObjects(this, GetActorLocation(), EndLocation, HarmonyTraceRadius, HarmonyTargets, false, DespairActorsToIgnore, EDrawDebugTrace::None, HarmonyHitResult, true, FLinearColor::Red, FLinearColor::Green, 5.0f))
	{
		if (HarmonyHitResult.bBlockingHit && IsValid(HitActor))
		{
			if (this->SetActorLocation(UKismetMathLibrary::VInterpTo(GetActorLocation(), HitActor->GetActorLocation(), UGameplayStatics::GetWorldDeltaSeconds(this), 5.0f), false, nullptr, ETeleportType::None))
			{
				if (PC->GetClass()->ImplementsInterface(UAsylumPlayerInterface::StaticClass()))
				{
					PC->Execute_OnRecoverHealth(PC, HealAmount);

				}
			}
		}
	}
}

