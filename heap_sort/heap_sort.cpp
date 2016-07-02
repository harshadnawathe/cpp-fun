#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <type_traits>
#include <vector>

template < class RAItr, class Relation >
void shift_down(RAItr heap, size_t i, const size_t max, Relation r) {
    using std::invoke;
    while(true) {
        auto big = i;
        auto c1 = 2*i + 1;
        auto c2 = c1 + 1;
        if(c1 < max && !invoke(r, heap[c1], heap[big])) big = c1;
        if(c2 < max && !invoke(r, heap[c2], heap[big])) big = c2;
        if( i == big ) return;
        std::iter_swap(heap+i, heap+big);
        i = big;
    }
}

template < class RAItr, class Relation >
void heapify(RAItr begin, RAItr end, Relation r) {
    auto const len = end-begin;
    for (auto i = (len)/2 - 1; i >= 0; --i )
        shift_down(begin, i, len, r);
}

template < class RAItr >
void heapify(RAItr begin, RAItr end) {
    heapify(begin, end, std::less<>{});
}


template < class RAItr, class Relation >
void heap_sort(RAItr begin, RAItr end, Relation r) {
    heapify(begin, end, r);
    while( end != begin ) {
        std::iter_swap(begin, --end);
        shift_down(begin, 0, end-begin, r); 
    }
}

template < class RAItr >
void heap_sort(RAItr begin, RAItr end) {
    heap_sort(begin, end, std::less<>{});
}


template < class Seq > 
void dump(const Seq& seq, std::ostream& o = std::cout) {
    using namespace std;
    using data_t = decay_t<decltype(*begin(seq))>;
    o << "[ ";
    copy(begin(seq), end(seq), ostream_iterator<data_t>{o," "} );
    o << "]\n";
}


int main()
{
    using namespace std;
    
    const size_t N = 10;
    array<int,N> v;
    
    auto gen = [ mt   = mt19937{ random_device{}() }
               , dist = uniform_int_distribution<int>{1,100}
               ] () mutable {
                    return dist(mt);
               };
    
    generate_n(begin(v), N, ref(gen) );
    
    dump(v);
    
    heap_sort(begin(v), end(v));
    
    dump(v);
    
    return 0;
}
