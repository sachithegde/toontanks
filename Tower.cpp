// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATower::ATower()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATower::BeginPlay()
{
    Super::BeginPlay();
    Enemy = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if(InFireRange())
    {
        RotateTurret(Enemy->GetActorLocation());
    }
}

void ATower::CheckFireCondition()
{
    if(InFireRange() && Enemy->bIsAlive)
    {
        Fire();
    }
}

bool ATower::InFireRange()
{
    if(Enemy)
    {
        float Dist = FVector::Dist(GetActorLocation(), Enemy->GetActorLocation());
        if(Dist < HitRange)
        {
            return true;
        }
    }
    return false;
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

