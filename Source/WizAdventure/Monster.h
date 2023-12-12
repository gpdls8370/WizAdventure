
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

UCLASS()
class WIZADVENTURE_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	UAnimMontage *DieMontage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// BPMonster의 자식 블루프린트가 사용할 BeginPlay() 
	UFUNCTION(BlueprintImplementableEvent)
	void OnBeginPlay();

	UFUNCTION(BlueprintImplementableEvent)
	void DelayDestroy();

	UFUNCTION(BlueprintCallable)
	void HandleHit();

	void HandleDestruction();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void HandleAttack();

	void Attack();

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MoveSpeed = 400.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float DetectRange = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackCooltime = 3.f;

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage *HitMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage *AttackMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase *HitSound;
};
