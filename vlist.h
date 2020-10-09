// Project 3
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
    	Vlist();
    	~Vlist();
   		void insert(Video *videoptr);
   		bool check_duplicates(string title);
   		bool lookup(string lookup_video);
   		bool remove(string remove_video);
   		int length();
        void print();
  
	  
}; // don't forget this ;


// part of the mechanism that prevents this file from being included multiple times
#endif
