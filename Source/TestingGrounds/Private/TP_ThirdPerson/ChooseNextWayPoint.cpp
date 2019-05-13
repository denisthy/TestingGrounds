// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWayPoint.h"
#include "..\..\Public\TP_ThirdPerson\ChooseNextWayPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	UE_LOG(LogTemp,Warning,TEXT("SUCCEEDED : %i"),Index);
	
	return EBTNodeResult::Succeeded;
}
