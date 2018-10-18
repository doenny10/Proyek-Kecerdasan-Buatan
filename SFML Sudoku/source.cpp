#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>
#include <string.h>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <sstream>
#define UNASSIGNED 0
#define N 9
using namespace std;

class CBackground{
private:
	sf::Texture bgTexture;
	sf::Sprite bg;
	string id;
public:
	CBackground(){
		id = "none";
		bgTexture.loadFromFile("Assets/bg_menu.jpg");
		bg.setTexture(bgTexture);
		bg.setPosition(sf::Vector2f(0,0));
	}
	void setBackground(string _id){
		id = _id;
		if (id == "menu")
			bgTexture.loadFromFile("Assets/bg_menu.jpg");
		else if (id == "game")
			bgTexture.loadFromFile("Assets/bg_game.png");
	}
	sf::Sprite getSprite(){
		return bg;
	}
};

bool UnassignedLocation(int map[N][N], int &row, int &col);

bool isSafe(int map[N][N], int row, int col, int num);

//int reg[N][N] = {
//	{ 1, 1, 2, 2, 2, 2, 2, 3, 3 },
//	{ 1, 1, 1, 2, 2, 2, 3, 3, 3 },
//	{ 8, 1, 1, 1, 2, 3, 3, 3, 4 },
//	{ 8, 8, 1, 9, 9, 9, 3, 4, 4 }, 
//	{ 8, 8, 8, 9, 9, 9, 4, 4, 4 },
//	{ 8, 8, 7, 9, 9, 9, 5, 4, 4 },
//	{ 8, 7, 7, 7, 6, 5, 5, 5, 4 },
//	{ 7, 7, 7, 6, 6, 6, 5, 5, 5 },
//	{ 7, 7, 6, 6, 6, 6, 6, 5, 5 }
//};

int reg[N][N] = {
	{ 1, 1, 1, 2, 2, 2, 3, 3, 3 },
	{ 1, 1, 1, 2, 2, 2, 3, 3, 3 },
	{ 1, 1, 1, 2, 2, 2, 3, 3, 3 },
	{ 8, 8, 8, 9, 9, 9, 4, 4, 4 }, 
	{ 8, 8, 8, 9, 9, 9, 4, 4, 4 },
	{ 8, 8, 8, 9, 9, 9, 4, 4, 4 },
	{ 7, 7, 7, 6, 6, 6, 5, 5, 5 },
	{ 7, 7, 7, 6, 6, 6, 5, 5, 5 },
	{ 7, 7, 7, 6, 6, 6, 5, 5, 5 }
};


class tulisan{
protected:
	sf::Font font;
	sf::Text angka[9][9];

public:
	tulisan(){
		font.loadFromFile("Fonts/Roboto-Regular.ttf");
		for(int x = 0; x<9; x++){
			for(int y = 0; y<9; y++){
				angka[x][y].setString("0");
				angka[x][y].setFont(font);
				angka[x][y].setStyle(sf::Text::Bold);
				angka[x][y].setColor(sf::Color::Black);
				angka[x][y].setCharacterSize(55);

			}
		}
	}

	void setposangka(){
		float horisontal = 50, vertical = 30;
		int co = 0;
		for(int x = 0; x<9; x++){
			for(int y = 0; y<9; y++){
				angka[x][y].setPosition(sf::Vector2f(horisontal, vertical));
				horisontal+=70;
				co++;
			}
			horisontal = 50;
			vertical +=70;
			co = 0;
		}
	}

	void setangka(int x, int y, int set){
		char *a = new char;
		itoa(set, a, 10);
		angka[x][y].setString(a);
	}

	void setangkastring(int x, int y, string set){
		angka[x][y].setString(set);
	}

	sf::Text getangka(int x, int y){
		return angka[x][y];
	}

	string getisi(int x, int y){
		return angka[x][y].getString();
	}

	int getisiint(int x, int y){
		int numb;
		istringstream ( angka[x][y].getString() ) >> numb;
		return numb;
	}

};

class sudoku{
protected:
	sf::RectangleShape kotak[9][9];
	sf::FloatRect kotakf[9][9];

public:
	sudoku(){
		for(int x = 0; x<9; x++){
			for(int y = 0; y<9; y++){
				kotak[x][y].setSize(sf::Vector2f(70,70));
				kotak[x][y].setOutlineColor(sf::Color::Black);
				kotak[x][y].setOutlineThickness(2);
			}
		}

	}

	void setposition(){
		float horisontal = 30, vertical = 30;
		int co = 0;
		for(int x = 0; x<9; x++){
			for(int y = 0; y<9; y++){
				kotak[x][y].setPosition(sf::Vector2f(horisontal, vertical));
				horisontal+=70;
				co++;
			}
			horisontal = 30;
			vertical +=70;
			co = 0;
		}

	}

	sf::RectangleShape getkotak(int x, int y){
		return kotak[x][y];
	}

	void setrectangle(){
		for(int x = 0; x<9; x++){
			for(int y = 0; y<9; y++){
				kotakf[x][y] = kotak[x][y].getGlobalBounds();
			}

		}
	}

	int* getindexkotak(sf::Vector2f(localPosition)){
		for(int x = 0; x<9; x++){
			for(int y = 0; y<9; y++){
				if(kotakf[x][y].contains(sf::Vector2f(localPosition))){
					if(kotak[x][y].getFillColor() == sf::Color::White)
						kotak[x][y].setFillColor(sf::Color(194, 243, 250));
					int a[2];
					a[0] = x;
					a[1] = y;
					return a;
				}
			}
		}
	}

	void setclicked(int x, int y){
		kotak[x][y].setFillColor(sf::Color(194, 243, 250));
	}

	void setwrongregion(int x, int y){
		kotak[x][y].setFillColor(sf::Color::Blue);
	}

	int* getindexkotak1(sf::Vector2f(localPosition)){
		for(int x = 0; x<9; x++){
			for(int y = 0; y<9; y++){
				if(kotakf[x][y].contains(sf::Vector2f(localPosition))){
					if(kotak[x][y].getFillColor() == sf::Color::White)
						kotak[x][y].setFillColor(sf::Color(194, 243, 250));
					int a[2];
					a[0] = x;
					a[1] = y;
					return a;
				}
			}
		}
	}

	sf::Color getwarna(int x, int y){
		return kotak[x][y].getFillColor();
	}

	void clearcolor(int x, int y){
		kotak[x][y].setFillColor(sf::Color::White);
	}

	void clearall(){
		for(int x = 0; x<9; x++){
			for(int y = 0; y<9; y++){
				kotak[x][y].setFillColor(sf::Color::White);
			}
		}
	}

	void clearcol1(int col){
		for(int x = 0; x<9; x++){
			kotak[x][col].setFillColor(sf::Color::White);
		}
	}

	void clearrow1(int row){
		for(int y = 0; y<9; y++){
			kotak[row][y].setFillColor(sf::Color::White);
		}
	}
	void setwrongcol1(int col){
		for(int x = 0; x<9; x++){
			kotak[x][col].setFillColor(sf::Color::Yellow);
		}
	}

	void setwrongrow1(int row){
		for(int y = 0; y<9; y++){
			kotak[row][y].setFillColor(sf::Color::Magenta);
		}
	}

	void clearreg1(int z){
		for (int x=0; x < 9; x++){
			for(int y = 0; y<9; y++){
				if(reg[x][y] == z)
					kotak[x][y].setFillColor(sf::Color::White);
			}
		}
	}
	void setwrongreg1(int z){
		for (int x=0; x < 9; x++){
			for(int y = 0; y<9; y++){
				if(reg[x][y] == z){
					kotak[x][y].setFillColor(sf::Color::Green);
				}
			}
		}
	}

};

class garis{
protected:
	sf::RectangleShape lines[40];
public:
	garis(){
		for(int x = 0; x<40; x++){
			lines[x].setFillColor(sf::Color::Blue);
			lines[x].setSize(sf::Vector2f(70, 5)); //panjang, ketebalan
		}

		//-------------vertical-------------------
		lines[0].setPosition(sf::Vector2f(170,30));
		lines[0].setRotation(90);

		lines[1].setPosition(sf::Vector2f(520,30));
		lines[1].setRotation(90);

		lines[2].setPosition(sf::Vector2f(240,100));
		lines[2].setRotation(90);

		lines[3].setPosition(sf::Vector2f(450,100));
		lines[3].setRotation(90);

		lines[4].setPosition(sf::Vector2f(310,170));
		lines[4].setRotation(90);

		lines[5].setPosition(sf::Vector2f(380,170));
		lines[5].setRotation(90);

		lines[6].setPosition(sf::Vector2f(100,170));
		lines[6].setRotation(90);

		lines[7].setPosition(sf::Vector2f(590,170));
		lines[7].setRotation(90);

		lines[8].setPosition(sf::Vector2f(170,240));
		lines[8].setRotation(90);

		lines[9].setPosition(sf::Vector2f(520,240));
		lines[9].setRotation(90);

		lines[10].setPosition(sf::Vector2f(170,380));
		lines[10].setRotation(90);

		lines[11].setPosition(sf::Vector2f(520,380));
		lines[11].setRotation(90);

		lines[12].setPosition(sf::Vector2f(100,450));
		lines[12].setRotation(90);

		lines[13].setPosition(sf::Vector2f(590,450));
		lines[13].setRotation(90);

		lines[14].setPosition(sf::Vector2f(310,450));
		lines[14].setRotation(90);

		lines[15].setPosition(sf::Vector2f(380,450));
		lines[15].setRotation(90);

		lines[16].setPosition(sf::Vector2f(240,520));
		lines[16].setRotation(90);

		lines[17].setPosition(sf::Vector2f(450,520));
		lines[17].setRotation(90);

		lines[18].setPosition(sf::Vector2f(170,590));
		lines[18].setRotation(90);

		lines[19].setPosition(sf::Vector2f(520,590));
		lines[19].setRotation(90);

		//---------horizontal -----------------------
		lines[20].setPosition(sf::Vector2f(170,100));
		lines[21].setPosition(sf::Vector2f(450,100));

		lines[22].setPosition(sf::Vector2f(240,170));
		lines[23].setPosition(sf::Vector2f(380,170));

		lines[24].setPosition(sf::Vector2f(30,170));
		lines[25].setPosition(sf::Vector2f(590,170));

		lines[26].setPosition(sf::Vector2f(100,240));
		lines[27].setPosition(sf::Vector2f(520,240));

		lines[28].setPosition(sf::Vector2f(170,310));
		lines[29].setPosition(sf::Vector2f(450,310));

		lines[30].setPosition(sf::Vector2f(170,380));
		lines[31].setPosition(sf::Vector2f(450,380));

		lines[32].setPosition(sf::Vector2f(100,450));
		lines[33].setPosition(sf::Vector2f(520,450));

		lines[34].setPosition(sf::Vector2f(30,520));
		lines[35].setPosition(sf::Vector2f(590,520));

		lines[36].setPosition(sf::Vector2f(240,520));
		lines[37].setPosition(sf::Vector2f(380,520));

		lines[38].setPosition(sf::Vector2f(170,590));
		lines[39].setPosition(sf::Vector2f(450,590));
	}

	sf::RectangleShape getline(int i){
		return lines[i];
	}
};

class garistengah{
protected:
	sf::RectangleShape tengah[4];
public:
	garistengah(){
		for(int x = 0; x<4; x++){
			tengah[x].setFillColor(sf::Color::Red);
			tengah[x].setSize(sf::Vector2f(210, 5));
		}
		tengah[0].setPosition(sf::Vector2f(240,240));
		tengah[1].setPosition(sf::Vector2f(240,450));

		tengah[2].setPosition(sf::Vector2f(240,240));
		tengah[2].setRotation(90);

		tengah[3].setPosition(sf::Vector2f(450,240));
		tengah[3].setRotation(90);
	}

	sf::RectangleShape gettengah(int i){
		return tengah[i];
	}
};

void printMap(int map[N][N], tulisan& nomor, sf::RenderWindow &window){
	for (int row = 0; row < N; row++){
		for (int col = 0; col < N; col++){
			if(map[row][col] != 0){
				nomor.setangka(row, col, map[row][col]);
				window.draw(nomor.getangka(row,col));
			}
		}
	}
}

// fungsi solve
bool SolveSudoku(int map[N][N], tulisan& nomor, sf::RenderWindow &window, sf::RectangleShape &background, sudoku &kotak, garis &batas,
	garistengah &batas2){
		int row, col;
		if (!UnassignedLocation(map, row, col))
			return true;
		window.clear(sf::Color::White);
		window.draw(background);
		for(int x = 0; x<9; x++){
			for(int y = 0; y<9; y++){
				window.draw(kotak.getkotak(x,y));
				if(nomor.getisi(x,y) != "0")
					window.draw(nomor.getangka(x,y));
			}
		}

		for(int x = 0; x<40; x++){
			window.draw(batas.getline(x));
		}

		for(int x = 0; x<4; x++){
			window.draw(batas2.gettengah(x));
		}

		printMap(map, nomor, window);
		window.display();

		for (int num = 1; num <= 9; num++){
			if (isSafe(map, row, col, num)){
				map[row][col] = num;

				if (SolveSudoku(map, nomor, window, background, kotak, batas, batas2)){
					return true;
				}
				map[row][col] = UNASSIGNED;
			}
		}
		return false; 
}

//bool SolveSudokuPlay(int map[N][N]){
//	int reg=1;
//
//	while(reg != 10){
//	for(int i=0;i<9;i++){
//		for(int j=0;j<9;j++){
//			if(reg == reg[i][j])	
//		}
//	}
//	}
//}

// cari map yang blm keisi
bool UnassignedLocation(int map[N][N], int &row, int &col){
	for (row = 0; row < N; row++)
		for (col = 0; col < N; col++)
			if (map[row][col] == UNASSIGNED)
				return true;
	return false;
}

bool cekBaris(int map[N][N], int row){

	int angka=1, co=0;

	while (angka < 10){
		co=0;
		for(int y=0; y<9; y++){
			if(map[row][y] == angka){
				co++;
			}
		}
		if(co >= 2){
			int dum_row = row +1;
			cout << "Ada salah di baris: " << dum_row << endl;
			return false;
		}
		angka++;
	}
	return true;
}

bool cekKolom(int map[N][N], int col){

	int angka1=1, co1=0;

	while (angka1 < 10){
		co1=0;
		for(int x=0; x<9; x++){
			if(map[x][col] == angka1){
				co1++;
			}
		}
		if(co1 >= 2){
			int dum_col = col+1;
			cout << "Ada salah di kolom: " << dum_col << endl;
			return false;
		}
		angka1++;
	}
	return true;
}
bool cekReg(int map[N][N], int row, int col){

	int angka =1, co2=0;
	while(angka < 10){
		int regMap = reg[row][col];
		co2=0;
		for (int x=0; x < 9; x++){
			for(int y = 0; y<9; y++){
				if(reg[x][y] == regMap){
					if(map[x][y] == angka)
						co2++;
				}
			}
		}
		if(co2 >= 2){
			cout << "Ada salah di region: " << regMap << endl;
			return false;
		}
		++angka;
	}
	return true;
}

// cek safe special & random 
bool isSafe(int map[N][N], int row, int col, int num){
	int regMap = reg[row][col];

	for (int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			// cek region dulu
			if(reg[i][j] == regMap && i!=row && j!=col){
				if (cekReg(map,i,j) == false) return false;
				// cek angka di dalam region
				if(map[i][j] == num ){
					return false;
				}
			}
		}

		// cek baris
		if (cekBaris(map,i) == false) return false;

		// cek kolom
		if (cekKolom(map,i) == false) return false;

		if (map[row][i] == num && i!=col) return false;

		// cek kolom
		if (map[i][col] == num && i!=row) return false;
	}
	return true;
}

// cek safe play
bool isSafePlay(int map[N][N], int row, int col, int num, sudoku& kotak, tulisan& nomor){
	int regMap = reg[row][col];
	kotak.setclicked(row, col);

	for (int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			// cek region dulu
			if(reg[i][j] == regMap && i!=row && j!=col){				
				// cek angka di dalam region
				if(map[i][j] == num){
					//salah region
					//cout<< "Region " << regMap << " salah ! " << endl;
					//kotak.setwrongreg1(regMap);
					return false;
				}
			}
		}

		// cek baris
		if (map[row][i] == num && i!=col) return false;

		// cek kolom
		if (map[i][col] == num && i!=row) return false;
	}
	return true;
}





void getMap(int map[N][N], tulisan& nomor){

	for( int x=0; x<9; x++){
		for( int y=0; y<9; y++){
			map[x][y] = nomor.getisiint(x,y);
		}
		cout << endl;
	}
}

void main(){
	sf::Font huruf;

	if (!huruf.loadFromFile("Fonts/Roboto-Regular.ttf")){
		cout<<"error";
	}
	sf::RectangleShape menangback;
	menangback.setFillColor(sf::Color::White);
	menangback.setOutlineThickness(8);
	menangback.setOutlineColor(sf::Color::Cyan);
	menangback.setSize(sf::Vector2f(500,300));
	menangback.setPosition(sf::Vector2f(100, 150));


	sf::Text win;
	win.setCharacterSize(65);
	win.setColor(sf::Color::Red);
	win.setFont(huruf);
	win.setPosition(sf::Vector2f(105, 155));
	win.setString("      You Win !!!\nCongratulation :)");

	sf::RectangleShape buttonback;
	buttonback.setFillColor(sf::Color::Black);
	buttonback.setOutlineThickness(8);
	buttonback.setOutlineColor(sf::Color::Yellow);
	buttonback.setSize(sf::Vector2f(200,100));
	buttonback.setPosition(sf::Vector2f(250, 330));

	sf::Text backtext;
	backtext.setCharacterSize(75);
	backtext.setColor(sf::Color::Red);
	backtext.setFont(huruf);
	backtext.setPosition(sf::Vector2f(275, 335));
	backtext.setString("EXIT");

	sf::FloatRect buttonbackf;

	buttonbackf = buttonback.getGlobalBounds();

	int code_game = 0;  //1 = play game, 2 = random solve, 3 = special solve
	sf::RenderWindow window;
	sf::Event event;
	window.create(sf::VideoMode(700,800), "SUDOKU");
	CBackground bg;
	bool menang = false;
home:
	while(window.isOpen()){
		window.setMouseCursorVisible(true);
		bg.setBackground("menu");
		//menu - init
		sf::Texture btnTexture[5];
		sf::Sprite btn[5];
		btnTexture[0].loadFromFile("Assets/title.png");
		btnTexture[1].loadFromFile("Assets/bt_play.png");
		btnTexture[2].loadFromFile("Assets/bt_random.png");
		btnTexture[3].loadFromFile("Assets/bt_special.png");
		btnTexture[4].loadFromFile("Assets/bt_exit.png");
		for (int a = 1; a < 5; a++){
			btn[a].setTexture(btnTexture[a]);
			btn[a].scale(0.41, 0.335);
			btn[a].setPosition(sf::Vector2f(227, 100*(a + 2) - 25));
		}
		btn[0].setTexture(btnTexture[0]);
		btn[0].setPosition(sf::Vector2f(190, 111));
		//menu - play

		while(window.pollEvent(event)){

			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				if(btn[1].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
					code_game = 1;
					window.close();
				}
				if(btn[2].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
					code_game = 2;
					window.close();
				}
				if(btn[3].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
					code_game = 3;
					window.close();
				}
				else if (btn[4].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
					window.close();
				}
			}
		}
		window.clear();
		window.draw(bg.getSprite());
		for (int a = 0; a < 5; a++)
			window.draw(btn[a]);
		window.display();
	}


	//-----------Gamenya---------
	window.create(sf::VideoMode(700, 800), "Sudoku Solver", sf::Style::Close);
	window.setFramerateLimit(60);


	// inside the main loop, between window.clear() and window.display()
	//================================================================================
	//deklarasi map
	int map[N][N];

	//-------Bikin Kotak - kotaknya---------
	garis batas;
	garistengah batas2;
	//Backround Kotak Luar
	sf::RectangleShape background;
	background.setPosition(sf::Vector2f(30,30));
	background.setSize(sf::Vector2f(630,630));
	background.setOutlineThickness(5);
	background.setOutlineColor(sf::Color::Black);

	sf::FloatRect backgroundf;
	backgroundf = background.getGlobalBounds();

	//deklarasi kotak sudoku
	sudoku kotak;
	kotak.setposition();
	kotak.setrectangle();
	// deklarasi tulisan
	tulisan nomor;
	nomor.setposangka();

	int dumx = 0, dumy = 0;
	int hisx = 0, hisy = 0;
	int isi = 1;
	int countx = 0, county = 0;
	int *x;


	if(code_game == 1){
		while (window.isOpen()){
			sf::Texture btnBackTexture;
			sf::Sprite btnBack;
			btnBackTexture.loadFromFile("Assets/bt_back.png");
			btnBack.setTexture(btnBackTexture);
			btnBack.setScale(0.41, 0.355);
			btnBack.setPosition(450, 670);
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && backgroundf.contains(sf::Vector2f(localPosition))){
				x = kotak.getindexkotak(sf::Vector2f(localPosition));
				dumx = x[0];
				dumy = x[1];
				sf::Color history;
				sf::Color now;
				if(hisx != dumx || hisy!= dumy){
					now = kotak.getwarna(dumx, dumy);
					history = kotak.getwarna(hisx, hisy);
					cout<<"Index Kotak Baris - "<<dumx<<endl<<"Index Kotak Kolom - "<<dumy<<endl;
					if(history == sf::Color(194, 243, 250))
						kotak.clearcolor(hisx, hisy);
				}
				hisx = dumx;
				hisy = dumy;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				bool kosong = false;
				bool salah = false;
				for (int x=0; x<9 ;x++){
					for(int y=0;y<9;y++){
						int angka = nomor.getisiint(x,y); 
						if( angka == 0){
							kosong = true;
							break;
						}
						if(kotak.getwarna(x,y) == sf::Color::White || kotak.getwarna(x,y) == sf::Color(194, 243, 250)){
							salah = false;
						}
						else{
							salah = true;
							break;
						}
					}
				}
				if(kosong)
					cout << "Anda belum selesai mengerjakan !! \n";
				if(salah)
					cout << "Pekerjaan Anda Masih Salah, Cek Lagi yah :) \n";

				if(salah == false && kosong == false){
					cout<< "You Win !!! Congratulation :)\n";
					menang = true;
				}
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
				menang = true;
			}


			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)){
				nomor.setangka(dumx, dumy, 1);
				getMap(map,nomor);
				if(isSafePlay(map,dumx,dumy,1,kotak,nomor) == true){
					cout << "True\n";
				}else{
					cout << "False\n";
				}

				int regMap = reg[dumx][dumy];
				//cout << regMap << endl; 

				if (cekBaris(map,dumx) == true){
					kotak.clearrow1(dumx);
					kotak.setclicked(dumx, dumy);
				}else if (cekBaris(map,dumx) == false){
					kotak.setwrongrow1(dumx);
				}

				if (cekKolom(map,dumy) == true){
					kotak.clearcol1(dumy);
					kotak.setclicked(dumx, dumy);
				}else if(cekKolom(map,dumy) == false){
					kotak.setwrongcol1(dumy);
				}

				if (cekReg(map,dumx,dumy) == true){
					kotak.clearreg1(regMap);
					kotak.setclicked(dumx, dumy);
				}else if (cekReg(map,dumx,dumy) == false){
					kotak.setwrongreg1(regMap);
				}
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)){
				nomor.setangka(dumx, dumy, 2);
				getMap(map, nomor);
				if(isSafePlay(map,dumx,dumy,2,kotak,nomor) == true){
					cout << "True\n";
				}else{
					cout << "False\n";
				}

				int regMap = reg[dumx][dumy];
				//cout << regMap << endl; 

				if (cekBaris(map,dumx) == true){
					kotak.clearrow1(dumx);
					kotak.setclicked(dumx, dumy);
				}else if (cekBaris(map,dumx) == false){
					kotak.setwrongrow1(dumx);
				}

				if (cekKolom(map,dumy) == true){
					kotak.clearcol1(dumy);
					kotak.setclicked(dumx, dumy);
				}else if(cekKolom(map,dumy) == false){
					kotak.setwrongcol1(dumy);
				}

				if (cekReg(map,dumx,dumy) == true){
					kotak.clearreg1(regMap);
					kotak.setclicked(dumx, dumy);
				}else if (cekReg(map,dumx,dumy) == false){
					kotak.setwrongreg1(regMap);
				}

			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)){
				nomor.setangka(dumx, dumy, 3);
				getMap(map,nomor);
				if(isSafePlay(map,dumx,dumy,3,kotak,nomor) == true){
					cout << "True\n";
				}else{
					cout << "False\n";
				}

				int regMap = reg[dumx][dumy];
				//cout << regMap << endl; 

				if (cekBaris(map,dumx) == true){
					kotak.clearrow1(dumx);
					kotak.setclicked(dumx, dumy);
				}else if (cekBaris(map,dumx) == false){
					kotak.setwrongrow1(dumx);
				}

				if (cekKolom(map,dumy) == true){
					kotak.clearcol1(dumy);
					kotak.setclicked(dumx, dumy);
				}else if(cekKolom(map,dumy) == false){
					kotak.setwrongcol1(dumy);
				}

				if (cekReg(map,dumx,dumy) == true){
					kotak.clearreg1(regMap);
					kotak.setclicked(dumx, dumy);
				}else if (cekReg(map,dumx,dumy) == false){
					kotak.setwrongreg1(regMap);
				}
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)){
				nomor.setangka(dumx, dumy, 4);
				getMap(map,nomor);
				if(isSafePlay(map,dumx,dumy,4,kotak,nomor) == true){
					cout << "True\n";
				}else{
					cout << "False\n";
				}

				int regMap = reg[dumx][dumy];
				//cout << regMap << endl; 

				if (cekBaris(map,dumx) == true){
					kotak.clearrow1(dumx);
					kotak.setclicked(dumx, dumy);
				}else if (cekBaris(map,dumx) == false){
					kotak.setwrongrow1(dumx);
				}

				if (cekKolom(map,dumy) == true){
					kotak.clearcol1(dumy);
					kotak.setclicked(dumx, dumy);
				}else if(cekKolom(map,dumy) == false){
					kotak.setwrongcol1(dumy);
				}

				if (cekReg(map,dumx,dumy) == true){
					kotak.clearreg1(regMap);
					kotak.setclicked(dumx, dumy);
				}else if (cekReg(map,dumx,dumy) == false){
					kotak.setwrongreg1(regMap);
				}
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)){
				nomor.setangka(dumx, dumy, 5);
				getMap(map,nomor);
				if(isSafePlay(map,dumx,dumy,5,kotak,nomor) == true){
					cout << "True\n";
				}else{
					cout << "False\n";
				}

				int regMap = reg[dumx][dumy];
				//cout << regMap << endl; 

				if (cekBaris(map,dumx) == true){
					kotak.clearrow1(dumx);
					kotak.setclicked(dumx, dumy);
				}else if (cekBaris(map,dumx) == false){
					kotak.setwrongrow1(dumx);
				}

				if (cekKolom(map,dumy) == true){
					kotak.clearcol1(dumy);
					kotak.setclicked(dumx, dumy);
				}else if(cekKolom(map,dumy) == false){
					kotak.setwrongcol1(dumy);
				}

				if (cekReg(map,dumx,dumy) == true){
					kotak.clearreg1(regMap);
					kotak.setclicked(dumx, dumy);
				}else if (cekReg(map,dumx,dumy) == false){
					kotak.setwrongreg1(regMap);
				}
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)){
				nomor.setangka(dumx, dumy, 6);
				getMap(map,nomor);
				if(isSafePlay(map,dumx,dumy,6,kotak,nomor) == true){
					cout << "True\n";
				}else{
					cout << "False\n";
				}

				int regMap = reg[dumx][dumy];
				//cout << regMap << endl; 

				if (cekBaris(map,dumx) == true){
					kotak.clearrow1(dumx);
					kotak.setclicked(dumx, dumy);
				}else if (cekBaris(map,dumx) == false){
					kotak.setwrongrow1(dumx);
				}

				if (cekKolom(map,dumy) == true){
					kotak.clearcol1(dumy);
					kotak.setclicked(dumx, dumy);
				}else if(cekKolom(map,dumy) == false){
					kotak.setwrongcol1(dumy);
				}

				if (cekReg(map,dumx,dumy) == true){
					kotak.clearreg1(regMap);
					kotak.setclicked(dumx, dumy);
				}else if (cekReg(map,dumx,dumy) == false){
					kotak.setwrongreg1(regMap);
				}
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)){
				nomor.setangka(dumx, dumy, 7);
				getMap(map,nomor);
				if(isSafePlay(map,dumx,dumy,7,kotak,nomor) == true){
					cout << "True\n";
				}else{
					cout << "False\n";
				}
				int regMap = reg[dumx][dumy];
				//cout << regMap << endl; 

				if (cekBaris(map,dumx) == true){
					kotak.clearrow1(dumx);
					kotak.setclicked(dumx, dumy);
				}else if (cekBaris(map,dumx) == false){
					kotak.setwrongrow1(dumx);
				}

				if (cekKolom(map,dumy) == true){
					kotak.clearcol1(dumy);
					kotak.setclicked(dumx, dumy);
				}else if(cekKolom(map,dumy) == false){
					kotak.setwrongcol1(dumy);
				}

				if (cekReg(map,dumx,dumy) == true){
					kotak.clearreg1(regMap);
					kotak.setclicked(dumx, dumy);
				}else if (cekReg(map,dumx,dumy) == false){
					kotak.setwrongreg1(regMap);
				}
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)){
				nomor.setangka(dumx, dumy, 8);
				getMap(map,nomor);
				if(isSafePlay(map,dumx,dumy,8,kotak,nomor) == true){
					cout << "True\n";
				}else{
					cout << "False\n";
				}

				int regMap = reg[dumx][dumy];
				//cout << regMap << endl; 

				if (cekBaris(map,dumx) == true){
					kotak.clearrow1(dumx);
					kotak.setclicked(dumx, dumy);
				}else if (cekBaris(map,dumx) == false){
					kotak.setwrongrow1(dumx);
				}

				if (cekKolom(map,dumy) == true){
					kotak.clearcol1(dumy);
					kotak.setclicked(dumx, dumy);
				}else if(cekKolom(map,dumy) == false){
					kotak.setwrongcol1(dumy);
				}

				if (cekReg(map,dumx,dumy) == true){
					kotak.clearreg1(regMap);
					kotak.setclicked(dumx, dumy);
				}else if (cekReg(map,dumx,dumy) == false){
					kotak.setwrongreg1(regMap);
				}
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)){
				nomor.setangka(dumx,dumy,9);
				getMap(map,nomor);
				if(isSafePlay(map,dumx,dumy,9,kotak,nomor) == true){
					cout << "True\n";
				}else{
					cout << "False\n";
				}

				int regMap = reg[dumx][dumy];
				//cout << regMap << endl; 

				if (cekBaris(map,dumx) == true){
					kotak.clearrow1(dumx);
					kotak.setclicked(dumx, dumy);
				}else if (cekBaris(map,dumx) == false){
					kotak.setwrongrow1(dumx);
				}

				if (cekKolom(map,dumy) == true){
					kotak.clearcol1(dumy);
					kotak.setclicked(dumx, dumy);
				}else if(cekKolom(map,dumy) == false){
					kotak.setwrongcol1(dumy);
				}

				if (cekReg(map,dumx,dumy) == true){
					kotak.clearreg1(regMap);
					kotak.setclicked(dumx, dumy);
				}else if (cekReg(map,dumx,dumy) == false){
					kotak.setwrongreg1(regMap);
				}
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)){
				nomor.setangka(dumx, dumy, 0);
			}

			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			while (window.pollEvent(event))
			{
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed)
					window.close();
				//----Button Back-----
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					if(btnBack.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
						goto home;
						window.close();
					}
				}
			}
			window.clear(sf::Color::White);
			window.draw(background);
			window.draw(btnBack);

			for(int x = 0; x<9; x++){
				for(int y = 0; y<9; y++){
					window.draw(kotak.getkotak(x,y));
					if(nomor.getisi(x,y) != "0")
						window.draw(nomor.getangka(x,y));
				}
			}

			for(int x = 0; x<40; x++){
				window.draw(batas.getline(x));
			}

			for(int x = 0; x<4; x++){
				window.draw(batas2.gettengah(x));
			}
			if(menang){
				window.draw(menangback);
				window.draw(win);
				window.draw(buttonback);
				window.draw(backtext);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && buttonbackf.contains(sf::Vector2f(localPosition))){
					window.close();
				}
			}
			window.display();
		}
	}

	//--------------------------------RANDOM----------------------------------

	else if(code_game == 2){
		sf::Texture btnBackTexture;
		sf::Sprite btnBack;
		btnBackTexture.loadFromFile("Assets/bt_back.png");
		btnBack.setTexture(btnBackTexture);
		btnBack.setScale(0.41, 0.355);
		btnBack.setPosition(450, 670);
		sf::Vector2i localPosition = sf::Mouse::getPosition(window);
		// inside the main loop, between window.clear() and window.display()
		//================================================================================
		//deklarasi map
		int map[N][N];
		//------open file write to map-------
		ifstream file;
		file.open("random.txt");
		if(file.is_open()){
			for(int i = 0; i < 9; i++){
				for(int j = 0; j < 9 ;j++){
					file >> map[i][j];
				}
			}
		}else{
			cout << "File not found !\n";
		}


		while (window.isOpen()){
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				if (SolveSudoku(map, nomor, window, background, kotak, batas, batas2) == true){
					printMap(map, nomor, window);
					printf("Sudoku Random Solved !!!\n\n");
				}

			}

			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			while (window.pollEvent(event))
			{
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed)
					window.close();
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					if(btnBack.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
						goto home;
						window.close();
					}
				}
			}
			window.clear(sf::Color::White);
			window.draw(background);

			for(int x = 0; x<9; x++){
				for(int y = 0; y<9; y++){
					window.draw(kotak.getkotak(x,y));
					if(nomor.getisi(x,y) != "0")
						window.draw(nomor.getangka(x,y));
				}
			}


			for(int x = 0; x<40; x++){
				window.draw(batas.getline(x));
			}

			for(int x = 0; x<4; x++){
				window.draw(batas2.gettengah(x));
			}
			window.draw(btnBack);
			window.display();
		}
	}

	//-------------SPECIAL----------------
	if(code_game == 3){
		sf::Texture btnBackTexture;
		sf::Sprite btnBack;
		btnBackTexture.loadFromFile("Assets/bt_back.png");
		btnBack.setTexture(btnBackTexture);
		btnBack.setScale(0.41, 0.355);
		btnBack.setPosition(450, 670);
		sf::Vector2i localPosition = sf::Mouse::getPosition(window);
		// inside the main loop, between window.clear() and window.display()
		//================================================================================
		//deklarasi map
		int map[N][N];
		//------open file write to map-------
		ifstream file;
		file.open("special.txt");
		if(file.is_open()){
			for(int i = 0; i < 9; i++){
				for(int j = 0; j < 9 ;j++){
					file >> map[i][j];
				}
			}
		}else{
			cout << "File not found !\n";
		}

		while (window.isOpen()){
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				if (SolveSudoku(map, nomor, window, background, kotak, batas, batas2) == true){
					printMap(map, nomor, window);
					printf("Sudoku Special Solved !!!\n\n");
				}

			}

			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			while (window.pollEvent(event))
			{
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed)
					window.close();
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					if(btnBack.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
						goto home;
						window.close();
					}
				}
			}
			window.clear(sf::Color::White);
			window.draw(background);

			for(int x = 0; x<9; x++){
				for(int y = 0; y<9; y++){
					window.draw(kotak.getkotak(x,y));
					if(nomor.getisi(x,y) != "0")
						window.draw(nomor.getangka(x,y));
				}
			}


			for(int x = 0; x<40; x++){
				window.draw(batas.getline(x));
			}

			for(int x = 0; x<4; x++){
				window.draw(batas2.gettengah(x));
			}
			window.draw(btnBack);
			window.display();
		}
	}
}