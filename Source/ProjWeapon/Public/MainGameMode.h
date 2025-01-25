// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS()
class PROJWEAPON_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMainGameMode();

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	void StartLoop();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> RollWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> StartWidgetClass;

	UPROPERTY()
    UUserWidget* RollWidgetInstance;

	UPROPERTY()
    UUserWidget* StartWidgetInstance;

protected:
	virtual void BeginPlay() override;
};
