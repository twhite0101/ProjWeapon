// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ABulletProjectile::ABulletProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// Bullet doesn't need to be called every frame so set to false
	PrimaryActorTick.bCanEverTick = false;

	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxCollisionComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	StaticMeshComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	StaticMeshComponent->SetupAttachment(RootComponent);

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	ProjectileComponent->InitialSpeed = 800.0f;
	ProjectileComponent->MaxSpeed = 800.0f;

}

// Called when the game starts or when spawned
void ABulletProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function to initialize the velocity of the bullet projectile
void ABulletProjectile::InitializeVelocity(const FVector& Direction)
{
	// Check if the projectile component was created successfully
	if (ProjectileComponent)
	{
		// If so, assign the direction param that was passed multiplied by the initial speed set when created
		ProjectileComponent->Velocity = Direction * ProjectileComponent->InitialSpeed;
		// Activate the projectile
		ProjectileComponent->Activate();
	}
}

