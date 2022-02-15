// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


// MLCG : MyLogCategory

DECLARE_LOG_CATEGORY_EXTERN(MLCG, Log, All);

#define MLCGLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define MLCGLOG_S(Verbosity) UE_LOG(MLCG, Verbosity, TEXT("%s"), *MLCGLOG_CALLINFO);
#define MLCGLOG(Verbosity, Format, ...) UE_LOG(MLCG, Verbosity, TEXT("%s %s"), *MLCGLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))