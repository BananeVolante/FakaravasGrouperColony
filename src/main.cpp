#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <Environment.h>
#include <Renderer.h>
#include <time.h>
#include <Timer.h>
#include <SDL2/SDL_events.h>

#include "Agent.h"
#include "Food.h"
#include "GrouperHQ.h"
#include "GrouperBase.h"
#include "SillyGrouper.h"
#include "Grouper.h"
#include "GrouperWithRules.h"
#include "ScoreBoard.h"
#include "GrouperSoldier.h"
#include "3d/RectCuboid.h"
#include "3d/ThreeDController.h"

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

	/*************************************
	 * Test area
	 * *************************************/
	/*Eigen::Quaternion<float> quat(0.78,0.484,0.209,0.337);
	ThreeD::Camera camera(Eigen::Vector3f(7.3,-6.9, 4.9), quat.toRotationMatrix(), 31.0/1000, 36.0/1000, 57.0/1000);

	ThreeD::RectCuboid cube(Vector3f(1,1,1), Vector3f(0,0,0));
	Eigen::Matrix3f rotMat(Eigen::AngleAxisf(1.5, Vector3f::UnitX()).toRotationMatrix());
	*/
	//Eigen::Quaternion<float> quat(1,0,0,0);
	
	Fakarava3d::ThreeDController controller(Fakarava3d::ThreeDController::point3D{-60,0,-1000}, windowWidth()/1000.0, windowHeight()/1000.0, 1, windowWidth(), windowHeight());
	Eigen::AngleAxisf rotation(0.0001, Eigen::Vector3f::UnitX());
	Fakarava3d::RectCuboid cube(Vector3f(100,100,100), Vector3f(25,25,300));



	/*******************************************
	 * 
	 * test area end
	 * ****************************************/

	// The main event loop...
	SDL_Event event;
	bool exit = false;
	while (!exit)
	{
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
				onKeyPressed((char)event.key.keysym.sym, &environment);
			}
		}
		// 2 - We update the simulation
		Timer::update(1);
		onSimulate();
		bool start = true;
		Vector2<float> oldPoint;
		for(auto p : cube.getPoints())
		{
			
			Vector2<float> point = controller.project(p);
			if(start)
				start = false;
			else
				Renderer::getInstance()->drawLine(oldPoint, point);
			oldPoint = point;
			Renderer::getInstance()->drawCircle(point, 5, Renderer::Color(0,0,255));
			controller.getCamera().rotate(Eigen::AngleAxisf(0.0001, Eigen::Vector3f::UnitZ() + Eigen::Vector3f::UnitX()/2));

		}

		// 3 - We render the scene
		Renderer::getInstance()->drawCircle(Vector2<float>(windowWidth()/2, windowHeight()/2), 1, Renderer::Color(255,0,0));

		Renderer::getInstance()->flush();

	}

	std::cout << "Shutting down renderer..." << std::endl;
	Renderer::finalize();

	SDL_Log("shutting down agents");
	Agent::finalize();


	std::cout << "Shutting down SDL" << std::endl;
	SDL_Quit();

	return 0;
}
