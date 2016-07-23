#include <iostream>

void println() {
	std::cout << '\n';
}

template < class T >
void println(T&& t) {
	std::cout << std::forward<T>(t) << '\n';
}

template < class T0, class... T1toN>
void println(T0&& t0, T1toN&&... t1toN ){
	std::cout << std::forward<T0>(t0) << ' ';
	println(std::forward<T1toN>(t1toN)...);
}

int main() {
	println();
	println("abcd");
	println(42,'X',"Hello");
}
