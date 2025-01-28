// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameStateBase.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

AMainGameStateBase::AMainGameStateBase()
{
    // Set game start to false to ensure game loop hasn't begun yet
    HasGameStarted = false;

    // Get PlayerStart and assign its FVector location to StartPoint
    TArray<AActor*> PlayerStarts;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

    if (PlayerStarts.Num() > 0)
    {
        APlayerStart* KitePlayerStart = Cast<APlayerStart>(PlayerStarts[0]);
        if (KitePlayerStart)
        {
            StartPoint = KitePlayerStart->GetActorLocation();
        }
    }

    //Get End Point object in world and assign its FVector location to EndPoint
    TArray<AActor*> EndPoints;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("EndPoint"), EndPoints);

    if (EndPoints.Num() > 0)
    {
        AActor* EndObject = Cast<AActor>(EndPoints[0]);
        if (EndObject)
        {
            EndPoint = EndObject->GetActorLocation();
        }
    }
}

bool AMainGameStateBase::GetHasGameStarted() const
{
    return HasGameStarted;
}

void AMainGameStateBase::SetHasGameStarted(bool GameStatus)
{
    HasGameStarted = GameStatus;
}

int32 AMainGameStateBase::GetRound() const
{
    return CurrentRound;
}

void AMainGameStateBase::SetRound(int32 NewRound)
{
    CurrentRound = NewRound;
}

int32 AMainGameStateBase::GetStartingEnemyAmount() const
{
    return StartingEnemyAmount;
}

void AMainGameStateBase::SetStartingEnemyAmount(int32 NewAmount)
{
    StartingEnemyAmount = NewAmount;
}

int32 AMainGameStateBase::GetCurrentEnemyAmount() const
{
    return CurrentEnemyAmount;
}

void AMainGameStateBase::SetCurrentEnemyAmount(int32 NewAmount)
{
    CurrentEnemyAmount = NewAmount;
}

bool AMainGameStateBase::GetRoundEndStatus() const
{
    return HasRoundEnded;
}

void AMainGameStateBase::SetRoundEndStatus(bool NewStatus)
{
    HasRoundEnded = NewStatus;
}

bool AMainGameStateBase::GetRoundStartStatus() const
{
    return HasRoundStarted;
}

void AMainGameStateBase::SetRoundStartStatus(bool NewStatus)
{
    HasRoundStarted = NewStatus;
}

FVector AMainGameStateBase::GetStartPoint() const
{
    return StartPoint;
}

FVector AMainGameStateBase::GetEndPoint() const
{
    return EndPoint;
}