#pragma once

/** Standard issue 3d vector */
struct vec3
{
	float x;
	float y;
	float z;

	vec3 operator -() const
	{
		return vec3{ -x, -y, -z };
	}

	vec3 operator +(const vec3& other) const
	{
		return vec3{ x + other.x, y + other.y, z + other.z };
	}

	vec3 operator -(const vec3& other) const
	{
		return vec3{ x - other.x, y - other.y, z - other.z };
	}

	vec3 operator *(float scalar) const
	{
		return vec3{ x * scalar, y * scalar, z * scalar };
	}

	// Returns the squared length of the vector
	static float length_sqr(const vec3& v);

	// Returns the length of the vector
	static float length(const vec3& v);

	// Returns a new vec3 containing the normalized form of `v`
	static vec3 normalize(const vec3& v);

	// Returns the dot product between `a` and `b`
	static float dot(const vec3& a, const vec3& b);

	// Returns a new vec3 containing the cross product between `a` and `b`
	static vec3 cross(const vec3& a, const vec3& b);

	// Returns a new vector with random values for each component
	static vec3 rand_vec(int min, int max);

	// Logs the components of the vector to the stdout
	static void print_vec(const vec3& v);

	static const vec3 zero;
	static const vec3 up;
	static const vec3 right;
	static const vec3 forward;
};


