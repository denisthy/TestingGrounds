// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"
class UActorPool;

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;
};




UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	/* Place Actors & AI */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale = 1, float MaxScale = 1);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int MinSpawn=1, int MaxSpawn=1, float Radius=500);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* Pool);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/* Navigation */
	UPROPERTY(EditDefaultsOnly,Category = "Spawning")
	FVector MaxExtent;
	UPROPERTY(EditDefaultsOnly,Category = "Spawning")
	FVector MinExtent;
	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	FVector NavigationBoundsOffset;

private:
	void PositionNavMeshBoundsVolume();

	
	template<class T>

	/* Random Functions used in actors & AI spawn */
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale = 1, float MaxScale = 1);
	bool GenerateRandomLocation(FVector& OutLocation, float Radius);
	void PlaceActor(TSubclassOf<AActor> &ToSpawn, FSpawnPosition SpawnPosition);
	void PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition);
	bool CanSpawnAtLocation(FVector Location, float Radius);

	UActorPool* Pool;
	AActor* NavMeshBoundsVolume;
};

