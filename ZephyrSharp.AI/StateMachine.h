#pragma once

#include "common.h"

using namespace System;
using namespace System::Collections::Generic;

namespace ZephyrSharp
{
    namespace AI
    {
        /// <summary>
        /// 状態遷移マシンを表します。
        /// </summary>
        public ref class StateMachine
        {
        private:

            using StateIndex = int;

            static constexpr int AnyState = 0;
            literal String^ AnyStateName = "any";

        public:

            /// <summary>
            /// 定義されている状態の数を取得します。
            /// </summary>
            property int StateCount
            {
                int get() { return m_next_assigned_index; }
            }

            /// <summary>
            /// 現在の状態を取得または設定します。
            /// </summary>
            property String^ CurrentState
            {
                String^ get() { return m_nameMap[m_current_state]; }
                void set(String^ value)
                {
                    runtime_assert(m_indexMap->ContainsKey(value));
                    m_current_state = m_indexMap[value];
                }
            }

            /// <summary>
            /// 現在の状態にとどまっている時間を取得します。
            /// </summary>
            property int DwellTime { int get() { return m_dwell_time; } }

            /// <summary>
            /// 定義されている状態の列挙子を取得します。
            /// </summary>
            property System::Collections::IEnumerable^ States
            {
                System::Collections::IEnumerable^ get()
                {
                    return m_nameMap->Values;
                }
            }

            /// <summary>
            /// 状態遷移マシンが更新される前に発生します。
            /// </summary>
            event Action^ BeforeUpdate;

            /// <summary>
            /// 状態遷移マシンが更新された後に発生します。
            /// </summary>
            event Action^ AfterUpdate;

            /// <summary>
            /// 状態が変化したときに発生します。
            /// </summary>
            event Action^ StateChanged;

        public:

            StateMachine()
            {
                this->StateChanged += gcnew Action(this, &StateMachine::OnStateChanged);
                m_indexMap[AnyStateName] = AnyState;
                m_nameMap[AnyState] = AnyStateName;
                for (int i = 1; i < 64; i++)
                {
                    m_probabilities[i, i] = 1;
                }
            }

            /// <summary>
            /// 状態を定義します。
            /// </summary>
            /// <param name="state">状態名。</param> 
            void DefineState(String^ state)
            {
                runtime_assert(!m_indexMap->ContainsKey(state));
                assign(state);
            }

            /// <summary>
            /// 状態の遷移確率を取得します。
            /// </summary>
            /// <param name="from">遷移前の状態名。</param> 
            /// <param name="to">遷移後の状態名。</param> 
            float GetTransitionProbability(String^ from, String^ to)
            {
                int _from = m_indexMap[from];
                int _to = m_indexMap[to];
                return m_probabilities[_from, _to];
            }

            /// <summary>
            /// 状態の遷移確率を設定します。
            /// </summary>
            /// <param name="from">遷移前の状態名。</param> 
            /// <param name="to">遷移後の状態名。</param> 
            /// <param name="probaility">遷移確率。</param> 
            void SetTransitionProbability(String^ from, String^ to, float probaility)
            {
                assign(from);
                assign(to);
                //runtime_assert(from != AnyStateName);
                int stateIndex1 = m_indexMap[from];
                int stateIndex2 = m_indexMap[to];
                m_probabilities[stateIndex1, stateIndex2] = probaility;
            }

            /// <summary>
            /// 状態遷移マシンを更新し、状態遷移を行います。
            /// </summary>
            void Update()
            {
                BeforeUpdate();

                m_dwell_time++;

                float totalProb = 0;
                array<float>^ probs = gcnew array<float>(this->StateCount);

                for (int j = 1; j < this->StateCount; j++)
                {
                    probs[j] += m_probabilities[m_current_state, j];
                    totalProb += probs[j];

                    probs[j] += m_probabilities[AnyState, j];
                    totalProb += probs[j];
                }

                if (totalProb > 0)
                {
                    RandomEngine^ engine = gcnew RandomEngine();
                    int next_state = engine->Random(gcnew DiscreteDistribution(probs));
                    if (m_current_state != next_state)
                    {
                        m_current_state = next_state;
                        this->StateChanged();
                    }
                }

                AfterUpdate();
            }

        private:

            void OnStateChanged()
            {
                m_dwell_time = 0;
            }

            void assign(String^% stateName)
            {
                stateName = stateName->ToLower();
                if (!m_indexMap->ContainsKey(stateName))
                {
                    m_indexMap[stateName] = m_next_assigned_index;
                    m_nameMap[m_next_assigned_index] = stateName;
                    m_next_assigned_index++;
                }
            }

        private:

            Dictionary<String^, StateIndex>^ m_indexMap = gcnew Dictionary<String^, StateIndex>();
            Dictionary<StateIndex, String^>^ m_nameMap = gcnew Dictionary<StateIndex, String^>();

            array<float, 2>^ m_probabilities = gcnew array<float, 2>(64, 64);

            int m_current_state = 1;
            int m_next_assigned_index = 1;
            int m_dwell_time = 0;
        };
    }
}
