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
	void EmitSomeSoundWaves();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
    TSubclassOf<AActor> BP_SoundWaveClass;	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    FTimerHandle SoundWaveTimerHandle;
    int32 SoundWaveCounter;

		
};
