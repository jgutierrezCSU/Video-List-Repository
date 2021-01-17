
//Gutierrez,jesus
//jgutierrez

// The following prevent this file from being included more than once
//
#ifndef Video_H
#define Video_H

#include <string>

using namespace std;


class Video
{
	

    public:
        Video(string title , string link, string description,double length , int rating);
        void print();
        //void insert_from_local_file(string title , string link, string description,string length , string rating);
        int videoCount = 0;
         string m_title;
	    string m_link;
	    string m_description;
	    double m_length;
	    int m_rating;
    private:
	   
}; // don't forget this ;
//


// part of the mechanism that prevents this file from being included multiple times
#endif
