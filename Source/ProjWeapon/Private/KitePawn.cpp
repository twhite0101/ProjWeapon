// Fill out your copyright notice in the Description page of Project Settings.


#include "KitePawn.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "BulletProjectile.h"

// Sets default values
AKitePawn::AKitePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach box collision component to Kite pawn as root component
	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComponent"));
	RootComponent = BoxCollisionComponent;

	// Create static mesh component and attach to root component (box collider)
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	FRotator StaticMeshRotator = FRotator(0.0f, 90.0f, 0.0f);

	StaticMeshComponent->SetRelativeRotation(StaticMeshRotator);

	// Create spring arm and camera, and attach to root component
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(StaticMeshComponent);

	// Set spring arm length
	SpringArmComp->TargetArmLength = 900.0f;

	// Rotate spring arm to have side presentation
	FRotator NewRotation = FRotator(0.0f, 0.0f, 180.0f);
	SpringArmComp->SetRelativeRotation(NewRotation);

	// Create camera component and attach to spring arm
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	// Get and set reference to bullet BP
	static ConstructorHelpers::FClassFinder<ABulletProjectile> BlueprintClass(TEXT("/Content/Blueprints/BP_Bullet"));
	if (BlueprintClass.Succeeded())
	{
		BulletBP = BlueprintClass.Class;
	}
}

// Called when the game starts or when spawned
void AKitePawn::BeginPlay()
{
	Super::BeginPlay();
	 
}

void AKitePawn::MouseClicked(const FInputActionValue& Value)
{
	SpawnBullet();
	// Logs that LMB was pressed
	UE_LOG(LogTemp, Warning, TEXT("Mouse Clicked"));

	const int8 Min = 1;
	const int8 Max = 7;

	const int8 RandNum = FMath::RandRange(Min, Max);

	UE_LOG(LogTemp, Warning, TEXT("%d"), RandNum);

}

void AKitePawn::SpawnBullet()
{
	if (BulletBP)
	{
		// Get the location of the projectile socket on the static mesh and the kite's rotation
		FVector SocketLocation = StaticMeshComponent->GetSocketLocation(FName("ProjectilePoint"));
		FRotator SpawnRotation = GetActorRotation();

		// Create spawn params and assign values to properties
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		// Spawn bullet blueprint
		ABulletProjectile* SpawnedBullet = GetWorld()->SpawnActor<ABulletProjectile>(BulletBP, SocketLocation, SpawnRotation, SpawnParams);
		if (SpawnedBullet)
		{
			// Assign launch direction to bullet projectile
			FVector LaunchDirection = GetActorTransform().GetRotation().RotateVector(FVector::DownVector);
			SpawnedBullet->InitializeVelocity(LaunchDirection);
			UE_LOG(LogTemp, Log, TEXT("Successfully spawned a copy of the bullet!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Bullet BP is not set!"));
	}
}

// Called every frame
void AKitePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if kite pawn is currently moving and if the current index of the target points is valid
	if (bIsMoving && TargetPoints.IsValidIndex(CurrentTargetIndex))
	{
		// If so, get the kite pawn's current location and get the target location based on the current indexed element in the points array
		FVector CurrentLocation = GetActorLocation();
		FVector TargetLocation = TargetPoints[CurrentTargetIndex];

		// Assign the new location by interpolating the kite's current location, the taget location, deltatime and the current move speed
		// Current move speed should be assigned in gamemode before setting target points
		// Then set kite's new location
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, CurrentMoveSpeed);
		SetActorLocation(NewLocation);

		// Check if distance between the current location of the kite and the target point are less than or equal to the Stop distance
		if (FVector::Dist(CurrentLocation, TargetLocation) <= StopDistance)
		{
			// if so, increase the current target index by one
			CurrentTargetIndex++;

			// If the current target index is greater than or equal to the number of target points, then stop moving
			if (CurrentTargetIndex >= TargetPoints.Num())
			{
				bIsMoving = false;
			}
		}
	}

}

// Called to bind functionality to input
void AKitePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = CastChecked<APlayerController>(Controller))
	{
		UE_LOG(LogTemp, Warning, TEXT("Success"))
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(CharMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AKitePawn::MouseClicked);
	}

}

void AKitePawn::AddForce(int32 Force)
{
	if (BoxCollisionComponent)
	{
		float ForceFloat = static_cast<float>(Force);
		BoxCollisionComponent->AddForce(FVector(ForceFloat, 0.0f, 0.0f), NAME_None, true);
	}
}

// Setter for target points of path for kite to travel on
void AKitePawn::SetTargetPoints(const TArray<FVector>& Points)
{
	TargetPoints = Points;
	CurrentTargetIndex = 0;

	if (TargetPoints.Num() > 0)
	{
		bIsMoving = true;
	}
}

// Setter for the current move speed
void AKitePawn::SetMoveSpeed(const int32 Velocity)
{
	CurrentMoveSpeed = Velocity;
}

// Getter for the default move speed
float AKitePawn::GetDefaultMoveSpeed() const
{
	return DefaultMoveSpeed;
}
