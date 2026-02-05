// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CultureWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetInternationalizationLibrary.h"

void UCultureWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Language = UKismetInternationalizationLibrary::GetCurrentLanguage();
	// LanguageList = {"zh", "en", "ru", "ar"};

	// LanguageList = {"zh", "en", "ru"};
	LanguageList = {"zh", "en"};

	if (LanguageList.Contains(Language))
	{
		ConfirmLanguage();
	}
	else
	{
		Language = "en";
		ConfirmLanguage();
	}


	// PreButton->OnClicked.AddDynamic(this, &UCultureWidget::OnClickPreButton);
	// NextButton->OnClicked.AddDynamic(this, &UCultureWidget::OnClickNextButton);
}

void UCultureWidget::OnClickPreButton()
{
	Index--;
	if (Index <= 0)
	{
		Index = 0;
	}
	Language = LanguageList[Index];

	ConfirmLanguage();
}

void UCultureWidget::OnClickNextButton()
{
	Index++;
	if (Index >= LanguageList.Num() - 1)
	{
		Index = LanguageList.Num() - 1;
	}


	Language = LanguageList[Index];
	ConfirmLanguage();
}

void UCultureWidget::ConfirmLanguage()
{
	FString LanguageDisplayName;
	if (Language == "zh")
	{
		LanguageDisplayName = TEXT("中文");
	}

	if (Language == "en")
	{
		LanguageDisplayName = TEXT("English");
	}

	if (Language == "ru")
	{
		LanguageDisplayName = TEXT("Русский");
	}
	// TODO  2024-09-07 18:52:54
	// if (Language == "ar")
	// {
	// 	LanguageDisplayName = TEXT(" العربية");
	// }


	TextBlock_Culture->SetText(FText::FromString(LanguageDisplayName));
	UKismetInternationalizationLibrary::SetCurrentLanguage(Language, true);
}
