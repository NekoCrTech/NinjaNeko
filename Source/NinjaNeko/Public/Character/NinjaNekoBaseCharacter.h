// Developed by Neko Creative Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NinjaNekoBaseCharacter.generated.h"

UCLASS()
class NINJANEKO_API ANinjaNekoBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ANinjaNekoBaseCharacter();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TObjectPtr<USkeletalMeshComponent> Weapon;

};
