#pragma once

template <typename T> T myFun(const T &t)
{
    return t;
}

template <typename T, typename... Ts> T myFun(const T &t, const Ts &...args)
{
    return t + myFun<T>(args...);
}

template <typename T1, typename T2> int myCompare(const T1 &t1, const T2 &t2)
{
    if (t1 < t2)
        return -1;
    if (t1 > t2)
        return 1;
    return 0;
}