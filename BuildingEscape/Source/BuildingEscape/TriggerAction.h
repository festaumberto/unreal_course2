// Umberto Festa

#pragma once

#include "Components/ActorComponent.h"
#include "TriggerAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionTriggerRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UTriggerAction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerAction();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void TriggerAnAction();

	UPROPERTY(BlueprintAssignable)
	FOnActionTriggerRequest  OnActionTriggerRequest;
	
};
