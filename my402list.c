#include<stdio.h>
#include<stdlib.h>
#include"my402list.h"

//Returns the number of elements in the list. 
int  My402ListLength(My402List* myList)
{
	if(myList == NULL) return 0;
	return myList->num_members;
}

// Checks if list itself is empty
int PrerequisitesMet(My402List* myList)
{
	if(myList==NULL) return FALSE;
	return TRUE;
}

//Returns TRUE if the list is empty. Returns FALSE otherwise. 
int  My402ListEmpty(My402List* myList)
{
	if(myList->num_members == 0)
		return TRUE;
	return FALSE;
}

//If list is empty, just add obj to the list. Otherwise, add obj after Last(). 
//This function returns TRUE if the operation is performed successfully and returns FALSE otherwise.
int  My402ListAppend(My402List* myList, void* data)
{
	if(myList == NULL) return FALSE;
	
	My402ListElem* temp = (My402ListElem*) malloc(sizeof(My402ListElem));
	if(temp==NULL)
	{
		fprintf(stderr, "Failed to allocate memory\n");
		return FALSE;
	}

	temp->obj = data;
	
	My402ListElem* last = My402ListLast(myList);
	temp->next = &myList->anchor;
	myList->anchor.prev = temp;
	if(last == NULL)
	{
		temp->prev = &myList->anchor;
		myList->anchor.next = temp;
	}
	else
	{
		temp->prev = last;
		last->next = temp;
	}
	++myList->num_members;
	return TRUE;
}

//If list is empty, just add obj to the list. Otherwise, add obj before First(). 
//This function returns TRUE if the operation is performed successfully and returns FALSE otherwise. 
int  My402ListPrepend(My402List* myList, void* data)
{
	if(myList == NULL) return FALSE;
	
	My402ListElem* temp = (My402ListElem*) malloc(sizeof(My402ListElem));
	if(temp==NULL)
	{
		fprintf(stderr, "Failed to allocate memory\n");
		return FALSE;
	}

	temp->obj = data;
	
	My402ListElem* first = My402ListFirst(myList);
	temp->prev = &myList->anchor;
	myList->anchor.next = temp;
	if(first == NULL)
	{
		temp->next = &myList->anchor;
		myList->anchor.prev = temp;
	}
	else
	{
		first->prev = temp;
		temp->next = first;
	}
	++myList->num_members;
	return TRUE;
}


//Unlink and delete elem from the list. Please do not delete the object pointed to by elem and do not check if elem is on the list. 
void My402ListUnlink(My402List* myList, My402ListElem* elem)
{
	if(My402ListEmpty(myList))
	{
		printf("List is empty\n");
		return;
	}
	if(elem != NULL)
	{
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
		free(elem);
		--myList->num_members;
	}
	if(My402ListEmpty(myList))
	{
		myList->anchor.prev = NULL;
		myList->anchor.next = NULL;
	}
}

//Unlink and delete all elements from the list and make the list empty. 
//Please do not delete the objects pointed to be the list elements. 
void My402ListUnlinkAll(My402List* myList)
{
	if(My402ListEmpty(myList) == FALSE)
	{
		My402ListElem* cur = myList->anchor.next;
		while(cur!= &myList->anchor)
		{
			My402ListElem* next = cur->next;
			free(cur);
			cur = next;
		}
		myList->anchor.prev = NULL;
		myList->anchor.next = NULL;
		myList->num_members=0;
	}
}

//Insert obj between elem and elem->prev. If elem is NULL, then this is the same as Prepend(). 
//This function returns TRUE if the operation is performed successfully and returns FALSE otherwise. 
//Please do not check if elem is on the list. 
int  My402ListInsertBefore(My402List* myList, void* data, My402ListElem* elem)
{
	if(myList == NULL) return FALSE;

	if(elem == NULL)
	{
		return My402ListPrepend(myList, data);
	}

	My402ListElem* temp = (My402ListElem*) malloc(sizeof(My402ListElem));
	if(temp==NULL)
	{
		fprintf(stderr, "Failed to allocate memory\n");
		return FALSE;
	}

	temp->obj = data;

	My402ListElem* prev = elem->prev;
	elem->prev = temp;
	temp->next = elem;
	temp->prev = prev;
	prev->next = temp;
	++myList->num_members;
	return TRUE;
}

//Insert obj between elem and elem->next. If elem is NULL, then this is the same as Append(). 
//This function returns TRUE if the operation is performed successfully and returns FALSE otherwise. 
//Please do not check if elem is on the list. 
int  My402ListInsertAfter(My402List* myList, void* data, My402ListElem* elem)
{
	if(myList == NULL) return FALSE;
	
	if(elem == NULL)
	{
		return My402ListPrepend(myList, data);
	}

	My402ListElem* temp = (My402ListElem*) malloc(sizeof(My402ListElem));
	if(temp==NULL)
	{
		fprintf(stderr, "Failed to allocate memory\n");
		return FALSE;
	}

	temp->obj = data;

	My402ListElem* next = elem->next;
	elem->next = temp;
	temp->prev = elem;
	temp->next = next;
	next->prev = temp;
	++myList->num_members;
	return TRUE;
}

//Returns the first list element or NULL if the list is empty. 
My402ListElem *My402ListFirst(My402List* myList)
{
	if(My402ListEmpty(myList) == TRUE)
		return NULL;
	else
		return myList->anchor.next;
}

//Returns the last list element or NULL if the list is empty. 
My402ListElem *My402ListLast(My402List* myList)
{
	if(My402ListEmpty(myList) == TRUE)
		return NULL;
	else
		return myList->anchor.prev;
}

//Returns elem->next or NULL if elem is the last item on the list. Please do not check if elem is on the list. 
My402ListElem *My402ListNext(My402List* myList, My402ListElem* elem)
{
	if(My402ListEmpty(myList) == TRUE)
		return NULL;
	if(elem == NULL) return NULL;
	if(elem->next == &myList->anchor) return NULL;
	return elem->next;
}

//Returns elem->prev or NULL if elem is the first item on the list. Please do not check if elem is on the list. 
My402ListElem *My402ListPrev(My402List* myList, My402ListElem* elem)
{
	if(My402ListEmpty(myList) == TRUE)
		return NULL;

	if(elem == NULL) return NULL;
	if(elem->prev == &myList->anchor) return NULL;
	return elem->prev;
}

//Returns the list element elem such that elem->obj == obj. Returns NULL if no such element can be found. 
My402ListElem *My402ListFind(My402List* myList, void* data)
{
	if(My402ListEmpty(myList) == TRUE)
		return NULL;
	My402ListElem* cur = myList->anchor.next;
	while(cur->obj != data && cur != &myList->anchor)
	{
		cur = cur->next;
	}
	if(cur == &myList->anchor)
		return NULL;
	return cur;
}

//Initialize the list into an empty list. Returns TRUE if all is well and returns FALSE if there is an error initializing the list. 
int My402ListInit(My402List* myList)
{
	if(myList == NULL) 
	{
		myList = (My402List*) malloc(sizeof(My402List));
		if(myList == NULL)
		{
			fprintf(stderr, "Failed to allocate memory\n");
			return FALSE;
		}
	}

	myList->anchor.next = NULL;
	myList->anchor.prev = NULL;
	myList->num_members = 0;
	return TRUE;
}
