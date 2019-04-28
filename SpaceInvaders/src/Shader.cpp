#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>
#include <fstream>

Shader::Shader(std::string filePath)
{
	std::ifstream stream(filePath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream tmp[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			tmp[(int)type] << line << "\n";
		}
	}

	shaderSource[0] = tmp[0].str();
	shaderSource[1] = tmp[1].str();
}

void Shader::Compile()
{
	// Compiling vertex shader
	id.VertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* src = (shaderSource[0]).c_str();
	glShaderSource(id.VertexShader, 1, &src, NULL);
	glCompileShader(id.VertexShader);

	// Check for errors
	int  success;
	char infoLog[512];
	glGetShaderiv(id.VertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(id.VertexShader, 512, NULL, infoLog);
		std::cout << "[Vertex Shader] Compilation failed.\n" << infoLog << std::endl;
	}
	// Compiling fragment shader
	
	id.FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	src = (shaderSource[1]).c_str();
	glShaderSource(id.FragmentShader, 1, &src, NULL);
	glCompileShader(id.FragmentShader);

	// Check for errors
	glGetShaderiv(id.FragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(id.FragmentShader, 512, NULL, infoLog);
		std::cout << "[Fragment Shader] Compilation failed.\n" << infoLog << std::endl;
	}

	// Shader program
	id.ShaderProgram = glCreateProgram();
	glAttachShader(id.ShaderProgram, id.VertexShader);
	glAttachShader(id.ShaderProgram, id.FragmentShader);
	glLinkProgram(id.ShaderProgram);

	// Check for errors
	glGetProgramiv(id.ShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id.ShaderProgram, 512, NULL, infoLog);
		std::cout << "[Shader Program] Linking shader program failed.\n";
	}

	glDeleteShader(id.VertexShader);
	glDeleteShader(id.FragmentShader);
}

void Shader::Use()
{
	glUseProgram(id.ShaderProgram);
}

void Shader::SetUniformF(const std::string& name, float v1, float v2, float v3, float v4) const
{
	glUniform4f(glGetUniformLocation(id.ShaderProgram, name.c_str()), v1, v2, v3, v4);
}

Shader::~Shader()
{
}
