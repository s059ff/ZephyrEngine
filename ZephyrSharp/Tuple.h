namespace ZephyrSharp
{
    /// <summary>
    /// 1 つの要素の組み合わせを表します。
    /// </summary>
    generic <typename T1> public value struct Tuple1
    {
        Tuple1(T1 item1)
            : Item1(item1)
        {
        }

        T1 Item1;
    };

    /// <summary>
    /// 2 つの要素の組み合わせを表します。
    /// </summary>
    generic <typename T1, typename T2> public value struct Tuple2
    {
        Tuple2(T1 item1, T2 item2)
            : Item1(item1), Item2(item2)
        {
        }

        T1 Item1;
        T2 Item2;
    };

    /// <summary>
    /// 3 つの要素の組み合わせを表します。
    /// </summary>
    generic <typename T1, typename T2, typename T3> public value struct Tuple3
    {
        Tuple3(T1 item1, T2 item2, T3 item3)
            : Item1(item1), Item2(item2), Item3(item3)
        {
        }

        T1 Item1;
        T2 Item2;
        T3 Item3;
    };

    /// <summary>
    /// 4 つの要素の組み合わせを表します。
    /// </summary>
    generic <typename T1, typename T2, typename T3, typename T4> public value struct Tuple4
    {
        Tuple4(T1 item1, T2 item2, T3 item3, T4 item4)
            : Item1(item1), Item2(item2), Item3(item3), Item4(item4)
        {
        }

        T1 Item1;
        T2 Item2;
        T3 Item3;
        T4 Item4;
    };

    /// <summary>
    /// 5 つの要素の組み合わせを表します。
    /// </summary>
    generic <typename T1, typename T2, typename T3, typename T4, typename T5> public value struct Tuple5
    {
        Tuple5(T1 item1, T2 item2, T3 item3, T4 item4, T5 item5)
            : Item1(item1), Item2(item2), Item3(item3), Item4(item4), Item5(item5)
        {
        }

        T1 Item1;
        T2 Item2;
        T3 Item3;
        T4 Item4;
        T5 Item5;
    };

    /// <summary>
    /// 6 つの要素の組み合わせを表します。
    /// </summary>
    generic <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> public value struct Tuple6
    {
        Tuple6(T1 item1, T2 item2, T3 item3, T4 item4, T5 item5, T6 item6)
            : Item1(item1), Item2(item2), Item3(item3), Item4(item4), Item5(item5), Item6(item6)
        {
        }

        T1 Item1;
        T2 Item2;
        T3 Item3;
        T4 Item4;
        T5 Item5;
        T6 Item6;
    };

    /// <summary>
    /// 7 つの要素の組み合わせを表します。
    /// </summary>
    generic <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> public value struct Tuple7
    {
        Tuple7(T1 item1, T2 item2, T3 item3, T4 item4, T5 item5, T6 item6, T7 item7)
            : Item1(item1), Item2(item2), Item3(item3), Item4(item4), Item5(item5), Item6(item6), Item7(item7)
        {
        }

        T1 Item1;
        T2 Item2;
        T3 Item3;
        T4 Item4;
        T5 Item5;
        T6 Item6;
        T7 Item7;
    };

    /// <summary>
    /// 8 つの要素の組み合わせを表します。
    /// </summary>
    generic <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> public value struct Tuple8
    {
        Tuple8(T1 item1, T2 item2, T3 item3, T4 item4, T5 item5, T6 item6, T7 item7, T8 item8)
            : Item1(item1), Item2(item2), Item3(item3), Item4(item4), Item5(item5), Item6(item6), Item7(item7), Item8(item8)
        {
        }

        T1 Item1;
        T2 Item2;
        T3 Item3;
        T4 Item4;
        T5 Item5;
        T6 Item6;
        T7 Item7;
        T8 Item8;
    };
}
