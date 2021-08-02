#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/*
Simplify original file to csv file
root 'modi_csv("original_file.csv","simple_file.csv")'
*/

void modi_csv(string RF, string WF)
{
    cout<<"RF is " << RF <<endl;
    fstream ReadFile;
    ofstream WriteFile;

    ReadFile.open(RF);
    WriteFile.open(WF);

    string str_buf;
    string comma = ",\n";
    int count=0, num=0, time=0, value=0;
    bool start=false;
    while(!ReadFile.eof())
    {
        getline(ReadFile,str_buf,',');
        if(str_buf == " Ch2 Data")
        {
            continue;
            count=0;
        }
        if(str_buf == "/m3")
            start=true;
        if(start==true)
            count++;
        if(count==13)
        {
            value=stoi(str_buf);
        }
        if(count==15)
        {
            value-=stoi(str_buf);
            stringstream sval;
            sval << value;
            WriteFile.write(sval.str().c_str(),sval.str().size());
            WriteFile.write(comma.c_str(),comma.size());
            count = 0;
            start = false;
            num++;
            time+=10;
        }
    }
    WriteFile.close();
}