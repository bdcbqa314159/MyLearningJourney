#ifndef TESTING_H
#define TESTING_H

#include <iostream>
#include <sstream>
#include <string>

bool isDebugEnabled();

void setDebugEnabled(bool enabled);

#define INFO(A)                                           \
    {                                                     \
        std::cerr << "INFO:\n"                            \
                  << __FILE__ << ":" << __LINE__ << ":\n" \
                  << A << "\n";                           \
    }

#define TEST(f)                                                       \
    do                                                                \
    {                                                                 \
        std::cerr << "Calling " << #f << "()\n";                      \
        try                                                           \
        {                                                             \
            f();                                                      \
        }                                                             \
        catch (const std::runtime_error &error)                       \
        {                                                             \
            std::cerr << "\n";                                        \
            std::cerr << "******* " << #f << "() FAILED. ********\n"; \
            std::cerr << "\n";                                        \
            std::cerr << error.what() << "\n";                        \
            exit(1);                                                  \
        }                                                             \
        std::cerr << "" << #f << "() passed.\n";                      \
        std::cerr << "\n";                                            \
    } while (false)

// on windows we define debug mode to be when _DEBUG is set
#ifdef _DEBUG
#define DEBUG_MODE 1
#endif

// on unix we define debug mode to be when _GLIBCXX is set
#ifdef _GLIBCXX_DEBUG
#define DEBUG_MODE 1
#endif

#ifdef DEBUG
#define DEBUG_MODE 1
#endif

#define DEBUG_PRINT(A)                                        \
    {                                                         \
        if (isDebugEnabled())                                 \
        {                                                     \
            std::cerr << "DEBUG:\n"                           \
                      << __FILE__ << ":" << __LINE__ << ":\n" \
                      << A << "\n";                           \
        }                                                     \
    }

#define ASSERT(c)                                               \
    do                                                          \
    {                                                           \
        if (!(c))                                               \
        {                                                       \
            std::stringstream testing_ss_;                      \
            testing_ss_ << "ASSERTION FAILED \n";               \
            testing_ss_ << __FILE__ << ":" << __LINE__ << ":\n" \
                        << #c;                                  \
            std::cerr << testing_ss_.str();                     \
            throw std::runtime_error(testing_ss_.str());        \
        }                                                       \
    } while (false)

#define ASSERT_APPROX_EQUAL(x, y, tolerance)                     \
    do                                                           \
    {                                                            \
        if (!(abs((x) - (y)) <= (tolerance)))                    \
        {                                                        \
            std::stringstream testing_ss_;                       \
            testing_ss_ << "ASSERTION FAILED \n";                \
            testing_ss_ << "Expected " << x << "\n";             \
            testing_ss_ << "Actual " << y << "\n";               \
            testing_ss_ << "tolerance " << tolerance << "\n";    \
            testing_ss_ << "|x-y| " << (double)(x - y) << "\n";  \
            testing_ss_ << __FILE__ << ":" << __LINE__ << ":\n"; \
            std::cerr << testing_ss_.str();                      \
            throw std::runtime_error(testing_ss_.str());         \
        }                                                        \
    } while (false)

#endif