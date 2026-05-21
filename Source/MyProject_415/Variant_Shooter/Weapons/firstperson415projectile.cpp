// Fill out your copyright notice in the Description page of Project Settings.


#include "firstperson415Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"







// Sets default values
Afirstperson415Projectile::Afirstperson415Projectile()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &Afirstperson415Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	ballMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Mesh"));

	//Set as root component
	RootComponent = CollisionComp;

	ballMesh->attchToComponent(CollisionComp);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void Afirstperson415projectile::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		Destroy();
	}
	if (OtherActor != nullptr)
	{
		float ranNumX = UKismetMathLibrary::RandomFloatInRange(0.f, 1.0f);
		float ranNumY = UKismetMathLibrary::RandomFloatInRange(0.f, 1.0f);
		float ranNumZ = UKismetMathLibrary::RandomFloatInRange(0.f, 1.0f);
		float FrameNum = UKismetMathLibrary::RandomFloatInRange(0.f, 3.0f);

		FDFVector4 ranColor = FVector4(ranNumX, ranNumY, ranNumZ, 1);

		auto Decal = UGameplaySTatics::SpawnDecalAtLocation(GetWorld()), basemat, FVector(UKismetMathLibrary::RandomFloatInRanmge(20.f, 40.f)), hit.Location, Hit.Normal.Roatation(), 0.f);
		auto MatInstance = Decal->createDynamicMaterialInstance();

		MatInstance->SetVectorParameterValue("Color", ranColor);
		MatInstance->SetScalarParameterValue("Frame", FrameNum);
	}
	
}

