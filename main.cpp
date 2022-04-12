#define BOOST_TEST_MODULE test_ranges_module

#include <ranges.h>

#include <vector>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_ranges_filters_suite)

BOOST_AUTO_TEST_CASE(test_ranges_filter)
{
    std::vector<int> v{3,1,4,6,7,5,8};
    std::vector<int> v_filtered;

    for(auto item: v | ranges::filter([](auto i){return i%2;}))
        v_filtered.push_back(item);

    BOOST_CHECK((v_filtered == std::vector<int>{3,1,7,5}));
}

BOOST_AUTO_TEST_CASE(test_ranges_drop)
{
    std::vector<int> v{3,1,4,6,7,5,8};
    std::vector<int> v_filtered;

    for(auto item: v | ranges::drop(2))
        v_filtered.push_back(item);

    BOOST_CHECK((v_filtered == std::vector<int>{4,6,7,5,8}));
}

BOOST_AUTO_TEST_CASE(test_ranges_take)
{
    std::vector<int> v{3,1,4,6,7,5,8};
    std::vector<int> v_filtered;

    for(auto item: v | ranges::take(3))
        v_filtered.push_back(item);

    BOOST_CHECK((v_filtered == std::vector<int>{3,1,4}));
}

BOOST_AUTO_TEST_CASE(test_ranges_reverse)
{
    std::vector<int> v{3,1,4,6,7,5,8};
    std::vector<int> v_filtered;

    for(auto item: v | ranges::reverse())
        v_filtered.push_back(item);

    BOOST_CHECK((v_filtered == std::vector<int>{8,5,7,6,4,1,3}));
}

BOOST_AUTO_TEST_CASE(test_ranges_2_filters_drop_filter)
{
    std::vector<int> v{3,1,4,6,7,5,8};
    std::vector<int> v_filtered;

    for(auto item: v | ranges::drop(3) | ranges::filter([](auto item){return item%2;}))
        v_filtered.push_back(item);

    BOOST_CHECK((v_filtered == std::vector<int>{7,5}));
}

BOOST_AUTO_TEST_CASE(test_ranges_2_filters_reverse_drop)
{
    std::vector<int> v{3,1,4,6,7,5,8};
    std::vector<int> v_filtered;

    for(auto item: v | ranges::reverse() | ranges::drop(3))
        v_filtered.push_back(item);

    BOOST_CHECK((v_filtered == std::vector<int>{6,4,1,3}));
}

BOOST_AUTO_TEST_SUITE_END()

//--------------------Same filters, only check for modification----------
BOOST_AUTO_TEST_SUITE(test_ranges_filters_modification_suite)

BOOST_AUTO_TEST_CASE(test_ranges_filter)
{
    std::vector<int> v{3,1,4,6,7,5,8};

    for(auto& item: v | ranges::filter([](auto i){return i%2;}))
        item = 99;

    BOOST_CHECK((v== std::vector<int>{99,99,4,6,99,99,8}));
}

BOOST_AUTO_TEST_CASE(test_ranges_drop)
{
    std::vector<int> v{3,1,4,6,7,5,8};

    for(auto &item: v | ranges::drop(2))
        item = 99;

    BOOST_CHECK((v == std::vector<int>{3,1,99,99,99,99,99}));
}

BOOST_AUTO_TEST_CASE(test_ranges_take)
{
    std::vector<int> v{3,1,4,6,7,5,8};

    for(auto &item: v | ranges::take(3))
        item = 99;

    BOOST_CHECK((v == std::vector<int>{99,99,99,6,7,5,8}));
}

BOOST_AUTO_TEST_CASE(test_ranges_2_filters_drop_filter)
{
    std::vector<int> v{3,1,4,6,7,5,8};

    for(auto &item: v | ranges::drop(3) | ranges::filter([](auto item){return item%2;}))
        item = 99;

    BOOST_CHECK((v == std::vector<int>{3,1,4,6,99,99,8}));
}

BOOST_AUTO_TEST_CASE(test_ranges_2_filters_reverse_drop)
{
    std::vector<int> v{3,1,4,6,7,5,8};

    for(auto &item: v | ranges::reverse() | ranges::drop(3))
        item = 99;

    BOOST_CHECK((v == std::vector<int>{99,99,99,99,7,5,8}));
}

BOOST_AUTO_TEST_SUITE_END()