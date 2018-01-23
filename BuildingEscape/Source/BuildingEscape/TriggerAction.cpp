// Umberto Festa

#include "BuildingEscape.h"
#include "TriggerAction.h"


// Sets default values for this component's properties
UTriggerAction::UTriggerAction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTriggerAction::BeginPlay()
{
	Super::BeginPlay();
	AActor* actor = GetOwner();
	FString actorName = actor->GetName();
	FString position = "X=%f, Y=%f, Z=%f";
	actor->GetTransform().GetLocation().X;
	UE_LOG(LogTemp, Warning, TEXT(" %s position is at X=%f, Y=%f, Z=%f!"), *actorName, actor->GetTransform().GetLocation().X, actor->GetTransform().GetLocation().Y, actor->GetTransform().GetLocation().Z);
	// ...
	
}


// Called every frame
void UTriggerAction::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTriggerAction::TriggerAnAction() {
	//provare a rimuovere componente
	//GetOwner()->RemoveOwnedComponent(this);
	OnActionTriggerRequest.Broadcast();
}