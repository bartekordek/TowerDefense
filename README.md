# Simple Tower Defense game in UE4.
* [Setup](#setup)

## Setup
* Before cloning, please make sure that your user is a member of
```
$ https://github.com/EpicGames
```
To do that you need to go to their github page and request access.

* After cloning this repo, please run:
```
$ git submodule update --recursive --init
```

* After repo is cloned, go to:
```
$ deps/UnrealEngine
```
And Run `Setup.bat` and `GenerateProjectFiles.bat`.
* After the command is completed, you need to go to:
```
$ deps/UnrealEngine/Engine/Binaries/Win64
```

and run: `UnrealVersionSelector-Win64-Shipping.exe`.
* In `TowerDefense` dir, right-click on .uproject file and select: `Switch Unreal...` and select the version from root dir.
* After that double click on uproject. The rest should be e-z.