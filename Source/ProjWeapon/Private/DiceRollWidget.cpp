#include "DiceRollWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MainGameStateBase.h"
#include "MainGameMode.h"

void UDiceRollWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Bind HandleButtonClicked function to Dice Roll Widget's button
    if (UButton* Button = Cast<UButton>(GetWidgetFromName(TEXT("RollButton"))))
    {
        Button->OnClicked.AddDynamic(this, &UDiceRollWidget::HandleButtonClicked);
    }
}

// Handle button click on Dice Roll Widget
void UDiceRollWidget::HandleButtonClicked()
{
    AMainGameMode* GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GameMode)
    {
        GameMode->SetVelocityAndArc();
    }
}

// Getter for widget's body text
FText UDiceRollWidget::GetBodyText() const
{
    return FText::FromString(BodyString);
}
// Setter for widget's body text
void UDiceRollWidget::SetBodyText(FString NewText)
{
    BodyString = NewText;
}

// Getter for widget's button text
FText UDiceRollWidget::GetButtonText() const
{
    return FText::FromString(ButtonString);
}

// Setter for widget's button text
void UDiceRollWidget::SetButtonText(FString NewText)
{
    ButtonString = NewText;
}

// Getter for widget's velocity text
FText UDiceRollWidget::GetVelocityText() const
{
    return FText::FromString(VelocityString);
}

// Setter for widget's velocity text
void UDiceRollWidget::SetVelocityText(FString NewText)
{
    VelocityString = NewText;
}

// Getter for widget's arc text
FText UDiceRollWidget::GetArcText() const
{
    return FText::FromString(ArcString);
}

// Setter for widget's arc text
void UDiceRollWidget::SetArcText(FString NewText)
{
    ArcString = NewText;
}

// Setter for Velocity to rand int
void UDiceRollWidget::RollVelocity()
{
    Velocity = FMath::RandRange(1, 6);
}

// Getter for Velocity
int32 UDiceRollWidget::GetVelcoity() const
{
    return Velocity;
}

//Setter for Arc to rand int
void UDiceRollWidget::RollArc()
{
    Arc = FMath::RandRange(1, 6);
}

// Getter for Arc
int32 UDiceRollWidget::GetArc() const
{
    return Arc;
}