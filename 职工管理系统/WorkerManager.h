#pragma once     //��ֹͷ�ļ��ظ�����
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
#include"worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#define FILENAME "empFile.txt"

class WorkerManager {
public :

	void Show_Menu();


	//��¼ְ������
	int m_EmpNum;

	//ְ������ָ��
	Worker** m_EmpArray;

	//���ְ��
	void Add_Emp();

	//�˳�ϵͳ
	void exitSystem();

	//�����ļ�
	void save();

	//ͳ������
	int get_EmpNum();

	//��ʼ��Ա��
	void init_Emp();

	//��ʾְ��
	void Show_Emp();

	//ɾ��ְ��
	void Del_Emp();
	
	//����ְ������ж�ְ���Ƿ���ڣ��������򷵻�ְ���������е�λ�ã����򷵻�-1
	int IsExist(int id);

	//�޸�ְ��
	void Mod_Emp();


	//����ְ��
	void Find_Emp();

	//����ְ��
	void Sort_Emp();

	//����ĵ�
	void Clean_File();
	//��־�ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;

	//���캯��
	WorkerManager();


	//��������
	~WorkerManager();
};


