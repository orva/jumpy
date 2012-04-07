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

static void draw_f2(object *obj)
{
	hidden_counter += 100;
}

TEST_GROUP(object_test_group)
{
	jpy_vbo vbo;
	jpy_prog programs[2];
	draw_func funcs[2];
	object *obj;

	void setup() {
		vbo = 1;
		programs[0] = 2;
		programs[1] = 3;
		funcs[0] = draw_f;
		funcs[1] = draw_f2;
		hidden_counter = 100;
		obj = jpy_obj_create(vbo, programs, funcs, draw_f);
	}

	void teardown() {
		jpy_obj_delete(obj);
	}
};




TEST(object_test_group, test_delete_bad_params)
{
	// this shouldn't segfault
	jpy_obj_delete(NULL);
}


TEST(object_test_group, test_create_bad_params)
{
	object *o = jpy_obj_create(0, programs, funcs, draw_f);
	CHECK(!o);
	jpy_obj_delete(o);

	o = jpy_obj_create(vbo, NULL, funcs, draw_f);
	CHECK(!o);
	jpy_obj_delete(o);

	o = jpy_obj_create(vbo, programs, funcs, NULL);
	CHECK(!o);
	jpy_obj_delete(o);
	
	// Function list is not mandatory
	o = jpy_obj_create(vbo, programs, NULL, draw_f);
	CHECK(o);
	jpy_obj_delete(o);
}


TEST(object_test_group, test_vbo)
{
	CHECK(jpy_obj_get_vbo(obj) == vbo);
	CHECK(!jpy_obj_get_vbo(NULL));
}


TEST(object_test_group, get_program)
{
	CHECK(jpy_obj_get_program(obj, 0) == programs[0]);
}


TEST(object_test_group, get_program_bad_params)
{
	CHECK(!jpy_obj_get_program(NULL, 0));
	CHECK(!jpy_obj_get_program(obj, -1));
	CHECK(!jpy_obj_get_program(obj, 100));
}


TEST(object_test_group, test_draw_func)
{
	int tmp = hidden_counter;
	jpy_obj_draw(obj);
	CHECK(hidden_counter == tmp+1);

	// This should't segfault
	jpy_obj_draw(NULL);
}


TEST(object_test_group, test_invoke)
{
	int tmp = hidden_counter;
	int retval = jpy_obj_invoke(obj, 0);
	CHECK(retval)
	CHECK(hidden_counter == tmp+1);
} 


TEST(object_test_group, test_invoke_bad_params)
{
	int retval = jpy_obj_invoke(obj, -1);
	CHECK(!retval)
	retval = jpy_obj_invoke(obj, 100);
	CHECK(!retval)
	retval = jpy_obj_invoke(NULL, 100);
	CHECK(!retval)
}


TEST(object_test_group, test_invoke_to_object_without_funcs)
{
	object *o = jpy_obj_create(vbo, programs, NULL, draw_f);
	CHECK(!jpy_obj_invoke(o, 0));
	jpy_obj_delete(o);
}

