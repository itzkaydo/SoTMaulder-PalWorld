# PalWorld-SotMaulder
This is the PalWorld simple hack.
modifying player data in the Player tab
Hacking in the Exploit tab
# Note: The master branch does not include visual

# Player Features
- Modify Player Speed
- Modify Player Attack Power
- Modify Player Defense Power
- Infinite Stamina
- Infinite Ammo

# Exploits
- SafeTeleport(You can choose the implementation for TP)  
- HomeTP  
- AnywhereTP(It requires you to manually give a position)  
- ToggleFly  
- DeleteSelf(Warning: After testing, it will delete your data on the server)  
- GodHealth  
- Give EXP (Credit: WoodgamerHD)
- Item Spawner
- Effigy Gatherer

# AOBS
> GObjects: `48 8B 05 ? ? ? ? 48 8B 0C C8 4C 8D 04 D1 EB 03`  
> FNames: `48 8D 05 ? ? ? ? EB 13 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 0F 10`  
> GWorld: `48 8B 1D ?? ?? ?? ?? 48 85 DB 74 33 41 B0`  
> Processs Event: `40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC 10 01 ? ? 48 8D`

## External Library Credits
[Dear ImGui](https://github.com/ocornut/imgui)  
[MinHook](https://github.com/TsudaKageyu/minhook)  
[Dumper7](https://github.com/Encryqed/Dumper-7)  
[DX11-Internal-Base](https://github.com/NightFyre/DX11-ImGui-Internal-Hook)  
