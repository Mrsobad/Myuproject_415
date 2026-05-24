// Fill out your copyright notice in the Description page of Project Settings.


#include "Variant_Shooter/Weapons/AMyBall.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AAMyBall::AAMyBall()
{

    // Create collision root
    SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
    RootComponent = SphereCollision;
    SphereCollision->SetSphereRadius(32.f);

    // Create mesh and attach to root
    BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
    BallMesh->SetupAttachment(RootComponent);

    // Assign the engine's built-in sphere mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(
        TEXT("/Engine/BasicShapes/Sphere.Sphere")
    );

    if (SphereMesh.Succeeded())
    {
        BallMesh->SetStaticMesh(SphereMesh.Object);
    }
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAMyBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAMyBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

