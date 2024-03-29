#include "Graphics\window.h"
#include "Camera\camera.h"
#include "Shaders\shader.h"
#include "Model Loading\mesh.h"
#include "Model Loading\texture.h"
#include "Model Loading\meshLoaderObj.h"
#include <string>
#include <iostream>
#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"
#define STBI_ASSERT(x)
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"



void processKeyboardInput ();

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
float distance_ship;
float distance_pkaxe;
float distance_rock;
float distance_bucket;
float distance_fuel;

int counter = 0;

bool cutscene = true;
bool ufo_lr = true;
bool isPickaxe = true;
bool isPickaxe2 = false;
bool isRock = true;
bool isBucket = false;
bool isFuel = true;
bool isShipFix = false;
bool refill = false;
bool fly_home = false;
bool endscene = false;
bool skyboxOn2 = false;
Window window("Game Engine", 800, 800);

Camera camera;
glm::vec3 lightColor = glm::vec3(1.0f);
glm::vec3 lightPos = glm::vec3(-1800.0f, 1000.0f, -100.0f);
glm::vec3 shipPos = glm::vec3(camera.getCameraPosition().x, camera.getCameraPosition().y - 60, camera.getCameraPosition().z - 100);
glm::vec3 shipPos2 = glm::vec3(0.0f, -15.0f, -15.0f);
glm::vec3 astPos = glm::vec3(-1805.0f, 200.0f, -3000.0f);
glm::vec3 ufoPos = glm::vec3(-500.0f, 3000.0f, 6000.0f);
glm::vec3 pickPos = glm::vec3(-20.0f, -25.0f, 50.0f);
glm::vec3 rockPos = glm::vec3(-500.0f, -85.0f, 1100.0f);
glm::vec3 bucketPos;
glm::vec3 fuelPos;



int main()
{

	glClearColor(0.0f, 0.0f, 0.09f, 1.0f);


	//building and compiling shader program
	Shader shader("Shaders/vertex_shader.glsl", "Shaders/fragment_shader.glsl");
	Shader sunShader("Shaders/sun_vertex_shader.glsl", "Shaders/sun_fragment_shader.glsl");
	Shader shader2("Shaders/water_vertex_shader.glsl", "Shaders/water_fragment_shader.glsl");
	Shader skyboxShader("Shaders/skybox_vertex_shader.glsl", "Shaders/skybox_fragment_shader.glsl");

	//Textures
	GLuint tex = loadBMP("Resources/Textures/rock.bmp");
	GLuint tex2 = loadBMP("Resources/Textures/ast.bmp");
	GLuint tex3 = loadBMP("Resources/Textures/ship.bmp");
	GLuint tex4 = loadBMP("Resources/Textures/planet.bmp");
	GLuint tex5 = loadBMP("Resources/Textures/sand.bmp");
	GLuint tex6 = loadBMP("Resources/Textures/water.bmp");
	GLuint tex7 = loadBMP("Resources/Textures/sand2.bmp");
	GLuint tex8 = loadBMP("Resources/Textures/ufo.bmp");
	GLuint tex9 = loadBMP("Resources/Textures/pickaxe.bmp");
	GLuint tex10 = loadBMP("Resources/Textures/iron.bmp");
	GLuint tex11 = loadBMP("Resources/Textures/fuel.bmp");
	GLuint tex12 = loadBMP("Resources/Textures/space.bmp");


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

	std::vector<Texture> textures9;
	textures9.push_back(Texture());
	textures9[0].id = tex9;
	textures9[0].type = "texture_diffuse";

	std::vector<Texture> textures10;
	textures10.push_back(Texture());
	textures10[0].id = tex10;
	textures10[0].type = "texture_diffuse";

	std::vector<Texture> textures11;
	textures11.push_back(Texture());
	textures11[0].id = tex11;
	textures11[0].type = "texture_diffuse";

	std::vector<Texture> textures12;
	textures12.push_back(Texture());
	textures12[0].id = tex12;
	textures12[0].type = "texture_diffuse";
	// Create Obj files - easier :)
	// we can add here our textures :)
	MeshLoaderObj loader;
	Mesh sun = loader.loadObj("Resources/Models/sphere.obj");
	Mesh planet = loader.loadObj("Resources/Models/planet.obj", textures);
	Mesh planet2 = loader.loadObj("Resources/Models/planet.obj", textures2);
	Mesh planet3 = loader.loadObj("Resources/Models/planet.obj", textures4);
	Mesh planet4 = loader.loadObj("Resources/Models/sphere.obj", textures5);
	Mesh asteroid = loader.loadObj("Resources/Models/asteroid.obj", textures2);
	Mesh ship = loader.loadObj("Resources/Models/ship.obj", textures3);
	Mesh terrain = loader.loadObj("Resources/Models/terrain.obj", textures5);
	Mesh mountain = loader.loadObj("Resources/Models/mountain.obj", textures7);
	Mesh water = loader.loadObj("Resources/Models/terrain.obj", textures6);
	Mesh ufo = loader.loadObj("Resources/Models/ufo.obj", textures8);
	Mesh pickaxe = loader.loadObj("Resources/Models/pickaxe.obj", textures9);
	Mesh rock = loader.loadObj("Resources/Models/rock.obj", textures10);
	Mesh bucket = loader.loadObj("Resources/Models/bucket.obj", textures10);
	Mesh fuel = loader.loadObj("Resources/Models/terrain.obj", textures11);
	Mesh cube = loader.loadObj("Resources/Models/cube.obj", textures12);

	//imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");


	//check if we close the window or press the escape button
	while (!window.isPressed(GLFW_KEY_ESCAPE) &&
		glfwWindowShouldClose(window.getWindow()) == 0)
	{
		
		
		window.clear();
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		
		
		processKeyboardInput();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		 //// Code for the light ////`

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
		//cutscene = false;
		}
		if (cutscene == false) {

			//terrain
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -40.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(3.0f, 1.0f, 3.0f));

			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			terrain.draw(shader);
			//ship
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, shipPos2);
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(20.0f, 20.0f, 20.0f));
			ModelMatrix = glm::rotate(ModelMatrix, 45.0f, glm::vec3(1.0, 1.0, 1.0));
			if (isShipFix)
			{
			ModelMatrix = glm::rotate(ModelMatrix, -45.0f, glm::vec3(1.0, 1.0, 1.0));
			ModelMatrix = glm::rotate(ModelMatrix, 180.0f, glm::vec3(0.0, 1.0, 0.0));
			ModelMatrix = glm::rotate(ModelMatrix, -8.0f, glm::vec3(1.0, 0.0, 0.0));

			}

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
			//ufo animation
			if (ufo_lr) {
				ufoPos.x -= 0.4;
				if (ufoPos.x < -2500.0f)
					ufo_lr = false;
			}
			if (!ufo_lr){
				ufoPos.x += 0.4;
				if (ufoPos.x > 2500.0f)
					ufo_lr = true;
			}

			// pickaxe
			if(isPickaxe){
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, pickPos);
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2.0f, 2, 2));

			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			pickaxe.draw(shader);
			}
			// rock
			if (isRock) {
				ModelMatrix = glm::mat4(1.0);
				ModelMatrix = glm::translate(ModelMatrix, rockPos);
				ModelMatrix = glm::scale(ModelMatrix, glm::vec3(100.0f, 100.0f, 100.0f));

				MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
				glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
				glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

				rock.draw(shader);
			}
			
			// bucket
			if (isBucket) {
				bucketPos = rockPos;
				bucketPos.x += 50;
				bucketPos.y += 25;
				bucketPos.z -= 100;

				ModelMatrix = glm::mat4(1.0);
				ModelMatrix = glm::translate(ModelMatrix, bucketPos);
				ModelMatrix = glm::scale(ModelMatrix, glm::vec3(10.0f, 10.0f, 10.0f));

				MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
				glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
				glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

				bucket.draw(shader);
			}
			// pickaxe animation for mining, fixing
			if (isPickaxe2) {
				if (isShipFix)
				{
					pickPos = rockPos;
					pickPos.y += 70;
					pickPos.z -= 100;
				}
				else {
					pickPos = shipPos2;
					pickPos.x += 5;
					pickPos.y += 15;
					pickPos.z += 10;
				}
				
				ModelMatrix = glm::mat4(1.0);
				ModelMatrix = glm::translate(ModelMatrix, pickPos);
				ModelMatrix = glm::scale(ModelMatrix, glm::vec3(3.0f, 3.0f, 3.0f));
				ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(0.0, 0.0, 1.0));
			

				if((int)lastFrame % 2 == 0) {
				ModelMatrix = glm::rotate(ModelMatrix, 20.0f, glm::vec3(0.0, 1.0, 0.0));
				counter++;
				}
				else {
				ModelMatrix = glm::rotate(ModelMatrix, -20.0f, glm::vec3(0.0, 1.0, 0.0));
				counter++;
				}
				if (isShipFix && counter > 6000)
				{
					isPickaxe2 = false;
					isRock = false;
					isBucket = true;
					

				}
				if (!isShipFix && counter > 6000) {
					counter = 0;
					isPickaxe2 = false;
					isShipFix = true;
			

				}
				MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
				glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
				glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
				pickaxe.draw(shader);
				
			}
			// cube for skybox
			if(skyboxOn2){
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -2000.0f, -4000.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(3000.0f, 3000.0f, 3000.0f));

			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			cube.draw(shader);
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

			//fuel
			if(isFuel){
			fuelPos = rockPos;
			fuelPos.x += 650;
			fuelPos.y += 50;
			fuelPos.z += 750;

			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, fuelPos);

			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			fuel.draw(shader2);
			}
			// calculate distances between player and objects
			distance_ship = sqrt(((camera.getCameraPosition().x - shipPos2.x) * (camera.getCameraPosition().x - shipPos2.x)) + ((camera.getCameraPosition().y - shipPos2.y) * (camera.getCameraPosition().y - shipPos2.y)) + ((camera.getCameraPosition().z - shipPos2.z) * (camera.getCameraPosition().z - shipPos2.z)));
			distance_pkaxe = sqrt(((camera.getCameraPosition().x - pickPos.x) * (camera.getCameraPosition().x - pickPos.x)) + ((camera.getCameraPosition().y - pickPos.y) * (camera.getCameraPosition().y - pickPos.y)) + ((camera.getCameraPosition().z - pickPos.z) * (camera.getCameraPosition().z - pickPos.z)));
			distance_rock = sqrt(((camera.getCameraPosition().x - rockPos.x) * (camera.getCameraPosition().x - rockPos.x)) + ((camera.getCameraPosition().y - rockPos.y) * (camera.getCameraPosition().y - rockPos.y)) + ((camera.getCameraPosition().z - rockPos.z) * (camera.getCameraPosition().z - rockPos.z)));
			distance_bucket = sqrt(((camera.getCameraPosition().x - bucketPos.x) * (camera.getCameraPosition().x - bucketPos.x)) + ((camera.getCameraPosition().y - bucketPos.y) * (camera.getCameraPosition().y - bucketPos.y)) + ((camera.getCameraPosition().z - bucketPos.z) * (camera.getCameraPosition().z - bucketPos.z)));
			distance_fuel = sqrt(((camera.getCameraPosition().x - fuelPos.x) * (camera.getCameraPosition().x - fuelPos.x)) + ((camera.getCameraPosition().y - fuelPos.y) * (camera.getCameraPosition().y - fuelPos.y)) + ((camera.getCameraPosition().z - fuelPos.z) * (camera.getCameraPosition().z - fuelPos.z)));

			//fly home, end scene
			if (endscene)
			{
				camera.reset();
				shipPos2.y += 0.1;
				shipPos2.z -= 0.1;
			}

		}

		std::string currentTaskText;		 
			if (!cutscene) {
				if (isPickaxe) {
					currentTaskText = "You've crashed your spaceship, find tool to fix it.\nPress P to pickup item";
				}
				if (!isPickaxe && !isShipFix) {
					currentTaskText = "You found your tool, use it to fix your spaceship.\nPress Q for repair";
				}
				if (!isPickaxe && isShipFix && isRock) {
					currentTaskText = "Your ship is repaired but it still needs fuel, mine minerals to create bucket.\nPress Q to mine";
				}
				if (!isPickaxe && isShipFix && !isRock && isFuel) {
					currentTaskText = "Here's your bucket, use it to collect fuel.\nPress P to pickup and collect";
				}
				if (!isPickaxe && isShipFix && !isRock && !isBucket && !isFuel && !refill) {
					currentTaskText = "Fuel collected, go to your spaceship and refill it.\nPress Q to refill";
				}
				if (!isPickaxe && isShipFix && !isRock && !isBucket && !isFuel && refill) {
					currentTaskText = "You're ready to go home! Press space to fly home";
				}
			}

		ImGui::Begin("Tasks");
		ImGui::Text(currentTaskText.c_str());
		
		if (ImGui::Button("Skybox On / Off"))
		{
			skyboxOn2 = !skyboxOn2;
		}

		
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		window.update();
	
	}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	
}


void processKeyboardInput()
{
	float cameraSpeed = 60 * deltaTime;

	if (!cutscene && !endscene) {

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
	//collect items
	if (window.isPressed(GLFW_KEY_P)) {
		if (distance_pkaxe < 50) {
			isPickaxe = false;
			
		}
		if (distance_bucket < 50) {
			isBucket = false;
		}
		if (distance_fuel < 400 && !isBucket) {
			isFuel = false;
		

		}
	}
	// mine rock, fix, refuel ship
	if (window.isPressed(GLFW_KEY_Q)) {
		// mine rock
		if (distance_rock < 250 && !isPickaxe && isShipFix) {
			isPickaxe2 = true;
		}
		// fix ship
		if (distance_ship < 100 && !isPickaxe && !isShipFix) {
			isPickaxe2 = true;
		}
		// refuel ship
		if (distance_ship < 100 && !isFuel) {
			refill = true;
			

		}
	}	
	}
	if (window.isPressed(GLFW_KEY_SPACE)) {
		// fly Home
		if (refill) {
			endscene = true;

		}
	}
	
}
