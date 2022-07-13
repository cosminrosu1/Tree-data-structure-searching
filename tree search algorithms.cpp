#include<iostream>
#include<conio.h>
#include<string>

using namespace std;

string nume[20] = { "Oradea","Zerind","Arad","Timisoara","Lugoj","Mehadia","Drobeta","Craiova","Sibiu","Ramnicu Valcea","Fagaras","Pitesti","Bucuresti","Giurgiu","Urziceni","Hrisova","Eforie","Vaslui","Iasi","Neamt" };

int distante[20][20], trafic[20][20], h[20], i, j;
float timpLatime = 0, timpAdancime = 0, timpUniform = 0, timpAdancimeLim = 0, timpAdancimeIter = 0, timpGreedy = 0, timpA = 0, costLatime, costAdancime, costUniform, costAdancimeLim, costAdancimeIter, costGreedy, costA;
int lim1 = 1;

void conversieTimp(float timp) {
	if (timp != (int)timp) {
		if ((int)timp > 0)
		{
			cout << (int)timp << " h ";
		}
		float minute = timp - (int)timp;
		minute = minute * 60;
		if (minute != (int)minute)
		{
			if ((int)minute > 0)
			{
				cout << (int)minute << " min ";
			}
			float secunde = minute - (int)minute;
			secunde = secunde * 60;
			if ((int)secunde > 0)
			{
				cout << (int)secunde << " sec";
			}
		}
		else
			cout << minute << " min";
	}
	else
		cout << timp << " h";
}

void cautareLatime(int start, int stop, float& timpLatime, float& costLatime) {
	int viz[20], noduri[20], nrNod = 0, parinte[20], gasit = 0, pas = 0, solutie[20], nrSol = 0, final, sume[20];
	final = stop;
	for (i = 0; i < 20; i++)
	{
		viz[i] = 0;
	}

	for (i = 0; i < 20; i++)
	{
		sume[i] = 0;
	}

	noduri[nrNod++] = start;
	viz[start] = 1;

	while ((gasit == 0) && (nrNod > 0))
	{
		int nod = noduri[0];
		int sum = sume[noduri[0]];

		cout << "Pasul " << ++pas << ": ";
		for (i = 0; i < nrNod; i++)
		{
			cout << nume[noduri[i]] << " [" << sume[noduri[i]] << "] ";
		}
		cout << endl;
		for (i = 0; i < nrNod - 1; i++)
		{
			noduri[i] = noduri[i + 1];
		}
		nrNod--;
		if (nod == stop)
		{
			gasit = 1;
		}
		else
		{
			for (i = 0; i < 20; i++)
			{
				if ((distante[nod][i] != 0) && (viz[i] == 0))
				{
					noduri[nrNod++] = i;
					sume[i] = sum + distante[nod][i];
					viz[i] = 1;
					parinte[i] = nod;
				}
			}
		}
	}

	float viteza;
	while (final != start)
	{
		float nrMasiniPeKm = (float)trafic[final][parinte[final]] / (float)distante[final][parinte[final]];
		if (nrMasiniPeKm >= 10)
		{
			viteza = 100 * (10 / nrMasiniPeKm);
		}
		else
		{
			viteza = 100;
		}
		timpLatime = timpLatime + (float)distante[final][parinte[final]] / viteza;
		solutie[nrSol++] = final;
		final = parinte[final];
	}
	solutie[nrSol++] = start;
	cout << "Cautati drum de la " << nume[start] << " la " << nume[stop] << "." << endl;

	for (i = nrSol - 1; i >= 0; i--)
	{
		cout << nume[solutie[i]] << " ";
	}
	cout << endl;
	cout << "Costul drumului este: " << sume[stop] << " km";
	cout << endl;
	costLatime = sume[stop];
	cout << "Timpul drumului este: ";
	conversieTimp(timpLatime);
}

void cautareAdancime(int start, int stop, float& timpAdancime, float& costAdancime) {
	int viz[20], noduri[20], nrNod = 0, parinte[20], gasit = 0, pas = 0, solutie[20], nrSol = 0, final, sume[20];
	final = stop;
	for (i = 0; i < 20; i++)
	{
		viz[i] = 0;
	}

	for (i = 0; i < 20; i++)
	{
		sume[i] = 0;
	}

	noduri[nrNod++] = start;
	viz[start] = 1;

	while ((gasit == 0) && (nrNod > 0))
	{
		int nod = noduri[0];
		int sum = sume[noduri[0]];
		cout << "Pasul " << ++pas << ": ";
		for (i = 0; i < nrNod; i++)
		{
			cout << nume[noduri[i]] << " [" << sume[noduri[i]] << "] ";
		}
		cout << endl;
		for (i = 0; i < nrNod - 1; i++)
		{
			noduri[i] = noduri[i + 1];
		}
		nrNod--;
		if (nod == stop)
		{
			gasit = 1;
		}
		else
		{
			for (i = 0; i < 20; i++)
			{
				if ((distante[nod][i] != 0) && (viz[i] == 0))
				{
					for (j = nrNod - 1; j >= 0; j--)
					{
						noduri[j + 1] = noduri[j];
					}
					noduri[0] = i;
					nrNod++;
					sume[i] = sum + distante[nod][i];
					viz[i] = 1;
					parinte[i] = nod;
				}
			}
		}
	}

	float viteza;
	while (final != start)
	{
		float nrMasiniPeKm = (float)trafic[final][parinte[final]] / (float)distante[final][parinte[final]];
		if (nrMasiniPeKm >= 10)
		{
			viteza = 100 * (10 / nrMasiniPeKm);
		}
		else
		{
			viteza = 100;
		}
		timpAdancime = timpAdancime + (float)distante[final][parinte[final]] / viteza;
		solutie[nrSol++] = final;
		final = parinte[final];
	}
	solutie[nrSol++] = start;
	cout << "Cautati drum de la " << nume[start] << " la " << nume[stop] << "." << endl;

	for (i = nrSol - 1; i >= 0; i--)
	{
		cout << nume[solutie[i]] << " ";
	}
	cout << endl;
	cout << "Costul drumului este: " << sume[stop] << " km";
	cout << endl;
	costAdancime = sume[stop];
	cout << "Timpul drumului este: ";
	conversieTimp(timpAdancime);
}

void cautareUniform(int start, int stop, float& timpUniform, float& costUniform) {
	int viz[20], noduri[20], nrNod = 0, parinte[20], gasit = 0, pas = 0, solutie[20], nrSol = 0, final, sume[20];
	final = stop;
	for (i = 0; i < 20; i++)
	{
		viz[i] = 0;
	}

	for (i = 0; i < 20; i++)
	{
		sume[i] = 0;
	}

	noduri[nrNod++] = start;
	viz[start] = 1;

	while ((gasit == 0) && (nrNod > 0))
	{
		int nod = noduri[0];
		int sum = sume[noduri[0]];
		cout << "Pasul " << ++pas << ": ";
		for (i = 0; i < nrNod; i++)
		{
			cout << nume[noduri[i]] << " [" << sume[noduri[i]] << "] ";
		}
		cout << endl;
		for (i = 0; i < nrNod - 1; i++)
		{
			noduri[i] = noduri[i + 1];
		}
		nrNod--;
		if (nod == stop)
		{
			gasit = 1;
		}
		else
		{
			for (i = 0; i < 20; i++)
			{
				if ((distante[nod][i] != 0) && (viz[i] == 0) || ((distante[nod][i] != 0) && (viz[i] == 1) && (distante[nod][i] > 0) && (distante[nod][i] + sum < sume[i])))
				{
					noduri[nrNod++] = i;
					sume[i] = sum + distante[nod][i];
					viz[i] = 1;
					parinte[i] = nod;
				}
			}
			for (i = 0; i < nrNod - 1; i++)
			{
				for (j = i + 1; j < nrNod; j++)
				{
					if (sume[noduri[i]] > sume[noduri[j]])
					{
						int aux = noduri[i];
						noduri[i] = noduri[j];
						noduri[j] = aux;
					}
				}
			}
		}
	}

	float viteza;
	while (final != start)
	{
		float nrMasiniPeKm = (float)trafic[final][parinte[final]] / (float)distante[final][parinte[final]];
		if (nrMasiniPeKm >= 10)
		{
			viteza = 100 * (10 / nrMasiniPeKm);
		}
		else
		{
			viteza = 100;
		}
		timpUniform = timpUniform + (float)distante[final][parinte[final]] / viteza;
		solutie[nrSol++] = final;
		final = parinte[final];
	}
	solutie[nrSol++] = start;
	cout << "Cautati drum de la " << nume[start] << " la " << nume[stop] << "." << endl;

	for (i = nrSol - 1; i >= 0; i--)
	{
		cout << nume[solutie[i]] << " ";
	}
	cout << endl;
	cout << "Costul drumului este: " << sume[stop] << " km";
	cout << endl;
	costUniform = sume[stop];
	cout << "Timpul drumului este: ";
	conversieTimp(timpUniform);
}

void cautareAdancimeLim(int start, int stop, float& timpAdancimeLim, float& costAdancimeLim, int lim) {
	int viz[20], noduri[20], nrNod = 0, parinte[20], gasit = 0, pas = 0, solutie[20], nrSol = 0, final, sume[20];
	final = stop;
	for (i = 0; i < 20; i++)
	{
		viz[i] = 0;
	}

	for (i = 0; i < 20; i++)
	{
		sume[i] = 0;
	}

	int adancime[20];
	for (i = 0; i < 20; i++)
	{
		adancime[i] = 0;
	}

	noduri[nrNod++] = start;
	viz[start] = 1;

	int nod;
	while ((gasit == 0) && (nrNod > 0))
	{
		nod = noduri[0];
		int sum = sume[noduri[0]];
		cout << "Pasul " << ++pas << ": ";
		for (i = 0; i < nrNod; i++)
		{
			cout << nume[noduri[i]] << " [" << sume[noduri[i]] << "] ";
		}
		cout << endl;
		for (i = 0; i < nrNod - 1; i++)
		{
			noduri[i] = noduri[i + 1];
		}
		nrNod--;
		if (nod == stop)
		{
			gasit = 1;
		}
		else
		{
			for (i = 0; i < 20; i++)
			{
				if ((distante[nod][i] != 0) && (viz[i] == 0) && (adancime[nod] + 1 <= lim))
				{
					parinte[i] = nod;
					adancime[i] = adancime[parinte[i]] + 1;
					for (j = nrNod - 1; j >= 0; j--)
					{
						noduri[j + 1] = noduri[j];
					}
					noduri[0] = i;
					nrNod++;
					sume[i] = sum + distante[nod][i];
					viz[i] = 1;

				}
			}
		}
	}

	if (nod != stop)
	{
		cout << "Nu exista solutie.";
	}
	else
	{
		float viteza;
		while (final != start)
		{
			float nrMasiniPeKm = (float)trafic[final][parinte[final]] / (float)distante[final][parinte[final]];
			if (nrMasiniPeKm >= 10)
			{
				viteza = 100 * (10 / nrMasiniPeKm);
			}
			else
			{
				viteza = 100;
			}
			timpAdancimeLim = timpAdancimeLim + (float)distante[final][parinte[final]] / viteza;
			solutie[nrSol++] = final;
			final = parinte[final];
		}
		solutie[nrSol++] = start;
		cout << "Cautati drum de la " << nume[start] << " la " << nume[stop] << "." << endl;

		for (i = nrSol - 1; i >= 0; i--)
		{
			cout << nume[solutie[i]] << " ";
		}
		cout << endl;
		cout << "Costul drumului este: " << sume[stop] << " km";
		cout << endl;
		costAdancimeLim = sume[stop];
		cout << "Timpul drumului este: ";
		conversieTimp(timpAdancimeLim);
	}
}

void cautareAdancimeIter(int start, int stop, float& timpAdancimeIter, float& costAdancimeIter) {
	int viz[20], noduri[20], nrNod = 0, parinte[20], gasit = 0, pas = 0, solutie[20], nrSol = 0, final, sume[20];
	final = stop;
	for (i = 0; i < 20; i++)
	{
		viz[i] = 0;
	}

	for (i = 0; i < 20; i++)
	{
		sume[i] = 0;
	}

	int adancime[20];
	for (i = 0; i < 20; i++)
	{
		adancime[i] = 0;
	}

	noduri[nrNod++] = start;
	viz[start] = 1;

	int nod;
	while ((gasit == 0) && (nrNod > 0))
	{
		nod = noduri[0];
		int sum = sume[noduri[0]];
		cout << "Pasul " << ++pas << ": ";
		for (i = 0; i < nrNod; i++)
		{
			cout << nume[noduri[i]] << " [" << sume[noduri[i]] << "] ";
		}
		cout << endl;
		for (i = 0; i < nrNod - 1; i++)
		{
			noduri[i] = noduri[i + 1];
		}
		nrNod--;
		if (nod == stop)
		{
			gasit = 1;
		}
		else
		{
			for (i = 0; i < 20; i++)
			{
				if ((distante[nod][i] != 0) && (viz[i] == 0) && (adancime[nod] + 1 <= lim1))
				{
					parinte[i] = nod;
					adancime[i] = adancime[parinte[i]] + 1;
					for (j = nrNod - 1; j >= 0; j--)
					{
						noduri[j + 1] = noduri[j];
					}
					noduri[0] = i;
					nrNod++;
					sume[i] = sum + distante[nod][i];
					viz[i] = 1;

				}
			}
		}
	}

	if (nod != stop)
	{
		cout << "Nu exista solutie cu adancimea " << lim1 << endl;
		lim1++;
		cautareAdancimeIter(start, stop, timpAdancimeIter, costAdancimeIter);
	}
	else
	{
		float viteza;
		while (final != start)
		{
			float nrMasiniPeKm = (float)trafic[final][parinte[final]] / (float)distante[final][parinte[final]];
			if (nrMasiniPeKm >= 10)
			{
				viteza = 100 * (10 / nrMasiniPeKm);
			}
			else
			{
				viteza = 100;
			}
			timpAdancimeIter = timpAdancimeIter + (float)distante[final][parinte[final]] / viteza;
			solutie[nrSol++] = final;
			final = parinte[final];
		}
		solutie[nrSol++] = start;
		cout << "Cautati drum de la " << nume[start] << " la " << nume[stop] << "." << endl;

		for (i = nrSol - 1; i >= 0; i--)
		{
			cout << nume[solutie[i]] << " ";
		}
		cout << endl;
		cout << "Adancimea cea mai mica la care se gaseste o solutie este: " << lim1;
		cout << endl;
		cout << "Costul drumului este: " << sume[stop] << " km";
		cout << endl;
		costAdancimeIter = sume[stop];
		cout << "Timpul drumului este: ";
		conversieTimp(timpAdancimeIter);
	}
}

void cautareGreedy(int start, int stop, float& timpGreddy, float& costGreedy) {
	int viz[20], noduri[20], nrNod = 0, parinte[20], gasit = 0, pas = 0, solutie[20], nrSol = 0, final, sume[20];
	final = stop;
	for (i = 0; i < 20; i++)
	{
		viz[i] = 0;
	}

	for (i = 0; i < 20; i++)
	{
		sume[i] = 0;
	}

	noduri[nrNod++] = start;
	viz[start] = 1;

	while ((gasit == 0) && (nrNod > 0))
	{
		int nod = noduri[0];
		int sum = sume[noduri[0]];

		cout << "Pasul " << ++pas << ": ";
		for (i = 0; i < nrNod; i++)
		{
			cout << nume[noduri[i]] << " [" << sume[noduri[i]] << "] ";
		}
		cout << endl;
		for (i = 0; i < nrNod - 1; i++)
		{
			noduri[i] = noduri[i + 1];
		}
		nrNod--;
		if (nod == stop)
		{
			gasit = 1;
		}
		else
		{
			for (i = 0; i < 20; i++)
			{
				if ((distante[nod][i] != 0) && (viz[i] == 0))
				{
					noduri[nrNod++] = i;
					sume[i] = sum + distante[nod][i];
					viz[i] = 1;
					parinte[i] = nod;
				}
			}
			for (i = 0; i < nrNod - 1; i++)
			{
				for (j = i + 1; j < nrNod; j++)
				{
					if (h[noduri[i]] > h[noduri[j]])
					{
						int aux = noduri[i];
						noduri[i] = noduri[j];
						noduri[j] = aux;
					}
				}
			}
		}
	}

	float viteza;
	while (final != start)
	{
		float nrMasiniPeKm = (float)trafic[final][parinte[final]] / (float)distante[final][parinte[final]];
		if (nrMasiniPeKm >= 10)
		{
			viteza = 100 * (10 / nrMasiniPeKm);
		}
		else
		{
			viteza = 100;
		}
		timpGreedy = timpGreedy + (float)distante[final][parinte[final]] / viteza;
		solutie[nrSol++] = final;
		final = parinte[final];
	}
	solutie[nrSol++] = start;
	cout << "Cautati drum de la " << nume[start] << " la " << nume[stop] << "." << endl;

	for (i = nrSol - 1; i >= 0; i--)
	{
		cout << nume[solutie[i]] << " ";
	}
	cout << endl;
	cout << "Costul drumului este: " << sume[stop] << " km";
	cout << endl;
	costGreedy = sume[stop];
	cout << "Timpul drumului este: ";
	conversieTimp(timpGreedy);
}

void cautareA(int start, int stop, float& timpA, float& costA) {
	int viz[20], noduri[20], nrNod = 0, parinte[20], gasit = 0, pas = 0, solutie[20], nrSol = 0, final, sume[20];
	final = stop;
	for (i = 0; i < 20; i++)
	{
		viz[i] = 0;
	}

	for (i = 0; i < 20; i++)
	{
		sume[i] = 0;
	}

	noduri[nrNod++] = start;
	viz[start] = 1;

	while ((gasit == 0) && (nrNod > 0))
	{
		int nod = noduri[0];
		int sum = sume[noduri[0]];

		cout << "Pasul " << ++pas << ": ";
		for (i = 0; i < nrNod; i++)
		{
			cout << nume[noduri[i]] << " [" << sume[noduri[i]] << "] ";
		}
		cout << endl;
		for (i = 0; i < nrNod - 1; i++)
		{
			noduri[i] = noduri[i + 1];
		}
		nrNod--;
		if (nod == stop)
		{
			gasit = 1;
		}
		else
		{
			for (i = 0; i < 20; i++)
			{
				if ((distante[nod][i] != 0) && (viz[i] == 0))
				{
					noduri[nrNod++] = i;
					sume[i] = sum + distante[nod][i];
					viz[i] = 1;
					parinte[i] = nod;
				}
			}
			for (i = 0; i < nrNod - 1; i++)
			{
				for (j = i + 1; j < nrNod; j++)
				{
					if (distante[noduri[i]] + h[noduri[i]] > distante[noduri[j]] + h[noduri[j]])
					{
						int aux = noduri[i];
						noduri[i] = noduri[j];
						noduri[j] = aux;
					}
				}
			}
		}
	}

	float viteza;
	while (final != start)
	{
		float nrMasiniPeKm = (float)trafic[final][parinte[final]] / (float)distante[final][parinte[final]];
		if (nrMasiniPeKm >= 10)
		{
			viteza = 100 * (10 / nrMasiniPeKm);
		}
		else
		{
			viteza = 100;
		}
		timpA = timpA + (float)distante[final][parinte[final]] / viteza;
		solutie[nrSol++] = final;
		final = parinte[final];
	}
	solutie[nrSol++] = start;
	cout << "Cautati drum de la " << nume[start] << " la " << nume[stop] << "." << endl;

	for (i = nrSol - 1; i >= 0; i--)
	{
		cout << nume[solutie[i]] << " ";
	}
	cout << endl;
	cout << "Costul drumului este: " << sume[stop] << " km";
	cout << endl;
	costA = sume[stop];
	cout << "Timpul drumului este: ";
	conversieTimp(timpA);

}

int main() {

	int start = 3, stop = 12, lim = 5;

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			distante[i][j] = 0;
			trafic[i][j] = 0;
		}
	}

	distante[0][1] = 71;
	distante[0][8] = 151;
	distante[1][2] = 75;
	distante[2][3] = 118;
	distante[2][8] = 140;
	distante[3][4] = 111;
	distante[4][5] = 70;
	distante[5][6] = 75;
	distante[6][7] = 120;
	distante[7][9] = 146;
	distante[7][11] = 138;
	distante[8][9] = 80;
	distante[8][10] = 99;
	distante[9][11] = 97;
	distante[10][12] = 211;
	distante[11][12] = 101;
	distante[12][13] = 90;
	distante[12][14] = 85;
	distante[14][15] = 98;
	distante[14][17] = 142;
	distante[15][16] = 86;
	distante[17][18] = 92;
	distante[18][19] = 87;

	trafic[0][1] = 700;
	trafic[0][8] = 2500;
	trafic[1][2] = 800;
	trafic[2][3] = 1100;
	trafic[2][8] = 1200;
	trafic[3][4] = 1000;
	trafic[4][5] = 400;
	trafic[5][6] = 600;
	trafic[6][7] = 900;
	trafic[7][9] = 1300;
	trafic[7][11] = 1600;
	trafic[8][9] = 800;
	trafic[8][10] = 900;
	trafic[9][11] = 1300;
	trafic[10][12] = 1200;
	trafic[11][12] = 1000;
	trafic[12][13] = 400;
	trafic[12][14] = 700;
	trafic[14][15] = 900;
	trafic[14][17] = 1400;
	trafic[15][16] = 300;
	trafic[17][18] = 1200;
	trafic[18][19] = 700;

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			if (distante[i][j] != 0)
			{
				distante[j][i] = distante[i][j];
				trafic[i][j] = trafic[j][i];
			}
		}
	}

	h[0] = 380;
	h[1] = 374;
	h[2] = 366;
	h[3] = 329;
	h[4] = 244;
	h[5] = 241;
	h[6] = 242;
	h[7] = 160;
	h[8] = 253;
	h[9] = 192;
	h[10] = 176;
	h[11] = 10;
	h[12] = 0;
	h[13] = 77;
	h[14] = 80;
	h[15] = 151;
	h[16] = 161;
	h[17] = 199;
	h[18] = 226;
	h[19] = 234;

	cout << "Cautare in latime:" << endl;
	cout << "----------------------------------------------" << endl;
	cautareLatime(start, stop, timpLatime, costLatime);
	cout << endl;
	cout << "----------------------------------------------" << endl;
	cout << "Cautare in adancime" << endl;
	cout << "----------------------------------------------" << endl;
	cautareAdancime(start, stop, timpAdancime, costAdancime);
	cout << endl;
	cout << "----------------------------------------------" << endl;
	cout << "Cautare cu cost uniform" << endl;
	cout << "----------------------------------------------" << endl;
	cautareUniform(start, stop, timpUniform, costUniform);
	cout << endl;
	cout << "----------------------------------------------" << endl;
	cout << "Cautare in adancime cu limita" << endl;
	cout << "----------------------------------------------" << endl;
	cautareAdancimeLim(start, stop, timpAdancimeLim, costAdancimeLim, lim);
	cout << endl;
	cout << "----------------------------------------------" << endl;
	cout << "Cautare in adancime iterativa" << endl;
	cout << "----------------------------------------------" << endl;
	cautareAdancimeIter(start, stop, timpAdancimeIter, costAdancimeIter);
	cout << endl;
	cout << "----------------------------------------------" << endl;
	cout << "Cautare greedy" << endl;
	cout << "----------------------------------------------" << endl;
	cautareGreedy(start, stop, timpGreedy, costGreedy);
	cout << endl;
	cout << "----------------------------------------------" << endl;
	cout << "Cautare A*" << endl;
	cout << "----------------------------------------------" << endl;
	cautareA(start, stop, timpA, costA);
	cout << endl;
	cout << "----------------------------------------------" << endl;
	cout << "Rezultate" << endl;
	cout << "----------------------------------------------" << endl;
	cout << "Cautare in latime: Drum de " << costLatime << " km parcurs in ";
	conversieTimp(timpLatime);
	cout << endl;
	cout << "Cautare in adancime: Drum de " << costAdancime << " km parcurs in ";
	conversieTimp(timpAdancime);
	cout << endl;
	cout << "Cautare cu cost uniform: Drum de " << costUniform << " km parcurs in ";
	conversieTimp(timpUniform);
	cout << endl;
	if (timpAdancimeLim == 0)
	{
		cout << "Cautare in adancime cu limita " << lim << ": Nu exista solutie";
	}
	else
	{
		cout << "Cautare in adancime cu limita " << lim << ": Drum de " << costAdancimeLim << " km parcurs in ";
		conversieTimp(timpAdancimeLim);
	}
	cout << endl;
	cout << "Cautare cu adancime iterativa: Drum de " << costAdancimeIter << " km cu o adancime de " << lim1 << " parcurs in ";
	conversieTimp(timpAdancimeIter);
	cout << endl;
	cout << "Cautare greedy: Drum de " << costGreedy << " km parcurs in ";
	conversieTimp(timpGreedy);
	cout << endl;
	cout << "Cautare A*: Drum de " << costA << " km parcurs in ";
	conversieTimp(timpA);

	_getch();
	return 0;
}