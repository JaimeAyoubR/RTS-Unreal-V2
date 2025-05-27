// Fill out your copyright notice in the Description page of Project Settings.


#include "asdssd.h"

// Sets default values
Aasdssd::Aasdssd()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Aasdssd::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Aasdssd::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("ASDASDSAD"));

}

