//============================================================================
// Name        : Functors.cpp
// Author      : Stephen Wray
// Version     : 1.1
// Copyright   : Copyright 2012 Stephen Wray
// Description : Trouble with Functors
//============================================================================

#include <algorithm>
#include <iostream>
#include <vector>

// Comment to fix.
using std::unary_function;

// Uncomment to fix.
/*
template<typename argument, typename result>
struct unary_function {
public:
	virtual ~unary_function() {};
	virtual result operator()(argument arg) = 0;
};
*/

template<typename argument, typename result>
struct square: public unary_function<argument, result> {
public:
	result operator()(argument arg) {
		return arg * arg;
	}
};

template<typename argument, typename result>
struct proxy_unary_function: public unary_function<argument, result> {
public:
	proxy_unary_function(unary_function<argument, result>& unary_function) :
			unary_function_(unary_function) {
	}

	result operator()(argument arg) {
		return unary_function_(arg);
	}

private:
	unary_function<argument, result>& unary_function_;
};

int main() {
	std::vector<int> vs;
	vs.push_back(1);
	vs.push_back(2);
	vs.push_back(3);

	for (std::vector<int>::const_iterator i = vs.begin(); i != vs.end(); ++i) {
		std::cout << *i << std::endl;
	}

	std::cout << "Transform..." << std::endl;
	square<int&, int> sq;
	std::transform(vs.begin(), vs.end(), vs.begin(),
			proxy_unary_function<int&, int>(sq));
	std::transform(vs.begin(), vs.end(), vs.begin(), sq);

	for (std::vector<int>::const_iterator i = vs.begin(); i != vs.end(); ++i) {
		std::cout << *i << std::endl;
	}

	return 0;
}
