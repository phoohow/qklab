#pragma once

template <typename T>
T myFun(const T &t)
{
    return t;
}

template <typename T, typename... Ts>
T myFun(const T &t, const Ts &...args)
{
    return t + myFun<T>(args...);
}