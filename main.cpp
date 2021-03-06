
//Gutierrez,jesus
//jgutierrez

#include <iostream>
using namespace std;
#include "video.h"
#include "vlist.h"



void cmd_help()
{

	cout << "OPTIONS:\ninsert: Insert a new video into the linked list (Title,  url, description,length,rating)"<< endl;
	cout << "print: Print  all  the  videos  in  the list  " << endl;
	cout << "length: Print the number of videos in the list as a single integer" << endl;
	cout << "lookup: If given title is in the list, print the video " << endl;
	cout << "remove: Remove given title if in list" << endl;
	cout << "sort_by_length: Sorts videos in list ordered by length (short to long)" << endl;
	cout << "sort_by_rating: Sorts videos in list ordered by rating (short to long)" << endl;
	cout << "sort_by_title: Sorts videos in list alphabetically title (ascending)" << endl;
	cout << "lookup_expression: Use any regular expression to search through list."<< endl;
	cout << "save: Save current state of repository locally" << endl;
	cout << "exit: Exit program\n" << endl;

	
}



int main()
{
	//Declerations
	Vlist list;
	string lookup_video;
	string remove_video;
	string title;
	string link;
	string description;
	float length;
	int rating;
	int videoCount = 0;
	string rg_expression = "";	
	string save_File_as ="";
	
	//command given by user , needs to be insert , remove ,print , length or lookup. Else will terminate w/ cerr
	string command;
	const int MAX = 1000;

	cmd_help(); // Show help at program start up

	// reads from file that was previoulsy saved
	// funtion has local file where videos are stored, these file are loaded here
	list.load_from_file();
	
	// while loop for user input
	while(getline(cin, command))
	{	

		//will insert users videos
		if (command == "insert")
		{
				
					cout << "Title: ";
					getline(cin,title);
					cout << "Link: " ;
					getline(cin,link);
					cout << "description: " ;
					getline(cin,description);
					cout << "Length (float): ";
					cin >> length;
					cout << "Rating (int): ";
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
					Video *video_ptr = new Video(title,link,description,length ,rating );
					// passing pointer to object in vlist
					list.insert(video_ptr);
					//list.write_to_file(video_ptr);
					 }
					 //if there are duplicates print our cerr
					 else{
					 	cerr << "Could not insert video <" << title << ">, already in list." << endl;
					 }
					
		}
		// user needs to look up video 
		else if(command == "lookup")
		{	
			cout << "Title: ";
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
			cout << "Title: ";
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
			cout << "Number of Videos in list: ";
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
		else if (command == "sort_by_length")
		{
			
			
			list.sort_by_length();
			cout << "Sorted using Quick sort...\n" << endl;
			
		}
		else if (command == "sort_by_rating")
		{
			
			
			list.sort_by_rating();
			cout << "Sorted using Quick sort..." << endl;
			
		}

		else if (command == "sort_by_title")
		{
			
			
			list.sort_by_title();
			cout << "Sorted using Quick sort...\n" << endl;
			
		}
		else if (command == "lookup_expression")
		{
			
			cout << "Enter regular expression (searches titles AND descriptions)" << endl;
			cout << ":";
			getline(cin, rg_expression);
			list.lookup_expression(rg_expression);
			

		}
		else if (command == "save")
		{
			
			cout << "Save as : ";
			getline(cin, save_File_as);
			list.write_to_file(true, save_File_as);
			

		}

		else if (command == "exit")
		{
			
			return 0;
			
		}


		//user did not choose any valid arguments/commands
		else{

		cerr << "<" << command << "> is not a legal command\n\n" << endl;
			cmd_help();
		}
	}
	
	
}