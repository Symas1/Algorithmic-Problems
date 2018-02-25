#include <assert.h>
#include <vector>

#include "list.h"
using namespace std;

void check_search();
void check_insert_after();
void check_delete_after();
void compare_list(shared_ptr<List_node<int>> L, const vector<int>& vec);

void main()
{
	check_search();
	check_insert_after();
	check_delete_after();
	system("pause");
}

void check_search()
{
	shared_ptr<List_node<int>> L;
	L = make_shared<List_node<int>>(List_node<int>{
		2, make_shared<List_node<int>>(List_node<int>{
			4, make_shared<List_node<int>>(List_node<int>{3, nullptr})})});
	assert(L == search_list(L, 2));
	assert(L->next == search_list(L, 4));
	assert(L->next->next == search_list(L, 3));
	assert(nullptr == search_list(L, 100));
}

void check_insert_after()
{
	shared_ptr<List_node<int>>L = make_shared<List_node<int>>(List_node<int>{
		1, make_shared<List_node<int>>(List_node<int>{
			3, make_shared<List_node<int>>(List_node<int>{5, nullptr}) }) });
	compare_list(L, { 1,3,5 });
	insert_after(L, make_shared<List_node<int>>(List_node<int>{ 2,nullptr }));
	compare_list(L, { 1,2,3,5 });
	insert_after(L->next->next, make_shared<List_node<int>>(List_node<int>{ 4, nullptr}));
	compare_list(L, { 1,2,3,4,5 });
	insert_after(L->next->next->next->next, make_shared<List_node<int>>(List_node<int>{ 6, nullptr}));
	compare_list(L, { 1,2,3,4,5,6 });
}

void check_delete_after()
{
	shared_ptr<List_node<int>>L = make_shared<List_node<int>>(List_node<int>{
		1, make_shared<List_node<int>>(List_node<int>{
			3, make_shared<List_node<int>>(List_node<int>{5, nullptr}) }) });
	insert_after(L, make_shared<List_node<int>>(List_node<int>{ 2, nullptr }));
	insert_after(L->next->next, make_shared<List_node<int>>(List_node<int>{ 4, nullptr}));
	delete_after(L);
	compare_list(L, { 1,3,4,5 });
	delete_after(L);
	compare_list(L, { 1,4,5 });
	delete_after(L);
	compare_list(L, { 1,5 });
	delete_after(L);
	compare_list(L, { 1 });
}

void compare_list(shared_ptr<List_node<int>>L, const vector<int>& vec)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		assert(L->data == vec[i]);
		L = L->next;
	}
	assert(!L);
}