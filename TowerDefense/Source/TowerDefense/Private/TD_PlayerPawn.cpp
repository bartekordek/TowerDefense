// Fill out your copyright notice in the Description page of Project Settings.


#include "TD_PlayerPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameplayHUDC_CPP.h"

// Sets default values
ATD_PlayerPawn::ATD_PlayerPawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    Position = {0.f, 0.f, 0.f};
    MoveDirection = {0.f, 0.f, 0.f};

    FullName = GetFullName();

    UE_LOG(LogTemp, Warning, TEXT("ATD_PlayerPawn(): %s"), *FullName);

    //TArray<UUserWidget*> HUDWidgets;
    //UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, HUDWidgets, UGameplayHUDC_CPP::StaticClass());

    //if (HUDWidgets.Num() > 0)
    //{
    //    UUserWidget* HUDB = HUDWidgets[0];
    //    HUD = Cast<UGameplayHUDC_CPP>(HUDB);
    //}

}

// Called when the game starts or when spawned
void ATD_PlayerPawn::BeginPlay()
{
    Super::BeginPlay();



    TArray<AActor*> FoundActors;
    //UGameplayStatics::GetAllActorsOfClass(GetWorld(), YourClass::StaticClass(), FoundActors);
  
    
    UE_LOG(LogTemp, Warning, TEXT("BeginPlay: %s"), *FullName);

    started = true;
}

void ATD_PlayerPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    UE_LOG(LogTemp, Warning, TEXT("EndPlay: %s"), *FullName);
}

// Called every frame
void ATD_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (started)
    {
        MoveTo(Position);
    }

}

// Called to bind functionality to input
void ATD_PlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    SetupInputComponent();

    //if (PlayerControllerRef)
    //{
    //    auto x = 0;
    //}

    //PlayerControllerRef = Cast<APlayerController>(GetController());

    //if (PlayerControllerRef)
    //{
    //    PlayerControllerRef->bEnableClickEvents = true;
    //}
}

void ATD_PlayerPawn::SetupInputComponent()
{
    auto PlayerInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (PlayerInputComponent)
    {
        PlayerInputComponent->BindAxis("MoveHorizontal", this, &ATD_PlayerPawn::MoveHorizontal);
        PlayerInputComponent->BindAxis("MoveVertical", this, &ATD_PlayerPawn::MoveVertical);
        PlayerInputComponent->BindAxis("MoveUpDown", this, &ATD_PlayerPawn::MoveUpDown);
        PlayerInputComponent->BindAxis("MoveHorizontalMouse", this, &ATD_PlayerPawn::MoveHorizontalMouse);
        PlayerInputComponent->BindAxis("MoveVerticalMouse", this, &ATD_PlayerPawn::MoveVerticalMouse);
        PlayerInputComponent->BindAxis("MouseWheel", this, &ATD_PlayerPawn::MouseWheel);

        PlayerInputComponent->BindAction("MouseLeft", EInputEvent::IE_Pressed, this, &ATD_PlayerPawn::SetMouseClickedLeftOn);
        PlayerInputComponent->BindAction("MouseLeft", EInputEvent::IE_Released, this, &ATD_PlayerPawn::SetMouseClickedLeftOff);
        PlayerInputComponent->BindAction("MouseRight", EInputEvent::IE_Pressed, this, &ATD_PlayerPawn::SetMouseClickedRightOn);
        PlayerInputComponent->BindAction("MouseRight", EInputEvent::IE_Released, this, &ATD_PlayerPawn::SetMouseClickedRightOff);
        PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ATD_PlayerPawn::JumpPressed);
        PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ATD_PlayerPawn::JumpReleased);

        PlayerInputComponent->BindAction("GamepadFaceButtonBottom", EInputEvent::IE_Released, this, &ATD_PlayerPawn::OnPressed);

        // GamepadFaceButtonBottom
    }
}

void ATD_PlayerPawn::OnPressed()
{
    UE_LOG(LogTemp, Warning, TEXT("OnPressed::GamepadFaceButtonBottom"));
}

void ATD_PlayerPawn::SetMouseClickedLeftOn()
{
    MouseClickedLeft = true;
    UE_LOG(LogTemp, Warning, TEXT("SetMouseClickedLeftOn: %s"), *FullName);
}

void ATD_PlayerPawn::SetMouseClickedLeftOff()
{
    MouseClickedLeft = false;
    UE_LOG(LogTemp, Warning, TEXT("SetMouseClickedLeftOff: %s"), *FullName);
}

void ATD_PlayerPawn::SetMouseClickedRightOn()
{
    UE_LOG(LogTemp, Warning, TEXT("[RIGHT][CLICKED]"));
}

void ATD_PlayerPawn::SetMouseClickedRightOff()
{
    UE_LOG(LogTemp, Warning, TEXT("[RIGHT][RELEASED]"));
}

void ATD_PlayerPawn::MoveTo(const FVector& InPosition)
{
    if (!EnableMovement)
    {
        return;
    }
    SetActorLocation(InPosition, false);
    Position = InPosition;
}

void ATD_PlayerPawn::MoveHorizontal(float Value)
{
    if (!EnableMovement)
    {
        return;
    }
    Position.Y -= Value;
}

void ATD_PlayerPawn::MoveVertical(float Value)
{
    if (!EnableMovement)
    {
        return;
    }
    Position.X += Value;
}

void ATD_PlayerPawn::MoveUpDown(float Value)
{
    if (!EnableMovement)
    {
        return;
    }
    Position.Z -= Value;
}

void ATD_PlayerPawn::MoveHorizontalMouse(float Value)
{
    if (!EnableMovement)
    {
        return;
    }
    if (MouseClickedLeft)
    {
        Position.Y -= Value;
    }
}

void ATD_PlayerPawn::MoveVerticalMouse(float Value)
{
    if (!EnableMovement)
    {
        return;
    }
    if (MouseClickedLeft)
    {
        Position.X -= Value;
    }
}

void ATD_PlayerPawn::MouseWheel(float Value)
{
    if (!EnableMovement)
    {
        return;
    }
    Position.Z -= Value * 2.56;
}

void ATD_PlayerPawn::JumpPressed()
{
    UE_LOG(LogTemp, Warning, TEXT("ATD_PlayerPawn::JumpPressed()"));
}

void ATD_PlayerPawn::JumpReleased()
{
    UE_LOG(LogTemp, Warning, TEXT("ATD_PlayerPawn::JumpReleased()"));
}

void ATD_PlayerPawn::ToggleEnableMovement(bool Enable)
{
    EnableMovement = Enable;
}

ATD_PlayerPawn::~ATD_PlayerPawn()
{
    UE_LOG(LogTemp, Warning, TEXT("~ATD_PlayerPawn(): %s"), *FullName);
}