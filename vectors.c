# include <math.h>

# include "vectors.h"
# define G 6.67e-11

double get_distance (struct Point * p1, struct Point * p2) {
	return sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2));
}

struct Vector multiply (struct Vector * v, double f) {
	return (struct Vector){v->x*f, v->y*f};
}

struct Vector add (struct Vector * v1, struct Vector * v2) {
	return (struct Vector){v1->x + v2->x, v1->y + v2->y};
}

struct Vector get_vector (struct Point * p1, struct Point * p2) {
	return (struct Vector){p1->x - p2->x, p1->y - p2->y};
}

struct Vector get_force_vector (struct PhysicalObject * obj1, struct PhysicalObject * obj2) {
	double dist, force;
	struct Vector dir;
	dir = get_vector(&(obj1->pos), &(obj2->pos));
	dist = get_distance(&(obj1->pos), &(obj2->pos));
	force = obj1->weight*obj2->weight*G/pow(dist, 2);
	dir = multiply(&dir, force / dist);
	return dir;
}


struct Vector get_acceleration_vector (struct PhysicalObject * obj1, struct PhysicalObject * obj2) {
	double dist, force;
	struct Vector dir;
	dir = get_vector(&(obj1->pos), &(obj2->pos));
	dist = get_distance(&(obj1->pos), &(obj2->pos));
	force = obj1->weight*G/pow(dist, 2);
	dir = multiply(&dir, force / dist);
	return dir;
}
