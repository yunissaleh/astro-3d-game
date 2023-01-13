#include "Graphics\window.h"
#include "Camera\camera.h"
#include "Shaders\shader.h"
#include "Model Loading\mesh.h"
#include "Model Loading\texture.h"
#include "Model Loading\meshLoaderObj.h"

void processKeyboardInput ();

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
bool cutscene = true;
bool c = false;
bool lr = true;
Window window("Game Engine", 800, 800);
Camera camera;
glm::vec3 lightColor = glm::vec3(1.0f);
glm::vec3 lightPos = glm::vec3(-1800.0f, 1000.0f, -100.0f);
glm::vec3 shipPos = glm::vec3(camera.getCameraPosition().x, camera.getCameraPosition().y - 60, camera.getCameraPosition().z - 100);
glm::vec3 astPos = glm::vec3(-1805.0f, 200.0f, -3000.0f);
glm::vec3 ufoPos = glm::vec3(-500.0f, 3000.0f, 6000.0f);

int main()
{
	glClearColor(0.0f, 0.0f, 0.09f, 1.0f);


	//building and compiling shader program
	Shader shader("Shaders/vertex_shader.glsl", "Shaders/fragment_shader.glsl");
	Shader sunShader("Shaders/sun_vertex_shader.glsl", "Shaders/sun_fragment_shader.glsl");
	Shader shader2("Shaders/water_vertex_shader.glsl", "Shaders/water_fragment_shader.glsl");

	//Textures
	GLuint tex = loadBMP("Resources/Textures/rock.bmp");
	GLuint tex2 = loadBMP("Resources/Textures/ast.bmp");
	GLuint tex3 = loadBMP("Resources/Textures/ship.bmp");
	GLuint tex4 = loadBMP("Resources/Textures/planet.bmp");
	GLuint tex5 = loadBMP("Resources/Textures/sand.bmp");
	GLuint tex6 = loadBMP("Resources/Textures/water.bmp");
	GLuint tex7 = loadBMP("Resources/Textures/sand2.bmp");
	GLuint tex8 = loadBMP("Resources/Textures/ufo.bmp");

	glEnable(GL_DEPTH_TEST);

	std::vector<Texture> textures;
	textures.push_back(Texture());
	textures[0].id = tex;
	textures[0].type = "texture_diffuse";

	std::vector<Texture> textures2;
	textures2.push_back(Texture());
	textures2[0].id = tex2;
	textures2[0].type = "texture_diffuse";

	std::vector<Texture> textures3;
	textures3.push_back(Texture());
	textures3[0].id = tex3;
	textures3[0].type = "texture_diffuse";

	std::vector<Texture> textures4;
	textures4.push_back(Texture());
	textures4[0].id = tex4;
	textures4[0].type = "texture_diffuse";

	std::vector<Texture> textures5;
	textures5.push_back(Texture());
	textures5[0].id = tex5;
	textures5[0].type = "texture_diffuse";

	std::vector<Texture> textures6;
	textures6.push_back(Texture());
	textures6[0].id = tex6;
	textures6[0].type = "texture_diffuse";

	std::vector<Texture> textures7;
	textures7.push_back(Texture());
	textures7[0].id = tex7;
	textures7[0].type = "texture_diffuse";

	std::vector<Texture> textures8;
	textures8.push_back(Texture());
	textures8[0].id = tex8;
	textures8[0].type = "texture_diffuse";
	// Create Obj files - easier :)
	// we can add here our textures :)
	MeshLoaderObj loader;
	Mesh sun = loader.loadObj("Resources/Models/sphere.obj");
	Mesh planet = loader.loadObj("Resources/Models/planet.obj", textures);
	Mesh planet2 = loader.loadObj("Resources/Models/planet.obj", textures2);
	Mesh planet3 = loader.loadObj("Resources/Models/planet.obj", textures4);
	Mesh planet4 = loader.loadObj("Resources/Models/sphere.obj", textures5);
	Mesh asteroid = loader.loadObj("Resources/Models/planet3.obj", textures2);
	Mesh ship = loader.loadObj("Resources/Models/ship.obj", textures3);
	Mesh plane = loader.loadObj("Resources/Models/plane1.obj", textures5);
	Mesh mountain = loader.loadObj("Resources/Models/everest.obj", textures7);
	Mesh water = loader.loadObj("Resources/Models/plane1.obj", textures6);
	Mesh ufo = loader.loadObj("Resources/Models/ufo.obj", textures8);

	//check if we close the window or press the escape button
	while (!window.isPressed(GLFW_KEY_ESCAPE) &&
		glfwWindowShouldClose(window.getWindow()) == 0)
	{
		window.clear();
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processKeyboardInput();

		//test mouse input
		if (window.isMousePressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			std::cout << "Pressing mouse button" << std::endl;
		}
		 //// Code for the light ////

		sunShader.use();

		glm::mat4 ProjectionMatrix = glm::perspective(90.0f, window.getWidth() * 1.0f / window.getHeight(), 0.1f, 10000.0f);
		glm::mat4 ViewMatrix = glm::lookAt(camera.getCameraPosition(), camera.getCameraPosition() + camera.getCameraViewDirection(), camera.getCameraUp());

		GLuint MatrixID = glGetUniformLocation(sunShader.getId(), "MVP");

		//Test for one Obj loading = light source

		glm::mat4 ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, lightPos);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		sun.draw(sunShader);

		//// End code for the light ////

		shader.use();

		///// Test Obj files for box ////

		GLuint MatrixID2 = glGetUniformLocation(shader.getId(), "MVP");
		GLuint ModelMatrixID = glGetUniformLocation(shader.getId(), "model");
		if(cutscene ==true){

		//draw spaceship
		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, shipPos);
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(15.0f, 15.0f, 15.0f));
		ModelMatrix = glm::rotate(ModelMatrix, 180.0f, glm::vec3(0.0, 1.0, 0.0));
		// after collision, rotate and move down
		if (shipPos.z < -1139.95) {
			ModelMatrix = glm::rotate(ModelMatrix, (float)glfwGetTime() * 100, glm::vec3(1.0, 0.0, 0.0));
			shipPos.y -= 0.06;
			camera.keyboardMoveDown(0.05);
		}
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);
		
		ship.draw(shader);
		shipPos.z -= 0.06;
		camera.keyboardMoveFront(0.058);
		
		///draw planet //////
		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(85.0f, 23.0f, -250));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(15.0f, 15.0f, 15.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

		planet.draw(shader);

		/// draw planet2 //////

		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-1805.0f, 203.0f, -3000.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(17.0f, 17.0f, 17.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

		planet2.draw(shader);

		/// draw planet3 //////

		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(2000.0f, 400, -3000.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(60.0f, 60.0f, 60.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

		planet3.draw(shader);

		/// draw asteroid //////

		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, astPos);
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(45.0f, 45.0f, 45.0f));
		ModelMatrix = glm::rotate(ModelMatrix, (float)glfwGetTime() * 10, glm::vec3(1.0, 0.0, 0.0));

		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

		asteroid.draw(shader);
		// move asteroid toward ship
		astPos.y -= 0.0099;
		astPos.x += 0.11;
		astPos.z += 0.1;
		// after collision reset camera and move to the next scene
		if (shipPos.y < -1000) {
			camera.reset();
			cutscene = false;
		}
		//uncomment to skip cutscene
		cutscene = false;
		}
		if (cutscene == false) {

			//terrain
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -40.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(3.0f, 1.0f, 3.0f));

			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			plane.draw(shader);
			//ship
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -15.0f, -15.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(20.0f, 20.0f, 20.0f));
			ModelMatrix = glm::rotate(ModelMatrix, 45.0f, glm::vec3(1.0, 1.0, 1.0));

			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			ship.draw(shader);
		
			//planet
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-800.0f, 4500.0f, -6200.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(120.0f, 110.0f, 100.0f));
		
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			planet4.draw(shader);

			//mountain
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(70.0f, -5.0f, 1900.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(620.0f, 700.0f, 700));
			ModelMatrix = glm::rotate(ModelMatrix, 180.0f, glm::vec3(0.0, 1.0, 0.0));
			ModelMatrix = glm::rotate(ModelMatrix, 1.0f, glm::vec3(0.0, 0.0, 1.0));

			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			mountain.draw(shader);

			//ufo
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix,ufoPos);
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(100.0f, 100.0f, 100));
		
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			ufo.draw(shader);
			if (lr) {
				ufoPos.x -= 0.4;
				if (ufoPos.x < -3300.0f)
					lr = false;
			}
			if (!lr){
				ufoPos.x += 0.4;
				if (ufoPos.x > 3300.0f) 
					lr = true;
			}
			//water

			shader2.use();
			float wave = (float)glfwGetTime();
			glUniform1f(glGetUniformLocation(shader2.getId(), "wave"), wave);
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -60.0f, -900.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -200.0f, -900.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(10.0f, 10.0f, 10.0f));

			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
			glUniform3f(glGetUniformLocation(shader2.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
			glUniform3f(glGetUniformLocation(shader2.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
			glUniform3f(glGetUniformLocation(shader2.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

			water.draw(shader2);


		}
		window.update();
	}

}

void processKeyboardInput()
{
	float cameraSpeed = 60 * deltaTime;

	if(cutscene == false){

	//translation
	if (window.isPressed(GLFW_KEY_W)){
		camera.keyboardMoveFront(cameraSpeed);
		}
	if (window.isPressed(GLFW_KEY_S))
		camera.keyboardMoveBack(cameraSpeed);
	if (window.isPressed(GLFW_KEY_A))
		camera.keyboardMoveLeft(cameraSpeed);
	if (window.isPressed(GLFW_KEY_D))
		camera.keyboardMoveRight(cameraSpeed);
	if (window.isPressed(GLFW_KEY_R))
		camera.keyboardMoveUp(cameraSpeed);
	if (window.isPressed(GLFW_KEY_F))
		camera.keyboardMoveDown(cameraSpeed);

	//rotation
	if (window.isPressed(GLFW_KEY_LEFT)) {
		camera.rotateOy(cameraSpeed);
		camera.keyboardMoveLeft(cameraSpeed);
			
	}
	if (window.isPressed(GLFW_KEY_RIGHT)) {
		camera.rotateOy(-cameraSpeed);
		camera.keyboardMoveRight(cameraSpeed);

	}
	if (window.isPressed(GLFW_KEY_UP)) {
		camera.rotateOx(cameraSpeed);
		camera.keyboardMoveUp(cameraSpeed);
	}
	if (window.isPressed(GLFW_KEY_DOWN)){
		camera.rotateOx(-cameraSpeed);
		camera.keyboardMoveDown(cameraSpeed);
	}
	if (window.isPressed(GLFW_KEY_V)) {
		std::cout << ufoPos.x << std::endl;
	}
	}

	
}
