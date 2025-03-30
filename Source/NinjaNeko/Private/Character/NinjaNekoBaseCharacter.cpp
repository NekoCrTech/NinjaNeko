// Developed by Neko Creative Technologies


#include "Character/NinjaNekoBaseCharacter.h"

// Sets default values
ANinjaNekoBaseCharacter::ANinjaNekoBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon -> SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ANinjaNekoBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


