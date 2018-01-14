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