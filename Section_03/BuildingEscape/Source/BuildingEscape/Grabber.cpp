// Copyright Sebastian Garofalo 2017

#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Owner = GetOwner();
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FString ObjName = Owner->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Grabber started for %s"), *ObjName);
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerLocation;
	FRotator PlayerRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Player located at %s and looking at %s"), *(playerLocation.ToString()), *(playerRotation.ToString()));

	FVector LineTracerEnd = PlayerLocation + PlayerRotation.Vector() * PlayerReach;

	DrawDebugLine(GetWorld(), PlayerLocation, LineTracerEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);
}

