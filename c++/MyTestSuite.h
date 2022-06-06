#include <cxx/cxxtest-4.3/cxxtest/TestSuite.h>
#include <string>
#include <iostream>
using namespace std;

  class MyTestSuite : public CxxTest::TestSuite
  {
  public:
      void testAddition( void )
      {
		  MyRevenue mr();
		  AssertAreEqual(mr.dqlinquent, true);
          //TS_ASSERT( 1 + 1 > 1 );
          //TS_ASSERT_EQUALS( 1 + 1, 2 );
      }
  };