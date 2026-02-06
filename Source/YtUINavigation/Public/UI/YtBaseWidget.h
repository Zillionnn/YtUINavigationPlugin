// Copyright (c) Yntoo, 2026
// All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UIStyleData.h"
#include "Blueprint/UserWidget.h"
#include "YtBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class YTUINAVIGATION_API UYtBaseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

	void ApplyStyleRecursive(const TObjectPtr<UWidget>& Widget, UUIStyleData* Style);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style")
	bool bUseDesignerStyle = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style")
	UUIStyleData* DesignerStyleData;
};
