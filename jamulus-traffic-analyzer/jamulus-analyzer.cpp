/*
This is a traffic file analyzer for the jamulus software. It gives various statistics on the traffic file that is generated from the jamulus server such as:
Number of Jams:
Number of Unique Visitors:
Total Jam Time:
Average Jame Size:
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <locale>
#include <cstdio>
#include <iterator>


std::string User_Log;
double elements=0, jammers=0;
double temp_users=0, multi_user=0, d=0;
std::string date;
std::ifstream ReadFile(R"(C:\Users\Fife\Documents\Chat_Log)");                                                       //Where the file to be analyzed is located
std::vector<std::string> gen_log, U_IP, Time, Date, jam_start, jam_end;
bool j_session=false, quit=false;                                                                                                   //Multi-User Session Identifier

int getIndex(std::vector<std::string> v, std::string K)
{
    std::string key = K;
    std::vector<std::string>::iterator itr = std::find(v.begin(), v.end(), key);

    if (itr != v.cend()) {
        d = std::distance(v.begin(), itr);
        return d;
    }
    else {
        std::cout << "Element not found";
    }
}

void Menu(){
    std::cout<<"//////////////////////////\n/Jamulus Traffic Analyzer/\n////////////////////////// \n \n";
    std::cout<<"Press 1 to display an all time traffic overview\nPress 2 to see the traffic of a certain date\n";
    std::cout<<"Press 5 to exit\n";
}
void Load_General_Form(){
    while (getline(ReadFile, User_Log,' '))
    {
        gen_log.push_back(User_Log);
        elements++;
    }
    ReadFile.close();
    for(int i=0; i<elements; i++)
    {
        if (gen_log[i].at(4)=='-' && gen_log[i].at(7)== '-')  //Date Catch
        {
            Date.push_back(gen_log[i]);
        }
        if (gen_log[i].at(2)==':' && gen_log[i].at(5)== ':') //Time Catch
        {
            Time.push_back(gen_log[i]);
        }
        if ((gen_log[i].at(3)=='.'||gen_log[i].at(2)=='.') && (gen_log[i].at(7)== '.'||gen_log[i].at(6)=='.'||gen_log[i].at(5)=='.')) //U_IP Catch
        {
            U_IP.push_back(gen_log[i]);
        }
    }
}                                                                                           //Load and read in file for analysis.
void Display_General_Form(){
    for(int i=0; i<gen_log.size(); i++)
    {
        std::cout<<gen_log[i]<<'\n';
    }
}                                                                                                                   //Used for Debugging and conceptualizing the data heap
void FindUniques(){                                                                                                     //this function sorts and counts the number of unique U_IP addresses that have connected
    std::sort(U_IP.begin(), U_IP.end() );
    U_IP.erase(std::unique(U_IP.begin(), U_IP.end() ), U_IP.end() );
    std::cout << "Number of Unique Visitors: " << U_IP.size() << '\n';
}                                                                                                 //Counts the number of unique users that have connected to the server
void FindJams(){
    multi_user =0;
    for(double i= (0); i < elements; i++)
    {
        if(gen_log[i].at(0)=='c')
        {
            temp_users++;
            jammers++;
        }
        if(gen_log[i].at(0)=='s' && gen_log[i].at(1)=='e' && j_session == true)
        {
            jam_end.push_back(gen_log[(i-1)]);
            j_session=false;
        }
        if(gen_log[i].at(0)=='s' && gen_log[i].at(1)=='e')
        {
            temp_users=0;
            j_session= false;
            jammers--;
        }
        if (temp_users>=2 && j_session == 0)
        {
            multi_user++;
            j_session= true;
            jam_start.push_back(gen_log[(i-6)]);
        }
    }
    std::cout<<"There has been a total of "<<multi_user<< " jams since "<<Date[0]<<'\n';
}                                                                                                    //Counts number of Multi-User Sessions and saves string timestamps of start and end times
void Calculate_Jam_Time(){
    std::tm when{}, when_2{};
    int tjt_h=0, tjt_m=0, tjt_s=0;
    std::ios::iostate state;
    for(int i =0; i<multi_user; i++)
    {
        std::locale loc;
        const auto& tmget = std::use_facet<std::time_get<char> >(loc);
        std::istringstream iss (jam_start[i]);
        std::istringstream iss_2 (jam_end[i]);
        tmget.get_time (iss, std::time_get<char>::iter_type(), iss, state, &when);
        tmget.get_time (iss_2, std::time_get<char>::iter_type(), iss_2, state, &when_2);

        tjt_s= tjt_s+(when_2.tm_sec-when.tm_sec);
        tjt_m= tjt_m+(when_2.tm_min-when.tm_min);
        tjt_h= tjt_h+(when_2.tm_hour-when.tm_hour);
        if (tjt_h <0)
        {
            tjt_h = tjt_h+24;
        }
        else if (tjt_m <0)
        {
            tjt_m = tjt_m+60;
        }
        else {
            if (tjt_s >= 0)
                continue;
            tjt_s = tjt_s + 60;
        }
    }
    while (tjt_s>59)
    {
        tjt_s= tjt_s-60;
        tjt_m=tjt_m+1;
    }
    while (tjt_m>59)
    {
        tjt_m= tjt_m-60;
        tjt_h=tjt_h+1;
    }
    std::cout<<"Total Jam Time is: "<< tjt_h<<" Hours ";
    std::cout<<tjt_m<<" Minutes and ";
    std::cout<<tjt_s<<" Seconds.\n";
}                                                                                          //Calculate the total amount of jam time
void Average_Jam_Size(){
    double avg;
    int avg2;
    avg = jammers / multi_user;
    avg = avg+ 0.5;
    avg2 = (int)avg;
    std::cout<<"Average Jam Size is: "<< avg2 <<" Users.\n\n";
}


int main() {
    int choice;
    Load_General_Form();
    Menu();
    std::cin >> choice;
    while (choice!=5){
        if (std::cin >> choice)
        {
            switch (choice)
            {
                case 0:
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cin >> choice;
                    break;
                case 1:
                    FindJams();
                    FindUniques();
                    Calculate_Jam_Time();
                    Average_Jam_Size();
                    choice = 0;
                    break;
                case 2:
                    std::cout<<"Type a date in the format: 2020-07-27\n";
                    std::cin >> date;
                    std::cout<<"Displaying activity since " << date << "\n";

                    break;
                case 5:
                    return 0;
                default:
                    std::cout << "Please Select again\n";
                    choice = 0;
                    break;
            }
        }
        else
        {
            std::cout << "Please Select again\n";
            Menu();
            std::cin.clear();
            std::cin.ignore(1000,'\n');
        }
    }
}
