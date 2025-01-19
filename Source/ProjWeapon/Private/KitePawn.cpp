// Fill out your copyright notice in the Description page of Project Settings.


#include "KitePawn.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/BoxComponent.h"

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
	StaticMeshComponent->SetupAttachment(BoxCollisionComponent);
}

// Called when the game starts or when spawned
void AKitePawn::BeginPlay()
{
	Super::BeginPlay();
	 
}

void AKitePawn::MouseClicked(const FInputActionValue& Value)
{
	// Logs that LMB was pressed
	UE_LOG(LogTemp, Warning, TEXT("Mouse Clicked"))
}

// Called every frame
void AKitePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

