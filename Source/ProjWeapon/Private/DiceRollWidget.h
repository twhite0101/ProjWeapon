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
    FText GetDynamicText() const;

    UFUNCTION(BlueprintCallable, Category = "Dice Roll")
    void RollVelocity();

    UFUNCTION(BlueprintCallable, Category = "Dice Roll")
    void RollArc();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Roll")
    FString DynamicString;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice Roll")
    int32 Velocity;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice Roll")
    int32 Arc;

};