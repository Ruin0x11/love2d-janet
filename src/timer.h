#ifndef TIMER_H_
#define TIMER_H_

#include <modules/timer/c_Timer.h>

static Janet cfun_love_timer_step(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 0);
    love_timer_step();
    return janet_wrap_nil();
}

static Janet cfun_love_timer_sleep(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    double secs = janet_getnumber(argv, 1);
    love_timer_sleep(secs);
    return janet_wrap_nil();
}

static JanetReg timer_cfuns[] = {
    {"timer/step", cfun_love_timer_step,
       "(timer/step)\n\n"
       "Steps the current timer"
    },
    {"timer/sleep", cfun_love_timer_sleep,
       "(timer/sleep secs)\n\n"
       "Sleep for a set period of seconds"
    },
    {NULL, NULL, NULL}
};

#endif // TIMER_H_
