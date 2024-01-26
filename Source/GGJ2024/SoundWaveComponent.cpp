// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundWaveComponent.h"

// Sets default values for this component's properties
USoundWaveComponent::USoundWaveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USoundWaveComponent::EmitOneSoundWave()
{
	// spawn my BP_SoundWave actor
    if(BP_SoundWaveClass)
    {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.Instigator = GetOwner()->GetInstigator();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FVector SpawnLocation = GetOwner()->GetActorLocation();
		FRotator SpawnRotation = GetOwner()->GetActorRotation();
		AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(BP_SoundWaveClass, SpawnLocation, SpawnRotation, SpawnParams);
	}
}

// Called when the game starts
void USoundWaveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USoundWaveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

