// Copyright JackK

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * 
 */
// start in lec 87
UCLASS()
class AURA_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:

	static UAuraAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
