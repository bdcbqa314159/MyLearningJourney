#include "working_stl_lib"

using namespace std;

vector<double> make_vector(int size)
{
    vector<double> result(size);
    for (int i = 0; i < size; ++i)
    {
        result[i] = static_cast<double>(i + 1);
    }
    return result;
}

void print(const vector<double> &v)
{
    cout << "size of vector is " << v.size() << endl;

    vector<double>::const_iterator i;
    for (i = v.begin(); i != v.end(); ++i)
        cout << *i << " ";
    cout << endl;
}

void first_test_iterators()
{
    vector<double> vector1 = make_vector(5);
    vector<double>::iterator bi;

    cout << "Traverse forward" << endl;
    bi = vector1.begin();
    while (bi != vector1.end())
        cout << (*bi++) << " ";
    cout << endl
         << endl;

    cout << "Traverse backward" << endl;
    bi = vector1.end();
    do
    {
        cout << (*--bi) << " ";
    } while (bi != vector1.begin());
    cout << endl
         << endl;

    cout << "Traverse random" << endl;
    bi = vector1.begin();
    cout << *bi << " ";
    cout << *(bi += 3) << " ";
    cout << *(bi -= 1) << " ";
    cout << bi[-1] << " ";
    cout << bi[1] << endl
         << endl;

    vector<double>::reverse_iterator ri;

    cout << "Traverse reverse forward" << endl;
    ri = vector1.rbegin();
    while (ri != vector1.rend())
        cout << (*ri++) << " ";
    cout << endl
         << endl;

    cout << "Traverse reverse backward" << endl;
    ri = vector1.rend();
    do
    {
        cout << (*--ri) << " ";
    } while (ri != vector1.rbegin());
    cout << endl
         << endl;

    cout << "Traverse reverse random" << endl;
    cout << *ri << " ";
    cout << *(ri += 3) << " ";
    cout << *(ri -= 1) << " ";
    cout << ri[-1] << " ";
    cout << ri[1] << endl
         << endl;

    cout << "Change first element with mutable iterator" << endl;
    bi = vector1.begin();
    *bi = double(99);
    print(vector1);

    cout << "Change first element with const iterator" << endl;
    vector<double>::const_iterator ci;
    ci = vector1.end();
    ci--;
    cout << *ci << endl;

    return;
}

Point::Point() : xc(0.), yc(0.) {}

Point::Point(double xcs, double ycs) : xc(xcs), yc(ycs) {}

Point::Point(const Point &source) : xc(source.xc), yc(source.yc) {}

ostream &operator<<(ostream &os, const Point &p)
{
    os << "Point: (" << p.xc << ", " << p.yc << ")";
    return os;
}

double Point::distance(const Point &p)
{
    double dx = xc - p.xc;
    double dy = xc - p.yc;

    return sqrt(dx * dx + dy * dy);
}

Point &Point::operator=(const Point &source)
{
    if (this == &source)
        return *this;

    xc = source.xc;
    yc = source.yc;

    return *this;
}

vector<Point> make_vector_point(int size)
{
    vector<Point> result(size);
    for (int i = 0; i < size; i++)
    {
        double j = static_cast<double>(i);
        result[i] = Point(j, j);
    }
    return result;
}

void print(const vector<Point> &v)
{
    cout << "Size of the vector is " << v.size() << endl;
    vector<Point>::const_iterator i;

    for (i = v.begin(); i != v.end(); i++)
    {
        cout << *i << " ";
    }
    cout << endl
         << endl;
}

void second_test_iterators()
{
    vector<Point> vector1 = make_vector_point(5);
    vector<Point>::iterator bi;

    cout << "Traverse forward" << endl;
    bi = vector1.begin();
    while (bi != vector1.end())
        cout << (*bi++) << " ";
    cout << endl
         << endl;

    cout << "Traverse backward" << endl;
    bi = vector1.end();
    do
    {
        cout << (*--bi) << " ";
    } while (bi != vector1.begin());
    cout << endl
         << endl;

    cout << "Traverse random" << endl;
    bi = vector1.begin();
    cout << *bi << " ";
    cout << *(bi += 3) << " ";
    cout << *(bi -= 1) << " ";
    cout << bi[-1] << " ";
    cout << bi[1] << endl
         << endl;

    vector<Point>::reverse_iterator ri;

    cout << "Traverse reverse forward" << endl;
    ri = vector1.rbegin();
    while (ri != vector1.rend())
        cout << (*ri++) << " ";
    cout << endl
         << endl;

    cout << "Traverse reverse backward" << endl;
    ri = vector1.rend();
    do
    {
        cout << (*--ri) << " ";
    } while (ri != vector1.rbegin());
    cout << endl
         << endl;

    cout << "Traverse reverse random" << endl;
    cout << *ri << " ";
    cout << *(ri += 3) << " ";
    cout << *(ri -= 1) << " ";
    cout << ri[-1] << " ";
    cout << ri[1] << endl
         << endl;

    cout << "Change first element with mutable iterator" << endl;
    bi = vector1.begin();
    *bi = Point(99, 99);
    print(vector1);

    cout << "Change first element with const iterator" << endl;
    vector<Point>::const_iterator ci;
    ci = vector1.end();
    ci--;
    cout << *ci << endl;

    return;
}

void print(const list<int> &my_list)
{
    cout << "Size of list is " << my_list.size() << endl;

    list<int>::const_iterator i;

    for (i = my_list.begin(); i != my_list.end(); ++i)
    {
        cout << *i << ", ";
    }
    cout << endl
         << endl;
}

void third_test_iterators()
{
    vector<int> a = {12, 3, 25, 7, 11, 213, 7, 123, 29, -31};

    vector<int>::iterator ptr = find(a.begin(), a.end(), 7);
    cout << "Value : " << *ptr << endl;

    list<int> list1;

    for (int i = 0; i < a.size(); i++)
        list1.push_back(a[i]);

    list<int>::iterator it = find(list1.begin(), list1.end(), 7);
    if (*it == 7 && *(++it) == 11)
        cout << "Ok, list element value is found" << endl;

    *it = 99;
    print(list1);

    /*
        cout << "Type some characters including an 'x' followed by at least one nonwhite-space character:" << flush;
        istream_iterator<char> in(cin);
        istream_iterator<char> eos;

        find(in, eos, 'x');
        cout << "first non-white character followin first 'x' was " << *(++in) << endl;
        */
}

void fourth_test_iterators()
{
    vector<int> a = {12, 3, 25, 7, 11, 213, 7, 123, 29, -31};
    vector<int> b(a.size());
    cout << "Vector a: " << endl;
    print(a);

    cout << "Vector b before : " << endl;
    print(b);

    copy(a.begin(), a.end(), b.begin());
    cout << "Vector b after copy from a : " << endl;
    print(b);

    list<int> list1;
    for (int i = 0; i < a.size(); i++)
        list1.push_back(a[i]);

    ostream_iterator<int> out(cout, "\n");
    copy(list1.begin(), list1.end(), out);

    ostream_iterator<int> out_1(cout, ",");
    copy(b.begin(), b.end(), out_1);
    cout << endl;
}

void fifth_test_iterators()
{
    vector<int> a = {12, 3, 25, 7, 11, 213, 7, 123, 29, -31};

    vector<int>::iterator ptr = find(a.begin(), a.end(), 7);
    cout << "Value : " << *ptr << endl;

    list<int> list1;

    for (int i = 0; i < a.size(); i++)
        list1.push_back(a[i]);

    print(list1);

    replace(list1.begin(), list1.end(), 7, 0);
    print(list1);

    return;
}

void sixth_test_iterators()
{
    vector<int> a = {12, 3, 25, 7, 11, 213, 7, 123, 29, -31};

    vector<int>::iterator ptr = find(a.begin(), a.end(), 7);
    cout << "Value : " << *ptr << endl;

    list<int> list1;

    for (int i = 0; i < a.size(); i++)
        list1.push_back(a[i]);

    print(list1);

    reverse(list1.begin(), list1.end());
    print(list1);

    list<int> list2;
    list<int>::iterator it1 = list2.begin();
    insert_iterator<list<int>> it2(list2, it1);
    reverse_copy(list1.begin(), list1.end(), it2);
    print(list2);

    vector<int> v1(100);
    for (int i = 0; i < 100; i++)
    {
        v1[i] = i;
    }

    v1[4] = 7;
    v1[6] = 3;

    bool found = binary_search(v1.begin(), v1.end(), 13);

    cout << "looking for 13 within the vector" << endl;

    if (found)
        cout << "ok, value found!" << endl;
    else
        cout << "not found, something rotten" << endl;

    vector<string> labels = {"aa", "bb", "ff", "ss", "zz"};

    found = binary_search(labels.begin(), labels.end(), "ff");

    cout << "looking for ff" << endl;
    if (found)
        cout << "ok, value found!" << endl;
    else
        cout << "not found, something rotten" << endl;

    found = binary_search(labels.begin(), labels.end(), "xx");

    cout << "looking for xx" << endl;
    if (found)
        cout << "ok, value found!" << endl;
    else
        cout << "not found, something rotten" << endl;

    /*
        istream_iterator<int> end_of_stream;
        partial_sum(istream_iterator<int>(cin), end_of_stream, ostream_iterator<int>(cout, "\n"));
    */

    return;
}

void seventh_test_iterators()
{

    int myarr[] = {1, 2, 3, 4};

    vector<int> myvec;
    back_insert_iterator<vector<int>> mybiter(myvec);
    print(myvec);

    copy(myarr, myarr + 4, mybiter);

    print(myvec);

    list<int> myList;
    front_insert_iterator<list<int>> myfiter(myList);
    print(myList);

    copy(myvec.begin(), myvec.end(), myfiter);

    print(myList);

    vector<int> vec2(myvec);
    print(vec2);

    list<int>::iterator list_it = myList.begin();
    ++list_it;

    insert_iterator<list<int>> my_iter(myList, list_it);

    print(myList);

    copy(vec2.begin(), vec2.end(), my_iter);

    print(myList);

    Point *parr = new Point[5];
    Point *ref = parr;

    raw_storage_iterator<Point *, Point> r(ref);

    for (int i = 0; i < 5; i++)
    {
        *r++ = Point(i, i);
    }

    for (int i = 0; i < 5; i++)
    {
        cout << *parr++ << endl;
    }

    cout << "Printing the reference" << endl;

    for (int i = 0; i < 5; i++)
    {
        cout << ref[i] << endl;
    }
    return;
}