#if 0
#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <queue>
#include <list>
using namespace std;
const int n = 2e6 + 10;

template<typename T>
T RandT(T _min, T _max)
{
	T temp;
	if (_min > _max)
	{
		temp = _max;
		_max = _min;
		_min = temp;
	}
	return rand() / (double)RAND_MAX *(_max - _min) + _min;
}


vector<long long> sortNum, sortedNum;

struct node {
	long long num;
	long long solve;
	int cont = 0;
}cache[n], cache2[n];

list<int> bucketP[10];
queue<int> bucketN[10];

queue<int> bucket4[10], bucket5[2];
int cont4[10], cont5[2];
long long cache4[n], cache5[n];
int que[2][n], st[2], ed[2];


void bucketSort2() {
	int limitSize = 0;
	bool finish = false;
	for (int i = 0; i < sortNum.size(); i++) {
		cache[i].cont = 0;
		cache[i].num = sortNum[i];
		cache[i].solve = sortNum[i];
		bucketP[cache[i].solve % 10].push_back(i);
	}
	while (!finish) {
		finish = true;
		for (int i = 0; i < 10; i++) {
			if (bucketP[i].empty()) {
				continue;
			}
			finish = false;
			list<int>::iterator p = bucketP[i].begin();
			while (p != bucketP[i].end() && limitSize == cache[*p].cont) {
				if (cache[*p].solve / 10 == 0) {
					sortedNum.push_back(cache[*p].num);
				}
				else {
					cache[*p].solve /= 10;
					bucketP[cache[*p].solve % 10].push_back(*p);
					cache[*p].cont++;
				}
				p = bucketP[i].erase(p);
			}
		}
		limitSize++;
	}
}

void bucketSort3() {
	int limitSize = 0;
	bool finish = false;
	for (int i = 0; i < sortNum.size(); i++) {
		cache2[i].cont = 0;
		//cache2[i].num = sortNum[i];
		cache2[i].solve = sortNum[i];
		bucketN[sortNum[i] % 10].push(i);
	}
	while (!finish) {
		finish = true;
		for (int i = 0; i < 10; i++) {
			while (!bucketN[i].empty() && limitSize == cache2[bucketN[i].front()].cont) {
				finish = false;
				int p = bucketN[i].front();
				if (cache2[p].solve / 10 == 0) {
					sortedNum.push_back(cache2[p].num);
				}
				else {
					cache2[p].solve /= 10;
					bucketN[cache2[p].solve % 10].push(p);
					cache2[p].cont++;
				}
				bucketN[i].pop();
			}
		}
		limitSize++;
	}
}

void bucketSort4() {
	bool finish = false;
	for (int i = 0; i < sortNum.size(); i++) {
		cache4[i] = sortNum[i];
		bucket4[sortNum[i] % 10].push(i);
		cont4[sortNum[i] % 10]++;
	}
	while (!finish) {
		finish = true;
		for (int i = 0; i < 10; i++) {
			int limit = 0;
			while (!bucket4[i].empty() && limit < cont4[i]) {
				finish = false;
				int p = bucket4[i].front();
				if (cache4[p] / 10 == 0) {
					sortedNum.push_back(sortNum[p]);
				}
				else {
					cache4[p] /= 10;
					bucket4[cache4[p] % 10].push(p);
				}
				bucket4[i].pop();
				limit++;
			}
		}
		for (int i = 0; i < 10; i++) {
			cont4[i] = bucket4[i].size();
		}
	}
}

void bucketSort5 () {

	st[0] = 0; st[1] = 0; ed[0] = 0; ed[1] = 0;
	bool finish = false;
	for (int i = 0; i < sortNum.size(); i++) {
		cache5[i] = sortNum[i];
		//bucket5[sortNum[i] & 1].push(i);
		que[sortNum[i] & 1][ed[sortNum[i] & 1]++] = i;
		cont5[sortNum[i] & 1]++;
	}
	int p;
	for (int bit = 0; bit < 32; bit++) {
		for (int i = 0; i < 2; i++) {
			int limit = 0;
			while (limit < cont5[i]) {
				//int p = bucket5[i].front();
				p = que[i][st[i]++];
				if (cache5[p] >> 1 == 0) {
					sortedNum.push_back(sortNum[p]);
				}
				else {
					cache5[p] >>= 1;
					//bucket5[cache5[p] & 1].push(p);
					que[cache5[p] & 1][ed[cache5[p] & 1]++] = p;
				}
				limit++;
				st[0] %= n; st[1] %= n;
				ed[0] %= n; ed[1] %= n;
			}
		}
		for (int i = 0; i < 2; i++) {
			if (ed[i] >= st[i]) {
				cont5[i] = ed[i] - st[i];
			}
			else {
				cont5[i] = n - st[i] + ed[i];
			}
		}
	}
}

//queue<long long*>bu[2];
//int ct[2] = { 0 };
//void twoBucketSort() {
//	bool finish = false;
//	for (long long &x : sortNum) {
//		bu[x & 1].push(&x);
//	}
//	ct[0] = bu[0].size();
//	ct[1] = bu[1].size();
//	long long limit = 1;
//	while (!finish) {
//		finish = true;
//		for (int i = 0; i < 2; i++) {
//			int cont = 0;
//			while (!bu[i].empty() && cont < ct[i]) {
//				finish = false;
//				long long* p = bu[i].front();
//				if (*p < limit) {
//					sortedNum.push_back(*p);
//				}
//				else {
//					bu[((*p) >> limit) & 1].push(p);
//				}
//				bu[i].pop();
//				cont++;
//			}
//		}
//		for (int i = 0; i < 2; i++) {
//			ct[i] = bu[i].size();
//		}
//		limit <<= 1;
//	}
//}

void show(int type) {
	if (type == 1) {
		for (auto &x : sortNum) {
			cout << x << " ";
		}
	}
	else if (type == 2) {
		for (auto &x : sortedNum) {
			cout << x << " ";
		}
	}
	cout << endl;
}



int main()
{
	time_t start, end;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 100000; i++) {
		sortNum.push_back(RandT<long long>(1, 100000));
	}
	/*show(1);
	start = clock();
	bucketSort4();
	end = clock();
	cout << "bucketSort4: " << end - start << endl;
	show(2);

	vector<long long>vec;
	{
		sortedNum.clear();
		swap(sortedNum, vec);
	}

	show(1);
	start = clock();
	bucketSort3();
	end = clock();
	cout << "bucketSort3: " << end - start << endl;
	show(2);*/

	//show(1);
	start = clock();
	bucketSort5();
	end = clock();
	cout << "bucketSort5: " << end - start << endl;
	//show(2);

	start = clock();
	sort(sortNum.begin(), sortNum.end());
	end = clock();
	cout << "quickSort: " << end - start << endl;



	return 0;
}

#endif

#if 0
#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <cmath>
#include <string>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <stack>
#include <unordered_set>
#include <set>
#include <map>
#include <sstream>
#include <queue>
#include <memory>
#include <vector>
#include <climits>
#include <array>
#include <functional>
#include <chrono>
#include <variant>
using namespace std;
using namespace chrono;

void bucket_sort(vector<int> &v) {
	queue<int> bucket[2][10];

	for (const auto &n : v) {
		bucket[0][n % 10].push(n);
	}

	int v_index = 0;
	for (int prev_index = 0, next_index = 1, n = 10; n <= 1000000000; swap(prev_index, next_index), n *= 10) {
		for (int j = 0; j < 10; ++j) {
			while (!bucket[prev_index][j].empty()) {
				int front = bucket[prev_index][j].front();
				bucket[prev_index][j].pop();
				if (front < n) {
					v[v_index] = front;
					++v_index;
				}
				else {
					bucket[next_index][(front / n) % 10].push(front);
				}
			}
		}
	}
	// 1000000000 - INT_MAX
	// 10 prev_index = 0, next_index = 1
	// 100 prev_index = 1, next_index = 0
	// ...
	// 10000000000 prev_index = 1, next_index = 0
	for (int j = 1; j < 3; ++j) {
		while (!bucket[1][j].empty()) {
			int front = bucket[1][j].front();
			bucket[1][j].pop();
			v[v_index] = front;
			++v_index;
		}
	}
}

void print_vector(const vector<int> &v) {
	for (const auto &n : v) {
		cout << n << ' ';
	}
	cout << endl;
}

int main()
{
	time_t start, end;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 1; ++i) {
		vector<int> num, s, b;

		for (int j = 0; j < 1000000; ++j) {
			num.push_back(rand());
		}

		s = num;
		b = num;

		start = clock();
		sort(s.begin(), s.end());
		end = clock();
		cout << end - start << endl;

		start = clock();
		bucket_sort(b);
		end = clock();
		cout << end - start << endl;

		if (s != b) {
			cout << "Diff" << endl;
			print_vector(num);
			print_vector(s);
			print_vector(b);
			break;
		}
	}
}
#endif

