
#include <cassert>

#include <algorithm>
#include <iterator>

namespace hpn {

template < class FwdItr >
FwdItr mid_point(FwdItr begin, FwdItr end )
{
    assert( std::distance(begin, end) > 1 ); //Pre-condition
    
    auto slow = std::next(begin);
    auto fast = std::next(slow);
    
    while(fast != end)
    {
        ++slow;
        
        ++fast;
        if(fast == end) break;
        ++fast;
    }
    
    return slow;
}

template < class FwdItr >
void reverse( FwdItr begin, FwdItr end )
{
	if(begin == end) return;
	
	if(std::next(begin) == end) return;
	
	auto mid = mid_point(begin, end);

	hpn::reverse( begin, mid);
	hpn::reverse( mid, end);

	std::rotate(begin, mid, end);	
}

} //namespace hpn


#include <forward_list>
#include <iostream>

int main()
{
	using namespace std;
	forward_list<int> lst{8,7,6,5,4,3,2,1,0};

	auto out = ostream_iterator<int>{cout, " "};
	
	copy(begin(lst), end(lst), out); cout << '\n';

	hpn::reverse(begin(lst), end(lst));

	copy(begin(lst), end(lst), out); cout << '\n';

	return 0;
}
