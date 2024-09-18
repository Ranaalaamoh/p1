#include <iostream>
#include<filesystem>
#include <string>
#include <windows.h>
#include<fstream>

using namespace std;
namespace fs = std::filesystem;

void FileOrganize(string &path)
{
    fs::path dir(path);

    fs::path img=dir/"img";
    fs::path vids=dir/"vids";
    fs::path doc=dir/"doc";
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
}

int main()
{
 string path ;
    cout<<"enter the path";
    getline(cin,path);
    FileOrganize(path);
    return 0;
}
