extern "C"
{
	#include "object.h"
}

#include <CppUTest/TestHarness.h>


/**
 * These 2 are needed to test draw function apply without actually doing
 * any rendering. Basicly we are testing if function pointers are handled rigth.
 */
static int hidden_counter;
static void draw_f(object *obj)
{
	hidden_counter += 1;
}


TEST_GROUP(object_test_group)
{
	jpy_vbo vbo;
	jpy_prog programs[2];
	object *obj;

	void setup() {
		vbo = 1;
		programs[0] = 2;
		programs[1] = 3;
		hidden_counter = 100;
		obj = jpy_create_object(vbo, programs[0], draw_f);
	}

	void teardown() {
		jpy_delete_object(obj);
	}
};



TEST(object_test_group, test_create)
{
	CHECK(jpy_create_object(0, programs[0], draw_f) == 0);
	CHECK(jpy_create_object(vbo, 0, draw_f) == 0);
	CHECK(jpy_create_object(vbo, programs[0], NULL) == 0);
}

TEST(object_test_group, test_vbo)
{
	CHECK(jpy_obj_get_vbo(obj) == vbo);
}

TEST(object_test_group, get_program)
{
	CHECK(jpy_obj_get_program(obj) == programs[0]);
}

TEST(object_test_group, test_draw_func)
{
	int tmp = hidden_counter;
	jpy_obj_draw(obj);
	CHECK(hidden_counter == tmp+1);
}

