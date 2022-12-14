#include "selection_lib"
#include <iostream>

void someTest()
{
    std::cout << "Working with selection flow." << std::endl;
}

void selection_homework1()
{
    int a, b;
    std::cin >> a >> b;

    bool a_is_even = a % 2 == 0, b_is_even = b % 2 == 0;

    if (!a_is_even && !b_is_even)
        std::cout << a * b << std::endl;

    else if (a_is_even && b_is_even)
        std::cout << a / b << std::endl;

    else if (!a_is_even && b_is_even)
        std::cout << a + b << std::endl;
    else
        std::cout << a - b << std::endl;
}

void selection_homework2()
{
    int a, b, c;
    std::cin >> a >> b >> c;
    std::vector<int> v = {a, b, c};
    std::sort(v.begin(), v.end());
    for (int x : v)
        std::cout << x << " ";
    std::cout << std::endl;
}

void selection_homework3()
{
    int a, b, c;
    std::cin >> a >> b >> c;
    std::vector<int> v = {a, b, c};
    std::sort(v.begin(), v.end());
    for (int i = 2; i >= 0; i--)
    {
        if (v[i] < 100)
        {
            std::cout << v[i] << std::endl;
            return;
        }
    }
    std::cout << -1 << std::endl;
    return;
}

void selection_homework4()
{
    int x;
    int a1, a2, a3, a4, a5;
    std::cin >> x;
    std::cin >> a1 >> a2 >> a3 >> a4 >> a5;
    std::vector<int> v = {a1, a2, a3, a4, a5};
    sort(v.begin(), v.end());
    int count = 0;
    for (int i = 0; i < 5; i++)
        if (v[i] <= x)
            count++;
        else
            break;
    std::cout << count << " " << 5 - count << std::endl;
}

void selection_homework5()
{
    int x;
    std::vector<int> v(10);
    for (int i = 0; i < 10; i++)
    {
        std::cin >> x;
        v[i] = x;
    }
    sort(v.begin(), v.end());
    std::cout << v[9] << std::endl;
}

void selection_homework6()
{
    int x;
    int N;
    std::cin >> N;
    std::vector<int> v(N);
    for (int i = 0; i < N; i++)
    {
        std::cin >> x;
        v[i] = x;
    }
    sort(v.begin(), v.end());
    std::cout << v[N - 1] << std::endl;
}

void selection_homework7()
{
    int x;
    int start, end;

    int count = 0;
    std::cin >> x;
    for (int i = 0; i < 3; i++)
    {
        std::cin >> start >> end;
        Interval interval(start, end);
        count += interval.has(x);
    }

    std::cout << count << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Interval &original)
{
    os << "[" << original.start << "," << original.end << "]";
    return os;
}

bool operator<(const Interval &i1, const Interval &i2)
{
    return (i1.start < i2.start);
}

void testingIntervals()
{
    Interval i(1, 2), i1(3, 4), i2(-1, 3);
    std::cout << (i < i1) << std::endl;
    std::vector<Interval> v_i = {i1, i, i2};
    for (auto x : v_i)
        std::cout << x << " ";
    std::cout << std::endl;
    sort(v_i.begin(), v_i.end());
    for (auto x : v_i)
        std::cout << x << " ";
    std::cout << std::endl;
}

void selection_homework8()
{
    int start, end;
    std::vector<Interval> v(2);
    for (int i = 0; i < 2; i++)
    {
        std::cin >> start >> end;
        Interval i_(start, end);
        v[i] = i_;
    }
    sort(v.begin(), v.end());
    if (v[0].has(v[1].start))
    {
        Interval intersection(v[1].start, v[0].end);
        std::cout << intersection << std::endl;
        return;
    }
    std::cout << -1 << std::endl;
    return;
}