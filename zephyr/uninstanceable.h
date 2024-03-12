#pragma once

#include "uncopyable.h"

namespace zephyr
{
    /// <summary>
    /// このクラスを継承するクラスは、インスタンスを生成できなくなります。
    /// </summary>
    class uninstanceable : uncopyable
    {
    public:

        // デフォルトコンストラクタ使用不可
        uninstanceable() = delete;
    };
}
