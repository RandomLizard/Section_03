// Copyright Tate Wilson 2016.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));

	/// Look for attached physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		//Physics handle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find physics handle component in %s!"), *(GetOwner()->GetName()));
	}

	Input = GetOwner()->FindComponentByClass<UInputComponent>();

	///Look for attached physics component
	if (Input)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component located in %s!"), *(GetOwner()->GetName()));
		///Bind the input axis
		Input->BindAction("Grab", IE_Pressed, this, &UGrabber::GrabPressed);
		Input->BindAction("Grab", IE_Released, this, &UGrabber::GrabReleased);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input component not found for %s!"), *(GetOwner()->GetName()));
	}
	
}

void UGrabber::GrabPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"));
}

void UGrabber::GrabReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"));
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// get player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;



	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*Reach;
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		3.f
		);

	// ray-cast out to reach distance

	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	///Line-Trace (AKA ray-cast) 
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	//log what's hit to console	

	if (Hit.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("HIT %s"), *(Hit.GetActor()->GetName()));
	}

}

