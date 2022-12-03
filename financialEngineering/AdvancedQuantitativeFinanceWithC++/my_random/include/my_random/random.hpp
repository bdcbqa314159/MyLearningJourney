#ifndef RANDOM_H
#define RANDOM_H

class SampleBoxMuller
{

public:
    double operator()();

private:
    double result{}, x{}, y{}, xysquare{};
};

#endif