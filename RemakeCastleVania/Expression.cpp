#include "Expression.h"



vector<float> CExpression::giaiPT2(float a, float b, float c)
{
	vector<float> n;
	n.clear();
	float x1, x2;
	float delta = b * b - 4 * a*c;
	if (a == 0) {
		if (b == 0)
			return n;
		else
			n.push_back(-c / b);
	}
	else {
		if (delta < 0) {
			return n;
		}
		else if (delta == 0) {
			x1 = x2 = -b / (2 * a);
			n.push_back(x1);
			n.push_back(x2);
		}
		else {
			delta = sqrt(delta);
			x1 = (-b + delta) / (2 * a);
			x2 = (-b - delta) / (2 * a);
			n.push_back(x1);
			n.push_back(x2);
		}
	}
	return n;
}

vector<float> CExpression::giaiPT3(float a, float b, float c, float d)
{
	vector<float> n;
	DebugOut(L"%f %f %f %f\n",a,b,c,d);
	n.clear();
	if (a == 0) {
		return giaiPT2(b, c, d);
	}
	float dt = pow(b, 2) - 3 * a*c;
	if (dt == 0) {
		float x = (-b + pow((pow(b, 3) - 27 * pow(a, 2)*d), 1.0 / 3)) / (3 * a);
		n.push_back(x);
		DebugOut(L"vào 1 \n");
		return n;
	}
	else {
		float k = (9 * a*b*c - 2 * pow(b, 3) - 27 * pow(a, 2)*d) / (sqrt(pow(abs(dt), 3)));
		if (dt < 0) {
			float x = (sqrt(abs(dt)) / (3 * a))*(safe_pow(k + sqrt(pow(k, 2) + 1), 1.0 / 3) + safe_pow(k - sqrt(pow(k, 2) + 1), 1.0 / 3)) - b / (3 * a);
			n.push_back(x);
			DebugOut(L"vào 2 \n");
			return n;
		}
		else {
			if (dt == 0) {
				DebugOut(L"vào 3 \n");
			}
			else {
				if (abs(k) <= 1) {
					float x1 = (2 * sqrt(dt)*cos(acos(k) / 3) - b) / (3 * a);
					float x2 = (2 * sqrt(dt)*cos(acos(k) / 3 - 2 * M_PI / 3) - b) / (3 * a);
					float x3 = (2 * sqrt(dt)*cos(acos(k) / 3 + 2 * M_PI / 3) - b) / (3 * a);
					n.push_back(x1);
					n.push_back(x2);
					n.push_back(x3);
					DebugOut(L"vào 4 \n");
					return n;
				}
				else {
					float x = (sqrt(dt)*abs(k) / (3 * a*k))*(safe_pow(abs(k) + sqrt(pow(k, 2) - 1), 1.0 / 3) + safe_pow(abs(k) - sqrt(pow(k, 2) - 1), 1.0 / 3)) - b / (3 * a);
					n.push_back(x);
					DebugOut(L"vào 5 \n");
					return n;
				}
			}
		}
	}
}

CExpression::CExpression()
{

}


CExpression::~CExpression()
{
}
