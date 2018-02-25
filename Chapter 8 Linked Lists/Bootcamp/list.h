#ifndef LIST_H_
#define LIST_H_

#include <memory>

template<typename T>
struct List_node {
	T data;
	std::shared_ptr<List_node<T>>next;
};

std::shared_ptr<List_node<int>> search_list(std::shared_ptr<List_node<int>>L, int key)
{
	while (L && L->data != key)L = L->next;
	return L;
}

void insert_after(const std::shared_ptr<List_node<int>>&node, const std::shared_ptr<List_node<int>>& new_node)
{
	new_node->next = node->next;
	node->next = new_node;
}

void delete_after(const std::shared_ptr<List_node<int>>& node)
{
	node->next = node->next->next;
}

#endif // LIST_H_
