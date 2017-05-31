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

	PhysicsHandle = Owner->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("No physics handle for %s"), *(GetOwner()->GetName()));
	}

	InputComponent = Owner->FindComponentByClass<UInputComponent>();
	if (InputComponent == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("No input component for %s"), *(GetOwner()->GetName()));
	}
	else {
		///Bind actions
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}

}

void UGrabber::Grab() {

	if (PhysicsHandle == nullptr) { return; }

	AActor* HitActor = GetPhysicalBodyHit();

	if (HitActor == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Nothing to grab"));
	}
	else {
				
		UPrimitiveComponent* ComponentToGrab = HitActor->GetRootPrimitiveComponent();

		if (ComponentToGrab) {
			
			UE_LOG(LogTemp, Warning, TEXT("Grabbing %s XXX"), *(HitActor->GetName()));

			PhysicsHandle->GrabComponentAtLocationWithRotation(
				ComponentToGrab,
				NAME_None,
				ComponentToGrab->GetOwner()->GetActorLocation(),
				FRotator(0.0f, 0.0f, 0.0f)
			);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Nothing to grab"));
		}
	}

}

void UGrabber::Release() {

	UE_LOG(LogTemp, Warning, TEXT("Grab released"));

	if (PhysicsHandle != nullptr) {
		PhysicsHandle->ReleaseComponent();
	}
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerLocation;
	FRotator PlayerRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Player located at %s and looking at %s"), *(playerLocation.ToString()), *(playerRotation.ToString()));

	/// Line trace or ray cast
	FVector LineTracerEnd = PlayerLocation + PlayerRotation.Vector() * PlayerReach;
	//DrawDebugLine(GetWorld(), PlayerLocation, LineTracerEnd, FColor(255, 0, 0), false, 0.f, 0.f, 3.f);

	if (PhysicsHandle != nullptr && PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(GetArmVector());
	}

}

AActor* UGrabber::GetPhysicalBodyHit() {

	AActor* Result = nullptr;

	FVector PlayerLocation;
	FRotator PlayerRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

	FVector LineTracerEnd = GetArmVector();

	FHitResult Hit;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	if (GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerLocation,
		LineTracerEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	)) {
		//UE_LOG(LogTemp, Warning, TEXT("Player is hitting %s"), *(Hit.GetActor()->GetName()));
		Result = Hit.GetActor();
	}

	return Result;

}

FVector UGrabber::GetArmVector() {

	FVector PlayerLocation;
	FRotator PlayerRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

	FVector LineTracerEnd = PlayerLocation + PlayerRotation.Vector() * PlayerReach;

	return LineTracerEnd;
}

