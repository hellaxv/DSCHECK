// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SprayProjectile.generated.h"

UCLASS()
class PROJECT2_API ASprayProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprayProjectile();

	//S-приставка, запомнить!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USphereComponent* Collisions;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* Cash;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Spray Projectile")
	float MoveSpeeds = 500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Spray Projectile")
	float MoveRates = 0.05;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Spray Projectile")
	float Damages = 0.2;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FTimerHandle Times;

	UFUNCTION()
	void OnBeginOverLaps(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	void MoveTicks();
/*
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
*/

};
