#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <modules/filesystem/c_Filesystem.h>

static Janet cfun_love_filesystem_init(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    char* error = NULL;
    const char* basepath = janet_getcstring(argv, 0);
    if (!love_filesystem_init(basepath, &error)) {
        janet_panic(error);
    }
    return janet_wrap_nil();
}

static Janet cfun_love_filesystem_getExecutablePath(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    char* exepath = NULL;
    love_filesystem_getExecutablePath(&exepath);
    return janet_cstringv(exepath);
}

static Janet cfun_love_filesystem_setSource(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    char* error = NULL;
    const char* basepath = janet_getcstring(argv, 0);
    if (!love_filesystem_setSource(basepath, &error)) {
        janet_panic(error);
    }
    return janet_wrap_nil();
}

static Janet cfun_love_filesystem_setIdentity(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    char* error = NULL;
    const char* identity = janet_getcstring(argv, 0);
    if (!love_filesystem_init(identity, &error)) {
        janet_panic(error);
    }
    return janet_wrap_nil();
}

static Janet cfun_love_filesystem_openFile(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    char* error = NULL;
    const char* filepath = janet_getcstring(argv, 0);
    const char* mode = janet_getcstring(argv, 1);
    LoveC_File_Mode mode_ = MODE_CLOSED;
    if (strcmp(mode, "r") == 0) {
        mode_ = MODE_READ;
    }
    else if (strcmp(mode, "w") == 0) {
        mode_ = MODE_WRITE;
    }
    else if (strcmp(mode, "a") == 0) {
        mode_ = MODE_APPEND;
    }
    LoveC_FileRef *outFile = (LoveC_FileRef *)janet_abstract(&object_type, sizeof(LoveC_FileRef));
    if (!love_filesystem_openFile(filepath, mode_, outFile, &error)) {
        janet_panic(error);
    }
    return janet_wrap_abstract(outFile);
}

static JanetReg filesystem_cfuns[] = {
    {"filesystem/init", cfun_love_filesystem_init,
        "(filesystem/init basepath)\n\n"
        "Initialize filesystem module"
    },
    {"filesystem/get-executable-path", cfun_love_filesystem_getExecutablePath,
        "(filesystem/get-executable-path)\n\n"
        "Gets the executable path"
    },
    {"filesystem/set-source", cfun_love_filesystem_setSource,
        "(filesystem/set-source)\n\n"
        "Sets the filesystem source"
    },
    {"filesystem/set-identity", cfun_love_filesystem_setIdentity,
        "(filesystem/set-identity)\n\n"
        "Sets the filesystem identity"
    },
    {"filesystem/open-file", cfun_love_filesystem_openFile,
        "(filesystem/open-file filepath mode)\n\n"
        "Opens a file. Returns the file handle."
    },
    {NULL, NULL, NULL}
};


#endif // FILESYSTEM_H_
