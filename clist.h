#pragma once
#include <mutex>


std::mutex g_num_mutex;
//std::lock_guard<std:mutex>lock(g_num_mutex);
/// TODO: complete this implementation of a thread-safe (concurrent) sorted
/// linked list of integers
class clist
{
	/// a Node consists of a value and a pointer to another node
	struct Node
	{
		int value;
		Node* next;
	  Node(): value(0), next(NULL) {
	  }
	};

	/// The head of the list is referenced by this pointer
  Node* head=new Node();

public:
	clist(int)
	: head(NULL)
	{}
  Node* create_Node(int insert){
    //printf("%d\n", insert);
    Node *a=new Node();
    a->value=insert;
    a->next=NULL;
    return a;

  }
	/// insert *key* into the linked list if it doesn't already exist; return
	/// true if the key was added successfully.
	bool insert(int key)
	{
  
	   g_num_mutex.lock();
	 
	    Node *a=create_Node(key);
	 
	 
	   if(head){
	 
	    if(key<head->value){
	      /*     Node* temp=head;
	      head->value=a->value;
	      head->next=temp;*/
	      a->next=head;
	      head=a;

	      g_num_mutex.unlock();
	      return true;
	      
	    }
	     Node* start=head;
	   
	     printf("Beggining new list %d\n", a->value);
	     while(start->next){
	       printf("%d\n", start->value);
	 
	      if(start->next && start->next->value>key){
		a->next=start->next;
	        start->next=a;
		g_num_mutex.unlock();
		return true;
	      }
	      start=start->next;
	   
	     }
	     start->next=a;
	     g_num_mutex.unlock();
	     return true;
	   

	   }
	   else{

	    
	      
	      
	     printf("Beggining new list %d\n", a->value); 


	    head=a;
	   
	    g_num_mutex.unlock();
	    return true;
	 
	   
	   }
	}
	
	/// remove *key* from the list if it was present; return true if the key
	/// was removed successfully.
	bool remove(int key)
	{
	  
	  g_num_mutex.lock();
	  printf("we are removing %d", key);
	  Node* a;
	  Node* RemovedNode;
	  // if(head){
	    if(head->value==key){
	      
	      
	      while(head->value==key){
		
		
		
		
		Node *temp=head;
		head=head->next;
		delete temp;
		
	     }
	    
	    /*else{
		delete head;
		}*/
	 
	      g_num_mutex.unlock();
	      return true;
	      
		

	     
	    }
	    a=head;
	    
	    while(a->next){
	       printf("value of a is %d\n", a->value);
	      //printf("value of a->next is %d\n", a->next->value);
		if(a->value>key){
		  g_num_mutex.unlock();
		  return false;
		}
		if(a->next->value==key){
		    Node* RemovedNode=a->next;


		    printf("value of RemovedNode is %d\n", RemovedNode->value);
		    while(RemovedNode->value==key && RemovedNode->next){
		      Node* temp=RemovedNode;
		      printf("value of RemovedNode is %d\n", RemovedNode->value);
		      RemovedNode=RemovedNode->next;
		      delete temp;
		     
		    }
		  
		 
		    a->next=RemovedNode;
		    if(RemovedNode->value==key){
		      a->next=NULL;
		      delete RemovedNode;
		    }
		    g_num_mutex.unlock();
		    return true;
		}
		

		   
		     a=a->next;
		   

	    }
	    //delete RemovedNode;
		  g_num_mutex.unlock();
		  return false;
	}
	       
	 
		 
		

	   
	       
	


  
	/// return true if *key* is present in the list, false otherwise
	bool lookup(int key) const
	{
	     g_num_mutex.lock();
	     
	     
	     if(head->value==key){
	       g_num_mutex.unlock();
	       return true;
	     }
	     
	       
	       Node* start=head;
	       while(start->next){
		 if(start->value==key){
		   g_num_mutex.unlock();
		   return true;
		 }
		 start=start->next;
	       

	       }
	       g_num_mutex.unlock();
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
