#include <future>
#include <iostream>
#include <string>
#include <vector>

#include "synchronize.h"



class Logger {
public:	
	void log(std::string const& line) const {
		std::cout << line << '\n';
	}
};



int test1()
{
	Synchronize<Logger> logger{ Logger{} };
	
	std::vector<std::future<void>> futures;

	for( auto n=0; n < 10; ++n ) {
		auto&& f = std::async( std::launch::async,[&logger, n]{		
			logger->log(std::to_string(n) + '\t' + std::to_string(n) + '\n');
		} );
		futures.push_back(std::move(f));
	}

	for( auto& f : futures ) f.wait();

	std::cout << "done\n";
	return 0;
}

int main()
{
	using sync_string = Synchronize<std::string>;
	
	sync_string s{"Hello\n"};
	
	std::vector<std::future<void>> futures;
	
	for( auto n=0; n < 5; ++n ) {
		auto&& f = std::async( std::launch::async, [&s, n]{
			s([n](auto& s ){
				s += std::to_string(n) + "\t" + std::to_string(n) + '\n';
			});

			s([](auto const& s){
				std::cout << s;
			});
		});
		
		futures.push_back(std::move(f));
	}

	for( auto& f : futures ) f.wait(); 

	return 0;
}
