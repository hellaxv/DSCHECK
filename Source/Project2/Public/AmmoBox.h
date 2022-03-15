// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "AmmoBox.generated.h"

UCLASS()
class PROJECT2_API AAmmoBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoBox();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UBoxComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* Mesh;

	//коробку 1 раз подобрали.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Ammo params")
	TSubclassOf<ACannon> CannonClass;
	//коробка уничтожалась, после взятия.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Ammo params")
	bool bInfinite = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

};
