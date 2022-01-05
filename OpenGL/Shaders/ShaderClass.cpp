#include "ShaderClass.h"
#include <windows.h>

std::string get_file_contents(const char* filename)
{
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	//Fragment Shader source code
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
		"}\n\0";
	std::ifstream inL(filename);
	/*
	std::ofstream lol(filename);
	if (lol.is_open()) {
		return "is open";
	}
	else if (lol.good())
	{
		return "Good";
	}
	else if (lol.bad()) 
	{
		return "Bad";
	}
	else if (lol.fail())
	{
		return "fail";
	}
	else
	{
		return "null";
	}
	*/
	
	if (inL)
	{
		std::string contents;
		inL.seekg(0, std::ios::end);
		contents.resize(inL.tellg());
		inL.seekg(0, std::ios::beg);
		inL.read(&contents[0], contents.size());
		inL.close();
		return(contents);
	}
	else
	{
		return "NULL";
	}
	throw(errno);
	
	/*
	if (filename == "default.frag")
		return fragmentShaderSource;
	else
	{
		return vertexShaderSource;
	}
	*/
}

Shader::Shader(std::string vertexFile, std::string fragmentFile)
{
	std::string Hvc = "ShaderFiles\\" + vertexFile;
	std::string Hfc = "ShaderFiles\\" + fragmentFile;
	
	std::string vertexCode;
	std::string fragmentCode;

	if (get_file_contents(vertexFile.c_str()) == "NULL")
	{
		vertexCode = get_file_contents(Hvc.c_str());
		fragmentCode = get_file_contents(Hfc.c_str());
	}
	else
	{
		vertexCode = get_file_contents(vertexFile.c_str());
		fragmentCode = get_file_contents(fragmentFile.c_str());
	}

	// Read vertexFile and fragmentFile and store the strings
	
	//memory mangemnt

	
	



#ifdef _DEBUG
	std::cout << get_file_contents(".\\default.frag") << std::endl;
	//std::cin.get();
	std::cout << get_file_contents(".\\default.vert") << std::endl;
	//std::cin.get();
#endif // _DEBUG

	

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");
	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");
	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");
	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}


void Shader::Activate() 
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hascompiled;
	char infolog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hascompiled);
		if (hascompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infolog);
#ifdef _DEBUG
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;
#endif // _DEBUG

		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hascompiled);
		if (hascompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infolog);
#ifdef _DEBUG
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infolog << std::endl;
#endif // _DEBUG

			
		}
	}
}
