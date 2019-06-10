#pragma once

#define TAU 6.2831853071795864769252867665590
#define PI  3.1415926535897932384626433832795

#include <math.h>
#include <stdio.h>


union vec2 {
    struct { float x, y; };
    struct { float u, v; };
    struct { float s, t; };
    float E[2];
};

union vec3 {
  struct { float x,y,z; };
  struct { float s,t,p; };
  struct { float r,g,b; };
  float v[3];
};

union vec4 {
  struct { vec3 xyz; float w; };
  struct { float x,y,z,w; };
  struct { float s,t,p,q; };
  struct { float r,g,b,a; };

  float v[4];
};

union mat4 {
  struct {
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;
  };
  float m[16];
};
inline vec3 operator*   (vec3 a, float b)    { return { a.x*b, a.y*b, a.z*b }; }
inline vec3 operator*   (float b, vec3 a)    { return a * b; }
inline vec3 operator/   (vec3 a, float b)    { return a * (1.f/b); }
inline vec3 operator-   (vec3 a)             { return { -a.x, -a.y, -a.z }; }
inline vec3 operator-   (vec3 a, vec3 b)     { return { a.x-b.x, a.y-b.y, a.z-b.z }; }
inline vec3 operator+   (vec3 a, vec3 b)     { return { a.x+b.x, a.y+b.y, a.z+b.z }; }

// inline vec3 operator*=  (vec3 &a, float b)   { a = a * b; return a; }
inline vec3 operator-=  (vec3 &a, vec3 b)    { a = a - b; return a; }
inline vec3 operator+=  (vec3 &a, vec3 b)    { a = a + b; return a; }
// inline  u32 operator==  (vec3 &a, vec3 b)    { return a.x==b.x && a.y==b.y && a.z==b.z; }

inline float dot(vec3 a, vec3 b) {
  return a.x*b.x + a.y*b.y + a.z*b.z;
}
inline vec3 cross(vec3 a, vec3 b) {
  return { a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x };
}
inline float length(vec3 v){
  return sqrt(dot(v,v));
}
inline vec3 normalize(vec3 v){
  return v / length(v);
}

 inline vec3 rotateX(vec3 v, float angleInRadians){
   float x = v.x;
   float y = v.y*cos(angleInRadians) - v.z*sin(angleInRadians);
   float z = v.y*sin(angleInRadians) + v.z*cos(angleInRadians);
   return {x,y,z};
 }
 inline vec3 rotateY(vec3 v, float angleInRadians){
   float x = v.x*cos(angleInRadians) + v.z*sin(angleInRadians);
   float y = v.y;
   float z = -v.x*sin(angleInRadians) + v.z*cos(angleInRadians);
   return {x,y,z};
 }
 inline vec3 rotateZ(vec3 v, float angleInRadians){
   float x = v.x*cos(angleInRadians) - v.y*sin(angleInRadians);
   float y = v.x*sin(angleInRadians) + v.y*cos(angleInRadians);
   float z = v.z;
   return {x,y,z};
 }

/*
void print_mat4(mat4 m) {
  printf("printing mat4 as row major (like it looks in regular math)\n\t%f %f %f %f\n\t%f %f %f %f\n\t%f %f %f %f\n\t%f %f %f %f\n",
    m.m00, m.m10, m.m20, m.m30,
    m.m01, m.m11, m.m21, m.m31,
    m.m02, m.m12, m.m22, m.m32,
    m.m03, m.m13, m.m23, m.m33);
  /*
  printf("printing mat4 as column major (memory layout)\n\t%f %f %f %f\n\t%f %f %f %f\n\t%f %f %f %f\n\t%f %f %f %f\n",
    m.m00, m.m01, m.m02, m.m03,
    m.m10, m.m11, m.m12, m.m13,
    m.m20, m.m21, m.m22, m.m23,
    m.m30, m.m31, m.m32, m.m33);

}*/


inline mat4 identity() {
  return {
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1
  };
}

inline mat4 translation(float x, float y, float z) {
  return {
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    x,y,z,1
  };
}

inline mat4 perspective(float fovyRadians, float aspect, float nearZ, float farZ){
  float cotan = 1.f / tanf(fovyRadians / 2.f);
  float a = cotan / aspect;
  float b = cotan;
  float c = (farZ + nearZ) / (nearZ - farZ);
  float d = (2.f * farZ * nearZ) / (nearZ - farZ);
  mat4 m = {
    a, 0, 0, 0,
    0, b, 0, 0,
    0, 0, c,-1,
    0, 0, d, 0
  };
  return m;
}


inline mat4 frustum(float left, float right, float bottom, float top, float nearZ, float farZ) {
    float rsl = right - left;
    float tsb = top - bottom;
    float fsn = farZ - nearZ;
    
    float a = 2.0f * nearZ / rsl;
    float b = 2.0f * nearZ / tsb;
    float c = (right + left) / rsl;
    float d = (top + bottom) / tsb;
    float e = -(farZ + nearZ) / fsn; 
    float f = (-2.0f * farZ * nearZ) / fsn;

    mat4 m = { 
      a, 0, 0, 0,
      0, b, 0, 0,
      c, d, e,-1,
      0, 0, f, 0 
    };
    
    return m;
}

inline mat4 lookat(
  float eyeX, float eyeY, float eyeZ,
  float centerX, float centerY, float centerZ,
  float upX, float upY, float upZ)
{
  vec3 ev = { eyeX, eyeY, eyeZ };
  vec3 cv = { centerX, centerY, centerZ };
  vec3 uv = { upX, upY, upZ };
  vec3 n = normalize(ev - cv);
  vec3 u = normalize(cross(uv, n));
  vec3 v = cross(n, u);
  float a = dot(-u, ev);
  float b = dot(-v, ev);
  float c = dot(-n, ev);
  mat4 m = {
    u.x, v.x, n.x, 0,
    u.y, v.y, n.y, 0,
    u.z, v.z, n.z, 0,
    a, b, c, 1
  };
  return m;
}

inline mat4 ortho(float left, float right, float bottom, float top, float nearZ, float farZ){
  float a = 0.5f * (right - left);
  float b = 0.5f * (top - bottom);
  float c = -0.5f * (farZ - nearZ);
  float x = -(right+left) / (right-left);
  float y = -(top+bottom) / (top-bottom);
  float z = -(farZ+nearZ) / (farZ-nearZ);
  mat4 m = {
    a, 0, 0, 0,
    0, b, 0, 0,
    0, 0, c, 0,
    x, y, z, 1
  };
  return m;
}

inline mat4 rotation(float radians, float x, float y, float z){
  vec3 v = normalize({x, y, z});
  float cos = cosf(radians);
  float cosp = 1.f - cos;
  float sin = sinf(radians);
  mat4 m = {
    cos + cosp * v.x * v.x,
    cosp * v.x * v.y + v.z * sin,
    cosp * v.x * v.z - v.y * sin,
    0.f,

    cosp * v.x * v.y - v.z * sin,
    cos + cosp * v.y * v.y,
    cosp * v.y * v.z + v.x * sin,
    0.f,

    cosp * v.x * v.z + v.y * sin,
    cosp * v.y * v.z - v.x * sin,
    cos + cosp * v.z * v.z,
    0.f,

    0.f,
    0.f,
    0.f,
    1.f
  };
  return m;
}

inline vec3 operator*(mat4 p_mat, vec3 p_vec)
{
	vec3 vec;

	vec.x = p_mat.m00*p_vec.x + p_mat.m10 * p_vec.y + p_mat.m20 * p_vec.z;
	vec.y = p_mat.m01*p_vec.x + p_mat.m11 * p_vec.y + p_mat.m21 * p_vec.z;
	vec.z = p_mat.m02*p_vec.x + p_mat.m12 * p_vec.y + p_mat.m22 * p_vec.z;
	
	return vec;
}


inline mat4 rotationX(float radians){
  float cos = cosf(radians);
  float sin = sinf(radians);
  mat4 m = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, cos, sin, 0.0f,
    0.0f, -sin, cos, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
  return m;
}

inline mat4 rotationY(float radians){
  float cos = cosf(radians);
  float sin = sinf(radians);
  mat4 m = {
    cos, 0.0f, -sin, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    sin, 0.0f, cos, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
  return m;
}

inline mat4 rotationZ(float radians){
  float cos = cosf(radians);
  float sin = sinf(radians);
  mat4 m = {
    cos, sin, 0.0f, 0.0f,
    -sin, cos, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
  return m;
}


inline mat4 scale(float s){
  mat4 m = {
	  s,0.f,0.f,0.f, 
	  0.f,s,0.f,0.f, 
	  0.f,0.f,s,0.f, 
	  0.f,0.f,0.f,1.f };
  return m;
}

inline mat4 scale(float x, float y, float z){
  mat4 m = { x,0.f,0.f,0.f,  0.f,y,0.f,0.f,  0.f,0.f,z,0.f,  0.f,0.f,0.f,1.f };
  return m;
}


inline mat4 operator* (mat4 L, mat4 R) {
  mat4 m;

  m.m[0]  = L.m[0] * R.m[0]  + L.m[4] * R.m[1]  + L.m[8] * R.m[2]   + L.m[12] * R.m[3];
  m.m[4]  = L.m[0] * R.m[4]  + L.m[4] * R.m[5]  + L.m[8] * R.m[6]   + L.m[12] * R.m[7];
  m.m[8]  = L.m[0] * R.m[8]  + L.m[4] * R.m[9]  + L.m[8] * R.m[10]  + L.m[12] * R.m[11];
  m.m[12] = L.m[0] * R.m[12] + L.m[4] * R.m[13] + L.m[8] * R.m[14]  + L.m[12] * R.m[15];

  m.m[1]  = L.m[1] * R.m[0]  + L.m[5] * R.m[1]  + L.m[9] * R.m[2]   + L.m[13] * R.m[3];
  m.m[5]  = L.m[1] * R.m[4]  + L.m[5] * R.m[5]  + L.m[9] * R.m[6]   + L.m[13] * R.m[7];
  m.m[9]  = L.m[1] * R.m[8]  + L.m[5] * R.m[9]  + L.m[9] * R.m[10]  + L.m[13] * R.m[11];
  m.m[13] = L.m[1] * R.m[12] + L.m[5] * R.m[13] + L.m[9] * R.m[14]  + L.m[13] * R.m[15];

  m.m[2]  = L.m[2] * R.m[0]  + L.m[6] * R.m[1]  + L.m[10] * R.m[2]  + L.m[14] * R.m[3];
  m.m[6]  = L.m[2] * R.m[4]  + L.m[6] * R.m[5]  + L.m[10] * R.m[6]  + L.m[14] * R.m[7];
  m.m[10] = L.m[2] * R.m[8]  + L.m[6] * R.m[9]  + L.m[10] * R.m[10] + L.m[14] * R.m[11];
  m.m[14] = L.m[2] * R.m[12] + L.m[6] * R.m[13] + L.m[10] * R.m[14] + L.m[14] * R.m[15];

  m.m[3]  = L.m[3] * R.m[0]  + L.m[7] * R.m[1]  + L.m[11] * R.m[2]  + L.m[15] * R.m[3];
  m.m[7]  = L.m[3] * R.m[4]  + L.m[7] * R.m[5]  + L.m[11] * R.m[6]  + L.m[15] * R.m[7];
  m.m[11] = L.m[3] * R.m[8]  + L.m[7] * R.m[9]  + L.m[11] * R.m[10] + L.m[15] * R.m[11];
  m.m[15] = L.m[3] * R.m[12] + L.m[7] * R.m[13] + L.m[11] * R.m[14] + L.m[15] * R.m[15];

  return m;
}
