#include <algorithm>

namespace hpn
{

template < class RandomItr, class UnaryPredicate >
RandomItr stable_partition(RandomItr begin, RandomItr end, UnaryPredicate p )
{
    const auto n = end - begin;
    
    if( n == 0 ) return begin;
    if( n == 1 ) return begin + p(*begin);
    
    auto mid = begin + n/2;
    
    return std::rotate( stable_partition(begin, mid, p)
                      , mid
                      , stable_partition(mid, end, p));
}
        
}

#include <cassert>

#include <array>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>

int main() 
{
    using namespace std;
    
    auto gen = [ mt   = mt19937{ random_device{}() }
               , dist = uniform_int_distribution<int>{1,100}
               ] () mutable 
               {
                    return dist(mt);
               };
    
    const size_t N = 10;
    array<int, N> a;
    
    generate_n( begin(a), N, ref(gen) );
    
    auto cnt = 0;
    auto is_even = [ &cnt = cnt](auto n) mutable 
                   {
                        ++cnt;
                        return (n & 0x1) != 1; 
                   }; 
    
		auto out = ostream_iterator<int>{ cout, " " };   

		copy( begin(a), end(a), out );
		cout << '\n';
		
		auto part = hpn::stable_partition( begin(a), end(a), is_even );
		
		assert( cnt == a.size() );
		
		copy( begin(a), part, out );
    cout << "^ ";
		copy( part, end(a), out );
		cout << '\n';
		
	  return 0;		
}
