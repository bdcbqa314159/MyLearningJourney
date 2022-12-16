#include "loops_lib"
#include <iostream>
#include <string>
#include <vector>

void testingLoops()
{
    std::cout << "From the loop library." << std::endl;
}

void homework_1()
{
    int a, b;
    std::cin >> a >> b;

    while (a <= b)
    {
        std::cout << a << std::endl;
        a++;
    }
}

void homework_2()
{
    int a;
    char c;
    std::cin >> a >> c;
    int i = 0;
    while (i < a)
    {
        std::cout << c;
        i++;
    }
    std::cout << std::endl;
}

void homework_3()
{
    int n;
    std::cin >> n;

    int i = 1;
    while (i <= n)
    {
        int j = 0;
        while (j < i)
        {
            std::cout << '*';
            j++;
        }
        i++;

        std::cout << std::endl;
    }
}

void homework_4()
{
    int n;
    std::cin >> n;

    int i = n;
    while (i > 0)
    {
        int j = 0;

        while (j < i)
        {
            std::cout << '*';
            j++;
        }

        i--;
        std::cout << std::endl;
    }
}

void homework_5()
{
    int n{};
    std::cin >> n;
    int no_odds{};
    int no_evens{};
    if (n % 2 == 1)
    {
        no_odds = (n + 1) / 2;
        no_evens = n - no_odds;
    }
    else
    {
        no_evens = n / 2;
        no_odds = n - no_evens;
    }

    double mean_odds{}, mean_evens{};
    int i = 1;
    while (i <= n)
    {
        int x{};
        std::cin >> x;
        if (i % 2 == 1)
        {

            mean_odds += x;
        }
        else
        {
            mean_evens += x;
        }
        i++;
    }
    mean_odds /= no_odds;
    mean_evens /= no_evens;
    std::cout << mean_odds << " " << mean_evens << std::endl;
}

void homework_6()
{

    int N{5};
    // std::cin >> N;

    int elements_to_be_printed = 2 * N - 1;
    int i = 0;
    int stars = 1;
    bool up = true;
    while (i < 2 * N)
    {
        int spaces = elements_to_be_printed - stars;

        int j = 0;
        while (j < spaces / 2)
        {
            std::cout << ' ';
            j++;
        }
        int k = 0;
        while (k < stars)
        {
            std::cout << '*';
            k++;
        }

        j = 0;
        while (j < spaces / 2)
        {
            std::cout << ' ';
            j++;
        }
        std::cout << std::endl;

        if (up && stars != elements_to_be_printed)
            stars += 2;

        if (!up)
            stars -= 2;

        if (stars == elements_to_be_printed)
            up = false;

        i++;
    }
}

void homework_7()
{
    int N;
    std::cin >> N;
    int i = 0;
    while (i <= N)
    {

        if (i % 8 == 0)
            std::cout << i << " ";
        else if (i % 4 == 0 && i % 3 == 0)
            std::cout << i << " ";
        else
        {
        }

        i++;
    }
    std::cout << std::endl;
}

void homework_8()
{
    int N;
    std::cin >> N;
    int i = 0;
    int number = 3;
    while (i < N)
    {
        if (number % 3 == 0 && number % 4 != 0)
        {
            std::cout << number << " ";
            i++;
        }
        number += 3;
    }
    std::cout << std::endl;
}

void homework_9()
{
    int T;
    std::cin >> T;
    int i = 0;

    while (i < T)
    {

        int N;
        std::cin >> N;
        int min_to_print = INT_MAX;
        int j = 0;
        while (j < N)
        {

            int a;
            std::cin >> a;

            if (a < min_to_print)
                min_to_print = a;

            j++;
        }

        std::cout << min_to_print << " ";
        i++;
    }
    std::cout << std::endl;
}

void homework_10()
{
    int N;
    std::string word{};
    std::cin >> N;
    std::cin.ignore();
    std::vector<std::string> ans;

    int i = 0;
    while (i < N)
    {
        std::getline(std::cin, word);

        if (word.size() == 2)
        {
            if (word[0] == 'N' || word[0] == 'n' && word[1] == 'O' || word[1] == 'o')
                ans.push_back(word);

            else if (word[1] == 'N' || word[1] == 'n' && word[0] == 'O' || word[0] == 'o')
                ans.push_back(word);
        }

        i++;
    }

    for (auto w : ans)
        std::cout << w << " ";
    std::cout << std::endl;
}

void homework_11()
{
    int N{};
    std::cin >> N;
    int ans{};
    while (N > 0)
    {
        int res = N % 10;
        ans = 10 * ans + res;

        N /= 10;
    }

    std::cout << ans << " " << 3 * ans << std::endl;
}

void homework_12()
{
    int M, N;
    std::cin >> M >> N;
    int i = 1, j = 1;
    while (i <= M)
    {
        int j = 1;
        while (j <= N)
        {
            std::cout << i << " * " << j << " = " << i * j << std::endl;
            j++;
        }
        i++;
    }
}

void homework_13()
{
    int T;
    std::cin >> T;

    std::vector<int> ans;
    int i = 0;

    while (i < T)
    {
        int N;
        std::cin >> N;
        int j = 1;
        int sum = 0;
        while (j <= N)
        {
            int a;
            std::cin >> a;
            int k = 0;
            int product = 1;
            while (k < j)
            {
                product *= a;
                k++;
            }

            sum += product;
            j++;
        }
        ans.push_back(sum);

        i++;
    }

    for (auto x : ans)
        std::cout << x << " ";
    std::cout << std::endl;
}