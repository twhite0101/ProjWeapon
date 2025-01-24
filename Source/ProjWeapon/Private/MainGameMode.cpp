// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "MainGameStateBase.h"

AMainGameMode::AMainGameMode()
{
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Content/Blueprints/BP_KitePAwn"));
    DefaultPawnClass = PlayerPawnClassFinder.Class;

    GameStateClass = AMainGameStateBase::StaticClass();
}

void AMainGameMode::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("GameMode has started!"));
}