#pragma once
#include <vector>
#include "clist.h"


class snode2{
  //mutable std::mutex newmutex;
  // std::unique_ptr<std::mutex> newmutex = std::make_unique<std::mutex>();
  public:
  //std::unique_ptr<std::mutex> newmutex = std::make_unique<std::mutex>();  
  mutable std::mutex newmutex;
  clist *listptr;

  snode2(): listptr(NULL) {
    
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
