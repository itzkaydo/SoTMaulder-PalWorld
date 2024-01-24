#include "pch.h"
#include "feature.h"

void ESP()
{
	/**
	if (Config.GetPalPlayerCharacter() != NULL)
	{
		if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
		{

				DrawUActorComponent(Config.GetPalPlayerCharacter()->BlueprintCreatedComponents, ImColor(128, 0, 0));
		}
	}
	**/
}
void DrawUActorComponent(SDK::TArray<SDK::UActorComponent*> Comps, ImColor color)
{
	ImGui::GetBackgroundDrawList()->AddText(nullptr, 16, ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), color, "Drawing...");
	if (Comps.IsValid())
	{
		for (int i = 0; i < Comps.Num(); i++)
		{

			if (Comps[i] != NULL)
			{

				ImGui::GetBackgroundDrawList()->AddText(nullptr, 16, ImVec2(10, 10 + (i * 30)), color, Comps[i]->GetFullName().c_str());
			}
		}
	}

}