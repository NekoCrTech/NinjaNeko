// Developed by Neko Creative Technologies


#include "AbilitySystem/NinjaNekoAttributeSet.h"
#include "Net/UnrealNetwork.h"

UNinjaNekoAttributeSet::UNinjaNekoAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitChakra(50.f);
	InitMaxChakra(50.f);
	InitStamina(75.f);
	InitMaxStamina(75.f);
}

void UNinjaNekoAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UNinjaNekoAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNinjaNekoAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNinjaNekoAttributeSet, Chakra, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNinjaNekoAttributeSet, MaxChakra, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNinjaNekoAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNinjaNekoAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
}

void UNinjaNekoAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNinjaNekoAttributeSet,Health, OldHealth);
}

void UNinjaNekoAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNinjaNekoAttributeSet, MaxHealth, OldMaxHealth);
}

void UNinjaNekoAttributeSet::OnRep_Chakra(const FGameplayAttributeData& OldChakra) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNinjaNekoAttributeSet, Chakra, OldChakra);
}

void UNinjaNekoAttributeSet::OnRep_MaxChakra(const FGameplayAttributeData& OldMaxChakra) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNinjaNekoAttributeSet, MaxChakra, OldMaxChakra);
}

void UNinjaNekoAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNinjaNekoAttributeSet, Stamina, OldStamina);
}

void UNinjaNekoAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNinjaNekoAttributeSet, MaxStamina, OldMaxStamina);
}
