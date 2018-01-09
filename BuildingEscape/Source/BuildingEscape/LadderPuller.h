// Umberto Festa

#pragma once

#include "Components/ActorComponent.h"
#include "LadderPuller.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPullStairsRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API ULadderPuller : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULadderPuller();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;


	UPROPERTY(BlueprintAssignable)
	FOnPullStairsRequest  OnPullStairsRequest;

	UPROPERTY(BlueprintAssignable)
	FOnPullStairsRequest  OnCloseStairsRequest;

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate = nullptr;
	

	AActor* actorThatOpens = nullptr;
};
