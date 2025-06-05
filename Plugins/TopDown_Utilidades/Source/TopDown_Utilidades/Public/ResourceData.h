// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumeratorResource.h"
#include "ResourceData.generated.h"

//QUEDA PENDIENTE HUD, SE HACE DESPUES
USTRUCT(BlueprintType)
struct FResourceData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
	EResourceType ResourceType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
	UTexture2D* Texture;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
	int32 DefaultValue;

	FResourceData(): ResourceType(EResourceType::Madera),DisplayName(TEXT("")),Texture(nullptr),DefaultValue(0) {}
	FResourceData(EResourceType Type, FString Name, UTexture2D* Texture, int32 Default)
		:ResourceType(Type), DisplayName(Name), Texture(Texture), DefaultValue(Default)
	{
		
	}
};