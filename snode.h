#pragma once
#include <vector>
#include "clist.h"
#include "Node.h"


//static std::mutex newmutex;
static int insertcount=0;


class snode{
  //mutable std::mutex newmutex;
  
  public:
    
  mutable std::mutex newmutex;
  Node *listptr;
  

  Node* create_Node(int insert){
        
    Node *a=new Node();
    a->value=insert;
    a->next=NULL;
    return a;

  }
  
  snode(): listptr(NULL) {
    // printf("called this\n");
  }

     snode(snode &&other){
       printf("called this\n");
     //std::lock_guard<std::mutex> lock(newmutex);
   

     }


  void setlistptr(clist *a){
    
    this->listptr=a->head;
  }

  bool insert(int key){
    newmutex.lock();
    insertcount=insertcount+1;
    //  printf("This is insercount %d\n", insertcount);
    // printf("value we are inserting %d\n", key);
   
    Node *a=create_Node(key);
    //  printf("reached here\n");
   
    
    if(listptr){

      if(key<listptr->value){

	a->next=listptr;
	listptr=a;
	//  printf("new value of listptr is %d\n", listptr->value);

	newmutex.unlock();
	return true;
      }

      Node *start=listptr;
      while(start->next){


         if(start->value==key){
	   //printList();
	   // printf("value of start is key %d\n", start->value);
	   newmutex.unlock();
	   return false;
	 }
	 else if (start->next->value>key){
	   // printf("value of start is %d\n", start->value);
	   //printf("value of start's next is %d\n", start->next->value);
	   a->next=start->next;
	   start->next=a;
	   //printf("new value of start's next is %d\n",
	   //start->next->value);
	   //printList();
	   newmutex.unlock();
	   return true;
	 }
	 //printf("value of start is %d\n", start->value);
	 start=start->next;
	 
      }
      //printf("reached end of list %d\n", start->value);

      if(start->value==key){
	//printList();
	newmutex.unlock();
	return false;
      }
      
      start->next=a;
      ///printList();  
      newmutex.unlock();
      return true;
    }
      //insert=(listptr->insert(key));
      //newmutex.unlock();
      //return insert;

  
	else{

	  // printf("no head");
	  listptr=a;
	  //printList();
	  newmutex.unlock();
	  return true;
	}
    
  }
  bool remove(int key){
     newmutex.lock();
     //printf("we are removing %d\n", key);
     Node *start=listptr;

     
     if(listptr){
       if(listptr->value==key){
	 // printf("value of head is %d\n", listptr->value);
	 if(listptr->next){
	   listptr=listptr->next;
	   //printf("new value of head is %d\n", listptr->value);
	 }
	 else{
	   listptr=NULL;
	 }
	 //printList();
	 newmutex.unlock();
	 return true;
       }
       while(start->next){
	 
	 
	 if(start->value>key){
	   //  printf("value of start is greater than key %d\n",
	   //  start->value);
	   //printList();
	   newmutex.unlock();
	   return false;
	 }
	 else if(start->next->value==key){
	   Node *RemovedNode=start->next;
	   //printf("value of start is %d\n", start->value);
	   //printf("value of start->next is %d\n", start->next->value);
	   if(RemovedNode->next){
	     start->next=RemovedNode->next;
	     //printf("new value of start->next is %d\n", start->next->value);
	   }
	   else{
	     start->next=NULL;
	   }
	   //printList();
	   newmutex.unlock();
	   return true;
	 }
	 //printf("value of start is %d\n", start->value);
	 start=start->next;
	
       }
       
       //printf("reached end of list. value of start is %d\n",
       //start->value);
       //printList();
       newmutex.unlock();
       return false;
     }
     else
       {
	 //printList();
	 newmutex.unlock();
	 return false;
       }
    
   
   
    
  }

  bool lookup(int key) const{
    newmutex.lock();
    //printf("we are looking up %d\n", key); 
    if(listptr){
      Node *start=listptr;
      while(start){
	if(start->value==key){
	  //printf("found key of %d\n", start->value);
	  newmutex.unlock();
	  return true;
	}
	else if(start->value>key){
	  // printf("value of start is %d\n", start->value);
	  newmutex.unlock();
	  return false;

       }
	//  printf("value of start is %d\n", start->value);
	start=start->next;
      }
      
      //printf("reached end of list\n");
      newmutex.unlock();
      return false;
	
    }
    else{
      newmutex.unlock();
      return false;

    }
  }



  void printList(){
    Node *begin=listptr;
    while(begin->next){
      printf("%d ", begin->value);
      begin=begin->next;

    }
   
    printf("%d\n", begin->value);

  }
  
     //newmutex.lock();
    //bool lookup=true;
    //lookup=(listptr->lookup(key));
    //newmutex.unlock();
    //return lookup;
    

    //}

};
