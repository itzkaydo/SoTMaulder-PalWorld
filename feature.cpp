#include "pch.h"
#include "feature.h"
using namespace SDK;

void ESP()
{
	APalPlayerCharacter* pPalCharacter = Config.GetPalPlayerCharacter();
	if (!pPalCharacter)
		return;

	UPalShooterComponent* pShootComponent = pPalCharacter->ShooterComponent;
	if (!pShootComponent)
		return;

	APalWeaponBase* pWeapon = pShootComponent->HasWeapon;
	if (pWeapon)
		DrawUActorComponent(pWeapon->InstanceComponents, ImColor(128, 0, 0));

	if (!Config.UCIM)
		return;

	TArray<SDK::APalCharacter*> T = {};
	Config.UCIM->GetAllPalCharacter(&T);
	if (!T.IsValid())
		return;

	for (int i = 0; i < T.Num(); i++)
		ImGui::GetBackgroundDrawList()->AddText(nullptr, 16, ImVec2(10, 10 + (i * 30)), ImColor(128, 0, 0), T[i]->GetFullName().c_str());
}

void entitiesESP() {
	SDK::TArray<SDK::APalCharacter*> T = {};
	Config.UCIM->GetAllPalCharacter(&T);
	if (T.IsValid())
	{
		for (int i = 0; i < T.Num(); i++) //NUM = 11
		{
			Config.GetPalPlayerCharacter()->GetPalPlayerController()->ProjectWorldLocationToScreen(SDK::FVector(T[i]->K2_GetActorLocation().X, T[i]->K2_GetActorLocation().Y, T[i]->K2_GetActorLocation().Z), &pokemonCOORD, true);
			ImGui::GetBackgroundDrawList()->AddText(nullptr, 16, ImVec2(pokemonCOORD.X, pokemonCOORD.Y), ImColor(255, 255, 255), T[i]->GetName().c_str());
		}
	}
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