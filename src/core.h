#ifndef CORE_H_
#define CORE_H_

#include <modules/love_c/love_c.h>
#include <modules/love_c/c_Object.h>

static Janet cfun_love_init(int32_t argc, Janet *argv) {
    (void) argv;
    char *error = NULL;
    janet_fixarity(argc, 0);
    if (!love_init(&error)) {
        janet_panic(error);
    }
    return janet_wrap_nil();
}

static JanetReg core_cfuns[] = {
    {"init", cfun_love_init,
        "(init)\n\n"
        "Initialize LÖVE engine"
    },
    {NULL, NULL, NULL}
};

static int object_gc(void *p, size_t s) {
    (void)s;
    LoveC_ObjectRef *ref = (LoveC_ObjectRef *)p;
    assert(love_Object_getReferenceCount(*ref) == 1);
    love_Object_release(*ref);
    return 0;
}

static const JanetAbstractType object_type = {
    "love/object",
    object_gc,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};


#endif // CORE_H_
