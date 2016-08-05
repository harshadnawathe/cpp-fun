#ifndef _SYNCHRONIZE_H_
#define _SYNCHRONIZE_H_

#include <mutex>

template < class T >
class Synchronize {
public:
	Synchronize() = default;

	Synchronize(T const& data)
		:data_(data)
	{}

	Synchronize(T&& data)
		:data_(std::move(data))
	{}

	struct Synchronizer {	
		std::mutex& m_;
		T* data_;

		~Synchronizer() {
			m_.unlock();
   	}

		auto operator -> () const {
			m_.lock();
			return this->data_;
		}
	};

	auto operator -> () const {
		return Synchronizer{m_, &data_};
	}

	template < class F >
	auto operator () (F f) {
		std::lock_guard<std::mutex> lock{m_};
		return f(data_);
	}
	
private:
	mutable T data_;
	mutable std::mutex m_;
};


#endif
