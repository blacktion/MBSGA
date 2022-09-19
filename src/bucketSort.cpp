#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <queue>
#include <list>
using namespace std;
const int n = 0x200000;
const int mod = 0x1fffff;

vector<long long> sortNum, sortedNum;
long long cache[n];
int que[2][n], cont[2], st[2], ed[2];

template<typename T>
T RandT(T _min, T _max){
	T temp;
	if (_min > _max)
	{
		temp = _max;
		_max = _min;
		_min = temp;
	}
	return rand() / (double)RAND_MAX *(_max - _min) + _min;
}

void bucketSort() {

	st[0] = 0; st[1] = 0; ed[0] = 0; ed[1] = 0;
	int category;
	bool finish = false;
	for (int i = 0; i < sortNum.size(); i++) {
		cache[i] = sortNum[i];
		category = sortNum[i] & 1;
		que[category][ed[category]++] = i;
		cont[category]++;
	}
	int p;
	for (int bit = 0; bit < 32; bit++) {
		for (int i = 0; i < 2; i++) {
			int limit = 0;
			while (limit < cont[i]) {
				p = que[i][st[i]++];
				if (cache[p] >> 1 == 0) {
					sortedNum.push_back(sortNum[p]);
				}
				else {
					cache[p] >>= 1;
					category = cache[p] & 1;
					que[category][ed[category]++] = p;
				}
				limit++;
				st[0] &= mod; st[1] &= mod;
				ed[0] &= mod; ed[1] &= mod;
			}
		}
		for (int i = 0; i < 2; i++) {
			if (ed[i] >= st[i]) {
				cont[i] = ed[i] - st[i];
			}
			else {
				cont[i] = n - st[i] + ed[i];
			}
		}
	}
}

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
	int num = 1000000;
	time_t start, end;
	srand((unsigned)time(NULL));
	for (int i = 0; i < num; i++) {
		sortNum.push_back(RandT<long long>(1, num));
	}
	
	//show(1);
	start = clock();
	bucketSort();
	end = clock();
	cout << "bucketSort: " << end - start << endl;
	//show(2);

	start = clock();
	sort(sortNum.begin(), sortNum.end());
	end = clock();
	cout << "quickSort: " << end - start << endl;

	bool flag = true;
	for (int i = 0; i < num; i++) {
		if (sortNum[i] != sortedNum[i]) {
			flag = false;
			break;
		}
	}

	if (flag) {
		cout << "Bucket sort is right!" << endl;
	}
	else {
		cout << "Bucket sort is wrong!" << endl;
	}

	return 0;
}
