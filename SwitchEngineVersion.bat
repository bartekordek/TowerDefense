@echo off

set BASE_SOURCE=%~dp0
set BASE_ENGINE=%BASE_SOURCE%deps\UnrealEngine\Engine
set BASE_PROJECT=%BASE_SOURCE%TowerDefense
set PROJECT_FILE=%BASE_PROJECT%\TowerDefense.uproject
set ENGINE_BUILD_BAT=%BASE_ENGINE%\Build\BatchFiles\Build.bat

echo Source base: %BASE_SOURCE%
echo Engine base: %BASE_ENGINE%
echo Project file: %PROJECT_FILE%
echo Engine build: %ENGINE_BUILD_BAT%

call %BASE_ENGINE%\Build\BatchFiles\Build.bat  -projectfiles -project="%PROJECT_FILE%" -game -engine -progress -log="SwitchEngineLog.log"