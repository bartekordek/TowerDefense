// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HAL/ThreadSafeBool.h"
#include "TD_PlayerPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;



UCLASS()
class ATD_PlayerPawn : public APawn
{
	GENERATED_BODY()

    enum class MoveDirection: short
    {
        NORTH = 0,
        SOUTH,
        WEST,
        EAST,
        UP,
        DOWN
    };

public:
    ATD_PlayerPawn();
    virtual ~ATD_PlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category = "Move")
    void MoveTo(const FVector& InPosition);

    UFUNCTION(BlueprintCallable, Category = "Input")
    void ToggleEnableMovement(bool Enable);


private:
    void SetupInputComponent();
    void SetMouseClickedLeftOn();
    void SetMouseClickedLeftOff();
    void SetMouseClickedRightOn();
    void SetMouseClickedRightOff();
    void JumpPressed();
    void JumpReleased();
    void OnPressed();

    APlayerController* PlayerControllerRef;

    void MoveHorizontal(float Value);
    void MoveVertical(float Value);
    void MoveUpDown(float Value);
    void MoveHorizontalMouse(float Value);
    void MoveVerticalMouse(float Value);
    void MouseWheel(float Value);
    float MoveXYDelta = 12.5f;

    bool started = false;

    UPROPERTY(EditAnywhere, Category = "Move", meta = (AllowPrivateAccess = "true"))
    float DeltaVal = 0.5f;

    UPROPERTY(EditAnywhere, Category = "Move", meta = (AllowPrivateAccess = "true"))
    float Epsilon = 0.00001f;

    FVector Position;
    FVector MoveDirection;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

    bool MouseClickedLeft = false;
    bool MouseClickedRight = false;

    FString FullName;

    bool EnableMovement = true;

};