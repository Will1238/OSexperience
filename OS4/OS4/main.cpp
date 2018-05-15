#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <stdio.h>
#include <string.h>

using namespace std;

struct UFD                  //用户文件目录结构体
{
    string filename;        //用户文件名
    char protectionCode[3]; //用户文件保护码
    int length;             //用户文件长度
    UFD()
    {
        filename="";
        protectionCode[0]='0';
        protectionCode[1]='0';
        protectionCode[2]='0';
        length=0;
    }
};

struct MFD                  //主文件目录结构体
{
    string username;        //用户名
    vector<UFD> files;      //用户文件列表（指针）
    MFD()
    {
        username="";
    }
};

struct AFD                  //运行文件目录结构体
{
    string filename;        //运行文件名
    char protectionCode[3]; //运行文件保护码
    string rwPointer;       //读写指针
    AFD()
    {
        filename="";
        protectionCode[0]='0';
        protectionCode[1]='0';
        protectionCode[2]='0';
        rwPointer="";
    }
};

vector<MFD> users;          //主文件目录
vector<AFD> openFiles;      //运行文件目录
int userExist(string);      //检测用户是否存在
void displayFiles(int);     //显示用户文件目录
void initAFD(void);         //初始化运行文件表
void commandMenu(int);      //处理输入的命令
void createFile(int);       //新建文件create
void deleteFile(int);       //删除文件delete
void openFile(int);         //打开文件open
void closeFile(int);        //关闭文件close
void readFile(int);         //读出文件read
void writeFile(int);        //写入文件write
void renameFile(int);       //修改文件名rename
void modifyFileCode(int);   //修改文件保护码mc

int userExist(string username)
{
    for(unsigned int i=0; i<users.size(); i++)
    {
        if(username==users[i].username)
            return i;
    }

    return -1;
}

void displayFiles(int userNum)
{
    printf("%-15s%-15s%-15s\n","文件名","文件保护码","文件长度");
    for(unsigned int i=0; i<users[userNum].files.size(); i++)
        printf("%-15s%-15s%-15d\n",
               users[userNum].files[i].filename.c_str(),
               users[userNum].files[i].protectionCode,
               users[userNum].files[i].length);
    printf("====================================\n");
}

void initAFD()
{
    openFiles.clear();
}

void commandMenu(int userNum)
{
    fflush(stdin);
    string command;

    displayFiles(userNum);
    printf("%-15s%-20s\n","命令","功能");
    printf("%-15s%-20s\n","1.create","创建文件");
    printf("%-15s%-20s\n","2.delete","删除文件");
    printf("%-15s%-20s\n","3.open","打开文件");
    printf("%-15s%-20s\n","4.close","关闭文件");
    printf("%-15s%-20s\n","5.read","读取文件");
    printf("%-15s%-20s\n","6.write","写入文件");
    printf("%-15s%-20s\n","7.rename","更改文件名");
    printf("%-15s%-20s\n","8.mc","更改文件保护码");
    printf("%-15s%-20s\n\n","9.return","返回主界面");

    cout<<"请输入命令或选项："<<endl;
    cin>>command;

    if(command=="create" || command=="1")
    {
        createFile(userNum);
    }
    else if(command=="delete" || command=="2")
    {
        deleteFile(userNum);
    }
    else if(command=="open" || command=="3")
    {
        openFile(userNum);
    }
    else if(command=="close" || command=="4")
    {
        closeFile(userNum);
    }
    else if(command=="read" || command=="5")
    {
        readFile(userNum);
    }
    else if(command=="write" || command=="6")
    {
        writeFile(userNum);
    }
    else if(command=="rename" || command=="7")
    {
        renameFile(userNum);
    }
    else if(command=="mc" || command=="8")
    {
        modifyFileCode(userNum);
    }
    else if(command=="return" || command=="9")
    {
        return;
    }
    else
    {
        cout<<"命令不存在！"<<endl;
    }
}

void createFile(int userNum)            //可添加文件查重功能
{
    UFD newFile;
    cout<<"请输入文件名："<<endl;
    cin>>newFile.filename;
    cout<<"请输入文件保护码："<<endl;
    scanf("%s",newFile.protectionCode);
    cout<<"请输入文件长度"<<endl;
    cin>>newFile.length;

    users[userNum].files.push_back(newFile);
    cout<<"新建文件成功！"<<endl;
}

void deleteFile(int userNum)
{
    string fileName;
    cout<<"请输入文件名："<<endl;
    cin>>fileName;
    for(unsigned int i=0; i<users[userNum].files.size(); i++)
    {
        if(users[userNum].files[i].filename==fileName)
            users[userNum].files.erase( users[userNum].files.begin()+i);
    }
    cout<<"删除文件成功！"<<endl;
}

void openFile(int userNum)
{
    string fileName;
    AFD file;
    cout<<"请输入文件名："<<endl;
    cin>>fileName;
    for(unsigned int i=0; i<users[userNum].files.size(); i++)
    {
        if(users[userNum].files[i].filename==fileName)
        {
            file.filename=users[userNum].files[i].filename;
            strcpy(file.protectionCode,users[userNum].files[i].protectionCode);
            file.rwPointer="NULL";
        }
    }
    cout<<"打开文件成功！"<<endl;
}

void closeFile(int userNum)             //可添加检查
{
    string fileName;
    cout<<"请输入文件名："<<endl;
    cin>>fileName;
    for(unsigned int i=0; i<openFiles.size(); i++)
    {
        if(openFiles[i].filename==fileName)
            openFiles.erase(openFiles.begin()+i);
    }
    cout<<"关闭文件成功！"<<endl;
}

void readFile(int userNum)              //可添加检查
{
    string fileName;
    cout<<"请输入文件名："<<endl;
    cin>>fileName;
    for(unsigned int i=0; i<openFiles.size(); i++)
    {
        if(openFiles[i].filename==fileName)
            openFiles[i].rwPointer="read";
    }
    cout<<"读取文件成功！"<<endl;
}

void writeFile(int userNum)             //可添加检查
{
    string fileName;
    cout<<"请输入文件名："<<endl;
    cin>>fileName;
    for(unsigned int i=0; i<openFiles.size(); i++)
    {
        if(openFiles[i].filename==fileName)
            openFiles[i].rwPointer="write";
    }
    cout<<"写入文件成功！"<<endl;
}

void renameFile(int userNum)
{
    string fileName,newName;
    cout<<"请输入文件名："<<endl;
    cin>>fileName;
    cout<<"请输入新文件名："<<endl;
    cin>>newName;
    for(unsigned int i=0; i<users[userNum].files.size(); i++)
    {
        if(users[userNum].files[i].filename==fileName)
            users[userNum].files[i].filename=newName;
    }
    cout<<"文件更名成功！"<<endl;
}

void modifyFileCode(int userNum)
{
    string fileName,newCode;
    cout<<"请输入文件名："<<endl;
    cin>>fileName;
    cout<<"请输入新保护码："<<endl;
    cin>>newCode;
    for(unsigned int i=0; i<users[userNum].files.size(); i++)
    {
        if(users[userNum].files[i].filename==fileName)
            memcpy(users[userNum].files[i].protectionCode,newCode.c_str(),newCode.length());
    }
    cout<<"文件保护码修改成功！"<<endl;
}

int main()
{
    string username;
    while(1)
    {
        system("cls");
        fflush(stdin);

        int selection=0;
        cout<<"请选择要进行的操作："<<endl;
        cout<<"1.管理文件"<<endl;
        cout<<"2.新建用户"<<endl;
        cout<<"3.查看命令列表"<<endl;
        cout<<"4.退出"<<endl;
        cin>>selection;
        switch(selection)
        {
        case 1:         //管理文件
            system("cls");
            cout<<"请输入用户名："<<endl;
            cin>>username;
            if((selection=userExist(username))!=-1)
                commandMenu(selection);
            else
                cout<<"用户不存在！"<<endl;
            system("pause");
            break;

        case 2:         //建立新用户
            system("cls");
            cout<<"请输入用户名："<<endl;
            cin>>username;
            if((selection=userExist(username))!=-1)
                cout<<"用户已存在！"<<endl;
            else
            {
                MFD newUser;
                newUser.username=username;
                users.push_back(newUser);
            }
            cout<<"新建用户成功！"<<endl;
            system("pause");
            break;

        case 3:         //查看命令列表
            system("cls");
            printf("%15s%20s\n","命令","功能");
            printf("%15s%20s\n","create","创建文件");
            printf("%15s%20s\n","delete","删除文件");
            printf("%15s%20s\n","open","打开文件");
            printf("%15s%20s\n","close","关闭文件");
            printf("%15s%20s\n","read","读取文件");
            printf("%15s%20s\n","write","写入文件");
            printf("%15s%20s\n","rename","更改文件名");
            printf("%15s%20s\n","mc","更改文件保护码");
            printf("%15s%20s\n","return","返回主界面");
            system("pause");
            break;

        case 4:
            exit(EXIT_SUCCESS);
            break;

        default:
            cout<<"选项输入错误，请重新输入！"<<endl;
            system("pause");
            break;
        }

    }

    return 0;
}
