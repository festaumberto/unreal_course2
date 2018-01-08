// Umberto Festa

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
	//la distanza massima degli oggetti
	float Reach = 100.0f;

	//l'handler che raccoglie gli oggetti
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	//il gestore dell'input del giocatore
	UInputComponent* InputComponent = nullptr;

	//ray-cast e afferra il primo oggetto raggiungibile
	void Grab();

	//rilascia l'oggetto raccolto
	void Release();

	//popola l'input controller
	void GetInputController();

	//popola il physics handler
	void GetPhysicHandler();

	//ritorna il primo elemento raggiungibile, se esiste
	FHitResult GetFirstElementInReach();

	//ritorna il punto finale del line trace
	FVector GetReachLineEnd();
	FVector GetReachLineStart();
};
