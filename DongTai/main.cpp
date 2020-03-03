#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Dongtai {
	string str;
	double bi = 0.0;
};

int max_in_list(vector<vector<int>>* cell) {
	int max_int = 0;
	for (vector<vector<int>>::iterator it_y = cell->begin(); it_y < cell->end(); ++it_y) {
		for (vector<int>::iterator it_x = it_y->begin(); it_x < it_y->end(); ++it_x) {
			if (*it_x > max_int) {
				max_int = *it_x;
			}
		}
	}
	return max_int;
}

int max(int* num_list, int length) {
	int max_int = 0;
	for (int i = 0; i < length; i++) {
		if (*(num_list + i) > max_int) {
			max_int = *(num_list + i);
		}
	}
	return max_int;
}

vector<Dongtai>* dongtai(string str, vector<string>* str_list) {
	// 创建结果返回列表
	vector<Dongtai>* result = new vector<Dongtai>(str_list->size());
	for (int index = 0; index < str_list->size(); index++) {
		// 创建表格
		vector<vector<int>>* cell = new vector<vector<int>>(str.size(), vector<int>((*str_list)[index].size()));
		for (int y = 0; y < str.size(); y++) {
			for (int x = 0; x < (*str_list)[index].size(); x++) {
				bool eq = str[y] == (*str_list)[index][x];
				if (x == 0 && y == 0) {
					if (eq) {
						(*cell)[y][x] = 1;
					}
					else {
						(*cell)[y][x] = 0;
					}
				}
				else if (x == 0) {
					if (eq) {
						(*cell)[y][x] = 1 + (*cell)[y - 1][x];
					}
					else {
						(*cell)[y][x] = (*cell)[y - 1][x];
					}
				}
				else if (y == 0) {
					if (eq) {
						(*cell)[y][x] = 1 + (*cell)[y][x - 1];
					}
					else {
						(*cell)[y][x] = (*cell)[y][x - 1];
					}
				}
				else {
					int list[] = { (*cell)[y][x - 1], (*cell)[y - 1][x], (*cell)[y - 1][x - 1] };
					if (eq) {
						(*cell)[y][x] = 1 + max(list, 3);
					}
					else {
						(*cell)[y][x] = max(list, 3);
					}
				}
			}
		}
		Dongtai dong;
		dong.str = (*str_list)[index];
		int result_num = max_in_list(cell);
		if (str.size() < (*str_list)[index].size()) {
			dong.bi = (double)result_num / (double)(*str_list)[index].size();
		}
		else {
			dong.bi = (double)result_num / (double)str.size();
		}
		(*result)[index] = dong;
		delete cell;
	}
	return result;
}

int main(void) {
	vector<string> str_list = { "123", "12345", "1234567" };
	vector<Dongtai>* result = dongtai(string("12345"), &str_list);
	for (vector<Dongtai>::iterator it = result->begin(); it < result->end(); ++it) {
		cout << "'" << it->str << "'与'12345'的相似度为：" << it->bi * 100 << "%" << endl;
	}
	delete result;
	system("pause");
	return 0;
}