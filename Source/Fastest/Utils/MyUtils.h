#pragma once

#include "CoreMinimal.h"
#include "GameDetail/ActEngine.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Fastest.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

class FASTEST_API Helpers
{
public:
    static AActEngine* GetActEngine()
    {
        UWorld* world = GEngine->GameViewport->GetWorld();
        TArray<AActor*> childActors;
        UGameplayStatics::GetPlayerPawn(world, 0)->GetAllChildActors(childActors);
        
        AActEngine* actEngine = nullptr;

        if(childActors.Num() > 0)
        {
            actEngine = Cast<AActEngine>(childActors[0]);
        }
        MLCGLOG(Display, TEXT("%s"), *actEngine->GetName());
        return actEngine;
    }

    static void SetPlayerInput(bool bEnabled)
    {
        UWorld* world = GEngine->GameViewport->GetWorld();
        APawn* pawn = UGameplayStatics::GetPlayerPawn(world, 0);
        APlayerController* controller = UGameplayStatics::GetPlayerController(world, 0);
        if(bEnabled)
        {
            pawn->EnableInput(controller);
        }

        pawn->DisableInput(controller);
    }

    template<typename T>
    static void CreateComponent(AActor* InActor, T** OutComponent, FName InName, USceneComponent* InParent = nullptr)
    {
        *OutComponent = InActor->CreateDefaultSubobject<T>(InName);

        if(!!InParent)
        {
            (*OutComponent)->SetupAttachment(InParent);
            return;
        }


        InActor->SetRootComponent(*OutComponent);
    }
};