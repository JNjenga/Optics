workspace 'VisonWorkspace'
	location 'workspace'
	architecture 'x86'
	language 'C++'
	startproject 'vision'
	configurations { "Debug", "Release" }

	
	filter {'configurations:Debug'}
		symbols 'On'
	filter {'configurations:Release'}
		optimize 'On'
	filter {}

	targetdir 'bin'

	objdir 'bin/obj'

project 'Vision'
	kind 'ConsoleApp'
	language 'C++'

	includedirs{
		'deps/glfw/include',
		'deps/glew/include',
		'deps/glm',
		'deps/stb',
		'src',
	}

	pchheader "vis_pch.hpp"

	files {
		'src/**.cpp',
		'src/**.hpp',
		'src/**.h'
	}

	libdirs {
		'deps/glfw/lib-vc2017',
		'deps/glew/lib',
	}
	
	links {
		'glfw3',
		'glew32'
	}

	filter {'system:windows'}
		links {'Opengl32'}
		defines{ '_CRT_SECURE_NO_WARNINGS' }
	filter{}

	filter {'system:not windows'}
		links {
			"GL",
			"dl",
			"pthread",
			"X11",
			"Xxf86vm",
			"Xrandr",
			"Xi",
			"Xinerama",
			"Xcursor",
		}
