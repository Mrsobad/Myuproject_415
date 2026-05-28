// Fill out your copyright notice in the Description page of Project Settings.


#include "PerlinProcTerrain.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
APerlinProcTerrain::APerlinProcTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh"));
	ProcMesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void APerlinProcTerrain::BeginPlay()
{
	Super::BeginPlay();

	CreateVertices();
	CreateTriangles();
	ProcMesh->CreateMeshSection(sectionID, vertices, triangles, normals, UV0, UpvertexColors, TArray<FProcMeshTangent>(), true);
	ProcMesh->SetMaterial(0, Mat);
	
}

// Called every frame
void APerlinProcTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APerlinProcTerrain::AlterMesh(FVector impactPoint)
{
	for (int i = 0; i < vertices.Num(); i++)
	{
		FVector tempVector = impactPoint - this->GetActorLocation();

		if (FVector(vertices[i] - tempVector).Size() < radius)
		{
			vertices[i] = vertices[i] - Depth;
			ProcMesh->UpdateMeshSection(sectionID, vertices, normals, UV0, UpvertexColors, TArray<FProcMeshTangent>());

		}

	}
}

void APerlinProcTerrain::CreateVertices()
{
	for(int X=0; X<=XSize; X++)
	{
		for(int Y=0; Y<=YSize; Y++)
		{
			float Z = FMath::PerlinNoise2D(FVector2D(X * NoiseScale + 0.1, Y * NoiseScale + 0.1)) * ZMultiplier;
			GEngine->AddOnScreenDebugMessage(-1, 999.0f, FColor::Yellow, FString::Printf(TEXT("Z: %f"), Z));
			vertices.Add(FVector(X * Scale, Y * Scale, Z));
			UV0.Add(FVector2D(X * UVScale, Y * UVScale));
		}
	}
}

void APerlinProcTerrain::CreateTriangles()
{
	int Vertex = 0;

	for(int X=0; X<XSize; X++)
	{
		for(int Y=0; Y<YSize; Y++)
		{
			
			triangles.Add(Vertex);
			triangles.Add(Vertex + 1);
			triangles.Add(Vertex + YSize + 1);
			triangles.Add(Vertex + 1);
			triangles.Add(Vertex + YSize + 2);
			triangles.Add(Vertex + YSize + 1);

			Vertex++;
		}

		Vertex++;
	}
}

