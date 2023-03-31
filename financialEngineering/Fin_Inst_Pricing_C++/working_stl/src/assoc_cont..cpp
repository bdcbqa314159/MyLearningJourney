#include "working_stl_lib"

using namespace std;

void working_maps()
{
    map<string, double> option_;
    option_["r"] = 0.1;
    option_["sig"] = 0.28;
    option_["K"] = 19.0;
    option_["T"] = 0.75;
    option_["S"] = 19.0;

    cout << "Size of map: " << option_.size() << endl;

    typename map<string, double>::iterator i = option_.begin();

    while (i != option_.end())
    {
        cout << "Element pair [" << (*i).first << ", " << (*i).second << "]" << endl;
        i++;
    }
    return;
}

void working_sets()
{
    set<string> first;

    first.insert("r");
    first.insert("T");
    first.insert("sigma");

    cout << "First size: " << first.size() << endl;

    set<string> second(first);

    second.insert("r");
    second.insert("K");
    second.insert("S");
    second.insert("b");

    cout << "Second size: " << second.size() << endl;

    if (first == second)
        cout << "sets have same elements" << endl;

    else
        cout << "sets are different" << endl;

    swap(first, second);

    set<string> third = first;

    print(first, "First set");
    print(second, "Second set");
    print(third, "Third set");

    set<string> execOption(first);
    execOption.insert("lambda");

    print(execOption, "An executive option");
}

void working_vectors()
{
    vector<int> v1(4, 2);
    vector<int> v2(5, 3);

    ostream_iterator<int> iter(cout, " ");

    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), iter);
    cout << endl;
}
