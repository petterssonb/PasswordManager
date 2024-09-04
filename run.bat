@echo off
if exist build\main.exe (
    build\main.exe
) else (
    echo "Program not built yet. Run build.bat first."
)