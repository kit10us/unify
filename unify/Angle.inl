/*
 * Unify Library
 * https://github.com/kit10us/unify
 * Copyright (c) 2002, Kit10 Studios LLC
 *
 * This file is part of Unify Library (a.k.a. Unify)
 *
 * Unify is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Unify is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Unify.  If not, see <https://www.gnu.org/licenses/>.
 */


namespace unify
{
	inline
	Angle AngleInRadians(float radians)
	{
		return Angle(radians);
	}

	inline
	Angle AngleInDegrees(float degrees)
	{
		return Angle(degrees * DTOR);
	}

	inline
	Angle AnglePI()
	{
		return AngleInRadians(PI);
	}

	inline
	Angle AnglePI2()
	{
		return AngleInRadians(TAU);
	}

	inline
	Angle AnglePIHalf()
	{
		return AngleInRadians(HALF_PI);
	}

	inline
	Angle::Angle()
		: Angle(0.0f)
	{
	}

	inline
	Angle::Angle(float radians)
		: m_radians(radians)
	{
	}

	inline
	Angle::Angle(const std::string_view angle)
		: m_radians{}
	{
		if (angle.length() < 2)
		{
			return;
		}

		const auto start = angle.data();
		const auto end = start + (angle.length() - 1);
		auto last = angle.back();

		float value{};
		auto [ptr, ec] = std::from_chars(start, end, value);

		if (ec == std::errc())
		{
			if (last == 'd' || last == 'D')
			{
				m_radians = value * DTOR;
			}
			else if (last == 'r' || last == 'R')
			{
				m_radians = value;
			}
		}
	}

	inline
	Angle::Angle(const Angle& angle)
		: Angle{ angle.m_radians }
	{
	}

	inline
	Angle& Angle::operator = (const Angle& angle)
	{
		m_radians = angle.m_radians;
		return *this;
	}

	inline
	Angle& Angle::operator += (const Angle& angle)
	{
		m_radians += angle.m_radians;
		return *this;
	}

	inline
	Angle& Angle::operator -= (const Angle& angle)
	{
		m_radians -= angle.m_radians;
		return *this;
	}

	inline
	Angle& Angle::operator *= (const Angle& angle)
	{
		m_radians *= angle.m_radians;
		return *this;
	}

	inline
	Angle& Angle::operator /= (const Angle& angle)
	{
		m_radians /= angle.m_radians;
		return *this;
	}

	inline
	Angle Angle::operator + (const Angle& angle) const
	{
		Angle returnAngle(*this);
		returnAngle += angle;
		return returnAngle;
	}

	inline
	Angle Angle::operator - (const Angle& angle) const
	{
		Angle returnAngle(*this);
		returnAngle -= angle;
		return returnAngle;
	}

	inline
	Angle Angle::operator * (const Angle& angle) const
	{
		Angle returnAngle(*this);
		returnAngle *= angle;
		return returnAngle;
	}

	inline
	Angle Angle::operator / (const Angle& angle) const
	{
		Angle returnAngle(*this);
		returnAngle /= angle;
		return returnAngle;
	}

	inline
	bool Angle::operator == (const Angle& angle) const
	{
		return m_radians == angle.m_radians;
	}

	inline
	bool Angle::operator != (const Angle& angle) const
	{
		return !(*this == angle);
	}

	inline
	Angle& Angle::operator *= (float scalar)
	{
		m_radians *= scalar;
		return *this;
	}

	inline
	Angle& Angle::operator /= (float scalar)
	{
		m_radians /= scalar;
		return *this;
	}

	inline
	Angle Angle::operator * (float scalar) const
	{
		Angle returnAngle(*this);
		returnAngle.m_radians *= scalar;
		return returnAngle;
	}

	inline
	Angle Angle::operator / (float scalar) const
	{
		Angle returnAngle(*this);
		returnAngle.m_radians /= scalar;
		return returnAngle;
	}

	inline
	bool Angle::operator > (const Angle& angle)
	{
		return m_radians > angle.m_radians;
	}

	inline
	bool Angle::operator >= (const Angle& angle)
	{
		return m_radians >= angle.m_radians;
	}

	inline
	bool Angle::operator < (const Angle& angle)
	{
		return m_radians < angle.m_radians;
	}

	inline
	bool Angle::operator <= (const Angle& angle)
	{
		return m_radians <= angle.m_radians;
	}

	inline
	float Angle::ToRadians() const
	{
		return m_radians;
	}

	inline
	float Angle::ToDegrees() const
	{
		return m_radians * RTOD;
	}

	inline
	int Angle::Normalize()
	{
		int magnitude = 0;
		while (m_radians > TAU)
		{
			m_radians -= TAU;
			magnitude -= 1;
		}
		while (m_radians < 0)
		{
			m_radians += TAU;
			magnitude += 1;
		}
		return magnitude;
	}

	inline
	float Angle::SinOf() const
	{
		return (float)sin(m_radians);
	}

	inline
	float Angle::CosOf() const
	{
		return (float)cos(m_radians);
	}

	inline
	std::string Angle::ToString(bool radians) const
	{
		std::string out;
		if (radians)
		{
			out = unify::Cast< std::string >(ToRadians());
			out.push_back('r');
		}
		else
		{
			out = unify::Cast< std::string >(ToDegrees());
			out.push_back('d');
		}
		return out;
	}

}
