#include <string>
#include <sstream>

template<typename A, typename B> 
struct CppUnitAssertEqualTraits {
	static void assertEqual(const A& a, const B& b) {
		CPPUNIT_ASSERT_EQUAL(a, b);
	}
};

template<typename A>
struct CppUnitAssertEqualTraits<A, std::string> {
	static void assertEqual(const A& a, const std::string& b) {
		std::ostringstream s;
		s << a;
		CPPUNIT_ASSERT_EQUAL(s.str(), b);
	}
};

template<>
struct CppUnitAssertEqualTraits<int, size_t> {
	static void assertEqual(int a, size_t b) {
		CPPUNIT_ASSERT_EQUAL(a, (int) b);
	}
};

template<typename A, typename B>
void ASSERT_EQUAL(const A& a, const B& b) {
	CppUnitAssertEqualTraits<A,B>::assertEqual(a, b);
}

#define ASSERT(a) CPPUNIT_ASSERT(a)
#define FAIL(a) CPPUNIT_FAIL(a)
