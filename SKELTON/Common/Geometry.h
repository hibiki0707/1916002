#pragma once

// �x�N�g���\����
struct Vector2{
	float x, y;
	Vector2() :x(0.0f), y(0.0f) {}
	Vector2(float inx, float iny) :x(inx), y(iny) {};
	void operator+=(const Vector2& vec);
	void operator-=(const Vector2& vec);
	void operator*=(float scale);
	void operator/=(float div);
	bool operator==(const Vector2& vec)const;
	/// <summary>
	/// �x�N�g���̑傫����Ԃ�
	/// </summary>
	/// <returns>�x�N�g���̑傫��</returns>
	float Magnitude()const;

	/// <summary>
	/// �x�N�g���̑傫����2���Ԃ��i������SQRT���Ȃ��j
	/// </summary>
	/// <returns>�x�N�g���̑傫����2��</returns>
	float SQMagnitude()const;

	/// <summary>
	/// �x�N�g���𐳋K������i�傫�����P�ɂ���j
	/// </summary>
	void Normalize();

	/// <summary>
	/// ���K���x�N�g����Ԃ�
	/// </summary>
	/// <returns>���K���x�N�g��</returns>
	Vector2 Normalized()const; 

	/// <summary>
	/// �x�N�g����90���Ȃ���
	/// </summary>
	void Rotate90();

	/// <summary>
	/// 90����]�����x�N�g����Ԃ�
	/// </summary>90����]�x�N�g��
	Vector2 Rotated90()const;
};

Vector2 operator+(const Vector2& lval, const Vector2& rval);
Vector2 operator-(const Vector2& lval, const Vector2& rval);
Vector2 operator*(const Vector2& lval,float scale);
Vector2 operator/(const Vector2& lval,float div);

// ���W�Ƃ��Ďg����悤��
using Position2 = Vector2;
