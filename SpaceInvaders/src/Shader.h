#pragma once

#include <string>
struct ID
{
	unsigned int VertexShader;
	unsigned int FragmentShader;
	unsigned int ShaderProgram;
};

class Shader
{
public:
	Shader(std::string shaderPath);
	void Compile();
	void Use();
	void SetUniformF(const std::string& name, float v1, float v2, float v3, float v4) const;
	~Shader();

private:
	ID id;
	std::string shaderPath;
	std::string shaderSource[2];
};

