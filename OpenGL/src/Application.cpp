
#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb/stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../ConsoleHelp/ConsoleHelp.h"


//Our Own Classes !!!

#include "../Shaders/ShaderClass.h"
#include "../Buffers/VBO/VBO.h"
#include "../Buffers/VBO/VAO/VAO.h"
#include "../Buffers/EBO/EBO.h"
#include "../Texture/Texture.h"


GLfloat verticies[] =
{
    //     COORDINATES     /        COLORS      /   TexCoord  //
   -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
   -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
    0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
    0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

GLfloat verticies2[] =
{
    //     COORDINATES     /        COLORS      /   TexCoord  //
   -1.5f, -1.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
   -1.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
    0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
    0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
{
   0, 2, 1, //Upper triangle
   0, 3, 2 //Lower triangle
};

const char* Name_Of_Window = "More than a triangle";

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    
    int WindowWidth = 720;
    int WindowHieght = 480;
    //For Debugging
#ifdef _DEBUG
    AllocConsole();
    FILE* fp = nullptr;//No initalizer will cause memory leak
    freopen_s(&fp, "CONIN$", "r", stdin); //more for stdin and out
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
#endif
#ifdef _DEBUG
    WriteLine("Allocated and created console");
    //std::cin.get();
#endif


    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    

#ifdef _DEBUG
    WriteLine("Initialized OpenGl, glfw and Glad");
    //std::cin.get();
#endif
    glfwWindowHint(GLFW_RESIZABLE, 0); //Diable rezizing
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WindowWidth, WindowHieght, Name_Of_Window, NULL, NULL); //
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    

#ifdef _DEBUG
    WriteLine("Created graphics window with OpenGL, GLFW and Glad");
    //std::cin.get();
#endif

    

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, WindowWidth, WindowHieght);
#ifdef _DEBUG
    std::cout << "Set context to current window (Set drawing to current window) also setting viewport also keycall back" << std::endl;
    //std::cin.get();
    
#endif 
    
#ifdef _DEBUG
    Shader shaderprogram("ShaderFiles\\default.vert", "ShaderFiles\\default.frag"); //if building on debug only use debug with debugger dont run on relase or it will not work
#else
    Shader shaderprogram("default.vert", "default.frag"); //if building on release
#endif // _DEBUG

    

#ifdef _DEBUG
    WriteLine("Init shader program class with defualt.vert and defualt.frag");
    //std::cin.get();
#endif // _DEBUG
    
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(verticies, sizeof(verticies));
    EBO EBO1(indices, sizeof(indices));

    //Links vbo attribues such as coords and color to vao
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    //gets id of unifrom called scale
    GLuint uniID = glGetUniformLocation(shaderprogram.ID, "scale");


#ifdef _DEBUG
    WriteLine("Starting Texture stuff");
#endif // _DEBUG

    Texture bird("Textures\\Icon_Bird_512x512.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE); //Something to load from application files on release
    bird.texUnit(shaderprogram, "tex0", 0);
    




#ifdef _DEBUG
    WriteLine("Init classes of buffer objects then unbound them after adding to shader program along with textures started");
    //std::cin.get();
#endif // _DEBUG


#ifdef _DEBUG
    WriteLine("Enabling window loop");
    //std::cin.get();
#endif
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //Backround color
        glClear(GL_COLOR_BUFFER_BIT);
        
        shaderprogram.Activate();
        /*
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        proj = glm::perspective(glm::radians(45.0f), (float)(800 / 800), 0.1f, 100.0f);
        */


        //assings a value ot the uniform; MUST ALWAYS BE DONE AFTER SHADER PROGRAM IS ACTIVIATED
        glUniform1f(uniID, 0.5f);
        bird.Bind();
        VAO1.Bind();
        
        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

#ifdef _DEBUG
    WriteLine("Ended Window loop");
#endif
   
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    bird.Delete();
    shaderprogram.Delete();

#ifdef _DEBUG
    WriteLine("Deleted Buffers");
#endif // _DEBUG

    glfwDestroyWindow(window);
    glfwTerminate();

    

#ifdef _DEBUG
    WriteLine("Terminated library");

    fclose(fp); 
    FreeConsole(); //To close console and destoy std pointers?
#endif
    
    
    return 0;
}