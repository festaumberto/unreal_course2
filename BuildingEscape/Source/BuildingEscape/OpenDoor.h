// Umberto Festa

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();

	void CloseDoor();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	float GetTotalMassOfActorsOnPlate();

private:
	UPROPERTY(VisibleAnywhere)
	float OpenAngle = 60.0f;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate;

	UPROPERTY(VisibleAnywhere)
	float doorCloseDelay = 1.0f;

	float lastDoorOpenTime;

	//AActor* actorThatOpens;

	bool isDoorOpened = false;
	
};