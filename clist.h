#pragma once
#include "Node.h"
#include <mutex>


std::mutex g_num_mutex;
//std::lock_guard<std:mutex>lock(g_num_mutex);
/// TODO: complete this implementation of a thread-safe (concurrent) sorted
/// linked list of integers
class clist
{
	/// a Node consists of a value and a pointer to another node
  /*	struct Node
		{
		int value;
		Node* next;
	  Node(): value(0), next(NULL) {
	  }
	  };*/

	/// The head of the list is referenced by this pointer
  //  Node* head=new Node();

public:
  /*      struct Node
	 {
	   int value;
	   Node* next;
	   Node(): value(0), next(NULL) {
	   }
	   };*/
        Node* head;
        clist()
	: head(NULL)
        {}  
	  
	clist(int)
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
	 
	   g_num_mutex.lock();
	   //printf("value we are inserting %d\n", key);
	   Node *a=create_Node(key);
	 
	 
	   if(head){
	   
	     if(key<head->value){
	   
	   
	       // printf("value of head is %d\n", head->value);
	      a->next=head;
	      head=a;
	      // printf("new value of head is %d\n", head->value);
	      g_num_mutex.unlock();
	      return true;
	      
	     }
	    Node* start=head;
	   
	  
	    while(start->next){
	      //printf("value of start %d\n", start->value);
	       if(start->value==key){
		
		 g_num_mutex.unlock();
		 return false;
	       }
	       else if(start->next->value>key){
		 //	printf("value of start is %d\n", start->value);
		 //printf("value of start's next is %d\n", start->next->value);
		a->next=start->next;
	        start->next=a;
		g_num_mutex.unlock();
		return true;
	      }
	       // printf("value of start %d\n", start->value); 
	      start=start->next;
	   
	    }
	   	   
	    //    printf("value of start is %d\n",start->value);
	     if(start->value==key){
	      
	       g_num_mutex.unlock();
	       return false;
	     }
	     start->next=a;
	     g_num_mutex.unlock();
	     return true;
	   

	   }
	   else{

	    
	      
	      
	     //printf("Beggining new list %d\n", a->value); 


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
	  //printf("value we are removing %d\n", key);
	  if(!head){
	    g_num_mutex.unlock();
	    return false;
	  }
	  Node *currentNode=head;

	  if(currentNode->value == key){
	    // printf("Removing head \n");
	    if(head->next){
	       head=currentNode->next;
	       //printf("New value of head is %d\n", head->value);
	    }
	    else{
	      head=NULL;
	    }
	  
	    g_num_mutex.unlock();
	    return true;
	  }
	  
		 
	   
	    
	  while(currentNode->next){
	        
	    //   printf("value in list is %d\n", currentNode->value);
		if(currentNode->value>key){
		  // printf("value %d is greater than key\n", currentNode->value);
		  g_num_mutex.unlock();
		  return false;
		}

		if(currentNode->next->value==key){
		    Node* RemovedNode=currentNode->next;
		    //printf("Removing value %d\n", currentNode->next);
		    if(RemovedNode->next){
		      currentNode->next=RemovedNode->next;
		    }
		    else{
		      currentNode->next=NULL;
		    }
		      // delete RemovedNode;
		    g_num_mutex.unlock();
		    return true;
		}
		
		    
		// printf("value of currentNode is %d\n", currentNode->value);
		     currentNode=currentNode->next;
		     

	  }

	          
		  g_num_mutex.unlock();
		  return false;
	}
	       
	 
		 
		

	   
	       
	


  
	/// return true if *key* is present in the list, false otherwise
	bool lookup(int key) const
	{
	       
	       g_num_mutex.lock();
	       if(!head){
		 g_num_mutex.unlock();
		 return false;
	       }
	       
	     
	       Node *n=head;
	       while(n->next)
		 {
		  
		   
		   if(n->value == key)
		     {
		       g_num_mutex.unlock();
		       return true;
		     }
		   else if(n->value > key){
		     g_num_mutex.unlock();
		     return false;
		   }
		   n = n->next;
	       }

	       if(n->value == key){
		 g_num_mutex.unlock();
		 return true;
	       }
	       g_num_mutex.unlock();
	       return false;
	}
	     
	       /*   if(head->value==key){
	       g_num_mutex.unlock();
	       return true;
	     }
	     
		     
	       Node* start=head;
	       while(start->next){
		
		 if(start->value==key){
		
		   g_num_mutex.unlock();
		 
		   return true;
		 }
		 if(start->value>key){
		   g_num_mutex.unlock();
		 
		   return false;
		 }
		
		 start=start->next;
	       

	       }

	       if(start->value==key){
		 g_num_mutex.unlock();
		 return true;
	       }
	       g_num_mutex.unlock();
	       return false;*/
	       
	     
	   
	  
	
	
	
	  
	   
	     
	
	


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
