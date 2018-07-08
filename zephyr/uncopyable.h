#pragma once

namespace zephyr
{
    /// <summary>
    /// ���̃N���X���p������N���X�́A�C���X�^���X���R�s�[�ł��Ȃ��Ȃ�܂��B
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
