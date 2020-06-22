#include "stdafx.h"
#include "../StringList/StringList.h"

using namespace std;

struct EmptyStringList
{
	CStringList list;
};

BOOST_FIXTURE_TEST_SUITE(String_list, EmptyStringList)
	BOOST_AUTO_TEST_CASE(has_a_default_constructor)
	{
		BOOST_CHECK_EQUAL(list.GetSize(), 0);
	}
	BOOST_AUTO_TEST_CASE(has_a_copy_constructor)
	{
		CStringList list;
		list.PushBack("first");
		list.PushBack("second");
		CStringList copy(list);
		BOOST_CHECK(list == copy);
	}
	BOOST_AUTO_TEST_CASE(has_a_copy_operator)
	{
		CStringList list;
		list.PushBack("first");
		list.PushBack("second");
		CStringList copy = list;
		BOOST_CHECK(list == copy);
	}
	BOOST_AUTO_TEST_CASE(can_be_moved)
	{
		CStringList list;
		list.PushBack("first");
		list.PushBack("second");
		CStringList copy(list);
		CStringList newList = move(list);
		BOOST_CHECK(copy == newList);
		BOOST_CHECK(list.GetSize() == 0);
	}
	BOOST_AUTO_TEST_SUITE(after_adding_a_string_via_PushBack_method)
		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.GetSize();
			list.PushBack("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			list.PushBack("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_method)
		{
			list.PushBack("hello");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
			list.PushBack("goodbye");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "goodbye");
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetFrontElement_method)
		{
			list.PushBack("hello");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
			list.PushBack("goodbye");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_first_element)
		{
			list.PushBack("hello");
			auto iter = list.begin();
			BOOST_CHECK_EQUAL(addressof(*iter), addressof(list.GetFrontElement()));
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_reverse_iteratir_to_first_element)
		{
			list.PushBack("hello");
			auto iter = list.rbegin();
			BOOST_CHECK_EQUAL(addressof(*iter), addressof(list.GetBackElement()));
		}	
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(after_adding_a_string_via_PushFront_method)
		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.GetSize();
			list.PushFront("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			list.PushFront("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_method)
		{
			list.PushFront("hello");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
			list.PushFront("goodbye");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetFrontElement_method)
		{
			list.PushFront("hello");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
			list.PushFront("goodbye");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "goodbye");
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_first_element)
		{
			list.PushFront("hello");
			auto iter = list.begin();
			BOOST_CHECK_EQUAL(addressof(*iter), addressof(list.GetFrontElement()));
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_reverse_iteratir_to_first_element)
		{
			list.PushFront("hello");
			auto iter = list.rbegin();
			BOOST_CHECK_EQUAL(addressof(*iter), addressof(list.GetBackElement()));
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(Insert_method)
		BOOST_AUTO_TEST_CASE(can_insert_at_the_beginning_of_empty_list)
		{
			list.Insert(list.begin(), "hello");
			BOOST_CHECK_EQUAL(list.GetSize(), 1);
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
		}
		BOOST_AUTO_TEST_CASE(can_insert_at_the_beginning_of_the_non_empty_list)
		{
			list.PushBack("goodbye");
			list.Insert(list.begin(), "hello");
			BOOST_CHECK_EQUAL(list.GetSize(), 2);
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "goodbye");
		}
		BOOST_AUTO_TEST_CASE(can_insert_at_the_middle_of_the_list)
		{
			list.PushBack("first");
			list.PushBack("third");
			auto iter = list.begin();
			list.Insert(++iter, "second");
			CStringList expected;
			expected.PushBack("first");
			expected.PushBack("second");
			expected.PushBack("third");
			BOOST_CHECK(list == expected);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(iterators)
		BOOST_AUTO_TEST_CASE(iterator_can_be_incrementing_and_decreasing)
		{
			list.PushBack("first");
			list.PushBack("second");
			auto iter = list.begin();
			BOOST_CHECK_EQUAL(*iter, "first");
			++iter;
			BOOST_CHECK_EQUAL(*iter, "second");
			--iter;
			BOOST_CHECK_EQUAL(*iter, "first");
		}
		BOOST_AUTO_TEST_CASE(reverse_iterator_can_be_incrementing_and_decreasing)
		{
			list.PushBack("first");
			list.PushBack("second");
			auto iter = list.rbegin();
			BOOST_CHECK_EQUAL(*iter, "second");
			--iter;
			BOOST_CHECK_EQUAL(*iter, "first");
			++iter;
			BOOST_CHECK_EQUAL(*iter, "second");
		}	
		BOOST_AUTO_TEST_CASE(can_be_checked_for_equality)
		{
			list.PushBack("first");
			list.PushBack("second");
			auto iter1 = list.begin();
			auto iter2 = list.rbegin();
			BOOST_CHECK(!(*iter1 == *iter2));
			++iter1;
			BOOST_CHECK(*iter1 == *iter2);
		}
		BOOST_AUTO_TEST_CASE(can_be_checked_for_inequality)
		{
			list.PushBack("first");
			list.PushBack("second");
			auto iter1 = list.begin();
			auto iter2 = list.rbegin();
			BOOST_CHECK(*iter1 != *iter2);
			++iter1;
			BOOST_CHECK(!(*iter1 != *iter2));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(cant_get_back_element_from_empty_list)
	{
		BOOST_CHECK_THROW(list.GetBackElement(), exception);
	}
	BOOST_AUTO_TEST_CASE(cant_get_front_element_from_empty_list)
	{
		BOOST_CHECK_THROW(list.GetFrontElement(), exception);
	}

	struct StringList : EmptyStringList
	{
		struct StringList()
		{
			list.PushBack("first");
			list.PushBack("second");
			list.PushBack("third");
		};
	};

	BOOST_FIXTURE_TEST_SUITE(Several_nodes_string_list, StringList)
		BOOST_AUTO_TEST_CASE(sting_lists_can_be_checked_for_equality)
		{
			CStringList copy;
			copy.PushBack("first");
			copy.PushBack("second");
			copy.PushBack("third");
			BOOST_CHECK(list == copy);
			CStringList notCopy;
			copy.PushBack("first");
			copy.PushBack("hello");
			copy.PushBack("third");
			BOOST_CHECK(!(list == notCopy));
		}
		BOOST_AUTO_TEST_CASE(sting_lists_can_be_checked_for_inequality)
		{
			CStringList notCopy;
			notCopy.PushBack("first");
			notCopy.PushBack("hello");
			notCopy.PushBack("third");
			BOOST_CHECK(list != notCopy);
			CStringList copy;
			copy.PushBack("first");
			copy.PushBack("second");
			copy.PushBack("third");
			BOOST_CHECK(!(list != copy));
		}
		BOOST_AUTO_TEST_SUITE(deletion)
			BOOST_AUTO_TEST_CASE(can_delete_an_item_from_the_beginning_of_the_list)
			{
				auto iter = list.begin();
				list.Delete(iter);
				BOOST_CHECK(list.GetSize() == 2);
				CStringList expected;
				expected.PushBack("second");
				expected.PushBack("third");
				BOOST_CHECK(list == expected);
			}
			BOOST_AUTO_TEST_CASE(can_delete_an_item_from_the_middle_of_the_list)
			{
				auto iter = list.begin();
				++iter;
				list.Delete(iter);
				BOOST_CHECK(list.GetSize() == 2);
				CStringList expected;
				expected.PushBack("first");
				expected.PushBack("third");
				BOOST_CHECK(list == expected);
			}
			BOOST_AUTO_TEST_CASE(can_delete_an_item_when_list_with_one_item)
			{
				CStringList oneNodeList;
				oneNodeList.PushBack("first");
				auto iter = oneNodeList.begin();
				oneNodeList.Delete(iter);
				BOOST_CHECK(oneNodeList.GetSize() == 0);
			}
			BOOST_AUTO_TEST_CASE(cant_delete_an_item_from_an_empty_list)
			{
				CStringList emptyList;
				auto iter = emptyList.begin();
				BOOST_CHECK_THROW(emptyList.Delete(iter), exception);
			}
			BOOST_AUTO_TEST_CASE(cant_delete_an_item_from_the_end_of_the_list)
			{
				auto iter = list.end();
				BOOST_CHECK_THROW(list.Delete(iter), exception);
			}
			BOOST_AUTO_TEST_CASE(can_delete_all_items_from_the_list_via_Clear_method)
			{
				list.Clear();
				BOOST_CHECK(list.GetSize() == 0);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()