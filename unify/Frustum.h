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


#pragma once

#include <unify/Matrix.h>
#include <unify/Plane.h>
#include <unify/BBox.h>

namespace unify
{
	/// <summary>
	/// Enumeration of the corners of a frustum.
	/// </summary>
	class FrustumCorner
	{
	public:
		enum
		{

			xyz,
			Xyz,
			xYz,
			XYz,
			xyZ,
			XyZ,
			xYZ,
			XYZ,
			Count
		};
	};

	/// <summary>
	/// Enumeration of the planes of a frustum.
	/// </summary>
	class FrustumPlane
	{
	public:
		enum
		{
			Near,
			Far,
			Left,
			Right,
			Top,
			Bottom,
			Count
		};
	};

	enum class CullState
	{
		Unknown,		// Cull state not yet computed.
		Inside,			// Object bounding box is at least partly inside the frustum.
		Outside,		// Object bounding box is outside the frustum.
		InsideSlow,		// OBB is inside frustum, but it took extensive testing to determine this.
		OutsideSlow,	// OBB is outside frustum, but it took extensive testing to determine this.
	};

	/// <summary>
	/// A view frustum, typically used for view point occlusion.
	/// </summary>
	class Frustum
	{
	public:
		Frustum();
        Frustum( const unify::Matrix & worldViewProjection );

		/// <summary>
		/// Calcuate frustum from a WVM projection matrix.
		/// </summary>
		void Calculate( const unify::Matrix & worldViewProjection );

        /// <summary>
		/// Casts a unit point from across the frustum to a position at the front of the frustom, 
		/// and a direction along the frustum. Returns false if unit components are not in the range [ 0, 1 ].
		/// </summary>
        bool CastPoint( const unify::V2< float > & unit, unify::Ray & rayOut );

		/// <summary>
		/// Determine the culling characteristics of a bounding blox.
		/// </summary>
		CullState CullBBox( unify::BBox< float > * pBBox/*, unify::Plane * BBPlane*/ );

	protected:
        unify::Matrix m_worldViewProjection;
		unify::V3< float > m_vCorner[ FrustumCorner::Count ];
		unify::Plane m_Plane[ FrustumPlane::Count ];
	};

	bool EdgeIntersectsFace( unify::V3< float > * pEdges, unify::V3< float > * pFacePoints, unify::Plane * pPlane );
}