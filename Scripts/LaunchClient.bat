@echo off

set PROJECT_NAME=GCDemo
set UE5_PATH="D:\Epic Games\UE_5.1\Engine\Binaries\Win64\UnrealEditor.exe"
set PROJECT_PATH="C:\Users\Neoxyne\Desktop\GCDemo"

%UE5_PATH% %PROJECT_PATH%\%PROJECT_NAME%.uproject 127.0.0.1 -game -log
