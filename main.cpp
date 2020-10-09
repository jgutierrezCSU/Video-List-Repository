// Project 3
//Gutierrez,jesus
//jgutierrez

#include <iostream>
using namespace std;
#include "video.h"
#include "vlist.h"

Vlist list;
string lookup_video;
string remove_video;
string title;
string link;
string comment;
float length;
int rating;
int videoCount = 0;



int main()
{
	//command given by user , needs to be insert , remove ,print , length or lookup.Else will terminate w/ cerr
	string command;
	const int MAX = 100;
	// while loop for user input
	while(getline(cin, command))
	{	
		//will insert users videos
		if (command == "insert")
		{
				
					
					getline(cin,title);
					getline(cin,link);
					getline(cin,comment);
					cin >> length;
					cin >> rating;
					cin.ignore();
					
					if (videoCount >= MAX)
					{
						cerr << "Too many videos, giving up." << endl;
						return 1;
					}
					// "if" will check if there are any duplicate videos and return tru or false
					//false means no duplicates
					if (list.check_duplicates(title) == false){
					//if no duplicates create new VIDEO objects DYNAMICALLY
					Video *video_ptr = new Video(title,link,comment,length ,rating );
					// passing pointer to object in vlist
					list.insert(video_ptr);
					 }
					 //if there are duplicates print our cerr
					 else{
					 	cerr << "Could not insert video <" << title << ">, already in list." << endl;
					 }
					
					
		}
		// user needs to look up video 
		else if(command == "lookup")
		{	
			getline(cin,lookup_video);
			//list.lookup(lookup_video);
			//if title of video is not in list return false and print cerr
			if (list.lookup(lookup_video) == false )
			{
				cerr << "Title <" <<lookup_video<< "> not in list." << endl;

			}

		}
		//user wants to remove video from list
		else if(command == "remove")
		{
			//get what video need to be removed
			getline(cin,remove_video);
			//list.lookup(lookup_video);
			if (list.remove(remove_video) == false )
			{  //print out cerr if video was not found
				cerr << "Title <" << remove_video << "> not in list, could not delete." << endl;

			}
		}
		// user wants to print length
		else if(command == "length")
		{
			//print count from lookup function
			cout << list.length() << endl;
			//cout  << counter << endl;
		}
		//user want to print list
		//print nothing if list is empty
		else if (command == "print")
		{
			
			list.print();
			
		}

		//user did not choose any valid arguments/commands
		else{

		cerr << "<" << command << "> is not a legal command, giving up." << endl;
			return 1;
		}
	}
	
	
}