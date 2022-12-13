#include "data_type_lib"
#include <iostream>

void someTest()
{
    std::cout << "Working with data types." << std::endl;
}

void homework_1()
{
    int a, b;
    std::cin >> a >> b;

    std::cout << a << " + " << b << " = " << a + b << std::endl;
    std::cout << a << " - " << b << " = " << a - b << std::endl;
    std::cout << a << " / " << b << " = " << a / b << std::endl;
    std::cout << a << " * " << b << " = " << a * b << std::endl;
}

std::ostream &operator<<(std::ostream &os, const student &obj)
{
    os << obj.name << " (with id " << obj.id << ") got grade : " << obj.grade << std::endl;
    return os;
}

void homework_2()
{
    std::string name;
    int id;
    double grade;
    std::cout << "What is student 1 name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "His id: ";
    std::cin >> id;
    std::cout << "His math exam grade: ";
    std::cin >> grade;
    std::cin.ignore();
    student stud1(name, id, grade);
    std::cout << "What is student 2 name: ";
    std::getline(std::cin, name);
    std::cout << "His id: ";
    std::cin >> id;
    std::cout << "His math exam grade: ";
    std::cin >> grade;
    student stud2(name, id, grade);

    double average = (stud1.grade + stud2.grade) * 0.5;

    std::cout << "Students grades in math" << std::endl;
    std::cout << stud1;
    std::cout << stud2;
    std::cout << "Average grade is " << average << std::endl;
}

void homework_3()
{
    int i{}, sum_odd{}, sum_even{};
    int number;
    while (i < 8)
    {
        std::cin >> number;
        if (i % 2 == 0)
            sum_odd += number;
        else
            sum_even += number;
        i++;
    }
    std::cout << sum_even << " " << sum_even << std::endl;
}

void easyProblems()
{
    homework_1();
    homework_2();
    homework_3();
}

void homework_4()
{
    int a = 0, b = 1;
    int c = a + b;
    int i = 0;
    while (i < 9)
    {

        std::cout << c << " ";
        a = b;
        b = c;
        c = a + b;

        i++;
    }
    std::cout << std::endl;
}

void homework_5()
{
    int num1, num2, num3;
    std::cin >> num1 >> num2;
    std::cout << "before:" << std::endl;
    std::cout << num1 << " " << num2 << std::endl;
    num3 = num1;
    num1 = num2;
    num2 = num3;
    std::cout << "after:" << std::endl;
    std::cout << num1 << " " << num2 << std::endl;
}

void mediumProblems()
{
    homework_4();
    homework_5();
}

void homework_6()
{
    int num1, num2, num3, num4;
    std::cin >> num1 >> num2 >> num3;
    std::cout << "before:" << std::endl;
    std::cout << num1 << " " << num2 << " " << num3 << std::endl;
    num4 = num1;
    num1 = num2;
    num2 = num3;
    num3 = num4;

    std::cout << "after:" << std::endl;
    std::cout << num1 << " " << num2 << " " << num3 << std::endl;
}

int helper(int A, int B)
{
    return (A + 1) * (A + 1) + (B == -1) * B * A * A - (B == 1) * B * (2 * A + 1);
}

void homework_7()
{
    int A, B;
    std::cin >> A >> B;
    int result = helper(A, B);
    std::cout << result << std::endl;
}

void homework_8()
{
    int N;
    std::cin >> N;
    std::cout << N * (N + 1) / 2 << std::endl;
}

void hardProblems()
{
    homework_6();
    homework_7();
    homework_8();
}
