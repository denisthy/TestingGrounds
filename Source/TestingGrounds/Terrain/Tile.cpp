// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn,int MinSpawn,int  MaxSpawn, float Radius,float MinScale,float MaxScale)
{
	int NbToSpawn = FMath::RandRange(MinSpawn,MaxSpawn);
	FVector SpawnPoint;
	for (size_t i = 0; i < NbToSpawn; i++)
	{
		float Scale = FMath::RandRange(MinScale, MaxScale);
		bool Found = GenerateRandomLocation(SpawnPoint,Radius*Scale);
		if (Found)
		{
			float Rotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ToSpawn, SpawnPoint,Rotation,Scale);
		}
	}
}

void ATile::PlaceActor(TSubclassOf<AActor> &ToSpawn, const FVector &SpawnPoint, float Rotation,float Scale)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, Rotation, 0));
	Spawned->SetActorScale3D(FVector(Scale));
}

bool ATile::GenerateRandomLocation(FVector& OutLocation,float Radius)
{
	FVector Max(4000, 2000, 0);
	FVector Min(0, -2000, 0);
	FBox Bounds(Min, Max);
	FVector ResultLocation;
	for (size_t i = 0; i < 20; i++)
	{
		ResultLocation = FMath::RandPointInBox(Bounds);
		if (CanSpawnAtLocation(ResultLocation, Radius)) {
			OutLocation=  ResultLocation;
			return true;
		}
	}
	return false;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	CanSpawnAtLocation(GetActorLocation(), 500);
	CanSpawnAtLocation(GetActorLocation()+FVector(0,0,600), 200);
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation,
		GlobalLocation + FVector(0.001f, 0.001f, 0.001f),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);
	/*FColor Color = HasHit ? FColor::Red : FColor::Green;
	DrawDebugSphere(
		GetWorld(),
		Location,
		Radius,
		32,
		Color,
		true,
		100
	);*/
	return !HasHit;
}
