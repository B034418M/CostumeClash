// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUps/Pickup.h"

#include "Components/BoxComponent.h"
#include "PowerUps/BasePowerUp.h"
#include "PowerUps/PowerUpManager.h"


// Sets default values
APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = _Mesh;
	_Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	_Collider->SetupAttachment(RootComponent);
	_Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	_Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &APickup::OnPickup);
}

void APickup::OnPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	_PowerUpManager = Cast<UPowerUpManager>(OtherActor->GetComponentByClass(UPowerUpManager::StaticClass()));
	
	if(_PowerUpManager)
	{
		_PowerUpManager->OnPickupDelegate.Broadcast(_PowerUpClass);

		Destroy();
	}


}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

