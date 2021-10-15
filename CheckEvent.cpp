#undef NDEBUG // to force asserts build

#ifdef  WIN32
#include <crtdbg.h>
#endif//WIN32

#include <nplug/clnEvent.h>
#include <nplug/conEvent.h>
#include <gtest/gtest.h>

using namespace std;
using namespace nplug;

const char	c_szSubscrName[] = "TestSubscriber";
const char	c_szEventName[] = "eventTemp";

struct CEventSubscriber : public ICbEventSubscriber
{
	bool			m_bIsSet;
	string			m_strEventName;
	CClnMap			m_map;
	int				m_iCount;

	CEventSubscriber()
        : m_bIsSet(false)
        , m_strEventName()
        , m_map( CClnMap( CConMap::CreateObj() ) )
        , m_iCount(0)
	{
//		m_bIsSet = false;
//		m_iCount = 0;
//		m_map = CClnMap( CConMap::CreateObj() );
	}
	NVoid	CbOnEvent( LPCNStr pEventName, NBool bIsSet, IMap* pParams )
	{
		m_strEventName = pEventName;
		m_bIsSet = ( bIsSet != 0 );
		if( pParams )
		{
			CClnMap mapSrc( pParams );
			m_map.CopyDataFrom( mapSrc );
		}
		m_iCount++;
	}
	IStr*	CbGetSubscriberName()
	{
		IStr* pStr = NULL;
		CClnStr sName( CConStr::CreateObj() );
		sName.Set( c_szSubscrName );
		pStr = sName.GetIF();
		sName.Unbind();
		return pStr;
	}
};

const char c_szDate[] = "2020-06-24";

TEST(TestCaseCheckEvent, AllTestsEvent)
{
    CEventSubscriber subscr;
    CClnEvent clnEvent( CConEvent::CreateObj() );
    CClnEvent clnEventCopy( clnEvent );
    ASSERT_EQ( clnEvent.GetIF(), clnEventCopy.GetIF() );
    ASSERT_TRUE( clnEvent.IsAttached() );
    clnEvent.Subscribe( &subscr );
    clnEvent.SetName( c_szEventName );
    ASSERT_EQ( c_szEventName, clnEvent.GetName() );
    ASSERT_FALSE( clnEvent.IsSet() );
    CClnMap clnMap( CConMap::CreateObj() );
    clnMap.Set( "Time", c_szDate );
    ASSERT_EQ( c_szDate, clnMap.Get( "Time" ) );
    clnEvent.SetState( true, clnMap );
    ASSERT_TRUE( clnEvent.IsSet() );
    clnMap.Clear();
    bool bState = false;
    clnEvent.GetState( bState, clnMap );
    ASSERT_TRUE( bState );
    ASSERT_EQ( c_szDate, clnMap.Get( "Time" ) );

    // check subscriber
    ASSERT_EQ( 1, clnEvent.GetSubscriberCount() );
    ASSERT_TRUE( subscr.m_bIsSet );
    ICbEventSubscriber* pSubscr = clnEvent.GetSubscriber( 0 );
    ASSERT_EQ( &subscr, pSubscr );
    CClnStr sSubscrName( pSubscr->CbGetSubscriberName() );
    string strSubscrName = sSubscrName.Get();
    ASSERT_EQ( c_szSubscrName, strSubscrName );
    clnEvent.UnSubscribe( &subscr );
    ASSERT_EQ( 0, clnEvent.GetSubscriberCount() );
    ASSERT_TRUE( subscr.m_bIsSet );
    ASSERT_EQ( c_szEventName, subscr.m_strEventName );
    ASSERT_EQ( c_szDate, subscr.m_map.Get( "Time" ) );
    ASSERT_EQ( 1, subscr.m_iCount );

    // check wait
    CClnEvent clnEventCancel( CConEvent::CreateObj() );
    clnEventCancel.SetState( true );
    clnEvent.SetState( true );
    ASSERT_TRUE( clnEvent.Wait( true ) );
    ASSERT_FALSE( clnEvent.Wait( false, &clnEventCancel ) );
    clnEvent.SetState( false );
    ASSERT_TRUE( clnEvent.Wait( false ) );
    ASSERT_FALSE( clnEvent.Wait( true, &clnEventCancel ) );
}

