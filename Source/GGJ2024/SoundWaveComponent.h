// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SoundWaveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GGJ2024_API USoundWaveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USoundWaveComponent();
	UFUNCTION(BlueprintCallable)
	void EmitOneSoundWave();
	void EmitOneSoundWaveTimed();
	UFUNCTION(BlueprintCallable)
	void EmitWavesStart(float Interval = 0.5f, float InitialRotationY = 90.0f, float DeltaRotationY = 1.0f);
	UFUNCTION(BlueprintCallable)
	void EmitWavesStop();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
    TSubclassOf<AActor> BP_SoundWaveClass;
	UPROPERTY(EditAnywhere)
	float SpawnPointOffsetZ = -21.0f;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    FTimerHandle SoundWaveTimerHandle;
    int32 SoundWaveCounter;
	float EmitRotationY = 0.0f;
	float EmitRotationYDelta = 0.0f; // degree per second
	float EmitInterval = 0.5f;

		
};
