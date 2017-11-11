#pragma once
#include <pthread.h>
/// TODO: complete this implementation of a thread-safe (concurrent) sorted
/// linked list of integers, which should use readers/writer locking.
class rwlist
{
        mutable pthread_rwlock_t lock_rw = PTHREAD_RWLOCK_INITIALIZER;
	/// a node consists of a value and a pointer to another node
	struct Node
	{
		int value;
		Node* next;
	};

	/// The head of the list is referenced by this pointer
	Node* head;

public:
	rwlist(int)
	: head(NULL)
	{}


     Node* create_Node(int insert){
	  Node *a=new Node();
	  a->value=insert;
	  a->next=NULL;
	  return a;
	    
	}   
	  
	/// insert *key* into the linked list if it doesn't already exist; return
	/// true if the key was added successfully.
	bool insert(int key)
	{
	       pthread_rwlock_wrlock(&lock_rw);
	       Node *a=create_Node(key);
	       if(head){
		 if(key==head->value){
		   pthread_rwlock_unlock(&lock_rw);
		   return false;
		 }
		 if(key<head->value){
		   a->next=head;
		   head=a;
		   pthread_rwlock_unlock(&lock_rw);
		   return true;
		 }
	       
		 Node* start=head;
		 while(start->next){
		   if(start->next->value==key){
		     pthread_rwlock_unlock(&lock_rw);
		     return false;
		   }
		   //printf("value of start is %d\n", start->value);
		   else if(start->next && start->next->value>key){
		     // printf("value of start is %d\n", start->value);
		     a->next=start->next;
		     start->next=a;
		     pthread_rwlock_unlock(&lock_rw);
		     return true;
		   }
		   start=start->next;
		 }
		 start->next=a;
		 pthread_rwlock_unlock(&lock_rw);
		 return true;
	       }
	       else{
		 head=a;
		 pthread_rwlock_unlock(&lock_rw);
		 return true;
	       }
	}
	/// remove *key* from the list if it was present; return true if the key
	/// was removed successfully.
	bool remove(int key)
	{
	        pthread_rwlock_wrlock(&lock_rw);
		//printf("We are removing %d\n", key);
		Node* a;
		Node* RemovedNode;
		if(head->value==key){

		  while(head->value==key){
		    Node* temp=head;
		    head=head->next;
		    delete temp;
		  }
		  pthread_rwlock_unlock(&lock_rw);
		  return true;
		}
		a=head;
		while(a->next){
		  //printf("Removal list %d\n", a->value);
		  if(a->value>key){
		    pthread_rwlock_unlock(&lock_rw);
		    return false;
		  }
		  
		  if(a->next->value==key){
		    // printf("Removal list %d\n", a->value);
		    Node* RemovedNode=a->next;
		    while(RemovedNode->value==key && RemovedNode->next){
		      Node* temp=RemovedNode;
		      RemovedNode=RemovedNode->next;
		      delete temp;
		    }
		    a->next=RemovedNode;
		    if(RemovedNode->value==key){
		      a->next=NULL;
		      delete RemovedNode;

		    }
		    pthread_rwlock_unlock(&lock_rw);
		    return true;
		  }
		  a=a->next;
		}
		
		pthread_rwlock_unlock(&lock_rw);
		return false;
	}
	/// return true if *key* is present in the list, false otherwise
	bool lookup(int key) const
	{
	        pthread_rwlock_rdlock(&lock_rw);
		//printf("we are looking up %d\n", key);
		//bool lookup=false;
		if(head->value==key){
		  // printf("true\n");
		  pthread_rwlock_unlock(&lock_rw);
		  return true;
		}
	
	
		Node* start=head;
		
		while(start->next){
		  if(start->value==key){
		    // printf("true\n");
		    pthread_rwlock_unlock(&lock_rw);
		    return true;
		  }
		  if(start->value>key){
		    pthread_rwlock_unlock(&lock_rw);
		    // printf("false\n");
		    return false;
		  }
		  start=start->next;
		  //printf("value we see while looking up %d\n", start->value);
		}

		if(start->value==key){
		  pthread_rwlock_unlock(&lock_rw);                         
		    return true;
		  
		}
		pthread_rwlock_unlock(&lock_rw);
	
		return false;
	}

	//The following are not tested by the given tester but are required for grading
	//No locks are required for these.
	size_t getSize() const
	{
		return 0;
	}
	int getElement(size_t idx) const
	{
		return 0;
	}

	//These functions just need to exist, they do not need to do anything
	size_t getBucketSize(size_t bucket) const
	{
		return 0;
	}
	int getElement(size_t bucket, size_t idx) const
	{
		return 0;
	}
};
