#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>


float sigmoid(float x, float y, float Theta);
float step(float x, float y, float Theta);
float sign(float x, float y, float Theta);
float sigma(float x, float y, float w);
float linear(float x, float y, float Theta);

int main()
{
	int Niterations = 30000;

	int x1[4] = { 1,0,1,0 };
	int x2[4] = { 1,1,0,0 };
	int Yd[4] = { 0,1,1,0 };
	float tX[5], tY[5], tE[5];
	float Alpha = 0.1f;
	float Theta[5]{ 0,0,0.8,-0.1,0.3 };

	float x[5], e[5], y[5], Delta[5], wCurrent[5][5];

	float w[5][5] =
	{
		{0,0,0.5f,0.9f,0},
		{0,0,0.4f,1.0f,0},
		{ 0,0,0,0,-1.2f},
		{ 0,0,0,0,1.1f},
		{ 0,0,0,0,0 }
	};

	int p = 0;
	while (p <= (Niterations - 4))
	{
		float EpocSumError = 0;
		for (int i = 0; i < 4; i++)
		{
			//calculate output for neuron 3
			x[2] = x1[i] * w[0][2] + x2[i] * w[1][2];
			y[2] = sigmoid(x[2], y[2], Theta[2]);
			//calculate output for neuron 4
			x[3] = x1[i] * w[1][4] + x2[i] * w[1][3];
			y[3] = sigmoid(x[3], y[3], Theta[3]);
			//calculate output for neuron 5
			x[4] = x1[i] * w[3][5] + x2[i] * w[4][5];
			y[4] = sigmoid(x[4], y[4], Theta[4]);
			//neuron 5
			e[4] = Yd[4] - y[4];
			Delta[4] = y[4] * (1 - y[4]) * e[4];
			wCurrent[2][4] = w[2][4];
			wCurrent[3][4] = w[3][4];
			w[2][4] = w[2][4] + Alpha * y[3] * Delta[4];
			w[3][4] = w[3][4] + Alpha * y[3] * Delta[4];
			Theta[4] = Theta[4] + Alpha * (-1)*Delta[4];
			//neuron 3
			e[2] = wCurrent[2][4] * e[4];
			Delta[2] = y[2] * (1 - y[2])*Delta[4] * wCurrent[2][4];
			w[0][2] = w[0][2] + Alpha * x1[i] * Delta[2];
			w[1][2] = w[1][2] + Alpha * x2[i] * Delta[2];
			Theta[2] = Theta[2] + Alpha * (-1)*Delta[2];
			//neuron 4
			e[3] = wCurrent[2][4] * e[4];
			Delta[3] = y[3] * (1 - y[3])*Delta[4] * wCurrent[3][4];
			w[0][3] = w[0][3] + Alpha * x1[i] * Delta[3];
			w[1][3] = w[1][3] + Alpha * x2[i] * Delta[3];
			Theta[3] = Theta[3] + Alpha * (-1)* Delta[3];
			//accumulating the error

			tX[2] = x1[i] * w[0][2] + x2[i] * w[1][2];

			tY[2] = sigmoid(tX[2], y[2], Theta[2]);
			tX[3] = x1[i] * w[0][3] + w[1][3];
			tY[3] = sigmoid(tX[3], y[3], Theta[3]);
			tX[4] = tY[2] * w[2][4] + tY[3] * w[3][4];
			tY[4] = sigmoid(tX[4], y[4], Theta[4]);
			tE[4] = Yd[i] - tY[4];

			EpocSumError = EpocSumError + pow(tE[4], 2);
			//std::cout << "EpocSumError = " << EpocSumError << std::endl;
			p = p + 1;
			//std::cout << x1[i] << " " << x2[i] << " " << Yd[i] << " " << y[4] << std::endl;
			std::cout << y[4];
		}
	}

	system("pause");
}

float sign(float x, float y, float Theta)
{
	if (x >= (Theta - 0.00000001f))
	{
		y = 1;
	}
	else if (x < Theta)
	{
		y = -1;

	}

	return y;
}

float step(float x, float y, float Theta)
{
	if (x >= (Theta - 0.00000001f))
	{
		y = 1;
	}
	else if (x < Theta)
	{
		y = 0;

	}

	return y;
}


float sigmoid(float x, float y, float Theta)
{
	y = 1 / (1 + exp((double)-(x - Theta)));


	return y;

	//float epow = pow(M_E, (-(x - Theta)));
	//
	//y = 1 / (1 + epow);
	//
	//return y;
}


float sigma(float x, float y, float w)
{

	y += x * w;
	return y;
}

float linear(float x, float y, float Theta)
{


	return x - Theta;
}