// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletProjectile.generated.h"

class UProjectileMovementComponent;
class UBoxComponent;

UCLASS()
class ABulletProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to initialize the velocity of the bullet
	void InitializeVelocity(const FVector& Direction);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Box collider
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxCollisionComponent;

	// Static mesh
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	// Projectile component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* ProjectileComponent;

};
