#pragma once

#define READONLY_PROPERTY(Type, Name, Func) Type _get_##Name() Func __declspec(property(get = _get_##Name)) Type Name

#define WRITEONLY_PROPERTY(Type, Name, Func) void _set_##Name(Type value) Func __declspec(property(put = _set_##Name)) Type Name

#define READWRITE_PROPERTY(Type, Name, GetFunc, SetFunc) Type _get_##Name() GetFunc void _set_##Name(Type value) SetFunc __declspec(property(get = _get_##Name, put = _set_##Name)) Type Name
