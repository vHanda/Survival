/*
* Copyright (c) 2006-2007 Erin Catto http://www.gphysics.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef POLY_AND_EDGE_CONTACT_H
#define POLY_AND_EDGE_CONTACT_H

#include "Dynamics/Contacts/b2Contact.h"

class b2BlockAllocator;

class b2PolyAndEdgeContact : public b2Contact
{
public:
	static b2Contact* Create(b2Shape* shape1, b2Shape* shape2, b2BlockAllocator* allocator);
	static void Destroy(b2Contact* contact, b2BlockAllocator* allocator);

	b2PolyAndEdgeContact(b2Shape* shape1, b2Shape* shape2);
	~b2PolyAndEdgeContact() {}

	void Evaluate(b2ContactListener* listener);
	void b2CollidePolyAndEdge(b2Manifold* manifold,
									const b2PolygonShape* poly, const b2XForm& xf1,
									const b2EdgeShape* edge, const b2XForm& xf2);
	b2Manifold* GetManifolds()
	{
		return &m_manifold;
	}

	b2Manifold m_manifold;
};

#endif
