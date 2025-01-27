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
    // Set default player pawn to kite BP
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_KitePAwn"));
    if (PlayerPawnClassFinder.Succeeded()) {
        DefaultPawnClass = PlayerPawnClassFinder.Class;
        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
        if (PlayerController && PlayerController->GetPawn())
        {
            PlayerController->SetViewTarget(PlayerController->GetPawn());
        }
    }

    // Set Dice Roll Widget BP class to pointer
    static ConstructorHelpers::FClassFinder<UDiceRollWidget> RollWidgetClassFinder(TEXT("/Game/Blueprints/BP_DiceRoll"));
    if (RollWidgetClassFinder.Succeeded())
    {
        RollWidgetClass = RollWidgetClassFinder.Class;
    }

    // Set Start Widget BP class to pointer
    static ConstructorHelpers::FClassFinder<UUserWidget> StartWidgetClassFinder(TEXT("/Game/Blueprints/BP_StartWidget"));
    if (StartWidgetClassFinder.Succeeded())
    {
        StartWidgetClass = StartWidgetClassFinder.Class;
    }

    // Set Game State Class
    GameStateClass = AMainGameStateBase::StaticClass();
}

void AMainGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (GameState)
    {
        // Cast Game State to pointer
        AMainGameStateBase* MainGameState = Cast<AMainGameStateBase>(GameState);

        if (MainGameState)
        {
            // Check if game has started yet
            const bool GameStatus = MainGameState->GetHasGameStarted();
            if (!GameStatus)
            {
                // Check if Start Widget was successfully set
                if (StartWidgetClass)
                {
                    // Create instance of Start Widget and set it to the StartWidgetInstance ptr
                    StartWidgetInstance = CreateWidget<UUserWidget>(GetGameInstance(), StartWidgetClass);
                    if (StartWidgetInstance)
                    {
                        // Add Start Widget to Viewport
                        StartWidgetInstance->AddToViewport();
                    }
                }
            }
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("GameMode has started!"));

}

// Function to handle Start Widget logic
void AMainGameMode::StartLoop()
{
    // Check if Start Widget Instance was set and present
    if (StartWidgetInstance)
    {
        // Remove Start Widget from Viewport and clean up ptr
        StartWidgetInstance->RemoveFromParent();
        StartWidgetInstance = nullptr;
    }

    // Pause game world
    GetWorld()->GetFirstPlayerController()->SetPause(true);

    // Check if Dice Roll Class was set successfully
    if (RollWidgetClass)
    {
        // Create Dice Roll Widget instance and set to ptr
        // Add to viewport
        // Set body text and button text
        RollWidgetInstance = CreateWidget<UDiceRollWidget>(GetGameInstance(), RollWidgetClass);
        RollWidgetInstance->AddToViewport();
        RollWidgetInstance->SetBodyText(FString("Roll for Velocity"));
        RollWidgetInstance->SetButtonText(FString("ROLL"));
    }
}

// Function to handle setting velocity and arc for upcoming round
void AMainGameMode::SetVelocityAndArc()
{
    // Check if GameState class is successfully set
    if (GameState)
    {
        // Cast Game State to ptr
        AMainGameStateBase* MainGameState = Cast<AMainGameStateBase>(GameState);

        // Get round status and confirm it hasn't started yet and Dice Roll Instance ptr isn't null
        const bool HasRoundStarted = MainGameState->GetRoundStartStatus();
        if (!HasRoundStarted && RollWidgetInstance)
        {
            // Check if Velocity was set yet
            if (RollWidgetInstance->GetVelcoity() == -1)
            {
                // If not, set velocity
                // Set velocity text in widget
                RollWidgetInstance->RollVelocity();
                const int32 Velocity = RollWidgetInstance->GetVelcoity();
                RollWidgetInstance->SetVelocityText(FString::FromInt(Velocity));
            }
            // Check if Arc was set yet
            else if (RollWidgetInstance->GetArc() == -1)
            {
                // If not, set arc
                // Set arc text in widget and update button text to Start Round
                RollWidgetInstance->RollArc();
                const int32 Arc = RollWidgetInstance->GetArc();
                RollWidgetInstance->SetArcText(FString::FromInt(Arc));
                RollWidgetInstance->SetButtonText(FString("START ROUND"));
            }
            // Check if both Velocity and Arc were set
            else
            {
                // If so, remove dice roll widget from viewport and clean up instance ptr
                // Set Round Start to true
                // Unpause world
                RollWidgetInstance->RemoveFromParent();
                RollWidgetInstance = nullptr;
                MainGameState->SetRoundStartStatus(true);
                GetWorld()->GetFirstPlayerController()->SetPause(false);
            }
        }
    }
}