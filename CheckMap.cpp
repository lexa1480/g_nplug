#undef NDEBUG // to force asserts build

#ifdef  WIN32
#include <crtdbg.h>
#endif//WIN32

#include <nplug/clnMap.h>
#include <nplug/conMap.h>

#include <string>
#include <gtest/gtest.h>

using namespace nplug;

TEST(TestCaseCheckMap, AllTestMap)
{
    CClnMap mapTemp( CConMap::CreateObj() );
    ASSERT_TRUE( mapTemp.IsAttached() );
    mapTemp.Set( "1", "first" );
    ASSERT_EQ( 1, mapTemp.GetParamCount() );
    mapTemp.Set( "2", "second" );
    mapTemp.Set( "3", "third" );
    ASSERT_EQ( 3, mapTemp.GetParamCount() );
    std::string str = mapTemp.Get( "2" );
    ASSERT_EQ( "second", str );



    CClnMap mapTempCopy( mapTemp );
    ASSERT_TRUE( mapTempCopy.IsAttached() );
    ASSERT_EQ(  mapTemp.GetIF(),mapTempCopy.GetIF() );



    ASSERT_TRUE( mapTemp.Get( "2", str ) );
    ASSERT_EQ( "second", str );
    ASSERT_TRUE( mapTemp.Get( "3", str ) );
    ASSERT_EQ( "third", str );
    ASSERT_FALSE( mapTemp.Get( "10", str ) );



    std::string str1;
    std::string str2;

    ASSERT_TRUE( mapTemp.GetParamByIdx( 1, str1, str2 ) );
    ASSERT_EQ( "2", str1 );
    ASSERT_EQ( "second", str2 );

    ASSERT_TRUE( mapTemp.GetParamByIdx( 2, str1, str2 ) );
    ASSERT_EQ( "3", str1);
    ASSERT_EQ( "third", str2 );

    ASSERT_TRUE( mapTemp.GetParamByIdx( 0, str1, str2 ) );
    ASSERT_EQ( "1", str1 );
    ASSERT_EQ( "first", str2 );

    ASSERT_TRUE( mapTemp.GetParamByIdx( 2, str1, str2 ) );
    ASSERT_EQ( "3", str1 );
    ASSERT_EQ( "third", str2 );



    mapTemp.Remove( "2" );
    ASSERT_EQ( 2, mapTemp.GetParamCount() );

    mapTemp.Clear();
    ASSERT_EQ( 0, mapTemp.GetParamCount() );
    ASSERT_FALSE( mapTemp.GetParamByIdx( 1, str1, str2 ) );
    ASSERT_FALSE( mapTemp.SetParam( "", str1 ) );
    ASSERT_FALSE( mapTemp.GetParam( "", str1 ) );



    unsigned char byData = 255;
    mapTemp.SetParam( "2", byData );
    byData = 0;
    mapTemp.GetParam( "2", byData );
    ASSERT_EQ( 255, byData );



    unsigned uData = 16;
    mapTemp.SetParam( "1", uData );
    uData = 0;
    mapTemp.GetParam( "1", uData );
    ASSERT_EQ( 16, uData );



    int iData = -16;
    mapTemp.SetParam( "1", iData );
    iData = 0;
    mapTemp.GetParam( "1", iData );
    ASSERT_EQ( -16, iData );



    double dData = -16.5;
    ASSERT_TRUE( mapTemp.SetParam( "2", dData ) );
    iData = 0;
    ASSERT_TRUE( mapTemp.GetParam( "2", dData ) );
    ASSERT_EQ( -16.5, dData );
}
