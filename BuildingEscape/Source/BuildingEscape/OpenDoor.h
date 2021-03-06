// Copyright Tate Wilson 2016.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
private:

	UPROPERTY(EditAnywhere)
	float OpenAngle = 0.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate=nullptr;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.f;

	float LastDoorOpenTime;

	UPROPERTY(EditAnywhere)

	AActor* Owner = nullptr; //owning door

	//returns total mass in kg
	float UOpenDoor::GetTotalMassOfActorsOnPlate();

};
