@echo off

set ROOT_PATH=%~dp0
echo Root: %ROOT_PATH%

echo Test: %~dp1%~2

set ENGINE_PATH=%ROOT_PATH%Engine
echo Engine: %ENGINE_PATH%

set ENGINE_BATCH_GENERATOR=%ENGINE_PATH%\\Build\BatchFiles\GenerateProjectFiles.bat
echo Batch Generator: %ENGINE_BATCH_GENERATOR%

set LYRA_PROJ_PATH=%ROOT_PATH%Samples\\Games\\Lyra\\Lyra.uproject
echo Proj Path: %LYRA_PROJ_PATH%

rem call "%ENGINE_BATCH_GENERATOR%" -projectfiles -project="%LYRA_PROJ_PATH%" -game -progress -log="GenerateLog.log"
rem F:\Dev\TowerDefense\TowerDefense\GenerateProjectsFiles.bat