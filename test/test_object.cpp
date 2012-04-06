extern "C"
{
	#include "object.h"
	#include <stdio.h>

}

#include <CppUTest/TestHarness.h>


int hidden_counter;
void draw_f(object *obj)
{
	hidden_counter += 1;
}


TEST_GROUP(object_test_group)
{
	jpy_vbo vbo;
	jpy_shader shaders;
	object *obj;

	void setup() {
		vbo = 1;
		shaders = 2;
		hidden_counter = 1;
		obj = jpy_create_object(vbo, shaders, draw_f);
	}

	void teardown() {
		jpy_delete_object(obj);
	}
};


TEST(object_test_group, test_create)
{
	CHECK(jpy_obj_get_vbo(obj) == vbo);
}


TEST(object_test_group, get_shader)
{
	CHECK(jpy_obj_get_shaders(obj) == shaders);
}


TEST(object_test_group, draw_object)
{
	int tmp = hidden_counter;
	jpy_obj_draw(obj);
	CHECK(hidden_counter == tmp+1);
}

