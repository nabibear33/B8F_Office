// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ChoiceList.h"
#include "Widgets/ChoiceItem.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

void UChoiceList::SetChoiceItems(const FDialogueRow& Row)
{
	int32 NumChoices = Row.Choices.Num();
	for(int32 i = 0; i < NumChoices; ++i)
	{
		// add child to wrap box
		UChoiceItem* NewChoiceItem = CreateWidget<UChoiceItem>(GetOwningPlayer(), ChoiceItemClass);
		ChoiceItems.Add(NewChoiceItem);
		FText ChoiceText = Row.Choices[i].ChoiceText;
		NewChoiceItem->SetChoiceText(ChoiceText);
		ChoiceItemWrapper->AddChild(NewChoiceItem);
	}
}

void UChoiceList::OnCurrentHighlightedChoiceUpdated(int32 CurrentHighlightedChoiceIndex)
{
	for(int32 i = 0; i < ChoiceItems.Num(); ++i)
	{
		UChoiceItem* ChoiceItem = ChoiceItems[i];
		if (ChoiceItem)
		{
			ChoiceItem->HighlightChoice(CurrentHighlightedChoiceIndex == i ? true : false);
		}
	}
}

void UChoiceList::ResetChoiceList()
{
	ChoiceItems.Empty();
	ChoiceItemWrapper->ClearChildren();
}
