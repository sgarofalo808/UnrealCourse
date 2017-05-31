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
	OnOpen.Broadcast();
	bDoorOpen = true;
}

void UOpenDoor::CloseDoor()
{
	OnClose.Broadcast();
	bDoorOpen = false;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate != nullptr)
	{
		if (!bDoorOpen) {
			if (GetTotalMassInPlate() >= TriggerMass) {
				OpenDoor();
			}
		}
		else if (GetTotalMassInPlate() < TriggerMass) {
			CloseDoor();
		}
	}
}

float UOpenDoor::GetTotalMassInPlate() {

	float TotalWeight = 0.f;

	TArray<AActor*> OutOverlappingActors;

	if (PressurePlate != nullptr) {
		PressurePlate->GetOverlappingActors(OutOverlappingActors);

		for (AActor* Actor : OutOverlappingActors) {
			TotalWeight += Actor->GetRootPrimitiveComponent()->GetMass();
		}

		UE_LOG(LogTemp, Warning, TEXT("Weight in pressure plate is %f and there are %i ActorsOverlapping"), TotalWeight, OutOverlappingActors.Num());
	}

	return TotalWeight;
}

