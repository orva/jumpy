#include "object.h"

#include <stdlib.h>

struct _object {
	jpy_vbo vbo;
	jpy_shader shader;
	draw_func draw;
};


object *jpy_create_object(jpy_vbo vbo, jpy_shader shaders, draw_func draw)
{
	struct _object *obj = malloc(sizeof(object));
	obj->vbo = vbo;
	obj->shader = shaders;
	obj->draw = draw;

	return (object *)obj;
}


void jpy_delete_object(object *obj)
{
	// TODO refcounting some day
	free(obj);
}


void jpy_obj_draw(object *obj)
{
	struct _object *tmp = (struct _object *)obj;
	tmp->draw(obj);
}


jpy_vbo jpy_obj_get_vbo(object *obj)
{
	struct _object *tmp = (struct _object *)obj;
	return tmp->vbo;
}


jpy_shader jpy_obj_get_shaders(object *obj)
{
	struct _object *tmp = (struct _object *)obj;
	return tmp->shader;
}

