// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "MainGameStateBase.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "DiceRollWidget.h"
#include "KitePawn.h"

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
                // RollWidgetInstance = nullptr;
                MainGameState->SetRoundStartStatus(true);
                GetWorld()->GetFirstPlayerController()->SetPause(false);
                StartRound();
            }
        }
    }
}

void AMainGameMode::StartRound()
{
    AMainGameStateBase* MainGameState = Cast<AMainGameStateBase>(GameState);
    if (MainGameState && MainGameState->GetRoundStartStatus())
    {
        // Get values for Velocity, Arc, Start Point and End Point, and assign them locally
        int32 Velocity = RollWidgetInstance->GetVelcoity();
        int32 Arc = RollWidgetInstance->GetArc();
        FVector Start = MainGameState->GetStartPoint();
        FVector End = MainGameState->GetEndPoint();

        // Create the curve path
        // Currently draws debug line to confirm path was correctly done but will be removed as dev progersses
        CreateCurveAndMove(GetWorld(), Start, End, Arc, 20);
    }
}

// Quadradic Bezier curve is defined by three control points: start, end, and a control point (which determines the curve's shape)
// Formula as a reminder for future use: P(t) = (1 - t)^2 * P0 + 2(1 = t)t * P1 + t^2 * P2
// P0 is the starting point, P1 is the control point, P2 is the end point, and t ranges from 0 to 1
FVector AMainGameMode::CalculateBezierPoint(const FVector& Start, const FVector& Control, const FVector& End, float T)
{
    float TDifference = 1.0f - T;
    return (TDifference * TDifference * Start) + (2.0f * TDifference * T * Control) + (T * T * End);
}

// Generate perpendicular vector point on the Z axis based on the Arc value rolled
FVector AMainGameMode::GetControlPoint(const FVector& Start, const FVector& End, int32 Curve)
{
    // Generate mid point vector between the Start and End points
    FVector Mid = (Start + End) * 0.5f;

    // Modify Z-axis value of mid point vector based on the Arc value
    // Multiply Arc value by 0.17 (equvalent of 1/6 to simulate weight of the dice roll)
    // Multiply that product by the value of the Z-axis on the mid point
    // Add that value to the current Z-axis value of the mid point
    // Set the value of the Z-axis mid point to that sum
    Mid.Z = Mid.Z + (Mid.Z * (Curve * 0.17f));

    // Return the FVector of the mid point
    return Mid;
}

// Generate points that would map out the curve of the line path between the player start and the end point
TArray<FVector> AMainGameMode::GenerateCurvePoints(const FVector& Start, const FVector& End, int32 Curvature, int32 NumSegments)
{
    // Create array of vector points
    TArray<FVector> CurvePoints;

    // Generate the control point via the GetControlPoint function created
    FVector ControlPoint = GetControlPoint(Start, End, Curvature);

    // Complete for loop based on the NumSegments param provided
    for (int32 i = 0; i <= NumSegments; i++)
    {
        // Generate T by converting i to a float and dividing it by NumSegments
        float T = static_cast<float>(i) / NumSegments;
        // Call CalculateBezierPoint to generate a curvature point, passing in Start, ControlPoint, End, and T
        FVector Point = CalculateBezierPoint(Start, ControlPoint, End, T);
        // Add the point to the CurvePoints array
        CurvePoints.Add(Point);
    }

    // Return the CurvePoints Array
    return CurvePoints;
}

// Draws debug line based on curve points to confirm curve was calculated correctly
void AMainGameMode::DrawCurve(const TArray<FVector>& CurvePoints, UWorld* World, const FVector& End)
{
    for (int32 i = 0; i < CurvePoints.Num(); i++)
    {
        if (i + 1 < CurvePoints.Num())
        {
            DrawDebugLine(World, CurvePoints[i], CurvePoints[i + 1], FColor::Green, false, 5.0f, 0, 2.0f);
        }
        else if (i + 1 == CurvePoints.Num())
        {
            DrawDebugLine(World, CurvePoints[i], End, FColor::Green, false, 5.0f, 0, 2.0f);
        }
    }
}

// Creates target points along a curved line for kite pawn to travel on and then sets target points in kite pawn to trigger movement
// Also still draws debug line but will be removed
void AMainGameMode::CreateCurveAndMove(UWorld* CurrentWorld, const FVector& Start, const FVector& End, int32 Curvature, int32 NumSegments)
{
    // Create array of target points along a curve by calling GenerateCurvePoints local function
    // Create pointer for kite pawn
    TArray<FVector> CurvePoints = GenerateCurvePoints(Start, End, Curvature, NumSegments);
    AKitePawn* KitePawn = Cast<AKitePawn>(UGameplayStatics::GetPlayerPawn(this, 0));
    // Check if kite pawn was successfully cast to pointer
    if (KitePawn)
    {
        // If successful, set current movement speed on kite pawn by passing in the product of the kite's default movement speed and the rolled velocity
        // Then, set the target points in the kite pawn by passing in the CurvePoints array
        KitePawn->SetMoveSpeed((KitePawn->GetDefaultMoveSpeed() * RollWidgetInstance->GetVelcoity()));
        KitePawn->SetTargetPoints(CurvePoints);
    }
    //Draw debug lien curve for path confirmation
    DrawCurve(CurvePoints, CurrentWorld, End);
}
