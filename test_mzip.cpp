#include <map>
#include <iostream>
#include <assert.h>
#include <vector>

#include "mzip_view.h"
using std::cout;using std::endl;using std::cerr;
static std::string program_name="qtcreator";
#define sassert(val, cond)do{ \
    if(!(val cond)){ \
    cout<<program_name<< " " <<std::string(__FILE__)<< " "<<__LINE__<<" "<< std::string(__PRETTY_FUNCTION__)\
    <<" "<<#cond<<" is false: "<<val<<endl;\
    }} while(false)


const std::vector<int> c_as{1,2,3};
const std::vector<int> c_bs{-1,-2,-3};
void must_exists_0(std::vector<int> as, std::vector<int> bs){    for ([[maybe_unused]] auto [i, x, y] : zip(as, bs)) {x++;y--;   [[maybe_unused]] std::size_t k=i; }}
void must_exists_1(std::vector<int> as, std::vector<int>& bs){    for ([[maybe_unused]] auto [i, x, y] : zip(as, bs)) {x++;y--;  [[maybe_unused]] std::size_t k=i;}}
void must_exists_2(std::vector<int>& as, std::vector<int>& bs){    for ([[maybe_unused]] auto [i, x, y] : zip(as, bs)) {x++;y--; [[maybe_unused]] std::size_t k=i; }}
void must_exists_3(const std::vector<int> as, const std::vector<int> bs){    for ([[maybe_unused]] auto [i, x, y] : zip(as, bs)) {[[maybe_unused]]auto a=x; [[maybe_unused]]auto b=y;   [[maybe_unused]] std::size_t k=i;}}
void must_exists_4(const std::vector<int>& as, const std::vector<int>& bs){    for ([[maybe_unused]] auto [i, x, y] : zip(as, bs)) {[[maybe_unused]]auto a=x; [[maybe_unused]]auto b=y;    [[maybe_unused]] std::size_t k=i;}}
void must_exists_5(const std::vector<int> as, const std::vector<int>& bs){    for ([[maybe_unused]] auto [i, x, y] : zip(as, bs)) {[[maybe_unused]]auto a=x; [[maybe_unused]]auto b=y;    [[maybe_unused]] std::size_t k=i;}}
void must_exists_6(const std::vector<int>& as, std::vector<int>& bs){    for ([[maybe_unused]] auto [i, x, y] : zip(as, bs)) {[[maybe_unused]]auto a=x; [[maybe_unused]]auto b=y;    [[maybe_unused]] std::size_t k=i;}}

void must_exists_7(std::vector<int> as, const std::vector<int> bs){
    for([[maybe_unused]] auto [i, x, y]: zip(as, bs)){x=y; [[maybe_unused]] std::size_t k=i;   }
}
void must_exists_8(std::vector<int> as, const std::vector<int>& bs){
    for([[maybe_unused]] auto [i, x, y] : zip(as, bs)){x=y;  [[maybe_unused]] std::size_t k=i;  }
}
void must_exists_9(std::vector<int>& as, const std::vector<int> bs){
    for([[maybe_unused]] auto [i, x, y] : zip(as, bs)){x=y;  [[maybe_unused]] std::size_t k=i;  }
}
void must_exists_10(std::vector<int>& as, const std::vector<int>& bs){
    for([[maybe_unused]] auto [i, x, y] : zip(as, bs)){x=y;  [[maybe_unused]] std::size_t k=i;  }
}
void must_exists(){
    std::vector<int> a{1,2,3};
    std::vector<int> b{-1,-2,-3};
    must_exists_0(a,b);
    must_exists_1(a,b);
    must_exists_2(a,b);
    must_exists_3(a,b);
    must_exists_4(a,b);
    must_exists_5(a,b);
    must_exists_6(a,b);
    must_exists_7(a,b);
    must_exists_8(a,b);
    must_exists_9(a,b);
    must_exists_10(a,b);

    must_exists_0(std::vector<int>({1,2,3}),std::vector<int>({1,2,3}));
    for([[maybe_unused]] auto [i, x, y] : zip(c_as, c_bs)){[[maybe_unused]]auto a_=x; [[maybe_unused]]auto b_=y;  [[maybe_unused]] std::size_t k=i;  }
    for([[maybe_unused]] auto [i, x, y] : zip(std::vector<int>({1,2,3}),std::vector<int>({1,2,3}))){[[maybe_unused]]auto a_=x; [[maybe_unused]]auto b_=y;   [[maybe_unused]] std::size_t k=i; }

    must_exists_0(c_as,c_bs);
    must_exists_3(c_as,c_bs);
    must_exists_4(c_as,c_bs);
    must_exists_5(c_as,c_bs);
}

#if 0
void must_not_work0(std::vector<int> as, const std::vector<int> bs){
    for([[maybe_unused]] auto [i, x, y] : zip(as, bs)){y=x;    }
}
void must_not_work1(std::vector<int> as, const std::vector<int>& bs){
    for([[maybe_unused]] auto [i, x, y] : zip(as, bs)){y=x;    }
}
void must_not_work2(){
    std::vector<int> vs{1,2,3,4};
    std::map<int,std::string> mp;
    mp[1]="0";
    mp[2]="1";
    mp[3]="2";
    cout<<vs.begin()[2]<<endl;
    //cout<<mp.begin()[2]<<endl;
    [[maybe_unused]] auto z=zip(vs,mp);
    z[1];// should not work,
}
#endif

void test1(){

    std::vector<int> as{1,2,3};
    std::vector<int> bs{-1,-2,-3};

    for ([[maybe_unused]] auto [i, x, y] : zip{as, bs}) {
        x++;y--;[[maybe_unused]] std::size_t k=i;
    }
    // check that the result is good
    sassert(as[0],== 2);
    sassert(as[1],== 3);
    sassert(bs[0],==-2);
    sassert(bs[1],==-3);
}

void test2_(std::vector<int>& as,
            std::vector<int>& bs)
{

    for ([[maybe_unused]] auto [i, x, y] : zip(as, bs)) {         x++;y--; [[maybe_unused]]std::size_t k=i;   }
}
void test2(){

    std::vector<int> as{1,2,3};
    std::vector<int> bs{-1,-2,-3};
    test2_(as,bs);
    sassert(as[0],== 2);
    sassert(as[2],== 4);
    sassert(bs[0],==-2);
    sassert(bs[2],==-4);
}

void test3(){
    std::vector<int> as{1,2,3};
    std::vector<int> bs{-1,-2,-3};
    test2_(as,bs);
    sassert(as[0],== 2);
    sassert(as[2],== 4);
    sassert(bs[0],==-2);
    sassert(bs[2],==-4);
}

void test4(){

    std::vector<int> as{1,2,3};
    std::vector<int> bs{-1,-2,-3};
    std::vector<double> cs{-1,-2,-3};

    for([[maybe_unused]] auto a:zip(as,bs,cs)){}
    for([[maybe_unused]] auto [i, a, b, c]:zip(as,bs,cs)){
        c=a;
        a=b;[[maybe_unused]]std::size_t k=i;
    }

    sassert(as[0],==-1);
    sassert(as[1],==-2);
    sassert(as[2],==-3);
    sassert(cs[0],==1);
    sassert(cs[1],==2);
    sassert(cs[2],==3);

}

template<class T> void test5_([[maybe_unused]]const T& z){

    for(auto [i, a,b]:z){
        a++;        b++; i++;
    }
}

void test5()
{
    std::vector<int> as{1,2,3};
    std::vector<double> bs{-1,-2,-3};
    test5_(zip(as,bs));



    for(const auto [i, a, b]:zip(as,bs)){
        a++;
        b++;[[maybe_unused]]std::size_t k=i;
    }

}

void test6(){
    std::map<int, std::string> map;
    map[0]="asdklasdfj";
    map[5]="hmm";
    std::vector<double> as{1,2};
    for([[maybe_unused]] auto [i, a, b]:zip(map,as)){
        [[maybe_unused]]auto k=i;
        [[maybe_unused]]auto l=a;
        [[maybe_unused]]auto m=b;
        //cout<<"i: "<<i<< " "<<a<< " "<<b<<endl;
    }
    [[maybe_unused]] auto z=zip(map,as);
    //z.at(3);


}



template<class T> void test8_(const T& t){

    for([[maybe_unused]] auto [i,a,b] : t)
    {
        // shouldnt work
        //a=0;
        [[maybe_unused]]auto k=i;
        [[maybe_unused]]auto l=a;
        [[maybe_unused]]auto m=b;

    }
    for([[maybe_unused]] auto [i,a,b] : t)
    {
        // should work, but not change
        //a=0;

        [[maybe_unused]]auto k=i;
        [[maybe_unused]]auto l=a;
        [[maybe_unused]]auto m=b;
    }
    {
        [[maybe_unused]] auto a=t.begin();
    }
    {
        [[maybe_unused]] auto a=t[1];

    }
    auto [a,b] = t[1];
            a=0;
            b=0;
            //t[2]; // can segfault! or assert!
            //t.at(3); // throws
            //cout<<t<<endl;
}

void test8(){
        std::vector<int> as{1,2,3};
        std::vector<double> bs{-1,-2};
        auto z=zip(as,bs);
        test8_(z);
        //cout<<z<<endl;

        //cout<<z.at(3)<<endl;// should throw!
    }

#define test_typename_(answer, output)    if(output!=answer) cout<<__PRETTY_FUNCTION__<< " "<<__LINE__<< " "<<"error: \""<<answer<<"\", \""<<output<<"\"" <<endl;
    void test_typename_0(int i){            test_typename_("int", type_name<decltype(i)>());}
    void test_typename_1(int& i){           test_typename_("int&", type_name<decltype(i)>());}
    void test_typename_2(const int i){      test_typename_("const int", type_name<decltype(i)>());}
    void test_typename_3(const int& i){     test_typename_("const int&", type_name<decltype(i)>());}


    template <class T> void test_typename_t0(T t, std::string answer){

        if(type_name<decltype(t)>()!= answer)
            cout<<__PRETTY_FUNCTION__<< " "<<__LINE__<< " "<<"error: \""<<answer<<"\", \""<<type_name<decltype(t)>()<<"\"" <<endl;
    }
    template <class T> void test_typename_t1(T& t, std::string answer){
        if(type_name<decltype(t)>()!= answer+"&")
            cout<<__PRETTY_FUNCTION__<< " "<<__LINE__<< " "<<"error: \""<<answer<<"\", \""<<type_name<decltype(t)>()<<"\"" <<endl;
    }
    template <class T> void test_typename_t2(const T t, std::string answer){
        if(type_name<decltype(t)>()!= "const "+answer)
            cout<<__PRETTY_FUNCTION__<< " "<<__LINE__<< " "<<"error: \""<<answer<<"\", \""<<type_name<decltype(t)>()<<"\"" <<endl;
    }
    template <class T> void test_typename_t3(const T& t, std::string answer){
        if(type_name<decltype(t)>()!= "const "+answer+"&")
            cout<<__PRETTY_FUNCTION__<< " "<<__LINE__<< " "<<"error: \""<<answer<<"\", \""<<type_name<decltype(t)>()<<"\"" <<endl;
    }
    template <class T> void test_typename_t4(T&& t, std::string answer){
        if(type_name<decltype(t)>()!= answer+"&&")
            cout<<__PRETTY_FUNCTION__<< " "<<__LINE__<< " "<<"error: \""<<answer<<"\", \""<<type_name<decltype(t)>()<<"\"" <<endl;
    }


    void test_typename(){

        // should give T
        // gcc only!

        test_typename_("int", type_name<int>());
        const int i=0;
        test_typename_("const int", type_name<decltype(i)>());
        int j=0;
        test_typename_("int", type_name<decltype(j)>());
        test_typename_0(j);
        test_typename_1(j);
        test_typename_2(j);
        test_typename_3(j);
        std::vector<int> vs;
        test_typename_t0(vs,"std::vector<int>");
        test_typename_t1(vs,"std::vector<int>");
        test_typename_t2(vs,"std::vector<int>");
        test_typename_t3(vs,"std::vector<int>");
        test_typename_t4(std::vector<int>(),"std::vector<int>");


    }


    void test_has_random_access(){
        std::cout << std::boolalpha;
        std::cout<<iterator_type::has_iterator_typedef_t<std::vector<int>>()<<endl;
        std::cout<<iterator_type::has_iterator_typedef_t<std::map<int,double>>()<<endl;
        std::cout<<iterator_type::random_access_t<std::vector<int>>()<<endl;
        std::cout<<iterator_type::random_access_t<std::map<int,double>>()<<endl;
        std::cout<<type_name<std::vector<int>::iterator::iterator_category>()<<std::endl;
    }


    int main(int argc, char** argv){
        if(argc==2)
            program_name=argv[1];

        //test_typename();


        std::vector<int>();


        must_exists();

        std::vector<int> as{1,2,3};

        test1();
        test2();
        test3();
        test4();
        test5();
        test6();
        test8();

        cout<<"all good"<<endl;
        return 0;
    }
