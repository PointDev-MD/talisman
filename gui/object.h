#ifndef GUI_OBJECT_H
#define GUI_OBJECT_H

#include <stdint.h>
#include "graphics.h"

typedef struct Object Object;
typedef struct ObjectClass ObjectClass;

struct ObjectClass {
    void (*destroy)(Object *self);
    void (*draw)(Object *self);
    void (*handle_event)(Object *self, int event_type, int param);
};

struct Object {
    ObjectClass *klass;
    Rect bounds;
};

Object *object_new(void);
void object_destroy(Object *obj);
void object_draw(Object *obj);
void object_handle_event(Object *obj, int event_type, int param);

#endif
