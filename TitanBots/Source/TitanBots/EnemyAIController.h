// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class AIClassType : uint8
{
	E_AINone		UMETA(DisplayName = "None"),
	E_AILight		UMETA(DisplayName = "Light"),
	E_AIMedium		UMETA(DisplayName = "Medium"),
	E_AIHeavy		UMETA(DisplayName = "Heavy")
};

UENUM(BlueprintType)
enum class EState : uint8
{
	E_Idle		UMETA(DisplayName = "Idle"),
	E_Chase		UMETA(DisplayName = "Chase"),
	E_Fire		UMETA(DisplayName = "Fire")
};

UCLASS()
class TITANBOTS_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
    
public:
    
    AEnemyAIController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
	EState State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	AIClassType TypeClass;

	UFUNCTION(BlueprintCallable, Category = Type)
	void SetClassType(AIClassType Type);
    
    virtual void Tick(float DeltaSeconds) override;
	
};
