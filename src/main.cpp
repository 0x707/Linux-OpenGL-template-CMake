#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shloader.h"
#include "texture.h"

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

void process_input(GLFWwindow* window)
{
	glfwSetWindowShouldClose(window, glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS);
}

bool is_key_pressed(GLFWwindow* window, int key)
{
	return glfwGetKey(window, key) == GLFW_PRESS;
}

int main()
{
	ShaderLoader sl{"../shaders/pupa.txt"};
	std::cout << sl.read() << '\n';
	sl.close();

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "TestGL", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to init GLAD\n";
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	constexpr char const* paths[2]{
		"../shaders/01.vert",
		"../shaders/01.frag"
	};

	SimpleShader mainShader{paths[0], paths[1]};

	float vertices[]{
		-1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		 1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		 1.0f,-1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
		-1.0f,-1.0f, 0.0f,  0.0f, 1.0f, 1.0f,  1.0f, 1.0f
	};

	unsigned indices[] {
		0, 1, 2,
		2, 3, 0
	};

	unsigned EBO, VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	Texture2d tex("img.png");
	Texture2d tex2("kk.jpg");

	mainShader.uni_int("theTex", 0);
	mainShader.uni_int("theKej", 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		if (is_key_pressed(window, GLFW_KEY_LEFT_ALT) && is_key_pressed(window, GLFW_KEY_Q)) {
			mainShader.reload(paths[0], paths[1]);
			mainShader.uni_int("theTex", 0);
			mainShader.uni_int("theKej", 1);
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float timeVal = static_cast<float>(glfwGetTime());
		mainShader.uni_float("u_time", timeVal);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
	glfwTerminate();

	return 0;
}
