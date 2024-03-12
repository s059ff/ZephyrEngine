#pragma once

#include "functional.h"
#include "vector.h"

namespace zephyr
{
    template <typename ...Args>
    class event
    {
        using action = function<void(Args...)>;

    public:

        void call(Args... args)
        {
            for (auto& action : m_actions)
            {
                action(args...);
            }
        }

        void clear() {
            m_actions.clear();
        }

        void operator +=(const action& action)
        {
            m_actions.push_back(action);
        }

        void operator +=(action&& action)
        {
            m_actions.push_back(std::move(action));
        }

        void operator =(const event& actions)
        {
            m_actions = actions;
        }

        void operator =(event&& actions)
        {
            m_actions = std::move(actions);
        }

        void operator ()(Args... args)
        {
            call(args...);
        }

        action* begin() { return m_actions.data(); }

        const action* begin() const { return m_actions.data(); }

        action* end() { return m_actions.data() + m_actions.size(); }

        const action* end() const { return m_actions.data() + m_actions.size(); }

    private:

        vector<action> m_actions;
    };
}
