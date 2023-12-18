#include <iostream>
#include <string>
#include <vector>

using std::cin; using std::cout;
using std::endl;
using std::string; 
using std::vector;

int main() 
{
	char ch;
	int a_cnt = 0, e_cnt = 0, 
		i_cnt = 0, o_cnt = 0, u_cnt = 0, 
		other_cnt = 0;
	while (cin >> ch && ch != '\n') {
		switch (ch) {
			case 'a':
			case 'A':
				++a_cnt;
				break;
			case 'e':
			case 'E':
				++e_cnt;
				break;
			case 'i':
			case 'I':
				++i_cnt;
				break;
			case 'o':
			case 'O':
				++o_cnt;
				break;
			case 'u':
			case 'U':
				++u_cnt;
				break;
			default:
				++other_cnt;
				break;
		}
	}
	cout << "a/A: " << a_cnt << endl;
	cout << "e/E: " << e_cnt << endl;
	cout << "i/I: " << i_cnt << endl;
	cout << "o/O: " << o_cnt << endl;
	cout << "u/U: " << u_cnt << endl;
	cout << "other: " << other_cnt << endl;

	return 0;
}
