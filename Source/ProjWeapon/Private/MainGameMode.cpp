// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "MainGameStateBase.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "DiceRollWidget.h"

AMainGameMode::AMainGameMode()
{
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_KitePAwn"));
    if (PlayerPawnClassFinder.Succeeded()) {
        DefaultPawnClass = PlayerPawnClassFinder.Class;
        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
        if (PlayerController && PlayerController->GetPawn())
        {
            PlayerController->SetViewTarget(PlayerController->GetPawn());
        }
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> RollWidgetClassFinder(TEXT("/Game/Blueprints/BP_DiceRoll"));
    if (RollWidgetClassFinder.Succeeded())
    {
        RollWidgetClass = RollWidgetClassFinder.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> StartWidgetClassFinder(TEXT("/Game/Blueprints/BP_StartWidget"));
    if (StartWidgetClassFinder.Succeeded())
    {
        StartWidgetClass = StartWidgetClassFinder.Class;
    }


    GameStateClass = AMainGameStateBase::StaticClass();
}

void AMainGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (GameState)
    {
        AMainGameStateBase* MainGameState = Cast<AMainGameStateBase>(GameState);

        if (MainGameState)
        {
            const bool GameStatus = MainGameState->GetHasGameStarted();
            if (!GameStatus)
            {
                if (StartWidgetClass)
                {
                    StartWidgetInstance = CreateWidget<UUserWidget>(GetGameInstance(), StartWidgetClass);
                    if (StartWidgetInstance)
                    {
                        StartWidgetInstance->AddToViewport();
                    }
                }
            }
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("GameMode has started!"));

    // GetWorld()->GetFirstPlayerController()->Pause();

    // if (WidgetClass)
    // {
    //     WidgetInstance = CreateWidget<UUserWidget>(GetGameInstance(), WidgetClass);

    //     if (WidgetInstance)
    //     {
    //         WidgetInstance->AddToViewport();
    //     }
    // }

}

void AMainGameMode::StartLoop()
{
    if (StartWidgetInstance)
    {
        StartWidgetInstance->RemoveFromParent();
        StartWidgetInstance = nullptr;
    }

    GetWorld()->GetFirstPlayerController()->Pause();

    if (RollWidgetClass)
    {
        RollWidgetInstance = CreateWidget<UUserWidget>(GetGameInstance(), RollWidgetClass);
        RollWidgetInstance->AddToViewport();
    }
}