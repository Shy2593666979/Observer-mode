## 观察者模式

### 一、基本概念

观察者模式（又被称为模型（Model）-视图（View）模式）是软件设计模式的一种。在此种模式中，一个目标物件管理所有相依于它的观察者物件，并且在它本身的状态改变时主动发出通知。这通常透过呼叫各观察者所提供的方法来实现。

### 二、实现方式

观察者模式有很多实现方式，从根本上说，该模式必须包含两个角色：观察者和被观察者。

比如在下面的代码表述中，发布作品的DY博主是**被观察者**，博主的粉丝是**观察者** ，当DY博主(**被观察者**) 发生某种变化时 (**状态改变**),就会立即通知博主的粉丝 (**观察者** )。

### 三、角色

**1、抽象主题（Subject）：**

它是一个抽象类，也是所有目标对象的父类。它用一个列表记录当前目标对象有哪些观察者对象，并提供增加(Add)、删除观察者对象(Delete)和通知观察者对象的接口。

**2、具体主题（ConcreteSubject）：**

具体目标类，可以有多个不同的具体目标类，它们同时继承Subject类。一个目标对象就是某个具体目标类的对象，一个具体目标类负责定义它自身的事务逻辑，并在状态改变时通知它的所有观察者对象。

**3、抽象观察者（Observer）：**

观察者类，它也是一个抽象类，是所有观察者对象的父类；它为所有的观察者对象都定义了一个名为show的方法（也叫成员函数）。当目标对象的状态改变时，它就是通过调用它的所有观察者对象的show方法来通知它们的。

**4、具体观察者（ConcreteObserver）：**

具体观察者类，可以有多个不同的具体观察者类，它们同时继承Observer类。一个观察者对象就是某个具体观察者类的对象。每个具体观察者类都要重定义Observer类中定义的show方法，在该方法中实现它自己的任务逻辑，当它被通知的时候（目标对象调用它的show方法）就执行自己特有的任务。

### 四、过程

实现观察者模式有很多形式，比较直观的一种是使用一种“注册—通知—撤销注册”的形式。

**观察者**

（Observer）将自己注册到被观察对象（Subject）中，被观察对象将观察者存放在一个容器（Container）里。

**被观察对象**

被观察对象发生了某种变化，从容器中得到所有注册过的观察者，将变化通知观察者。

**撤销观察**

观察者告诉被观察者要撤销观察，被观察者从容器中将观察者去除。

### 五、结构图

![在这里插入图片描述](https://img-blog.csdnimg.cn/f7ae1e04e3a94ebdaa0fc6a664246fe1.png)

### 六、构建思路

我们在前期已经了解了observer和subject的代表意义及用法，下面我们开始构思如何写代码

先写出subject和observer类定义用法

```c++
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
```

Observer中的成员函数都是虚函数，不需要强调其作用，只需要了解虚函数的用法；

**Subject类的成员函数及变量：**

void Add(Observer *obs)---------------增加观察者

void Delete(Observer *obs)------------删除观察者

void show()-----------------------------------当被观察者状态发生改变时，及时通知观察者

~Subject()-------------------------------------析构函数，创建了许多观察者，最后需要析构删除

std::vector<Observer *>observer-----存放观察者的信息，观察者存放到vector容器中

**具体主题（ConcreteSubject）和具体观察者（ConcreteObserver）的类定义**

```c++
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
```

**具体主题（ConcreteSubject）类的成员函数及成员变量**

std::string getSubjectStatus() -------------------获得被观察者的状态

void   setSubjectStatus(ConcreteSubject * subject, const std::string &str) ------------设置被观察者的状态

std::string subjectStatus---------------------------被观察者状态的变量

**具体主题（ConcreteObserver）类的成员函数及成员变量**

ConcreteObserver(ConcreteSubject *subject,std::string name)---------构造函数，初始化具体观察者

std::string getName()-----------得到观察者的名字

void update() ----------------------当被观察者状态改变时，提醒观察者

std::string observerStatus-----观察者状态

### 七、完整代码

***observer.h***

```c++
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
```

***observer.cpp***

```c++
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
```

***main.cpp***

```c++
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
```

