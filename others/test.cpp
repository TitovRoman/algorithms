#include <iostream>
#include <vector>
#include <string_view>
using namespace std;

vector<string_view> fun(string_view str){
    vector<string_view> result;
    while (true)
    {
        
        size_t pos = str.find(' ');
        cout << pos  << " " << str.size()<< endl;
        result.push_back(str.substr(0, pos));
        if(pos != string_view::npos)
            str.remove_prefix(pos+1);
        else
        {
            break;
        }
        
    }
    
    return result;
}

int main(){
    //string a = ""
    string_view str1("qweqwe qqq qwasdf qw 123123 44423 ssqqwe  ");
    auto res = fun(str1);
    for(auto el : res){
        cout << el << endl;
    }

    cout << "QWE";
    int ww; cin >> ww;
}