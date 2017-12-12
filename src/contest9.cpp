#include <iostream>
#include <set>
#include <vector>

using namespace std;

void toLower_string(string & s) {
	int length = s.size();
	for(int i = 0; i < length; i++) {
		s[i] = tolower(s[i]);
	}
}

template<typename T>
bool contains(const std::set<T>& v, const T& value)
    {
        return v.find(value) != v.end();
    }

int main() {
	int n = 0;
	std::cin >> n;
	std::set<int> numbers;
	set<string> used;
	vector<string> all_words;
	for(int i = 0; i < n; i++) {
		string tmp;
		cin >> tmp;
		toLower_string(tmp);
		all_words.insert(all_words.end(), tmp);
	}
	int count = 0, m = 0;
	string ans;
	for(int i = 0; i < n; i++) {
		if(!contains(used, string(all_words[i]))) {
			for(int j = i; j < n; j++) {
				if(all_words[j] == all_words[i]) {
					count++;
				}
			}
		}
		if (count > m) {
			ans = all_words[i];
			m = count;
			count = 0;
		}
		count = 0;
	}
	cout << ans << " " << m;
	return 0;
}
