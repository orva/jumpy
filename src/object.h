#ifndef OBJECT_H
#define OBJECT_H

#include "gpu_data_utils.h"
#include <GL/glfw.h>

typedef struct _object *object;
typedef void (*draw_func)(object *);

object *jpy_obj_create(jpy_vbo vbo, jpy_prog programs[], draw_func funcs[],
		draw_func draw);
void jpy_obj_delete(object *obj);

void jpy_obj_draw(object *obj);
int jpy_obj_invoke(object *obj, size_t id);
jpy_vbo jpy_obj_get_vbo(object *obj);
jpy_prog jpy_obj_get_program(object *obj, size_t id);

#endif

