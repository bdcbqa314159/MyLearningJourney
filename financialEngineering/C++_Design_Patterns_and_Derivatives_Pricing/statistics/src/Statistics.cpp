#include "statistics_lib"

StatisticsMean::StatisticsMean() : runningSum(0), pathsDone(0)
{
}

void StatisticsMean::dumpOneResult(double result)
{
    pathsDone++;
    runningSum += result;
}

std::vector<std::vector<double>> StatisticsMean::getResultSoFar() const
{
    std::vector<std::vector<double>> results(1);

    results[0].resize(1);
    results[0][0] = runningSum / pathsDone;

    return results;
}

std::unique_ptr<Statistics> StatisticsMean::clone() const
{
    return std::make_unique<StatisticsMean>(*this);
}

ConvergenceTable::ConvergenceTable(const Wrapper<Statistics> &inner) : inner(inner)
{
    stoppingPoint = 2;
    pathsDone = 0;
}

std::unique_ptr<Statistics> ConvergenceTable::clone() const
{
    return std::make_unique<ConvergenceTable>(*this);
}

void ConvergenceTable::dumpOneResult(double result)
{
    (inner.operator->())->dumpOneResult(result);
    ++pathsDone;

    if (pathsDone == stoppingPoint)
    {
        stoppingPoint *= 2;
        std::vector<std::vector<double>> thisResult(inner->getResultSoFar());
        for (unsigned long i = 0; i < thisResult.size(); i++)
        {
            thisResult[i].push_back(pathsDone);
            resultsSoFar.push_back(thisResult[i]);
        }
    }
    return;
}

std::vector<std::vector<double>> ConvergenceTable::getResultSoFar() const
{
    std::vector<std::vector<double>> finalResult(resultsSoFar);
    if (pathsDone * 2 != stoppingPoint)
    {
        std::vector<std::vector<double>> thisResult(inner->getResultSoFar());
        for (unsigned long i = 0; i < thisResult.size(); i++)
        {
            thisResult[i].push_back(pathsDone);
            finalResult.push_back(thisResult[i]);
        }
    }
    return finalResult;
}
