#ifndef ranges_H
#define ranges_H

#include <iterator>
#include <memory>

namespace  ranges{

template <typename Container, typename InputIterator>
class Iterator: public std::iterator<std::forward_iterator_tag, typename InputIterator::value_type>
{
    friend Container;

    //private constructor
    Iterator(Container& container_,const InputIterator& current_): container(container_), current(current_)
    {
        while(current != container.endInputIter && !container(*current))
            ++current;
    };


public:

    decltype(auto) operator*() {return *current;}
    decltype(auto) operator->() {return current->operator->();}


    Iterator& operator++() {
        do{
            ++current;
        }while(current != container.endInputIter && !container(*current));
        return *this;
    }
    Iterator operator++(int) {
        auto tmp = current;
        ++(*this);
        return tmp;
    }

    bool operator!=(const Iterator& other){
        return current != other.current;
    }
    bool operator==(const Iterator& other){
        return current == other.current;
    }


private:
    Container &container;
    InputIterator current;

};

//-----------------filter_object-------------------------------
template <typename Input, typename UnaryPredicate>
class filter_object: public UnaryPredicate{

    template <typename Container,typename InputIterator>
    friend class Iterator;

public:
   
    filter_object(Input input_, UnaryPredicate up):
        UnaryPredicate(up), input(input_), endInputIter(std::end(input)) {};
    auto begin() {return Iterator{*this,std::begin(input)};} 
    auto end() {return Iterator{*this, std::end(input)};}
    auto rbegin() {return Iterator{*this,std::rbegin(input)};} 
    auto rend() {return Iterator{*this, std::rend(input)};}
private:
    Input input;
    decltype(std::end(input)) endInputIter; 
};

//--------------Filter object reverse---------------------
template <typename Input, typename UnaryPredicate>
class filter_object_reverse: public UnaryPredicate{

    template <typename Container,typename InputIterator>
    friend class Iterator;

public:
   
    filter_object_reverse(Input input_, UnaryPredicate up):
        UnaryPredicate(up), input(input_), endInputIter(std::rend(input)) {};
    auto begin() const {return Iterator{*this,std::rbegin(input)};} 
    auto end() const  {return Iterator{*this, std::rend(input)};}
    auto rbegin() const {return Iterator{*this,std::begin(input)};} 
    auto rend() const  {return Iterator{*this, std::end(input)};}
private:
    Input input;
    decltype(std::rend(input)) endInputIter; 
};

//------Regular filter----------
template <typename UnaryPredicate>
struct filter: UnaryPredicate{
    filter(const UnaryPredicate& up): UnaryPredicate(up) {};
};

//-----DROP------------------
//don't take first n elements
struct drop{
    drop(int drop_n_values_): drop_n_values(drop_n_values_), counter(1) {};
    template<typename T>
    bool operator()(T) {return counter++ > drop_n_values;}
private:
    int drop_n_values;
    int counter;
};

//-----Take------------------
//take first n elements
struct take{
    take(int take_n_values_): take_n_values(take_n_values_), counter(0) {};
    template<typename T>
    bool operator()(T) {return counter++ < take_n_values;}
private:
    int take_n_values;
    int counter;
};

//-----Slice------------------
//take ranges [n_begin, n_end)
struct slice{
    slice(int n_begin_, int n_end_): n_begin(n_begin_), n_end(n_end_), counter(0) {};
    template<typename T>
    bool operator()(T) {
        auto temp = counter;
        counter++;
        return  temp >= n_begin && temp < n_end;
    }
private:
    int n_begin;
    int n_end;
    int counter;
};

//-----Reverse------------------
struct reverse{
    template<typename T>
    bool operator()(T) const {;
        return  1;
    }
};


template <typename Input, typename UnaryPredicate>
auto operator|(Input &&input, UnaryPredicate up)
{
    return filter_object<Input, UnaryPredicate>(input, up);
}

template <typename Input>
auto operator|(Input &&input, reverse _reverse)
{
    return filter_object_reverse<Input, reverse>(input, _reverse);
}


}
#endif // ranges_H
