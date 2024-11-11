
#include "Charcters/SBProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASBProjectile::ASBProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));

}

void ASBProjectile::BeginPlay()
{
	Super::BeginPlay();
}