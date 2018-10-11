#include<iostream>
#include<time.h>
#include<ctime>

using namespace std;

int const NumOfCoins = 5;
int Dist[NumOfCoins], Time[NumOfCoins], FreeCoins[NumOfCoins];
int CurrentTime, CurrentPos, MinTime = -1;

void Jump(int CoinPos);
int My_Start();


int main() {

	srand(time(0));

	for (int i = 0; i < NumOfCoins; i++) {	//randomise
		Dist[i] = rand() % 100 + 1;
		Time[i] = rand() % 150 + 1;
		FreeCoins[i] = 1;
	}

	My_Start();													//just comment this to have random coins

	cout << NumOfCoins << "\n";
	for (int i = 0; i < NumOfCoins; i++)
		cout << Dist[i] << "  " << Time[i] << "\n";

	for (int StartCoin = 0; StartCoin < NumOfCoins; StartCoin++) {	//diffrent start positions
		CurrentPos = StartCoin;
		CurrentTime = 0;
		FreeCoins[StartCoin] = -1;
		if (StartCoin != 0) Jump(StartCoin - 1);
		if (StartCoin != NumOfCoins - 1) Jump(StartCoin + 1);
		FreeCoins[StartCoin] = 1;
	}
	
	cout << MinTime;

	cout << "\n";
	system("pause");
	return 0;
}




void Jump(int CoinPos) {
	
	for (int i = 0; i < NumOfCoins; i++)						//checking
		if (FreeCoins[i] != -1 && Time[i] - fabs(Dist[CurrentPos] - Dist[CoinPos]) < 0)
			return;
	for (int i = 0; i < NumOfCoins; i++)						//decreasing time
		if (FreeCoins[i] != -1)
			Time[i] -= fabs(Dist[CoinPos] - Dist[CurrentPos]);
	
	int PrevPos;
	
	CurrentTime += fabs(Dist[CoinPos] - Dist[CurrentPos]);					//if all okey, we can stay in this position
	PrevPos = CurrentPos;
	CurrentPos = CoinPos;
	FreeCoins[CoinPos] = -1;
	
	int sum = 0;												//if its the last coin, checking for time
	for (int i = 0; i < NumOfCoins; i++)
		sum += FreeCoins[i];
	if (sum == -NumOfCoins)
		if (MinTime == -1 || MinTime > CurrentTime)
			MinTime = CurrentTime;

	for (int NextCoin = 1; NextCoin <= CurrentPos; NextCoin++)	//jumping on the nearest coin on the left, if possible
		if (FreeCoins[CurrentPos - NextCoin] != -1) {
			Jump(CurrentPos - NextCoin);
			break;
		}
	for (int NextCoin = 1; NextCoin < NumOfCoins - CurrentPos; NextCoin++)	//jumping on the nearest coin on the right, if possible
		if (FreeCoins[CurrentPos + NextCoin] != -1) {
			Jump(CurrentPos + NextCoin);
			break;
		}

	CurrentPos = PrevPos;										//preparing to go back
	FreeCoins[CoinPos] = 1;
	CurrentTime -= fabs(Dist[CoinPos] - Dist[CurrentPos]);
	return;
}




int My_Start() {												//Dist and Time for your example
	Dist[0] = 1;
	Time[0] = 3;
	Dist[1] = 3;
	Time[1] = 1;
	Dist[2] = 5;
	Time[2] = 8;
	Dist[3] = 8;
	Time[3] = 19;
	Dist[4] = 10;
	Time[4] = 15;
	return 0;
}