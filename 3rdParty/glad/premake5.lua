

project "Glad"
	
	kind "StaticLib"
	language "C"
	pic "On"

	filter{}

	files {

			"src/glad.c",
		}
	includedirs {"include"}
	-- includedirs {"src","Glfw/include"}
	defines {
		"_CRT_SECURE_NO_WARNINGS","_WINDOWS",
	  }
	  filter{}


