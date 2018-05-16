#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

struct file{
    string name;
    string code;
    int length;
};

struct filedir{
    string name;
    vector<filedir> dirs;
    vector<file> files;
}root;

void init(void);
void display(filedir);
void newfile(void);
void newdir(void);
void deletefile(void);
void deletedir(void);

void init()
{
    root.name="root";
    filedir newDir;
    file newFile;

    newFile.name="c";
    newFile.code="111";
    newFile.length=12;
    root.files.push_back(newFile);
    newFile.name="d";
    newFile.code="111";
    newFile.length=12;
    root.files.push_back(newFile);

    newDir.name="A";
    newDir.files.push_back(newFile);
    root.dirs.push_back(newDir);
    newDir.name="B";
    newDir.files.push_back(newFile);
    root.dirs.push_back(newDir);

}

void display(filedir dir)
{
    if(dir.name!="root")
        cout<<"|--";
    cout<<dir.name<<endl;
    for(unsigned int i=0;i<dir.dirs.size();i++)
        display(dir.dirs[i]);
    for(unsigned int i=0;i<dir.files.size();i++)
        cout<<"|--"<<dir.files[i].name<<endl;
}

void newfile()
{
    file newFile;
    cout<<"请输入文件名:"<<endl;
    cin>>newFile.name;
    cout<<"请输入文件保护码："<<endl;
    cin>>newFile.code;
    cout<<"请输入文件长度："<<endl;
    cin>>newFile.length;
    root.files.push_back(newFile);
    cout<<"新建文件成功！"<<endl;
}

void newdir()
{
    filedir newDir;
    cout<<"请输入文件目录名："<<endl;
    cin>>newDir.name;
    root.dirs.push_back(newDir);
    cout<<"新建目录成功！"<<endl;
}

void deletefile()
{
    string name;
    cout<<"请输入文件名："<<endl;
    cin>>name;
    for(unsigned int i=0;i<root.files.size();i++)
        if(root.files[i].name==name)
            root.files.erase(root.files.begin()+i);
    cout<<"删除文件成功！"<<endl;
}

void deletedir()
{
    string name;
    cout<<"请输入目录名："<<endl;
    cin>>name;
    for(unsigned int i=0;i<root.dirs.size();i++)
        if(root.dirs[i].name==name)
            root.dirs.erase(root.dirs.begin()+i);
    cout<<"删除目录成功！"<<endl;
}

int main()
{
    int selection;
    init();
    while(1)
    {
      system("cls");
      cout<<"请选择要进行的操作："<<endl;
      cout<<"1.显示文件列表"<<endl;
      cout<<"2.新建文件"<<endl;
      cout<<"3.新建目录"<<endl;
      cout<<"4.删除文件"<<endl;
      cout<<"5.删除目录"<<endl;
      cout<<"6.退出"<<endl;
      cin>>selection;

      switch(selection){
        case 1:
            system("cls");
            display(root);
            system("pause");
            break;

        case 2:
            system("cls");
            newfile();
            system("pause");
            break;

        case 3:
            system("cls");
            newdir();
            system("pause");
            break;

        case 4:
            system("cls");
            deletefile();
            system("pause");
            break;

        case 5:
            system("cls");
            deletedir();
            system("pause");
            break;

        case 6:
            exit(EXIT_SUCCESS);
            break;

        default:
            cout<<"选项不存在，请重新输入！"<<endl;
            system("pause");
            break;
      }

    }

    return 0;
}
