#pragma once
#include"GameObject.h"
#include<math.h>
#include<algorithm>
#include"Utils.h"

# define M_PI           3.14159265358979323846  /* pi */

class CExpression
{
public:
	static vector<float> giaiPT2(float a, float b, float c);
	vector<float> giaiPT3(float a, float b, float c, float d);

	template <typename T> int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}

	template <class T, class U> auto safe_pow(T val, U p) -> decltype(pow(val, p)) {
		return pow(abs(val), p) * sgn(val);
	}

	CExpression();
	~CExpression();
};

