#include "object.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct _object {
	size_t prog_count;
	size_t func_count;
	jpy_vbo vbo;
	jpy_prog *programs;
	draw_func draw;
	draw_func *funcs;
};


object *jpy_obj_create(jpy_vbo vbo, jpy_prog programs[], draw_func funcs[],
		draw_func draw)
{
	if (vbo == 0 || programs == NULL || draw == NULL)
		return NULL;


	struct _object *obj = malloc(sizeof(struct _object));
	obj->vbo = vbo;

	obj->programs = malloc(sizeof programs);
	memcpy(obj->programs, programs, sizeof programs);
	obj->prog_count = sizeof programs/sizeof *programs;

	if (funcs) {
		obj->funcs = malloc(sizeof funcs);
		memcpy(obj->funcs, funcs, sizeof programs);
		obj->func_count = sizeof funcs/sizeof *funcs;
	} else {
		obj->funcs = NULL;
		obj->func_count = 0;
	}

	obj->draw = draw;

	return (object *)obj;
}


void jpy_obj_delete(object *obj)
{
	if (!obj)
		return;

	// TODO refcounting some day
	struct _object *tmp = (struct _object *)obj;
	
	if (tmp->funcs)
		free(tmp->funcs);
	if (tmp->programs)
		free(tmp->programs);
	free(tmp);
}


void jpy_obj_draw(object *obj)
{
	if (!obj)
		return;

	struct _object *tmp = (struct _object *)obj;
	draw_func fun = tmp->draw;
	fun(obj);
}


jpy_vbo jpy_obj_get_vbo(object *obj)
{
	if (!obj)
		return 0;

	struct _object *tmp = (struct _object *)obj;
	return tmp->vbo;
}


jpy_prog jpy_obj_get_program(object *obj, size_t id)
{
	if (!obj)
		return 0;

	struct _object *tmp = (struct _object *)obj;
	if (id >= tmp->prog_count)
		return 0;

	return tmp->programs[id];
}


int jpy_obj_invoke(object *obj, size_t id)
{
	if (!obj)
		return 0;

	struct _object *tmp = (struct _object *)obj;
	if (id >= tmp->func_count)
		return 0;

	draw_func fun = tmp->funcs[id];
	fun(obj);

	return 1;
}

