// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

UCLASS()
class PROJECT2_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATurret();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UCapsuleComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USphereComponent* RangeSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UArrowComponent* CannonPosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Fire params")
	TSubclassOf<ACannon> CannonClass;

	UPROPERTY()
	ACannon* Cannon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Fire params")
	float TargetingSpeed = 0.01f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Fire params")
	float TargetingRate = 0.005f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Fire params")
	float AimSlack = 6;


	/*создаются они здесь, а переносим их в протектед, так как это делегаты.
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult);
	*/

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:

	void FindNextTarget();
	void Fire();
	void Targeting();

	//хранение врагов//TWeakObjectPtr-это специальный указатель на объект, который может хранить указатель на "Actor" или на любой "UObject" и его наследники и при этом знать уничтожен ли этот объект или нет.
	//если мы уничтожим объект, TWeakObjectPtr<AActor> подскажет что данный объект, больше не существует.
	UPROPERTY()
	TArray<AActor*> OtherActors;
	TWeakObjectPtr<AActor> Target;
	

};


