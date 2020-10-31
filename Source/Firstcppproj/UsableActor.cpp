// Fill out your copyright notice in the Description page of Project Settings.

#include "UsableActor.h"

AUsableActor::AUsableActor(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	UsageLabel = CreateDefaultSubobject<UTextRenderComponent>(StringForUsageLabel);
}