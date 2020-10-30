// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ActorWidgetComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (LODZERO), meta = (BlueprintSpawnableComponent))
class FIRSTCPPPROJ_API UActorWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	virtual void InitWidget() override;

	UActorWidgetComponent();
};
