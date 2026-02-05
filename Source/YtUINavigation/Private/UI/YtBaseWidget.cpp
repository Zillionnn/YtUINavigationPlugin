// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/YtBaseWidget.h"

#include "YtUIGameInstance.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/UIStyleData.h"


void UYtBaseWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!bUseDesignerStyle)
	{
		return;
	}
	UUIStyleData* UseStyle = DesignerStyleData;
	// if (!UseStyle) // 运行时回退到 GameInstance
	// {
	// 	// if (!IsDesignTime()) 
	// 	// {
	// 	// 	if (UYtUIGameInstance* GI = Cast<UYtUIGameInstance>(GetGameInstance()))
	// 	// 	{
	// 	// 		UseStyle = GI->GlobalUIStyle;
	// 	// 	}
	// 	// }
	// }

	if (UseStyle)
	{
		ApplyStyleRecursive(WidgetTree->RootWidget, UseStyle);
	}

	// 获取全局样式（假设 GameInstance 有 GlobalUIStyle）
	// if (UGameInstance* GI = GetGameInstance())
	// {
	// 	if (UYtUIGameInstance* MyGI = Cast<UYtUIGameInstance>(GI))
	// 	{
	// 		if (UUIStyleData* Style = MyGI->GlobalUIStyle)
	// 		{
	// 			if (WidgetTree && WidgetTree->RootWidget)
	// 			{
	// 				ApplyStyleRecursive(WidgetTree->RootWidget, Style);
	// 			}
	// 		}
	// 	}
	// }
}

/**
 * ====================================================
 * get widget and apply style
 * @param Widget 
 * @param Style
 * ====================================================
 */
void UYtBaseWidget::ApplyStyleRecursive(const TObjectPtr<UWidget>& Widget, UUIStyleData* Style)
{
	if (!Widget || !Style) return;

	// 1) TextBlock
	if (UTextBlock* TB = Cast<UTextBlock>(Widget))
	{
		// 设置字体
		FSlateFontInfo FI = TB->GetFont(); // 基于原先字体保留其他属性
		// TODO FONT
		if (Style->UIFont)
		{
			FI.FontObject = Style->UIFont;
			FI.Size = Style->FontSize;
		}
		TB->SetFont(FI);
		TB->SetColorAndOpacity(Style->TextColor);
	}

	// 2) Image
	// if (UImage* Img = Cast<UImage>(Widget))
	// {
	// 	if (Style->ButtonBackgroundTexture)
	// 	{
	// 		Img->SetBrushFromTexture(Style->ButtonBackgroundTexture, true);
	// 	}
	// 	Img->SetColorAndOpacity(Style->ButtonTint);
	// }

	// 3) Button (不尝试直接改 Button 的 FButtonStyle，通常我们改其子 Image/Text)
	if (UButton* Btn = Cast<UButton>(Widget))
	{
		// 如果 Button 是 ContentWidget，可以尝试递归其内容
		// if (UContentWidget* CW = Cast<UContentWidget>(Btn))
		// {
		// 	if (UWidget* Child = CW->GetContent())
		// 	{
		// 		ApplyStyleRecursive(Child, Style);
		// 	}
		// }

		Btn->SetStyle(Style->ButtonStyle);
	}

	// 4) PanelWidget: 遍历所有子项
	if (UPanelWidget* PW = Cast<UPanelWidget>(Widget))
	{
		const int32 ChildCount = PW->GetChildrenCount();
		for (int32 i = 0; i < ChildCount; ++i)
		{
			if (UWidget* Child = PW->GetChildAt(i))
			{
				ApplyStyleRecursive(Child, Style);
			}
		}
	}
	else
	{
		// 5) 其他：尝试 ContentWidget（部分不是 Panel 的容器，单子节点）
		if (UContentWidget* CW = Cast<UContentWidget>(Widget))
		{
			if (UWidget* Child = CW->GetContent())
			{
				ApplyStyleRecursive(Child, Style);
			}
		}
	}
}
