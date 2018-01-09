// Umberto Festa

#include "BuildingEscape.h"
#include "LadderPuller.h"


// Sets default values for this component's properties
ULadderPuller::ULadderPuller()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULadderPuller::BeginPlay()
{
	Super::BeginPlay();

	actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!actorThatOpens) {
		UE_LOG(LogTemp, Error, TEXT("%s manca actorThatOpens"), *(GetOwner()->GetName()));
	}
	
}


// Called every frame
void ULadderPuller::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (!actorThatOpens || !pressurePlate)
		return;

	if (pressurePlate->IsOverlappingActor(actorThatOpens)) {
		UE_LOG(LogTemp, Warning, TEXT("Trigger nuovo attivato"));
		OnPullStairsRequest.Broadcast();

	}
	else {
		OnCloseStairsRequest.Broadcast();
	}
}

