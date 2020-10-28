#pragma once
#include "lin_maths_types.h"

#define to_radians(deg)			((deg) * (MATH_PI / 180.0f))
#define to_degrees(rad)			((rad) * (180.0f / MATH_PI_INVERSE))
#define real_equals(a, b, tol)	(fabsf((a) - (b)) < (tol))

inline r32 map(r32 from_x1, r32 from_x2, r32 to_x1, r32 to_x2, r32 x) {
	return (to_x2 - to_x1) / (from_x2 - from_x1) * (x - from_x1) + to_x1;
}

inline r32 map01(r32 x1, r32 x2, r32 x) {
	return map(x1, x2, 0, 1, x);
}

inline Vec2 vec2_min(Vec2 a, Vec2 b) {
	Vec2 r;
	r.x = minimum(a.x, b.x);
	r.y = minimum(a.y, b.y);
	return r;
}

inline Vec3 vec3_min(Vec3 a, Vec3 b) {
	Vec3 r;
	r.x = minimum(a.x, b.x);
	r.y = minimum(a.y, b.y);
	r.z = minimum(a.z, b.z);
	return r;
}

inline Vec4 vec4_min(Vec4 a, Vec4 b) {
	Vec4 r;
	r.x = minimum(a.x, b.x);
	r.y = minimum(a.y, b.y);
	r.z = minimum(a.z, b.z);
	r.w = minimum(a.w, b.w);
	return r;
}

inline bool operator ==(Vec2 a, Vec2 b) {
	return a.x == b.x && a.y == b.y;
}
inline bool operator !=(Vec2 a, Vec2 b) {
	return !(a == b);
}

inline bool operator ==(Vec3 a, Vec3 b) {
	return a.x == b.x && a.y == b.y && a.z == b.z;
}
inline bool operator !=(Vec3 a, Vec3 b) {
	return !(a == b);
}

inline bool operator ==(Vec4 a, Vec4 b) {
	return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}
inline bool operator !=(Vec4 a, Vec4 b) {
	return !(a == b);
}

inline bool operator ==(Vec2s a, Vec2s b) {
	return a.x == b.x && a.y == b.y;
}
inline bool operator !=(Vec2s a, Vec2s b) {
	return !(a == b);
}

inline bool operator ==(Vec3s a, Vec3s b) {
	return a.x == b.x && a.y == b.y && a.z == b.z;
}
inline bool operator !=(Vec3s a, Vec3s b) {
	return !(a == b);
}

inline bool operator ==(Vec4s a, Vec4s b) {
	return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}
inline bool operator !=(Vec4s a, Vec4s b) {
	return !(a == b);
}

inline Vec2 to_vec2(Vec2s v) {
	return vec2((r32)v.x, (r32)v.y);
}

inline Vec3 to_vec3(Vec3s v) {
	return vec3((r32)v.x, (r32)v.y, (r32)v.z);
}

inline Vec4 to_vec4(Vec4s v) {
	return vec4((r32)v.x, (r32)v.y, (r32)v.z, (r32)v.w);
}

const Vec3 WORLD_UP      = vec3(0, 1, 0);
const Vec3 WORLD_RIGHT   = vec3(1, 0, 0);
const Vec3 WORLD_FORWARD = vec3(0, 0, 1);

Vec2  vec2_add(Vec2 a, Vec2 b);
Vec3  vec3_add(Vec3 a, Vec3 b);
Vec4  vec4_add(Vec4 a, Vec4 b);
Vec2s vec2s_add(Vec2s a, Vec2s b);
Vec3s vec3s_add(Vec3s a, Vec3s b);
Vec4s vec4s_add(Vec4s a, Vec4s b);

//
//
//

Vec2  vec2_sub(Vec2 a, Vec2 b);
Vec3  vec3_sub(Vec3 a, Vec3 b);
Vec4  vec4_sub(Vec4 a, Vec4 b);
Vec2s vec2s_sub(Vec2s a, Vec2s b);
Vec3s vec3s_sub(Vec3s a, Vec3s b);
Vec4s vec4s_sub(Vec4s a, Vec4s b);

//
//
//

Vec2  vec2_mul(r32 s, Vec2 v);
Vec2  vec2_mul(Vec2 v, r32 s);
Vec3  vec3_mul(r32 s, Vec3 v);
Vec3  vec3_mul(Vec3 v, r32 s);
Vec4  vec4_mul(r32 s, Vec4 v);
Vec4  vec4_mul(Vec4 v, r32 s);
Vec2s vec2s_mul(s32 s, Vec2s v);
Vec2s vec2s_mul(Vec2s v, s32 s);
Vec3s vec3s_mul(s32 s, Vec3s v);
Vec3s vec3s_mul(Vec3s v, s32 s);
Vec4s vec4s_mul(s32 s, Vec4s v);
Vec4s vec4s_mul(Vec4s v, s32 s);

//
//
//

Vec2  vec2_div(Vec2 v, r32 s);
Vec3  vec3_div(Vec3 v, r32 s);
Vec4  vec4_div(Vec4 v, r32 s);
Vec2s vec2s_div(Vec2s v, s32 s);
Vec3s vec3s_div(Vec3s v, s32 s);
Vec4s vec4s_div(Vec4s v, s32 s);

//
//
//

Vec2  vec2_hadamard(Vec2 l, Vec2 r);
Vec3  vec3_hadamard(Vec3 l, Vec3 r);
Vec4  vec4_hadamard(Vec4 l, Vec4 r);
Vec2s vec2s_hadamard(Vec2s l, Vec2s r);
Vec3s vec3s_hadamard(Vec3s l, Vec3s r);
Vec4s vec4s_hadamard(Vec4s l, Vec4s r);

//
//
//

inline Vec2 operator-(const Vec2 &v) {
	return vec2(-v.x, -v.y);
}
inline Vec3 operator-(const Vec3 &v) {
	return vec3(-v.x, -v.y, -v.z);
}
inline Vec4 operator-(const Vec4 &v) {
	return vec4(-v.x, -v.y, -v.z, -v.w);
}
inline Vec2s operator-(const Vec2s &v) {
	return vec2s(-v.x, -v.y);
}
inline Vec3s operator-(const Vec3s &v) {
	return vec3s(-v.x, -v.y, -v.z);
}
inline Vec4s operator-(const Vec4s &v) {
	return vec4s(-v.x, -v.y, -v.z, -v.w);
}

//
//
//

inline Vec2 operator+(Vec2 a, Vec2 b) {
	return vec2_add(a, b);
}
inline Vec3 operator+(Vec3 a, Vec3 b) {
	return vec3_add(a, b);
}
inline Vec4 operator+(Vec4 a, Vec4 b) {
	return vec4_add(a, b);
}
inline Vec2s operator+(Vec2s a, Vec2s b) {
	return vec2s_add(a, b);
}
inline Vec3s operator+(Vec3s a, Vec3s b) {
	return vec3s_add(a, b);
}
inline Vec4s operator+(Vec4s a, Vec4s b) {
	return vec4s_add(a, b);
}

//
//
//

inline Vec2 operator-(Vec2 a, Vec2 b) {
	return vec2_sub(a, b);
}
inline Vec3 operator-(Vec3 a, Vec3 b) {
	return vec3_sub(a, b);
}
inline Vec4 operator-(Vec4 a, Vec4 b) {
	return vec4_sub(a, b);
}
inline Vec2s operator-(Vec2s a, Vec2s b) {
	return vec2s_sub(a, b);
}
inline Vec3s operator-(Vec3s a, Vec3s b) {
	return vec3s_sub(a, b);
}
inline Vec4s operator-(Vec4s a, Vec4s b) {
	return vec4s_sub(a, b);
}

//
//
//

inline Vec2 &operator+=(Vec2 &a, Vec2 b) {
	a = vec2_add(a, b);
	return a;
}
inline Vec3 &operator+=(Vec3 &a, Vec3 b) {
	a = vec3_add(a, b);
	return a;
}
inline Vec4 &operator+=(Vec4 &a, Vec4 b) {
	a = vec4_add(a, b);
	return a;
}
inline Vec2s &operator+=(Vec2s &a, Vec2s b) {
	a = vec2s_add(a, b);
	return a;
}
inline Vec3s &operator+=(Vec3s &a, Vec3s b) {
	a = vec3s_add(a, b);
	return a;
}
inline Vec4s &operator+=(Vec4s &a, Vec4s b) {
	a = vec4s_add(a, b);
	return a;
}

//
//
//

inline Vec2 &operator-=(Vec2 &a, Vec2 b) {
	a = vec2_sub(a, b);
	return a;
}
inline Vec3 &operator-=(Vec3 &a, Vec3 b) {
	a = vec3_sub(a, b);
	return a;
}
inline Vec4 &operator-=(Vec4 &a, Vec4 b) {
	a = vec4_sub(a, b);
	return a;
}
inline Vec2s &operator-=(Vec2s &a, Vec2s b) {
	a = vec2s_sub(a, b);
	return a;
}
inline Vec3s &operator-=(Vec3s &a, Vec3s b) {
	a = vec3s_sub(a, b);
	return a;
}
inline Vec4s &operator-=(Vec4s &a, Vec4s b) {
	a = vec4s_sub(a, b);
	return a;
}

//
//
//

inline Vec2 operator*(Vec2 v, r32 s) {
	return vec2_mul(v, s);
}
inline Vec2 operator*(r32 s, Vec2 v) {
	return vec2_mul(v, s);
}
inline Vec3 operator*(Vec3 v, r32 s) {
	return vec3_mul(v, s);
}
inline Vec3 operator*(r32 s, Vec3 v) {
	return vec3_mul(v, s);
}
inline Vec4 operator*(Vec4 v, r32 s) {
	return vec4_mul(v, s);
}
inline Vec4 operator*(r32 s, Vec4 v) {
	return vec4_mul(v, s);
}
inline Vec2s operator*(Vec2s v, s32 s) {
	return vec2s_mul(v, s);
}
inline Vec2s operator*(s32 s, Vec2s v) {
	return vec2s_mul(v, s);
}
inline Vec3s operator*(Vec3s v, s32 s) {
	return vec3s_mul(v, s);
}
inline Vec3s operator*(s32 s, Vec3s v) {
	return vec3s_mul(v, s);
}
inline Vec4s operator*(Vec4s v, s32 s) {
	return vec4s_mul(v, s);
}
inline Vec4s operator*(s32 s, Vec4s v) {
	return vec4s_mul(v, s);
}

//
//
//

inline Vec2 operator/(Vec2 v, r32 s) {
	return vec2_div(v, s);
}
inline Vec3 operator/(Vec3 v, r32 s) {
	return vec3_div(v, s);
}
inline Vec4 operator/(Vec4 v, r32 s) {
	return vec4_div(v, s);
}
inline Vec2s operator/(Vec2s v, s32 s) {
	return vec2s_div(v, s);
}
inline Vec3s operator/(Vec3s v, s32 s) {
	return vec3s_div(v, s);
}
inline Vec4s operator/(Vec4s v, s32 s) {
	return vec4s_div(v, s);
}

//
//
//

inline Vec2 &operator*=(Vec2 &t, r32 s) {
	t = vec2_mul(t, s);
	return t;
}
inline Vec3 &operator*=(Vec3 &t, r32 s) {
	t = vec3_mul(t, s);
	return t;
}
inline Vec4 &operator*=(Vec4 &t, r32 s) {
	t = vec4_mul(t, s);
	return t;
}
inline Vec2s &operator*=(Vec2s &t, s32 s) {
	t = vec2s_mul(t, s);
	return t;
}
inline Vec3s &operator*=(Vec3s &t, s32 s) {
	t = vec3s_mul(t, s);
	return t;
}
inline Vec4s &operator*=(Vec4s &t, s32 s) {
	t = vec4s_mul(t, s);
	return t;
}

//
//
//

inline Vec2 &operator/=(Vec2 &t, r32 s) {
	t = vec2_div(t, s);
	return t;
}
inline Vec3 &operator/=(Vec3 &t, r32 s) {
	t = vec3_div(t, s);
	return t;
}
inline Vec4 &operator/=(Vec4 &t, r32 s) {
	t = vec4_div(t, s);
	return t;
}
inline Vec2s &operator/=(Vec2s &t, s32 s) {
	t = vec2s_div(t, s);
	return t;
}
inline Vec3s &operator/=(Vec3s &t, s32 s) {
	t = vec3s_div(t, s);
	return t;
}
inline Vec4s &operator/=(Vec4s &t, s32 s) {
	t = vec4s_div(t, s);
	return t;
}

//
//
//

r32 vec2_dot(Vec2 a, Vec2 b);
r32 vec3_dot(Vec3 a, Vec3 b);
r32 vec4_dot(Vec4 a, Vec4 b);

//
//
//

r32 vec2_determinant(Vec2 a, Vec2 b);
Vec3 vec2_cross(Vec2 a, Vec2 b);
Vec3 vec3_cross(Vec3 a, Vec3 b);
Vec2 vec2_triple_product(Vec2 a, Vec2 b, Vec2 c);
Vec3 vec3_triple_product(Vec3 a, Vec3 b, Vec3 c);


//
//
//

r32 vec2_length2(Vec2 v);
r32 vec3_length2(Vec3 v);
r32 vec4_length2(Vec4 v);

r32 vec2_length(Vec2 v);
r32 vec3_length(Vec3 v);
r32 vec4_length(Vec4 v);

r32 vec2_distance(Vec2 a, Vec2 b);
r32 vec3_distance(Vec3 a, Vec3 b);
r32 vec4_distance(Vec4 a, Vec4 b);

//
//
//

// these check for division by zero
// returns {0,0,0} if vector length is zero
Vec2 vec2_normalize_check(Vec2 v);
Vec3 vec3_normalize_check(Vec3 v);
Vec4 vec4_normalize_check(Vec4 v);

// no checking for division by zero
Vec2 vec2_normalize(Vec2 v);
Vec3 vec3_normalize(Vec3 v);
Vec4 vec4_normalize(Vec4 v);

//
//
//

r32 vec2_angle_between(Vec2 a, Vec2 b);
r32 vec2_angle_between_normalize(Vec2 a, Vec2 b);
r32 vec3_angle_between(Vec3 a, Vec3 b);
r32 vec3_angle_between_normalize(Vec3 a, Vec3 b);

r32 vec2_signed_angle_between(Vec2 a, Vec2 b);
r32 vec2_signed_angle_between_normalize(Vec2 a, Vec2 b);
r32 vec3_signed_angle_between(Vec3 a, Vec3 b, Vec3 n);
r32 vec3_signed_angle_between_normalize(Vec3 a, Vec3 b, Vec3 n);

//
//
//

inline bool vec2_null(Vec2 a) { return fabsf(a.x) < EPSILON_FLOAT && fabsf(a.y) < EPSILON_FLOAT; }
inline bool vec3_null(Vec3 a) { return fabsf(a.x) < EPSILON_FLOAT && fabsf(a.y) < EPSILON_FLOAT && fabsf(a.z) < EPSILON_FLOAT; }
inline bool vec4_null(Vec4 a) { return fabsf(a.x) < EPSILON_FLOAT && fabsf(a.y) < EPSILON_FLOAT && fabsf(a.z) < EPSILON_FLOAT && fabsf(a.w) < EPSILON_FLOAT; }

bool vec2_equals(Vec2 a, Vec2 b, r32 tolerance = MATH_R32_EQUALS_DEFAULT_TOLERANCE);
bool vec3_equals(Vec3 a, Vec3 b, r32 tolerance = MATH_R32_EQUALS_DEFAULT_TOLERANCE);
bool vec4_equals(Vec4 a, Vec4 b, r32 tolerance = MATH_R32_EQUALS_DEFAULT_TOLERANCE);

//
//
//

Mat2 mat2_identity();
r32 mat2_det(const Mat2 &mat);
Mat2 mat2_inverse(const Mat2 &mat);
Mat2 mat2_transpose(const Mat2 &m);

Mat3 mat3_identity();
r32 mat3_det(const Mat3 &mat);
Mat3 mat3_inverse(const Mat3 &mat);
Mat3 mat3_transpose(const Mat3 &m);

Mat4 mat4_identity();
r32 mat4_det(const Mat4 &mat);
Mat4 mat4_inverse(const Mat4 &mat);
Mat4 mat4_transpose(const Mat4 &m);

//
//
//

Mat2 mat2_mul(const Mat2 &left, const Mat2 &right);
Vec2 mat2_vec2_mul(const Mat2 &mat, Vec2 vec);

Mat3 mat3_mul(const Mat3 &left, const Mat3 &right);
Vec3 mat3_vec3_mul(const Mat3 &mat, Vec3 vec);
Vec2 mat3_vec2_mul(const Mat3 &mat, Vec2 vec, r32 h = 1);

Mat4 mat4_mul(const Mat4 &left, const Mat4 &right);
Vec4 mat4_vec4_mul(const Mat4 &mat, Vec4 vec);

inline Mat2 operator*(const Mat2 &a, const Mat2 &b) {
	return mat2_mul(a, b);
}
inline Mat2 &operator*=(Mat2 &t, Mat2 &o) {
	t = mat2_mul(t, o);
	return t;
}
inline Vec2 operator*(const Mat2 &m, Vec2 v) {
	return mat2_vec2_mul(m, v);
}

inline Mat3 operator*(const Mat3 &a, const Mat3 &b) {
	return mat3_mul(a, b);
}
inline Mat3 &operator*=(Mat3 &t, Mat3 &o) {
	t = mat3_mul(t, o);
	return t;
}
inline Vec3 operator*(const Mat3 &m, Vec3 v) {
	return mat3_vec3_mul(m, v);
}

inline Mat4 operator*(const Mat4 &a, const Mat4 &b) {
	return mat4_mul(a, b);
}
inline Mat4 &operator*=(Mat4 &t, Mat4 &o) {
	t = mat4_mul(t, o);
	return t;
}
inline Vec4 operator*(const Mat4 &m, Vec4 v) {
	return mat4_vec4_mul(m, v);
}

//
//
//

Mat2 mat2_scalar(r32 x, r32 y);
Mat2 mat2_scalar(Vec2 s);

Mat2 mat2_rotation(r32 angle);

Mat3 mat3_scalar(r32 S_1, r32 S_2);
Mat3 mat3_scalar(Vec2 s);

Mat3 mat3_translation(r32 T_x, r32 T_y);
Mat3 mat3_translation(Vec2 t);

Mat3 mat3_rotation(r32 angle);

Mat3 mat3_lookat(Vec2 from, Vec2 to, Vec2 forward = vec2(1, 0));

Mat4 mat4_scalar(r32 S_1, r32 S_2, r32 S_3);
Mat4 mat4_scalar(Vec3 s);

Mat4 mat4_translation(r32 T_x, r32 T_y, r32 T_z);
Mat4 mat4_translation(Vec3 t);

Mat4 mat4_rotation_x(r32 angle);
Mat4 mat4_rotation_y(r32 angle);
Mat4 mat4_rotation_z(r32 angle);
Mat4 mat4_rotation(r32 x, r32 y, r32 z, r32 angle);
Mat4 mat4_rotation(Vec3 axis, r32 angle);

Mat4 mat4_lookat(Vec3 from, Vec3 to, Vec3 world_up = WORLD_UP);

Mat4 mat4_ortho_gl(r32 l, r32 r, r32 t, r32 b, r32 n, r32 f);
Mat4 mat4_perspective_gl(r32 fov, r32 aspect_ratio, r32 n, r32 f);

Mat4 mat4_ortho_dx(r32 l, r32 r, r32 t, r32 b, r32 n, r32 f);
Mat4 mat4_perspective_dx(r32 fov, r32 aspect_ratio, r32 n, r32 f);

Vec3 mat4_right(const Mat4 &m);
Vec3 mat4_up(const Mat4 &m);
Vec3 mat4_forward(const Mat4 &m);

bool mat3_equals(const Mat3 &a, const Mat3 &b, r32 tolerance = MATH_R32_EQUALS_DEFAULT_TOLERANCE);
bool mat4_equals(const Mat4 &a, const Mat4 &b, r32 tolerance = MATH_R32_EQUALS_DEFAULT_TOLERANCE);

Mat3 mat4_to_mat3(const Mat4 &mat);
Mat4 mat3_to_mat4(const Mat3 &mat);

//
//
//

Quat quat_identity();

inline Quat operator-(Quat &q) {
	return quat(-q.v4);
}
inline Quat operator-(Quat r1, Quat r2) {
	return quat(r1.v4 - r2.v4);
}
inline Quat operator+(Quat r1, Quat r2) {
	return quat(r1.v4 + r2.v4);
}
inline Quat operator*(Quat q, r32 s) {
	return quat(q.v4 * s);
}
inline Quat operator*(r32 s, Quat q) {
	return quat(q.v4 * s);
}

r32 quat_dot(Quat q1, Quat q2);
r32 quat_length(Quat q);

Quat        quat_normalize(Quat q);
Quat        quat_conjugate(Quat q);
Quat        quat_mul(Quat q1, Quat q2);
inline Quat operator*(Quat a, Quat b) {
	return quat_mul(a, b);
}

Vec3 quat_rotate(Quat q, Vec3 v);
Quat quat_angle_axis(Vec3 axis, r32 angle);
Quat quat_angle_axis_normalize(Vec3 axis, r32 angle);

void quat_get_angle_axis(Quat q, r32 *angle, Vec3 *axis);
Vec3 quat_get_axis(Quat q);
r32  quat_get_angle(Quat q);

Quat quat_mat4(const Mat4 &m);
Quat quat_mat4_normalize(const Mat4 &m);
Mat4 quat_get_mat4(Quat q);

Vec3 quat_forward(Quat q);
Vec3 quat_right(Quat q);
Vec3 quat_up(Quat q);

Quat quat_euler_angles(r32 pitch, r32 yaw, r32 roll);
Quat quat_euler_angles(Vec3 euler);
Vec3 quat_get_euler_angles(Quat q);

Quat quat_between(Vec3 from, Vec3 to);
Quat quat_between(Quat a, Quat b);

Quat quat_lookat(Vec3 from, Vec3 to, Vec3 world_forward = WORLD_FORWARD);

bool quat_equals(Quat a, Quat b, r32 tolerance = MATH_R32_EQUALS_DEFAULT_TOLERANCE);

//
//
//

inline Quad quad_from_points(Vec2 a, Vec2 b, Vec2 c, Vec2 d) {
	Quad quad;
	quad.positions[0] = a;
	quad.positions[1] = b;
	quad.positions[2] = c;
	quad.positions[3] = d;

	auto n1 = vec2_normalize(b - a);
	auto n2 = vec2_normalize(c - b);
	auto n3 = vec2_normalize(d - c);
	auto n4 = vec2_normalize(a - d);

	quad.normals[0] = vec2(-n1.y, n1.x);
	quad.normals[1] = vec2(-n2.y, n2.x);
	quad.normals[2] = vec2(-n3.y, n3.x);
	quad.normals[3] = vec2(-n4.y, n4.x);

	return quad;
}

inline Ray2d ray_from_points(Vec2 a, Vec2 b) {
	Ray2d ray;
	ray.origin	= a;
	ray.dir		= vec2_normalize(b - a);
	return ray;
}

//
//
//

Color3 linear_to_srgb(Color3 color);
Color4 linear_to_srgb(Color4 color);
Color3 linear_to_srgb(Color3 color, r32 gamma);
Color4 linear_to_srgb(Color4 color, r32 gamma);

Color3 srgb_to_linear(Color3 color);
Color4 srgb_to_linear(Color4 color);
Color3 srgb_to_linear(Color3 color, r32 gamma);
Color4 srgb_to_linear(Color4 color, r32 gamma);

Colorh color4_to_hex(Color4 v);
Color4 hex_to_color4(Colorh c);
Color3 hex_to_color3(Colorh c);

Color3 hsv_to_rgb(Color3 c);
Color3 rgb_to_hsv(Color3 c);
Color4 hsv_to_rgb(Color4 c);
Color4 rgb_to_hsv(Color4 c);

//
//
//

Vec2 vec2_clamp(Vec2 min, Vec2 max, Vec2 v);
Vec3 vec3_clamp(Vec3 min, Vec3 max, Vec3 v);
Vec4 vec4_clamp(Vec4 min, Vec4 max, Vec4 v);

//
//
//

template <typename Type>
Type lerp(Type from, Type to, r32 t) {
	return (1 - t) * from + t * to;
}

template <typename Type>
Type bezier_quadratic(Type a, Type b, Type c, r32 t) {
	r32 mt = 1 - t;
	r32 w1 = mt * mt;
	r32 w2 = 2 * mt * t;
	r32 w3 = t * t;
	return w1 * a + w2 * b + w3 * c;
}

template <typename Type>
Type bezeir_cubic(Type a, Type b, Type c, Type d, r32 t) {
	r32 mt = 1.0f - t;
	r32 w1 = mt * mt * mt;
	r32 w2 = 3 * mt * mt * t;
	r32 w3 = 3 * mt * t * t;
	r32 w4 = t * t * t;
	return w1 * a + w2 * b + w3 * c + w4 * d;
}

template <typename Type>
Type slerp(Type from, Type to, r32 angle, r32 t) {
	r32 s   = sinf(angle);
	r32 ts  = sinf(angle * t);
	r32 mts = sinf(angle * (1 - t));
	return (mts * from + ts * to) * (1.0f / s);
}

Mat4 lerp(Mat4 &from, Mat4 &to, r32 t);
Vec2 slerp(Vec2 from, Vec2 to, r32 t);
Vec3 slerp(Vec3 from, Vec3 to, r32 t);
Quat slerp(Quat from, Quat to, r32 t);

r32  step(r32 edge, r32 val);
Vec2 step(Vec2 edge, Vec2 val);
Vec3 step(Vec3 edge, Vec3 val);
Vec4 step(Vec4 edge, Vec4 val);
Quat step(Quat edge, Quat val);

r32 smoothstep(r32 a, r32 b, r32 x);
r32 smoothstep(Vec2 a, Vec2 b, Vec2 x);
r32 smoothstep(Vec3 a, Vec3 b, Vec3 x);
r32 smoothstep(Vec4 a, Vec4 b, Vec4 x);
r32 smoothstep(Quat a, Quat b, Quat x);
r32 inverse_smoothstep(r32 x);

//
//
//

Vec2 move_toward(Vec2 from, Vec2 to, r32 factor);
Vec3 move_toward(Vec3 from, Vec3 to, r32 factor);
Vec4 move_toward(Vec4 from, Vec4 to, r32 factor);

//
//
//

Vec2 rotate_around(Vec2 point, Vec2 center, r32 angle);
Quat rotate_toward(Quat from, Quat to, r32 max_angle);

//
//
//

template <typename T>
inline T integrate(const T &x, r32 h, const T &f) {
	return x + h * f;
}

template <typename T, typename Function>
inline T integrate(const T &x, r32 t, r32 h, Function f) {
	return x + h * f(t, x);
}

template <typename T, typename Function>
inline T integrate_rk4(const T &x, r32 t, r32 h, Function f) {
	T k1 = h * f(t, x);
	T k2 = h * f(t + 0.5f * h, x + 0.5f * k1);
	T k3 = h * f(t + 0.5f * h, x + 0.5f * k2);
	T k4 = h * f(t + h, x + k3);
	return x + (k1 + 2.0f * (k2 + k3) + k4) / 6.0f;
}

//
//
//

//
// TODO: Testing all of these functions
//

r32 signed_area(Vec2 a, Vec2 b, Vec2 c);
r32 signed_area(Vec3 a, Vec3 b, Vec3 c);
bool triangle_is_cw(Vec2 a, Vec2 b, Vec2 c);
Vec2 corner_point(const Mm_Rect &b, u32 n); // n=00,01,10,11 for 4 different corners

r32 point_to_segment_length2(Vec2 p, Vec2 a, Vec2 b);
r32 point_to_mm_rect_length2(Vec2 p, const Mm_Rect &rect);
r32 point_to_aabb2d_length2(Vec2 p, const Aabb2d &aabb);

Vec2 closest_point_point_segment(Vec2 p, Vec2 a, Vec2 b, r32 *t);
Vec2 closest_point_point_segment(Vec2 p, Vec2 a, Vec2 b);
Vec2 closest_point_origin_segment(Vec2 a, Vec2 b, r32 *t);
Vec2 closest_point_origin_segment(Vec2 a, Vec2 b);
Vec2 closest_point_point_mm_rect(Vec2 a, const Mm_Rect &rect);
Vec2 closest_point_origin_mm_rect(const Mm_Rect &rect);
Vec2 closest_point_point_aabb2d(Vec2 a, const Aabb2d &aabb);
Vec2 closest_point_point_aabb2d(const Aabb2d &aabb);
Vec2 closest_point_point_triangle(Vec2 p, Vec2 a, Vec2 b, Vec2 c);
Vec2 closest_point_origin_triangle(Vec2 a, Vec2 b, Vec2 c);

r32 closest_point_segment_segment(Vec2 p1, Vec2 q1, Vec2 p2, Vec2 q2, r32 *s, r32 *t, Vec2 *c1, Vec2 *c2);

Vec3 barycentric(Vec2 a, Vec2 b, Vec2 c, Vec2 p);
Vec3 barycentric(Vec3 a, Vec3 b, Vec3 c, Vec3 p);

bool is_quad_convex(Vec2 a, Vec2 b, Vec2 c, Vec2 d);
bool is_quad_convex(Vec3 a, Vec3 b, Vec3 c, Vec3 d);

Mm_Rect enclosing_mm_rect_mm_rect(const Mm_Rect &a0, const Mm_Rect &a1);
Circle enclosing_circle_circle(const Circle &c0, const Circle &c1);
Mm_Rect enclosing_mm_rect_circle(const Mm_Rect &r, const Circle &c);

s32 point_farthest_from_edge(Vec2 a, Vec2 b, Vec2 *p, s32 n);
void extreme_points_alone_direction(Vec2 dir, Vec2 *pt, s32 n, s32 *min_index, s32 *max_index);
void most_seperated_points_on_aabb(Vec2 *pt, s32 n, s32 *min, s32 *max);
Circle circle_from_distant_points(Vec2 *pt, s32 n);
r32 min_area_rect(Vec2 *pt, s32 num_pts, Vec2 *center, Vec2 u[2]);

Mm_Rect transform_mmrect(const Mm_Rect &a, const Mat2 &mat, Vec2 t);
Mm_Rect transform_mmrect(const Mm_Rect &a, r32 rot, Vec2 t);
Aabb2d update_aabb(const Aabb2d &a, const Mat2 &mat, Vec2 t);
Aabb2d update_aabb(const Aabb2d &a, r32 rot, Vec2 t);

bool test_point_inside_rect(Vec2 point, const Mm_Rect &rect);
bool test_point_inside_aabb(Vec2 point, const Aabb2d &aabb);
bool test_point_inside_circle(Vec2 p, const Circle &c);
bool test_point_inside_capsule(Vec2 p, const Capsule &c);
bool test_point_inside_triangle(Vec2 p, Vec2 a, Vec2 b, Vec2 c);
bool test_origin_inside_triangle(Vec2 a, Vec2 b, Vec2 c);
bool test_point_inside_convex_polygon(Vec2 p, Vec2 *v, s32 n);

bool test_mmrect_vs_mmrect(const Mm_Rect &a, const Mm_Rect &b);
bool test_aabb_vs_aabb(const Aabb2d &a, const Aabb2d &b);
bool test_circle_vs_circle(const Circle &a, const Circle &b);
bool test_quad_vs_quad(const Quad &a, const Quad &b);
bool test_circle_vs_capsule(const Circle& circle, const Capsule& capsule);
bool test_segment_vs_circle(Vec2 a, Vec2 b, const Circle &c);
bool test_circle_vs_aabb(const Circle &c, const Aabb2d &b);
bool test_ray_vs_circle(const Ray2d &ray, const Circle &circle);
bool test_segment_vs_mm_rect(Vec2 p0, Vec2 p1, const Mm_Rect &rect);

bool segment_vs_segment(Vec2 a, Vec2 b, Vec2 c, Vec2 d, r32 *t, Vec2 *p);
bool circle_vs_aabb(const Circle &c, Aabb2d &b, Vec2 *p);
bool circle_vs_triangle(const Circle &circle, Vec2 a, Vec2 b, Vec2 c, Vec2 *p);

bool intersect_segment_ray(Vec2 p1, Vec2 p2, Vec2 q1, Vec2 q2, r32 *t, Vec2 *p);
bool intersect_segment_ray(Vec2 p1, Vec2 q1, const Ray2d &ray, r32 *t, Vec2 *p);
bool intersect_ray_ray(Vec2 p1, Vec2 q1, Vec2 p2, Vec2 q2, r32 *t, r32 *u, Vec2 *p);
bool intersect_ray_ray(Vec2 p1, Vec2 q1, const Ray2d &b, r32 *t, r32 *u, Vec2 *p);
bool intersect_ray_ray(const Ray2d &a, const Ray2d &b, r32 *t, r32 *u, Vec2 *p);
bool intersect_segment_segment(Vec2 p1, Vec2 q1, Vec2 p2, Vec2 q2, r32 *t, r32 *u, Vec2 *p);
bool intersect_circle_ray(const Circle &circle, const Ray2d &ray, r32 *t, Vec2 *p); // |ray.dir|=1
bool intersect_circle_segment(const Circle &circle, Vec2 p, Vec2 q, r32 *t);
bool intersect_mm_rect_ray(const Ray2d &ray, const Mm_Rect &rect, r32 *tmin, Vec2 *q);
bool intersect_mm_rect_segment(Vec2 a, Vec2 b, const Mm_Rect &rect, r32 *tmin, Vec2 *q);

bool dynamic_circle_vs_circle(const Circle &c0, const Circle &c1, Vec2 v0, Vec2 v1, r32 *t);
bool dynamic_circle_vs_mm_rect(const Circle &c, Vec2 d, const Mm_Rect &b, r32 *t);
bool dynamic_mm_rect_vs_mm_rect(const Mm_Rect &a, const Mm_Rect &b, Vec2 va, Vec2 vb, r32 *tfirst, r32 *tlast);

Vec2 support(const Circle &c, Vec2 dir);
Vec2 support(const Mm_Rect &m, Vec2 dir);
Vec2 support(const Polygon &p, Vec2 dir);
Vec2 support(const Capsule &c, Vec2 dir);

Vec2 support(const Circle &a, const Circle &b, Vec2 dir);
Vec2 support(const Circle &a, const Capsule &b, Vec2 dir);
Vec2 support(const Capsule &a, const Circle &b, Vec2 dir);
Vec2 support(const Capsule &a, const Capsule &b, Vec2 dir);
Vec2 support(const Mm_Rect &a, const Mm_Rect &b, Vec2 dir);

template <typename ShapeA, typename ShapeB>
inline Vec2 support(const ShapeA &a, const ShapeB &b, Vec2 dir) {
	return support(a, dir) - support(b, -dir);
}

template <typename ShapeA, typename ShapeB>
inline Vec2 support(const ShapeA &a, const ShapeB &b, Vec2 dir, Vec2 dp) {
	Vec2 s = support(a, b, dir);
	if (vec2_dot(dp, dir) <= 0.0f)
		s -= dp;
	return s;
}

template <typename ShapeA, typename ShapeB>
inline Vec2 support(const ShapeA &a, const ShapeB &b, Vec2 dir, const Mat3 &ta, const Mat3 &tb, const Mat2 &tdira, const Mat2 &tdirb) {
	Vec2 p = support(a, mat2_vec2_mul(tdira, dir));
	p = mat3_vec2_mul(ta, p);

	Vec2 q = support(b, mat2_vec2_mul(tdirb, -dir));
	q = mat3_vec2_mul(tb, q);

	return p - q;
}

template <typename ShapeA, typename ShapeB>
inline Vec2 support(const ShapeA &a, const ShapeB &b, Vec2 dir, const Mat3 &ta, const Mat3 &tb, const Mat2 &tdira, const Mat2 &tdirb, Vec2 dp) {
	Vec2 s = support(a, b, dir, ta, tb, tdira, tdirb);
	if (vec2_dot(dp, dir) <= 0.0f)
		s -= dp;
	return s;
}

bool next_simplex(Vec2 *simplex, Vec2 *dir, u32 *n);

Nearest_Edge2d closest_edge_origin_polygon(const Polygon &polygon);

template <typename ShapeA, typename ShapeB, typename ...Args>
bool gjk(const ShapeA &sa, const ShapeB &sb, const Args & ...args) {
	Vec2 simplex[3];

	Vec2 dir = vec2(0, 1);
	simplex[0] = support(sa, sb, dir, args...);
	dir = -simplex[0];
	u32 n = 1;

	Vec2 a;
	while (true) {
		a = support(sa, sb, dir, args...);
		if (vec2_dot(a, dir) < 0.0f) return false; // no intersection
		simplex[n] = a;
		n += 1;

		if (next_simplex(simplex, &dir, &n)) {
			return true;
		}
	}

	return false;
}

constexpr r32 EPA_TOLERANCE = 0.00001f;

template <typename ShapeA, typename ShapeB, typename ...Args>
bool gjk_epa(const ShapeA &sa, const ShapeB &sb, Vec2 *normal, r32 *penetration_depth, const Args &...args) {
	u32 allocated = 8;
	Polygon *simplex = (Polygon *)tallocate(sizeof(Polygon) + sizeof(Vec2) * (allocated - 3));
	simplex->vertex_count = 1;

	Vec2 dir = vec2(0, 1);
	simplex->vertices[0] = support(sa, sb, dir, args...);
	dir = -simplex->vertices[0];

	bool collision = false;

	Vec2 a;
	while (true) {
		if (vec2_null(dir)) return false;
		a = support(sa, sb, dir, args...);
		if (vec2_dot(a, dir) < 0.0f) return false; // no intersection
		simplex->vertices[simplex->vertex_count] = a;
		simplex->vertex_count += 1;

		if (next_simplex(simplex->vertices, &dir, &simplex->vertex_count)) {
			collision = true;
			break;
		}
	}

	if (!collision) return false;

	while (true) {
		Nearest_Edge2d e = closest_edge_origin_polygon(*simplex);
		if (vec2_null(e.normal)) return false;

		Vec2 p = support(sa, sb, e.normal, args...);

		r32 d = vec2_dot(p, e.normal);
		if (d - e.distance < EPA_TOLERANCE) {
			*normal = e.normal;
			*penetration_depth = d;
			break;
		} else {
			if (simplex->vertex_count == allocated) {
				allocated *= 2;
				simplex = (Polygon *)treallocate(simplex, sizeof(Polygon) + sizeof(Vec2) * (allocated - 3));
			}

			memmove(simplex->vertices + e.index + 1, simplex->vertices + e.index, sizeof(Vec2) * (simplex->vertex_count - e.index));
			simplex->vertices[e.index] = p;
			simplex->vertex_count += 1;
		}
	}

	return true;
}
