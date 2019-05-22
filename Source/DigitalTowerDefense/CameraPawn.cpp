// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraPawn.h"
#include "DigitalTDController.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "TimerManager.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	static ConstructorHelpers::FObjectFinder<UCurveFloat> FloatCurve(TEXT("/Game/BP/MoveSmooth"));
	Curve = FloatCurve.Object;
	RootComponent = Mesh;
	RootComponent->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	SpringArm->AttachTo(RootComponent);
	SpringArm->TargetArmLength = 6000.0f;
	SpringArm->SetWorldRotation(FRotator(-45.0f, 0, 0));
	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);
	//Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	CamOrthoWidth = 2048;
	Camera->SetOrthoWidth(CamOrthoWidth);
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	ZoomVelocity = 0;
	ZoomUnit = 60;
	Camera->FieldOfView = 45.0f;
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = 
				GetActorLocation() + (CurrentVelocity*Speed*DeltaTime);
		SetActorLocation(NewLocation);
	}
	if (Camera->OrthoWidth != CamOrthoWidth)
	{
		int NewWidth =
			Camera->OrthoWidth + (CamOrthoWidth - Camera->OrthoWidth)/0.25*DeltaTime;
		Camera->SetOrthoWidth(NewWidth);
	}
	if (SpringArm->TargetArmLength != (6000 + ZoomVelocity * ZoomUnit))
	{
		float NewLength =
			SpringArm->TargetArmLength + ((6000 + ZoomVelocity * ZoomUnit) - SpringArm->TargetArmLength) / 0.25*DeltaTime;
		SpringArm->TargetArmLength = NewLength;
	}
}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveX", this, &ACameraPawn::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &ACameraPawn::MoveY);
	PlayerInputComponent->BindAction("ZoomIn", EInputEvent::IE_Pressed, this, &ACameraPawn::ZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &ACameraPawn::ZoomOut);
	PlayerInputComponent->BindAxis("CamRotation", this, &ACameraPawn::CamRotation);
}

void ACameraPawn::MoveX(float AxisValue)
{
	if(GetActorLocation().X<200.0f&&GetActorLocation().X>-2400.0f)
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f)*100.0f;
	else if(GetActorLocation().X >= 200.0f)
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 0.0f)*100.0f;
	else if (GetActorLocation().X <= -2400.0f)
	CurrentVelocity.X = FMath::Clamp(AxisValue, 0.0f, 1.0f)*100.0f;

}

void ACameraPawn::MoveY(float AxisValue)
{
	if (GetActorLocation().Y<1300.0f&&GetActorLocation().Y>-1300.0f)
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f)*100.0f;
	else if (GetActorLocation().Y >= 1300.0f)
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 0.0f)*100.0f;
	else if (GetActorLocation().Y <= -1300.0f)
	CurrentVelocity.Y = FMath::Clamp(AxisValue, 0.0f, 1.0f)*100.0f;
}

void ACameraPawn::ZoomIn()
{
	if (Curve != NULL) 
	{
		if (ZoomVelocity > -20)
		{
			ZoomVelocity -= 1;
			CamOrthoWidth = 2048 + ZoomVelocity * ZoomUnit;
			GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Blue, TEXT("Wheel UP"));
		}
	}
	
}

void ACameraPawn::ZoomOut()
{
	if (Curve != NULL)
	{
		if (ZoomVelocity < 0)
		{
			ZoomVelocity += 1;
			CamOrthoWidth = 2048 + ZoomVelocity * ZoomUnit;
			GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Blue, TEXT("Wheel Down"));
		}
	}
}

void ACameraPawn::CamRotation(float AxisValue)
{
	FRotator NewAngle = GetActorRotation();
	if (bIsActorRotationActive&&AxisValue!=0)
	{
		NewAngle.Yaw += FMath::Clamp(AxisValue, -1.0f, 1.0f)*90.0f;
		SetActorRotation(NewAngle);
		ToggleRotationActive();
		GetWorldTimerManager().SetTimer(DelayTimer, this, &ACameraPawn::ToggleRotationActive, 0.5f, false,0.5f);
		GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Yellow, FString::Printf(TEXT("Rotation is %f"), GetActorRotation().Yaw));
	}
	
}

void ACameraPawn::ToggleRotationActive()
{
	if (bIsActorRotationActive)
		bIsActorRotationActive = false;
	else
		bIsActorRotationActive = true;
}

void ACameraPawn::isCamRotationActive()
{
	
}




