// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

class UUserWidget;
class UDiceRollWidget;
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

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	void SetVelocityAndArc();

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	void StartRound();

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	FVector CalculateBezierPoint(const FVector& Start, const FVector& Control, const FVector& End, float T);

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	FVector GetControlPoint(const FVector& Start, const FVector& End, int32 Curve);

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	TArray<FVector> GenerateCurvePoints(const FVector& Start, const FVector& End, int32 Curvature, int32 NumSegments);

	UFUNCTION(BlueprintCallable, Category = "Debug")
	void DrawCurve(const TArray<FVector>& CurvePoints, UWorld* World, const FVector& End);

	UFUNCTION(BlueprintCallable, Category = "Debug")
	void CreateAndDrawCurve(UWorld* CurrentWorld, const FVector& Start, const FVector& End, int32 Curvature, int32 NumSegments);

	UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> RollWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> StartWidgetClass;

	UPROPERTY()
    UDiceRollWidget* RollWidgetInstance;

	UPROPERTY()
    UUserWidget* StartWidgetInstance;

protected:
	virtual void BeginPlay() override;
};
