#include "clist.h"
#pragma once

#include <vector>
/// TODO: complete this implementation of a thread-safe (concurrent) hash
///       table of integers, implemented as an array of linked lists.  In
///       this implementation, each list should have a "sentinel" node that
///       contains the lock, so we can't just reuse the clist
///       implementation

class shash
{
    struct SNode{
      std::mutex g_num_mutex;
      clist* a=new clist(0);
    };

    int num=0;
    SNode* bucketlist;

    public:
  shash(unsigned _buckets): num(_buckets)
  	{
	 bucketlist=new SNode[_buckets];
	 //printf("%d\n", _buckets);
	 
	  
  	}

   
          
        /// insert *key* into the appropriate linked list if it doesn't already
	/// exist; return true if the key was added successfully.
	bool insert(int key)
	{
	  int b = key % num;
	  bool insert=true;
	  bucketlist[b].g_num_mutex.lock();
	  insert=(bucketlist[b].a)->insert(key);
	  bucketlist[b].g_num_mutex.unlock();
	  //printf("%s\n", insert ? "true" : "false" );
	  return insert;
	  //printf("%d\n", num);
	  /*      printf("%d\n", num);	  
	        int b = key % num;
		printf("%d\n", num);*/
		/*	bucketlist[b].g_num_mutex.lock();
	        bucketlist[b].(*a).insert(key);
		bucketlist[b].g_num_mutex.unlock();*/
		
		
		
	}
	/// remove *key* from the appropriate list if it was present; return true
	/// if the key was removed successfully.
	bool remove(int key)
	{
	        bool remove=true;
	        int b = key % num;
		bucketlist[b].g_num_mutex.lock();
		remove=(bucketlist[b].a)->remove(key);
		bucketlist[b].g_num_mutex.unlock();
	        
		return remove;
	}
	/// return true if *key* is present in the appropriate list, false
	/// otherwise
	bool lookup(int key) const
	{
	  bool lookup=true;
	  int b = key % num;
	  bucketlist[b].g_num_mutex.lock();
	  lookup=(bucketlist[b].a)->lookup(key);
	  bucketlist[b].g_num_mutex.unlock();

	  return lookup;
	  
	}

	//The following are not tested by the given tester but are required for grading
	//No locks are required for these.

	//This refers to the number of buckets not the total number of elements.
	size_t getSize() const
	{
		return 0;
	}

	//This refers to the number of elements in a bucket, not the sentinel node.
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
