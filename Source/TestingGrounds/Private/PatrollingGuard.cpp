// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrollingGuard.h"
TArray<AActor*> APatrollingGuard::GetPatrolPoints() {
	return PatrollingPoints;
}