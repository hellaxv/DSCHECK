// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"

#include "DrawDebugHelpers.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>("ProjectileSpawnPoint");
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
	//Mesh->SetupAttachment(RootComponent);
}

void ACannon::Shoot(int& AmmoTap)
{
	if (!bReadyToShoot)
		return;
	switch (Type)
	{
	case ECannonType::FireProjectile:
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, FString(TEXT("SHOOT")));
		GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
		AmmoTap--;
		GEngine->AddOnScreenDebugMessage(3, 666, FColor::Cyan, FString::Printf(TEXT("AMMOTAP - %i"),AmmoTap));
		break;
	case ECannonType::FireTrace:
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString(TEXT("TAPPED")));
		FHitResult Result;
		FCollisionObjectQueryParams Params;
		Params.AddObjectTypesToQuery(ECollisionChannel::ECC_Vehicle);
		Params.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
		Params.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
		auto Start = ProjectileSpawnPoint->GetComponentLocation();
		auto End = Start + ProjectileSpawnPoint->GetForwardVector() * FireRange;
		bool HasHit = GetWorld()->LineTraceSingleByObjectType(
			Result,
			Start,
			End,
			Params);
		if (HasHit)
		{
		    End = Result.Location;
		    if (Result.Actor.IsValid())
		    {
		    	Result.Actor->Destroy();
		    }
			
		}

		/*полный код того, что написано выше.
		bool HasHit = GetWorld()->LineTraceSingleByObjectType(
			Result,
			ProjectileSpawnPoint->GetComponentLocation(),
			ProjectileSpawnPoint->GetComponentLocation() + ProjectileSpawnPoint->GetForwardVector() * FireRange, Params);
		*/
		/*
		if (HasHit)
		{
			DrawDebugLine(GetWorld(), Start, Result.Location, FColor::Black, false, 0.1, 0, 10);
			//0.1 - время жизни трейса, 10-толщина трейса.
		}
		else
		{
			DrawDebugLine(GetWorld(), End, Result.Location, FColor::Black, false, 0.1, 0, 10);
		}
		*/
		
		DrawDebugLine(GetWorld(), Start, End, FColor::Black, false, 0.1, 0, 10);
		
		break;
	}
	bReadyToShoot = false;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle,FTimerDelegate::CreateUObject(this, &ACannon::ResetShootState), 1/FireRate, false);
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(12345, -1, FColor::Purple, FString::Printf(TEXT("RECHARDE %f"),GetWorld()->GetTimerManager().GetTimerElapsed(TimerHandle)));

}

void ACannon::ResetShootState()
{
	bReadyToShoot = true;
}

