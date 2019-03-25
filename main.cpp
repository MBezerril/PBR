/*
  Define the numbers of images to be rendered to create Gifs or animations
*/
#define imagesQuantity 1

#include "main.h"

int main(void) {
	unsigned int x_resolution = 512;
	unsigned int y_resolution = 512;

	for (int actual = 0; actual < imagesQuantity; actual++) { //Loop used to make all images
		std::string nome = "Outputs/output_image" + std::to_string(actual) + ".ppm";
		glm::vec3 camera_position{ 0.0f, 0.0f,  5.0f };

		PerspectiveCamera camera{ -1.25f,
									1.25f,
								   -1.25f,
									1.25f,
									glm::ivec2{ x_resolution, y_resolution },
									camera_position,     // position
									glm::vec3{ 0.0f, 1.0f,  0.0f },     // up
									glm::vec3{ 0.0f, 0.0f, -1.0f }, // look at
									2.0f }; //Depthof field distance for perspective Camera
		Scene scene{};

		scene.load();

		Buffer rendering_buffer{ x_resolution, y_resolution };
		glm::vec3 background_color{ 0.0f, 0.0f, 0.0f };

		// Set up the renderer.
		PathTracer rt(camera,
			scene,
			background_color,
			rendering_buffer, 200, 5);

		rt.integrate(); // Renders the final image.

		// Save the rendered image to a .ppm file.
		rendering_buffer.save(nome);
	}

	return EXIT_SUCCESS;
}

