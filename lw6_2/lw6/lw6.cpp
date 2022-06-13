// 01_simple_vertex_shader.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include "MyApplication.h"


CMyApplication app("Simple fragment shader", 800, 500);


int _tmain(int argc, _TCHAR* argv[])
{
	glewInit();
	if (!GLEW_ARB_shader_objects)
	{
		return -1;
	}

	try
	{
		app.MainLoop();
	}
	catch (std::exception const& e)
	{
		std::cout << e.what();
	}

	return 0;
}