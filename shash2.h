#pragma once
#include "snode.h"
#include <vector>
/// TODO: complete this implementation of a thread-safe (concurrent) hash
///       table of integers, implemented as an array of linked lists.  In
///       this implementation, each list should have a "sentinel" node that
///       contains the lock, so we can't just reuse the clist implementation.
///       In addition, the API now allows for multiple keys on each
///       operation.
 class shash2
{
   std::vector<clist> buckets;
   int mynum=0;
   std::vector<snode>bucketlist;
  
public:

   mutable std::mutex newmutex;  
   
  /*shash2(unsigned _buckets)
    {}*/
   
  shash2(unsigned _buckets): mynum(_buckets), buckets(_buckets, clist(0)) //bucketlist(_buckets, snode2())
	{

	  bucketlist.resize(_buckets);
	  /* for(int i=0; i<_buckets;i++){
	    bucketlist[i]=snode2();
	    }*/
	  // bucketlist.resize(_buckets);
	  // snode2 a=snode2();
	  
	  // for(int i=0; i<_buckets; i++){
	    // a.setlistptr(&buckets[i]);
	  //  bucketlist[i].setlistptr(&buckets[i]);
	    // bucketlist[i](&a); //copy constructor
	  // }
	  
	}

	/// insert /num/ values from /keys/ array into the hash, and return the
	/// success/failure of each insert in /results/ array.
     void insert(int* keys, bool* results, int num)
       {
	 newmutex.lock();
	 bool insert=true;
	 for(int i=0; i< num; i++){
	  
	  
	   
	   int b= keys[i] % mynum;
	  
	  
	  
	   insert=bucketlist[b].insert(keys[i]);
	   results[i] = insert;
	  
	 }
	 newmutex.unlock();
	 
	 /*	 bool insert=true;
         int b = keys % num;
         insert=bucketlist[b].insert(key);
         return insert;*/
  /// insert /num/ values from /keys/ array into the\|        return insert;
	  
       }
	/// remove *key* from the list if it was present; return true if the key
	/// was removed successfully.
	void remove(int* keys, bool* results, int num)
	{
	  newmutex.lock();
	  bool ourremove=true;
	  
	  for(int i=0; i< num; i++){
	    int b= keys[i] % mynum;
	    ourremove=bucketlist[b].remove(keys[i]);
	    //printf("value of i is %d\n", i);
	    //printf("value of b is %d\n", b);
	    //printf("we are inserting %d\n", keys[i]);
	
	
	
	
	
	    results[i] = ourremove;
	  }
	  newmutex.unlock();
	}
	/// return true if *key* is present in the list, false otherwise
	void lookup(int* keys, bool* results, int num) const
	{
	  newmutex.lock();
	  bool ourlookup=true;
	  for(int i=0; i< num; i++){
	    int b= keys[i] % mynum;
	    ourlookup=bucketlist[b].lookup(keys[i]);
	
	    results[i] = ourlookup;
	  }
	  newmutex.unlock();

	}

	//The following are not tested by the given tester but are required for grading
	//No locks are required for these.

	//This refers to the number of buckets not the total number of elements.
	size_t getSize() const
	{
		return 0;
	}

	//This refers to the number of elements in a bucket, not the sentinel node.
	size_t getBucketSize() const
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
