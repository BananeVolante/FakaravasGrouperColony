#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <Environment.h>
#include <Renderer.h>
#include <time.h>
#include <Timer.h>
#include <SDL2/SDL_events.h>
#include <algorithm>

#include "Agent.h"
#include "Food.h"
#include "GrouperHQ.h"
#include "GrouperBase.h"
#include "SillyGrouper.h"
#include "Grouper.h"
#include "GrouperWithRules.h"
#include "ScoreBoard.h"
#include "3d/RectCuboid.h"
#include "3d/ThreeDController.h"
#include "3d/ObjParser.h"
#include "3d/CameraControls.h"


static unsigned int windowWidth() { return 1024; }
static unsigned int windowHeight() { return 700; }




/// <summary>
/// called each time a key is pressed.
/// </summary>
/// <param name="key">The key.</param>
/// <param name="environment">The environment.</param>
void onKeyPressed(char key, Environment *environment)
{
	std::cout << "Key pressed: " << key << std::endl;


	if(key == SDLK_UP)


	if (key == 'f') // create a pile of food
	{
		float foodAmount = MathUtils::random(200, 2000);
		Vector2<float> position = environment->randomPosition();
		new Food(environment, position, foodAmount);
		SDL_Log("Created food at (%f, %f) with %f units of food", position[0], position[1], foodAmount);
	}

	if (key == 'd') // destroy a random pile of food
	{
		std::vector<Food *> allFoodPiles = environment->getAllInstancesOf<Food>(); // get all pile of foods
		if (!allFoodPiles.empty())
		{
			size_t selectedIndex = MathUtils::random(0, allFoodPiles.size());
			allFoodPiles[selectedIndex]->setStatus(Agent::destroy);
			SDL_Log("Deleted a pile of food");
		}
		else
			SDL_Log("Tried to delete a pile of food, but there is no food to delete");
	}

	if (key == 'a') // creates a GrouperHQ
	{
		Vector2<float> pos = environment->randomPosition();
		new GrouperHQ(environment, pos, "a");
		SDL_Log("Created a grouperHQ");
	}
}

/// <summary>
/// Called at each time step.
/// </summary>
void onSimulate()
{
	/*************************************
	 * Zone de tests
	 * *************************************/

	/*******************************************
	 * Fin zone de test
	 * ****************************************/
	Agent::simulate();
}

/// <summary>
/// The main program.
/// </summary>
/// <param name="argc">The number of arguments.</param>
/// <param name="argv">The arguments.</param>
/// <returns></returns>
int main(int /*argc*/, char ** /*argv*/)
{
	// 1 - Initialization of SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS /* | SDL_INIT_AUDIO*/) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}
	// 2 - Initialization of the renderer
	Renderer::initialize(windowWidth(), windowHeight());

	// 3 - Creation of an environment
	Environment environment(windowWidth(), windowHeight());

	// 4 - We change the seed of the random number generator
	srand((unsigned int)time(NULL));


	// Define the functions used for rendering points, lines and triangles to the screen
	Renderer* renderer = Renderer::getInstance();
	auto drawPointFunction = [renderer](const Vector2<float>& point, float radius, Fakarava3d::ThreeDController::rgba c)
	{
		renderer->drawCircle(point, radius, Renderer::Color(c.r, c.g, c.b, c.a));
	};
	auto drawLineFunction = [renderer](const Vector2<float>& start,const Vector2<float>& end, Fakarava3d::ThreeDController::rgba c)
	{
		renderer->drawLine(start, end, Renderer::Color(c.r, c.g, c.b, c.a));
	};
	auto drawTriangleFunction = [renderer](const Vector2<float>& firstPoint,const Vector2<float>& secondPoint,const Vector2<float>& thirdPoint, const Fakarava3d::ThreeDController::rgba& c)
	{
		renderer->drawTriangle(firstPoint, secondPoint, thirdPoint, Renderer::Color(c.r, c.g, c.b, c.a));
	};

	// Initialisation of the 3d controller, which creates a camera
	Fakarava3d::ThreeDController controller(Fakarava3d::ThreeDController::point3D{0,0,-10}, windowWidth()/1000.0, windowHeight()/1000.0, 0.5,
	 windowWidth(), windowHeight(), drawPointFunction, drawLineFunction, drawTriangleFunction);
	

	CameraControls controls(controller.getCamera(), 0.3, 1);

	//create some 3d models
	//read the points of a 3d model from a file
	Fakarava3d::Mesh mesh =  Fakarava3d::ObjParser::readObject("ressources/fish.obj");
	Fakarava3d::Mesh reference = Fakarava3d::ObjParser::readObject("ressources/suzanne.obj");

	
	//fps average is made on FRAME_AVERAGE frames
	const size_t FRAME_AVERAGE = 10;
	//containes the fps history of the last FRAME_AVERAGE frames
	std::vector<Uint64> fpsList(FRAME_AVERAGE);
	//count every frame
	int counter = 0;

	// The main event loop...
	SDL_Event event;
	bool exit = false;
	while (!exit)
	{
		//store the time at which the frame starts
		Uint64 timingStart = SDL_GetPerformanceCounter();

		// 1 - We handle events
		while (SDL_PollEvent(&event))
		{
			if ((event.type == SDL_QUIT) || (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'q'))
			{
				::std::cout << "Exit signal detected" << ::std::endl;
				exit = true;
				break;
			}
			if (event.type == SDL_KEYDOWN)
			{
				controls.handleControls(event.key.keysym.sym);
				onKeyPressed((char)event.key.keysym.sym, &environment);
			}
		}
		// 2 - We update the simulation
		Timer::update(1);
		onSimulate();


		//proeject the mesh onto the screen		
		//std::vector<Vector2<float>> projectedPoints = controller.project(mesh.getWorldPoints());
		controller.drawMesh(mesh, Fakarava3d::ThreeDController::DRAW_FLAG_DRAW_TRIANGLE |Fakarava3d::ThreeDController::DRAW_FLAG_FACE_BACK );
		controller.drawMesh(reference);


		//rotate the fish, 
		mesh.rotate(Eigen::AngleAxisf(0.004, Eigen::Vector3f::UnitY()));


		// 3 - We render the scene
		controller.flushDrawings();

		//mark the center of the screen
		Renderer::getInstance()->drawCircle(Vector2<float>(windowWidth()/2, windowHeight()/2), 1, Renderer::Color(255,0,0));

		Renderer::getInstance()->flush();

		//store the time at which the frame ends
		Uint64 timingEnd = SDL_GetPerformanceCounter();

		//process the fps , store it in the vector, process the mean and print it every 10 frames
		float elapsed = (timingEnd - timingStart) / (float)SDL_GetPerformanceFrequency();
		fpsList[counter%10] = 1.0f/elapsed;
		if(counter%10 == 0)
			std::cout << "Current FPS: " << std::to_string(std::accumulate(fpsList.begin(), fpsList.end(),0)/10) << std::endl;

		counter++;

	}

	std::cout << "Shutting down renderer..." << std::endl;
	Renderer::finalize();

	SDL_Log("shutting down agents");
	Agent::finalize();


	std::cout << "Shutting down SDL" << std::endl;
	SDL_Quit();

	return 0;
}
