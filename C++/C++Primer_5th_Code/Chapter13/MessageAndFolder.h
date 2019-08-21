#ifndef MESSAGEANDFOLDER
#define MESSAGEANDFOLDER

#include<iostream>
#include<set>
#include<string>

class Folder;

class Message
{
    friend class Folder;
private:
    std::string contents;
    std::set<Folder*> folders;    
    void add_to_Folders(const Message&);
    void remove_from_Folders();

public:
    explicit Message(const std::string &str=""):contents(str){};
    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();

    //从给定的Folder集合中添加、删除本Message
    void save(Folder&);
    void remove(Folder&);
};


Message::~Message()
{
}



#endif