// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SRButton.h"


void USRButton::NativePreConstruct()
{
	Super::NativePreConstruct();
	TextBlock->SetText(Text);
}

void USRButton::NativeConstruct()
{
	Super::NativeConstruct();
	SetIsFocusable(true);

	SRButton->OnClicked.AddDynamic(this, &USRButton::OnClick);
	SRButton->OnPressed.AddDynamic(this, &USRButton::OnPress);
	SRButton->OnReleased.AddDynamic(this, &USRButton::OnRelease);
}

void USRButton::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	OnFocus.Broadcast(this);
	// SRButton->SetBackgroundColor(FLinearColor::Gray);

	Super::NativeOnAddedToFocusPath(InFocusEvent);
}

void USRButton::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	// SRButton->SetBackgroundColor(FLinearColor(0.145833f, 0.145833f, 0.145833f, 1.0f));
	Super::NativeOnRemovedFromFocusPath(InFocusEvent);
}

void USRButton::OnClick()
{
	OnButtonClicked.Broadcast();
}

void USRButton::OnPress()
{
	OnButtonPress.Broadcast();
}

void USRButton::OnRelease()
{
	OnButtonRelease.Broadcast();
}

void USRButton::SetButtonText(FString InText)
{
	TextBlock->SetText(FText::FromString(InText));
}
