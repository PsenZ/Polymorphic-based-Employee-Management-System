#include "WorkerManager.h"


//构造函数
WorkerManager::WorkerManager() {
	//初始化属性
	this->m_EmpNum = 0;
	this->m_EmpArray = NULL;

	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//文件不存在的情况
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;//测试输出
		this->m_EmpNum = 0;//初始化人数
		this->m_FileIsEmpty = true;//初始化文件为空标志
		this->m_EmpArray = NULL;//初始化数组指针
		ifs.close();//关闭文件
		return;
	}

	//文件存在，并且没有记录，数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空！" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}


	int num = this->get_EmpNum();
	cout << "职工个数为：" << num << endl;
	this->m_EmpNum = num;


	//根据职工数创建数组
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//初始化职工
	init_Emp();


	//测试
	for (int i = 0; i < m_EmpNum; i++) {
		cout << "职工号：" << this->m_EmpArray[i]->m_Id;
		cout << "职工姓名：" << this->m_EmpArray[i]->m_Name;
		cout << "部门编号：" << this->m_EmpArray[i]->m_DeptId<<endl;
	}


}

//析构函数
WorkerManager::~WorkerManager() {
	if (this->m_EmpArray != NULL) {
		delete[]this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}


 

void WorkerManager::Add_Emp() {
	cout << "请输入加入职工的数量" << endl;
	int addNum = 0;//保存用户的输入数量

	cin >> addNum;

	if (addNum > 0) {
		//计算新空间的大小
		int newSize = this->m_EmpNum + addNum;
		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原空间下内容存放到新空间下
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}

		}
		for (int i = 0; i < addNum; i++) {
			int id;  //职工编号
			string name; //职工姓名
			int dSelect;  //部门选择

			cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
			cin >> id;

			cout << "请输入第" << i + 1 << "新职工姓名：" << endl;
			cin >> name;

			cout << "请选择职工的岗位" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker =new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//将创建职工职责，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;

		}

		//释放原有空间
		delete[] this->m_EmpArray;
		//更改新空间指向
		this->m_EmpArray = newSpace;
		//更新新的职工人数
		this->m_EmpNum = newSize;

		//更新职工不为空的标志
		this->m_FileIsEmpty = false;

		cout << "成功添加" <<addNum<<"名新职工！" << endl;

		//保存到文件中
		this->save();
	}
	else {
		cout << "输入的数据有误" << endl;
	}
	
	//按任意键清屏，清屏回到上级目录
	system("pause");
	system("cls");
}

void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_Id << " " 
			<< this->m_EmpArray[i]->m_Name << " " 
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	ofs.close();
}

int WorkerManager::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;	
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		//记录人数
		num++;

	}
	ifs.close();
	return num;
}


void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		Worker* worker = NULL;

		//根据不同部门的ID创建不同的对象
		if (dId == 1) {               //普通员工
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) {          //经理
			worker = new Manager(id, name, dId);
		}
		else {                        //老板
			worker = new Boss(id, name, dId);
		}
		//存放在数组中
		this->m_EmpArray[index] = worker;
		index++;
	}
}

void WorkerManager::Show_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {
			//利用多态调用接口
			this->m_EmpArray[i]->showInfo();

		}
	}
	system("pause");
	system("cls");
}


int WorkerManager::IsExist(int id) {
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->m_Id == id) {
			index = i;
			break;
		}
	}

	return index;
}

void WorkerManager::Del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空！！";
	}

	else {
		//按照职工编号删除
		cout << "请输入想要删除的职工号";
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1) {    //index上位置上的数据要删除一下子
			for (int i = index; i < this->m_EmpNum; i++) {
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;

			this->save();
			cout << "删除成功！" << endl;
		}
		else {
			cout << "删除失败，未找到该职工" << endl;
		}

	}
	system("pause");
	system("cls");
}


//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		return;
	}

	cout << "请输入修改职工的编号：" << endl;
	int id;
	cin >> id;
	cin.get();

	for (int i = 0; i < m_EmpNum; i++)
	{
		if (id == m_EmpArray[i]->m_Id)
		{
			//查到此人
			cout << "查到: " << id << "号职工，请输入新职工号： " << endl;

			int newId = 0;
			cin >> newId;
			cin.get();

			cout << "请输入新姓名：" << endl;
			string newName = "";
			cin >> newName;
			cin.get();

			cout << "请输入岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			int dSelect;
			cin >> dSelect;
			cin.get();

			m_EmpArray[i]->m_Id = newId;
			m_EmpArray[i]->m_Name = newName;

			cout << "修改成功" << endl;
			this->save();

			return;
		}
	}

	cout << "修改失败，查无此人" << endl;
}





// 查找职工
void WorkerManager::Find_Emp(){
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int select = 0;
		cin >> select;


		if (select == 1) //按职工号查找
		{
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;

			int ret = IsExist(id);
			if(ret != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if (select == 2) //按姓名查找
		{
			string name;
			cout << "请输入查找的姓名：" << endl;
			cin >> name;

			bool flag = false;  //查找到的标志
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功,职工编号为："
						<< m_EmpArray[i]->m_Id
						<< " 号的信息如下：" << endl;

					flag = true;

					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				//查无此人
				cout << "查找失败，查无此人" << endl;
			}
		}
		else
		{
			cout << "输入选项有误" << endl;
		}
	}


	system("pause");
	system("cls");
}



void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件记录不存在或者记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "请选择排序方式： " << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;

		int select = 0;
		cin >> select;

		for (int i = 0; i < m_EmpNum; i++) {
			int minOrMax = i;
			for (int j = i + 1; j < m_EmpNum; j++) {
				if (select == 1) {
					if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
				else {
					if (m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
			}
			if (i != minOrMax) {
				Worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "排序成功，排序后的结果为：" << endl;
		this->save();
		this->Show_Emp();
	}


}

void WorkerManager::Clean_File() {
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;
	

	int select = 0;
	cin >> select;
	
	if (select == 1) {
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL) {
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;

		}
		cout << "清空已完成！！" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::exitSystem(){

	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);

}




