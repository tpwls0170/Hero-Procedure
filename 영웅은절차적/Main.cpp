// 영웅은 절차적
	/*
		1) 텍스트로 진행되는 게임
		2) 게임이 시작되면 영웅의 이름과 난이도를 입력
		3) 난이도에 따라서 영웅의 HP / 만나게 되는 몬스터의 숫자가 변동
		4) 게임이 시작되면 마지막 몬스터를 잡을 때까지 전투가 진행되는 방식
		5) 몬스터를 잡으면 랜덤하게 돈을 획득한다. (0 ~ 100)
		6) 몬스터를 잡으면 던전을 계속 탐험할지 상점을 들를지 결정한다.
		7) 상점을 들르면 돈을 소모해서 HP를 회복할 수 있다.
		8) 전투는 가위 바위 보로 이루어진다. (비기면 승패가 정해질 때까지 반복)
		지면 HP가 소모 (몬스터는 1번 지면 사망)
		9) 몬스터를 다 잡으면 클리어 HP가 0이 되면 게임 오버
		10) 클리어시 엔딩 멘트 출력
	*/
#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>
#include <Windows.h>
using namespace std;

void MainbackGround();

struct Hero {
	string Hero_Name;
	int Hero_HP{ 0 };
	int Money{ 0 };
	int Hero_Attack{ 0 };
	int px{ 0 }, py{ 0 };	// 좌표값
};

struct Monster {
	int Monster_Attack{ 0 };
	int Monster_Hp{ 0 };
	int Monster_Cnt{ 0 };
	int MonsterPosX[5];		// 몬스터 위치값 저장 나중에 동적할당 배우면 수정가능하도록
	int MonsterPosY[5];
	int ex{ 0 }, ey{ 0 }; // 몬스터 생성및 위치 좌표값

};

int main()
{
	int difficulty_Select;	// 난이도 선택

	//플레이어 변수
	string Hero_Name;
	int Hero_HP = 0;
	int Money{ 0 };
	int Hero_Attack = 0;
	int px = 0, py = 0;	// 좌표값

	srand(time(NULL));
	//몬스터 변수
	int Monster_Attack = 0;
	int Monster_Hp = 0;
	int Monster_Cnt = 0;
	int MonsterPosX[5];		// 몬스터 위치값 저장 나중에 동적할당 배우면 수정가능하도록
	int MonsterPosY[5];
	int ex = 0, ey = 0; // 몬스터 생성및 위치 좌표값
	//맵관련 변수
	int EXODUS_Map[10][10] = { 0 };
	char keyDown = 0;
	EXODUS_Map[0][0] = 1;	// 시작시점
	EXODUS_Map[0][5] = 3;
	MainbackGround();
	//cout << "영웅의 이름을 입력하세요" << endl;
	//cin >> Hero_Name;
	cout << "난이도를 선택하세요 1) 초보 2) 중수 3) 고수 4) 신" << endl;
	cin >> difficulty_Select;
	if (difficulty_Select == 1) {
		Hero_HP = 50;
		cout << "초보 난이도 선택 던전에 입장합니다" << endl;
		int MonsterCreate_cnt{ 0 };
		while (MonsterCreate_cnt < 5) {
			ex = rand() % 10;
			ey = rand() % 10;
			if ((ex == 0 && ey == 0) || (ex == 0 && ey == 5))
				continue;
			else {
				MonsterPosX[MonsterCreate_cnt] = ex;
				MonsterPosY[MonsterCreate_cnt] = ey;
				++MonsterCreate_cnt;
			}
		}
		for (int i = 0; i < 5; ++i) {
			ex = MonsterPosX[i];
			ey = MonsterPosY[i];
			EXODUS_Map[ex][ey] = 2;
		}
		while (1) {
			cout << "플레이어 상태창" << endl;
			cout << "체력 : " << Hero_HP << "\t" << "보유금액 : " << Money << endl;
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j) {
					if (EXODUS_Map[i][j] == 0) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
						cout << "#";
					}
					else if (EXODUS_Map[i][j] == 1) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
						cout << "O";
					}
					else if (EXODUS_Map[i][j] == 2) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						cout << "M";
					}
					else if (EXODUS_Map[i][j] == 3) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
						cout << "S";
					}
				}
				cout << endl;
			}
			keyDown = _getch();

			if (keyDown == 'W' || keyDown == 'w') {
				px -= 1;
				EXODUS_Map[px][py] = 1;
				EXODUS_Map[px + 1][py] = 0;
			}
			if (keyDown == 'A' || keyDown == 'a') {
				py -= 1;
				EXODUS_Map[px][py] = 1;
				EXODUS_Map[px][py + 1] = 0;
			}
			if (keyDown == 'S' || keyDown == 's') {
				px += 1;
				EXODUS_Map[px][py] = 1;
				EXODUS_Map[px - 1][py] = 0;
			}
			if (keyDown == 'D' || keyDown == 'd') {
				py += 1;
				EXODUS_Map[px][py] = 1;
				EXODUS_Map[px][py - 1] = 0;
			}
			if (px == ex && py == ey) {
				EXODUS_Map[ex][ey] = 1;
			}

			system("cls");

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			int random_Gold = 0;
			for (int i = 0; i < 5; ++i) {
				if (MonsterPosX[i] == px && MonsterPosY[i] == py && Hero_HP > 0) {
					Monster_Hp = 10;
					while (1) {
						cout << "1.가위 2.바위 3.보 중에 하나를 선택하세요" << endl;
						Monster_Attack = (rand() % 3) + 1;
						cin >> Hero_Attack;
						if (Hero_Attack == Monster_Attack) {
							while (1) {
								cout << "재대결" << endl;
								cout << "1.가위 2.바위 3.보 중에 하나를 선택하세요" << endl;
								Monster_Attack = (rand() % 3) + 1;
								cin >> Hero_Attack;
								if (Monster_Attack != Hero_Attack)
									break;
							}
						}
						if (Hero_Attack != Monster_Attack) {
							if ((Hero_Attack == 1 && Monster_Attack == 2) ||
								(Hero_Attack == 2 && Monster_Attack == 3) ||
								(Hero_Attack == 3 && Monster_Attack == 1)) {
								cout << "몬스터 승리 플레이어 체력 -5감소!!" << endl;
								Hero_HP -= 5;
								cout << "플레이어의 현재 체력 " << Hero_HP << endl;
								cout << "몬스터의 현재 체력" << Monster_Hp << endl;
							}
							else if ((Hero_Attack == 1 && Monster_Attack == 3) ||
								(Hero_Attack == 2 && Monster_Attack == 1) ||
								(Hero_Attack == 3 && Monster_Attack == 2)) {
								cout << "플레이어 승리!! " << "몬스터 체력 -5감소" << endl;
								Monster_Hp -= 5;
								cout << "플레이어의 현재 체력 " << Hero_HP << endl;
								cout << "몬스터의 현재 체력" << Monster_Hp << endl;
							}
						}
						if (Hero_HP <= 40 && Monster_Hp > 0) {
							cout << "1.계속 하기 2. 도망가기" << endl;
							int select_Num;
							cin >> select_Num;
							if (select_Num == 1) {
								continue;
							}
							if (select_Num == 2) {
								if (EXODUS_Map[px - 1][py] == 0) {
									EXODUS_Map[px][py] = 2;
									EXODUS_Map[px - 1][py] = 1;
									px -= 1;
								}
								else if (EXODUS_Map[px + 1][py] == 0) {
									EXODUS_Map[px][py] = 2;
									EXODUS_Map[px + 1][py] = 1;
									px += 1;
								}
								else if (EXODUS_Map[px][py - 1] == 0) {
									EXODUS_Map[px][py] = 2;
									EXODUS_Map[px][py - 1] = 1;
									py -= 1;
								}
								else if (EXODUS_Map[px][py + 1] == 0) {
									EXODUS_Map[px][py] = 2;
									EXODUS_Map[px][py + 1] = 1;
									py += 1;
								}
								else if (EXODUS_Map[px - 1][py - 1] == 0) {
									EXODUS_Map[px][py] = 2;
									EXODUS_Map[px - 1][py - 1] = 1;
									px -= 1; py -= 1;
								}
								else if (EXODUS_Map[px + 1][py + 1] == 0) {
									EXODUS_Map[px][py] = 2;
									EXODUS_Map[px + 1][py + 1] = 1;
									px += 1; py += 1;
								}
								else if (EXODUS_Map[px - 1][py + 1] == 0) {
									EXODUS_Map[px][py] = 2;
									EXODUS_Map[px - 1][py + 1] = 1;
									px -= 1; py += 1;
								}
								else if (EXODUS_Map[px + 1][py - 1] == 0) {
									EXODUS_Map[px][py] = 2;
									EXODUS_Map[px + 1][py - 1] = 1;
									px += 1; py -= 1;
								}
								break;
							}
						}
						if (Monster_Hp <= 0) {
							MonsterPosX[i] = 0, MonsterPosY[i] = 0;
							random_Gold = rand() % 100;
							cout << random_Gold << "GOLD 획득" << endl;
							Money += random_Gold;
							cout << "현재 보유 금화 " << Money << endl;
							++Monster_Cnt;
							cout << "몬스터 사냥한 횟수 " << Monster_Cnt << endl;
							while (1) {
								cout << "1. 사냥 계속 하기 2. 상점가기" << endl;
								int Select_Number;
								cin >> Select_Number;
								if (Select_Number == 1) { break; }
								else if (Select_Number == 2) {
									if (Money < 50) {
										cout << "돈없어서 입장불가" << endl;
										continue;
									}
									cout << "강제 포션구입 및 사용" << endl;
									Money -= 50;
									Hero_HP = 50;
									cout << "현재 체력 " << Hero_HP << "현재 소유한 돈 " << endl << Money << "GOLD" << endl;
								}
								else
								{
									cout << "잘못된 값 입력 재선택" << endl;
									continue;
								}
							}
							break;
						}
					}
				}
				if (Hero_HP <= 0) {
					cout << "GAME OVER" << endl << "\t ㅠ . ㅠ" << endl;
					break;
				}
			}
			if (px == 0 && py == 5) {
				if (Money >= 50) {
					cout << "강제포션구입 HP회속 및 50골드 감소" << endl;
					Sleep(1000);
					Money -= 50;
					Hero_HP = 50;
					if (EXODUS_Map[px - 1][py] == 0) {
						EXODUS_Map[px][py] = 3;
						EXODUS_Map[px - 1][py] = 1;
						px -= 1;
					}
					else if (EXODUS_Map[px + 1][py] == 0) {
						EXODUS_Map[px][py] = 3;
						EXODUS_Map[px + 1][py] = 1;
						px += 1;
					}
					else if (EXODUS_Map[px][py - 1] == 0) {
						EXODUS_Map[px][py] = 3;
						EXODUS_Map[px][py - 1] = 1;
						py -= 1;
					}
					else if (EXODUS_Map[px][py + 1] == 0) {
						EXODUS_Map[px][py] = 3;
						EXODUS_Map[px][py + 1] = 1;
						py += 1;
					}
					else if (EXODUS_Map[px - 1][py - 1] == 0) {
						EXODUS_Map[px][py] = 3;
						EXODUS_Map[px - 1][py - 1] = 1;
						px -= 1; py -= 1;
					}
					else if (EXODUS_Map[px + 1][py + 1] == 0) {
						EXODUS_Map[px][py] = 3;
						EXODUS_Map[px + 1][py + 1] = 1;
						px += 1; py += 1;
					}
					else if (EXODUS_Map[px - 1][py + 1] == 0) {
						EXODUS_Map[px][py] = 3;
						EXODUS_Map[px - 1][py + 1] = 1;
						px -= 1; py += 1;
					}
					else if (EXODUS_Map[px + 1][py - 1] == 0) {
						EXODUS_Map[px][py] = 3;
						EXODUS_Map[px + 1][py - 1] = 1;
						px += 1; py -= 1;
					}
				}
				else {
					cout << "거지 출입불가" << endl;
					if (EXODUS_Map[px - 1][py] == 0) {
						EXODUS_Map[px][py] = 3;
						EXODUS_Map[px - 1][py] = 1;
						px -= 1;
					}
					else if (EXODUS_Map[px + 1][py] == 0) {
						EXODUS_Map[px][py] = 3;
						EXODUS_Map[px + 1][py] = 1;
						px += 1;
					}
					else if (EXODUS_Map[px][py - 1] == 0) {
						EXODUS_Map[px][py] = 3;
						EXODUS_Map[px][py - 1] = 1;
						py -= 1;
					}
					else if (EXODUS_Map[px][py + 1] == 0) {
						EXODUS_Map[px][py] = 3;
						EXODUS_Map[px][py + 1] = 1;
						py += 1;
					}
					else if (EXODUS_Map[px - 1][py - 1] == 0) {
						EXODUS_Map[px][py] = 3;
						EXODUS_Map[px - 1][py - 1] = 1;
						px -= 1; py -= 1;
					}
					else if (EXODUS_Map[px + 1][py + 1] == 0) {
						EXODUS_Map[px][py] = 3;
						EXODUS_Map[px + 1][py + 1] = 1;
						px += 1; py += 1;
					}
					else if (EXODUS_Map[px - 1][py + 1] == 0) {
						EXODUS_Map[px][py] = 3;
						EXODUS_Map[px - 1][py + 1] = 1;
						px -= 1; py += 1;
					}
					else if (EXODUS_Map[px + 1][py - 1] == 0) {
						EXODUS_Map[px][py] = 3;
						EXODUS_Map[px + 1][py - 1] = 1;
						px += 1; py -= 1;
					}
					Sleep(1000);
				}
			}
			system("cls");
			if (Hero_HP <= 0) { break; }
			if (Monster_Cnt == 5) {
				for (int i = 0; i < 10; ++i) {
					cout << "☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆" << endl;
					cout << "☆\t    Clear!!!다음단계에 도전하세요\t  ☆" << endl;
					cout << "☆\t\t       ^ . ^     \t\t  ☆" << endl;
					cout << "☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆" << endl;
					system("cls");
					cout << "★★★★★★★★★★★★★★★★★★★★★★★★★★" << endl;
					cout << "★\t    Clear!!!다음단계에 도전하세요\t  ★" << endl;
					cout << "★\t\t       ^ . ^     \t\t  ★" << endl;
					cout << "★★★★★★★★★★★★★★★★★★★★★★★★★★" << endl;
					system("cls");
				}
				break;
			}
		}
	}
	if (difficulty_Select == 2) {
		cout << "추후 업데이트 중" << endl;
	}
	if (difficulty_Select == 3) {
		cout << "추후 업데이트 중" << endl;
	}
	if (difficulty_Select == 4) {
		cout << "추후 업데이트 중" << endl;
	}
}


void MainbackGround() {

	for (int i = 0; i < 10; ++i) {
		cout << "☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆" << endl;
		cout << "☆\t\t영웅의 절차적 Game \t\t  ☆" << endl;
		cout << "☆\t\t                   \t\t  ☆" << endl;
		cout << "☆\t\t  Press Keyboard \t\t  ☆" << endl;
		cout << "☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆" << endl;
		system("cls");
		cout << "★★★★★★★★★★★★★★★★★★★★★★★★★★" << endl;
		cout << "★\t\t영웅의 절차적 Game \t\t  ★" << endl;
		cout << "★\t\t                   \t\t  ★" << endl;
		cout << "★\t\t  Press Keyboard \t\t  ★" << endl;
		cout << "★★★★★★★★★★★★★★★★★★★★★★★★★★" << endl;
		system("cls");
	}
	cout << "★★★★★★★★★★★★★★★★★★★★★★★★★★" << endl;
	cout << "★\t\t영웅의 절차적 Game \t\t  ★" << endl;
	cout << "★\t\t                   \t\t  ★" << endl;
	cout << "★\t\t  Press Keyboard \t\t  ★" << endl;
	cout << "★★★★★★★★★★★★★★★★★★★★★★★★★★" << endl;
	_getch();
	system("cls");
}