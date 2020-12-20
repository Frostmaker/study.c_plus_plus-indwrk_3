#include "pch.h"
#include "CppUnitTest.h"
#include "../IndividWork_3/funs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char str[256]{ "One Two  Free   Four     Six" };
			change_cstring(str);
			char res[256]{ "One Two *Free **Four ****Six" };
			for (int i{ 0 }; i < strlen(str); ++i) {
				Assert::AreEqual(str[i], res[i]);
			}
		}

		TEST_METHOD(TestMethod2)
		{
			char str[256]{ "                      " };
			change_cstring(str);
			char res[256]{ " *********************" };
			for (int i{ 0 }; i < strlen(str); ++i) {
				Assert::AreEqual(str[i], res[i]);
			}
		}

		TEST_METHOD(TestMethod3)
		{
			char str[256]{ "          Hello         " };
			change_cstring(str);
			char res[256]{ " *********Hello ********" };
			for (int i{ 0 }; i < strlen(str); ++i) {
				Assert::AreEqual(str[i], res[i]);
			}
		}
	};
}
