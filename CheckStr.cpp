#undef NDEBUG // to force asserts build

#ifdef  WIN32
#include <crtdbg.h>
#endif//WIN32

#include <nplug/clnStr.h>
#include <nplug/conStr.h>

#include <string>
#include <gtest/gtest.h>

using namespace nplug;

const char c_szStrInit[] =		"InitialString";
const char c_szStr[] =			"TestString";

TEST(TestCaseCheckStr, NotAttached)
{
    // not attached
    std::string sRes = c_szStrInit;
    CClnStr str;
    ASSERT_FALSE( str.Set( c_szStr ));
    ASSERT_FALSE( str.Get( sRes ));
    ASSERT_EQ( c_szStrInit, sRes );

    // attached
    str = CClnStr( CConStr::CreateObj() );
    ASSERT_TRUE( str.Set( c_szStr ) );
    ASSERT_TRUE( str.Get( sRes ) );
    ASSERT_EQ( c_szStr, sRes );
    sRes = c_szStrInit;
    ASSERT_FALSE( sRes.empty() );
    sRes = str;
    ASSERT_EQ( c_szStr, sRes );

    // empty string
    sRes.clear();
    ASSERT_TRUE( str.Set( sRes ) );
    sRes = c_szStrInit;
    ASSERT_TRUE( str.Get( sRes ) );
    ASSERT_TRUE( sRes.empty() );

    // zero-characters
    const char c_szStrZeroed[] =	"*\x00*";
    size_t szSize = sizeof(c_szStrZeroed) - 1;
    std::string sZeroed;
    sZeroed.assign( c_szStrZeroed, szSize );
    ASSERT_EQ( szSize, sZeroed.size() );
    str.Set(sZeroed);
    sRes = c_szStrInit;
    str.Get(sRes);
    ASSERT_EQ( szSize, sRes.size());
    EXPECT_EQ( sRes[0], c_szStrZeroed[0]);
    EXPECT_EQ( sRes[1], c_szStrZeroed[1]);
    EXPECT_EQ( sRes[2], c_szStrZeroed[2]);
    EXPECT_EQ( sRes, sZeroed );

    // references
    ASSERT_EQ( 1, str.GetRefCount() );
    ASSERT_EQ( 1, str.GetRefClientCount() );
    CClnStr strCopy = str;
    ASSERT_EQ( 2, strCopy.GetRefCount() );
    ASSERT_EQ( 2, strCopy.GetRefClientCount() );
    strCopy.Detach();
    ASSERT_EQ( 1, str.GetRefCount() );
    ASSERT_EQ( 1, str.GetRefClientCount() );
}
