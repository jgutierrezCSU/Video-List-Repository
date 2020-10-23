
//Gutierrez,jesus
//jgutierrez

#include <fstream>
#include "video.h"
#include "vlist.h"
#include <iostream>
const int MAX = 100;
using namespace std;
Video *video_array[MAX];


Video::Video(string title , string link, string comment,double length , int rating)
{
    m_title = title;
    m_link = link;
    m_comment = comment;
    m_length = length;
    m_rating = rating;
}

void Video::print()
{
    cout << m_title << ", " << m_link << ", " << m_comment << ", ";
    cout << m_length << ", " ;

	for (int ratingCount = 0; ratingCount < m_rating; ratingCount++){
		cout << "*";
	}
	cout << endl;
}

void Video::write_vid_to_file()
{

    string a_String = "";
    string a_Rating_string = "";
    string a_final_string = "";

    a_String= m_title + ", " + m_link + ", " + m_comment + ", " + to_string(m_length) + ", " ;

    
    for (int ratingCount = 0; ratingCount < m_rating; ratingCount++){
         a_Rating_string = "*" + a_Rating_string;
    }
    
    a_final_string= a_String + a_Rating_string + "\n";

  ofstream myfile;
  myfile.open ("vlr",ios_base::app);
  myfile << a_final_string;
  myfile.close();
  


}


void Video::read_from_file()
{

  /*vector<char> v;
  if (FILE *fp = fopen("vlr", "r"))
  {
    char buf[1024];
    while (size_t len = fread(buf, 1, sizeof(buf), fp))
      v.insert(v.end(), buf, buf + len);
    fclose(fp);
  }*/

}








