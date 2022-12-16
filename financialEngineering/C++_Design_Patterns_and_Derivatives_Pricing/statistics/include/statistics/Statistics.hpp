#ifndef STATISTICS_H
#define STATISTICS_H

#include "wrappers_lib"
#include <vector>
#include <memory>

class Statistics
{
public:
    Statistics() {}
    virtual void dumpOneResult(double result) = 0;
    virtual std::vector<std::vector<double>> getResultSoFar() const = 0;
    virtual std::unique_ptr<Statistics> clone() const = 0;
    virtual ~Statistics() {}

private:
};

class StatisticsMean : public Statistics
{
public:
    StatisticsMean();
    virtual void dumpOneResult(double result) override;
    virtual std::vector<std::vector<double>> getResultSoFar() const override;
    virtual std::unique_ptr<Statistics> clone() const override;
    ~StatisticsMean(){};

private:
    double runningSum;
    unsigned long pathsDone;
};

class ConvergenceTable : public Statistics
{
public:
    ConvergenceTable(const Wrapper<Statistics> &inner);
    virtual std::unique_ptr<Statistics> clone() const override;
    virtual void dumpOneResult(double result) override;
    virtual std::vector<std::vector<double>> getResultSoFar() const override;

private:
    Wrapper<Statistics> inner;
    std::vector<std::vector<double>> resultsSoFar;
    unsigned long stoppingPoint;
    unsigned long pathsDone;
};

#endif