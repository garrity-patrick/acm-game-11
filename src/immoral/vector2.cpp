#include "immoral/vector2.hpp"
#include "immoral/float.hpp"
#include <cmath>

namespace immoral
{
	vector2::vector2(void)
	{
		m_xy[0] = 0.0f;
		m_xy[1] = 0.0f;
	}
	
	vector2::vector2(const vector2 & other)
	{
		m_xy[0] = other.m_xy[0];
		m_xy[1] = other.m_xy[1];
	}
	
	vector2::vector2(float x, float y)
	{
		m_xy[0] = x;
		m_xy[1] = y;
	}
	
	vector2::~vector2(void)
	{
	}
	
	vector2 & vector2::operator=(const vector2 & other)
	{
		if (this != &other)
		{
			m_xy[0] = other.m_xy[0];
			m_xy[1] = other.m_xy[1];
		}
	}
	
	bool vector2::operator==(const vector2 & v) const
	{
		return feq(m_xy[0], v.m_xy[0]) && feq(m_xy[1], v.m_xy[1]);
	}
	
	bool vector2::operator!=(const vector2 & v) const
	{
		return fneq(m_xy[0], v.m_xy[0]) && fneq(m_xy[1], v.m_xy[1]);
	}
	
	vector2 vector2::operator+(const vector2 & v) const
	{
		vector2 u(*this);
		u.m_xy[0] += v.m_xy[0];
		u.m_xy[1] += v.m_xy[1];
		return u;
	}
	
	vector2 vector2::operator-(const vector2 & v) const
	{
		vector2 u(*this);
		u.m_xy[0] -= v.m_xy[0];
		u.m_xy[1] -= v.m_xy[1];
		return u;
	}
	
	vector2 vector2::operator*(float scalar) const
	{
		vector2 u(*this);
		u.m_xy[0] *= scalar;
		u.m_xy[1] *= scalar;
		return u;
	}
	
	float vector2::operator*(const vector2 & v) const
	{
		return (m_xy[0] * v.m_xy[0]) + (m_xy[1] * v.m_xy[1]);
	}
	
	vector2 & vector2::operator+=(const vector2 & v)
	{
		m_xy[0] += v.m_xy[0];
		m_xy[1] += v.m_xy[1];
		return *this;
	}
	
	vector2 & vector2::operator-=(const vector2 & v)
	{
		m_xy[0] -= v.m_xy[0];
		m_xy[1] -= v.m_xy[1];
		return *this;
	}
	
	vector2 & vector2::operator*(float scalar)
	{
		m_xy[0] *= scalar;
		m_xy[1] *= scalar;
		return *this;
	}
	
	void vector2::add(const vector2 & v)
	{
		m_xy[0] += v.m_xy[0];
		m_xy[1] += v.m_xy[1];
	}
	
	void vector2::subtract(const vector2 & v)
	{
		m_xy[0] -= v.m_xy[0];
		m_xy[1] -= v.m_xy[1];
	}
	
	void vector2::scale(float scalar)
	{
		m_xy[0] *= scalar;
		m_xy[1] *= scalar;
	}
	
	float vector2::dot(const vector2 & v)
	{
		return (m_xy[0] * v.m_xy[0]) + (m_xy[1] * v.m_xy[1]);
	}
	
	float vector2::mag(void) const
	{
		return sqrt(mag2);
	}
	
	float vector2::mag2(void) const
	{
		return (m_xy[0] * m_xy[0]) + (m_xy[1] * m_xy[1]);
	}
	
	float vector2::distance(const vector2 & v) const
	{
		return sqrt(distance2(v));
	}
	
	float vector2::distance2(const vector2 & v) const
	{
		return ((v.m_xy[0] - m_xy[0]) * (v.m_xy[0] - m_xy[0]))
			+  ((v.m_xy[1] - m_xy[1]) * (v.m_xy[1] - m_xy[1]));
	}
	
	void vector2::normalize(void)
	{
		float m = mag();
		if (fneq(0.0f, m)) { m_xy[0] /= m; m_xy[1] /= m; }
	}
	
	vector2 vector2::normal(void) const
	{
		vector2 u(*this);
		u.normalize();
		return u;
	}
}
