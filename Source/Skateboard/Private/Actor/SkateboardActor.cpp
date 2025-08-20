// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SkateboardActor.h"

ASkateboardActor::ASkateboardActor()
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkateMesh"));
	RootComponent = BaseMesh;

	FrontWheelsMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontWheels"));
	FrontWheelsMesh->SetupAttachment(BaseMesh);

	BackWheelsMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackWheels"));
	BackWheelsMesh->SetupAttachment(BaseMesh);
};