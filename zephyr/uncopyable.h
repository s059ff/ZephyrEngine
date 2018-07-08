#pragma once

namespace zephyr
{
    /// <summary>
    /// このクラスを継承するクラスは、インスタンスをコピーできなくなります。
    /// </summary>
    class uncopyable
    {
    public:

        uncopyable() = default;

        ~uncopyable() = default;

        uncopyable(const uncopyable&) = delete;

        uncopyable(uncopyable&&) = delete;

        uncopyable& operator= (const uncopyable&) = delete;

        uncopyable& operator= (uncopyable&&) = delete;
    };
}
