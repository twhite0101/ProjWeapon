// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MainGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJWEAPON_API AMainGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AMainGameStateBase();

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	bool GetHasGameStarted() const;

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	virtual void SetHasGameStarted(bool GameStatus);

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	int32 GetRound() const;

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	virtual void SetRound(int32 NewRound);

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	int32 GetStartingEnemyAmount() const;

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	virtual void SetStartingEnemyAmount(int32 NewAmount);

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	int32 GetCurrentEnemyAmount() const;

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	virtual void SetCurrentEnemyAmount(int32 NewAmount);

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	bool GetRoundEndStatus() const;
	
	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	virtual void SetRoundEndStatus(bool NewStatus);

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	bool GetRoundStartStatus() const;
	
	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	virtual void SetRoundStartStatus(bool NewStatus);

private:
	UPROPERTY(VisibleAnywhere, Category = "Game Logic")
	bool HasGameStarted;

	UPROPERTY(VisibleAnywhere, Category = "Game Logic")
	int32 CurrentRound;

	UPROPERTY(VisibleAnywhere, Category = "Game Logic")
	int32 StartingEnemyAmount;

	UPROPERTY(VisibleAnywhere, Category = "Game Logic")
	int32 CurrentEnemyAmount;

	UPROPERTY(VisibleAnywhere, Category = "Game Logic")
	bool HasRoundStarted;

	UPROPERTY(VisibleAnywhere, Category = "Game Logic")
	bool HasRoundEnded;
	
};
