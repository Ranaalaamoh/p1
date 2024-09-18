#include <iostream>
#include<filesystem>
#include <string>
#include <windows.h>
#include<fstream>

using namespace std;
namespace fs = std::filesystem;

void FileOrganize(string &path , string &imag , string &docm , string &vid)
{
    fs::path dir(path);

    fs::path img=dir/imag;
    fs::path vids=dir/vid;
    fs::path doc=dir/docm;
    fs::path other=dir/"other";


    fs::create_directory(img);
    fs::create_directory(vids);
    fs::create_directory(doc);
    fs::create_directory(other);

    for(auto file:fs::directory_iterator(dir))
    {
        if(fs::is_regular_file(file))
        {
            string ext=file.path().extension().string();
            fs::path destination;
            if (ext == ".jpg" || ext == ".png" || ext == ".gif") {
                destination = img / file.path().filename();
            } else if (ext == ".pdf" || ext == ".docx" || ext == ".doc") {
                destination = doc / file.path().filename();
            } else if (ext == ".mp4" || ext == ".avi" || ext == ".mkv") {
                destination = vids / file.path().filename();
            } else {
                destination = other / file.path().filename();
            }
            fs::rename(file.path(),destination);
        }
    }
    ShellExecute(NULL,"open",path.c_str(),NULL,NULL,SW_SHOWNORMAL);
}

int main()
{
 string path , imag , vid, doc ;
    cout<<"enter the path";
    getline(cin,path);
    cout<<"[0] to modifiy setting "<<endl<<"[1] to organize directory"<<endl<<"Note:[0] your first time:";
    int x;
    cin>>x;
    if(x==0)
    {
        cout<<"enter the img folder name: ";
        cin>>imag;
        cout<<"enter the doc folder name";
        cin>>doc;
        cout<<"enter the vid folder name: ";
        cin>>vid;
        ofstream filecsv("data.csv");
        if(!filecsv)
        {
            cout<<"error opening data.csv file";
        }
        filecsv<<imag<<endl<<doc<<endl<<vid;
        filecsv.close();
    }
    else
    {
        ifstream file("data.csv");
        if(!file)
        {
            cout<<"error opening data.csv file";
        }
        string line ;
        int counter=0;
        while(getline(file,line))
        {
            if(counter==0)imag=line;
            else if (counter==1)doc=line;
            else vid=line;
            counter++;
        }

    }
    FileOrganize(path ,imag,doc,vid);
    return 0;
}
