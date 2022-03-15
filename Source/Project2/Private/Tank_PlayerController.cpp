// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank_PlayerController.h"

#include "DrawDebugHelpers.h"
#include "Tank_Pawn.h"

void ATank_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATank_PlayerController::OnMoveForward);
	InputComponent->BindAxis("RoteitRigth", this, &ATank_PlayerController::OnRotateRight);
	InputComponent->BindAction("Shoot", IE_Repeat, this, &ATank_PlayerController::OnShoot);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &ATank_PlayerController::OnShoot);
	InputComponent->BindAction("SprayShoot", IE_Repeat, this, &ATank_PlayerController::OnSprayShoot);
	InputComponent->BindAction("SwapWeapon", IE_Pressed, this, &ATank_PlayerController::OnSwapWeapon);

	

	/*для выстрелов подобно автомату
	InputComponent->BindAction("Shoot", IE_Repeat, this, &ATank_PlayerController::OnShoot);
	*/
	bShowMouseCursor = true;
}

void ATank_PlayerController::OnMoveForward(float Value)
{
	if (PlayerTank)
		PlayerTank->MoveForward(Value);
}

void ATank_PlayerController::OnRotateRight(float Value)
{
	if(PlayerTank)
		PlayerTank->RotateRight(Value);
}

void ATank_PlayerController::OnShoot()
{
	if(PlayerTank)
		PlayerTank->Shoot();
}

void ATank_PlayerController::OnSprayShoot()
{
	if(PlayerTank)
		PlayerTank->SprayShoot();
}

void ATank_PlayerController::OnSwapWeapon()
{
	if(PlayerTank)
		PlayerTank->Swap();
}

void ATank_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	PlayerTank=CastChecked<ATank_Pawn>(GetPawn());
}

void ATank_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector MousePosition, MouseDirection;
	DeprojectMousePositionToWorld(MousePosition, MouseDirection);

	auto Z = FMath::Abs(PlayerTank->GetActorLocation().Z - MousePosition.Z);
	MouseWorldPosition = MousePosition - MouseDirection * Z / MouseDirection.Z;

	/*когда курсор зеленый держится на уровне танка
	DrawDebugSphere(GetWorld(), MousePosition, 3, 16, FColor::Silver);
	DrawDebugLine(GetWorld(), MousePosition, MousePosition + MouseDirection * 5000, FColor::Silver);
	DrawDebugSphere(GetWorld(), MouseWorldPosition, 3, 16, FColor::Green);
	*/

	/*математический метод, который врезает точку либо в ландшафт, либо в танк при настроенной коллизии самого танка
	FHitResult Result;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Result);
	DrawDebugSphere(GetWorld(), Result.ImpactPoint, 3, 16, FColor::Green);
	*/
}
