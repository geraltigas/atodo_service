////
//// Created by jb030 on 03/05/2024.
////
//
#include <node_api.h>
#include <interface/database.h>

namespace database_js {
    napi_value check_database_existence(napi_env env, napi_callback_info info) {
        napi_value result;
        bool ret = database::check_database_existence();
        napi_get_boolean(env, ret, &result);
        return result;
    }
    // hello world
    napi_value hello_world(napi_env env, napi_callback_info info) {
        napi_value result;
        napi_create_string_utf8(env, "hello world", NAPI_AUTO_LENGTH, &result);
        return result;
    }
}

napi_value Init(napi_env env, napi_value exports) {
    napi_value check_database_existence_fn;
    napi_create_function(env, nullptr, 0, database_js::check_database_existence, nullptr, &check_database_existence_fn);
    napi_set_named_property(env, exports, "check_database_existence", check_database_existence_fn);

    napi_value hello_world_fn;
    napi_create_function(env, nullptr, 0, database_js::hello_world, nullptr, &hello_world_fn);
    napi_set_named_property(env, exports, "hello_world", hello_world_fn);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)

//#include <napi.h>
//#include <interface/database.h>
//
//Napi::String check_database_existence(const Napi::CallbackInfo &info) {
//    Napi::Env env = info.Env();
//    bool ret = database::check_database_existence();
//    return Napi::String::New(env, ret ? "true" : "false");
//}
//
//Napi::String Method(const Napi::CallbackInfo& info) {
//  // env 是个环境变量，提供一些执行上下文的环境
//  Napi::Env env = info.Env();
//  // 返回一个构造好的 Napi::String 类型的值
//  // New是个静态方法，一般第一个参数是当前执行环境的上下变量，第二个是对应的值
//  // 其他参数不做过多介绍
//  return Napi::String::New(env, "hello world~");
//}

//Napi::Object Init(Napi::Env env, Napi::Object exports) {
////    exports.Set(Napi::String::New(env, "check_database_existence"), Napi::Function::New(env, check_database_existence));
//    exports.Set(
//    Napi::String::New(env, "hello"),
//    Napi::Function::New(env, Method)
//    );
//    return exports;
//}
//
//
//NODE_API_MODULE(database, Init)