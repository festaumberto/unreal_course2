// Umberto Festa

#include "BuildingEscape.h"
#include "Action.h"
#include "TriggerAction.h"

#define OUT

// Sets default values for this component's properties
UAction::UAction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UAction::BeginPlay()
{
	Super::BeginPlay();

	GetInputController();

	
}


// Called every frame
void UAction::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	DrawDebugLine(GetWorld(),GetRayTraceStartPoint(),GetRayTraceEndPoint(), FColor(255, 0, 0), false, 0.f, 0.f, 10.f);
}

void UAction::FindObjectWithAction()
{

	FHitResult HitResult;

	FCollisionQueryParams queryParams{ FName(TEXT("")), false, GetOwner() };

	GetWorld()->LineTraceSingleByObjectType(OUT HitResult, GetRayTraceStartPoint(), GetRayTraceEndPoint(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), queryParams);

	if (HitResult.GetActor()) {
		UTriggerAction* triggerActionComponent = HitResult.GetActor()->FindComponentByClass<UTriggerAction>();
		if (triggerActionComponent) {
			triggerActionComponent->TriggerAnAction();
		}else{
			UE_LOG(LogTemp, Warning, TEXT("oggetto non valido"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No hit result"));
	}
}

FVector UAction::GetRayTraceStartPoint()
{
	FVector player_location;
	FRotator player_rotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT player_location, OUT player_rotation);
	
	return player_location;
}

FVector UAction::GetRayTraceEndPoint()
{
	FVector player_location;
	FRotator player_rotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT player_location, OUT player_rotation);

	FVector endPointVector = player_location + (player_rotation.Vector() * Reach);

	return endPointVector;
}

void UAction::GetInputController()
{
	///Cerco il component InputComponent che viene creato a runtime
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		//UE_LOG(LogTemp, Warning, TEXT("Trovato InputComponent per %s"), *(GetOwner()->GetName()));
		//lego gli eventi di click e release all'input Grab
		InputComponent->BindAction("Action", IE_Pressed, this, &UAction::Action);
	}
	else {
		///non ho trovato il componente, mostro un errore
		UE_LOG(LogTemp, Error, TEXT("All'oggetto %s manca il componente InputComponent"), *(GetOwner()->GetName()));
	}
}





void UAction::Action() {
	UE_LOG(LogTemp, Warning, TEXT("Premuto action"));
	FindObjectWithAction();
}

