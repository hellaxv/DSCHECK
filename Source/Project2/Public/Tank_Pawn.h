// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmmoBox.h"
#include "Cannon.h"
#include "SprayCannon.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Tank_Pawn.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS(Blueprintable)
class PROJECT2_API ATank_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank_Pawn();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UBoxComponent* BoxComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USkeletalMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USkeletalMeshComponent* MachineGunMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USpringArmComponent* ArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* CannonPosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* SprayCannonPosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Fire params")
	TSubclassOf<ACannon> CannonType;
	UPROPERTY()
	ACannon* Cannon;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Fire params")
	TSubclassOf<ASprayCannon> SprayCannonType;
	UPROPERTY()
	ASprayCannon* SprayCannon;

	
	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Move|Speed")
	float MoveSpeed = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Move|Speed")
	float RotationSpeed = 100;
*/
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MovementSpeed = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MovementAcceleration = 0.09;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float RotationSpeed = 90;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float RotationAcceleration = 0.09;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float TurretRotationAcceleration = 0.1;

	//UFUNCTION()
	void MoveForward (float Scale);
	//UFUNCTION()
	void RotateRight (float Scale);

	void Shoot();
	void SetupCannon(const TSubclassOf<ACannon>& CannonClass);

	
	void SprayShoot();
	void SetupCannonSpray(const TSubclassOf<ASprayCannon>& CannonClass);

	void Swap();
	int SwapWep = 0;

	void UploadAmmo(const int ShellCount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;
	
	/*доп.код для движения.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float InterpolationKey = 0.1f;
	float TargetRightAxisValue;
	float CurrentRightAxisValue;
	*/

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveTank(float DeltaTime);
	void RotateTank(float DeltaTime);
	void RotateCannon(float DeltaTime);

	float MoveScaleTarget = 0;
	float MoveScaleCurrent = 0;
	float RotationScaleTarget = 0;
	float RotationScaleCurrent = 0;

	int AmmoTap = 10;
	int AmmoSpray = 25;

	UPROPERTY()
	class ATank_PlayerController* TankController;
};
