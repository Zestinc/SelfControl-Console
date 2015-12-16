//
//  selfcontrol.h
//  SelfControl
//
//  Created by Zestinc on 15/9/17.
//  Copyright (c) 2015年 Zestinc. All rights reserved.
//

#ifndef SelfControl_selfcontrol_h
#define SelfControl_selfcontrol_h

#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

enum {msleep = 0, target, event_long_time, event_short_time, waste_long, waste_short, break_long, break_short, cancel};

class selfControl
{
private:
    int maxValue;
    int currentValue;
    int exp;
    char motto[200];
    //    int finishWork;
    //    int date;
    //更新当前经验值
    void UpdateExp(int x);
    //更新文件
    void UpdateFiles();
    //初始化文件
    void Initial();
    
public:
    void ShowMotto();
    void SetMotto();
    //获得文件的数值
    void GetValue();
    //更新当前的自控力数值
    void UpdateCurrentValue();
    //显示当前的自控力水平
    void ShowValue();
    //清屏
    void ClearScreen();
    //超级更改
    void SuModify();
    
};

void selfControl::ShowMotto(){
    ClearScreen();
    FILE *fin = fopen("motto", "r");
    if(fin==NULL)
    {
        FILE *fout = fopen("motto", "w");
        fprintf(fout, "要加油哦");
        fclose(fout);
        fin = fopen("motto", "r");
    }
    fscanf(fin, "%s", motto);
    printf("%s\n", motto);
    sleep(3);
}

void selfControl::SetMotto(){
    ClearScreen();
    cout<<"请输入给未来自己的留言：（回车结束）"<<endl;
    scanf("%s", motto);
    FILE *fout = fopen("motto", "w");
    fprintf(fout, "%s", motto);
    fclose(fout);
}

void selfControl::SuModify(){
    ShowValue();
    cout<<"请输入自控力值上限"<<endl;
    cin>>maxValue;
    cout<<"请输入当前自控力值"<<endl;
    cin>>currentValue;
    UpdateFiles();
    ClearScreen();
}

void selfControl::ClearScreen(){
    for(int i = 0; i < 30; i++)
        printf("\n\n\n");
}

void selfControl::UpdateFiles(){
    FILE *fout = fopen("self_control_value", "w");
    char ch = maxValue;
    fprintf(fout, "%c", ch);
    ch = currentValue;
    fprintf(fout, "%c", ch);
    ch = exp;
    fprintf(fout, "%c", ch);
    fclose(fout);
}

void selfControl::Initial(){
    FILE *fout = fopen("self_control_value", "w");
    char ch = 30;
    fprintf(fout, "%c", ch);
    fprintf(fout, "%c", ch);
    ch = 0;
    fprintf(fout, "%c", ch);
    fclose(fout);
}

void selfControl::GetValue(){
    FILE *fin = fopen("self_control_value", "r");
    if(fin == NULL){
        Initial();
        fin = fopen("self_control_value", "r");
        if(fin == NULL) {
            cout<<"初始化出错"<<endl;
            exit(-1);
        }
        else    cout<<"初始文件创建成功"<<endl;
    }
    char ch;
    fscanf(fin, "%c", &ch);
    maxValue = ch;
    fscanf(fin, "%c", &ch);
    currentValue = ch;
    fscanf(fin, "%c", &ch);
    exp = ch;
    fclose(fin);
}

void selfControl::ShowValue(){
    ClearScreen();
    cout<<"当前自控力上限为"<<maxValue<<endl;
    cout<<"当前的自控力数值为"<<currentValue<<endl;
    if(currentValue<=5) cout<<"当前自控力水平较低，建议进行娱乐休息吃饭等活动"<<endl;
    else if(currentValue == maxValue) cout<<"平心静气，想想清单还有什么要干的，马上动手"<<endl;
    else if(currentValue < maxValue && currentValue > 5) cout<<"加油，再加把劲"<<endl;
    else
    {
        cerr<<"似乎出现了什么错误"<<endl;
        exit(-1);
    }
    cout<<"\n\n看完了吧? 看完了点**回车**就回到主菜单啦！！！"<<endl;
    string st;
    cin.clear();    //这里如果用cin.clear(istream::failbit); 是不行的
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    getchar();
    ClearScreen();
}

void selfControl::UpdateCurrentValue(){
    ClearScreen();
    bool flag = true;
    while(flag){
        flag = false;
        cout<<"请输入活动代码:\n"
        <<"0. 睡了一觉\n"
        <<"1. 达成了一个长期坚持的目标！！！\n"
        <<"2. 完成了一件费时的事情\n"
        <<"3. 完成了一件琐碎的事情\n"
        <<"4. 浪费了大量的时间在不应的事情上T T\n"
        <<"5. 莫名奇妙干了些别的事情= =!!!（浪费了少量时间）\n"
        <<"6. 好好的休息了一把\n"
        <<"7. 稍微休息了一下下\n"
        <<"8. 手滑了，取消\n"
        <<"请输入：";
        int select;
        cin>>select;
        cout<<endl;
        if(select == msleep){
            currentValue = maxValue;
        }
        else if(select == target){
            UpdateExp(100);
            currentValue -= 20;
        }
        else if(select == event_long_time){
            UpdateExp(20);
            currentValue -= 10;
        }
        else if(select == event_short_time){
            UpdateExp(5);
            currentValue -= 1;
        }
        else if(select == waste_long){
            UpdateExp(-30);
            cout<<"失控乃兵家常事，找找原因，不用气馁"<<endl;
            currentValue -= 5;
        }
        else if(select == waste_short){
            currentValue -= 2;
            UpdateExp(2);
        }
        else if(select == break_long){
            currentValue += 20;
        }
        else if(select == break_short){
            currentValue += 10;
        }
        else if(select == cancel){
            return ;
        }
        else
        {
            cout<<"输入错误=0=, 再输入一次吧"<<endl;
            flag = true;
        }
    }
    
    cout<<"~~~更新完毕~~~"<<endl;
    
    if(currentValue > maxValue)
    {
        currentValue = maxValue;
        cout<<"平心静气，回忆目标，前进！\n";
    }
    else if (currentValue == 0)
    {
        cout<<"没有自控力啦~~~~~~好好休息一下，看看感兴趣的演讲，电影，书，动漫什么的"<<endl;
    }
    else if (currentValue < 0)
    {
        currentValue = 0;
        cout<<"自控力透支了噢，真不知道说你厉害还是厉害好\(^o^)/~，好好休息一下，看看感兴趣的演讲，电影，书，动漫什么的"<<endl;
    }
    else
    {
        cout<<"继续加油~~！！"<<endl;
    }
    cin.clear();    //这里如果用cin.clear(istream::failbit); 是不行的
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout<<"\n\n点回车回去主菜单=0="<<endl;
    getchar();
    
    UpdateFiles();
}

void selfControl::UpdateExp(int x){
    exp += x;
    if(exp >= 70+maxValue){
        exp -= 100;
        maxValue ++;
        cout<<"升级啦，升级啦~~~~~自控力上限提高了噢！！！！！！！！！！吼吼吼！"<<endl;
    }
    else if(exp < 0){
        exp += 70;
        maxValue --;
        cout<<"玩物丧志，自控力上限又下降了"<<endl;
    }
}
#endif
