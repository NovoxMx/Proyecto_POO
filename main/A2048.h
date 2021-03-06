
#include "Rooms.h"
#include "conio.h"



int const ROW = 4;
int const COL = 4;
int game[ROW][COL] = { 0 };

//arriba abajo izquierda derecha
int const UP = 1;
int const DOWN = 2;
int const LEFT = 3;
int const RIGHT = 4;

// El estado del juego
int const GAME_OVER = 1;
int const GAME_WIN = 2;
int const GAME_CONTINUE = 3;

class A2048: public Rooms{
    public:
        void Print();
        bool CreateNumber();
        void Process(int);
        int Input();
        int Judge();
        int mainA();
		int mainB();

};

enum GameNum{


	Game_2 = 2,
	Game_4 = 4,
	Game_8 = 8,
	Game_16 = 16,
	Game_32 = 32,
	Game_64 = 64,
	Game_128 = 128,
	Game_256 = 256,
	Game_512 = 512,
	Game_1024 = 1024,
	Game_2048 = 2048,
};

// Imprime la matriz resultante
void A2048::Print()
{
	system("cls");
	cout << "******* 2048 *******" << endl << endl;
	for (int i = 0; i < ROW; ++i)
	{
		cout<< "---------------------------------" << endl;
		for(int j = 0;j < COL;++j)
		{
			if (game[i][j] == 0)
			{
				cout << "|   \t";
			}
			else   
			{
				cout << "|   " << game[i][j] << "\t";
			}
		}
		cout << "|" << endl;
	}
	cout << "---------------------------------" << endl;
}


bool A2048::CreateNumber()
{
	int x = -1;
	int y = -1;
	int times = 0;
	int maxTimes = ROW * COL;
	// La probabilidad de dos tercios genera 2 y la probabilidad de un tercio genera 4
	int whitch = rand() % 3;
	do   
	{
		x = rand() % ROW;
		y = rand() % COL;
		++times;
	} while (game[x][y] != 0 && times <= maxTimes);

	// Indica que la cuadrícula está llena
	if (times >= maxTimes)
	{
		return false;
	}
	else
	{
		GameNum num;
		if (whitch == 0)
		{
			num = Game_4;
		}
		else if(whitch)
		{
			num = Game_2;
		}
		game[x][y] = num;
	}

	return true;
}

void A2048::Process(int direction)
{
	switch (direction)
	{
	case UP:
		// La línea superior no se mueve
		for (int row = 1; row < ROW; ++row)
		{
			for (int crow = row; crow >= 1; --crow)
			{
				for (int col = 0; col < COL; ++col)
				{
					// La última cuadrícula está vacía
					if (game[crow - 1][col] == 0)
					{
						game[crow - 1][col] = game[crow][col];
						game[crow][col] = 0;
					}
					else
					{
						//unir
						if (game[crow - 1][col] == game[crow][col])
						{
							game[crow - 1][col] *= 2;
							game[crow][col] = 0;
						}

					}
				}
			}
		}
		break;
	case DOWN:
		// La línea de fondo no se mueve
		for (int row = ROW - 2; row >= 0; --row)
		{
			for (int crow = row; crow < ROW - 1; ++crow)
			{
				for (int col = 0; col < COL; ++col)
				{ 
					// La última cuadrícula está vacía
					if (game[crow + 1][col] == 0)
					{
						game[crow + 1][col] = game[crow][col];
						game[crow][col] = 0;
					}
					else
					{
						//unir
						if (game[crow + 1][col] == game[crow][col])
						{
							game[crow + 1][col] *= 2;
							game[crow][col] = 0;
						}

					}
				}
			}
		}
		break;
	case LEFT:
		// La columna de la izquierda no se mueve
		for (int col = 1; col < COL; ++col)
		{
			for (int ccol = col; ccol >= 1; --ccol)
			{
				for (int row = 0; row < ROW; ++row)
				{
					// La última cuadrícula está vacía
					if (game[row][ccol - 1] == 0)
					{
						game[row][ccol - 1] = game[row][ccol];
						game[row][ccol] = 0;
					}
					else
					{
						//unir
						if (game[row][ccol - 1] == game[row][ccol])
						{
							game[row][ccol - 1] *= 2;
							game[row][ccol] = 0;
						}

					}
				}
			}
		}
		break;
	case RIGHT:
		// La columna de la derecha no se mueve
		for (int col = COL - 2; col >= 0; --col)
		{
			for (int ccol = col; ccol <= COL - 2; ++ccol)
			{
				for (int row = 0; row < ROW; ++row)
				{
					// La última cuadrícula está vacía
					if (game[row][ccol + 1] == 0)
					{
						game[row][ccol + 1] = game[row][ccol];
						game[row][ccol] = 0;
					}
					else
					{
						//unir
						if (game[row][ccol + 1] == game[row][ccol])
						{
							game[row][ccol + 1] *= 2;
							game[row][ccol] = 0;
						}

					}
				}
			}
		}
		break;
	}

}

// Procesar entrada y salida, devolver arriba, abajo, izquierda y derecha
int A2048::Input()
{
	// Leer las cuatro teclas de flecha
	int upArrow = 0;
	int downArrow = 0;
	int leftArrow = 0;
	int rightArrow = 0;
	int direction = 0;
	while (true)
	{
		upArrow = GetAsyncKeyState(VK_UP);
		downArrow = GetAsyncKeyState(VK_DOWN);
		leftArrow = GetAsyncKeyState(VK_LEFT);
		rightArrow = GetAsyncKeyState(VK_RIGHT);

		if (upArrow)
		{
			direction = UP;
			break;
		}
		else if(downArrow)
		{
			direction = DOWN;
			break;
		}
		else if(leftArrow)
		{
			direction = LEFT;
			break;
		}
		else if(rightArrow)
		{
			direction = RIGHT;
			break;
		}

		Sleep(100);
	}

	return direction;
}

// Juzga el estado del juego
int A2048::Judge()
{
	//Gana el juego
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			if (game[i][j] == 32)
			{
				return GAME_WIN;
				break;
			}
		}
	}

	// Inspección horizontal
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL - 1; ++j)
		{
			if (!game[i][j] || (game[i][j] == game[i][j + 1]))
			{
				return GAME_CONTINUE;
				break;
			}
		}
	}
	// Inspección vertical
	for (int j = 0; j< COL; ++j)
	{
		for (int i = 0; i < ROW - 1; ++i)
		{
			if (!game[i][j] || (game[i][j] == game[i + 1][j]))
			{
				return GAME_CONTINUE;
				break;
			}
		}
	}

	// No cumple las dos condiciones anteriores, el juego ha terminado
	return GAME_OVER;

}


int A2048::mainB()
{
	    int eleccion;
    while(true){
        cout << "Que es esto?, una puerta metalica que parece de laboratorio..."<< endl;
        system ("pause");
        system("cls");
        cout << "\tQuieres entrar?" << endl;
        cout << "[1] Entrar al laboratorio" << endl;
        cout << "[2] Salir" << endl;
        cout <<  "Que quieres hacer: ";
        cin >> eleccion;
        if(eleccion == 1){
            system("cls");
            cout << "...";
            getch();
            system("cls");
            cout << "  ~ 2046, 2047 y por ultimo, 2048...";
            getch();
            cout << "\n    ~ Eh? quien eres tu?";
            getch();
            cout << "\n    ~ Espera, no, no, no puede ser verdad?";
            getch(); 
            cout << "\n    ~ Uno de los grandes heroes????";
            getch();
            cout << "\n    ~ Jaj!, que ironico, tantas tesis que hice sobre la nula existencia de heroes como tu";
            getch();
			cout << "\n    ~ Y al final resulta que si son de verdad!!";
            getch(); 
            cout << "\n    ~ Supongo que ahora te tengo que vencer, si no el Gran Rey se enojara";
            getch();
            cout << "\n    ~ Esta bien, esto sera muy rapido.";
            getch();
            system("cls");
			system("Color 04");
            cout << "PREPARATE PARA UNA BATALLA!!!!";
            getch();
			system("Color 07");
            system("cls");
            cout << "                                  ~~[ 2048 ]]~~";
            cout << "\nUn juego de digitos, tienes que juntar los numeros iguales para que estos se hagan su doble";
            cout << " \nAl llegar a 32, el juego sera tomado como terminado, utiliza las flechas para mover las casillas.";
            getch();
            system("cls");

            mainA();
            break;
        }
        else if(eleccion == 2){
            return 0;
            break;
        }
    }
}



int A2048::mainA()
{
	// Establecer una semilla de número aleatorio
	srand((unsigned int)time(0));
	CreateNumber();
	CreateNumber();
	Print();
	int direction = 0;
	int gameState = -1;
	int siono = 0;
	while (true)
	{
		direction = Input();

		gameState = Judge();
		if (direction && gameState == GAME_CONTINUE)
		{
			Process(direction);
			CreateNumber();
			Print();
			Sleep(100);
		}
		else if(gameState == GAME_WIN)
		{
			// system("cls");
            // cout << "No puede ser!";
            // getch();
            // system("cls");
            // cout << "  ~ Tenia todos los numeros a mi favor!! como perdi?";
            // getch();
            // cout << "\n  ~ Tantos estudios, tanto tiempo gastado, para que al final mi oponente sea un cerebrito";
            // getch();
			// cout << "\n  ~ Segun mis calculos este es mi fin, lo siento Gran Rey...";
            // getch();
            // system("cls");
            // cout << "Agarras una llave dorada, un poco daniada que estaba tirada y entras por un portal";
            // getch();
            // cout << "\n  ~ Parece que va al incio del laberinto";
            // getch();
            // cout << "\n ...";
            getch();
			return 1;
			break;
		}
		else if(gameState == GAME_OVER)
		{
			return 0;
			break;
		}
	}
}
