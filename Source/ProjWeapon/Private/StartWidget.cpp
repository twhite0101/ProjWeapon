#include "StartWidget.h"
#include "Components/Button.h"
#include "MainGameMode.h"
#include "Kismet/GameplayStatics.h"

void UStartWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (UButton* Button = Cast<UButton>(GetWidgetFromName(TEXT("StartButton"))))
    {
        Button->OnClicked.AddDynamic(this, &UStartWidget::HandleButtonClicked);
    }
}

void UStartWidget::HandleButtonClicked()
{
    AMainGameMode* GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GameMode)
    {
        GameMode->StartLoop();
    }
}