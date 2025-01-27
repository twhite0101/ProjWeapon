#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DiceRollWidget.generated.h"

UCLASS(Abstract)
class UDiceRollWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Dice Roll")
    FText GetBodyText() const;

    UFUNCTION(BlueprintCallable, Category = "Dice Roll")
    void SetBodyText(FString NewText);

    UFUNCTION(BlueprintCallable, Category = "Dice Roll")
    FText GetButtonText() const;

    UFUNCTION(BlueprintCallable, Category = "Dice Roll")
    void SetButtonText(FString NewText);

    UFUNCTION(BlueprintCallable, Category = "Dice Roll")
    FText GetVelocityText() const;

    UFUNCTION(BlueprintCallable, Category = "Dice Roll")
    void SetVelocityText(FString NewText);

    UFUNCTION(BlueprintCallable, Category = "Dice Roll")
    FText GetArcText() const;

    UFUNCTION(BlueprintCallable, Category = "Dice Roll")
    void SetArcText(FString NewText);

    UFUNCTION(BlueprintCallable, Category = "Dice Roll")
    void RollVelocity();

    UFUNCTION(BlueprintCallable, Category = "Dice Roll")
    int32 GetVelcoity() const;

    UFUNCTION(BlueprintCallable, Category = "Dice Roll")
    void RollArc();

    UFUNCTION(BlueprintCallable, Category = "Dice Roll")
    int32 GetArc() const;

protected:
    virtual void NativeConstruct() override;

    UFUNCTION()
    void HandleButtonClicked();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Roll")
    FString BodyString;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Roll")
    FString ButtonString;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Roll")
    FString VelocityString;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Roll")
    FString ArcString;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice Roll")
    int32 Velocity = -1;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice Roll")
    int32 Arc = -1;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice Roll")
    bool HasVelocityBeenSet;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice Roll")
    bool HasArcBeenSet;

};