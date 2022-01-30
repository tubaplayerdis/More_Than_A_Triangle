
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

//Camera

#include "../Camera/Camera.h"


// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};




GLfloat lightVertices[] =
{ //     COORDINATES     //
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
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

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    //Links vbo attribues such as coords and color to vao
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

#ifdef _DEBUG
    Shader lightshader("ShaderFiles\\light.vert", "ShaderFiles\\light.frag");
    
#else
    Shader lightshader("light.vert", "light.frag");

#endif

    VAO LightVAO;
    LightVAO.Bind();

    VBO LightVBO(lightVertices, sizeof(lightVertices));
    EBO LightEBO(lightIndices, sizeof(lightIndices));

    LightVAO.LinkAttrib(LightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    LightVAO.Unbind();
    LightVBO.Unbind();
    LightEBO.Unbind();

    glm::vec3 lightpos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightmodel = glm::mat4(1.0f);
    lightmodel = glm::translate(lightmodel, lightpos);

    glm::vec3 pyramidpos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyrimidModel = glm::mat4(1.0f);
    pyrimidModel = glm::translate(pyrimidModel, pyramidpos);

    lightshader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightshader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightmodel));
    shaderprogram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderprogram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyrimidModel));


#ifdef _DEBUG
    WriteLine("Starting Texture stuff");
    
#endif // _DEBUG


    //Need to set debug and non debug versions

    Texture bird("Textures\\yellow.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE); //Something to load from application files on release
    bird.texUnit(shaderprogram, "tex0", 0);
    




#ifdef _DEBUG
    WriteLine("Init classes of buffer objects then unbound them after adding to shader program along with textures started");
    
#endif // _DEBUG


#ifdef _DEBUG
    WriteLine("Enabling window loop");

    //std::cin.get();
#endif

   

    //Enable depth buffer
    glEnable(0x0B71); // To disable wierd glitched with overlap can use GL_DEPTH_TEST for readability also used in clear buffer function

    Camera camera(WindowWidth, WindowHieght, glm::vec3(0.0f, 0.0f, 2.0f));

    /* Loop until the user closes the window */;
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //Backround color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
       
        
        

       
        camera.Inputs(window);
        camera.updateMatrix(60.0f, 0.1f, 100.0f);

        
        shaderprogram.Activate();
        camera.Matrix(shaderprogram, "camMatrix");

        

        bird.Bind();
        VAO1.Bind();

        
        
        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        

        lightshader.Activate();
        camera.Matrix(lightshader, "camMatrix");
        LightVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

        

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