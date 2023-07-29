#ifndef WINDOW_H_
#define WINDOW_H_


#include <modules/window/c_Window.h>

static Janet cfun_love_window_setTitle(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char* title = janet_getcstring(argv, 0);
    love_window_setTitle(title);
    return janet_wrap_nil();
}

static Janet cfun_love_window_setMode(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    char* error = NULL;
    double width = janet_getnumber(argv, 0);
    double height = janet_getnumber(argv, 1);
    JanetTable* settings;
    if (janet_checktype(argv[2], JANET_STRUCT)) {
        JanetStruct settingsStruct = janet_getstruct(argv, 2);
        settings = janet_struct_to_table(settingsStruct);
    }
    else {
        settings = janet_gettable(argv, 2);
    }
    LoveC_Window_WindowSettings settings_;

#define GET_SETTING(name, type, type2) \
    Janet name ## _ = janet_table_get(settings, janet_ckeywordv(#name)); \
    if (janet_checktype(name ## _, JANET_ ## type2)) { \
        settings_.name = janet_unwrap_ ## type(name ## _); \
    }

    GET_SETTING(fullscreen, boolean, BOOLEAN);
    GET_SETTING(fstype, number, NUMBER);
    GET_SETTING(vsync, integer, NUMBER);
    GET_SETTING(msaa, integer, NUMBER);
    GET_SETTING(stencil, boolean, BOOLEAN);
    GET_SETTING(depth, integer, NUMBER);
    GET_SETTING(resizable, boolean, BOOLEAN);
    GET_SETTING(minwidth, integer, NUMBER);
    GET_SETTING(minheight, integer, NUMBER);
    GET_SETTING(borderless, boolean, BOOLEAN);
    GET_SETTING(centered, boolean, BOOLEAN);
    GET_SETTING(displayindex, integer, NUMBER);
    GET_SETTING(highdpi, boolean, BOOLEAN);
    GET_SETTING(usedpiscale, boolean, BOOLEAN);
    GET_SETTING(refreshrate, number, NUMBER);
    GET_SETTING(useposition, boolean, BOOLEAN);
    GET_SETTING(x, integer, NUMBER);
    GET_SETTING(y, integer, NUMBER);

#undef GET_SETTING

    if (!love_window_setMode(width, height, &settings_, &error)) {
        janet_panic(error);
    }
    return janet_wrap_nil();
}

static JanetReg window_cfuns[] = {
    {"window/set-title", cfun_love_window_setTitle,
        "(window/set-title title)\n\n"
        "Sets the window's title"
    },
    {"window/set-mode", cfun_love_window_setMode,
        "(window/set-mode width height {:fullscreen true, ...})\n\n"
        "Sets the window's mode"
    },
    {NULL, NULL, NULL}
};


#endif // WINDOW_H_
