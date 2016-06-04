#ifndef json_h
#define json_h

#ifdef WITH_JANSSON
#include <jansson.h>

#define JSON_OBJECT json_t
#define JSON_TOKENER_DEF(t)

#define JSON_LOADB(jsobj, jstok, buf, buflen, flags) {     \
    jsobj = json_loadb(buf, (size_t)buflen, flags, NULL);  \
}

#define JSON_TOKENER_NEW(t)
#define JSON_TOKENER_FREE(t)

#define JSON_DECREF(jsobj) \
    json_decref(jsobj)

#define JSON_ARRAY_LENTH(jsobj) \
    json_array_size(jsobj)

#define JSON_ARRAY_GET(jsobj, i) \
    json_array_get(jsobj, i)

#define JSON_OBJECT_GET(jsobj, key, value) { \
    value = json_object_get(jsobj, key);     \
}

#define JSON_STRING_VALUE(jsobj) \
    json_string_value(jsobj)

#define JSON_INT_VALUE(jsobj) \
    json_integer_value(jsobj)

#else

#include <json-c/json.h>

#define JSON_OBJECT struct json_object
#define JSON_TOKENER_DEF(t) struct json_tokener t

#define JSON_LOADB(jsobj, jstok, buf, buflen, flags) {      \
    jstok = json_tokener_new();                             \
    jsobj = json_tokener_parse_ex(jstok, buf, (int)buflen); \
}

#define JSON_TOKENER_NEW(t) { \
    t = json_tokener_new();   \
}
#define JSON_TOKENER_FREE(t) \
    json_tokener_free(t)

#define JSON_DECREF(jsobj) \
    json_object_put(jsobj)

#define JSON_ARRAY_LENTH(jsobj) \
    json_object_array_length(jsobj)

#define JSON_ARRAY_GET(jsobj, i) \
    json_object_array_get_idx(jsobj, i)

#define JSON_OBJECT_GET(jsobj, key, value) {       \
    json_object_object_get_ex(jsobj, key, &value); \
}

#define JSON_STRING_VALUE(jsobj) \
    json_object_get_string(jsobj)

#define JSON_INT_VALUE(jsobj) \
    json_object_get_int(jsobj)

#endif

#endif /* ifndef json_h */
