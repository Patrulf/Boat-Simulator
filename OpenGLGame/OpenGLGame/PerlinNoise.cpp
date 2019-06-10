#include "PerlinNoise.h"
#include <math.h>

/*Based on perlin noise found here: https://cs.nyu.edu/~perlin/noise/ */
/*OctavePerlin function from here: https://flafla2.github.io/2014/08/09/perlinnoise.html*/
PerlinNoise::PerlinNoise()
{
	for (int i = 0; i < 256; i++)
	{
		p[256 + i] = p[i] = permutation[i];
	}
}


PerlinNoise::~PerlinNoise()
{
}


float PerlinNoise::Noise(float p_x, float p_y, float p_z)
{
	int x = (int)floor(p_x) & 255;
	int y = (int)floor(p_y) & 255;
	int z = (int)floor(p_z) & 255;

	p_x -= floor(p_x);
	p_y -= floor(p_y);
	p_z -= floor(p_z);

	float u = Fade(p_x);
	float v = Fade(p_y);
	float w = Fade(p_z);

	int A = p[x] + y, AA = p[A] + z, AB = p[A + 1] + z,      // HASH COORDINATES OF
		B = p[x + 1] + y, BA = p[B] + z, BB = p[B + 1] + z;	// THE 8 CUBE CORNERS,

	return lerp(w, lerp(v, lerp(u, Grad(p[AA], p_x, p_y, p_z),  // AND ADD
								Grad(p[BA], p_x - 1, p_y, p_z)), // BLENDED
								lerp(u, Grad(p[AB], p_x, p_y - 1, p_z),  // RESULTS
								Grad(p[BB], p_x - 1, p_y - 1, p_z))),// FROM  8
								lerp(v, lerp(u, Grad(p[AA + 1], p_x, p_y, p_z - 1),  // CORNERS
								Grad(p[BA + 1], p_x - 1, p_y, p_z - 1)), // OF CUBE
								lerp(u, Grad(p[AB + 1], p_x, p_y - 1, p_z - 1),
								Grad(p[BB + 1], p_x - 1, p_y - 1, p_z - 1))));

}

float PerlinNoise::Fade(float t) {
	return t * t * t * (t * (t * 6 - 15) + 10);
}

float PerlinNoise::lerp(float p_t, float p_a, float p_b)
{
	return p_a + p_t * (p_b - p_a);
}

float PerlinNoise::Grad(int p_hash, float p_x, float p_y, float p_z)
{
	int h = p_hash & 15;                      // CONVERT LO 4 BITS OF HASH CODE
	float u = h<8 ? p_x : p_y,                 // INTO 12 GRADIENT DIRECTIONS.
		v = h<4 ? p_y : h == 12 || h == 14 ? p_x : p_z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float PerlinNoise::OctavePerlin(float x, float y, float z, int octaves, float persistence) {
	float total = 0;
	float frequency = 1;
	float amplitude = 1;
	float maxValue = 0;

	int i = 0;
	for (i = 0; i<octaves; i++) {
		total += Noise(x * frequency, y * frequency, z * frequency) * amplitude;

		maxValue += amplitude;

		amplitude *= persistence;
		frequency *= 2;
	}

	return total / maxValue;
}

