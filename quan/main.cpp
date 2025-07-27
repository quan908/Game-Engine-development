#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <miniaudio.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "SoundManager.hpp"


#include <iostream>

using namespace XQ;
using namespace std;

const char* vertexShaderSource = R"(
#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;
layout (location=2) in vec2 atexCoord;
layout (location=3) in vec3 aNormal;

out vec3 vertexColor;
out vec2 texCoord;
out vec3 normal;

out vec3 fragPos;

uniform float size;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  vec4 worldPos = model * vec4(aPos.x*size, aPos.y*size, aPos.z*size, 1.0);
  fragPos = vec3(worldPos);
  gl_Position = projection * view * worldPos;
  vertexColor = aColor;
  texCoord = atexCoord;
  normal = normalize(aNormal);
}

)";

const char* fragmentShaderSource = R"(
#version 330 core
in vec3 vertexColor;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 FragColor;

uniform sampler2D mytexture;
uniform float ambientIntensity;

uniform vec3 lightPos;
vec3 finalLight;
vec3 lightColor;

void main()
{

  lightColor.r = 1.0;
  lightColor.g = 1.0;
  lightColor.b = 1.0;
 
  vec3 lightDirection = normalize(lightPos-fragPos) ;
  float diff = max(dot(normal, lightDirection), 0.0);
  vec3 diffLight = diff * lightColor;

  vec3 ambientLignt = ambientIntensity * lightColor;

  finalLight = ambientLignt + diff;
  FragColor = vec4(finalLight, 1.0) * texture(mytexture, texCoord);
}
)";

unsigned int compileShader(unsigned int type, const char* source)
{
    unsigned int shader_id = glCreateShader(type);
    glShaderSource(shader_id, 1, &source, NULL); // load shader source to opengl
    glCompileShader(shader_id); // compile the code


    int success;
    char infoLog[512];
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
        std::cout << "ERROR : " << infoLog << std::endl;
    }

    return shader_id;
}

unsigned int createShaderProgram()
{
    unsigned int vertexShader_id = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader_id = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader_id);
    glAttachShader(shaderProgram, fragmentShader_id);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader_id);
    glDeleteShader(fragmentShader_id);

    return shaderProgram;
}

int main(void)
{
    XQ::SoundManager soundManager;
    if (soundManager.init() < 0)
    {
        std::cout << "sound init is unsuccessful";
        return -1;
    }
    soundManager.playMusic("assets/bgmusic.mp3");
   

   

    stbi_set_flip_vertically_on_load(true);
    int w, h, n;
    unsigned char* data = stbi_load("assets/23.png", &w, &h, &n, STBI_rgb_alpha);
    if (!data)
    {
        std::cout << "Failed to load texture image!" << std::endl;
        return -1;
    }


    GLFWwindow* window;
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "First Shader", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        cout << "Failed to initialize GLEW" << endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);

    // ask opengl to gen texture reference id.
    unsigned int textureID1;
    glGenTextures(1, &textureID1);
    glBindTexture(GL_TEXTURE_2D, textureID1); // tell opengl that I will use this texture

    // set texture warping and filtering option;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0); // deselected any texture.


    float vertices[] = {
        // positions         // colors        // texture coord    //normal vector
         0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   0.0f,0.0f,1.0f,
         0.5f, -0.3f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   0.0f,0.0f,1.0f,
        -0.5f, -0.3f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   0.0f,0.0f,1.0f,
        -0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,    0.0f,0.0f,1.0f
    };

    unsigned int indices[] = {
      0,1,3,
      1,2,3
    };




    unsigned int VAO, VBO, VEO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VEO);

    glBindVertexArray(VAO); // Hey I will work with that memory! (VAO)

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Hey I will work with that buffer! (VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);   // Hey I want to copy my vertices data to GPU ram.

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO); // Hey I will work with that buffer! (VEO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Postion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)0);
    glEnableVertexAttribArray(0);
    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture Coord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    //Normal
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);

    unsigned int sharderProgram = createShaderProgram();

    float size = 1.0f;
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    

    //------------------------------------

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();


    //--------------------------------------

    glm::vec3 cam_position(0.0f, 0.0f, 1.0f);
    glm::vec3 cam_center(0.0f, 0.0f, 0.0f);
    float ambientIntensity = 0.5f;
    glm::vec3 lightPos(3.0f, 3.0f, 3.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glfwPollEvents();


        glUseProgram(sharderProgram);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID1); // tell opengl that I will use this texture

        glUniform1f(glGetUniformLocation(sharderProgram, "size"), size);

        glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 view = glm::lookAt(
            cam_position,
            cam_center,
            glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(sharderProgram, "model"), 1,
            GL_FALSE,
            glm::value_ptr(model));

        glUniformMatrix4fv(glGetUniformLocation(sharderProgram, "view"), 1,
            GL_FALSE,
            glm::value_ptr(view));

        glUniformMatrix4fv(glGetUniformLocation(sharderProgram, "projection"), 1,
            GL_FALSE,
            glm::value_ptr(projection));

        glUniform1i(glGetUniformLocation(sharderProgram, "mytexture"), 0);

        glUniform1f(glGetUniformLocation(sharderProgram, "ambientIntensity"), ambientIntensity);

        glUniform3fv(glGetUniformLocation(sharderProgram, "lightPos"), 1,glm::value_ptr(lightPos));
        glBindVertexArray(VAO); // I will working on VAO
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Inspector");
        ImGui::Text("Transform");
        ImGui::DragFloat3("Position", &position.x, 0.1f);
        ImGui::SliderFloat("Size", &size, 0.1f, 3.0f);
        ImGui::DragFloat3("Cam Position", &cam_position.x, 0.1f);
        ImGui::DragFloat3("Cam Center", &cam_center.x, 0.1f);


        ImGui::Spacing;
        ImGui::DragFloat3("lightPos", &lightPos.x, -0.1f, 0.1f);
        ImGui::SliderFloat("Amint", &ambientIntensity, 0.5f, 1.0f);
        ImGui::End();

        // Rendering
        // (Your code clears your framebuffer, renders your other stuff etc.)
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();


    glfwTerminate();

    stbi_image_free(data);
  

    return 0;
}

