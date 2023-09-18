#include "observer.h"
#include <iostream>
int main()
{
    ConcreteSubject *subject = new ConcreteSubject;
    subject->Add(new ConcreteObserver(subject,"TMG"));
    subject->Add(new ConcreteObserver(subject,"WYA"));
    subject->setSubjectStatus(subject,"在线");
    std::cout<<std::endl;
    delete subject;
}