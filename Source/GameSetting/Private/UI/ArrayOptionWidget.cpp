// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ArrayOptionWidget.h"


void UArrayOptionWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UArrayOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// PreButton->OnClicked.AddDynamic(this, &UArrayOptionWidget::OnClickPreButton);
	// NextButton->OnClicked.AddDynamic(this, &UArrayOptionWidget::OnClickNextButton);

	if (OptionList.Num() > 0)
	{
		TextBlock_CurrentOption->SetText(FText::FromString(OptionList[0]));
	}
}

void UArrayOptionWidget::OnClickPreButton()
{
	Index--;
	if (Index <= 0)
	{
		Index = 0;
	}
	FText OptionText = FText::FromString(OptionList[Index]);
	TextBlock_CurrentOption->SetText(OptionText);
	OptionChanged.Broadcast(OptionText);
}

void UArrayOptionWidget::OnClickNextButton()
{
	Index++;
	if (Index >= OptionList.Num())
	{
		Index = OptionList.Num() - 1;
	}
	FText OptionText = FText::FromString(OptionList[Index]);
	TextBlock_CurrentOption->SetText(OptionText);
	OptionChanged.Broadcast(OptionText);
}
