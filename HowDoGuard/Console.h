
#pragma once

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "Defines.h"

#ifdef WINDOWS

#include <windows.h>

#endif 

#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

using namespace std;

#ifdef WINDOWS

static const WORD MAX_CONSOLE_LINES = 500;

#endif

void init_console( void );

#endif //__CONSOLE_H__