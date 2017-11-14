#pragma once
#include <vector>
#include "clist.h"
#include "Node.h"

class snode2{
  //mutable std::mutex newmutex;
  // std::unique_ptr<std::mutex> newmutex = std::make_unique<std::mutex>();
  public:

  mutable std::mutex newmutex;
  Node *listptr;

  Node* create_Node(int insert){
    Node *a=new Node();
    a->value=insert;
    a->next=NULL;
    return a;
  }
  
  snode2(): listptr(NULL) {
    std::lock_guard<std::mutex> (this->newmutex); 
  }
 
 snode2(const snode2& a){
   
    std::lock_guard<std::mutex> (a.newmutex);
     listptr=a.listptr;
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
	 if(start->value==key){
	 
	   newmutex.unlock();
	   // printf("value of start is %d\n", start->next);
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
     
       if(start->value==key){
	 newmutex.unlock();
	 return false;
       }
       start->next=a;
       newmutex.unlock();
       return true;
    }
    else{
      listptr=a;
      newmutex.unlock();
      return true;
     }
  }
  bool remove(int key){
     newmutex.lock();
     Node* start=listptr;
     if(listptr){
       if(listptr->value==key){
	 if(listptr->next){ //set listptr to next if has a next
	   listptr=listptr->next;
	 }
	 else{
	   listptr=NULL;
	 }
	 newmutex.unlock();
	 return true;
       }
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
       else{
	 newmutex.unlock();
	 return false;

       }
       /* bool remove=true;
    remove=(listptr->remove(key));
    newmutex.unlock();
    return remove;*/
     }
     

  bool lookup(int key) const{
    newmutex.lock();
    //printf("value we are looking for is %d\n", key);
    if(listptr){
      Node *start=listptr;
      while(start){
	//printf("value of start is %d\n", start->value);
	if(start->value==key){
	  //printf("key is %d\n", start->value);
	  newmutex.unlock();
	  return true;
	}
	else if(start->value>key){
	  // printf("leaving list at %d\n", start->value);
	  newmutex.unlock();
	  return false;
	}
	start=start->next;
      }
      /*     if(start->value==key){
	newmutex.unlock();
	return true;
	}*/
      newmutex.unlock();
      return false;

    }
    else{
      newmutex.unlock();
      return false;

    }
    /* newmutex.lock();
    bool lookup=true;
    lookup=(listptr->lookup(key));
    newmutex.unlock();
    return lookup;*/
    

  }

};
