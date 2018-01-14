// Umberto Festa

#pragma once

#include "Components/ActorComponent.h"
#include "Action.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UAction : public UActorComponent
{
	GENERATED_BODY()

public:	

	//la distanza massima degli oggetti
	float Reach = 100.0f;

	// Sets default values for this component's properties
	UAction();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void FindObjectWithAction();

	FVector GetRayTraceStartPoint();
	
	FVector GetRayTraceEndPoint();

	void GetInputController();

	void Action();

	//il gestore dell'input del giocatore
	UInputComponent* InputComponent = nullptr;
	
};
