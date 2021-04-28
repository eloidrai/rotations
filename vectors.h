struct Vector {
	double x;
	double y;
};

struct Point {
	double x;
	double y;
};

struct PhysicalObject {
	struct Point pos;
	struct Vector movement;
	double weight;
};

double get_distance (struct Point * p1, struct Point * p2);
struct Vector multiply (struct Vector * v, double f);
struct Vector add (struct Vector * v1, struct Vector * v2);


struct Vector get_vector (struct Point * p1, struct Point * p2);

struct Vector get_force_vector (struct PhysicalObject * obj1, struct PhysicalObject * obj2);
struct Vector get_acceleration_vector (struct PhysicalObject * obj1, struct PhysicalObject * obj2);
