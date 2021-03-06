// Copyright Tate Wilson 2016.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:

	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* Input = nullptr;
	
	//Ray-cast and grab what's in reach
	void GrabPressed();

	//called when grab is released
	void GrabReleased();
	//Find attached physics handle
	void FindPhysicsHandleComponent();
	// Setup attached input component
	void SetupInputComponent();
	//Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
	// Returns current start of reach line
	FVector GetReachLineStart();
	// Returns current end of reach line
	FVector GetReachLineEnd();
};

