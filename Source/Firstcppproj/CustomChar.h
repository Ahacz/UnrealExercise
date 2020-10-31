// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "UsableActor.h"

#include "CustomChar.generated.h"

UCLASS()
class FIRSTCPPPROJ_API ACustomChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomChar();
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

	void MoveForward(float Value);
	void MoveRight(float Value);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Get actor derived from UsableActor currently looked at by the player
	class AUsableActor* GetUsableInView();
	// Max distance to use/focus on actors.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float MaxUseDistance;
	// True only in first frame when focused on new usable actor.
	bool bHasNewFocus;

	// Actor derived from UsableActor currently in center-view.
	AUsableActor* FocusedUsableActor;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	/** Use the actor currently in view (if derived from UsableActor) */
	UFUNCTION(BlueprintCallable, WithValidation, Server, Reliable, Category = PlayerAbility)
		virtual void Use();
};
