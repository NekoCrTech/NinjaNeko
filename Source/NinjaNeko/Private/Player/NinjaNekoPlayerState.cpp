// Developed by Neko Creative Technologies


#include "Player/NinjaNekoPlayerState.h"

#include "AbilitySystem/NinjaNekoAbilitySystemComponent.h"
#include "AbilitySystem/NinjaNekoAttributeSet.h"

ANinjaNekoPlayerState::ANinjaNekoPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UNinjaNekoAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UNinjaNekoAttributeSet>("AttributeSet");

	NetUpdateFrequency=100.f;
}

UAbilitySystemComponent* ANinjaNekoPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
