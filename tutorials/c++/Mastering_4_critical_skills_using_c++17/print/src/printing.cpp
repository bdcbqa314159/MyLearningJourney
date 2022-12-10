#include "print_lib"
#include <iostream>

void printing()
{
    std::cout << "My name is Bernardo" << std::endl;
    std::cout << "I was born on earth.\n";
    std::cout << "And that is it." << std::endl;
}

void homework_1()
{
    using namespace std;
    cout << "\n\nGuess the "
         << "output\n---\n";

    cout << 10 + 20 - 5 << endl;
    cout << "14/2"
         << "\n";
    cout << 17 - 10 << "\n";
    cout << "endl";
    cout << "\nPractice makes perfect";

    // cout<<"The way to get started is to quit talking and begin doing";

    return;

    cout << "\n\nBye\n\n";
}

void Draw_1(int lines)
{
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j <= i; j++)
            std::cout << "* ";
        std::cout << std::endl;
    }
}

void Draw_2(int lines)
{
    int elements_to_be_printed = 2 * lines - 1;
    for (int i = 0; i < lines; i++)
    {
        int stars = 2 * i + 1;
        int spaces = elements_to_be_printed - stars;
        for (int j = 0; j < spaces / 2; j++)
            std::cout << "  ";
        for (int k = 0; k < stars; k++)
            std::cout << "* ";
        for (int j = 0; j < spaces / 2; j++)
            std::cout << " ";
        std::cout << std::endl;
    }
}

void Draw_3(int lines)
{
    int counter = 0;
    int stars = 2 * counter + 1;
    int spaces = lines - stars;
    bool up = true;

    while (counter < lines)
    {
        for (int j = 0; j < spaces / 2; j++)
            std::cout << "  ";
        for (int k = 0; k < stars; k++)
            std::cout << "* ";
        for (int j = 0; j < spaces / 2; j++)
            std::cout << " ";
        std::cout << std::endl;

        if (up)
            stars += 2;
        else
            stars -= 2;
        if (stars == lines)
            up = false;

        spaces = lines - stars;
        counter++;
    }
}

void homework_2()
{
    Draw_1();
    std::cout << std::endl;
    Draw_2();
    std::cout << std::endl;
    Draw_3();
}