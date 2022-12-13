#include "operators_lib"
#include <iostream>

void testingOperator()
{
    std::cout << "Say hi" << std::endl;
}

void operatorsHomework_1()
{
    int a = 0, b = 1;
    /*
    0
    2
    a(5)
    b(12)
    6 12

    b(6)
    a(9)

    9
    2


    */

    std::cout << a++ << "\n";
    std::cout << ++a << "\n";
    a += 2 * b + 1;
    b = ++a * 2;
    std::cout << a << " " << b << "\n";

    b = a;
    a = 12 + a / 3 / 2 - 2 * 2;
    std::cout << a << "\n";

    a = b;
    a = ((12 + a) / 3 / 2 - 2) * 2;
    std::cout << a << "\n";
    std::cout << "*********" << std::endl;
}

void operatorsHomework_2()
{
    // 8
    int a = 1, b = 1, c;

    std::cout << (c = a + b, a = b, b = c,
                  c = a + b, a = b, b = c,
                  c = a + b, a = b, b = c,
                  c = a + b, a = b, b = c)
              << std::endl;
    std::cout << "*********" << std::endl;
}

void operatorsHomework_3()
{
    /*
    a(105)
    105
    35
    5

    1

    20
    22
    22
    20

    31?
    11
    22

    */
    int a = 210;

    a /= 2;
    std::cout << a << "\n";

    std::cout << (a /= 3) << "\n";
    std::cout << (a /= 5) << "\n";
    std::cout << (a /= 7) << "\n";

    std::cout << (2 + 3) * (5 - (-3)) / 5 / 8 << "\n";

    a = 10;
    std::cout << a++ + 10 << "\n";
    std::cout << ++a + 10 << "\n";
    std::cout << a-- + 10 << "\n";
    std::cout << --a + 10 << "\n";

    int b = 20;
    std::cout << a++ + ++b << "\n"; // Don't code this way

    std::cout << a << "\n";
    ++a += 10; // Don't code this way
    std::cout << a << "\n";
}

void operatorsHomework_4()
{
    int a = 10, b = 20, c = 30, d = 40;

    std::cout << (a + b == c) << "\n";
    std::cout << (a + b + c >= 2 * d) << "\n";

    std::cout << (a > 5 || d < 30) << "\n";
    std::cout << (a > 5 && d < 30) << "\n";
    std::cout << (a <= b && b <= c) << "\n";

    std::cout << (a > 5 && d < 30 || c - b == 10) << "\n";
    std::cout << (a <= b && b <= c && c <= d) << "\n";

    std::cout << (a > 5 && d < 30 || c > d || d % 2 == 0) << "\n";
    std::cout << (a > 5 && d < 30 || c > d && d % 2 == 0) << "\n";

    std::cout << (a == 10 || b != 20 && c != 30 || d != 40) << "\n";
    std::cout << ((a == 10 || b != 20) && c != 30 || d != 40) << "\n";

    /*
    1
    0
    1
    0
    1
    1
    1
    1
    0
    1
    0
    */
}

void operatorsHomework_5()
{
    int nb, ng, nt;
    std::cout << std::endl;
    std::cin >> nb >> ng >> nt;

    std::cout << (nb > 25) << std::endl;
    std::cout << (ng <= 30) << std::endl;
    std::cout << ((nb > 20 && nt > 2) || (ng > 30 && nt > 4)) << std::endl;
    std::cout << ((nb < 60) || (ng < 70)) << std::endl;
    std::cout << (!(nb >= 60) && !(ng < 70)) << std::endl;
    std::cout << ((nb + 10) == ng) << std::endl;
    std::cout << ((nb - ng) > 10 || (nt > 5)) << std::endl;
    std::cout << ((nb == (10 + ng)) || (ng == (15 + nb))) << std::endl;
}

void operatorsHomework_6()
{
    std::cout << "F T T T T T T T" << std::endl;
}

void operatorsHomework_7()
{
    int a1, a2, a3, a4, a5;
    std::cin >> a1 >> a2 >> a3 >> a4 >> a5;
    double average = 0.2 * (a1 + a2 + a3 + a4 + a5);
    double x = static_cast<double>(a1 + a2 + a3) / (a4 + a5);
    double y = static_cast<double>(a1 + a2 + a3) / 3;
    double z = static_cast<double>(a4 + a5) / 2;
    double t = y / z;

    std::cout << average << " " << x << " " << t << std::endl;
}

void operatorsHomework_8()
{
    int a, b;
    std::cin >> a >> b;
    std::cout << static_cast<double>(a) / b - a / b << std::endl;
}

void operatorsHomework_9()
{
    int a, b;
    std::cin >> a >> b;
    std::cout << a - (a / b) * 12 << std::endl;
}

void operatorsHomework_10()
{
    int num;
    std::cin >> num;

    bool is_even1 = (num % 2 == 0);
    bool is_even2 = (2 * (num / 2) == num);
    bool is_even3 = (num % 10 == 0) || (num % 10 == 2) || (num % 10 == 4) || (num % 10 == 6) || (num % 10 == 8);

    std::cout << is_even1 << " " << is_even2 << " " << is_even3 << std::endl;
}

void operatorsHomework_11()
{
    int num;
    std::cin >> num;

    int answer = 0;
    int i = 0;
    while (i < 3)
    {
        answer += num % 10;
        num /= 10;
        i++;
    }
    std::cout << answer << std::endl;
}

void operatorsHomework_12()
{
    int num;
    std::cin >> num;

    int answer = 0;
    int i = 0;
    while (i < 3)
    {
        num /= 10;
        i++;
    }
    answer = num % 10;
    std::cout << answer << std::endl;
}

void operatorsHomework_13()
{
    int num;
    std::cin >> num;
    std::cout << 100 * (num % 2 == 0) + 7 * (num % 2 == 1) << std::endl;
}

void operatorsHomework_14()
{
    int num;
    std::cin >> num;

    int years{}, months{}, days{};

    years = num / 360;
    num %= 360;
    months = num / 30;
    num %= 30;
    days = num;
    std::cout << years << " " << months << " " << days << std::endl;
}