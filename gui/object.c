#include "object.h"
#include <stdlib.h>

static void default_destroy(Object *self) {
    if (self) {
        free(self);
    }
}

static void default_draw(Object *self) {
}

static void default_handle_event(Object *self, int event_type, int param) {
}

static ObjectClass base_class = {
    .destroy = default_destroy,
    .draw = default_draw,
    .handle_event = default_handle_event,
};

Object *object_new(void) {
    Object *obj = (Object *)malloc(sizeof(Object));
    if (obj) {
        obj->klass = &base_class;
        obj->bounds.x = 0;
        obj->bounds.y = 0;
        obj->bounds.width = 0;
        obj->bounds.height = 0;
    }
    return obj;
}

void object_destroy(Object *obj) {
    if (obj && obj->klass && obj->klass->destroy) {
        obj->klass->destroy(obj);
    }
}

void object_draw(Object *obj) {
    if (obj && obj->klass && obj->klass->draw) {
        obj->klass->draw(obj);
    }
}

void object_handle_event(Object *obj, int event_type, int param) {
    if (obj && obj->klass && obj->klass->handle_event) {
        obj->klass->handle_event(obj, event_type, param);
    }
}
