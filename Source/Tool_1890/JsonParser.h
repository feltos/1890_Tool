// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "JsonUtilities/Public/JsonUtilities.h"
#include <string>
#include <list>
#include "iostream"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JsonParser.generated.h"

USTRUCT(BlueprintType)
struct FHintsBox
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	FString hintName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	bool hintFind;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	FString description;
};


UCLASS()
class TOOL_1890_API AJsonParser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJsonParser();

	UFUNCTION(BlueprintCallable, Category = "JsonParser")
	void LoadJson();

	UFUNCTION(BlueprintCallable, Category = "JsonParser")
	TArray<FHintsBox> GetHintVariables() { return Variables; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<FHintsBox> Variables;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
