#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>

using namespace std;

//menu function
char mainMenu()
{
    //getting the name from the user
    cout<<"Input your name"<<endl;
    string name;
    cin>>name;

    //menu
    cout<<"+==============================================================+"<<endl;
    cout<<"|                         MAIN MENU                            |"<<endl;
    cout<<"|           Botswana Ministry of Health COVID Register         |"<<endl;
    cout<<"|                                                              |"<<endl;
    cout<<"+=============================================================+"<<endl;
    cout<<"                       GOOD DAY! "<<name<<"                    "<<endl;
    cout<<"+==============================================================+"<<endl;
    cout<<"|                                                              |"<<endl;
    cout<<"|               1. CAPTURE CONTACT DETAILS                     |"<<endl;
    cout<<"|                                                              |"<<endl;
    cout<<"|               2. VIEW UNSORTED DATA                          |"<<endl;
    cout<<"|                                                              |"<<endl;
    cout<<"|               3. VIEW SORTED DATA IN ASCENDING               |"<<endl;
    cout<<"|                                                              |"<<endl;
    cout<<"|               4. SEARCH FOR A RECORD (omang/surname)         |"<<endl;
    cout<<"|                                                              |"<<endl;
    cout<<"|               5. EXIT                                        |"<<endl;
    cout<<"+==============================================================+"<<endl;

    cout<<"Enter number from main menu"<<endl;
    char mainmenu;
    cin>>mainmenu;

    return mainmenu;
}
//connection for the databse
MYSQL* connectionVariable()
{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"192.168.0.27","admin","admin","datastructure",0,NULL,0);

    return conn;
}
//outputing the results from the db
string outputRender(MYSQL_RES* res)
{
    //checking for mysql connection
    MYSQL_ROW data;

    cout<<"+============+================+================+===============+================+============+=============+=============================+"<<endl;
    cout<<"| firstname  | lastname       | location       | number        | omang /id      | age        | temperature | time created                |"<<endl;
    cout<<"+============+================+================+===============+================+============+=============+=============================+"<<endl;
    while(data = mysql_fetch_row(res))
    {
        //displaying the database results
        cout<<" "<<data[1]<<"         "<<data[2]<<"           "<<data[3]<<"          "<<data[4]<<"          "<<data[5]<<"            "<<data[6]<<"          "<<data[7]<<"          "<<data[8]<<endl;
    }
    cout<<"+========================================================================================================================================+"<<endl;

}

//saving the data to the database
string saving(string firstname,string lastname,string location,int number,int omang,int age,float temp)
{
    MYSQL* conn;
    //checking for mysql connection
    conn = connectionVariable();
    //check for connection
    if(conn)
    {
        //declaration
        int queryString = 0;
        stringstream treams;

        //inserting the data
        treams<<"INSERT INTO users(firstname,lastname,location,number,omang,age,temperature) VALUES('"<<firstname<<"','"<<lastname<<"','"<<location<<"','"<<number<<"','"<<omang<<"','"<<age<<"','"<<temp<<"')";
        string query = treams.str();
        const char* q = query.c_str();
        queryString = mysql_query(conn,q);

        //checking for success
        if(queryString == 0)
        {
            cout<<"Saving process successful..."<<endl;
        }
        else
        {
            cout<<"The saving process has failed!...."<<endl;
        }

    }
    else
    {
        cout<<"poor database connection"<<endl;
    }
}
//capturing data
string inputInfo()
{
    //names
    cout<<"Input first and last name"<<endl;
    string firstname,lastname;
    cin>>firstname>>lastname;

    //location
    cout<<"Input location"<<endl;
    string location;
    cin>>location;

    //cell number
    cout<<"Input cell number"<<endl;
    int num;
    cin>>num;

    //date of birth
    cout<<"Input date of birth (days,month,year)"<<endl;
    int bd,bm,by;
    cin>>bd>>bm>>by;

    //present date
    cout<<"Input present date (days,month,year)"<<endl;
    int pd,pm,py;
    cin>>pd>>pm>>py;

    //temperature
    cout<<"Input temparature"<<endl;
    float temp;
    cin>>temp;

    //temperature
    cout<<"Input omang"<<endl;
    int omang;
    cin>>omang;

    //computing for the age
    int d, m, y;
    int md[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    y = py - by;
    if (pm < bm)
    {
        y--;
        m = 12 - (bm - pm);
    }
    else
    {
        m = pm - bm;
    }

    if (pd < bd)
    {
        m--;
        d = md[pm - 1] - (bd - pd);
    }
    else
    {d = pd - bd;}

    //calling the fucntion for the database
    saving(firstname,lastname,location,num,omang,y,temp);
}

//getting data from the database
string unsorted()
{
    MYSQL* conn;
    //checking for mysql connection
    conn = connectionVariable();
    MYSQL_RES* res;

    //checking for connection
    if(conn)
    {
        int queryString = mysql_query(conn,"SELECT * FROM users");

        if(!queryString)
        {
            //checking the result
            res = mysql_store_result(conn);
            outputRender(res);
        }
        else
        {
            cout<<"The record failed to be invoked"<<endl;
        }
    }
    else
    {
        cout<<"no connection with the DATABASE"<<endl;
    }
}

//fucntion for displaying the sorted data from the database
string sorted()
{
    MYSQL* conn;
    //checking for mysql connection
    conn = connectionVariable();
    MYSQL_RES* res;

    //checking for connection
    if(conn)
    {
        int queryString = mysql_query(conn,"SELECT * FROM users ORDER BY firstname");

        if(!queryString)
        {
            //checking the result
            res = mysql_store_result(conn);
            outputRender(res);
        }
        else
        {
            cout<<"The record failed to be invoked"<<endl;
        }
    }
    else
    {
        cout<<"no connection with the DATABASE"<<endl;
    }
}

//searching from the database
string searching(string value)
{
    MYSQL* conn;
    //checking for mysql connection
    conn = connectionVariable();
    MYSQL_RES* res;

    //checking for connection
    if(conn)
    {
        //checking if the parameter passed is string or integer
        ostringstream strstr;
        strstr << "SELECT * FROM users WHERE lastname='" << value << "'";

        string str = strstr.str();
        int queryString = mysql_query(conn, str.c_str());


        if(!queryString)
        {
            //checking the result
            res = mysql_store_result(conn);
            outputRender(res);
        }
        else
        {
            cout<<"The record failed to be invoked"<<endl;
        }
    }
    else
    {
        cout<<"no connection with the DATABASE"<<endl;
    }
}
//search 2
string searching(int value)
{
    MYSQL* conn;
    //checking for mysql connection
    conn = connectionVariable();
    MYSQL_RES* res;

    //checking for connection
    if(conn)
    {
        //checking if the parameter passed is string or integer
        ostringstream strstr;
        strstr << "SELECT * FROM users WHERE omang='" << value << "'";

        string str = strstr.str();
        int queryString = mysql_query(conn, str.c_str());


        if(!queryString)
        {
            //checking the result
            res = mysql_store_result(conn);
            outputRender(res);
        }
        else
        {
            cout<<"The record failed to be invoked"<<endl;
        }
    }
    else
    {
        cout<<"no connection with the DATABASE"<<endl;
    }
}

int main()
{
    int count= 0;
    while(count <100)
    {
        //recalling the same logic again
        //calling the menu method
        char menuChar = mainMenu();

        //checking the service chosen buy the user and rendering it
        switch(menuChar)
        {
            case '1':
                inputInfo();
                break;
            case '2':
                unsorted();
                break;
            case '3':
                sorted();
                break;
            case '4':
                cout<<"+==============================================================+"<<endl;
                cout<<"|                          SECOND MENU                         |"<<endl;
                cout<<"|             search for a record by selecting below           |"<<endl;
                cout<<"+==============================================================+"<<endl;
                cout<<"|                           1. surname                         |"<<endl;
                cout<<"|                                                              |"<<endl;
                cout<<"|                           2. id                              |"<<endl;
                cout<<"+==============================================================+"<<endl;
                cout<<"Enter number from menu"<<endl;
                int menuNum;
                cin>>menuNum;

                //checking for what the user has opted to search with
                if(menuNum == 1)
                {

                    cout<<"Searching with username....."<<endl;
                    string name;
                    cin>>name;
                    //passing the value to the search function
                    searching(name);
                }
                else if(menuNum == 2)
                {
                    cout<<"Searching with id"<<endl;
                    int id;
                    cin>>id;

                    //passing value to the search function
                    searching(id);
                }
                else
                {
                    cout<<"Invalid number"<<endl;
                }
                break;
            case '5':
                exit;
                break;
            default:
                cout<<"INVALID NUMBER ENTERED CHOOSE FROM THE MAIN MENU"<<endl;
        }
        //the count variable
        cout<<"do you want to continue yes/no"<<endl;
        string choic;
        cin>>choic;

        if(choic == "yes")
        {
            count++;
        }
        else if(choic == "no")
        {
            cout<<"THANK FOR USING OUR PLATFORM. GOOD BYE!!!"<<endl;
            exit(1);
        }
        else
        {
            cout<<"the input text was invalid"<<endl;
        }
    }
    return 0;
}



