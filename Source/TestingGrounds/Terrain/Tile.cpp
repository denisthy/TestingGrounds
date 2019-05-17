// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "ActorPool.h"
#include "Engine/World.h"
#include "NavigationSystem.h"
// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MinExtent = FVector(0, -2000, 0);
	MaxExtent = FVector(4000, 2000, 0);
	NavigationBoundsOffset = FVector(2000, 0, 0);

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
	
	FBox Bounds(MinExtent, MaxExtent);
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
	TActorIterator<AActor> AActorIterator = TActorIterator<AActor>(GetWorld());
	while (AActorIterator)
	{
		AActor* FoundActor = *AActorIterator;
		++AActorIterator;
	}
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Pool->Return(NavMeshBoundsVolume);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SetPool(UActorPool * InPool)
{
	UE_LOG(LogTemp, Warning, TEXT("Working %s"), *InPool->GetName());
	Pool = InPool;
	PositionNavMeshBoundsVolume();


}

void ATile::PositionNavMeshBoundsVolume()
{

	NavMeshBoundsVolume = Pool->Checkout();
	if (NavMeshBoundsVolume == nullptr) 
	{
		UE_LOG(LogTemp, Error, TEXT("NullPtr for NavMeshBoundsVolume"));
		return;
	}
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
	FNavigationSystem::Build(*GetWorld());
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
	return !HasHit;
}

