#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
/* Задание 1. Дан текстовый файл. Удалить из него послед-
 нюю строку. Результат записать в другой файл.
 */
void noLastLine(string in_filename, string out_filename) {
	vector<string> lines;
	string line;
	fstream in;
	fstream out;
	in.open(in_filename, ios::in);
	out.open(out_filename, ios::out);
	while (getline(in, line)) {
		lines.push_back(line);
	}
	for_each(lines.begin(), lines.end() - 1, [&out](auto l) {
		out << l << endl;
	});
	in.close();
	out.close();
}

/* Задание 2. Дан текстовый файл. Найти длину самой
 длинной строки.
 */
int longestLine(string in_filename) {
	size_t max { };
	string line;
	fstream in;
	in.open(in_filename, ios::in);
	while (getline(in, line))
		if (line.size() > max)
			max = line.size();
	in.close();
	return max;
}

/* Задание 3. Дан текстовый файл. Посчитать сколько раз
 в нем встречается заданное пользователем слово.*/
int countWord(string in_filename, string word) {
	size_t count { };
	string line;
	fstream in;
	in.open(in_filename, ios::in);
	while (getline(in, line)) {
		auto found = line.find(word);
		while (found != string::npos) {
			++count;
			found = line.find(word, found + 1);
		}
	}
	in.close();
	return count;
}

/*Задание 4. Дан текстовый файл. Найти и заменить в нем
 заданное слово. Что искать и на что заменять определя-
 ется пользователем.
 */
void replace_all(string &s, string &toReplace, string &replaceWith) {
	ostringstream oss;
	size_t pos = 0;
	size_t prevPos = pos;

	while (1) {
		prevPos = pos;
		pos = s.find(toReplace, pos);
		if (pos == std::string::npos)
			break;
		oss << s.substr(prevPos, pos - prevPos);
		oss << replaceWith;
		pos += toReplace.size();
	}

	oss << s.substr(prevPos);
	s = oss.str();
}

void replaceWord(string in_filename, string out_filename, string toReplace,
		string replaceWith) {
	string line;
	fstream in;
	fstream out;
	in.open(in_filename, ios::in);
	out.open(out_filename, ios::out);
	while (getline(in, line)) {
		replace_all(line, toReplace, replaceWith);
		out << line << endl;
	}
}

int main() {
	string r = "read.txt", w = "write.txt";

	noLastLine(r, w);

	cout << longestLine(r) << endl;
	cout << countWord(r, "daliaunce") << endl;

	replaceWord(r, w, "daliaunce", "romantic relationship");

	cout << "That's all, folks!" << endl;
	return 0;
}
