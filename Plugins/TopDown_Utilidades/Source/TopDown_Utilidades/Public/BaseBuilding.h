// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Actor.h"
#include "SelectableInterface.h"
#include "BaseBuilding.generated.h"

class UBoxComponent;
struct FinputActionValue;
class UInputAction;
UCLASS()
class TOPDOWN_UTILIDADES_API ABaseBuilding : public AActor,public ISelectableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBuilding();
	private:
	//Box Collider
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Building,meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxComponent;
	//Mesh
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Building,meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	//Select Indicator
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Building,meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> SelectIndicator;

	UPROPERTY(EditAnywhere,blueprintReadOnly,Category=Building,meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PlaceAction;

	UPROPERTY()
	FTimerHandle PlacementTimerHandle;

	UPROPERTY()
	FName RequiredTag = "CanPlace"; //Si tiene este tag, se puede poner el edificio

	UPROPERTY()
	bool bCanPlaceBuilding = false;

	UPROPERTY()
	FVector BuildingLocation = FVector(500.0f,500.0f,500.0f);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SelectActor_Implementation(const bool select) override;

	//Modo para construir
	UFUNCTION(BlueprintCallable,Category="Building")
	void EnablePlacingMode();

	//Checar si si se puede colocar el edificio
	void CheckPlace();

	//Poner el edificio
	void PLaceBilding(const FInputActionValue& Value);

	//Cancelar poner edificio
	void CancelBuild(const FInputActionValue& Value);

	
	
	

};
