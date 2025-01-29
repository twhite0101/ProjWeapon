// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "KitePawn.generated.h"

class UInputMappingContext;
class UInputAction;
class UBoxComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class AKitePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AKitePawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AddForce(int32 Force);

	void SetTargetPoints(const TArray<FVector>& Points);

	void SetMoveSpeed(const int32 Velocity);

	float GetDefaultMoveSpeed() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Create pointer to input mapping context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* CharMappingContext;

	// Create pointer to input action for movement
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxCollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<AActor> BulletBP;

	// Create function to call when the Equip Input Action (E key) event is triggered
	void MouseClicked(const FInputActionValue& Value);

	// Create bullet BP
	void SpawnBullet();

private:	
	TArray<FVector> TargetPoints;

	int32 CurrentTargetIndex = 0;

	bool bIsMoving = false;

	float DefaultMoveSpeed = 200.0f;

	float CurrentMoveSpeed;

	float StopDistance = 10.0f;

};
