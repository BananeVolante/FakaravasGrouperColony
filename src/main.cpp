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

static unsigned int windowWidth() { return 1920; }
static unsigned int windowHeight() { return 1080; }

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
	 * Zone de tests
	 * *************************************/
	//new GrouperBase(&environment, environment.randomPosition(), (GrouperHQ *)NULL, Vector2<float>(0, 0), 1.0, 20);
	GrouperHQ* hq = new GrouperHQ(&environment, environment.randomPosition(), "titan grouper");
	GrouperHQ* hq2 = new GrouperHQ(&environment, environment.randomPosition(), "super  grouper");
	ScoreBoard scoreboard(Vector2<float>(0,0));
	scoreboard.addElement(hq);
	scoreboard.addElement(hq2);
	for (size_t i = 0; i < 100; i++)
	{
		new GrouperWithRules(&environment, environment.randomPosition(), hq, Vector2<float>::random(), 3, 1);
	}
	for (size_t i = 0; i < 100; i++)
	{
		new GrouperWithRules(&environment, environment.randomPosition(), hq2, Vector2<float>::random(), 3, 1);
	}

	/*******************************************
	 * Fin zone de test
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
		Timer::update(0.5);
		onSimulate();
		scoreboard.draw();
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
