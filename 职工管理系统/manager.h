#pragma once
#include<iostream>
#include"worker.h"
using namespace std;
#include<string>

class Manager :public Worker {
public:
		//��ʾ������Ϣ
		virtual void showInfo();
		//��ȡְ����λ����
		virtual string getDeptName();
		Manager(int id, string name, int dId);

};