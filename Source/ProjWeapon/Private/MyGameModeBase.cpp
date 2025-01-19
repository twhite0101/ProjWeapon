// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "KitePawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/Actor.h"

void AMyGameModeBase::AMyGameMode()
{
	// Sets player controller class to the kite pawn's class
	PlayerControllerClass = AKitePawn::StaticClass();
}
