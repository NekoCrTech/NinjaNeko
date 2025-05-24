// Developed by Neko Creative Technologies

#pragma once

#include "CoreMinimal.h"
#include "Character/NinjaNekoBaseCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"


UCLASS()
class NINJANEKO_API AEnemyCharacter : public ANinjaNekoBaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AEnemyCharacter();
	
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
};
