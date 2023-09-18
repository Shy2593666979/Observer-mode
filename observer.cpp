#include "observer.h"
#include<iostream>

void Subject::Add(Observer *obs)
{
    observer.push_back(obs);
}
void Subject::Delete(Observer *obs)
{
    for(auto i = 0;i < observer.size();i++)
    {
        if(obs == observer[i])
        {
            observer.erase(observer.begin() + i);
        }
    }
}
void Subject::show()
{
    auto it = observer.begin();  //vector<Observer*>::iterator
    while(it != observer.end())  
    {
        (*it)->update();        // it是指向observer元素的地址类似于observer.begin()。*it才相当于 observer[i]
        it++;
    }
}
Subject::~Subject()
{
    std::cout<<"执行析构函数------"<<std::endl;
    auto it = observer.begin();
    while(it != observer.end())
    {
        std::cout<<"已经删除："<<(*it)->getName()<<std::endl;
        delete *it;
        it++;
    }
    observer.clear();
}
std::string ConcreteSubject::getSubjectStatus()
{
    return subjectStatus;
}
void ConcreteSubject::setSubjectStatus(ConcreteSubject * subject,const std::string &str)
{
    subjectStatus = str;
    subject->show();
}
ConcreteObserver::ConcreteObserver(ConcreteSubject *subject,std::string name)
{
    this->subject = subject;
    this->name = name;
}
std::string ConcreteObserver::getName()
{
    return name;
}
void ConcreteObserver::update()
{
    observerStatus = subject->getSubjectStatus();
    std::cout<<"您关注的DY博主更新动态了    粉丝: "<<name<<"用户状态: "<<observerStatus<<std::endl;
}