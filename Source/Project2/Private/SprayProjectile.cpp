// Fill out your copyright notice in the Description page of Project Settings.


#include "SprayProjectile.h"

// Sets default values
ASprayProjectile::ASprayProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collisions = CreateDefaultSubobject<USphereComponent>("Collisions");
	RootComponent = Collisions;

	Collisions->OnComponentBeginOverlap.AddDynamic(this, &ASprayProjectile::OnBeginOverLaps);

	Cash = CreateDefaultSubobject<UStaticMeshComponent>("Cash");
	Cash->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASprayProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(Times, this, &ASprayProjectile::MoveTicks, MoveRates, true);
}

void ASprayProjectile::OnBeginOverLaps(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this)
		return;
	GetWorld()->GetTimerManager().ClearTimer(Times);
	Destroy();
	OtherActor->Destroy();
}

void ASprayProjectile::MoveTicks()
{
	auto Locations = GetActorLocation();
	SetActorLocation(Locations + GetActorForwardVector() * MoveRates * MoveSpeeds, true);
}

/*
// Called every frame
void ASprayProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/
