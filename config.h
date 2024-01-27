#pragma once
#include <Windows.h>
#include "libs/utils/memory.h"
#include <map>
#include "SDK.hpp"
#include "database.h"

typedef bool(*Tick)(SDK::APalPlayerCharacter* m_this,float DeltaSecond);
typedef void(*GetAllPlayer)(SDK::UPalCharacterImportanceManager* i_this, SDK::TArray<SDK::APalCharacter*>* OutArray);
typedef void(*CatchRate)(SDK::APalCaptureJudgeObject* m_this);


class config
{
public:
	DWORD64 ClientBase = 0;
	DWORD64 offset_Tick = 0x2AB1DC0;
	DWORD64 offset_AddStatus = 0x7EA520; //UPalNetworkIndividualComponent::AddPlayerCharacterStatusPoint_ToServer
	DWORD64 offset_CatchRate = 0x26E70C2; //APalCaptureJudgeObject::ChallengeCapture

	//TP Locations
	float AnubisLocation[3] = { -170269, 94163.7, -1527.83 };
	float FrostallionLocation[3] = { 111978, -6394.85, 21940.2 };
	float JetragonLocation[3] = { -270762, -205837, 3834.92 };
	float PaladiusLocation[3] = { 187235, 349924, 2563.07 };

	//�˵��ж�
	bool IsESP = false;
	bool IsAimbot = false;
	bool IsSpeedHack = false;
	bool IsAttackModiler = false;
	bool IsDefuseModiler = false;
	bool IsInfStamina = false;
	bool IsSafe = true;
	bool IsInfinAmmo = false;
	bool IsMuteki = false;
	bool IsAdmin = true;
	bool IsRevive = false;
	bool IsToggledFly = false;
	bool isCatchRate = false;

	//����
	float SpeedModiflers = 1.0f;
	float CatchRate = 1;
	int DamageUp = 0;
	int DefuseUp = 0;
	int EXP = 0;
	int Item = 0;
	int PalRank = 0;
	int MaxWeight = 9999999;
	float Pos[3] = { 0,0,0 };
	char ItemName[255];
	char PalName[255];
	char inputTextBuffer[255] = "";
	static SDK::UWorld* gWorld;
	int PalLvL = 1;
	SDK::APalPlayerCharacter* localPlayer = NULL;
	SDK::TArray<SDK::APalPlayerCharacter*> AllPlayers = {};
	SDK::UPalCharacterImportanceManager* UCIM = NULL;
	SDK::UObject* WorldContextObject = NULL;
	std::vector<std::string> db_filteredItems;
	
	//����
	static SDK::UWorld* GetUWorld();
	static SDK::UPalCharacterImportanceManager* GetCharacterImpManager();
	static SDK::APalPlayerCharacter* GetPalPlayerCharacter();
	static SDK::APalPlayerState* GetPalPlayerState();
	static SDK::TArray<SDK::APalPlayerCharacter*> GetTAllPlayers();
	static bool	GetTAllPlayers(SDK::TArray<class SDK::APalCharacter*>* outResult);
	static bool	GetTAllImpNPC(SDK::TArray<class SDK::APalCharacter*>* outResult);
	static bool	GetTAllNPC(SDK::TArray<class SDK::APalCharacter*>* outResult);
	static bool	GetTAllPals(SDK::TArray<class SDK::APalCharacter*>* outResult);
	static void Init();;
	static void Update(const char* filterText);
	static const std::vector<std::string>& GetFilteredItems();
};
extern config Config;

