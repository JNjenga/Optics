(vertex)

#version 330 core

in vec3 aPos;
in vec2 aTex;

out vec2 tex_coord;

uniform mat4 p_mat = mat4(1.0);
uniform mat4 m_mat = mat4(1.0);

uniform int numCols = 1;
uniform int numRows = 1;
uniform float tx_offset = 0.0f;
uniform float ty_offset = 0.0f;

void main() {
	gl_Position = p_mat * m_mat * vec4(aPos,1.0);

	if(numCols != 1)
	{
		float x = (aTex.x / numCols + tx_offset);
		float y = (aTex.y / numRows + ty_offset);
		tex_coord =  vec2(x, y);

		return;
	}

	tex_coord = aTex;
}

(fragment)

#version 330 core

out vec4 fragColor;
in vec2 tex_coord;

uniform float aCol;
uniform sampler2D tex;

void main()
{
	fragColor = texture(tex, tex_coord) * vec4(1.0f, 0.5f, 0.0f, 1.0f);
}

