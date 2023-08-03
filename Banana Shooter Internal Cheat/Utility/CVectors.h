struct Vector2
{
	float x = 0; 
	float y = 0; 
	
	bool IsZero(); 

	Vector2 operator+(Vector2 Vec2); 
	Vector2 operator-(Vector2 Vec2); 

	Vector2 operator*(Vector2 Vec2); 
	Vector2 operator/(Vector2 Vec2); 

	Vector2 operator*(float factor); 
	Vector2 operator/(float divided); 
	
};


struct Vector3
{
	float x = 0; 
	float y = 0; 
	float z = 0; 
	
	bool IsZero(); 

	Vector3 operator+(Vector3 Vec3);
	Vector3 operator-(Vector3 Vec3);

	Vector3 operator*(Vector3 Vec3);
	Vector3 operator/(Vector3 Vec3);

	Vector3 operator*(float factor);
	Vector3 operator/(float divided);

};

struct Vector4
{
	float x = 0; 
	float y = 0; 
	float z = 0; 
	float w = 0; 

	Vector4 operator+( Vector4 Vec4 );
	Vector4 operator-( Vector4 Vec4 );

	Vector4 operator*( Vector4 Vec4 );
	Vector4 operator/( Vector4 Vec4 );

	Vector4 operator*( float factor );
	Vector4 operator/( float divided);
};
