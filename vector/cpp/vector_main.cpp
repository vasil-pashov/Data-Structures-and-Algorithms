#include <iostream>
//#include "../include/vector.hpp"
#include <string>
//#include <vector>

using namespace std;
//using namespace Vector;

class MyClass {
   private:
       string a; 
   public: 

       MyClass(){}
       MyClass(string str) : a{str}{}
       ~MyClass() {
           cout<<"Destruct: "<<a<<endl;
       }
       string get() {
           return a;
       }
};

class C {
    public:
        C(MyClass *sth) {ptr = sth;}
        C(const C &other) : ptr{other.ptr}{}
        MyClass& operator*() {
            return *ptr;
        }
        MyClass *operator->() {
            return ptr;
        }
    private:
        MyClass *ptr;
};

int main() {
 /*   vector<MyClass> vec, vec2;
    MyClass a("a"), b("b"), c("c"), d("d"), e("e");
    vec.push_back(a);
    vec.push_back(b);
    vec.push_back(c);
    vec.push_back(d);
    vec.push_back(e);
    vector<MyClass> vec1 = vec;
    vec2 = vec;*/
    MyClass s("s");
    MyClass *a = new MyClass("abc");
    C c(a);
    cout<<c->get();
    *c = s; 
    cout<<c->get();
    return 0;
}
