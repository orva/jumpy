#ifndef OBJECT_H
#define OBJECT_H

#include "gpu_data_utils.h"

#include <GL/glfw.h>

typedef struct _object *object;
typedef void (*draw_func)(object *);

object *jpy_create_object(jpy_vbo vbo, jpy_prog program, draw_func draw);
void jpy_delete_object(object *obj);
void jpy_obj_draw(object *obj);

jpy_vbo jpy_obj_get_vbo(object *obj);
jpy_shader jpy_obj_get_program(object *obj);

#endif

