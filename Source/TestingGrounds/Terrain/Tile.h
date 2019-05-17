// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"
class UActorPool;

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale = 1, float MaxScale = 1);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* Pool);
private:
	void PositionNavMeshBoundsVolume();
	UActorPool* Pool;
	void PlaceActor(TSubclassOf<AActor> &ToSpawn, const FVector &SpawnPoint,float Rotation, float Scale);
	bool GenerateRandomLocation(FVector& OutLocation, float Radius);
	bool CanSpawnAtLocation(FVector Location, float Radius);
	AActor* NavMeshBoundsVolume;
};
