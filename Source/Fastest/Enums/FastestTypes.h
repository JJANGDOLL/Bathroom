#pragma once

#include "FastestTypes.generated.h"

UENUM()
namespace EObjectInteract
{
	enum Type
	{
		NONE  UMETA(DisplayName = "None"),
		ZOOM  UMETA(DisplayName = "Zoom"),
		ACT   UMETA(DisplayName = "Act")
	};
}

UENUM()
namespace EObjectBlink
{
	enum Type
	{
		NORMAL UMETA(DisplayName = "NORMAL"),
		CRAZY UMETA(DisplayName = "CRAZY")
	};
}