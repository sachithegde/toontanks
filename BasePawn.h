// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class USceneComponent;
class UParticleSystem;
class USoundBase;
class UMatineeCameraShake;
UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

	UFUNCTION(BlueprintCallable)
	void SetDamageCounter(int32 SetValue);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bNeedsAmmo = false;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float DamageModifier = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Ammo;

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();

private:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem* DeathParticle;
	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* DeathSound;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMatineeCameraShake> HitDShake;
	

	int32 DamageCounter;
	void DecDamageCounter();
	


};
