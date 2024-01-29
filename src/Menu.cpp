#include "../pch.h"
#include "../include/Menu.hpp"
#include "SDK.hpp"
#include "config.h"
#include <algorithm>
std::string rand_str(const int len)
{
    std::string str;
    char c;
    int idx;
    for (idx = 0; idx < len; idx++)
    {
        c = 'a' + rand() % 26;
        str.push_back(c);
    }
    return str;
}
void Damage(SDK::APalCharacter* character, int32 damage)
{
    SDK::FPalDamageInfo  info = SDK::FPalDamageInfo();
    info.AttackElementType = SDK::EPalElementType::Normal;
    info.Attacker = Config.GetPalPlayerCharacter();
    info.AttackerGroupID = Config.GetPalPlayerState()->IndividualHandleId.PlayerUId;
    info.AttackerLevel = 50;
    info.AttackType = SDK::EPalAttackType::Weapon;
    info.bApplyNativeDamageValue = true;
    info.bAttackableToFriend = true;
    info.IgnoreShield = true;
    info.NativeDamageValue = damage;
    Config.GetPalPlayerState()->SendDamage_ToServer(character, info);
}

int InputTextCallback(ImGuiInputTextCallbackData* data) {
    char inputChar = data->EventChar;

    Config.Update(Config.inputTextBuffer);

    return 0;
}

CatchRate CRate;
CatchRate OldRate;

void DetourCatchRate(SDK::APalCaptureJudgeObject* p_this) {
    if (p_this) {
        //p_this->ChallengeCapture_ToServer(Config.localPlayer, Config.CatchRate);
        p_this->ChallengeCapture(Config.localPlayer, Config.CatchRate);
    }
}
void ToggleCatchRate(bool catchrate) {
    if (catchrate) {
        if (CRate == NULL) {
            CRate = (CatchRate)(Config.ClientBase + Config.offset_CatchRate);
            MH_CreateHook(CRate, DetourCatchRate, reinterpret_cast<void**>(OldRate));
            MH_EnableHook(CRate);
            return;
        }
        MH_EnableHook(CRate);
        return;
    }
    else
    {
        MH_DisableHook(CRate);

    }
}

namespace DX11_Base {
    char inputBuffer_getFnAddr[100];
    namespace Styles {
        void InitStyle()
        {
            ImGuiStyle& style = ImGui::GetStyle();
            ImVec4* colors = ImGui::GetStyle().Colors;

            //	STYLE PROPERTIES
            style.WindowPadding = ImVec2(15, 15);
            style.WindowRounding = 5.0f;
            style.FramePadding = ImVec2(5, 5);
            style.FrameRounding = 4.0f;
            style.ItemSpacing = ImVec2(12, 8);
            style.ItemInnerSpacing = ImVec2(8, 6);
            style.IndentSpacing = 25.0f;
            style.ScrollbarSize = 15.0f;
            style.ScrollbarRounding = 9.0f;
            style.GrabMinSize = 5.0f;
            style.GrabRounding = 3.0f;

            //  Base ImGui Styling , Aplying a custyom style is left up to you.
            ImGui::StyleColorsDark();

            /// EXAMPLE COLOR 
            //colors[ImGuiCol_FrameBg] = ImVec4(0, 0, 0, 0);

            //	COLORS
            if (g_Menu->dbg_RAINBOW_THEME) {
                //  RGB MODE STLYE PROPERTIES
                colors[ImGuiCol_Separator] = ImVec4(g_Menu->dbg_RAINBOW);
                colors[ImGuiCol_TitleBg] = ImVec4(0, 0, 0, 1.0f);
                colors[ImGuiCol_TitleBgActive] = ImVec4(0, 0, 0, 1.0f);
                colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0, 0, 0, 1.0f);
            }
            else {
                /// YOUR DEFAULT STYLE PROPERTIES HERE
                colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
                colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
                colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
                colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
                colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
                colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
                colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
                colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
                colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
                colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
                colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
                colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
                colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
                colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
                colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
                colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
                colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
                colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
                colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
                colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
                colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
                colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
                colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
                colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
                colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
                colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
                colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
                colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
                colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
                colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
                colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
                colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
                colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
                colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
                colors[ImGuiCol_Tab] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
                colors[ImGuiCol_TabActive] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
                colors[ImGuiCol_TabHovered] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
            }
        }
    }


    namespace Tabs 
    {
        void TABPlayer()
        {
            ImGui::Checkbox("InfAmmo", &Config.IsInfinAmmo);

            ImGui::Checkbox("SpeedHack", &Config.IsSpeedHack);

            ImGui::Checkbox("AttackHack", &Config.IsAttackModiler);

            ImGui::Checkbox("DefenseHack", &Config.IsDefuseModiler);

            ImGui::Checkbox("InfStamina", &Config.IsInfStamina);

            ImGui::Checkbox("Godmode", &Config.IsMuteki);

            ImGui::Checkbox("Revive", &Config.IsRevive);

            ImGui::InputText("Character Name", Config.CharName, sizeof(Config.CharName));
            if (ImGui::Button("ChangeName", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
            {
                if (Config.GetPalPlayerCharacter() != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        SDK::UKismetStringLibrary* lib = SDK::UKismetStringLibrary::GetDefaultObj();

                        wchar_t ws[255];
                        swprintf(ws, 255, L"%hs", Config.CharName);
                        Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->NetworkIndividualComponent->UpdateCharacterNickName_ToServer(Config.GetPalPlayerCharacter()->CharacterParameterComponent->IndividualHandle->ID, SDK::FString(ws));
                    }
                }
            }

            if (ImGui::Button("RandomName", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
            {
                if (Config.GetPalPlayerCharacter() != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        SDK::UKismetStringLibrary* lib = SDK::UKismetStringLibrary::GetDefaultObj();
                        std::string s = rand_str(20);

                        wchar_t  ws[255];
                        swprintf(ws, 255, L"%hs", s.c_str());

                        Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->NetworkIndividualComponent->UpdateCharacterNickName_ToServer(Config.GetPalPlayerCharacter()->CharacterParameterComponent->IndividualHandle->ID, SDK::FString(ws));
                    }
                }
            }

            ImGui::Checkbox("Open Manager", &Config.bisOpenManager);

            //��������һ��
            ImGui::SliderFloat("SpeedModifilers", &Config.SpeedModiflers, 1, 10);
            ImGui::SliderInt("AttackModifilers", &Config.DamageUp, 0, 200000);
            ImGui::SliderInt("defenseModifilers", &Config.DefuseUp, 0, 200000);

            if (ImGui::Button("PrintCoords", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
            {
                SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
                if (p_appc != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        SDK::FVector PlayerLocation = p_appc->K2_GetActorLocation();
                        std::string MyLocation = std::format("\nX: {} | Y: {} | Z: {}\n", PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z);
                        g_Console->printdbg(MyLocation.c_str(), Console::Colors::green, p_appc);
                    }
                }
            }

            SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
            if (p_appc != NULL)
            {
                if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                {
                    SDK::FVector PlayerLocation = p_appc->K2_GetActorLocation();
                    std::string MyLocation = std::format("X: {} | Y: {} | Z: {}", PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z);
                    ImGui::Text(MyLocation.c_str());
                }
            }
        }
        
        void TABExploit()
        {
            //�����õİ�
            //Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState()->RequestSpawnMonsterForPlayer(name, 5, 1);
            ImGui::Checkbox("SafeTeleport", &Config.IsSafe);
            ImGui::InputFloat3("Pos:", Config.Pos);

            if (ImGui::Button("Coord TP", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
            {
                if (Config.GetPalPlayerCharacter() != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        if (Config.Pos != NULL)
                        {
                            SDK::FVector vector = { Config.Pos[0],Config.Pos[1],Config.Pos[2] };
                            AnyWhereTP(vector, Config.IsSafe);
                        }
                    }
                }
            }

            ImGui::InputInt("EXP:", &Config.EXP);
            if (ImGui::Button("Give exp", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
            {
                SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
                if (p_appc != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        if (Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState() != NULL)
                        {
                            if (Config.EXP >= 0)
                            {
                                Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState()->GrantExpForParty(Config.EXP);
                            }
                        }
                    }
                }
            }

            /*if (ImGui::BeginCombo("Pal Name", combo_preview_Pal, flags))
            {
                for (int n = 0; n < IM_ARRAYSIZE(PalNames); n++)
                {
                    const bool is_selected = (palSelecteditem == n);
                    if (ImGui::Selectable(PalNames[n], is_selected))
                        palSelecteditem = n;

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            //ImGui::InputText("PalName", Config.PalName, sizeof(Config.PalName));
            ImGui::InputInt("PalRank", &Config.PalRank);
            ImGui::InputInt("Pallvl", &Config.PalLvL);
            if (ImGui::Button("Spawn Pal", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
            {
                if (Config.GetPalPlayerCharacter() != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        if (Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState() != NULL)
                        {
                            if (Config.PalName != NULL)
                            {
                                g_Console->printdbg("\n\n[+] PalName: %s [+]\n\n", g_Console->color.green, Config.ItemName);
                                SpawnPal((char*)combo_preview_Pal, Config.PalRank, Config.PalLvL);
                            }
                        }
                    }
                }
            }*/
            if (ImGui::Button("Teleport Home", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
            {
                SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
                if (p_appc != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        if (Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState() != NULL)
                        {
                            if (Config.IsSafe)
                            {
                                Config.GetPalPlayerCharacter()->GetPalPlayerController()->TeleportToSafePoint_ToServer();
                            }
                            else
                            {
                                Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState()->RequestRespawn();
                            }

                        }
                    }
                }

            }

            if (ImGui::Button("ToggleFly", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
            {
                Config.IsToggledFly = !Config.IsToggledFly;
                ExploitFly(Config.IsToggledFly);
            }

            if (ImGui::Button("NormalHealth", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
            {
                SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
                if (p_appc != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        if (Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState() != NULL)
                        {
                            SDK::FFixedPoint fixpoint = SDK::FFixedPoint();
                            fixpoint.Value = Config.GetPalPlayerCharacter()->CharacterParameterComponent->GetMaxHP().Value;
                            Config.GetPalPlayerCharacter()->ReviveCharacter_ToServer(fixpoint);
                        }
                    }
                }
            }

            if (ImGui::Button("GodHealth", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
            {
                SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
                if (p_appc != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        if (Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState() != NULL)
                        {
                            SDK::FFixedPoint fixpoint = SDK::FFixedPoint();
                            fixpoint.Value = 99999999;
                            Config.GetPalPlayerCharacter()->ReviveCharacter_ToServer(fixpoint);
                        }
                    }
                }
            }

            if (ImGui::Button("MaxWeight", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
            {
                SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
                if (p_appc != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        if (Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState() != NULL)
                        {
                            Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState()->InventoryData->MaxInventoryWeight = Config.MaxWeight;
                        }
                    }
                }
            }
            if (ImGui::Button("Catch Rate", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
            {
                Config.isCatchRate = !Config.isCatchRate;
                ToggleCatchRate(Config.isCatchRate);
            }
            ImGui::InputFloat("Catch Rate Modifier", &Config.CatchRate);
        }

        void TABQuickTP() // Credits to NuLLxD for compressing/making it look nicer and saving like 1000 lines of junk.
        {
            class TeleportTabs {
            public:
                TeleportTabs() : currentPage(0), buttonsPerPage(9) {
                    // Add your teleport locations here
                    locationMap["Anubis"] = Config.AnubisLocation;
                    locationMap["Astegon"] = Config.AstegonLocation;
                    locationMap["Azurobe"] = Config.AzurobeLocation;
                    locationMap["Beakon"] = Config.BeakonLocation;
                    locationMap["Billys Base"] = Config.BillysBase; // Trolling this kid on official NA 0046
                    locationMap["Broncherry Aqua"] = Config.BroncherryAquaLocation;
                    locationMap["Broncherry"] = Config.BroncherryLocation;
                    locationMap["Bushi"] = Config.BushiLocation;
                    locationMap["Chillet"] = Config.ChilletLocation;
                    locationMap["Dinossom Lux"] = Config.DinossomLuxLocation;
                    locationMap["Elizabee"] = Config.ElizabeeLocation;
                    locationMap["Felbat"] = Config.FelbatLocation;
                    locationMap["Fenglope"] = Config.FenglopeLocation;
                    locationMap["Frostallion"] = Config.FrostallionLocation;
                    locationMap["Grintale"] = Config.GrintaleLocation;
                    locationMap["Gumoss"] = Config.GumossLocation;
                    locationMap["Jetragon"] = Config.JetragonLocation;
                    locationMap["Jormuntide2"] = Config.Jormuntide2Location;
                    locationMap["Jormuntide"] = Config.JormuntideLocation;
                    locationMap["Katress"] = Config.KatressLocation;
                    locationMap["Kingpaca"] = Config.KingpacaLocation;
                    locationMap["Lunaris"] = Config.LunarisLocation;
                    locationMap["Mammorest"] = Config.MammorestLocation;
                    locationMap["Menasting"] = Config.MenastingLocation;
                    locationMap["Mossanda Lux"] = Config.MossandaLuxLocation;
                    locationMap["Nitewing"] = Config.NitewingLocation;
                    locationMap["Paladius"] = Config.PaladiusLocation;
                    locationMap["Penking"] = Config.PenkingLocation;
                    locationMap["Petallia"] = Config.PetalliaLocation;
                    locationMap["Quivern"] = Config.QuivernLocation;
                    locationMap["Relaxasaurus"] = Config.RelaxasaurusLuxLocation;
                    locationMap["Siblex"] = Config.SiblexLocation;
                    locationMap["Suzaku"] = Config.SuzakuLocation;
                    locationMap["Univolt"] = Config.UnivoltLocation;
                    locationMap["Vaelet"] = Config.VaeletLocation;
                    locationMap["Verdash"] = Config.VerdashLocation;
                    locationMap["Warsect"] = Config.WarsectLocation;
                    locationMap["Wumpo Botan"] = Config.WumpoBotanLocation;
                    // Add more teleport locations as needed

                    // Extract button names from the map
                    for (const auto& pair : locationMap) {
                        teleportLocations.push_back(pair.first);
                    }

                    UpdateCurrentPageButtons();
                }

                void Draw() {
                    // Draw buttons only if there are locations
                    if (teleportLocations.empty()) {
                        ImGui::Text("No teleport locations available.");
                        return;
                    }

                    // Draw buttons
                    for (int i = 0; i < currentButtons.size(); ++i) {
                        if (ImGui::Button(currentButtons[i].c_str(), ImVec2(ImGui::GetContentRegionAvail().x - 3, 20))) {
                            // Button logic
                            TeleportToLocation(currentButtons[i]);
                        }
                    }

                    // Draw page navigation
                    ImGui::Separator();
                    ImGui::Text("Page: %d", currentPage + 1);
                    ImGui::SameLine();
                    if (ImGui::Button("Previous")) {
                        currentPage = (currentPage - 1 + totalPages) % totalPages;
                        UpdateCurrentPageButtons();
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Next")) {
                        currentPage = (currentPage + 1) % totalPages;
                        UpdateCurrentPageButtons();
                    }
                }

                void TeleportToLocation(const std::string& location) {
                    // Check if the location exists in the map
                    if (locationMap.find(location) != locationMap.end()) {
                        SDK::FVector vector = { locationMap[location][0], locationMap[location][1], locationMap[location][2] };
                        AnyWhereTP(vector, Config.IsSafe);
                    }
                }

            private:
                void UpdateCurrentPageButtons() {
                    int startIdx = currentPage * buttonsPerPage;
                    int endIdx = (currentPage + 1) * buttonsPerPage;

                    if (startIdx < 0) {
                        startIdx = 0;
                    }

                    if (endIdx > teleportLocations.size()) {
                        endIdx = teleportLocations.size();
                    }

                    currentButtons.clear();
                    for (int i = startIdx; i < endIdx; ++i) {
                        currentButtons.push_back(teleportLocations[i]);
                    }

                    totalPages = (teleportLocations.size() + buttonsPerPage - 1) / buttonsPerPage;
                }

            private:
                std::vector<std::string> teleportLocations;
                std::vector<std::string> currentButtons;
                int currentPage;
                int buttonsPerPage;
                int totalPages;
                std::map<std::string, float*> locationMap; // Map button names to their corresponding locations in Config
            };
            static TeleportTabs teleportTabs; // Static to retain state between calls
            // Render your user interface
            teleportTabs.Draw();
        }

        void TABGameBreaking()
        {
            if (ImGui::Button("Max Level<50>", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
            {
                SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
                if (p_appc != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        if (Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState() != NULL)
                        {
                            Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState()->GrantExpForParty(99999999);
                        }
                    }
                }
            }
            if (ImGui::Button("All Effigies", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20))) //credit to bennett
            {
                SDK::APalPlayerCharacter* pPalCharacter = Config.GetPalPlayerCharacter();
                if (!pPalCharacter)
                    return;

                SDK::UWorld* world = Config.GetUWorld();
                if (!world)
                    return;

                SDK::TUObjectArray* objects = world->GObjects;

                for (int i = 0; i < objects->NumElements; ++i) {
                    SDK::UObject* object = objects->GetByIndex(i);

                    if (!object) {
                        continue;
                    }

                    if (!object->IsA(SDK::APalLevelObjectRelic::StaticClass())) {
                        continue;
                    }

                    SDK::APalLevelObjectObtainable* relic = (SDK::APalLevelObjectObtainable*)object;
                    if (!relic) {
                        continue;
                    }

                    ((SDK::APalPlayerState*)pPalCharacter->PlayerState)->RequestObtainLevelObject_ToServer(relic);
                }
            }
            if (ImGui::Button("Unlock Fast Travel", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20))) //credit aaacaaac
            {
                std::vector<std::string> keyStrings = {
                    "6E03F8464BAD9E458B843AA30BE1CC8F","DDBBFFAF43D9219AE68DF98744DF0831","603ED0CD4CFB9AFDC9E11F805594CCE5","6282FE1E4029EDCDB14135AA4C171E4C","9FBB93D84811BE424A37C391DBFBB476","979BF2044C8E8FE559B598A95A83EDE3","923B781345D2AB7ECED6BABD6E97ECE8",
                    "16C7164C43E2B96BEDCC6696E2E592F7","D27AFCAD472164F000D33A8D8B61FE8B","41727100495D21DC905D309C53989914","6DB6B7B2431CA2EFFFC88EB45805BA6A","74270C2F45B8DCA66B6A1FAAA911D024","DF9FB9CB41B43052A9C74FA79A826A50","8CA5E9774FF1BBC1156ABCA09E616480",
                    "15314BE94E2FB8D018D5749BE9A318F0","79C561B747335A7A0A8FBF9FAE280E62","23B9E99C4A454B99220AF7B4A58FD8DE","A1BC65AA445619EF338E0388BC010648","BF8B123244ADB794A06EA8A10503FBDD","F8DF603B4C750B37D943C9AF6A911946","596996B948716D3FD2283C8B5C6E829C",
                    "28D514E74B51FD9EB078A891DB0787C2","ACAE5FB04D48DE4197443E9C0993086B","4D2F204549AB656CA1EA4B8E39C484F3","1BDEABA240B1699541C17F83E59E61DF","2BC5E46049E69D3549CFB58948BE3288","91DAC6F34D2A9FD7F01471B5166C6C02","41E36D9A4B2BA79A3AD1B7B83B16F77D",
                    "76B000914943BADDC56BCFBAE2BF051E","DC0ECF9241B4410C59EE619F56D1106A","71C4B2B2407F2BBBD77572A20C7FF0F5","EC94023A4CA571FF0FD19E90944F4231","2A2B744B41AC79964DAE6B89CAC51FC3","E0819EFB41581AEAC3A029B0EE2FE195","22095BFA48A46172F8D154B2EBEB7493",
                    "7C5E91514F6E84B0C1DEFFB52C7C4DBA","AECFED0D41AFEE11F30B4F9687BC3243","2EC07ACC4505CB726DE38A84246CA999","F8E5CB8143F4FA2F6213E6B454569F87","5F426B49469368B0C131D3A6DB8F7831","A277AE6341EF40D84D711EA52303353F","6231802D40C81C00445379AE238D9F90",
                    "F6C005A14B38FE0B57F1C7869FD899CB","7170881D44249E90902F728E240493AF","3E8E504B4A3975FD3862E1BC85A5D4F6","B001852C491FF5E70C4747BFF9972924","2DE1702048A1D4A82126168C49BE51A9","E88379634CB5B6117DA2E7B8810BFE0A","3697999C458BF8A3C7973382969FBDF9",
                    "65B10BB14ABDA9C2109167B21901D195","4669582D4081BF550AFB66A05D043A3D","FE90632845114C7FBFA4669D071E285F","5970E8E648D2A83AFDFF7C9151D9BEF5","B639B7ED4EE18A7AA09BA189EA703032","099440764403D1508D9BADADF4848697","B44AA24445864494E7569597ACCAEFC6",
                    "3A0F123947BE045BC415C6B061A5285A","F382ADAE4259150BF994FF873ECF242B", "866881DB443444AA7F4E7C8E5DCDAA29", "01ACCA6E4BDAA68220821FB05AB54E4D", "75BD9923489E2A4EBCED5A81175D5928", "513E166044565A0BD3360F94142577E8"
                };

                SDK::APalPlayerCharacter* pPalCharacter = Config.GetPalPlayerCharacter();

                for (const std::string& keyString : keyStrings)
                {
                    SDK::UKismetStringLibrary* lib = SDK::UKismetStringLibrary::GetDefaultObj();
                    //Convert FNAME
                    wchar_t  ws[255];
                    swprintf(ws, 255, L"%hs", keyString.c_str());
                    SDK::FName FNameKS = lib->Conv_StringToName(SDK::FString(ws));

                    ((SDK::APalPlayerState*)pPalCharacter->PlayerState)->RequestUnlockFastTravelPoint_ToServer(FNameKS);
                }

            }
            if (ImGui::Button("Crash Server", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
            {
                if (Config.GetPalPlayerCharacter() != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        SDK::UWorld* world = Config.GetUWorld();
                        if (!world)
                            return;

                        SDK::TUObjectArray* objects = world->GObjects;

                        for (int i = 0; i < objects->NumElements; ++i) {
                            SDK::UObject* object = objects->GetByIndex(i);

                            if (!object) {
                                continue;
                            }

                            if (!object->IsA(SDK::APalMonsterCharacter::StaticClass())) {
                                continue;
                            }

                            SDK::APalMonsterCharacter* Monster = (SDK::APalMonsterCharacter*)object;
                            if (!object) {
                                continue;
                            }

                            Config.GetPalPlayerCharacter()->GetPalPlayerController()->RequestLiftup_ToServer((SDK::APalCharacter*)object);
                        }

                    }
                }
            }
            if (ImGui::Button("Killaura", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
            {
                if (Config.GetPalPlayerCharacter() != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        if (Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState())
                        {
                            SDK::TArray<SDK::AActor*> T = Config.GetUWorld()->PersistentLevel->Actors;
                            for (int i = 0; i < T.Count(); i++)
                            {

                                if (T[i] != NULL)
                                {
                                    if (T[i]->IsA(SDK::APalCharacter::StaticClass()))
                                    {
                                        SDK::APalCharacter* monster = (SDK::APalCharacter*)T[i];
                                        if (monster->IsLocallyControlled())
                                        {
                                            continue;
                                        }
                                        Config.GetPalPlayerState()->SendDeath_ToServer(monster);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            if (ImGui::Button("Clone", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
            {
                if (Config.GetPalPlayerCharacter() != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        if (Config.CloneCharacter != NULL)
                        {
                            /*char PalName[7] = "Anubis";
                            SDK::UKismetStringLibrary* lib = SDK::UKismetStringLibrary::GetDefaultObj();
                            wchar_t  ws[255];
                            swprintf(ws, 255, L"%hs", PalName);
                            SDK::FName Name = lib->Conv_StringToName(SDK::FString(ws));*/

                            //g_Console->printdbg("Start Spawning %s...", g_Console->color.blue,PalName);
                            SDK::FNetworkActorSpawnParameters sp;
                            //sp.NetworkOwner = Config.CloneCharacter->Owner;
                            sp.Name = Config.CloneCharacter->Name;
                            sp.Owner = Config.CloneCharacter->Owner;
                            sp.SpawnLocation = Config.GetPalPlayerCharacter()->K2_GetActorLocation();
                            sp.SpawnRotation = Config.GetPalPlayerCharacter()->K2_GetActorRotation();
                            sp.SpawnScale = { 1,1,1 };
                            sp.ControllerClass = Config.CloneCharacter->AIControllerClass;
                            sp.SpawnCollisionHandlingOverride = SDK::ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

                            SDK::FGuid guid;

                            guid.A = 1221412521;
                            guid.B = 12512312312;
                            Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->SpawnActor_ToServer(SDK::APalCharacter::StaticClass(), sp, guid);
                        }
                    }
                }
            }
        }
        
        void TABConfig()
        {
            
            ImGui::Text("SoTMaulder Menu");
            ImGui::Text("Version: v2.7");
            ImGui::Text("Credits to: bluesword007");
            ImGui::Text("Credits to: Palworld Offsets UnknownCheats.me");

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();
            if (ImGui::Button("Unload DLL", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20))) {
#if DEBUG
                g_Console->printdbg("\n\n[+] UNHOOK INITIALIZED [+]\n\n", Console::Colors::red);

#endif
                g_KillSwitch = TRUE;
            }
        }
        
        

        void TABItemSpawner()
        {
            static int num_to_add = 1;
            static int category = 0;

            ImGui::InputInt("Num To Add", &num_to_add);

            ImGui::Combo("Item Category", &category, "Accessories\0Ammo\0Armor\0Crafting Materials\0Eggs\0Food\0Hats\0\Medicine\0Money\0Other\0Pal Spheres\0Saddles\0Seeds\0Tools\0Weapons\0\All\0");

            std::initializer_list list = database::all;

            switch (category)
            {
            case 1:
                list = database::ammo;
                break;
            case 2:
                list = database::armor;
                break;
            case 3:
                list = database::craftingmaterials;
                break;
            case 4:
                list = database::eggs;
                break;
            case 5:
                list = database::food;
                break;
            case 6:
                list = database::hats;
                break;
            case 7:
                list = database::medicine;
                break;
            case 8:
                list = database::money;
                break;
            case 9:
                list = database::other;
                break;
            case 10:
                list = database::palspheres;
                break;
            case 11:
                list = database::saddles;
                break;
            case 12:
                list = database::seeds;
                break;
            case 13:
                list = database::toolss;
                break;
            case 14:
                list = database::weapons;
                break;
            case 15:
                list = database::all;
                break;
            default:
                list = database::all;
            }

            int cur_size = 0;

            static char item_search[100];

            ImGui::InputText("Search", item_search, IM_ARRAYSIZE(item_search));

            for (const auto& item : list) {
                std::istringstream ss(item);
                std::string left_text, right_text;

                std::getline(ss, left_text, '|');
                std::getline(ss, right_text);

                auto right_to_lower = right_text;
                std::string item_search_to_lower = item_search;

                std::transform(right_to_lower.begin(), right_to_lower.end(), right_to_lower.begin(), ::tolower);
                std::transform(item_search_to_lower.begin(), item_search_to_lower.end(), item_search_to_lower.begin(), ::tolower);

                if (item_search[0] != '\0' && (right_to_lower.find(item_search_to_lower) == std::string::npos))
                    continue;

                if (cur_size != 0 && cur_size < 20)
                {
                    ImGui::SameLine();
                }
                else if (cur_size != 0)
                {
                    cur_size = 0;
                }

                cur_size += right_text.length();

                ImGui::PushID(item);
                if (ImGui::Button(right_text.c_str()))
                {
                    SDK::UPalPlayerInventoryData* InventoryData = Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState()->GetInventoryData();
                    AddItemToInventoryByName(InventoryData, (char*)left_text.c_str(), num_to_add);
                }
                ImGui::PopID();
            }
        }

        void TABQuick()
        {
            if (ImGui::Button("Basic Items stack", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
                SpawnMultiple_ItemsToInventory(config::QuickItemSet::basic_items_stackable);

            if (ImGui::Button("Basic Items single", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
                SpawnMultiple_ItemsToInventory(config::QuickItemSet::basic_items_single);

            if (ImGui::Button("Unlock Pal skills", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
                SpawnMultiple_ItemsToInventory(config::QuickItemSet::pal_unlock_skills);

            if (ImGui::Button("Spheres", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
                SpawnMultiple_ItemsToInventory(config::QuickItemSet::spheres);

            if (ImGui::Button("Tools", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
                    SpawnMultiple_ItemsToInventory(config::QuickItemSet::tools);
        }
        
        void TABDebug()
        {
            ImGui::Checkbox("DEBUG ESP", &Config.isDebugESP);
            if (Config.isDebugESP)
            {
                ImGui::SameLine();
                ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
                ImGui::SliderFloat("##DISTANCE", &Config.mDebugESPDistance, 1.0f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
            }

            //  @TODO: print additional debug information
            if (ImGui::Button("PrintPlayerAddr", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
            {
                SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
                if (p_appc)
                    g_Console->printdbg("\n\n[+] APalPlayerCharacter: 0x%llX\n", Console::Colors::green, p_appc);
                
            }

            ImGui::InputTextWithHint("##INPUT", "INPUT GOBJECT fn NAME", inputBuffer_getFnAddr, 100);
            ImGui::SameLine();
            if (ImGui::Button("GET fn", ImVec2(ImGui::GetContentRegionAvail().x, 20)))
            {
                std::string input = inputBuffer_getFnAddr;
                SDK::UFunction* object = SDK::UObject::FindObject<SDK::UFunction>(input);
                if (object)
                {
                    static __int64 dwHandle = reinterpret_cast<__int64>(GetModuleHandle(0));
                    void* fnAddr = object->ExecFunction;
                    unsigned __int64 fnOffset = (reinterpret_cast<__int64>(fnAddr) - dwHandle);
                    g_Console->printdbg("[+] Found [%s] -> 0x%llX\n", Console::Colors::yellow, input.c_str(), fnOffset);
                }
                else
                    g_Console->printdbg("[!] OBJECT [%s] NOT FOUND!\n", Console::Colors::red, input.c_str());
                memset(inputBuffer_getFnAddr, 0, 100);
            }

        }
	}

	void Menu::Draw()
	{

		if (g_GameVariables->m_ShowMenu)
			MainMenu();

		if (g_GameVariables->m_ShowHud)
			HUD(&g_GameVariables->m_ShowHud);

		if (g_GameVariables->m_ShowDemo)
			ImGui::ShowDemoWindow();
	}

    void Menu::ManagerMenu()
    {
        if (!ImGui::Begin("Manager", &g_GameVariables->m_ShowMenu, 96))
        {
            ImGui::End();
            return;
        }


        if (Config.gWorld)
        {
            ImGui::Checkbox("filterPlayer", &Config.filterPlayer);
            SDK::TArray<SDK::AActor*> T = Config.GetUWorld()->PersistentLevel->Actors;
            for (int i = 0; i < T.Count(); i++)
            {
                if (!T[i])
                    continue;

                if (!T[i]->IsA(SDK::APalCharacter::StaticClass()))
                    continue;

                SDK::APalCharacter* Character = (SDK::APalCharacter*)T[i];
                SDK::FString name;
                if (Config.filterPlayer)
                {
                    if (!T[i]->IsA(SDK::APalPlayerCharacter::StaticClass()))
                        continue;
                }
                if (T[i]->IsA(SDK::APalPlayerCharacter::StaticClass()))
                {
                    if (!Character)
                        continue;

                    Character->CharacterParameterComponent->GetNickname(&name);
                }
                else
                {
                    SDK::UKismetStringLibrary* lib = SDK::UKismetStringLibrary::GetDefaultObj();
                    if (!Character)
                        continue;

                    std::string s = Character->GetFullName();
                    size_t firstUnderscorePos = s.find('_');

                    if (firstUnderscorePos != std::string::npos)
                    {
                        std::string result = s.substr(firstUnderscorePos + 1);

                        size_t secondUnderscorePos = result.find('_');

                        if (secondUnderscorePos != std::string::npos) {
                            result = result.substr(0, secondUnderscorePos);
                        }
                        wchar_t  ws[255];
                        swprintf(ws, 255, L"%hs", result);
                        name = SDK::FString(ws);
                    }
                }
                ImGui::Text(name.ToString().c_str());
                ImGui::SameLine();
                ImGui::PushID(i);
                if (ImGui::Button("Kill"))
                {
                    if (T[i]->IsA(SDK::APalCharacter::StaticClass()))
                        Damage(Character, 99999999999);
                }
                ImGui::SameLine();
                if (ImGui::Button("TP"))
                {
                    if (Config.GetPalPlayerCharacter() != NULL)
                    {
                        if (Character)
                        {
                            SDK::FVector vector = Character->K2_GetActorLocation();
                            AnyWhereTP(vector, Config.IsSafe);
                        }
                    }
                }

                /*if (Character->IsA(SDK::APalPlayerCharacter::StaticClass()))
                {
                    ImGui::SameLine();
                    if (ImGui::Button("Boss"))
                    {
                        if (Config.GetPalPlayerCharacter() != NULL)
                        {
                            auto controller = Config.GetPalPlayerCharacter()->GetPalPlayerController();
                            if (controller != NULL)
                            {
                                controller->Transmitter->BossBattle->RequestBossBattleEntry_ToServer(SDK::EPalBossType::ElectricBoss, (SDK::APalPlayerCharacter*)Character);
                                controller->Transmitter->BossBattle->RequestBossBattleStart_ToServer(SDK::EPalBossType::ElectricBoss, (SDK::APalPlayerCharacter*)Character);
                            }
                        }
                    }
                }*/
                if (Character->IsA(SDK::APalPlayerCharacter::StaticClass()))
                {
                    ImGui::SameLine();
                    if (ImGui::Button("MaskIt"))
                    {
                        if (Config.GetPalPlayerCharacter() != NULL)
                        {
                            auto controller = Config.GetPalPlayerCharacter()->GetPalPlayerController();
                            if (controller != NULL)
                            {
                                auto player = (SDK::APalPlayerCharacter*)Character;
                                SDK::FString fakename;
                                player->CharacterParameterComponent->GetNickname(&fakename);
                                Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->NetworkIndividualComponent->UpdateCharacterNickName_ToServer(Config.GetPalPlayerCharacter()->CharacterParameterComponent->IndividualHandle->ID, fakename);
                            }
                        }
                    }
                }
                ImGui::PopID();
            }

        }

        if (Config.GetUWorld() != NULL)
        {
        }

        ImGui::End();
    }
	
    void Menu::MainMenu()
	{
        if (!g_GameVariables->m_ShowDemo)
            Styles::InitStyle();

        if (g_Menu->dbg_RAINBOW_THEME) {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(g_Menu->dbg_RAINBOW));
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(g_Menu->dbg_RAINBOW));
            ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(g_Menu->dbg_RAINBOW));
        }
        if (!ImGui::Begin("SoTMaulder-Palworld", &g_GameVariables->m_ShowMenu, 96))
        {
            ImGui::End();
            return;
        }
        if (g_Menu->dbg_RAINBOW_THEME) {
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
        }
        
        ImGuiContext* pImGui = GImGui;

        //  Display Menu Content
        //Tabs::TABMain();

        ImGui::Text("W.I.P. Some Functions Might Not work.");

        if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
        {
            if (ImGui::BeginTabItem("Player"))
            {
                Tabs::TABPlayer();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Exploits"))
            {
                Tabs::TABExploit();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Item Spawner"))
            {
                Tabs::TABItemSpawner();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Quick TP"))
            {
                Tabs::TABQuickTP();
                ImGui::EndTabItem();
            }
#if DEBUG
                if (ImGui::BeginTabItem("DEBUG"))
                {
                    Tabs::TABDebug();
                    ImGui::EndTabItem();
                }
#endif
            if (ImGui::BeginTabItem("GameBreaking"))
            {
                Tabs::TABGameBreaking();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Info"))
            {
                Tabs::TABConfig();
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
        ImGui::End();



        if (Config.bisOpenManager)
            ManagerMenu();
	}

	void Menu::HUD(bool* p_open)
	{
        
        ImGui::SetNextWindowPos(g_D3D11Window->pViewport->WorkPos);
        ImGui::SetNextWindowSize(g_D3D11Window->pViewport->WorkSize);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, NULL);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.00f, 0.00f, 0.00f, 0.00f));
        if (!ImGui::Begin("##HUDWINDOW", (bool*)true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs))
        {
            ImGui::PopStyleColor();
            ImGui::PopStyleVar();
            ImGui::End();
            return;
        }
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();

        auto ImDraw = ImGui::GetWindowDrawList();
        auto draw_size = g_D3D11Window->pViewport->WorkSize;
        auto center = ImVec2({ draw_size.x * .5f, draw_size.y * .5f });
        auto top_center = ImVec2({ draw_size.x * .5f, draw_size.y * 0.0f });
        
        //  Watermark
        ImDraw->AddText(top_center, g_Menu->dbg_RAINBOW, "SoTMaulder Palworld");

        if (Config.IsESP)
            ESP();

        if (Config.isDebugESP)
            ESP_DEBUG(Config.mDebugESPDistance, ImVec4(0, 1, 0, 1));

        ImGui::End();
	}

    void Menu::Loops()
    {
        //  Respawn
        if ((GetAsyncKeyState(VK_F5) & 1))
            RespawnLocalPlayer(Config.IsSafe);

        //  Revive Player
        if ((GetAsyncKeyState(VK_F6) & 1))
            ReviveLocalPlayer();

        //  
        if (Config.IsSpeedHack)
            SpeedHack(Config.SpeedModiflers);
        
        //  
        if (Config.IsAttackModiler)
            SetPlayerAttackParam(Config.DamageUp);

        //  
        if (Config.IsDefuseModiler)
            SetPlayerDefenseParam(Config.DefuseUp);

        //  
        if (Config.IsInfStamina)
            ResetStamina();

        //  
        // if (Config.GetPalPlayerCharacter() != NULL)
        {
            if (Config.GetPalPlayerCharacter()->ShooterComponent != NULL && Config.GetPalPlayerCharacter()->ShooterComponent->CanShoot())
            {
                if (Config.GetPalPlayerCharacter()->ShooterComponent->GetHasWeapon() != NULL)
                {
                    Config.GetPalPlayerCharacter()->ShooterComponent->GetHasWeapon()->IsRequiredBullet = !Config.IsInfinAmmo;
                }
            }
        }
        //  SetDemiGodMode(Config.IsMuteki);
    }
}