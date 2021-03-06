#include "clist.h"
#include "Node.h"
#pragma once
#include<vector>

/// TODO: complete this implementation of a thread-safe (concurrent) hash
///       table of integers, implemented as an array of linked lists.
class chash
{
  /// The bucket list
     const std::vector<clist> buckets;
     int bNum = 0;

 public:
 chash(unsigned _buckets) : bNum(_buckets), buckets(_buckets, clist(0))
    {
      if(bNum<=0){
	printf("You need more than 1 bucket \n");
	exit(0);
      }
      // bNum=_buckets;
      // buckets= new clist[bNum];
    }


  /// insert *key* into the appropriate linked list if it doesn't already
  /// exist; return true if the key was added successfully.
  bool insert(int key)
  {
    int b = key % bNum;
    clist &castedlist=const_cast<clist&>(buckets[b]);
    return castedlist.insert(key);
    //return false;

    //return true;
  }
  /// remove *key* from the appropriate list if it was present; return true
  /// if the key was removed successfully.
  bool remove(int key)
  {
    int b = key % bNum;
    clist &castedlist=const_cast<clist&>(buckets[b]);
    return castedlist.remove(key);
    //return false;

  }
  /// return true if *key* is present in the appropriate list, false
  /// otherwise
  bool lookup(int key) //const
  {
    int b = key % bNum;
    clist &castedlist=const_cast<clist&>(buckets[b]);
    return castedlist.lookup(key);
    //return false;

  }

  //The following are not tested by the given tester but are required for grading
  //No locks are required for these.

  //This refers to the number of buckets not the total number of elements.
  size_t getSize() const
  {
    return 0;
  }
  size_t getBucketSize(size_t bucket) const
  {
    return 0;
  }
  int getElement(size_t bucket, size_t idx) const
  {
    return 0;
  }



  //These functions just need to exist, they do not need to do anything
  int getElement(size_t idx) const
  {
    return 0;
  }
};
