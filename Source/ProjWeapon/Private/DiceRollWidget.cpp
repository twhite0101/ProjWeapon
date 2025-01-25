#include "DiceRollWidget.h"

FText UDiceRollWidget::GetDynamicText() const
{
    return FText::FromString(DynamicString);
}

void UDiceRollWidget::RollVelocity()
{
    Velocity = FMath::RandRange(1, 6);
}

void UDiceRollWidget::RollArc()
{
    Arc = FMath::RandRange(1, 6);
}