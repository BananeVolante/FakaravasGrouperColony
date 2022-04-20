#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <Environment.h>
#include <Renderer.h>
#include <time.h>
#include <Timer.h>

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
	//new GrouperBase(&environment, environment.randomPosition(), (GrouperHQ *)NULL, Vector2<float>(0, 0), 1.0, 20);
	GrouperHQ* hq = new GrouperHQ(&environment, environment.randomPosition(), "titan grouper");
	GrouperHQ* hq2 = new GrouperHQ(&environment, environment.randomPosition(), "super  grouper");
	ScoreBoard scoreboard(Vector2<float>(0,0));
	scoreboard.addElement(hq);
	scoreboard.addElement(hq2);


	ThreeD::RectCuboid c(Vector3f(100,50,100),Vector3f(500,500,500));
	ThreeD::Camera cam(Eigen::Vector3f(0,0,0), Eigen::Hyperplane<float, 3>(Eigen::Vector3f(0,0,1), Vector3f(0,0,0)), 0, 0);
	ThreeD::ThreeDController controller(&cam);
	//std::cout << c.getPoints()[0] << std::endl;
	//std::cout << controller.project(c.getPoints()[0])[0] <<  controller.project(c.getPoints()[0])[1] << std::endl;
	std::vector<Vector2<float>> pwoints;
	Eigen::AngleAxisf rot(1, Vector3f(1,1,0).normalized());
	auto rotMat = rot.toRotationMatrix();
	for(auto p : c.getPoints())
		pwoints.push_back(controller.project(rotMat * p ) + Vector2<float>(1500,0));


	/*******************************************
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
		scoreboard.draw();
		for(Vector2<float> p : pwoints)
		{
			Renderer::getInstance()->drawCircle(p, 3, Renderer::Color(0,0,255));
		}
		// 3 - We render the scene
		Renderer::getInstance()->flush();
	}

	SDL_Log("Amount of food %f", hq->getAmount());

	std::cout << "Shutting down renderer..." << std::endl;
	Renderer::finalize();

	SDL_Log("shutting down agents");
	Agent::finalize();


	std::cout << "Shutting down SDL" << std::endl;
	SDL_Quit();

	return 0;
}
