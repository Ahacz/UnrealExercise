// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/TextRenderComponent.h"
#include "UsableActor.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTCPPPROJ_API AUsableActor : public AStaticMeshActor
{
	GENERATED_BODY()
	AUsableActor(const class FObjectInitializer& PCIP);


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FString StringForUsageLabel;
	UTextRenderComponent* UsageLabel;

	UFUNCTION(BlueprintImplementableEvent)
	bool OnUsed(ACharacter* character);

	UFUNCTION(BlueprintImplementableEvent)
	bool StartFocusItem();

	UFUNCTION(BlueprintImplementableEvent)
	bool EndFocusItem();
};
