#include <CppUTest/CommandLineTestRunner.h>

/**
 * We cannot do real testing easily with functions that internally use OpenGL
 * because those tests cannot be run automated from scons. Anyway, those are
 * just thing wrappers over OpenGL calls and should not need testing anyway..
 * *knocks wood*
 */
int main(int argc, const char *argv[])
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}
