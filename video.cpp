
//Gutierrez,jesus
//jgutierrez

#include <fstream>
#include "video.h"
#include "vlist.h"
#include <iostream>
const int MAX = 100;
using namespace std;
Video *video_array[MAX];


Video::Video(string title , string link, string description,double length , int rating)
{
    m_title = title;
    m_link = link;
    m_description = description;
    m_length = length;
    m_rating = rating;
}

void Video::print()
{
    cout << m_title << ", " << m_link << ", " << m_description << ", ";
    cout << m_length << ", " ;
    //

	for (int ratingCount = 0; ratingCount < m_rating; ratingCount++){
		cout << "*";
	}
	cout << endl;
}










