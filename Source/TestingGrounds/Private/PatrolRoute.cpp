// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolRoute.h"

// Sets default values for this component's properties
UPatrolRoute::UPatrolRoute()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPatrolRoute::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UPatrolRoute::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
TArray<AActor*> UPatrolRoute::GetPatrolPoints()const  {
	return PatrolPoints;
}
