// Umberto Festa

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	FRotator newRotator = FRotator(0.f, -20.0f, 0.f);
	GetOwner()->SetActorRotation(newRotator);
	isDoorOpened = true;
}

void UOpenDoor::CloseDoor()
{
	FRotator newRotator = FRotator(0.f, -90.0f, 0.f);
	GetOwner()->SetActorRotation(newRotator);
	isDoorOpened = false;
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (pressurePlate->IsOverlappingActor(actorThatOpens)) {
		OpenDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (isDoorOpened && GetWorld()->GetTimeSeconds() - lastDoorOpenTime > doorCloseDelay) {
		CloseDoor();
	}
	
}

