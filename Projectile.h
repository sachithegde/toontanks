// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;
class UParticleSystem;
class UParticleSystemComponent;
class USoundBase;
class UMatineeCameraShake;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	float DamageAdd;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditAnywhere)
	float Damage = 20.f;

	
	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem* HitParticles;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* TrailParticles;
	UPROPERTY(EditAnywhere)
	USoundBase* LaunchSound;
	UPROPERTY(EditAnywhere)
	USoundBase* BlastSound;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMatineeCameraShake> HitCShake;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* otherActor, UPrimitiveComponent* otherComp, FVector NormalImpulse, const FHitResult& Hit);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
