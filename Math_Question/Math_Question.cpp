#include <iostream>
#include <string>
#include <vector>

// == Defines a vector class with a few helpful functions provided
#include "vec3.h"

/*
* Your task is to implement the body of this function such that it does the following:
*
* This function is used to determine which object within the players field of view they are looking at, in order
* to select / highlight that object. It should return the index in the targets array, of the "best" target
*
* The best target is the one which one is closest to the aim ray.
* Imagine the field of view represented by the aim location and direction, you want to find the target that
* is closest to the center of this field of view.
*
* For bonus points, you can factor in the distance of the target to the aim location to favour nearer targets
* over far away ones.
*/
int get_best_target(vec3 aimDirection, vec3 aimLocation, const std::vector<vec3>& targets)
{
	return -1;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~
//  MAIN Function
//  - Your implementation should support all of the tests performed in this method
int main()
{
	std::cout << "targets: \n";

	// generate some random targets in range -10 to 10, with a few decimal points
	std::vector<vec3> targets;
	for (int i = 0; i < 10; ++i)
	{
		vec3 v = vec3::rand_vec(-10, 10);
		targets.push_back(v);
	
		std::cout << std::to_string(i) + ": ";
		vec3::print_vec(v);
	}

	std::cout << "\n\n";

	vec3 aimDir = vec3::forward;
	vec3 aimLoc = vec3::rand_vec(-5, 5);

	std::cout << "results:\n";
	std::cout << "view point = ";
	vec3::print_vec(aimLoc);

	int bestIdx = get_best_target(aimDir, aimLoc, targets);
	if (bestIdx <= 0)
	{
		std::cout << "get_best_target failed to find a valid target!";
	}
	else
	{
		std::cout << "the best target was [" + std::to_string(bestIdx) + "]";
	}

	// keep the console open
	std::string str;
	std::cin >> str;
	return 0;
}