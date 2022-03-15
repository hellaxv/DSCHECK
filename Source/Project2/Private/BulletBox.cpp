// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletBox.h"

#include "Tank_Pawn.h"

// Sets default values
ABulletBox::ABulletBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = Collision;

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABulletBox::OnBeginOverlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABulletBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABulletBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Tank = Cast<ATank_Pawn>(OtherActor);
	if(Tank)
	{
		Tank->UploadAmmo(ShellCount);
	}
	if(!bInfinite)
	{
		Destroy();
	}
}

