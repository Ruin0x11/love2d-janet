#include <janet.h>
#include <assert.h>

#include "core.h"
#include "event.h"
#include "filesystem.h"
#include "graphics.h"
#include "timer.h"
#include "window.h"

JANET_MODULE_ENTRY(JanetTable *env) {
    janet_cfuns(env, "love", core_cfuns);
    janet_cfuns(env, "love", event_cfuns);
    janet_cfuns(env, "love", filesystem_cfuns);
    janet_cfuns(env, "love", graphics_cfuns);
    janet_cfuns(env, "love", timer_cfuns);
    janet_cfuns(env, "love", window_cfuns);
}
