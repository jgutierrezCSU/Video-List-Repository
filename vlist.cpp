// Project 3
//Gutierrez,jesus
//jgutierrez

#include<iostream>
#include "vlist.h"
using namespace std;
//vlist function will remove video which was passed on from main
bool Vlist::remove(string remove_video)
{
  
  Node *ptr = m_head;
  //return false if list is empty  avoid seg fault
  if (ptr == NULL)
  {
    return false;
  }
  //go through linked list and find given video (remove_video)
  if(ptr != NULL && ptr->m_video_ptr->m_title  == remove_video)
  {
    Node *temp = m_head;
    Video *temp_videoptr1 = m_head->m_video_ptr;
    m_head = m_head->m_next;
    //delete temp pointer , avoid seg fault
    delete temp_videoptr1;
    delete temp;
  }
  else
  {
    while(ptr->m_next != NULL && ptr->m_next->m_video_ptr->m_title != remove_video) 
    {
      ptr = ptr->m_next;
    }
    if(ptr->m_next == NULL)
    {
      return false;
    }
    Node *temp = ptr->m_next;
    Video *temp_videoptr = ptr->m_next->m_video_ptr;
    ptr->m_next = ptr->m_next->m_next;
    delete temp_videoptr;
    delete temp;
  }  
  return true;
}




//insert  objects from Video class
//passed video object pointer 
void Vlist::insert(Video *video_ptr)
{
	//insert funtion where video will be inserted alphabetically by title
  if(m_head == NULL || m_head->m_video_ptr->m_title > video_ptr->m_title)
  {
    m_head = new Node(video_ptr, m_head);
  }
  else
  {
    Node *ptr = m_head;
    while(ptr->m_next != NULL && ptr->m_next->m_video_ptr->m_title <= video_ptr->m_title)
    {
      ptr = ptr->m_next;
    }
    ptr->m_next = new Node(video_ptr, ptr->m_next);
  }

  

}
//boolean funtion will check if there are any duplicate videos and return tru or false

bool Vlist::check_duplicates(string title)
{
  Node *ptr = m_head;
	  while(ptr != NULL)
	  {
	    if(title == ptr->m_video_ptr->m_title)
    {
    	//we found a duplicate, return true
      return true;
    }
    ptr = ptr->m_next;
  }
  //false means no duplicates
  return false;
}
//count of videos in list
int Vlist::length()
{
	Node*ptr = m_head;
  int counter = 0;
  while(ptr != NULL)
  {
    ptr = ptr->m_next;
    //increment each time we go from node to node
    counter++;
  }
  //pass counter to main where it will be printed
  return counter;

}

//lookup function where video is passed from main
//boolean function will return true if it found a video in the list 
//and call print from VIDEO CLASS
//else it will return false not in the list
bool Vlist::lookup(string lookup_video)
{
	
  Node *ptr = m_head;
  while(ptr != NULL)
  {
  	// if found the video in the list , print it
    if(lookup_video == ptr->m_video_ptr->m_title)
    {

      ptr->m_video_ptr->print();

      
      return true; // found the video in the list and return true
     
    }
    ptr = ptr->m_next;
  }
  return false;// no video in list , return false and print cerr in main
}

//print the list ...(hence the title)
void Vlist::print()
{
	
	Node *ptr = m_head;
  while (ptr != NULL)
  {
    ptr->m_video_ptr->print();
    ptr = ptr->m_next;
  }


}
//constructor
Vlist::Vlist()
{
  m_head = NULL;
}
//destructor
Vlist::~Vlist()
{
  Node *ptr = m_head;
  while (ptr != NULL)
  {
    Node *temp;

    temp = ptr;
    ptr = ptr->m_next;
    Video *tmp = temp->m_video_ptr;
    delete tmp;
    delete temp;
  }
  m_head = NULL;
}