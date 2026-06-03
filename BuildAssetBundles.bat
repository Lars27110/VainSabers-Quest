@echo off
REM Build Asset Bundles Script for VainSabers (Batch version)
REM This script builds asset bundles without needing to open Unity manually

setlocal enabledelayedexpansion

REM Configuration
set "UNITY_PATH=C:\Program Files\Unity\Hub\Editor\2021.3.16f1\Editor\Unity.exe"
set "PROJECT_PATH=%~dp0VainSabers asset creation"
set "OUTPUT_PATH=%~dp0VainSabers"

REM Check if Unity exists
if not exist "%UNITY_PATH%" (
    echo Error: Unity not found at: %UNITY_PATH%
    echo.
    echo Please ensure Unity is installed or update the UNITY_PATH variable in this script.
    echo You can find your Unity installation path in Unity Hub.
    exit /b 1
)

REM Check if project exists
if not exist "%PROJECT_PATH%" (
    echo Error: Project not found at: %PROJECT_PATH%
    exit /b 1
)

echo.
echo ========================================
echo Building Asset Bundles for VainSabers
echo ========================================
echo.
echo Unity Path: %UNITY_PATH%
echo Project Path: %PROJECT_PATH%
echo Output Path: %OUTPUT_PATH%
echo.

REM Run Unity in batch mode
echo Starting build process...
"%UNITY_PATH%" ^
    -projectPath "%PROJECT_PATH%" ^
    -executeMethod CreateAssetBundles.BuildAllAssetBundles ^
    -quit ^
    -batchmode ^
    -nographics ^
    -logFile "%PROJECT_PATH%\Logs\BuildLog.txt"

REM Check result
if %ERRORLEVEL% equ 0 (
    echo.
    echo ========================================
    echo Asset bundles built successfully!
    echo Output: %OUTPUT_PATH%
    echo ========================================
    echo.
    exit /b 0
) else (
    echo.
    echo ========================================
    echo ERROR: Build failed with exit code %ERRORLEVEL%
    echo ========================================
    echo.
    exit /b %ERRORLEVEL%
)
