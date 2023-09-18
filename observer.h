#include<iostream>
#include<vector>

class Observer
{
public:
    virtual void update(){};
    virtual std::string getName()
    {
        return "";
    }
};
class Subject 
{
public:
    void Add(Observer *obs);
    void Delete(Observer *obs);
    void show();
    ~Subject();
private:
    std::vector<Observer *>observer;
};
class ConcreteSubject : public Subject
{
public:
    std::string getSubjectStatus();
    void   setSubjectStatus(ConcreteSubject * subject, const std::string &str);
private:
    std::string subjectStatus;
};
class ConcreteObserver : public Observer
{
public:
    ConcreteObserver(ConcreteSubject *subject,std::string name);
    std::string getName();
    void update();
private:
    std::string name;
    ConcreteSubject *subject;
    std::string observerStatus;
};