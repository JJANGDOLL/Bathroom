// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class FASTEST_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AMyHUD();

	virtual void DrawHUD() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, category="UI")
	FVector2D CrosshairSize = FVector2D(50.f, 50.f);

	class UTexture2D* CrosshairTex;

	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<class UUIBase> HUDWidgetClass;

	UPROPERTY(EditAnywhere, Category="UI")
	class UUserWidget* CurrentWidget;
};
