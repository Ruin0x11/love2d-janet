#ifndef EVENT_H_
#define EVENT_H_

#include <modules/love_c/c_Variant.h>
#include <modules/event/c_Event.h>


Janet janetx_wrap_variant(const LoveC_VariantRef ref) {
   LoveC_Variant_Type type = love_Variant_getType(ref);
   const LoveC_Variant_Data* data = love_Variant_getData(ref);

   char* str = NULL;
   size_t len = 0;

   switch (type) {
       case VARIANT_BOOLEAN:
           return janet_wrap_boolean(data->boolean);
       case VARIANT_NUMBER:
           return janet_wrap_number(data->number);
       case VARIANT_STRING:
           love_Variant_SharedString_getData(data->string, &str, &len);
           return janet_stringv(str, len);
       case VARIANT_SMALLSTRING:
           return janet_stringv(data->smallstring.str, data->smallstring.len);
       case VARIANT_NIL:
           return janet_wrap_nil();
       case VARIANT_LUSERDATA:
       case VARIANT_LOVEOBJECT:
       case VARIANT_TABLE:
       default:
           janet_panic("Unsupported variant type");
           break;
   }
   return janet_wrap_nil();
}

static Janet cfun_love_event_poll(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 0);
    LoveC_Event_MessageRef outMes;
    if (love_event_poll(&outMes)) {
        LoveC_VariantRef* args;
        LoveC_SizeT size;
        love_Event_Message_getArgs(outMes, &args, &size);
        const char* mesName = love_Event_Message_getName(outMes);
        JanetArray* arr = janet_array(size + 1);
        janet_array_push(arr, janet_cstringv(mesName));
        for (int i = 0; i < size; i++) {
            Janet data = janetx_wrap_variant(args[i]);
            janet_array_push(arr, data);
        }
        return janet_wrap_array(arr);
    }
    else {
        return janet_wrap_nil();
    }
}

static Janet cfun_love_event_pump(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 0);
    char* error = NULL;
    if (!love_event_pump(&error)) {
        janet_panic(error);
    }
    return janet_wrap_nil();
}

static JanetReg event_cfuns[] = {
    {"event/poll", cfun_love_event_poll,
       "(event/poll)\n\n"
       "Polls for events"
    },
    {"event/pump", cfun_love_event_pump,
       "(event/pump)\n\n"
       "Pumps events"
    },
    {NULL, NULL, NULL}
};

#endif // EVENT_H_
