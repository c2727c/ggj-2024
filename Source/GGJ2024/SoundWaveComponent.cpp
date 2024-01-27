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
		// Actor location + SpawnPointOffsetZ
		FVector SpawnLocation = GetOwner()->GetActorLocation() + FVector(0.0f, 0.0f, SpawnPointOffsetZ);
		FRotator SpawnRotation = FRotator(0.0f, EmitRotationY, 0.0f); // P(Y-axis),Y(X-axis),R(Z-axis)
		AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(BP_SoundWaveClass, SpawnLocation, SpawnRotation, SpawnParams);
	}
}

void USoundWaveComponent::EmitOneSoundWaveTimed()
{
	EmitOneSoundWave();
	EmitRotationY += EmitRotationYDelta * EmitInterval;
}

// Initial rotation
// Delta rotation
void USoundWaveComponent::EmitWavesStart(float Interval, float InitialRotationY, float DeltaRotationY)
{
	EmitRotationY = InitialRotationY;
	EmitInterval = Interval;
	EmitRotationYDelta = DeltaRotationY;
	GetWorld()->GetTimerManager().SetTimer(SoundWaveTimerHandle, this, &USoundWaveComponent::EmitOneSoundWaveTimed, Interval, true);
}

void USoundWaveComponent::EmitWavesStop()
{
	GetWorld()->GetTimerManager().ClearTimer(SoundWaveTimerHandle);
}

void USoundWaveComponent::EmitOneSmallWave(FVector TargetLocation, FVector SpawnLoationOffset)
{
	// spawn my BP_SoundWave actor
    if(BP_SoundWaveClass)
    {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.Instigator = GetOwner()->GetInstigator();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		// Actor location + SpawnPointOffsetZ
		FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnLoationOffset;
		FVector Direction = TargetLocation - SpawnLocation;
		Direction.Normalize();
		FRotator SpawnRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(BP_SoundWaveClass, SpawnLocation, SpawnRotation, SpawnParams);
        if (SpawnedActorRef)
        {
            // Set the scale of the spawned actor
            SpawnedActorRef->SetActorScale3D(FVector(0.2f, 0.2f, 1.0f));
        }
	}
}

void USoundWaveComponent::EmitOneSmallWaveTimed()
{
	FVector Offsets[3] = {FVector(0.0f, 0.0f, 0.0f), FVector(-50.0f, 0.0f, 50.0f ), FVector(50.0f, 0.0f, 80.0f )};
	if (SmallWaveCounter < 3)
	{
		EmitOneSmallWave(SmallWaveTargetLocation, Offsets[SmallWaveCounter]);
		SmallWaveCounter++;
		GetWorld()->GetTimerManager().SetTimer(SoundWaveTimerHandle, this, &USoundWaveComponent::EmitOneSmallWaveTimed,SmallWaveInterval, false);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(SoundWaveTimerHandle);
	}
}

void USoundWaveComponent::SmallWavesAttack(FVector TargetLocation, float Interval)
{
	//shoots a series of small sound waves to a target
	SmallWaveCounter = 0;
	SmallWaveTargetLocation = TargetLocation;
	SmallWaveInterval = Interval;
	EmitOneSmallWaveTimed();
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

