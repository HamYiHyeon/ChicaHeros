#include "MyGameModeBase.h"
#include "UObject/ConstructorHelpers.h"

AMyGameModeBase::AMyGameModeBase()
{
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BluePrints/BP_NanoRobot.BP_NanoRobot"));
    if (PlayerPawnBPClass.Succeeded())
    {
        DefaultPawnClass = nullptr;
    }
}
