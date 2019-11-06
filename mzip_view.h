#pragma once
/* ********************************* FILE ************************************/
/** \file    mzip.hpp
 *
 * \brief    This header contains the zip iterator class.
 *
 * WARNING this is a zip view, not a zip copy!
 *
 * \remark
 * - c++17
 * - no dependencies
 * - header only
 * - tested by test_zip_iterator.cpp
 * - not thread safe
 * - view !
 * - extends lifetime of rvalue inputs untill the end of the for loop
 *
 * \todo
 * - add algorithm tests, probably does not work at all...
 *
 *
 * \example
 * std::vector<int> as{1,2},bs{1,2,3};
 * for(auto [index, a,b]: zip(as,bs)){
 *  a++;
 * }
 * cout<<as<<endl; // shows (2, 3)
 * works for any number
 *
 * zip returns tuples of references to the contents
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * does not copy the containers
 * returns tuple of references to the containers content
 * iterates untill the first iterator hits end.
 * extends ownership to the end of the for loop, or untill zip goes out of scope.
 *
 * possibly risky behaviour on clang, gcc for fun(const zip& z) when called as fun(zip(a,b))
 *
 *
 * Depends on the following behaviour for for loops:
 *
 *   // in for(x:zip)
 *   // equiv:
 *  { // c++ 11+
 *      auto && __range = range_expression ;
 *          for (auto __begin = begin_expr, __end = end_expr; __begin != __end; ++__begin) {
 *          range_declaration = *__begin;
 *          loop_statement
 *      }
 *  }
 *
 *   { // in c++ 17
 *      auto && __range = range_expression ;
 *      auto __begin = begin_expr ;
 *      auto __end = end_expr ;
 *      for ( ; __begin != __end; ++__begin) {
 *          range_declaration = *__begin;
 *          loop_statement
 *      }
 *  }
 *
 *
 * \author   Mikael Persson
 * \date     2019-09-01
 ******************************************************************************/

static_assert(__cplusplus>=201703L, " must be c++17 or greater"); // could be rewritten in c++11, but the features you must use will be buggy in an older compiler anyways.
#include <sstream>
#include <iostream>
#include <tuple>
#include <vector>
#include <functional>
#include <assert.h>
#include <type_traits>


namespace iterator_type
{
template <typename... Ts> using void_t = void;
template <typename T, typename = void> struct has_iterator_typedef : std::false_type {}; // default variant
template <typename T> struct has_iterator_typedef<T, void_t<typename T::iterator>> : std::true_type {}; // better match if exists,
template<class T> constexpr bool has_iterator_typedef_t(){ return has_iterator_typedef<T>::value;}

template <typename T> struct random_access : std::false_type {}; // default variant
template<> struct random_access<std::random_access_iterator_tag> : std::true_type {};
template<class T> constexpr bool random_access_t(){return random_access<typename std::remove_reference_t<T>::iterator::iterator_category>::value;}

// really what I want is to know if random access works.
template<class T> struct has_random_access : std::false_type{};
template<> struct has_random_access<std::random_access_iterator_tag> : std::true_type {};
}

template<class T>
/**
 * @brief The zip_iterator class
 *
 * Provides a zip iterator which is at end when any is at end
 */
class zip_iterator{
public:
    // speeds up compilation a little bit...
    using tuple_indexes=std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<T>>>;

    zip_iterator(T iter, T iter_end):
        iter(iter),
        iter_end(iter_end),
        index(0){    }
    // prefix, inc first, then return
    zip_iterator& operator++()
    {
        for_each_in_tuple([](auto&& x){return x++;},iter);
        // then if any hit end, update all to point to end.
        auto end=apply2([](auto x, auto y){return x==y;},iter,iter_end);
        if(if_any_in(end))

            apply2([](auto& x, auto y){return x=y;},iter,iter_end);
        index++;
        return *this;
    }
    // post fix, return value before increment
    zip_iterator operator++(int) {
        zip_iterator ret = *this;
        this->operator++();
        return ret;
    }
    // sufficient because ++ keeps track and sets all to end when any is
    bool operator != (const zip_iterator& other) const {
        return other.iter!=iter;
    }
    auto operator*() const{
        return std::forward<decltype(get_refs(iter, tuple_indexes{}))>(get_refs(iter, tuple_indexes{}));
    }
private:
    T iter, iter_end;
    std::size_t index=0;

    template<std::size_t... I> auto get_refs(T t, std::index_sequence<I...>)  const  {
        return std::make_tuple(index, std::ref(*std::get<I>(t))...);
    }

    template<class F, class A, std::size_t... I>
    auto apply2_impl(F&& f, A&& a, A&& b,
                     std::index_sequence<I...>)    {
        return std::make_tuple(f(std::get<I>(a),std::get<I>(b))...);
    }
    template<class F, class A> auto apply2(F&& f, A&& a, A&& b){
        return apply2_impl(
                    std::forward<F>(f),
                    std::forward<A>(a),
                    std::forward<A>(b),
                    tuple_indexes{}
                    );
    }
    template<class A, std::size_t... I>
    bool if_any_impl(const A& t,
                     std::index_sequence<I...>) const{
        return (...|| std::get<I>(t)); // c++17
    }

    // in general context we must enforce that these are tuples
    template<class A> bool if_any_in(A&& t)  const{
        return if_any_impl(std::forward<A>(t),
                           tuple_indexes{}
                           );
    }

    template <class F, class Tuple, std::size_t... I>
    auto for_each_in_impl(F&& f, Tuple&& t, std::index_sequence<I...>) const{
        return std::make_tuple( f(std::get<I>(t))...);
    }

    template<class F, class A> void for_each_in_tuple(F&& f, A&& t)  const{
        for_each_in_impl(std::forward<F>(f),
                         std::forward<A>(t),
                         tuple_indexes{});
    }
};


template<class... S>
class zip{
    using arg_indexes=std::make_index_sequence<sizeof...(S)>;
public:
    zip(S... args ) : args(std::forward<S>(args)...)    {}
    auto begin() const { return get_begins( arg_indexes{});    }
    auto end()   const { return get_ends( arg_indexes{});    }
    std::size_t size() const{
        return size_impl(arg_indexes{});
    }
    // in the time honored tradition of letting people shoot themselves in the foot...
    auto operator[](std::size_t index) const{
        static_assert((...&&iterator_type::random_access_t<S>()), " requires random access iterators");
        assert(index<size());
        return access(index,arg_indexes{});
    }
    auto at(std::size_t index) const{
        static_assert((...&&iterator_type::random_access_t<S>()), " requires random access iterators");
        if(size()<=index)
            throw new std::out_of_range("zip iterator out of bounds");
        return access(index,arg_indexes{});
    }
private:
    std::tuple<S...> args;
    template<std::size_t... I> auto get_begins( std::index_sequence<I...>)  const  {
        return zip_iterator(std::make_tuple(std::get<I>(args).begin()...),
                            std::make_tuple(std::get<I>(args).end()...));
    }
    template<std::size_t... I> auto get_ends( std::index_sequence<I...>)  const  {
        return zip_iterator(std::make_tuple(std::get<I>(args).end()...),
                            std::make_tuple(std::get<I>(args).end()...));
    }
    template <std::size_t... I>
    auto access(std::size_t index,
                std::index_sequence<I...>) const
    {
        static_assert((...&&iterator_type::random_access_t<S>()), " requires random access iterators");
        assert(index<size());
        // this works for e.g. map<int,int>, is that a good thing?
        return std::make_tuple(std::ref(std::get<I>(args)[index])...);
    }
    template <std::size_t... I>
    auto size_impl(std::index_sequence<I...>) const{
        return std::max({std::size_t(std::get<I>(args).size())...});
    }


    template<class A, std::size_t... I>
    bool if_any_impl(const A& t,
                     std::index_sequence<I...>) const{
        return (...|| std::get<I>(t)); // c++17
    }
};


// deduction guide,
template<class... S> zip(S&&...) -> zip<S...>;



template <typename T>
/**
 * @brief type_name<decltype(t)>
 *
 * useful for testing types when there are too many templates and autos everywhere.
 * returns a std::string with the cv ref qualified name of the type
 * \notes
 * -  std::string has multiple names, so auto is used.
 * - type_name<T> will give the cvref unqualified type?
 */
auto type_name()
{
    const std::string name(__PRETTY_FUNCTION__);
    // output varies by compiler, so gcc:
    const std::string gcc_prefix("auto type_name() [with T = ");
    const std::string clang_prefix("auto type_name() [T = ");
    const std::string suffix("]");
    if(name.size()>clang_prefix.size()){
        if(name.substr(0,clang_prefix.size()) == clang_prefix){
            return  name.substr(clang_prefix.size(),name.size()-clang_prefix.size() - suffix.size());
        }
    }
    if(name.size()>gcc_prefix.size()){
        if(name.substr(0,gcc_prefix.size()) == gcc_prefix){
            return  name.substr(gcc_prefix.size(),name.size()-gcc_prefix.size() - suffix.size());
        }
    }
    return std::string("failed to get typename via pretty function, unknown compiler?");
}

namespace tuple_print{
template<class T> std::string str_typename(T t){
    std::stringstream ss;
    ss<<type_name<decltype(t)>();
    return ss.str();
}
template<class T> std::string str(T t){
    std::stringstream ss;
    ss<<t;
    return ss.str();
}
template<> std::string str<bool>(bool t){
    if(t)
        return "true";
    return "false";
}
template<class... T>
std::string str_t(T... t) {
    std::stringstream ss;
    std::vector<std::string> strs{str(t)...};
    for(auto s:strs)
        ss<<s<<", ";
    std::string s=ss.str();
    if(s.size()<2) return s;
    return s.substr(0,s.size()-2);
}

template<class T, std::size_t... I > std::string tuple2str_impl(T tuple, std::index_sequence<I...>){
    return str_t(std::get<I>(tuple)...);
}

template<class T>
std::string  tuple2str(T tuple){
    return str_t(tuple,std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<T>>>{});
}
}

template<class... T>
std::ostream& operator<<(std::ostream& os,
                         std::tuple<T...> t){
    os<<"(";
    os<<tuple_print::tuple2str_impl(t, std::make_index_sequence<sizeof...(T)>{});
    os<<")";
    return os;
}
template<class A, class B>
std::ostream& operator<<(std::ostream& os,
                         std::pair<A,B> t){
    return os<<std::make_tuple(t.first, t.second);
}


template<class... S>
std::ostream& operator<<(std::ostream& os,
                         zip<S...> z){
    std::stringstream ss;
    ss<<"{\n";
    for(auto t:z){
        ss<<t<<",\n";
    }
    ss<<"}";
    return os<<ss.str();
}




