// Fill out your copyright notice in the Description page of Project Settings.


#include "StagePlayer.h"

// Sets default values
AStagePlayer::AStagePlayer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Cpp_RootCamera = CreateDefaultSubobject<USceneComponent>(TEXT("Cpp_RootCamera"));
	AStagePlayer::Cpp_RootCamera->SetupAttachment(RootComponent);
	Cpp_CameraDirector = CreateDefaultSubobject<USceneComponent>(TEXT("CppCameraDirector"));
	AStagePlayer::Cpp_CameraDirector->SetupAttachment(Cpp_RootCamera);
	Cpp_CameraPlayer = CreateDefaultSubobject<UCameraComponent>(TEXT("CppCameraPlayer"));
	AStagePlayer::Cpp_CameraPlayer->SetupAttachment(Cpp_CameraDirector);
	Cpp_CameraFar = CreateDefaultSubobject<UCameraComponent>(TEXT("Cpp_CameraFar"));
	AStagePlayer::Cpp_CameraFar->SetupAttachment(Cpp_CameraPlayer);

	//CameraFoCus
	Cpp_RootCameraFocus_P1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cpp_RootCameraFocus_P1"));
	AStagePlayer::Cpp_RootCameraFocus_P1->SetupAttachment(Cpp_RootCamera);
	Cpp_RootCameraFocus_P2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cpp_RootCameraFocus_P2"));
	AStagePlayer::Cpp_RootCameraFocus_P2->SetupAttachment(Cpp_RootCamera);
	Cpp_CameraFocus_P1 = CreateDefaultSubobject<UCameraComponent>(TEXT("Cpp_CameraFocus_P1"));
	AStagePlayer::Cpp_CameraFocus_P1->SetupAttachment(Cpp_RootCameraFocus_P1);
	Cpp_CameraFocus_P2 = CreateDefaultSubobject<UCameraComponent>(TEXT("Cpp_CameraFocus_P2"));
	AStagePlayer::Cpp_CameraFocus_P2->SetupAttachment(Cpp_RootCameraFocus_P2);
		
	//Wall
	Cpp_Wall_Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cpp_Wall_Left"));
	AStagePlayer::Cpp_Wall_Left->SetupAttachment(Cpp_RootCamera);
	Cpp_Wall_BlockLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cpp_Wall_BlockLeft"));
	AStagePlayer::Cpp_Wall_BlockLeft->SetupAttachment(Cpp_Wall_Left);
	Cpp_Wall_Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cpp_Wall_Right"));
	AStagePlayer::Cpp_Wall_Right->SetupAttachment(Cpp_RootCamera);
	Cpp_Wall_BlockRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cpp_Wall_BlockRight"));
	AStagePlayer::Cpp_Wall_BlockRight->SetupAttachment(Cpp_Wall_Right);

	//CameraWall
	Cpp_Camera_Wall_Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cpp_CameraWall_Left"));
	AStagePlayer::Cpp_Camera_Wall_Left->SetupAttachment(Cpp_CameraDirector);
	Cpp_Camera_Wall_BlockLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cpp_CameraWall_BlockLeft"));
	AStagePlayer::Cpp_Camera_Wall_BlockLeft->SetupAttachment(Cpp_Camera_Wall_Left);
	Cpp_Camera_Wall_Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cpp_CameraWall_Right"));
	AStagePlayer::Cpp_Camera_Wall_Right->SetupAttachment(Cpp_CameraDirector);
	Cpp_Camera_Wall_BlockRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cpp_CameraWall_BlockRight"));
	AStagePlayer::Cpp_Camera_Wall_BlockRight->SetupAttachment(Cpp_Camera_Wall_Right);

	//cameras
	Cpp_CameraPlayer->FieldOfView = 55;
	Cpp_CameraPlayer->SetRelativeLocation(FVector (-690.034, 2.192, 110.0));
	Cpp_CameraPlayer->SetRelativeRotation(FQuat(FRotator(0, 3.1, 0)));
	Cpp_CameraPlayer->SetIsReplicated(true);
	Cpp_CameraPlayer->SetActive(false);
	Cpp_CameraFar->FieldOfView = 55;
	Cpp_CameraFar->SetRelativeLocation(FVector(-231.31, 0,0));
	Cpp_CameraFar->SetRelativeRotation(FQuat(FRotator(0, 0, 0)));
	Cpp_CameraFar->SetIsReplicated(true);
	Cpp_CameraFar->SetActive(false);
	Cpp_CameraFocus_P1->FieldOfView = 55;
	Cpp_CameraFocus_P1->SetIsReplicated(true);
	Cpp_CameraFocus_P1->SetActive(false);
	Cpp_CameraFocus_P2->FieldOfView = 55;
	Cpp_CameraFocus_P2->SetIsReplicated(true);
	Cpp_CameraFocus_P1->SetActive(false);
	//wall
	Cpp_Wall_Left->SetRelativeLocation(FVector(0, -900.0, 58.0));
	Cpp_Wall_Left->SetRelativeScale3D(FVector(5, 1, 24));
	Cpp_Wall_BlockLeft->SetRelativeLocation(FVector(0, 50, 0));
	Cpp_Wall_Right->SetRelativeLocation(FVector(0, 900.0, 58.0));
	Cpp_Wall_Right->SetRelativeScale3D(FVector(5, 1, 24));
	Cpp_Wall_BlockRight->SetRelativeLocation(FVector(0, -50, 0));
	Cpp_Camera_Wall_Left->SetRelativeLocation(FVector(0, -350.0, 50));
	Cpp_Camera_Wall_Left->SetRelativeScale3D(FVector(8, 1, 8));
	Cpp_Camera_Wall_BlockLeft->SetRelativeLocation(FVector(0, 50, 0));
	Cpp_Camera_Wall_Right->SetRelativeLocation(FVector(0, 350, 50));
	Cpp_Camera_Wall_Right->SetRelativeScale3D(FVector(8, 1, 8));
	Cpp_Camera_Wall_BlockRight->SetRelativeLocation(FVector(0, -50, 0));

}

// Called when the game starts or when spawned
void AStagePlayer::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AStagePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsValid(Cpp_P01) && IsValid(Cpp_P02) && Cpp_StartCameraGame && Cpp_LockCamera == false && GetWorld()->IsPaused() == false)
		{
			if (Cpp_P01->CPP_EnmCpp_HitType != EnumHitState::EHT_Hit_TrowHorizontal || Cpp_P02->CPP_EnmCpp_HitType != EnumHitState::EHT_Hit_TrowHorizontal)
			{
				Cpp_CameraDirector->SetWorldLocation(FVector(Cpp_CameraDirector->GetComponentLocation().X,
					(Cpp_P01->GetMesh()->GetComponentLocation().Y + Cpp_P02->GetMesh()->GetComponentLocation().Y) / 2, Cpp_CameraDirector->GetComponentLocation().Z));
			}

			float YTempPos = FMath::Abs(Cpp_P01->GetActorLocation().Y - Cpp_P02->GetActorLocation().Y);
			float ZTempPos = FMath::Abs
			(
				(Cpp_P01->GetCapsuleComponent()->GetComponentLocation().Z > 10 && Cpp_P02->GetCapsuleComponent()->GetComponentLocation().Z > 10) ?
				FVector(Cpp_P01->GetMesh()->GetSocketTransform(FName("head"), RTS_World).GetTranslation()).Z + FMath::GetMappedRangeValueClamped(FVector2D(40, 300), FVector2D(1, 80), 
				FVector(Cpp_P01->GetMesh()->GetSocketTransform(FName("head"), RTS_World).GetTranslation()).Z)
				:
				(Cpp_P01->GetCapsuleComponent()->GetComponentLocation().Z < 40 ? 0 : FVector(Cpp_P01->GetMesh()->GetSocketTransform(FName("head"), RTS_World).GetTranslation()).Z)
				- (Cpp_P02->GetCapsuleComponent()->GetComponentLocation().Z < 40 ? 0 : FVector(Cpp_P02->GetMesh()->GetSocketTransform(FName("head"), RTS_World).GetTranslation()).Z)
			);
			//float ZTempPos = (Cpp_P01->GetMesh()->GetSocketTransform(FName("pelvis"), RTS_World).GetTranslation().Z  + Cpp_P02->GetMesh()->GetSocketTransform(FName("pelvis"), RTS_World).GetTranslation().Z)   / 2;
			bool AirCondTemp = ((Cpp_P01->CPP_EnmCpp_LaucherState == EnumLauncherState::ELS_Launch_Up || Cpp_P01->CPP_EnmCpp_LaucherState == EnumLauncherState::ELS_Launch_Down) &&
				(Cpp_P02->CPP_EnmCpp_LaucherState == EnumLauncherState::ELS_Launch_Up || Cpp_P02->CPP_EnmCpp_LaucherState == EnumLauncherState::ELS_Launch_Down));

			float HitPositionTemp = (FVector(Cpp_P01->GetMesh()->GetSocketTransform(FName("head"), RTS_World).GetTranslation()).Z > FVector(Cpp_P02->GetMesh()->GetSocketTransform(FName("head"), RTS_World).GetTranslation()).Z ?
				FVector(Cpp_P01->GetMesh()->GetSocketTransform(FName("head"), RTS_World).GetTranslation()).Z + HitPosition_Height +30 : FVector(Cpp_P02->GetMesh()->GetSocketTransform(FName("head"), RTS_World).GetTranslation()).Z) + HitPosition_Height +30;

			float RotationCameYaw = FMath::FInterpTo(Cpp_CameraPlayer->GetRelativeRotation().Pitch,
				FMath::GetMappedRangeValueClamped(FVector2D(90, 300), FVector2D(3.1, 12), ZTempPos),
				GetWorld()->GetDeltaSeconds(), AirCondTemp ? 10 : 6);

			Cpp_RootCameraFocus_P1->SetWorldLocation(Cpp_P01->GetActorLocation());
			Cpp_RootCameraFocus_P2->SetWorldLocation(Cpp_P02->GetActorLocation());

			//Action
			Cpp_CameraPlayer->SetRelativeRotation(FQuat(FRotator(RotationCameYaw, 0,0)));
			Cpp_CameraPlayer->SetRelativeLocation(FVector(
					FMath::FInterpTo(Cpp_CameraPlayer->GetRelativeLocation().X,

					FMath::GetMappedRangeValueClamped(FVector2D(220, 550), FVector2D(-480.034, -710.034), YTempPos) + FMath::GetMappedRangeValueClamped(FVector2D(90.0, 300.0), FVector2D(0, 40.0),				FMath::GetMappedRangeValueClamped(FVector2D(90, 300), FVector2D(3.1, 12), ZTempPos)),
					GetWorld()->GetDeltaSeconds(), 9),2.192,
					FMath::FInterpTo(Cpp_CameraPlayer->GetRelativeLocation().Z,
					FMath::GetMappedRangeValueClamped(FVector2D(SettingA),
					FVector2D(FMath::GetMappedRangeValueClamped(SettingB, SettingC, YTempPos),
					AirCondTemp ? HitPositionTemp : FMath::GetMappedRangeValueClamped(SettingD, SettingE, YTempPos)), ZTempPos),
					GetWorld()->GetDeltaSeconds(), AirCondTemp ? 10 : 6)));
	}
}

void AStagePlayer::Cpp_StartCameraMovement()
{
	Cpp_StartCameraGame = true;
}
	
