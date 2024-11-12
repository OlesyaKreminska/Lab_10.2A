#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_10.2A/Lab_10.2A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(StudentTests)
    {
    public:

        TEST_METHOD(TestSortStudents)
        {
            
            Student students[3] = {
                {"Ivanov", 1, KOMPYUTERNI_NAUKY, 80, 85, 90},   
                {"Petrenko", 2, INFORMATYKA, 75, 80, 70},       
                {"Shevchenko", 1, MATEMATYKA_TA_EKONOMIKA, 85, 90, 95} 
            };

            SortStudents(students, 3);

            Assert::AreEqual(students[0].prizv, string("Shevchenko")); 
            Assert::AreEqual(students[1].prizv, string("Ivanov"));     
            Assert::AreEqual(students[2].prizv, string("Petrenko"));  
        }

    };
}