// Copyright Sebastian Garofalo 2017

#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Owner = GetOwner();
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

}

void UOpenDoor::OpenDoor()
{	
	FRotator NewRotation = FRotator(0.0f, 90.0f, 0.0f);
	Owner->SetActorRotation(NewRotation);
	LastOpenDoorTime = GetWorld()->GetTimeSeconds();
	bDoorOpen = true;
}

void UOpenDoor::CloseDoor()
{	
	FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);
	Owner->SetActorRotation(NewRotation);
	bDoorOpen = false;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bDoorOpen && PressurePlate != nullptr) {
		if (PressurePlate->IsOverlappingActor(PlayerPawn)) {			
			OpenDoor();
		}
	}

	if (bDoorOpen && (GetWorld()->GetTimeSeconds()  - LastOpenDoorTime) > OpenDoorDelay) {
		CloseDoor();
	}
	
	/*
	FRotator NewRotation = Owner->GetActorRotation();
	NewRotation.Add(0.0f, 0.1f, 0.0f);
	Owner->SetActorRotation(NewRotation);
	*/
}

