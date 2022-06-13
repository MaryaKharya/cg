#pragma once

#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <math.h>
#include <string>
