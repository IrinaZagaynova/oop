#include "stdafx.h"
#include "StringList.h"
#include <iostream>

int main()
{
	CStringList list;
	list.PushBack("first");
	list.PushBack("hello");
	list.PushBack("third");

	auto iter = list.begin();
	++iter;
	list.Insert(iter, "new");

	CStringList list1;
	list1.PushBack("first");
	list1.PushBack("new");
	list1.PushBack("third");

	if (list1 == list)
	{
		std::cout << "what";
	}

	return 0;
}
