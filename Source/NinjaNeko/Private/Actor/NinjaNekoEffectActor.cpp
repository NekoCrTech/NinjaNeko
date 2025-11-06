// Developed by Neko Creative Technologies


#include "Actor/NinjaNekoEffectActor.h"

#include "Components/SphereComponent.h"

// Sets default values
ANinjaNekoEffectActor::ANinjaNekoEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
	
}

void ANinjaNekoEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ANinjaNekoEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ANinjaNekoEffectActor::EndOverlap);
	
}

void ANinjaNekoEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
}

void ANinjaNekoEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
}




