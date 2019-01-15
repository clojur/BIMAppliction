@echo off

set "current_dir_name=%cd%"
:loop
set "current_dir_name=%current_dir_name:*\=%"
set "current_dir_nametmp=%current_dir_name:\=%"
if not "%current_dir_nametmp%"=="%current_dir_name%" goto loop
del ..\..\..\Intermediate\ProjectFiles\%current_dir_name%.*

rem genreate program solution
echo Using UnrealBuildTool Genreate Program "%current_dir_name%" solution
echo ..\..\..\Binaries\DotNET\UnrealBuildTool.exe -ProjectFiles %current_dir_name%
..\..\..\Binaries\DotNET\UnrealBuildTool.exe -ProjectFiles %current_dir_name% -2017

rem open project vs solution
rem echo open solution Intermediate\ProjectFiles\%current_dir_name%.vcxproj
rem cmd /c "..\..\..\Intermediate\ProjectFiles\%current_dir_name%.vcxproj"

pause