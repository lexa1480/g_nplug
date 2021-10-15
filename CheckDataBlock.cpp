#undef NDEBUG // to force asserts build

#ifdef  WIN32
#include <crtdbg.h>
#endif//WIN32

#include <nplug/clnDataBlock.h>
#include <nplug/conDataBlock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace nplug;

TEST(TestCaseCheckDataBlock, AllTestDataBlock)
{
    CClnDataBlock clnDataBlock( CConDataBlock::CreateObj() );
    CClnDataBlock clnDataBlockCopy( clnDataBlock );
    ASSERT_EQ( clnDataBlock.GetIF(), clnDataBlockCopy.GetIF() );
    NByte* pBuf = clnDataBlock.GetBuf();
    ASSERT_EQ( NULL, pBuf );
    clnDataBlock.SetBufCapacity( 100 );
    unsigned uiCapacity = clnDataBlock.GetBufCapacity();
    ASSERT_EQ( 100, uiCapacity );
    pBuf = clnDataBlock.GetBuf();
    ASSERT_TRUE( NULL != pBuf );
    clnDataBlock.Clear();
    clnDataBlock.SetBytesCount( 50 );
    unsigned uiBytes = clnDataBlock.GetBytesCount();
    ASSERT_EQ( 50, uiBytes );
    std::cout << "DataBlock> Bytes: " << uiBytes << std::endl;
    clnDataBlock.SetBufCapacity( 50 );
    uiCapacity = clnDataBlock.GetBufCapacity();
    ASSERT_EQ( 100, uiCapacity );
    std::cout << "DataBlock> Capacity: " << uiCapacity << std::endl;
    clnDataBlock.SetTime( 1000 );
    NUInt64 i64Time = clnDataBlock.GetTime();
    ASSERT_EQ( 1000, i64Time );
    clnDataBlock.SetFlags( 0xFF );
    unsigned dwFlags = clnDataBlock.GetFlags();
    ASSERT_EQ( 0xFF, dwFlags );
    std::cout << "DataBlock> Flags: 0x" << std::hex << dwFlags << std::endl;
    CClnMap clnMap = clnDataBlock.GetParams();
    clnMap.Set( "MyParamName", "ParamData" );
    clnMap.Set( "MySecondParamName", "SecondParamData" );
    string strParam = clnMap.Get( "MyParamName" );
    ASSERT_EQ( "ParamData", strParam  );
    strParam = clnMap.Get( "MySecondParamName" );
    ASSERT_EQ( "SecondParamData", strParam  );
}
