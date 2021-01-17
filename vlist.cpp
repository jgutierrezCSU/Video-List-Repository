
//Gutierrez,jesus
//jgutierrez
#include<string>
#include<fstream>
#include<iostream>
#include "vlist.h"
#include<regex> 
using namespace std;

  
   string remove_trailing_zeros(string str) { 
    str.erase ( str.find_last_not_of('0') + 1, std::string::npos ); 
    str.erase ( str.find_last_not_of('.') + 1, std::string::npos );   
    return str; 
  }



void Vlist::write_to_file(){


  // function creates a local saved csv file after insert, video list was sorted or item was removed.

    ofstream myfile;
    myfile.open ("vlr.csv");
    string a_String = "";
    string a_final_string = "";
    Node *ptr = m_head;

    // pointer goes through the list and appends each video on the list after it already has been sorted
    while(ptr != NULL)
    { 

      string tmp_length= to_string(ptr->m_video_ptr->m_length);
      string a_length =tmp_length.substr (0,5); // arbitrary length size
      a_length=remove_trailing_zeros(a_length);

        a_String= ptr->m_video_ptr->m_title + "," + ptr->m_video_ptr->m_link + "," + ptr->m_video_ptr->m_description + "," + a_length + "," ;
        string a_Rating_string = "";
    
        for (int ratingCount = 0; ratingCount < ptr->m_video_ptr->m_rating; ratingCount++){
             a_Rating_string = "*" + a_Rating_string;
          }
    
        a_final_string= a_String + a_Rating_string + "\n";

      myfile << a_final_string;
     

      ptr = ptr->m_next;
    }

     myfile.close();



}
void Vlist::read_from_file(){

  string title,link,description,an_item,rating,length ,line ,a_filename;
  double t_length = -1; // for debugging
  int t_rating = -2; // for debugging
  cout << "looking file..... Done\n" << endl;
 

  a_filename ="vlr.csv";
  ifstream aStream(a_filename);
  if(!aStream)
    cout << "Could not find " << a_filename << ", Please create list." << endl;
    else{
      while(getline(aStream,line)){
        istringstream s(line);
       int count =0;
          // for each item (string or strings of letters) upto to the comma.
          while(getline(s,an_item,',')){
            if(count == 0)
            title = an_item;
            else if(count == 1)
           link = an_item;
            else if(count == 2)
            description = an_item;
            else if(count == 3){
           length = an_item;
           t_length = atof(length.c_str());
           }
           else if(count == 4){
           rating = an_item;
           t_rating = rating.size();
           }
           count++;
           
           }
   
      if (check_duplicates(title) == false){
          //if no duplicates create new VIDEO objects DYNAMICALLY
          Video *video_ptr = new Video(title,link,description,t_length ,t_rating );
          // passing pointer to object in vlist
          insert(video_ptr);
          //list.write_to_file(video_ptr);
       }

     
      }
    }
   
}


    
//}


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

      //list modified, update local csv
      write_to_file();

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

    //list modified, update local csv
    write_to_file();

  }  
  cout << "Removed.." << endl;
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
  //list modified, update local csv
  write_to_file();


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

 Vlist::Node *Vlist::sort_by_length(){


  Node *ptr = m_head;
  quickSort(&m_head,"length");
  return ptr;

}

 Vlist::Node *Vlist::sort_by_rating(){


  Node *ptr = m_head;
  quickSort(&m_head,"rating");
  return ptr;

}

 Vlist::Node *Vlist::sort_by_title(){


  Node *ptr = m_head;
  quickSort(&m_head,"title");
  return ptr;

}




void Vlist::quickSort( Node **headRef,string sort_cri) 
{ 
    Node *cur = m_head;

    while (cur != NULL && cur->m_next != NULL) 
          cur = cur->m_next; 


    (*headRef) = quickSortRecur(*headRef, cur, sort_cri); 
    return; 
} 



// Partitions the list taking the last element as the pivot 
Vlist::Node *Vlist:: partition( Node *head,  Node *end,  Node **newHead,  Node **newEnd,string sort_cri) 
{ 
     Node *pivot = end; 
     Node *prev = NULL, *cur = head, *tail = pivot; 
  
    // During partition, both the head and end of the list might change 
    // which is updated in the newHead and newEnd variables 
    while (cur != pivot) 
    { 
        if (sort_cri == "length" && cur->m_video_ptr->m_length  < pivot-> m_video_ptr->m_length  ) 
        { 
            // First node that has a value less than the pivot - becomes 
            // the new head 
            if ((*newHead) == NULL) 
                (*newHead) = cur; 
  
            prev = cur;  
            cur = cur->m_next; 
        } 
        else if (sort_cri == "rating" && cur->m_video_ptr->m_rating  < pivot-> m_video_ptr->m_rating ){
              // First node that has a value less than the pivot - becomes 
            // the new head 
            if ((*newHead) == NULL) 
                (*newHead) = cur; 
  
            prev = cur;  
            cur = cur->m_next; 

        }
        else if (sort_cri == "title" && cur->m_video_ptr->m_title  < pivot-> m_video_ptr->m_title ){
              // First node that has a value less than the pivot - becomes 
            // the new head 
            if ((*newHead) == NULL) 
                (*newHead) = cur; 
  
            prev = cur;  
            cur = cur->m_next; 

        }
        else // If cur node is greater than pivot 
        { 
            // Move cur node to next of tail, and change tail 
            if (prev) 
                prev->m_next = cur->m_next; 
             Node *tmp = cur->m_next; 
            cur->m_next = NULL; 
            tail->m_next = cur; 
            tail = cur; 
            cur = tmp; 
        } 
    } 
  
    // If the pivot data is the smallest element in the current list, 
    // pivot becomes the head 
    if ((*newHead) == NULL) 
        (*newHead) = pivot; 
  
    // Update newEnd to the current last node 
    (*newEnd) = tail; 
  
    // Return the pivot node 
    return pivot; 
} 

  

 Vlist::Node *Vlist::quickSortRecur( Node *head,  Node *end,string sort_cri) 
{ 
    // base condition 
    if (!head || head == end) 
        return head; 
  
    Node *newHead = NULL, *newEnd = NULL; 
  
    // Partition the list, newHead and newEnd will be updated 
    // by the partition function 
     Node *pivot = partition(head, end, &newHead, &newEnd,sort_cri); 
  
    // If pivot is the smallest element - no need to recur for 
    // the left part. 
    if (newHead != pivot) 
    { 
        // Set the node before the pivot node as NULL 
         Node *tmp = newHead; 
        while (tmp->m_next != pivot) 
            tmp = tmp->m_next; 
        tmp->m_next = NULL; 
  
        // Recur for the list before pivot 
        newHead = quickSortRecur(newHead, tmp,sort_cri); 
  
        // Change m_next of last node of the left half to pivot 
        Node *cur = NULL;

        cur=newHead;
        while (cur != NULL && cur->m_next != NULL) 
          cur = cur->m_next; 

        tmp=cur;
        //tmp = getTail(newHead); 
        tmp->m_next = pivot; 
    } 
  
    // Recur for the list after the pivot element 
    pivot->m_next = quickSortRecur(pivot->m_next, newEnd,sort_cri); 
  
    return newHead; 
} 

void Vlist::lookup_expression(string rg_xp){
    bool is_found =false;
            
            try {
                    regex search_exp(rg_xp);     
                    Node *ptr = m_head;
                  while(ptr != NULL)
                   {
                      // if found the video in the list , print it
                        if(regex_search(ptr->m_video_ptr->m_title, search_exp))
                        {
                              ptr->m_video_ptr->print();  
                              is_found = true;
                         
                         }
                         if(regex_search(ptr->m_video_ptr->m_description, search_exp))
                        {
                              ptr->m_video_ptr->print();  
                              is_found = true;
                         
                         }      
                  
                        ptr = ptr->m_next;
                    }
                    if(is_found == false)
                      cout << "Regular expression <"<< rg_xp << "> does not match any titles in list"<< endl;
                }

            catch (const regex_error& err) { 
                    cout << "There was a regex_error caughted: " << err.what() << '\n'; 
                    //an_error =true;
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