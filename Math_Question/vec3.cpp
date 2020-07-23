#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include "vec3.h"

const vec3 vec3::zero		= vec3{ 0.0f, 0.0f, 0.0f };
const vec3 vec3::up			= vec3{ 0.0f, 1.0f, 0.0f };
const vec3 vec3::right		= vec3{ 1.0f, 0.0f, 0.0f };
const vec3 vec3::forward	= vec3{ 0.0f, 0.0f, 1.0f };

// Returns the squared length of the vector
float vec3::length_sqr(const vec3& v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

// Returns the length of the vector
float vec3::length(const vec3& v)
{
	return sqrtf(length_sqr(v));
}

// Returns a new vec3 containing the normalized form of `v`
vec3 vec3::normalize(const vec3& v)
{
	const float l = length(v);
	return vec3{ v.x / l, v.y / l, v.z / l };
}

// Returns the dot product between `a` and `b`
float vec3::dot(const vec3& a, const vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Returns a new vec3 containing the cross product between `a` and `b`
vec3 vec3::cross(const vec3& a, const vec3& b)
{
	return vec3
	{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

// Returns a new vector with random values for each component
vec3 vec3::rand_vec(int min, int max)
{
	const int factor = 10 ^ 4;
	int d = max - min;
	float x = (static_cast<float>(rand() % (d * factor)) / factor) + min;
	float y = (static_cast<float>(rand() % (d * factor)) / factor) + min;
	float z = (static_cast<float>(rand() % (d * factor)) / factor) + min;
	return vec3{ x, y, z };
}

// Logs the components of the vector to the stdout
void vec3::print_vec(const vec3& v)
{
	std::cout << std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + "\n";
}