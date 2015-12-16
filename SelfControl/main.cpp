//
//  main.cpp
//  SelfControl
//
//  Created by Zestinc on 15/9/17.
//  Copyright (c) 2015年 Zestinc. All rights reserved.
//

//1. 第二天醒来的时候自控力回复到人物上限
//2. 当不断的玩手机的时候，自控力不断的下降
//3. 每当完成一件事情的时候，提升自控力上限经验值
//4. 每当完成一件事情的时候，减少当前自控力值
//5. 当进行一定时间的娱乐活动之后，当前自控力水平回升
//6. 当自控力回升到最大值时，提醒

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <map>
#include "selfcontrol.h"
using namespace std;

enum {CheckLevel = 1, Update, ChangeMotto, GoodBye};

void ShowTime(){
    time_t timeval;
    timeval=time(NULL);
    cout<<"现在的时间为："<<ctime(&timeval)<<endl;
}


int main(){
    ShowTime();
    selfControl self;
    self.GetValue();
    self.ShowMotto();
    bool flag = true;
    while(flag){
        self.ClearScreen();
        int x;
        cout<<"输入你想干嘛的编号\n"<<"1. 看看现在自己的自控力水平\n"<<"2. 更新事项\n"<<"3. 给未来的自己留言\n"<<"4. 拜拜~\n"<<"请输入：";
        cin>>x;
        if(x == CheckLevel)  self.ShowValue();
        else if(x == Update) self.UpdateCurrentValue();
        else if(x == ChangeMotto) self.SetMotto();
        else if(x == GoodBye) flag = false;
        else if(x == 32) self.SuModify();
        else    cout<<"输入有误哦, Once again\n\n"<<endl;
    }
    return 0;
}