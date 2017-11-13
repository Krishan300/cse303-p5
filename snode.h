#pragma once
#include <vector>
#include "clist.h"
#include "Node.h"
std::mutex newmutex;
class snode{
  //mutable std::mutex newmutex;
  
  public:
    
  //std::mutex g_num_mutex;
  Node *listptr;

  Node* create_Node(int insert){

    Node *a=new Node();
    a->value=insert;
    a->next=NULL;
    return a;

  }
  
  snode(): listptr(NULL) {
    
  }

  /*  snode(snode &&other){
    std::lock_guard<std::mutex> lock(other.mtx);
    listptr=std::move(other.listptr);

    }*/


  void setlistptr(clist *a){
    
    this->listptr=a->head;
  }

  bool insert(int key){
    newmutex.lock();
    // printf("we are inserting %d\n", key);
    Node *a=create_Node(key);
    
    Node *start=listptr;
    
    if(listptr){

      if(key<listptr->value){
	a->next=listptr;
	listptr=a;
	newmutex.unlock();
	return true;
      }
      
      while(start->next){

	// printf("value of start is %d\n", start->value);
         if(start->value==key){
	   newmutex.unlock();
	   return false;
	 }
	 else if (start->next->value>key){
	   a->next=start->next;
	   start->next=a;
	   newmutex.unlock();
	   return true;
	 }
	 start=start->next;
      }
      start->next=a;
      newmutex.unlock();
      return true;
    }
      //insert=(listptr->insert(key));
      //newmutex.unlock();
      //return insert;

  
	else{
	  
	  listptr=a;
	  newmutex.unlock();
	  return true;
	}
    
  }
  bool remove(int key){
     newmutex.lock();
     
     Node *start=listptr;
     
     if(listptr){
       while(start->next){
	
	 if(start->value>key){
	  
	   newmutex.unlock();
	   return false;
	 }
	 else if(start->next->value==key){
	   Node *RemovedNode=start->next;
	   if(RemovedNode->next){
	     start->next=RemovedNode->next;
	   }
	   else{
	     start->next=NULL;
	   }
	   newmutex.unlock();
	   return true;
	 }
	 start=start->next;
	
       }
       if(start->value==key){
	 
	 start=NULL;
	
	 newmutex.unlock();
	 return true;
       }
      
       newmutex.unlock();
       return false;
     }
     else
       {

	 newmutex.unlock();
	 return false;
       }
    
    // remove=(listptr->remove(key));
    //newmutex.unlock();
    
  }

  bool lookup(int key){
    newmutex.lock();
    if(listptr){
      Node *start=listptr;
      while(start){
	if(start->value==key){
	  newmutex.unlock();
	  return true;
	}
	else if(start->value>key){
	  newmutex.unlock();
	  return false;

       }
	start=start->next;
      }
      newmutex.unlock();
      return false;
	
    }
    else{
      newmutex.unlock();
      return false;

    }
  }
    //newmutex.lock();
    //bool lookup=true;
    //lookup=(listptr->lookup(key));
    //newmutex.unlock();
    //return lookup;
    

    //}

};
