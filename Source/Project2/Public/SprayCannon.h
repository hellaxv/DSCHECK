// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SprayProjectile.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "SprayCannon.generated.h"
UENUM()
enum class ESprayCannonType:uint8
{
	FireProjectiles = 0 UMETA(DisplayName = "Use projectiles"),
	FireTraces = 1 UMETA(DisplayName = "Use spray")
};

UCLASS()
class PROJECT2_API ASprayCannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprayCannon();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* Cash;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UArrowComponent* ProjectileSpawnPoints;

	//частота выстрела/скорость выстрела
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Fire params")
	float FireRateSpray = 0.2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Fire params")
	float FireRangeSpray = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Fire params")
	ESprayCannonType Types = ESprayCannonType::FireProjectiles;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Fire params")
	TSubclassOf<ASprayProjectile> SprayProjectileClass;

	void SprayShoot(int &AmmoSpray);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void ResetSprayShootState();

	FTimerHandle TimerPencil;
	bool bReadyToSprayShoot = true;
	

};
