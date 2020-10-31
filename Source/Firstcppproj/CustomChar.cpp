// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomChar.h"
#include "Firstcppproj.h"
#include "UsableActor.h"

// Sets default values
ACustomChar::ACustomChar()
{

	MaxUseDistance = 800;
	bHasNewFocus = true;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = true;

	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.4f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->SetFieldOfView(110.0f);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
}

// Called when the game starts or when spawned
void ACustomChar::BeginPlay()
{
	Super::BeginPlay();
	
}

//Perform a raytrace to find the closest interactable object from camera's pov
AUsableActor* ACustomChar::GetUsableInView()
{
	FVector camLoc;
	FRotator camRot;

	if (Controller == NULL)
		return NULL;

	Controller->GetPlayerViewPoint(camLoc, camRot);
	const FVector start_trace = camLoc;
	const FVector direction = camRot.Vector();
	const FVector end_trace = start_trace + (direction * MaxUseDistance);

	FCollisionQueryParams TraceParams(FName(TEXT("")), true, this);
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.bTraceComplex = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, start_trace, end_trace, COLLISION_PROJECTILE, TraceParams);

	return Cast<AUsableActor>(Hit.GetActor());
}

// Called every frame
void ACustomChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Controller && Controller->IsLocalController())
	{
		AUsableActor* usable = GetUsableInView();

		// End Focus
		if (FocusedUsableActor != usable)
		{
			if (FocusedUsableActor)
			{
				FocusedUsableActor->EndFocusItem();
			}

			bHasNewFocus = true;
		}

		// Assign new Focus
		FocusedUsableActor = usable;

		// Start Focus.
		if (usable)
		{
			if (bHasNewFocus)
			{
				usable->StartFocusItem();
				bHasNewFocus = false;
			}
		}
	}

}

void ACustomChar::Use_Implementation()
{
	AUsableActor* usable = GetUsableInView();
	if (usable)
	{
		usable->OnUsed(this);
	}
}

bool ACustomChar::Use_Validate()
{
	// No special server-side validation performed.
	return true;
}



// Called to bind functionality to input
void ACustomChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACustomChar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACustomChar::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &ACustomChar::Use);
}
void ACustomChar::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}
void ACustomChar::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}