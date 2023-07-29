#ifndef FONT_H_
#define FONT_H_


#include <modules/font/c_Font.h>


static Janet cfun_love_font_newTrueTypeRasterizer(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    char* error = NULL;
    LoveC_FileDataRef* fileData = janet_getabstract(argv, 0);
    int size = janet_getinteger(argv, 1);
    int dpiscale = janet_getnumber(argv, 2);
    const char* hinting = janet_getcstring(argv, 3);
    love_Object_retain((LoveC_ObjectRef)(*fileData));
    LoveC_Font_TrueTypeRasterizer_Hinting hinting_ = HINTING_NORMAL;
    if (strcmp(str, "light") == 0) {
        hinting_ = HINTING_LIGHT;
    }
    else if (strcmp(str, "mono") == 0) {
        hinting_ = HINTING_MONO;
    }
    else if (strcmp(str, "none") == 0) {
        hinting_ = HINTING_NONE;
    }
    LoveC_Font_RasterizerRef *outRasterizer = (LoveC_Font_RasterizerRef *)janet_abstract(&object_type, sizeof(LoveC_Font_RasterizerRef));
    if (!love_font_newTrueTypeRasterizer(fileData, 12, 1.0, hinting_, outRasterizer, &error)) {
        janet_panic(error);
    }
    return janet_wrap_abstract(outRasterizer);
}


static JanetReg font_cfuns[] = {
    {"font/new-true-type-rasterizer", cfun_love_font_newTrueTypeRasterizer,
        "(filesystem/new-true-type-rasterizer file-data size dpiscale hinting)\n\n"
        "Creates a new TrueType rasterizer."
    },
    {NULL, NULL, NULL}
};

#endif // FONT_H_
