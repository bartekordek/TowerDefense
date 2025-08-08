rem @echo off

set ROOT_PATH=%~dp0
echo Root: %ROOT_PATH%

set ENGINE_PATH=%ROOT_PATH%deps\UnrealEngine\Engine
echo Engine: %ENGINE_PATH%

set ROOT_PROJECT=%ROOT_PATH%TowerDefense
echo Project: %ROOT_PROJECT%

set ENGINE_BATCH_GENERATOR=%ENGINE_PATH%\Build\BatchFiles\GenerateProjectFiles.bat
echo Batch Generator: %ENGINE_BATCH_GENERATOR%

set MAIN_PROJ_PATH=%ROOT_PROJECT%\TowerDefense.uproject
echo Proj Path: %MAIN_PROJ_PATH%

call "%ENGINE_BATCH_GENERATOR%" -projectfiles -project="%MAIN_PROJ_PATH%" -game -progress -log="GenerateLog.log"
