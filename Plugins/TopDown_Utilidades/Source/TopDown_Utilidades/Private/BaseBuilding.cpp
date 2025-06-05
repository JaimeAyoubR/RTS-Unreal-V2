// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuilding.h"

#include "Components/BoxComponent.h"
#include "Components/Button.h"
#include "Misc/MapErrors.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

// Sets default values
ABaseBuilding::ABaseBuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	StaticMesh->SetupAttachment(BoxComponent);
	//Create Box
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	//
	// BoxComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	//
	// BoxComponent->SetupAttachment(RootComponent);


	//Crete Indicator
	SelectIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SelectIndicator"));
	SelectIndicator->SetupAttachment(RootComponent);
	SelectIndicator->SetHiddenInGame(true);
	SelectIndicator->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ABaseBuilding::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseBuilding::SelectActor_Implementation(const bool select)
{
	SelectIndicator->SetHiddenInGame(!select);
}

void ABaseBuilding::EnablePlacingMode()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController != nullptr)
	{
		EnableInput(PlayerController);
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(
			PlayerController->InputComponent);
		if (EnhancedInputComponent != nullptr)
		{
			EnhancedInputComponent->BindAction(PlaceAction, ETriggerEvent::Completed, this,
			                                   &ABaseBuilding::PLaceBilding);
		}
	}
	GetWorld()->GetTimerManager().SetTimer(PlacementTimerHandle, this,
	                                       &ABaseBuilding::CheckPlace, 0.02f, true);

	this->SetActorEnableCollision(false);
}

void ABaseBuilding::CheckPlace()
{
	bCanPlaceBuilding = false;
	FHitResult HitResult;
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	if (!HitResult.bBlockingHit)
	{
		return;
	}
	if (!HitResult.GetActor()->ActorHasTag(RequiredTag))
	{
		return;
	}
	FVector BoxHalfSize = BuildingLocation / 2;
	FVector StartBox = HitResult.Location + FVector(0, 0, BoxHalfSize.Z);
	FVector EndBox = StartBox + FVector::UpVector;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.bTraceComplex = false;
	TArray<FHitResult> Hits;

	bool bHit = GetWorld()->SweepMultiByChannel(Hits, StartBox, EndBox,
	                                            GetActorRotation().Quaternion(),
	                                            ECC_Visibility, FCollisionShape::MakeBox(BoxHalfSize), CollisionParams);
	for (const FHitResult& HitResults : Hits)
	{
		if (!(HitResults.GetActor() != nullptr && HitResult.GetActor()->ActorHasTag(RequiredTag)))
		{
			return;
		}
	}
	bCanPlaceBuilding = true; 
	SetActorLocation(HitResult.Location);
}

void ABaseBuilding::PLaceBilding(const FInputActionValue& Value)
{
	if (!bCanPlaceBuilding)
	{
		SetLifeSpan(0.1f);
		return;
	}
	GetWorld()->GetTimerManager().ClearTimer(PlacementTimerHandle);
	this->SetActorEnableCollision(true);
}

void ABaseBuilding::CancelBuild(const FInputActionValue& Value)
{
}
