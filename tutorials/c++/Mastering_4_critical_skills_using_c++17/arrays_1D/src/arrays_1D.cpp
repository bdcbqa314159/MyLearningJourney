#include "arrays_1D_lib"
#include <iostream>
#include <string>
#include <vector>

void testingArrays_1D()
{
    std::cout << "From the arrays_1D library." << std::endl;
}

bool isIncreasing(std::vector<int> &data)
{
    int n = data.size();
    if (n == 0)
        return false;
    else if (n == 1)
        return true;

    for (int i = 1; i < n; i++)
    {
        if (data[i] < data[i - 1])
            return false;
    }
    return true;
}

void homework_1()
{
    std::vector<int> a = {1, 2, 2, 5};
    for (int x : a)
        std::cout << x << " ";
    std::cout << std::endl;
    bool ans = isIncreasing(a);
    if (ans)
        std::cout << " is increasing" << std::endl;
    else
        std::cout << " is not increasing" << std::endl;

    std::vector<int> b = {1, 0, 7, 8, 9};
    for (int x : b)
        std::cout << x << " ";
    std::cout << std::endl;
    ans = isIncreasing(b);
    if (ans)
        std::cout << " is increasing" << std::endl;
    else
        std::cout << " is not increasing" << std::endl;
}

void replaceMinMax(std::vector<int> &data)
{
    std::vector<int> temp = data;
    std::sort(temp.begin(), temp.end());
    int min = temp[0];
    int max = temp[temp.size() - 1];

    for (int i = 0; i < data.size(); i++)
    {
        if (data[i] == min)
            data[i] = max;
        else if (data[i] == max)
            data[i] = min;
    }
    return;
}

void homework_2()
{
    std::vector<int> a = {4, 1, 3, 10, 8, 10, 10};

    for (int x : a)
        std::cout << x << " ";
    std::cout << std::endl;
    replaceMinMax(a);
    for (int x : a)
        std::cout << x << " ";
    std::cout << std::endl;
}

std::vector<int> withoutRepitition(std::vector<int> &data)
{
    std::vector<int> ans;
    ans.push_back(data[0]);
    for (int i = 1; i < data.size(); i++)
    {
        if (data[i] == data[i - 1])
            continue;
        else
            ans.push_back(data[i]);
    }
    return ans;
}

void homework_3()
{
    std::vector<int> a = {1, 1, 2, 2, 2, 5, 6, 6, 7, 8, 9, 9};

    for (int x : a)
        std::cout << x << " ";
    std::cout << std::endl;
    std::vector<int> b = withoutRepitition(a);
    for (int x : b)
        std::cout << x << " ";
    std::cout << std::endl;
}

bool is_Palindrome(std::vector<int> &data)
{
    int n = data.size();
    if (n == 0)
        return false;
    if (n == 1)
        return true;

    int l = 0, r = n - 1;
    while (l < r)
    {
        if (data[l] != data[r])
            return false;
        l++;
        r--;
    }
    return true;
}

void homework_4()
{
    std::vector<int> a = {1, 2, 3, 2, 1};

    for (int x : a)
        std::cout << x << " ";
    std::cout << std::endl;
    bool ans = is_Palindrome(a);
    if (ans)
        std::cout << "is a palindrome" << std::endl;
    else
        std::cout << "is not a palindrome" << std::endl;
}

int minPair(std::vector<int> &data)
{
    int n = data.size();
    int ans = INT_MAX;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int value_of_interest = data[i] + data[j] + j - i;
            if (ans >= value_of_interest)
                ans = value_of_interest;
        }
    }
    return ans;
}

void homework_5()
{
    std::vector<int> a = {20, 1, 9, 4};

    for (int x : a)
        std::cout << x << " ";
    std::cout << std::endl;
    int ans = minPair(a);
    std::cout << "The minimum value is " << ans << std::endl;
}