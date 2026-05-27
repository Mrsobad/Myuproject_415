// Fill out your copyright notice in the Description page of Project Settings.


#include "ProMeshFromStatic.h"
#include "kismetProceduralMeshLibrary.h"

// Sets default values
AProMeshFromStatic::AProMeshFromStatic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	procMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Proc Mesh"));
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));

	//procMesh->SetupAttachment(GetRootComponent());
	RootComponent = procMesh;
	baseMesh->SetupAttachment(procMesh);

}

// Called when the game starts or when spawned
void AProMeshFromStatic::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProMeshFromStatic::PostActorCreated()
{
	Super::PostActorCreated();
	GetMeshData();
}

void AProMeshFromStatic::PostLoad()
{
	Super::PostLoad();
	GetMeshData();
}

void AProMeshFromStatic::GetMeshData()
{
	UStaticMesh* mesh = baseMesh->GetStaticMesh();
	if (mesh)
	{
		UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(mesh, 0, 0, Vertices, Triangles, Normals, UV0, Tangents);
		procMesh->UpdateMeshSection(0, Vertices, Normals, UV0, UpVertexColors, Tangents);
		CreateMesh();
	}
}

void AProMeshFromStatic::CreateMesh()
{
	if (baseMesh)
	{
		procMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, UpVertexColors, Tangents, true);
	}
}

// Called every frame
void AProMeshFromStatic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

