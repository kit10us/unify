// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#include <unify/Frustum.h>

using namespace unify;

bool unify::EdgeIntersectsFace( unify::V3< float > * pEdges, unify::V3< float > * pFacePoints, unify::Plane * pPlane )
{
    // If both edge points are on the same side of the plane, the edge does
    // not intersect the face
    float fDist1;
    float fDist2;
    fDist1 = pPlane->a * pEdges[0].x + pPlane->b * pEdges[0].y +
             pPlane->c * pEdges[0].z + pPlane->d;
    fDist2 = pPlane->a * pEdges[1].x + pPlane->b * pEdges[1].y +
             pPlane->c * pEdges[1].z + pPlane->d;
    if( fDist1 > 0 && fDist2 > 0 ||
        fDist1 < 0 && fDist2 < 0 )
    {
        return false;
    }

    // Find point of intersection between edge and face plane (if they're
    // parallel, edge does not intersect face and D3DXPlaneIntersectLine 
    // returns NULL)
    unify::V3< float > ptIntersection;
	if( ! pPlane->IntersectLine( ptIntersection, pEdges[0], pEdges[1] ) )
	{
        return false;
	}

    // Project onto a 2D plane to make the pt-in-poly test easier
    float fAbsA = (pPlane->a > 0 ? pPlane->a : -pPlane->a);
    float fAbsB = (pPlane->b > 0 ? pPlane->b : -pPlane->b);
    float fAbsC = (pPlane->c > 0 ? pPlane->c : -pPlane->c);
    unify::V2< float > facePoints[4];
    unify::V2< float > point;
    if( fAbsA > fAbsB && fAbsA > fAbsC )
    {
        // Plane is mainly pointing along X axis, so use Y and Z
        for( int i = 0; i < 4; i++)
        {
            facePoints[i].x = pFacePoints[i].y;
            facePoints[i].y = pFacePoints[i].z;
        }
        point.x = ptIntersection.y;
        point.y = ptIntersection.z;
    }
    else if( fAbsB > fAbsA && fAbsB > fAbsC )
    {
        // Plane is mainly pointing along Y axis, so use X and Z
        for( int i = 0; i < 4; i++)
        {
            facePoints[i].x = pFacePoints[i].x;
            facePoints[i].y = pFacePoints[i].z;
        }
        point.x = ptIntersection.x;
        point.y = ptIntersection.z;
    }
    else
    {
        // Plane is mainly pointing along Z axis, so use X and Y
        for( int i = 0; i < 4; i++)
        {
            facePoints[i].x = pFacePoints[i].x;
            facePoints[i].y = pFacePoints[i].y;
        }
        point.x = ptIntersection.x;
        point.y = ptIntersection.y;
    }

    // If point is on the outside of any of the face edges, it is
    // outside the face.  
    // We can do this by taking the determinant of the following matrix:
    // | x0 y0 1 |
    // | x1 y1 1 |
    // | x2 y2 1 |
    // where (x0,y0) and (x1,y1) are points on the face edge and (x2,y2) 
    // is our test point.  If this value is positive, the test point is
    // "to the left" of the line.  To determine whether a point needs to
    // be "to the right" or "to the left" of the four lines to qualify as
    // inside the face, we need to see if the faces are specified in 
    // clockwise or counter-clockwise order (it could be either, since the
    // edge could be penetrating from either side).  To determine this, we
    // do the same test to see if the third point is "to the right" or 
    // "to the left" of the line formed by the first two points.
    // See http://forum.swarthmore.edu/dr.math/problems/scott5.31.96.html
    float x0, x1, x2, y0, y1, y2;
    x0 = facePoints[0].x;
    y0 = facePoints[0].y;
    x1 = facePoints[1].x;
    y1 = facePoints[1].y;
    x2 = facePoints[2].x;
    y2 = facePoints[2].y;
    bool bClockwise = false;
    if( x1*y2 - y1*x2 - x0*y2 + y0*x2 + x0*y1 - y0*x1 < 0 )
	{
        bClockwise = true;
	}
    x2 = point.x;
    y2 = point.y;
    for( int i = 0; i < 4; i++ )
    {
        x0 = facePoints[i].x;
        y0 = facePoints[i].y;
        
		if( i < 3 )
        {
            x1 = facePoints[i+1].x;
            y1 = facePoints[i+1].y;
        }
        else
        {
            x1 = facePoints[0].x;
            y1 = facePoints[0].y;
        }

        if( ( x1*y2 - y1*x2 - x0*y2 + y0*x2 + x0*y1 - y0*x1 > 0 ) == bClockwise )
		{
            return false;
		}
    }

    // If we get here, the point is inside all four face edges, 
    // so it's inside the face.
    return true;
}


Frustum::Frustum()
{
}

Frustum::Frustum( const unify::Matrix & worldViewProjection )
{
    Calculate( worldViewProjection );
}

void Frustum::Calculate( const unify::Matrix & worldViewProjection )
{
    m_worldViewProjection = worldViewProjection;
	unify::Matrix result = worldViewProjection;
	result.Invert();

	m_vCorner[CORNER_xyz] = unify::V3< float >(-1.0f, -1.0f,  0.0f);
	m_vCorner[CORNER_Xyz] = unify::V3< float >( 1.0f, -1.0f,  0.0f);
	m_vCorner[CORNER_xYz] = unify::V3< float >(-1.0f,  1.0f,  0.0f);
	m_vCorner[CORNER_XYz] = unify::V3< float >( 1.0f,  1.0f,  0.0f);
	m_vCorner[CORNER_xyZ] = unify::V3< float >(-1.0f, -1.0f,  1.0f);
	m_vCorner[CORNER_XyZ] = unify::V3< float >( 1.0f, -1.0f,  1.0f);
	m_vCorner[CORNER_xYZ] = unify::V3< float >(-1.0f,  1.0f,  1.0f);
	m_vCorner[CORNER_XYZ] = unify::V3< float >( 1.0f,  1.0f,  1.0f);

	int i;
	for( i = 0; i < 8; i++ )
	{
		m_vCorner[i] = result.TransformCoord( m_vCorner[i] );
	}

	m_Plane[PLANE_NEAR] = unify::Plane::PlaneFromPoints( m_vCorner[ CORNER_xyz ], m_vCorner[ CORNER_Xyz ], m_vCorner[ CORNER_xYz ] );
	m_Plane[PLANE_FAR] = unify::Plane::PlaneFromPoints( m_vCorner[ CORNER_xYZ ], m_vCorner[ CORNER_XYZ ], m_vCorner[ CORNER_XyZ ] );
	m_Plane[PLANE_LEFT] = unify::Plane::PlaneFromPoints( m_vCorner[ CORNER_xYz ], m_vCorner[ CORNER_xYZ ], m_vCorner[ CORNER_xyZ ] );
	m_Plane[PLANE_RIGHT] = unify::Plane::PlaneFromPoints( m_vCorner[ CORNER_XYZ ], m_vCorner[ CORNER_XYz ], m_vCorner[ CORNER_XyZ ] );
	m_Plane[PLANE_TOP] = unify::Plane::PlaneFromPoints( m_vCorner[ CORNER_xYz ], m_vCorner[ CORNER_XYz ], m_vCorner[ CORNER_xYZ ] );
	m_Plane[PLANE_BOTTOM] = unify::Plane::PlaneFromPoints( m_vCorner[ CORNER_Xyz ], m_vCorner[ CORNER_xyz ], m_vCorner[ CORNER_xyZ ] );
}

bool Frustum::CastPoint( const unify::V2< float > & unit, unify::Ray & rayOut )
{
    if ( unit.x < 0 || unit.y < 0 || unit.x > 1.0f || unit.y > 1.0f )
    {
        return false;
    }

    unify::V3< float > vNear1 = unify::V3< float >::V3Lerp( m_vCorner[ CORNER_xYz ], m_vCorner[ CORNER_XYz ], unit.x );
    unify::V3< float > vNear2 = unify::V3< float >::V3Lerp( m_vCorner[ CORNER_xyz ], m_vCorner[ CORNER_Xyz ], unit.x );
    unify::V3< float > vNear = unify::V3< float >::V3Lerp( vNear1, vNear2, unit.y );

    unify::V3< float > vFar1 = unify::V3< float >::V3Lerp( m_vCorner[ CORNER_xYZ ], m_vCorner[ CORNER_XYZ ], unit.x );
    unify::V3< float > vFar2 = unify::V3< float >::V3Lerp( m_vCorner[ CORNER_xyZ ], m_vCorner[ CORNER_XyZ ], unit.x );
    unify::V3< float > vFar = unify::V3< float >::V3Lerp( vFar1, vFar2, unit.y );

    rayOut.origin = vNear;
    rayOut.direction = vFar - vNear;
    rayOut.direction.Normalize();

    return true;
}

CULLSTATE Frustum::CullBBox( unify::BBox< float > * pBBox/*, unify::Plane * BBPlane*/ )
{
	unsigned char outside[8];
	memset( &outside, 0, sizeof( outside ) );

	unify::V3< float > vBounds[8];
	pBBox->GenerateCorners( &vBounds[0] );
	
	unify::Plane BBPlane[6];

	BBPlane[0] = unify::Plane::PlaneFromPoints( vBounds[0], vBounds[1], vBounds[2] ); // Near
	BBPlane[1] = unify::Plane::PlaneFromPoints( vBounds[6], vBounds[7], vBounds[5] ); // Far
	BBPlane[2] = unify::Plane::PlaneFromPoints( vBounds[2], vBounds[6], vBounds[4] ); // Left
	BBPlane[3] = unify::Plane::PlaneFromPoints( vBounds[7], vBounds[3], vBounds[5] ); // Right
	BBPlane[4] = unify::Plane::PlaneFromPoints( vBounds[2], vBounds[3], vBounds[6] ); // Top
	BBPlane[5] = unify::Plane::PlaneFromPoints( vBounds[1], vBounds[0], vBounds[4] ); // Bottom

	// Check boundary vertices against all 6 frustum planes, 
	// and store result (1 if outside) in a bitfield
	for( int iPoint = 0; iPoint < 8; iPoint++ )
	{
		for( int iPlane = 0; iPlane < 6; iPlane++ )
		{
			if( m_Plane[iPlane].a * vBounds[iPoint].x +
				m_Plane[iPlane].b * vBounds[iPoint].y +
				m_Plane[iPlane].c * vBounds[iPoint].z +
				m_Plane[iPlane].d < 0)
			{
				// TODO: Figure this out.
				outside[iPoint] |= (1 << iPlane);
			}
		}
		// If any point is inside all 6 frustum planes, it is inside
		// the frustum, so the object must be rendered.
		if( outside[iPoint] == 0 )
		{
			return CS_INSIDE;
		}
	}

	// If all points are outside any single frustum plane, the object is
	// outside the frustum
	if( (outside[0] & outside[1] & outside[2] & outside[3] & outside[4] & outside[5] & outside[6] & outside[7]) != 0 )
	{
		return CS_OUTSIDE;
	}

	// Now see if any of the frustum edges penetrate any of the faces of
	// the bounding box
	unify::V3< float > edge[12][2] = 
	{
		m_vCorner[0], m_vCorner[1], // front bottom
		m_vCorner[2], m_vCorner[3], // front top
		m_vCorner[0], m_vCorner[2], // front left
		m_vCorner[1], m_vCorner[3], // front right
		m_vCorner[4], m_vCorner[5], // back bottom
		m_vCorner[6], m_vCorner[7], // back top
		m_vCorner[4], m_vCorner[6], // back left
		m_vCorner[5], m_vCorner[7], // back right
		m_vCorner[0], m_vCorner[4], // left bottom
		m_vCorner[2], m_vCorner[6], // left top
		m_vCorner[1], m_vCorner[5], // right bottom
		m_vCorner[3], m_vCorner[7], // right top
	};
	unify::V3< float > face[6][4] =
	{
		vBounds[0], vBounds[2], vBounds[3], vBounds[1], // front
		vBounds[4], vBounds[5], vBounds[7], vBounds[6], // back
		vBounds[0], vBounds[4], vBounds[6], vBounds[2], // left
		vBounds[1], vBounds[3], vBounds[7], vBounds[5], // right
		vBounds[2], vBounds[6], vBounds[7], vBounds[3], // top
		vBounds[0], vBounds[4], vBounds[5], vBounds[1], // bottom
	};
	unify::V3< float > * pEdge;
	unify::V3< float > * pFace;
	pEdge = &edge[0][0];
	for( int iEdge = 0; iEdge < 12; iEdge++ )
	{
		pFace = &face[0][0];
		for( int iFace = 0; iFace < 6; iFace++ )
		{
			if( EdgeIntersectsFace( pEdge, pFace, &BBPlane[iFace] ) )
			{
				return CS_INSIDE_SLOW;
			}
			pFace += 4;
		}
		pEdge += 2;
	}

	// Now see if any of the bounding box edges penetrate any of the faces of
	// the frustum
	unify::V3< float > edge2[12][2] = 
	{
		vBounds[0], vBounds[1], // front bottom
		vBounds[2], vBounds[3], // front top
		vBounds[0], vBounds[2], // front left
		vBounds[1], vBounds[3], // front right
		vBounds[4], vBounds[5], // back bottom
		vBounds[6], vBounds[7], // back top
		vBounds[4], vBounds[6], // back left
		vBounds[5], vBounds[7], // back right
		vBounds[0], vBounds[4], // left bottom
		vBounds[2], vBounds[6], // left top
		vBounds[1], vBounds[5], // right bottom
		vBounds[3], vBounds[7], // right top
	};
	unify::V3< float > face2[6][4] =
	{
		m_vCorner[0], m_vCorner[2], m_vCorner[3], m_vCorner[1], // front
		m_vCorner[4], m_vCorner[5], m_vCorner[7], m_vCorner[6], // back
		m_vCorner[0], m_vCorner[4], m_vCorner[6], m_vCorner[2], // left
		m_vCorner[1], m_vCorner[3], m_vCorner[7], m_vCorner[5], // right
		m_vCorner[2], m_vCorner[6], m_vCorner[7], m_vCorner[3], // top
		m_vCorner[0], m_vCorner[4], m_vCorner[5], m_vCorner[1], // bottom
	};
	pEdge = &edge2[0][0];
	for( int iEdge = 0; iEdge < 12; iEdge++ )
	{
		pFace = &face2[0][0];
		for( int iFace = 0; iFace < 6; iFace++ )
		{
			if( EdgeIntersectsFace( pEdge, pFace, &m_Plane[iFace] ) )
			{
				return CS_INSIDE_SLOW;
			}
			pFace += 4;
		}
		pEdge += 2;
	}

	// Now see if frustum is contained in bounding box
	// If any frustum corner point is outside any plane of the bounding box,
	// the frustum is not contained in the bounding box, so the object
	// is outside the frustum
	for( int iPlane = 0; iPlane < 6; iPlane++ )
	{
		if( BBPlane[iPlane].a * m_vCorner[0].x +
			BBPlane[iPlane].b * m_vCorner[0].y +
			BBPlane[iPlane].c * m_vCorner[0].z +
			BBPlane[iPlane].d  < 0 )
		{
			return CS_OUTSIDE_SLOW;
		}
	}

	// Bounding box must contain the frustum, so render the object
	return CS_INSIDE_SLOW;
}

