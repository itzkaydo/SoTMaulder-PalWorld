#pragma once
#include <Windows.h>
#include "libs/utils/memory.h"
#include "SDK.hpp"

typedef bool(*Tick)(SDK::APalPlayerCharacter* m_this,float DeltaSecond);


class config
{
public:
	DWORD64 ClientBase = 0;
	DWORD64 offset_Tick = 0x2AB44D0;
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

	//����
	float SpeedModiflers = 1.0f;
	int DamageUp = 0;
	int DefuseUp = 0;
	int MaxWeight = 9999999;
	SDK::APalPlayerCharacter* localPlayer = NULL;
	
	//����
	static SDK::UWorld* GetUWorld();
	static SDK::APalPlayerCharacter* GetPalPlayerCharacter();
	static void Init();
};
extern config Config;

