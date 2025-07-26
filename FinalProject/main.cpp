#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <vector>
#include <string> 
#include "Shader.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "GameObject.hpp"


const char* vtx = R"(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 atexCoord;
out vec3 vertexColor;
out vec2 texCoord;
uniform mat4 model, view, projection;
void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vertexColor = aColor;
    texCoord = atexCoord;
})";

const char* frag = R"(#version 330 core
in vec3 vertexColor;
in vec2 texCoord;
out vec4 FragColor;
uniform sampler2D mytexture;
void main() {
    FragColor = texture(mytexture, texCoord);
})";


float vertices[] = {
     0.5f,  0.5f, 0.0f, 1,0,0, 1,1,
     0.5f, -0.5f, 0.0f, 0,1,0, 1,0,
    -0.5f, -0.5f, 0.0f, 0,0,1, 0,0,
    -0.5f,  0.5f, 0.0f, 1,1,0, 0,1,
};
unsigned int indices[] = { 0,1,3, 1,2,3 };

bool CheckCollision(GameObject& one, GameObject& two) {
    float one_half_size_x = one.size / 2.0f;
    float one_half_size_y = one.size / 2.0f;
    float two_half_size_x = two.size / 2.0f;
    float two_half_size_y = two.size / 2.0f;
    bool collisionX = (one.position.x + one_half_size_x >= two.position.x - two_half_size_x) &&
        (two.position.x + two_half_size_x >= one.position.x - one_half_size_x);
    bool collisionY = (one.position.y + one_half_size_y >= two.position.y - two_half_size_y) &&
        (two.position.y + two_half_size_y >= one.position.y - one_half_size_y);
    return collisionX && collisionY;
}

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Dog eats cookies", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, 800, 600);

   
    Shader shader(vtx, frag);
    Texture dogTexture("assets/dog.png");
    Texture cookieTexture("assets/cookie.png");
    Texture background("assets/bg.png");
    Mesh mesh(vertices, sizeof(vertices), indices, sizeof(indices));

    
    GameObject bg(&mesh, &background, &shader);
    bg.position.z = -0.5f;
    bg.size = 10.0f;

    GameObject dog(&mesh, &dogTexture, &shader);
    dog.size = 1.5f;

    std::vector<GameObject> cookies;
    GameObject cookie1(&mesh, &cookieTexture, &shader);
    cookie1.position = glm::vec3(3.0f, 2.0f, 0.0f);
    cookies.push_back(cookie1);

    GameObject cookie2(&mesh, &cookieTexture, &shader);
    cookie2.position = glm::vec3(-2.5f, -2.0f, 0.0f);
    cookies.push_back(cookie2);

    GameObject cookie3(&mesh, &cookieTexture, &shader);
    cookie3.position = glm::vec3(-1.0f, 3.0f, 0.0f);
    cookies.push_back(cookie3);

 
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    glm::vec3 camPos(0, 0, 8), camCenter(0, 0, 0);

   
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        
        for (GameObject& cookie : cookies) {
            if (cookie.isActive) {
                if (CheckCollision(dog, cookie)) {
                    cookie.isActive = false;
                }
            }
        }

        glClearColor(0.1, 0.1, 0.1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 view = glm::lookAt(camPos, camCenter, { 0,1,0 });
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.f / 600.f, 0.1f, 100.f);
        bg.Draw(view, proj);
        dog.Draw(view, proj);
        for (GameObject& cookie : cookies) {
            cookie.Draw(view, proj);
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Control Panel");
        ImGui::Text("Drag to move the characters!");
        ImGui::Separator();

        ImGui::DragFloat3("Dog Position", &dog.position.x, 0.1f);
        ImGui::Separator();

        for (int i = 0; i < cookies.size(); ++i) {
            std::string label = "Cookie " + std::to_string(i + 1) + " Position";
            if (cookies[i].isActive) {
                ImGui::DragFloat3(label.c_str(), &cookies[i].position.x, 0.1f);
            }
        }

        ImGui::Separator();
        ImGui::DragFloat3("Camera Position", &camPos.x, 0.1f);
        ImGui::DragFloat3("Camera Center", &camCenter.x, 0.1f);
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}