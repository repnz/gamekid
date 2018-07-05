#pragma once

template <typename T>
void assert_equals(const T& expected, const T& actual)
{
    ASSERT_EQ(expected, actual);
}