// Copyright Mohamed Labidi (Nazake). All Rights Reserved.

#include "GCDemoGameMode.h"
#include "GCDemoPlayerController.h"
#include "GCDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGCDemoGameMode::AGCDemoGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AGCDemoPlayerController::StaticClass();
	
	// use our custom Character class
	DefaultPawnClass = AGCDemoCharacter::StaticClass();
}