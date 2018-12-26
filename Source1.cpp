//stark_180706

#include <iostream>
#include <iomanip>
#include <string>
#include <dirent.h>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <algorithm>

using namespace std;

struct pl {
	string playerName;
	unsigned highscore;
	struct pl* next;
} players[10];

string **words;
string *prefix, *suffix;
int wordCount[10], scores[10], prefixCount, suffixCount;
unsigned score;
string *yourWords = new string[200];
int yourCount;

int getRandom(int max) {
	SYSTEMTIME st;
	GetSystemTime(&st);
	return st.wMilliseconds % max;
}
char check(int mode, string input, string qualifier) {
	system("cls");
	if (mode == 0) {
		if ((input.find(qualifier) != 0) || (input.length() <= qualifier.length())){
			cout << "Score: " << score << endl;
			cout << "Enter words beginning with " + qualifier << endl;
			cout <<"Uh Oh!" << endl;
		} else {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < wordCount[i]; j++) {
					if (words[i][j] == input) {
						for (int k = 0; k < yourCount; ++k) {
							if (yourWords[k] == input) {
								cout << "Score: " << score << endl;
								cout << "Enter words beginning with " + qualifier << endl;
								cout << "You can't enter the same word twice!" << endl;
								return getch();
							}
						}
						yourWords[yourCount++] = input;
						score += scores[i];
						cout << "Score: " << score << endl;
						cout << "Enter words beginning with " + qualifier << endl;
						cout << "Good Job! You get " << scores[i] << " points for that!" << endl;
						return getch();
					}
				}
			}
			cout << "Score: " << score << endl;
			cout << "Enter words beginning with " + qualifier << endl;
			cout <<"Uh Oh!" << endl;
		}
	} else {
		if ((input.rfind(qualifier) != input.length() - qualifier.length()) || (input.length() <= qualifier.length())) {
			cout << "Score: " << score << endl;
			cout << "Enter words ending with " + qualifier << endl;
			cout << "Uh Oh!" << endl;
		}
		else {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < wordCount[i]; j++) {
					if (words[i][j] == input) {
						for (int k = 0; k < yourCount; ++k) {
							if (yourWords[k] == input) {
								cout << "Score: " << score << endl;
								cout << "Enter words ending with " + qualifier << endl;
								cout << "You can't enter the same word twice!" << endl;
								return getch();
							}
						}
						yourWords[yourCount++] = input;
						score += scores[i];
						cout << "Score: " << score << endl;
						cout << "Enter words ending with " + qualifier << endl;
						cout << "Good Job! You get " << scores[i] << " points for that!" << endl;
						return getch();
					}
				}
			}
			cout << "Score: " << score << endl;
			cout << "Enter words ending with " + qualifier << endl;
			cout <<"Uh Oh!" << endl;
		}
	}
	return getch();
}

void writeFile() {
	ofstream outfile;
	outfile.open("highScores.txt", ios::out | ios::trunc);
	for (int i = 0; i < 10; ++i) {
		if (players[i].highscore > 0) {
			outfile << players[i].playerName << " " << players[i].highscore << endl;
		} else
			break;
	}
}

void updateHighScore() {
	string name, tempName, tempName2;
	int tempScore, tempScore2;
	system("cls");
	cout << "Congratulations! You made a new High Score." << endl;
	int millisecondCount = GetTickCount();
	while (GetTickCount() - millisecondCount < 1000) {}
	cout << "Enter Your Name Here: ";
	cin >> name;
	int i;
	for (i = 0; i < 10; ++i) {
		cout << score << " " << players[i].highscore << " " << players[i].playerName;
		if ( score > players[i].highscore) {
			tempScore = players[i].highscore;
			tempName = players[i].playerName;
			players[i].highscore = score;
			players[i].playerName = name;
			++i;
			break;
		}
	}
	for (; i < 10; ++i) {
		tempScore2 = players[i].highscore;
		tempName2 = players[i].playerName;
		players[i].highscore = tempScore;
		players[i].playerName = tempName;
		tempName = tempName2;
		tempScore = tempScore2;
	}
	writeFile();
}

void newLevel() {
	score = 0;
	yourCount = 0;
	int mode = getRandom(2);
	string pre, suf;
	if (mode == 0) {
		pre = prefix[getRandom(prefixCount)];
	} else {
		suf = suffix[getRandom(suffixCount)];
	}
	int millisecondCount = GetTickCount();
	string input = "";
	int temp = 0;
	char c;
	while (GetTickCount() - millisecondCount < 60000) {
		system("cls");
		cout << "Score: " << score << endl;
		cout << ((mode == 0) ? ("Enter words beginning with " + pre) : ("Enter words ending with " + suf)) << endl;
		cout << input;
		if (temp == 0)
			c = getch();
		if(isalpha(c)){
			input += c;
			temp = 0;
		} else if (c == '\b') {
			input = "";
			temp = 0;
		}
		else if (c == '\r') {
			transform(input.begin(), input.end(), input.begin(), ::tolower);
			if (mode == 0)
				c = check(mode, input, pre);
			else
				c = check(mode, input, suf);
			input = "";
			temp = 1;
		}
	}
	if (score > players[9].highscore)
		updateHighScore();
}

void displayProgress() {
	cout << "That was a nice game!" << endl;
	cout << "Your scored: " << score <<endl;
}
void displayHighScore() {
	system("cls");
	cout << "High Scores:" << endl << endl;
	for (int i = 0; i < 10; ++i) {
		cout << right << setw(5) << players[i].highscore << " " << players[i].playerName << endl;
	}
	cout << endl << endl << endl;
}

int main() {
	DIR *dir;
	struct dirent *ent;
	string x = "directory\\", path[241];
	int i = -2;
	if ((dir = opendir ("directory")) != NULL) {
	  /* Get all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {
		if (i >= 0)
			path[i] = x + ent->d_name;
		i++;
	  }
	  closedir (dir);
	} else {
	  /* Could not open directory */
	  cout << "There seems to be some issue, Please make sure that the directory folder has not been tampered.";
	  return 0;
	}
    /* Creating arrays to store words */
    words = new string*[10];
    words[0] = new string[4733], words[1] = new string[9372], words[2] = new string[46311], words[3] = new string[8992], words[4] = new string[42282], words[5] = new string[8258], words[6] = new string[18807], words[7] = new string[48943], words[8] = new string[174114], words[9] = new string[238458];
    prefix = new string[42], suffix = new string[39];
    /* Could not allocate memory */
    if (!words) {
    	cout << "Memory Allocation Failed!";
    	return 0;
    }
    for (int i = 0; i < 10; ++i) {
    	if (!words[i]) {
    		cout << "Memory Allocation Failed!";
    		return 0;
    	}
    }
    /* Array to stores word wordCounts */
    for (int i = 0; i < 10; i++)
		wordCount[i] = 0;
    prefixCount = 0, suffixCount = 0;
    /* Reading the files and storing the words */
    ifstream ifile;
    for (int i = 0; i < 241; i++) {
	   ifstream infile(path[i].c_str());
		string a;
		while (infile >> a){
			transform(a.begin(), a.end(), a.begin(), ::tolower);
			if ((path[i].at(path[i].length() - 2) == '1') && (path[i].at(path[i].length() - 1) == '0')) {
				words[0][wordCount[0]] = a;
				wordCount[0]++;
			} else if ((path[i].at(path[i].length() - 2) == '2') && (path[i].at(path[i].length() - 1) == '0')) {
				words[1][wordCount[1]] = a;
				wordCount[1]++;
			} else if ((path[i].at(path[i].length() - 2) == '3') && (path[i].at(path[i].length() - 1) == '5')) {
				words[2][wordCount[2]] = a;
				wordCount[2]++;
			} else if ((path[i].at(path[i].length() - 2) == '4') && (path[i].at(path[i].length() - 1) == '0')) {
				words[3][wordCount[3]] = a;
				wordCount[3]++;
			} else if ((path[i].at(path[i].length() - 2) == '5') && (path[i].at(path[i].length() - 1) == '0')) {
				words[4][wordCount[4]] = a;
				wordCount[4]++;
			} else if ((path[i].at(path[i].length() - 2) == '5') && (path[i].at(path[i].length() - 1) == '5')) {
				words[5][wordCount[5]] = a;
				wordCount[5]++;
			} else if ((path[i].at(path[i].length() - 2) == '6') && (path[i].at(path[i].length() - 1) == '0')) {
				words[6][wordCount[6]] = a;
				wordCount[6]++;
			} else if ((path[i].at(path[i].length() - 2) == '7') && (path[i].at(path[i].length() - 1) == '0')) {
				words[7][wordCount[7]] = a;
				wordCount[7]++;
			} else if ((path[i].at(path[i].length() - 2) == '8') && (path[i].at(path[i].length() - 1) == '0')) {
				words[8][wordCount[8]] = a;
				wordCount[8]++;
			} else if ((path[i].at(path[i].length() - 2) == '9') && (path[i].at(path[i].length() - 1) == '5')) {
				words[9][wordCount[9]] = a;
				wordCount[9]++;
			} else if (path[i].at(10) == 'p') {
				prefix[prefixCount] = a;
				prefixCount++;
			} else if (path[i].at(10) == 's') {
				suffix[suffixCount] = a;
				suffixCount++;
			}
		}
    }
    /* Reading player high scores */
    ifstream infile("highScores.txt");
    for (int i = 0; i < 10; i++) {
		if (!(infile >> players[i].playerName >> players[i].highscore)) {
			players[i].highscore = 0;
			players[i].playerName = "Unknown";
		}
    }
    /* Assigning scores to different type of words */
    scores[0] = 10, scores[1] = 20, scores[2] = 35, scores[3] = 40, scores[4] = 50, scores[5] = 55, scores[6] = 60, scores[7] = 70, scores[8] = 80, scores[9] = 95;
    /* Starting up */
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPress any key to start.";
	getch();
	while(1) {
		system("cls");
		checkpoint:
		cout << "Press 'A' to Play, Press 'B' to Display HighScores, Press 'C' to Exit" << endl;
		char c = getch();
		if (c =='A' || c == 'a') {
			newLevel();
			system("cls");
			displayProgress();
		}
		else if (c == 'B' || c == 'b') {
			displayHighScore();
			goto checkpoint;
		}
		else if (c == 'C' || c == 'c')
			break;
		else
			goto checkpoint;
	}
	system("cls");
	cout << "Good Bye!";
	return 0;
}
