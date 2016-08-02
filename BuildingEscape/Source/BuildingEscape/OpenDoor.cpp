// Copyright Tate Wilson 2016.

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	if (!Owner) { UE_LOG(LogTemp, Error, TEXT("Owner is NULL")); return; }
	if (!PressurePlate) { UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *GetOwner()->GetName()); return; }

}

void UOpenDoor::OpenDoor()
{
	if (!Owner) { return; }
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	if (!Owner) { return; }
	Owner->SetActorRotation(FRotator(0.f, -90.f, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the Trigger Volume
	if (GetTotalMassOfActorsOnPlate() > 30.f) //TODO make into a parameter
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}

}

//returns total mass in kg
float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	
	//find all overlapping actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return 0.f; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (auto& Actor : OverlappingActors)
	{	
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}


	return TotalMass;
}