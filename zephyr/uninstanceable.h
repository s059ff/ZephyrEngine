#pragma once

#include "uncopyable.h"

namespace zephyr
{
    /// <summary>
    /// ���̃N���X���p������N���X�́A�C���X�^���X�𐶐��ł��Ȃ��Ȃ�܂��B
    /// </summary>
    class uninstanceable : uncopyable
    {
    public:

        // �f�t�H���g�R���X�g���N�^�g�p�s��
        uninstanceable() = delete;
    };
}
