#include "clist.h"
//#include "snode.h"
#pragma once
#include "snode.h"
#include <vector>
/// TODO: complete this implementation of a thread-safe (concurrent) hash
///       table of integers, implemented as an array of linked lists.  In
///       this implementation, each list should have a "sentinel" node that
///       contains the lock, so we can't just reuse the clist
///       implementation

class shash
{
     std::vector<clist> buckets;
    int num=0;
    std::vector<snode> bucketlist;
    public:
    shash(unsigned _buckets): num(_buckets), buckets(_buckets, clist(0)), bucketlist(_buckets, snode())
  	{
	 
         	 
	  /* for(int i=0; i<_buckets; i++){
          
	   bucketlist[i].setlistptr(&buckets[i]);
	   }*/
	  
	}
  

  /* shash(unsigned _buckets){
  }*/

   
          
        /// insert *key* into the appropriate linked list if it doesn't already
	/// exist; return true if the key was added successfully.
	bool insert(int key)
	{

	  int b = key % num;
	  //printf("%d\n", b);
	  
	  return bucketlist[b].insert(key);
	
	  
	 		
	}
	/// remove *key* from the appropriate list if it was present; return true
	/// if the key was removed successfully.
	bool remove(int key)
	{
	       
	       int b = key % num;
	       
	       return bucketlist[b].remove(key);
		
			  /*bucketlist[b].g_num_mutex.lock();
		remove=(bucketlist[b].listptr)->remove(key);
		bucketlist[b].g_num_mutex.unlock();*/
	        
		
	}
	/// return true if *key* is present in the appropriate list, false
	/// otherwise
	bool lookup(int key) 
	{
	  //bool lookup=true;
	  int b = key % num;
	  return bucketlist[b].lookup(key);
	  
	  
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
