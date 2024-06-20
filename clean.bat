@echo off
setlocal

set PROJECTS=ALL_BUILD ZERO_CHECK unify
set PROJECT_FILE_EXTENSIONS=vcxproj vcxproj.filters vcxproj.user
set CONFIGS=DebugWindows ReleaseWindows

for %%p in (%PROJECTS%) do (
for %%e in (%PROJECT_FILE_EXTENSIONS%) do (
	call:call_remove_file %%p.%%e
)
)

call:call_remove_file CMakeCache.txt
call:call_remove_dir CMakeFiles
call:call_remove_file cmake_install.cmake
call:call_remove_file Unify.sln
call:call_remove_dir Unify.dir

goto goto_exit


:call_remove_file
set FILE=%1
if EXIST %FILE% (
	echo Removing file %FILE%
 	del %FILE%
)
goto :eof


:call_remove_dir
set DIRECTORY=%1%
if EXIST %DIRECTORY%\ (
	echo Removing directory %DIRECTORY%
	rmdir /s /q %DIRECTORY%
)
goto :eof


:goto_exit
