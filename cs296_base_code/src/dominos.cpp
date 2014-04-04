/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
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

/*
 * Base code for CS 296 Software Systems Lab
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */


#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
  /**  The is the constructor
   * This is the documentation block for the constructor.
   */

  dominos_t::dominos_t()
  {
    //Ground
   /*! \par Making Ground
	 * variable b1 :: <br>
	 * Data Type is b2Body* <br>
	 * pointer to the ground <br>
	 * variable shape :: <br>
	 * Data Type is b2EdgeShape <br>
	 * Its left value is (-90,0) and right value is (90,0) <br>
	 * variable bd :: <br>
	 * Data Type is b2BodyDef <br>
	 * CreateBody is used for Creating Bodies in the Physical world <br>
	 * CreateFixture is used for fixing body in its parent <br>
	 */
    b2Body* b1;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
      b2FixtureDef groundfd;
      groundfd.shape = &shape;
      groundfd.friction = 1.0f;
      groundfd.restitution = 0.6f;
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&groundfd);
    }

    //Top horizontal shelf
    /*! \par Top Horizontal Shelf
     * variable shape :: <br>
     * Data Type is b2PolygonShape <br>
     * length : 6 , width : 0.25 , Its Center coordinates are (-31,30) <br>
     * variable bd :: <br>
     * Data Type is b2BodyDef <br>
     * variable ground :: <br>
     * Data Type is b2Body* <br>
     */
    b2Body* ground;
    {
      b2PolygonShape shape;
      shape.SetAsBox(15.0f, 1.0f);

      b2BodyDef bd;
      bd.type = b2_dynamicBody;
      bd.position.Set(0.0f, 3.0f);
      ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    
    b2Body* spherebody;
    b2Body* spherebody2;
    b2Body* spherebody3;
    {
      b2CircleShape circle;
      circle.m_radius = 3;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.5f;
      ballfd.restitution = 0.6f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(-15, 3.0f);
      spherebody = m_world->CreateBody(&ballbd);
      spherebody->CreateFixture(&ballfd);
      ballbd.position.Set(15, 3.0f);
      spherebody2 = m_world->CreateBody(&ballbd);
      spherebody2->CreateFixture(&ballfd);
      ballbd.position.Set(18, 50.0f);
      ballfd.density = 10.0f;
      spherebody3 = m_world->CreateBody(&ballbd);
      spherebody3->CreateFixture(&ballfd);
	}
	{
		b2RevoluteJointDef jointDef;
		b2Vec2 anchor;
		anchor.Set(-15,3);
		jointDef.Initialize(ground,spherebody,anchor);
		m_world->CreateJoint(&jointDef);
		b2RevoluteJointDef jointDef2;
		b2Vec2 anchor2;
		anchor2.Set(15,3);
		jointDef2.Initialize(ground,spherebody2,anchor2);
		m_world->CreateJoint(&jointDef2);
	}
	
	b2Body* perpen;
    {
      b2PolygonShape shape;
      shape.SetAsBox(1.5f, 8.5f);

      b2BodyDef bd;
      bd.type = b2_dynamicBody;
      bd.position.Set(0.0f, 12.5f);
      perpen = m_world->CreateBody(&bd);
      perpen->CreateFixture(&shape, 0.0f);
    }
	
	{
		b2RevoluteJointDef jointDef;
		b2Vec2 anchor;
		anchor.Set(0,4);
		jointDef.Initialize(ground,perpen,anchor);
		m_world->CreateJoint(&jointDef);
	}
	
	b2Body* trapfir;
    {
		
		b2Vec2 vertices[4];
		vertices[0].Set(9.0f, 0.0f);
		vertices[1].Set(11.5f, 0.0f);
		vertices[2].Set(0.0f, 9.0f);
		vertices[3].Set(0.0f, 11.5f);
		int32 count = 4;
		b2PolygonShape polygon;
		polygon.Set(vertices, count);
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position.Set(1.5f, 4.0f);
		trapfir = m_world->CreateBody(&bd);
		trapfir->CreateFixture(&polygon, 0.0f);
    }
    
    {
		b2RevoluteJointDef jointDef;
		b2Vec2 anchor;
		anchor.Set(11.75,4);
		jointDef.Initialize(ground,trapfir,anchor);
		m_world->CreateJoint(&jointDef);
	}
	
    b2Body* trapsec;
    {
		
		b2Vec2 vertices[4];
		vertices[0].Set(-9.0f, 0.0f);
		vertices[1].Set(-11.5f, 0.0f);
		vertices[2].Set(0.0f, 9.0f);
		vertices[3].Set(0.0f, 11.5f);
		int32 count = 4;
		b2PolygonShape polygon;
		polygon.Set(vertices, count);
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position.Set(-1.5f, 4.0f);
		trapsec = m_world->CreateBody(&bd);
		trapsec->CreateFixture(&polygon, 0.0f);
    }
    
    {
		b2RevoluteJointDef jointDef;
		b2Vec2 anchor;
		anchor.Set(-11.75,4);
		jointDef.Initialize(ground,trapsec,anchor);
		m_world->CreateJoint(&jointDef);
	}
	
	b2Body* top1;
	{
		b2PolygonShape shape;
		shape.SetAsBox(10.0f, 1.0f);
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position.Set(-10.0f, 18.0f);
		top1 = m_world->CreateBody(&bd);
		b2FixtureDef ballfd;
		ballfd.shape=&shape;
		ballfd.density=1.0f;
		ballfd.filter.groupIndex=-1;
		top1->CreateFixture(&ballfd);
	}
	
	b2Body* top2;
	{
		b2PolygonShape shape;
		shape.SetAsBox(4.0f, 2.0f);
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position.Set(4.0f, 18.0f);
		top2 = m_world->CreateBody(&bd);
		b2FixtureDef ballfd;
		ballfd.shape=&shape;
		ballfd.density=1.0f;
		ballfd.filter.groupIndex=-1;
		top2->CreateFixture(&ballfd);
	}
	
	{
		b2RevoluteJointDef jointDef;
		b2Vec2 anchor;
		anchor.Set(0,18);
		jointDef.Initialize(perpen,top1,anchor);
		jointDef.collideConnected=false;
		m_world->CreateJoint(&jointDef);
		
		jointDef.Initialize(perpen,top2,anchor);
		jointDef.collideConnected=false;
		m_world->CreateJoint(&jointDef);
		
		b2WeldJointDef weldDef;
		weldDef.Initialize(top1,top2,anchor);
		m_world->CreateJoint(&weldDef);
	}
	
	b2Body* circleontop;
	{
		b2CircleShape circle;
		circle.m_radius = 1;
		b2FixtureDef ballfd;
		ballfd.shape = &circle;
		ballfd.density = 1.0f;
		ballfd.friction = 0.5f;
		ballfd.restitution = 0.6f;
		b2BodyDef ballbd;
		ballbd.type = b2_dynamicBody;
		ballbd.position.Set(6, 18.0f);
		circleontop = m_world->CreateBody(&ballbd);
		circleontop->CreateFixture(&ballfd);
	}
	
	{
		b2WeldJointDef jointDef;
		b2Vec2 anchor;
		anchor.Set(6,18);
		jointDef.Initialize(top2,circleontop,anchor);
		m_world->CreateJoint(&jointDef);
	}
		
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
