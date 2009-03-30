#include <string>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

int main(int argc, char* argv[])
{
	CppUnit::TextUi::TestRunner runner;
	runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );
	return (runner.run("") ? 0 : 1);
}
