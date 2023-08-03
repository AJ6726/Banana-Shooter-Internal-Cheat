#include "CVectors.h"


bool Vector2::IsZero()
{
    if (x == 0.f && y == 0.f)
        return true;

    return false;
}

Vector2 Vector2::operator+(Vector2 Vec2)
{
	return Vector2{ x + Vec2.x, y + Vec2.y };
}

Vector2 Vector2::operator-(Vector2 Vec2)
{
	return Vector2{ x - Vec2.x, y - Vec2.y };
}

Vector2 Vector2::operator*(Vector2 Vec2)
{
	return Vector2{ x * Vec2.x, y * Vec2.y };
}

Vector2 Vector2::operator/(Vector2 Vec2)
{
	return Vector2{ x / Vec2.x, y / Vec2.y };
}

Vector2 Vector2::operator*(float factor)
{
	return Vector2{ x * factor, y * factor };
}

Vector2 Vector2::operator/(float divided)
{
	return Vector2{ x / divided, y / divided };
}

//=====================================================================================//
//=====================================================================================//

bool Vector3::IsZero()
{
    if (x == 0.f && y == 0.f && z == 0.f)
        return true;

    return false;
}

Vector3 Vector3::operator+(Vector3 Vec3) 
{
    return Vector3{ x + Vec3.x, y + Vec3.y, z + Vec3.z };
}

Vector3 Vector3::operator-(Vector3 Vec3) 
{
    return Vector3{ x - Vec3.x, y - Vec3.y, z - Vec3.z };
}

Vector3 Vector3::operator*(Vector3 Vec3)
{
    return Vector3{ x * Vec3.x, y * Vec3.y, z * Vec3.z };
}

Vector3 Vector3::operator/(Vector3 Vec3) 
{ 
    return Vector3{ x / Vec3.x, y / Vec3.y, z / Vec3.z };
}

Vector3 Vector3::operator*(float factor) 
{
    return Vector3{ x * factor, y * factor, z * factor };
}

Vector3 Vector3::operator/(float divided) 
{
    return Vector3{ x / divided, y / divided, z / divided };
}

//=====================================================================================//
//=====================================================================================//

Vector4 Vector4::operator+(Vector4 Vec4)
{
    return { x + Vec4.x, y + Vec4.y, z + Vec4.z, w + Vec4.w };
}

Vector4 Vector4::operator-(Vector4 Vec4)
{
    return { x - Vec4.x, y - Vec4.y, z - Vec4.z, w - Vec4.w };
}

Vector4 Vector4::operator*(Vector4 Vec4)
{
    return { x * Vec4.x, y * Vec4.y, z * Vec4.z, w * Vec4.w };
}

Vector4 Vector4::operator/(Vector4 Vec4) 
{
    return { x / Vec4.x, y / Vec4.y, z / Vec4.z, w / Vec4.w };
}

Vector4 Vector4::operator*(float factor) 
{
    return { x * factor, y * factor, z * factor, w * factor };
}

Vector4 Vector4::operator/(float divided) 
{
    return { x / divided, y / divided, z / divided, w / divided };
}
