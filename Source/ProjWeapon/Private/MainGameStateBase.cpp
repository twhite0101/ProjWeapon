// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameStateBase.h"

AMainGameStateBase::AMainGameStateBase()
{
    HasGameStarted = false;
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