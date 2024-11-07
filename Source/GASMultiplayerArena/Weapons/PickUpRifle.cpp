// Fill out your copyright notice in the Description page of Project Settings.


#include "GASMultiplayerArena/Weapons/PickUpRifle.h"

// Sets default values
APickUpRifle::APickUpRifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickUpRifle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

