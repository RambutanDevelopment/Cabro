#pragma once

//Templated within function, checks if the value is with in the array of size size
template<typename T> 
bool within(T checkVal, T* checkArray, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (checkVal == checkArray[i]) return true;
    }
    return false;
}

template<typename T> 
bool within(T checkVal, const T* checkArray, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (checkVal == checkArray[i]) return true;
    }
    return false;
}