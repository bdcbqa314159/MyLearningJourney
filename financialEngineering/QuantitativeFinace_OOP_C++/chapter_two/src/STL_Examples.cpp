#include "chapter_two_lib"

#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

void workingWithVectors(){
    vector<int> my_vector(10);

    for (int i = 1; i<my_vector.size(); i++) my_vector[i-1] = i;

    for (int i = 0; i<my_vector.size(); i++) cout<<my_vector[i]<<' '<<flush;

    cout<<endl;

    vector<int>::iterator my_iter;

    for (my_iter = my_vector.begin(); my_iter!=my_vector.end(); my_iter++)
        cout<<*my_iter<<' '<<flush;
    cout<<endl;

    int j = 35123;
    my_iter = my_vector.begin();

    for (int i = 0; i<2; i++) my_iter++;
    my_vector.insert(my_iter,j);

    for (my_iter = my_vector.begin(); my_iter!=my_vector.end(); my_iter++)
        cout<<*my_iter<<' '<<flush;
    cout<<endl;

    my_iter = my_vector.begin();

    for (int i = 0; i<4; i++) my_iter++;
    my_vector.erase(my_iter);

    for (my_iter = my_vector.begin(); my_iter!=my_vector.end(); my_iter++)
        cout<<*my_iter<<' '<<flush;
    cout<<endl;
}

void workingWithMaps(){
    map<string, double> my_map;

    my_map["Mended Hill Properties"] = 25.2;
    my_map["Yoyodyne Industries"] = 105.1;
    my_map["Peak Petroleum Corporation"] = 803.5;
    my_map["Titanic Shipping Ltd."] = 3.15;
    
    cout << "The share price of Yoyodyne Industries is " << my_map["Yoyodyne Industries"] << endl;
    
    map<string,double>::iterator my_iter;
    for (my_iter=my_map.begin();my_iter!=my_map.end();my_iter++)
        cout << "The share price of " << my_iter->first << " is " << my_iter->second << endl;
}

void workingWithLists(){
 
    
    list<int> my_list;
    
    for (int i=1;i<=10;i++) my_list.push_back(i);
    
    list<int>::iterator my_iter;
    
    for (my_iter=my_list.begin();my_iter!=my_list.end();my_iter++) 
        cout << *my_iter << ' ' << flush;
    cout << endl;

    int j = 34677
    ;
    my_iter=my_list.begin();
    for (int i=0;i<2;i++) my_iter++;
    my_list.insert(my_iter,j);
    
    for (my_iter=my_list.begin();my_iter!=my_list.end();my_iter++) 
        cout << *my_iter << ' ' << flush;
    cout << endl;

    my_iter=my_list.begin();
    for (int i=0;i<4;i++) my_iter++;
    my_list.erase(my_iter);

    for (my_iter=my_list.begin();my_iter!=my_list.end();my_iter++) 
        cout << *my_iter << ' ' << flush;
    cout << endl;
}

void workingWithForEach(){

    list<int> my_list;

    for (int i=1;i<=10;i++) my_list.push_back(i);
    
    my_list.push_back(5);
    my_list.push_back(3);
    
    number_of_occurences<int> f;
    
    number_of_occurences<int> g = for_each(my_list.begin(),my_list.end(),f);
    map<int,int>& occurences = g;
   
    map<int,int>::iterator my_iter;
    for (my_iter=occurences.begin();my_iter!=occurences.end();my_iter++)
        cout << "The integer " << my_iter->first << " occurs " << my_iter->second << " times in the list." << endl;

}
