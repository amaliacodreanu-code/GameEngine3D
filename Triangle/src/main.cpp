#include"Mesh.h"


int main()
{
    // Initialize GLFW
    glfwInit();

    // Specify OpenGL version (3.3 Core Profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    
    Vertex vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	Vertex{glm::vec3(-0.5f, 0.0f,  0.5f),     glm::vec3(0.83f, 0.70f, 0.44f),	glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f, 0.0f, -0.5f),     glm::vec3(0.83f, 0.70f, 0.44f),	glm::vec2(5.0f, 0.0f)},
	Vertex{glm::vec3(0.5f, 0.0f, -0.5f),     glm::vec3(0.83f, 0.70f, 0.44f),	glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3 (0.5f, 0.0f,  0.5f),   glm::vec3(0.83f, 0.70f, 0.44f),     glm::vec2(5.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.8f,  0.0f),    glm::vec3(0.92f, 0.86f, 0.76f),	    glm::vec2(2.5f, 5.0f)}
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


    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 800, "Scene", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        std::cin.get();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        std::cin.get();
        return -1;
    }

    // Set the viewport to the full window size
    glViewport(0, 0, 800, 800);


    // Initialize the Shader Program
    Shader shaderProgram(
    "C:/UPB_LAB/GameEngine3D/Shaders/default.vert", 
    "C:/UPB_LAB/GameEngine3D/Shaders/default.frag"
);
   
   Texture texture(
    "C:/UPB_LAB/GameEngine3D/ResourcesFiles/Textures/texture_Egipt.jpg", 
    "diffuse", 
    0, 
    GL_RGB, 
    GL_UNSIGNED_BYTE
);


     // Store mesh data in vectors for the mesh
	// ...
   std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
   std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));

   std::vector<Texture> floorTextures;
   floorTextures.push_back(texture);
   Mesh floor(verts, ind, floorTextures);

    
   	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);


    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));

     glEnable(GL_DEPTH_TEST);  

    // Creates camera object
    Camera camera(800, 800, glm::vec3(0.0f, 1.0f, 20.0f));
   
    // --- Main Render Loop ---
while (!glfwWindowShouldClose(window))
{
    // Specify the background color
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // Roz
    // Clear the back buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Handles camera inputs
    camera.Inputs(window); 
    // Updates and exports the camera matrix to the Vertex Shader
    camera.updateMatrix(45.0f, 0.1f, 100.0f);

    floor.Draw(shaderProgram, camera);

    // Swap the front and back buffers
    glfwSwapBuffers(window);
    // Poll for window events
    glfwPollEvents();
}
  
    shaderProgram.Delete();
    //Delete window before ending the program
    glfwDestroyWindow(window); 
    //Terminate GLFW beofore ending the program
    glfwTerminate();
    std::cin.get();
    return 0; 
}


