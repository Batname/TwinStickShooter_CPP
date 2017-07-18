// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "DamagableInterface.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Attach a scene componet to root
	USceneComponent * SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = SceneComponent;

	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
	ProjectileCollision->SetupAttachment(RootComponent);
	ProjectileCollision->bGenerateOverlapEvents = true;
	ProjectileCollision->SetSphereRadius(10.f);
	ProjectileCollision->SetCollisionProfileName(FName("OverlapAllDynamic"));
	ProjectileCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ProjectileCollision->SetRelativeLocation(FVector(15.f, 0.f, 0.f));


	LaserMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserMeshComp"));
	LaserMeshComp->SetupAttachment(RootComponent);


	static ConstructorHelpers::FObjectFinder<UStaticMesh> Shape_Sphere(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> Lazer_Material(TEXT("/Game/Materials/Lazer.Lazer"));

	if (Lazer_Material.Succeeded())
	{
		LaserMeshComp->SetMaterial(0, Lazer_Material.Object);
	}

	if (Shape_Sphere.Succeeded())
	{
		LaserMeshComp->SetStaticMesh(Shape_Sphere.Object);
	}

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 1200.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Destroy projectile
	Destroy();

	// Check actor implementable interface and actor tag
	bool bIsImplemented = OtherActor->GetClass()->ImplementsInterface(UDamagableInterface::StaticClass());
	if (ActorHasTag(FName("Friendly")) || !bIsImplemented)
	{
		return;
	}

	// Cast to interface object and affect health
	IDamagableInterface* ReactingObject = Cast<IDamagableInterface>(OtherActor);
	ReactingObject->AffectHealth(-Damage);
}
