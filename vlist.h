
//Gutierrez,jesus
//jgutierrez

// The following prevent this file from being included more than once
#ifndef Vlist_H
#define Vlist_H
#include "video.h"

#include <string>

using namespace std;


class Vlist
{
  private:
	 class Node
     {

        public:
          Node(Video *video_ptr, Node *next)
          {m_video_ptr = video_ptr; m_next = next;}
          Video *m_video_ptr;
          Node *m_next;
     };
     Node *m_head;
	

    public:
    	Vlist();//constructor

    	~Vlist();
   		void insert(Video *videoptr);
   		bool check_duplicates(string title);
   		bool lookup(string lookup_video);
   		bool remove(string remove_video);
   		int length();
      void print();
     
      void quickSort( Node **headRef,string sort_cri);
   

      Node* partition( Node *head,  Node *end,  Node **newHead,  Node **newEnd,string sort_cri);
      Node* quickSortRecur( Node *head,  Node *end,string sort_cri);
      Node* sort_by_length();
      Node* sort_by_rating();
  
	  
}; // don't forget this ;


// part of the mechanism that prevents this file from being included multiple times
#endif
