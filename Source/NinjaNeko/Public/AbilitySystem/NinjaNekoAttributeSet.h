// Developed by Neko Creative Technologies

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "NinjaNekoAttributeSet.generated.h"

// #define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
// GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
// GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
// GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
// GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class NINJANEKO_API UNinjaNekoAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UNinjaNekoAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//---------------------------------------------------------------------------------
	//Vital Attributes: Health, Chakra, Stamina 
	//---------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	// MaxHealth
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	// Chakra
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Chakra, Category = "Vital Attributes")
	FGameplayAttributeData Chakra;

	UFUNCTION()
	void OnRep_Chakra(const FGameplayAttributeData& OldChakra) const;

	// MaxChakra
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxChakra, Category = "Vital Attributes")
	FGameplayAttributeData MaxChakra;

	UFUNCTION()
	void OnRep_MaxChakra(const FGameplayAttributeData& OldMaxChakra) const;

	// Stamina
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Vital Attributes")
	FGameplayAttributeData Stamina;

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;

	// MaxStamina
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Vital Attributes")
	FGameplayAttributeData MaxStamina;

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;
	
};
