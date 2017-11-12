#pragma once
#include <vector>
#include "clist.h"

std::mutex newmutex;
class snode{
  //mutable std::mutex newmutex;
  
  public:
    
  //std::mutex g_num_mutex;
  clist *listptr;

  snode(): listptr(NULL) {
    
  }

  /*  snode(snode &&other){
    std::lock_guard<std::mutex> lock(other.mtx);
    listptr=std::move(other.listptr);

    }*/


  void setlistptr(clist *a){
   
    this->listptr=a;
  }

  bool insert(int key){
    newmutex.lock();
    bool insert=true;
    
    insert=(listptr->insert(key));
    newmutex.unlock();
    return insert;
    

  }
  bool remove(int key){
    newmutex.lock();
    bool remove=true;
    remove=(listptr->remove(key));
    newmutex.unlock();
    return remove;
  }

  bool lookup(int key){
    newmutex.lock();
    bool lookup=true;
    lookup=(listptr->lookup(key));
    newmutex.unlock();
    return lookup;
    

  }

};
