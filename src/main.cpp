#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shloader.h"
#include "texture.h"
#include "matrix.h"
#include "detail/array_f.h"
#include "gl_stuff/vertex_array.h"
#include "gl_stuff/vertex_buffer.h"
#include "gl_stuff/element_vertex_buffer.h"
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"

camera cam{glm::vec3{0.f, 0.f, 3.f},
		   glm::vec3{0.f, 1.f, 0.f}};		

float g_dt_time = 0.0f;
float g_last_frame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int w, int h) noexcept
{
	glViewport(0, 0, w, h);
}

void process_input(GLFWwindow*) noexcept;

bool is_key_pressed(GLFWwindow* window, int key) noexcept
{
	return glfwGetKey(window, key) == GLFW_PRESS;
}

void trans_rot_scale(Mat4f& m, vec3 const* v_arr, float t) noexcept
{
	m.normalize();
	m.translate(v_arr[modif::TRNS]);
	m.rotate(t, v_arr[modif::SCLE]);
	m.scale(v_arr[modif::ROTE]);
}

struct ScrollInput
{
	float x;
	float y;
} sc_input;

void sc_cb(GLFWwindow* w, double xoff, double yoff) noexcept
{
	sc_input.y += static_cast<float>(yoff / 10.0);
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
	glEnable(GL_DEPTH_TEST);

	glfwSetScrollCallback(window, sc_cb);;

	constexpr char const* paths[2]{
		"../shaders/01.vert",
		"../shaders/01.frag"
	};

	SimpleShader mainShader{paths[0], paths[1]};

	float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,

         0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  1.0f, 1.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 1.0f
         
    };

	array_f<arr_size(vertices), 3> arrf{vertices, std::array<std::size_t, 3>{3,2,3}};

	unsigned indices[] {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};

	// Init vertex array, vertex vuffer and element buffer
	VAO vao{};
	VBO vbo{arrf};
	EBO ebo{indices};
	// !

	vbo.fill_data(arrf);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	unbind_vertex_array();

	Texture2d tex("img.png");
	Texture2d tex2("kk.jpg");
	Texture2d tex3("pikameme.png");
	Texture2d tex4("kaka.jpg");

	mainShader.uni_int("theTex", 0);
	mainShader.uni_int("theKej", 1);
	mainShader.uni_int("pikachu", 2);
	mainShader.uni_int("kaka", 3);

	Mat4f trans;

	sc_input.y = -4.0f;

	constexpr std::size_t c_cubes_count{2};
	glm::vec3 cubes[c_cubes_count] {
		{0.75f, 0.75f, -3.0f},
		{-0.75f, - 0.75f, -5.0f}
	};

	Mat4f projection;
	projection.perspective(glm::radians(cam.get_zoom()), 800.f, 600.f, 0.1f, 100.0f);
	mainShader.uni_mat4fv("projection", projection.first_elem());

	auto do_some_transforms = [&mainShader](glm::vec3 const& cb_pos, float t){
		Mat4f model;
		model.translate(cb_pos);
		model.rotate(t * glm::radians(45.0f), {1.0f, 1.0f, 0.0f});

		mainShader.uni_mat4fv("model", model.first_elem());
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	};

	Mat4f view;

	while (!glfwWindowShouldClose(window)) {
		process_input(window);


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		vao.bind();

		float time_val = static_cast<float>(glfwGetTime());
		mainShader.uni_float("u_time", time_val);

		g_dt_time = time_val - g_last_frame;
		g_last_frame = time_val;

		cubes[0].z = sc_input.y;
		cubes[1].z = sc_input.y * 0.5f;

		view.normalize();
		view = cam.view_matrix();
		mainShader.uni_mat4fv("view", view.first_elem());

		for (std::size_t i = 0; i < c_cubes_count; ++i)
			do_some_transforms(cubes[i], time_val);

		if (is_key_pressed(window, GLFW_KEY_LEFT_ALT) && is_key_pressed(window, GLFW_KEY_Q)) {
			mainShader.reload(paths[0], paths[1]);
			mainShader.uni_int("theTex", 0);
			mainShader.uni_int("theKej", 1);
			mainShader.uni_int("pikachu", 2);
			mainShader.uni_int("kaka", 3);
			
			mainShader.uni_mat4fv("projection", projection.first_elem());
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}

void process_input(GLFWwindow* window) noexcept
{
	glfwSetWindowShouldClose(window, glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam.kb_input(CAM_DIR::FRWD, g_dt_time);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam.kb_input(CAM_DIR::BCWD, g_dt_time);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam.kb_input(CAM_DIR::LEFT, g_dt_time);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam.kb_input(CAM_DIR::RGHT, g_dt_time);
}
