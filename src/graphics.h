#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <modules/graphics/c_Graphics.h>

static Janet cfun_love_graphics_setGammaCorrect(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int enable = janet_getboolean(argv, 0);
    love_graphics_setGammaCorrect(enable);
    return janet_wrap_nil();
}

static Janet cfun_love_graphics_newFont(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    char* error = NULL;
    LoveC_Font_RasterizerRef* rasterizer = janet_getabstract(argv, 0, &object_type);
    LoveC_FontRef* outFont = (LoveC_FontRef*)janet_abstract(&object_type, sizeof(LoveC_FontRef));
    love_Object_retain((LoveC_ObjectRef)(*rasterizer));
    if (!love_graphics_newFont(*rasterizer, outFont, &error)) {
        janet_panic(error);
    }
    return janet_wrap_nil();
}

static Janet cfun_love_graphics_setBackgroundColor(int32_t argc, Janet *argv) {
    janet_arity(argc, 1, 4);
    float r = 1;
    float g = 1;
    float b = 1;
    float a = 1;
    if (argc == 1) {
        if (janet_checktype(argv[0], JANET_NUMBER))
            r = (float)janet_getnumber(argv, 0);
    }
    if (argc <= 2) {
        if (janet_checktype(argv[1], JANET_NUMBER))
            g = (float)janet_getnumber(argv, 1);
    }
    if (argc <= 3) {
        if (janet_checktype(argv[2], JANET_NUMBER))
            b = (float)janet_getnumber(argv, 2);
    }
    if (argc <= 4) {
        if (janet_checktype(argv[3], JANET_NUMBER))
            a = (float)janet_getnumber(argv, 3);
    }
    LoveC_Colorf bg = {.r = r, .g = g, .b = b, .a = a};
    love_graphics_setBackgroundColor(&bg);
    return janet_wrap_nil();
}

static Janet cfun_love_graphics_isActive(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 0);
    LoveC_Bool active = love_graphics_isActive();
    return janet_wrap_boolean(active);
}

static Janet cfun_love_graphics_origin(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 0);
    love_graphics_origin();
    return janet_wrap_nil();
}

static Janet cfun_love_graphics_present(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 0);
    char* error = NULL;
    if (!love_graphics_present(&error)) {
        janet_panic(error);
    }
    return janet_wrap_nil();
}

static JanetReg graphics_cfuns[] = {
    {"graphics/set-gamma-correct", cfun_love_graphics_setGammaCorrect,
        "(graphics/set-gamma-correct enabled)\n\n"
        "Sets gamma correction"
    },
    {"graphics/new-font", cfun_love_graphics_newFont,
        "(graphics/new-font rasterizer)\n\n"
        "Creates a new Font"
    },
    {"graphics/set-background-color", cfun_love_graphics_setBackgroundColor,
        "(graphics/set-background-color r g b a)\n\n"
        "Sets the background color"
    },
    {"graphics/is-active", cfun_love_graphics_isActive,
        "(graphics/is-active)\n\n"
        "Returns true if graphics is active"
    },
    {"graphics/origin", cfun_love_graphics_origin,
        "(graphics/origin)\n\n"
        "Resets graphics to origin"
    },
    {"graphics/present", cfun_love_graphics_present,
        "(graphics/present)\n\n"
        "Presents graphics"
    },
    {NULL, NULL, NULL}
};

#endif // GRAPHICS_H_
