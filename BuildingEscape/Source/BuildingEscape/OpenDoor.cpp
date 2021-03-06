// Umberto Festa

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

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

	//actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

//non pi� usato
void UOpenDoor::CloseDoor()
{
	FRotator newRotator = FRotator(0.f, -90.0f, 0.f);
	GetOwner()->SetActorRotation(newRotator);
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );



	//if (pressurePlate->IsOverlappingActor(actorThatOpens)) 
	if(GetTotalMassOfActorsOnPlate() > TriggerMass)
	{
		OnOpenRequest.Broadcast();
	}
	else{
		OnCloseRequest.Broadcast();
	}
	
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {

	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	//trova tutti gli oggetti sulla piattaforma
	if (!pressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("All'oggetto %s manca il componente pressurePlate"), *(GetOwner()->GetName()));
		return TotalMass;
	}
	pressurePlate->GetOverlappingActors(OUT OverlappingActors);
	//somma tutte le masse
	for (AActor* actor : OverlappingActors)
	{
		UPrimitiveComponent* primitiveComponent = actor->FindComponentByClass<UPrimitiveComponent>();
		if(primitiveComponent)
			TotalMass = TotalMass + primitiveComponent->GetMass();

	}
	//UE_LOG(LogTemp, Warning, TEXT("Total Mass on platform trigger %f"), TotalMass);
	return TotalMass;
}

