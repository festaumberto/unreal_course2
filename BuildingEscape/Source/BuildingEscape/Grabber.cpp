// Umberto Festa

#include "BuildingEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	GetPhysicHandler();

	
	GetInputController();
	
}

void UGrabber::GetInputController()
{
	///Cerco il component APlayerController che viene creato a runtime
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Trovato InputComponent per %s"), *(GetOwner()->GetName()));
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		///non ho trovato il componente, mostro un errore
		UE_LOG(LogTemp, Error, TEXT("All'oggetto %s manca il componente InputComponent"), *(GetOwner()->GetName()));
	}
}

void UGrabber::GetPhysicHandler()
{
	///Cerco il component PhysicsHandle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		///trovato, non faccio niente
	}
	else {
		///non ho trovato il componente, mostro un errore
		UE_LOG(LogTemp, Error, TEXT("All'oggetto %s manca il componente PhysicsHandle"), *(GetOwner()->GetName()));
	}
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (PhysicsHandle->GrabbedComponent) {

		FVector out_Location;
		FRotator out_Rotator;

		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT out_Location, OUT out_Rotator);

		//UE_LOG(LogTemp, Warning, TEXT("%s , %s"), *out_Location.ToString(), *out_Rotator.ToString());

		FVector LineTraceEnd = out_Location + (out_Rotator.Vector() * Reach);// FVector(0.f, 0.f, 70.f);

		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}

}

FHitResult UGrabber::GetFirstElementInReach()
{
	FVector out_Location;
	FRotator out_Rotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT out_Location, OUT out_Rotator);

	//UE_LOG(LogTemp, Warning, TEXT("%s , %s"), *out_Location.ToString(), *out_Rotator.ToString());

	FVector LineTraceEnd = out_Location + (out_Rotator.Vector() * Reach);// FVector(0.f, 0.f, 70.f);

	//DrawDebugLine(GetWorld(), out_Location, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);


	FHitResult LineTraceHit;

	FCollisionQueryParams queryParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTraceHit,
		out_Location,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		queryParams
	);

	if (LineTraceHit.GetActor()) {
		UE_LOG(LogTemp, Warning, TEXT("Grabbero hit something , %s"), *(LineTraceHit.GetActor()->GetName()));
	}

	return LineTraceHit;
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
	auto HitResult = GetFirstElementInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	if(ActorHit)
		PhysicsHandle->GrabComponent(ComponentToGrab,NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(),true);


	
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Object Released"));
	if (PhysicsHandle->GrabbedComponent)
		PhysicsHandle->ReleaseComponent();
}

