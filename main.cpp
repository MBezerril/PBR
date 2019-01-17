#include "main.h"

int main(void) {
	unsigned int x_resolution = 512;
	unsigned int y_resolution = 512;

	for (int actual = 0; actual < 10; actual++) {
		std::string nome = "output_image" + std::to_string(actual) + ".ppm";
		glm::vec3 camera_position{ (float)actual/10.0, 0.0f,  1.0f };

		PerspectiveCamera camera{ -1.25f,
									1.25f,
								   -1.25f,
									1.25f,
									glm::ivec2{ x_resolution, y_resolution },
									camera_position,     // position
									glm::vec3{ 0.0f, 1.0f,  0.0f },     // up
									glm::vec3{ 0.0f, 0.0f, -1.0f },   // look at
									2.0f }; //Depthof field distance
		Scene scene{};

		scene.load();

		Buffer rendering_buffer{ x_resolution, y_resolution };
		glm::vec3 background_color{ 10.0f, 0.0f, 0.0f };

		// Set up the renderer.
		RayTracer rt(camera,
			scene,
			background_color,
			rendering_buffer);

		rt.integrate(); // Renders the final image.

		// Save the rendered image to a .ppm file.
		rendering_buffer.save(nome);
	}

	return EXIT_SUCCESS;
}

