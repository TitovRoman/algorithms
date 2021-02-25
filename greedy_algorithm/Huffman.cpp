#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>
#include <cmath>
#include <map>
#include <deque>

using namespace std;

template<class T>
class binary_tree{
private:
    struct Node{
        Node(T obj, shared_ptr<Node> left_ = nullptr, shared_ptr<Node> right_ = nullptr) : left(left_), right(right_), value(obj) {}
        shared_ptr<Node> left;
        shared_ptr<Node> right;
        T value;
    };

    shared_ptr<Node> head;
public:
    binary_tree() = default;
    binary_tree(T obj) : head(make_shared<Node>(obj, nullptr, nullptr)){}
    binary_tree(binary_tree left, binary_tree right, T obj) : head(make_shared<Node>(obj, left.head, right.head)){}

    T getValue(){
        return head->value;
    }

    map<T, string> get_huffman(){
        map<T, string> result;  // 'a' : "001" ...
        deque<pair<shared_ptr<Node>, string>> deq;  //string - code (0101...) 0 - left; 1 - rigth
        deq.push_back(make_pair(head, ""));
        while(!deq.empty()){
            auto obj = deq.front();
            deq.pop_front();
            if(obj.first->left == nullptr){
                result[obj.first->value] = obj.second;
            } else {
                deq.push_front(make_pair(obj.first->left, obj.second+"0"));
                if(obj.first->right != nullptr){
                    deq.push_front(make_pair(obj.first->right, obj.second+"1"));
                }
            }
        }
        if(result.size() == 1){
            result.begin()->second = "0";
        }
        return result;
    }


};

template<class T, size_t d = 2, class Fun = std::less<int>>
class priority_queue{
private:
    using Obj = pair<T, int>;
    vector<Obj> bin_tree;
    Fun fun;

    vector<int> get_childs(int ind) const{
        vector<int> result;
        for(int i=(ind-1)*d+2, min_ind = min(bin_tree.size(), ind*d+2); i < min_ind; ++i){
            result.push_back(i);
        }
        return result;
    }

    int get_parent(int ind) const{
        return ceil((ind - 1.0) / d);
    }

    int get_priority(int index){
        return bin_tree[index].second;
    }

    void sift_up(int ind){
        if(ind < 2) return;

        int parent = get_parent(ind);
        while(ind != 1 && fun(get_priority(ind), get_priority(parent))){
            swap(bin_tree[ind], bin_tree[parent]);
            ind = parent;
            parent = get_parent(ind);
        }
    }

    int get_min_child(int ind){
        vector<int> childs = get_childs(ind);
        if( childs.size() == 0) return -1;
        auto min_child = childs[0];
        for(int i = 1; i < childs.size(); ++i){
            if(fun(get_priority(childs[i]), get_priority(min_child))){
                min_child = childs[i];
            }
        }
        return min_child;
    }

    void sift_down(int ind){
        for(int min_child_ind = get_min_child(ind);
                min_child_ind != -1 && !fun(get_priority(ind), get_priority(min_child_ind));
                min_child_ind = get_min_child(ind))
        {
            swap(bin_tree[min_child_ind], bin_tree[ind]);
            ind = min_child_ind;
        }
    }
public:
    priority_queue(const Fun& fun = {}) : bin_tree(1), fun(fun) {}

    void Insert(T obj, int priority){
        bin_tree.push_back(make_pair(obj, priority));
        sift_up(bin_tree.size()-1);
    }

    Obj GetObj(int ind) const{
        return bin_tree[ind];
    }

    Obj GetHead() const{
        return bin_tree[1];
    }

    Obj ExtractHead(){
        Obj head_obj = GetHead();
        bin_tree[1] = bin_tree.back();
        bin_tree.pop_back();
        sift_down(1);
        return head_obj;
    }

    void print(){
        for(int i = 1; i < bin_tree.size(); ++i){
            auto obj = bin_tree[i];
            cout << "( " << obj.first << ", " << obj.second << " ), ";
        }
        cout << endl;
    }

    size_t size(){
        return bin_tree.size() - 1;
    }

};

#include <fstream>

void fun(){
    priority_queue<int, 2, std::greater<int>> test;
    ifstream cin("D:\\moto\\Dropbox\\PROG\\algorithms\\greedy_algorithm\\test.txt");
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i){
        string cmd;
        cin >> cmd;
        if(cmd == "Insert"){            
            int num;
            cin >> num;
            test.Insert(num, num);
        } else if(cmd == "ExtractMax"){
            cout << test.ExtractHead().first << endl;
        }
    }
}

map<char, int> get_frequency(string str){
    map<char, int> result;
    for(int i = 0; i < str.size(); i++){
        result[str[i]]++;
    }
    return result;
}



int main(){
    string str;
    cin >> str;
    auto frequency = get_frequency(str);

    priority_queue<binary_tree<char>> queue;
    for(auto obj : frequency){
        
        queue.Insert(obj.first, obj.second);
    }
    int n = frequency.size();
    int total_cost = 0;
    for(int k = n+1; k < 2*n; ++k){
        auto first_element = queue.ExtractHead();
        auto second_element = queue.ExtractHead();
        total_cost += first_element.second + second_element.second;
        queue.Insert(binary_tree<char>(first_element.first, second_element.first, '\0'), first_element.second + second_element.second);
    }

    binary_tree<char> huffman_tree = queue.GetHead().first;
    if( n == 1) total_cost += queue.GetHead().second;
    auto result = huffman_tree.get_huffman();

    cout << result.size() << " " << total_cost << endl;
    for(auto obj : result){
        cout << obj.first << ": " << obj.second<< endl;
    }
    for(int i = 0; i < str.size(); ++i){
        cout << result[str[i]];
    }



    int ww; std::cin >> ww;
}