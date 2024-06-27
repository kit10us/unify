#!/bin/bash

function End
{
	exit -1
}


function RemoveFile
{
	if [ -f "$1" ]; then
		rm "$1"
	fi
}

function RemoveDir
{
	rm -rf $1
}


# CMake files
RemoveFile CMakeCache.txt
RemoveDir CMakeFiles

# XCode
RemoveDir build


End