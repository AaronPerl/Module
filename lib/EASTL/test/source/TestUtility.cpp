/////////////////////////////////////////////////////////////////////////////
// Copyright (c) Electronic Arts Inc. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#include "EASTLTest.h"
#include <EASTL/utility.h>
#include <EAStdC/EAString.h>

struct BasicObject
{
	int mX;
	BasicObject(int x) : mX(x) {}
};

inline bool operator==(const BasicObject& t1, const BasicObject& t2) { return t1.mX == t2.mX; }

inline bool operator<(const BasicObject& t1, const BasicObject& t2) { return t1.mX < t2.mX; }

///////////////////////////////////////////////////////////////////////////////
// TestUtilityPair
//
static int TestUtilityPair()
{
	using namespace eastl;

	int nErrorCount = 0;

	{
		int _0 = 0, _2 = 2, _3 = 3;
		float _1f = 1.f;

		// pair();
		pair<int, float> ifPair1;
		EATEST_VERIFY((ifPair1.first == 0) && (ifPair1.second == 0.f));

		// pair(const T1& x, const T2& y);
		pair<int, float> ifPair2(_0, _1f);
		EATEST_VERIFY((ifPair2.first == 0) && (ifPair2.second == 1.f));

		// template <typename U, typename V>
		// pair(U&& u, V&& v);
		pair<int, float> ifPair3(int(0), float(1.f));
		EATEST_VERIFY((ifPair3.first == 0) && (ifPair3.second == 1.f));

		// template <typename U>
		// pair(U&& x, const T2& y);
		const float fConst1 = 1.f;
		pair<int, float> ifPair4(int(0), fConst1);
		EATEST_VERIFY((ifPair4.first == 0) && (ifPair4.second == 1.f));

		// template <typename V>
		// pair(const T1& x, V&& y);
		const int intConst0 = 0;
		pair<int, float> ifPair5(intConst0, float(1.f));
		EATEST_VERIFY((ifPair5.first == 0) && (ifPair5.second == 1.f));

		pair<const int, const int> constIntPair(_2, _3);
		EATEST_VERIFY((constIntPair.first == 2) && (constIntPair.second == 3));

		// pair(const pair&) = default;
		pair<int, float> ifPair2Copy(ifPair2);
		EATEST_VERIFY((ifPair2Copy.first == 0) && (ifPair2Copy.second == 1.f));

		pair<const int, const int> constIntPairCopy(constIntPair);
		EATEST_VERIFY((constIntPairCopy.first == 2) && (constIntPairCopy.second == 3));

		// template<typename U, typename V>
		// pair(const pair<U, V>& p);
		pair<long, double> idPair2(ifPair2);
		EATEST_VERIFY((idPair2.first == 0) && (idPair2.second == 1.0));

		// pair(pair&& p);

		// template<typename U, typename V>
		// pair(pair<U, V>&& p);

		// pair& operator=(const pair& p);

		// template<typename U, typename V>
		// pair& operator=(const pair<U, V>& p);

		// pair& operator=(pair&& p);

		// template<typename U, typename V>
		// pair& operator=(pair<U, V>&& p);

		// void swap(pair& p);

		// use_self, use_first, use_second
		use_self<pair<int, float> > usIFPair;
		use_first<pair<int, float> > u1IFPair;
		use_second<pair<int, float> > u2IFPair;

		ifPair2 = usIFPair(ifPair2);
		EATEST_VERIFY((ifPair2.first == 0) && (ifPair2.second == 1));

		int first = u1IFPair(ifPair2);
		EATEST_VERIFY(first == 0);

		float second = u2IFPair(ifPair2);
		EATEST_VERIFY(second == 1);

		// make_pair
		pair<int, float> p1 = make_pair(int(0), float(1));
		EATEST_VERIFY((p1.first == 0) && (p1.second == 1.f));

		pair<int, float> p2 = make_pair_ref(int(0), float(1));
		EATEST_VERIFY((p2.first == 0) && (p2.second == 1.f));

		pair<const char*, int> p3 = eastl::make_pair("a", 1);
		EATEST_VERIFY((EA::StdC::Strcmp(p3.first, "a") == 0) && (p2.second == 1));

		pair<const char*, int> p4 = eastl::make_pair<const char*, int>("a", 1);
		EATEST_VERIFY((EA::StdC::Strcmp(p4.first, "a") == 0) && (p4.second == 1));

		pair<int, const char*> p5 = eastl::make_pair<int, const char*>(1, "b");
		EATEST_VERIFY((p5.first == 1) && (EA::StdC::Strcmp(p5.second, "b") == 0));

#if !defined(EA_COMPILER_NO_AUTO)
		auto p60 = eastl::make_pair("a", "b");  // Different strings of same length of 1.
		EATEST_VERIFY((EA::StdC::Strcmp(p60.first, "a") == 0) && (EA::StdC::Strcmp(p60.second, "b") == 0));

		auto p61 = eastl::make_pair("ab", "cd");  // Different strings of same length > 1.
		EATEST_VERIFY((EA::StdC::Strcmp(p61.first, "ab") == 0) && (EA::StdC::Strcmp(p61.second, "cd") == 0));

		auto p62 = eastl::make_pair("abc", "bcdef");  // Different strings of different length.
		EATEST_VERIFY((EA::StdC::Strcmp(p62.first, "abc") == 0) && (EA::StdC::Strcmp(p62.second, "bcdef") == 0));

		char strA[] = "a";
		auto p70 = eastl::make_pair(strA, strA);
		EATEST_VERIFY((EA::StdC::Strcmp(p70.first, "a") == 0) && (EA::StdC::Strcmp(p70.second, "a") == 0));

		char strBC[] = "bc";
		auto p71 = eastl::make_pair(strA, strBC);
		EATEST_VERIFY((EA::StdC::Strcmp(p71.first, "a") == 0) && (EA::StdC::Strcmp(p71.second, "bc") == 0));

		const char cstrA[] = "a";
		auto p80 = eastl::make_pair(cstrA, cstrA);
		EATEST_VERIFY((EA::StdC::Strcmp(p80.first, "a") == 0) && (EA::StdC::Strcmp(p80.second, "a") == 0));

		const char cstrBC[] = "bc";
		auto p81 = eastl::make_pair(cstrA, cstrBC);
		EATEST_VERIFY((EA::StdC::Strcmp(p81.first, "a") == 0) && (EA::StdC::Strcmp(p81.second, "bc") == 0));
#endif
	}

	{
// One-off tests and regressions

#if EASTL_PAIR_CONFORMANCE  // See http://www.open-std.org/jtc1/sc22/wg21/docs/lwg-defects.html#811
		pair<char*, char*> zeroLiteralPair(0, 0);
		EATEST_VERIFY((zeroLiteralPair.first == NULL) && (zeroLiteralPair.second == NULL));
#endif

		// template<typename U>
		// pair(U&& x, const T2& y)
		typedef eastl::pair<uint16_t, const char8_t*> LCIDMapping;
		LCIDMapping lcidMappingArray[1] = {LCIDMapping(0x0036, "af")};  // Note that 0x0036 is of type int.
		EATEST_VERIFY((lcidMappingArray[0].first == 0x0036));

		// template<typename V>
		// pair(const T1& x, V&& y)
		typedef eastl::pair<const char8_t*, uint16_t> LCIDMapping2;
		LCIDMapping2 lcidMapping2Array[1] = {LCIDMapping2("af", 0x0036)};
		EATEST_VERIFY((lcidMapping2Array[0].second == 0x0036));

// The following code was giving an EDG compiler:
//       error 145: a value of type "int" cannot be used to initialize
//       an entity of type "void *" second(eastl::forward<V>(v)) {}
// template <typename U, typename V>
// pair(U&& u, V&& v);
#if EASTL_PAIR_CONFORMANCE
		typedef eastl::pair<float*, void*> TestPair1;
		float fOne = 1.f;
		TestPair1 testPair1(&fOne, NULL);
		EATEST_VERIFY(*testPair1.first == 1.f);
#endif
	}

	return nErrorCount;
}

///////////////////////////////////////////////////////////////////////////////
// TestUtilityRelops
//
static int TestUtilityRelops()
{
	int nErrorCount = 0;

	{
		using namespace eastl::rel_ops;  // Defines default versions of operators !=, <, >, <=, >= based on == and <.

		BasicObject bo1(1), bo2(2);

		EATEST_VERIFY(!(bo1 == bo2));
		EATEST_VERIFY((bo1 != bo2));
		EATEST_VERIFY((bo1 < bo2));
		EATEST_VERIFY(!(bo1 > bo2));
		EATEST_VERIFY((bo1 <= bo2));
		EATEST_VERIFY(!(bo1 >= bo2));
	}

	return nErrorCount;
}

// ThrowSwappable
struct ThrowSwappable
{
};

void swap(ThrowSwappable& x, ThrowSwappable& y) EA_NOEXCEPT_IF(false)
{
	ThrowSwappable temp(x);
	x = y;
	y = temp;

#if EASTL_EXCEPTIONS_ENABLED
	throw int();
#endif
}

#if EASTL_TYPE_TRAIT_is_nothrow_swappable_CONFORMANCE

// NoThrowSwappable
struct NoThrowSwappable
{
};

void swap(NoThrowSwappable& x, NoThrowSwappable& y) EA_NOEXCEPT_IF(true)
{
	NoThrowSwappable temp(x);
	x = y;
	y = temp;
}
#endif

static int TestUtilitySwap()
{
	int nErrorCount = 0;

// is_swappable
// is_nothrow_swappable
#if EASTL_TYPE_TRAIT_is_swappable_CONFORMANCE
	static_assert((eastl::is_swappable<int>::value == true), "is_swappable failure");
	static_assert((eastl::is_swappable<eastl::vector<int> >::value == true), "is_swappable failure");
	static_assert((eastl::is_swappable<ThrowSwappable>::value == true), "is_swappable failure");
// Need to come up with a class that's not swappable. How do we do that, given the universal swap template?
// static_assert((eastl::is_swappable<?>::value  == false), "is_swappable failure");
#endif

#if EASTL_TYPE_TRAIT_is_nothrow_swappable_CONFORMANCE
	static_assert((eastl::is_nothrow_swappable<int>::value == true),
				  "is_nothrow_swappable failure");  // There currently isn't any specialization for swap of scalar types
													// that's nothrow.
	static_assert((eastl::is_nothrow_swappable<eastl::vector<int> >::value == false), "is_nothrow_swappable failure");
	static_assert((eastl::is_nothrow_swappable<ThrowSwappable>::value == false), "is_nothrow_swappable failure");
	static_assert((eastl::is_nothrow_swappable<NoThrowSwappable>::value == true), "is_nothrow_swappable failure");
#endif

	return nErrorCount;
}

#if !defined(EA_COMPILER_NO_NOEXCEPT) && EASTL_MOVE_SEMANTICS_ENABLED

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Warning C4626 warns against an implicitly deleted move assignment operator.
// This warning was disabled by default in VS2013. It was enabled by default in
// VS2015.  Since the the tests below are explicitly testing move construction
// of the various classes explicitly deleting the move assignment to remove the
// warning is safe. 
//
// https://msdn.microsoft.com/en-us/library/23k5d385.aspx

struct noexcept_move_copy
{
	bool mStatus;

	noexcept_move_copy() : mStatus(true) {}

	noexcept_move_copy(const noexcept_move_copy&) = default;

	noexcept_move_copy(noexcept_move_copy&& r) noexcept { r.mStatus = false; }

	noexcept_move_copy& operator=(const noexcept_move_copy&) = delete;  // required as VS2015 enabled C4626 by default.
};

struct noexcept_move_no_copy
{
	bool mStatus;

	noexcept_move_no_copy() : mStatus(true) {}

	noexcept_move_no_copy(const noexcept_move_no_copy&) = delete;

	noexcept_move_no_copy(noexcept_move_no_copy&& r) noexcept { r.mStatus = false; };

	noexcept_move_no_copy& operator=(const noexcept_move_no_copy&) = delete;  // required as VS2015 enabled C4626 by default.
};

struct except_move_copy
{
	bool mStatus;

	except_move_copy() : mStatus(true) {}

	except_move_copy(const except_move_copy&) = default;

	except_move_copy(except_move_copy&& r) noexcept(false) { r.mStatus = false; };

	except_move_copy& operator=(const except_move_copy&) = delete;  // required as VS2015 enabled C4626 by default.
};

struct except_move_no_copy
{
	bool mStatus;

	except_move_no_copy() : mStatus(true) {}

	except_move_no_copy(const except_move_no_copy&) = delete;

	except_move_no_copy(except_move_no_copy&& r) noexcept(false) { r.mStatus = false; };

	except_move_no_copy& operator=(const except_move_no_copy&) = delete;  // required as VS2015 enabled C4626 by default.
};
#endif

static int TestUtilityMove()
{
	int nErrorCount = 0;

// move_if_noexcept
#if !defined(EA_COMPILER_NO_NOEXCEPT) && EASTL_MOVE_SEMANTICS_ENABLED
	noexcept_move_copy nemcA;
	noexcept_move_copy nemcB =
		eastl::move_if_noexcept(nemcA);  // nemcB should be constructed via noexcept_move_copy(noexcept_move_copy&&)
	EATEST_VERIFY(nemcA.mStatus == false);
	EA_UNUSED(nemcB);

	noexcept_move_no_copy nemncA;
	noexcept_move_no_copy nemncB = eastl::move_if_noexcept(
		nemncA);  // nemncB should be constructed via noexcept_move_no_copy(noexcept_move_no_copy&&)
	EATEST_VERIFY(nemncA.mStatus == false);
	EA_UNUSED(nemncB);

	except_move_copy emcA;
	except_move_copy emcB = eastl::move_if_noexcept(
		emcA);  // emcB should be constructed via except_move_copy(const except_move_copy&) if exceptions are enabled.
#if EASTL_EXCEPTIONS_ENABLED
	EATEST_VERIFY(emcA.mStatus == true);
#else
	EATEST_VERIFY(emcA.mStatus == false);
#endif
	EA_UNUSED(emcB);

	except_move_no_copy emncA;
	except_move_no_copy emncB =
		eastl::move_if_noexcept(emncA);  // emncB should be constructed via except_move_no_copy(except_move_no_copy&&)
	EATEST_VERIFY(emncA.mStatus == false);
	EA_UNUSED(emncB);
#endif

	return nErrorCount;
}

static int TestUtilityIntegerSequence()
{
	using namespace eastl;
	int nErrorCount = 0;
#if EASTL_VARIADIC_TEMPLATES_ENABLED
// Android clang chokes with an internal compiler error on make_integer_sequence
#if !defined(EA_PLATFORM_ANDROID)
	EATEST_VERIFY((integer_sequence<int, 0, 1, 2, 3, 4>::size() == 5));
	EATEST_VERIFY((make_integer_sequence<int, 5>::size() == 5));
#endif
	EATEST_VERIFY((index_sequence<0, 1, 2, 3, 4>::size() == 5));
	EATEST_VERIFY((make_index_sequence<5>::size() == 5));
#endif  // EASTL_VARIADIC_TEMPLATES_ENABLED

	return nErrorCount;
}

///////////////////////////////////////////////////////////////////////////////
// TestUtility
//
int TestUtility()
{
	int nErrorCount = 0;

	nErrorCount += TestUtilityPair();
	nErrorCount += TestUtilityRelops();
	nErrorCount += TestUtilitySwap();
	nErrorCount += TestUtilityMove();
	nErrorCount += TestUtilityIntegerSequence();

	return nErrorCount;
}
