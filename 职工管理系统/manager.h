#pragma once
#include<iostream>
#include"worker.h"
using namespace std;
#include<string>

class Manager :public Worker {
public:
		//显示个人信息
		virtual void showInfo();
		//获取职工岗位名称
		virtual string getDeptName();
		Manager(int id, string name, int dId);

};