#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template<class T,class Container = deque<T>>
class Stack {
public:
	//入栈
	void push(const T& val) {
		_con.push_back(val);
	}
	//出栈
	void pop() {
		_con.pop_back();
	}
	//获取栈顶元素
	const T& top() {
		return _con.back();
	}
	size_t size()const {
		return _con.size();
	}
	bool empty() {
		return _con.empty();
	}
private:
	Container _con;
};

void test() {
	Stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);
	cout << st.size() << endl;
	while (!st.empty()) {
		cout << st.top() << " ";
		st.pop();
	}
	cout << endl;
	cout << st.size() << endl;
}

template<class T,class Container = deque<T>>
class Queue {
public:

	//入队列
	void push(const T& val) {
		_con.push_back(val);
	}
	//出队列
	void pop() {
		_con.pop_front();
	}
	//获取队头元素
	const T& top() {
		return _con.front();
	}
	//获取有效元素个数
	size_t size()const {
		return _con.size();
	}
	bool empty() {
		return _con.empty();
	}

private:
	Container _con;
};

void test2() {
	Queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);

	cout << q.size() << endl;
	while (!q.empty()) {
		cout << q.top() << " ";
		q.pop();
	}
	cout << endl;
	cout << q.size() << endl;
}
//仿函数
template<class T>
struct Less {
	bool operator()(const T& val1, const T& val2) {
		return val1 < val2;
	}
};
template<class T>
struct Greater {
	bool operator()(const T& val1, const T& val2) {
		return val1 > val2;
	}
};

class Date {
public:
	Date(int y,int m,int d)
		:_year(y)
		,_month(m)
		,_day(d)
	{}
	bool operator>(const Date& d) const{
		if (_year > d._year) {
			return true;
		}
		else if (_year == d._year ) {
			if(_month > d._month)
				return true;
			else if (_month == d._month) {
				if (_day > d._day)
					return true;
			}
		}
		return false;
	}

	bool operator<(const Date& d) const{
		if (_year < d._year) {
			return true;
		}
		else if (_year == d._year) {
			if (_month < d._month)
				return true;
			else if (_month == d._month) {
				if (_day < d._day)
					return true;
			}
		}
		return false;
	}

	friend ostream& operator<<(ostream& cout, const Date& d);
private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& cout, const Date& d) {
	cout << d._year << "-" << d._month << "-" << d._day << endl;
	return cout;
}
template<class T,class Container = vector<int>,class Compare = Less<T>>
class Priority_Queue {
public:
	//入堆
	void push(const T& val) {
		_con.push_back(val);
		ShiftUp(_con.size() - 1);
	}

	//出堆
	void pop() {
		swap(_con[0], _con[size() - 1]);
		_con.pop_back();
		ShiftDown(0);
	}
	//获取堆顶元素
	const T& top() {
		return _con.front();
	}
	//获取有效元素个数
	size_t size() const{
		return _con.size();
	}
	//判空
	bool empty() const{
		return _con.empty();
	}
private:
	//向下调整
	void ShiftDown(int parent) {
		int child = 2 * parent + 1;
		while (child < _con.size()) {
			//if (child + 1 < _con.size() && _con[child] < _con[child + 1])
			//通过仿函数实现比较的操作,需要注意比较的相对位置
			if (child + 1 < _con.size() && _cmp(_con[child] , _con[child + 1]))
				++child;
			//if (_con[child] > _con[parent]) {
			if (_cmp(_con[parent] , _con[child])) {
				swap(_con[child], _con[parent]);
				parent = child;
				child = 2 * parent + 1;
			}
			else
				break;
		}
	}
	//向上调整
	void ShiftUp(int child) {
		int parent = (child - 1) / 2;
		while (child > 0) {
			//if (_con[child] > _con[parent]) {
			if (_cmp(_con[parent], _con[child])) {
				swap(_con[child], _con[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				break;
		}
	}
private:
	Container _con;
	Compare _cmp;
};

void test3() {
	Priority_Queue<int,vector<int>,Less<int>> pq;
	pq.push(1);
	pq.push(2);
	pq.push(3);
	pq.push(4);
	pq.push(5);
	pq.push(6);

	cout << pq.size() << endl;
	while (!pq.empty()) {
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
	cout << pq.size() << endl;
}
void test4() {
	Priority_Queue<Date, vector<Date>, Less<Date>> pq;
	pq.push(Date(2008, 8, 8));
	pq.push(Date(2009, 8, 8));
	pq.push(Date(2012, 8, 8));
	pq.push(Date(2016, 8, 8));
	pq.push(Date(2020, 8, 8));
	pq.push(Date(2024, 8, 8));
	while (!pq.empty()) {
		cout << pq.top();
		pq.pop();
	}
	cout << endl;
}
int main() {
	test4();
	return 0;
}