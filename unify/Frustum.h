// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved
#pragma once

#include <unify/Matrix.h>
#include <unify/Plane.h>
#include <unify/BBox.h>

namespace unify
{
	enum FrustumCorner
	{
		CORNER_xyz,
		CORNER_Xyz,
		CORNER_xYz,
		CORNER_XYz,
		CORNER_xyZ,
		CORNER_XyZ,
		CORNER_xYZ,
		CORNER_XYZ,
		CORNER_COUNT
	};

	enum FrustumPlane
	{
		PLANE_NEAR,
		PLANE_FAR,
		PLANE_LEFT,
		PLANE_RIGHT,
		PLANE_TOP,
		PLANE_BOTTOM,
		PLANE_COUNT
	};

	enum CULLSTATE
	{
		CS_UNKNOWN,      // cull state not yet computed
		CS_INSIDE,       // object bounding box is at least partly inside the frustum
		CS_OUTSIDE,      // object bounding box is outside the frustum
		CS_INSIDE_SLOW,  // OBB is inside frustum, but it took extensive testing to determine this
		CS_OUTSIDE_SLOW, // OBB is outside frustum, but it took extensive testing to determine this
	};


	class Frustum
	{
	public:
		Frustum();
        Frustum( const unify::Matrix & worldViewProjection );

		void Calculate( const unify::Matrix & worldViewProjection );

        // Casts a unit point from across the frustum to a position at the front of the frustom, 
        // and a direction along the frustum. Returns false if unit components are not in the range [ 0, 1 ].
        bool CastPoint( const unify::V2< float > & unit, unify::Ray & rayOut );

		CULLSTATE CullBBox( unify::BBox< float > * pBBox/*, unify::Plane * BBPlane*/ );

	protected:
        unify::Matrix m_worldViewProjection;
		unify::V3< float > m_vCorner[ CORNER_COUNT ];
		unify::Plane m_Plane[ PLANE_COUNT ];
	};

	bool EdgeIntersectsFace( unify::V3< float > * pEdges, unify::V3< float > * pFacePoints, unify::Plane * pPlane );
}