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

	//popola gli oggetti iniziali
	GetPhysicHandler();
	GetInputController();
	
}

void UGrabber::GetInputController()
{
	///Cerco il component InputComponent che viene creato a runtime
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		//UE_LOG(LogTemp, Warning, TEXT("Trovato InputComponent per %s"), *(GetOwner()->GetName()));
		//lego gli eventi di click e release all'input Grab
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
	if (!PhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("All'oggetto %s manca il componente PhysicsHandle"), *(GetOwner()->GetName()));
	}
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//DrawDebugLine(GetWorld(), GetReachLineStart(), GetReachLineEnd(), FColor(255, 0, 0), false, 0.f, 0.f, 10.f);
	
	if (!PhysicsHandle) {
		return;
	}
	//se ho un oggetto raccolto...
	if (PhysicsHandle->GrabbedComponent) {
		//sposta l'oggetto raccolto alla posizione dove si trova la fine dell'attuale raytrace
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}

}

FVector UGrabber::GetReachLineEnd() {
	FVector out_Location;
	FRotator out_Rotator;

	//recupera il punto di vista del giocatore
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT out_Location, OUT out_Rotator);

	/// calcola la direnza di raytrace sommando il vettore della posizione del giocatore con il vettore risultante dalla moltiplicazione del vettore della direzione per la costante di reach
	FVector LineTraceEnd = out_Location + (out_Rotator.Vector() * Reach);// FVector(0.f, 0.f, 70.f);

	return LineTraceEnd;
}

FVector UGrabber::GetReachLineStart() {
	FVector out_Location;
	FRotator out_Rotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT out_Location, OUT out_Rotator);
	return out_Location;
}



FHitResult UGrabber::GetFirstElementInReach()
{

	//DrawDebugLine(GetWorld(), out_Location, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);

	FHitResult LineTraceHit;

	///crea i parametri per la ricerca 
	FCollisionQueryParams queryParams(
		FName(TEXT("")), //nome della traccia, per debug
		false,//riportare collisioni complesse
		GetOwner() //actors da ignorare (se stesso)
	);

	//ray-cast e recupera il primo elemento colpito
	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTraceHit, //l'oggetto risultante
		GetReachLineStart(), //l'inizio della linea
		GetReachLineEnd(), //la fine della linea
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), //il tipo di oggetto che deve cercare
		queryParams //i parametri per la ricerca
	);

	//if (LineTraceHit.GetActor()) {
	//	UE_LOG(LogTemp, Warning, TEXT("Grabber hit something , %s"), *(LineTraceHit.GetActor()->GetName()));
	//}

	return LineTraceHit;
}

void UGrabber::Grab() {
	//UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
	//alla pressione del tasto per il grab, recupera il primo elemento in reach e se esiste, raccoglilo
	auto HitResult = GetFirstElementInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	if (!PhysicsHandle)
		return;

	if(ActorHit)
		PhysicsHandle->GrabComponent(
			ComponentToGrab, //quale elemento raccogliere
			NAME_None, //se ha uno scheletro (in questo caso no)
			ComponentToGrab->GetOwner()->GetActorLocation(), //destinazione dell'elemento raccolto
			true //può rotare?
		);


	
}

void UGrabber::Release() {
	if (!PhysicsHandle)
		return;
	//UE_LOG(LogTemp, Warning, TEXT("Object Released"));
	//se c'è un oggetto raccolto, rilascialo
	if (PhysicsHandle->GrabbedComponent)
		PhysicsHandle->ReleaseComponent();
}

