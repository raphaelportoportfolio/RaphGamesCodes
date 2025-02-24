// Copyright ? 2024 Raph - Games & Multimidia Ltda, All rights reserved


#include "HitBoxes.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include <Kismet/KismetSystemLibrary.h>



void AHitBoxes::fDetect_HitboxCollision(TArray<FHitResult> Targets, RpE_MoveStates cc_TempMoveState)
{
	bool LoopeMode = true;
	for (int32 a = 0; a < Targets.Num(); ++a)
	{
		if (LoopeMode)
		{

		if (Targets[a].GetComponent() != nullptr && cc_TempAttackComp != nullptr && cc_Current_TagAction.IsValidIndex(0) && cc_Current_TagAction.IsValidIndex(1))
		{
			
		bool Cond1 = (Targets[a].GetComponent()->ComponentTags[0] != FName(TEXT("Root")) && Targets[a].GetComponent()->ComponentTags[0] != FName(TEXT("root")));
		bool Cond2 = (Targets[a].GetComponent()->ComponentTags[0] != cc_Current_TagAction[0]);
		bool Cond3 = (Targets[a].GetComponent()->ComponentTags[1] != cc_Current_TagAction[1]);
		bool Cond4 = (Targets[a].GetComponent()->ComponentTags[2] != cc_Current_TagAction[2]);
		bool Cond5 = cc_Hitdef.Contains(cc_TempAttackComp->ComponentTags[1].ToString());
		bool Cond6 = cc_CurrentState == UKismetStringLibrary::ParseIntoArray(cc_TempAttackComp->ComponentTags[1].ToString(), "_",true)[0];
		bool Cond12 = Targets[a].GetComponent()->GetCollisionEnabled() == ECollisionEnabled::QueryOnly;

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, cc_Current_TagAction[0].ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, cc_Current_TagAction[1].ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, cc_Current_TagAction[2].ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, Cond12 ? "True" : "False");

		if (Cond1 && Cond2 && Cond3 && Cond4 && Cond5 && Cond6 && Cond12)
			{
		
			FVector TempFinalImpactPoint = FVector(Targets[a].ImpactPoint);
	    	FRpzStruct_HitStates* TempHitState = cc_Hitdef.Find(cc_TempAttackComp->ComponentTags[1].ToString());
			RpE_HitFlag TempHitFlag = TempHitState->Attributes.HitFlag;
			RpE_HitFlag TempBlockFlag = TempHitState->Attributes.BlockFlag;
			bool TempDraw = (Targets[a].GetComponent()->ComponentTags[0].ToString() == cc_TempAttackComp->ComponentTags[0].ToString() && Targets[a].GetComponent()->ComponentTags[2].ToString() == cc_TempAttackComp->ComponentTags[2].ToString());
			bool TempBlock = (
				//S
				TempBlockFlag == RpE_HitFlag::S && cc_TempMoveState == RpE_MoveStates::Ground ||
				//C
				TempBlockFlag == RpE_HitFlag::C && cc_TempMoveState == RpE_MoveStates::Crouch ||
				//A
				TempBlockFlag == RpE_HitFlag::A && (cc_TempMoveState == RpE_MoveStates::JumpUp || cc_TempMoveState == RpE_MoveStates::JumpDown) ||
				//SC
				TempBlockFlag == RpE_HitFlag::SC && (cc_TempMoveState == RpE_MoveStates::Ground || cc_TempMoveState == RpE_MoveStates::Crouch) ||
				//SA
				TempBlockFlag == RpE_HitFlag::SA && (cc_TempMoveState == RpE_MoveStates::Ground || cc_TempMoveState == RpE_MoveStates::JumpUp || cc_TempMoveState == RpE_MoveStates::JumpDown) ||
				//CA
				TempBlockFlag == RpE_HitFlag::CA && (cc_TempMoveState == RpE_MoveStates::Crouch || cc_TempMoveState == RpE_MoveStates::JumpUp || cc_TempMoveState == RpE_MoveStates::JumpDown) ||
				//CA
				TempBlockFlag == RpE_HitFlag::SCA);

			bool Cond7 = (
				//S
				TempHitFlag == RpE_HitFlag::S && cc_TempMoveState == RpE_MoveStates::Ground ||
				//C
				TempHitFlag == RpE_HitFlag::C && cc_TempMoveState == RpE_MoveStates::Crouch ||
				//A
				TempHitFlag == RpE_HitFlag::A && (cc_TempMoveState == RpE_MoveStates::JumpUp || cc_TempMoveState == RpE_MoveStates::JumpDown)||
				//SC
				TempHitFlag == RpE_HitFlag::SC && (cc_TempMoveState == RpE_MoveStates::Ground || cc_TempMoveState == RpE_MoveStates::Crouch) ||
				//SA
				TempHitFlag == RpE_HitFlag::SA && (cc_TempMoveState == RpE_MoveStates::Ground || cc_TempMoveState == RpE_MoveStates::JumpUp || cc_TempMoveState == RpE_MoveStates::JumpDown) ||
				//CA
				TempHitFlag == RpE_HitFlag::CA && (cc_TempMoveState == RpE_MoveStates::Crouch || cc_TempMoveState == RpE_MoveStates::JumpUp || cc_TempMoveState == RpE_MoveStates::JumpDown) ||
				//CA
				TempHitFlag == RpE_HitFlag::SCA);

			bool Cond8 = (FCString::Atoi(*cc_TempAttackComp->ComponentTags[0].ToString()) > FCString::Atoi(*Targets[a].GetComponent()->ComponentTags[0].ToString()) ||
				FCString::Atoi(*cc_TempAttackComp->ComponentTags[0].ToString()) == FCString::Atoi(*Targets[a].GetComponent()->ComponentTags[0].ToString()) && 
				FCString::Atoi(*cc_TempAttackComp->ComponentTags[2].ToString()) > FCString::Atoi(*Targets[a].GetComponent()->ComponentTags[2].ToString())
				|| TempDraw);
			
			if (Cond7 && Cond8 && LoopeMode)
				{
				/*GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, Targets[a].GetComponent()->ComponentTags[0].ToString());
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, cc_Current_TagAction[0].ToString());
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TempDraw ? "True" : "False");*/
				cc_Current_TagAction = Targets[a].GetComponent()->ComponentTags;
				fCheckHitCond(cc_TempAttackComp, Targets[a].GetComponent(), Targets[a].GetActor()->GetParentActor(), this->GetParentActor(), TempFinalImpactPoint, TempBlock, TempDraw);
				LoopeMode = false;
				cc_TempAttackComp = nullptr;
				break;
				}
				
			}
		}

		}
	}
	

}


void AHitBoxes::fHidden_HitBoxes(UPrimitiveComponent* BoxCollisionRef)
{
	if (BoxCollisionRef)
	{
		BoxCollisionRef->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BoxCollisionRef->SetHiddenInGame(true,false);
	}
}

void AHitBoxes::fShow_HitBoxes(UPrimitiveComponent* BoxCollisionRef)
{
	if (BoxCollisionRef)
	{

		BoxCollisionRef->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		BoxCollisionRef->SetHiddenInGame(false, false);
		int32 TempChoose = FCString::Atoi(*BoxCollisionRef->ComponentTags[0].ToString());
		if (TempChoose == 2 || TempChoose == 3 || TempChoose == 4 || TempChoose == 5)
		{
			cc_Current_TagAction.Insert(TEXT("-1"), 0);
			cc_Current_TagAction.Insert(TEXT("-1"), 1);
			cc_Current_TagAction.Insert(TEXT("-1"), 2);
			cc_TempAttackComp = Cast<UBoxComponent>(BoxCollisionRef);
		}

	}
}



void AHitBoxes::fSetup_AllHitBoxes(FString Key)
{
	if (cc_FHitBoxList.Find(Key))
	{
		cc_TempAttackComp = nullptr;
		
		if (cc_ListBoxComponent.Find(cc_HoldBoxComponent) && cc_HoldBoxComponent != "")
		{
			FRpBox_Library* TempLibrary = cc_ListBoxComponent.Find(cc_HoldBoxComponent);
			TArray<UPrimitiveComponent*> TempHitbox = TempLibrary->HitBoxesLibrary;
			for (int32 a = 0; a < TempHitbox.Num(); ++a)
			{
			fHidden_HitBoxes(TempHitbox[a]);
			}
		}
			
		cc_HoldBoxComponent = cc_FHitBoxList.FindRef(Key)->ComponentTags[1];
		
		if (cc_ListBoxComponent.Find(cc_HoldBoxComponent))
		{
			FRpBox_Library* TempLibrary2 = cc_ListBoxComponent.Find(cc_HoldBoxComponent);
			TArray<UPrimitiveComponent*> TempHitbox2 = TempLibrary2->HitBoxesLibrary;
			for (int32 a = 0; a < TempHitbox2.Num(); ++a)
			{
				fShow_HitBoxes(TempHitbox2[a]);
			}

		}

	}
}

void AHitBoxes::ccFCreateHitBoxes(FString Key, bool OnlyCollision, int32 State, FString CurrentState, RpE_MoveStates MoveState)
{
	if (OnlyCollision == false)
	{
		fSetup_AllHitBoxes(Key);
	}

	if (cc_TempAttackComp)
	{
		TArray <FHitResult> TempHitResult;
		TArray<AActor*> TempIgnoreActor;
		TempIgnoreActor.Add(this);
		TempIgnoreActor.Add(GetParentActor());
		UKismetSystemLibrary::BoxTraceMultiByProfile(GetWorld(), cc_TempAttackComp->GetComponentLocation(), cc_TempAttackComp->GetComponentLocation(), cc_TempAttackComp->GetScaledBoxExtent(), FRotator(0, 0, 0), ccp1 ? "P1Hitbox" : "P2Hitbox", false, TempIgnoreActor, EDrawDebugTrace::None, TempHitResult, true, FLinearColor(1, 0, 0), FLinearColor(0, 1, 0), 0.2);
		cc_CurrentState = CurrentState;
		fDetect_HitboxCollision(TempHitResult, MoveState);

	}

}