// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include "Kismet/GameplayStatics.h"


void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor* deadActor)
{
    if(deadActor == Tank)
    {
        Tank->HandleDestruction();
        if(playerController)
        {
            playerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
       
    }
    else if(ATower* destroyedTower = Cast<ATower>(deadActor))
    {
        destroyedTower->HandleDestruction();
        --TargetTowers;
        if(TargetTowers == 0)
        {
            GameOver(true);
        }
    }


}

void AToonTanksGameMode::HandleGameStart()
{
    TargetTowers = GetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    playerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();
    if(playerController)
    {
        playerController->SetPlayerEnabledState(false);

        FTimerHandle playerEnableTimeHandle;

        FTimerDelegate playerEnableDelegate = FTimerDelegate::CreateUObject(playerController,&AToonTanksPlayerController::SetPlayerEnabledState,true);
        GetWorldTimerManager().SetTimer(playerEnableTimeHandle, playerEnableDelegate,StartDelay,false);
    }
}

int32 AToonTanksGameMode::GetTowerCount()
{
    TArray<AActor*> TowersInGame;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), TowersInGame);

    return TowersInGame.Num();
}