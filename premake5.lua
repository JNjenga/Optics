workspace 'ViisonWorkspace'
	location 'workspace'
	architecture 'x86_64'
	language 'C++'
	startproject 'Vision'
	configurations { "Debug", "Release" }

	
	filter {'configurations:Debug'}
		symbols 'On'
	filter {'configurations:Release'}
		optimize 'On'
	filter {}

	targetdir 'bin'

	objdir 'bin/Obj'

	-- cppdialect 'C++11'

-- Include Glad
include '3rdParty/glad'
include '3rdParty/glfw'
-- include '3rdParty/dearimgui'

project 'Vision'
	kind 'ConsoleApp'
	language 'C++'

	includedirs{
		'3rdParty/glfw/include',
		'3rdParty/glad/include',
		'3rdParty/glm',
		'src',
	}

	-- pchheader "src/vis_pch.hpp"

	files {
		'src/**.cpp',
		'src/**.hpp',
		'src/**.h'
	}

	links {
		'GlfwStatic3.3',
		'Glad'
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
