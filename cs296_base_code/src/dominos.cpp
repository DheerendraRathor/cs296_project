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
#define PI 3.14159265
using namespace std;

#include "dominos.hpp"

namespace cs296
{
  /**  The is the constructor
   * This is the documentation block for the constructor.
   */
   	b2Body* circleontrap;
	b2Body* stopper;
	b2Body* heavybody;
	b2Body* trapsec;
   void dominos_t::keyboard(unsigned char key)
{
	if(key=='d'){	
		b2Vec2 pos;
		pos.Set(0.0,0.0);
		circleontrap->SetTransform(pos,circleontrap->GetAngle()-(10*PI/180));
	}
	else if(key=='m'){
		//m_world->DestroyBody(stopper);
		b2CircleShape circle;
		circle.m_radius = 0.5f;
		b2FixtureDef ballfd;
		ballfd.shape = &circle;
		ballfd.density = 0.01f;
		ballfd.friction = 1.0f;
		ballfd.restitution = 0.001f;
		b2BodyDef ballbd;
		b2Vec2 hello=circleontrap->GetPosition();
		b2Vec2 ancr;
		ancr.Set(hello.x+2.0f,hello.y+2.0f);
		ballbd.type = b2_dynamicBody;
		ballbd.position.Set(ancr.x,ancr.y);
		stopper = m_world->CreateBody(&ballbd);
		ballfd.filter.categoryBits = 0x02FF	;
		ballfd.filter.maskBits = 0x004F;
		stopper->CreateFixture(&ballfd);
		
		b2WeldJointDef jointDef;
		b2Vec2 anchor;
		anchor=stopper->GetPosition();
		jointDef.Initialize(trapsec,stopper,anchor);
		m_world->CreateJoint(&jointDef);
	}
	else if(key == 'l'){
		m_world->DestroyBody(stopper);
	}
	else if(key == 'i'){
		heavybody->ApplyLinearImpulse(b2Vec2(-2000,0),heavybody->GetWorldCenter(),true);
	}
}


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

      b2PolygonShape shape;
      shape.SetAsBox(90,90,b2Vec2(0.0f, -90.0f),0.0);
      b2FixtureDef groundfd;
      groundfd.shape = &shape;
      groundfd.friction = 1.0f;
      groundfd.restitution = 0.0f;
      groundfd.filter.categoryBits = 0x0004;
      groundfd.filter.maskBits = 0xFFFF;
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
      b2FixtureDef ballfd;
      ballfd.shape = &shape;
      ballfd.density = 0.0f;
      ballfd.filter.categoryBits = 0x0001;
      ballfd.filter.maskBits = 0x0004;
      ground->CreateFixture(&ballfd);
      
      
    }
    
    b2Body* spherebody;
    b2Body* spherebody2;
    b2Body* spherebody3;
    {
      b2CircleShape circle;
      circle.m_radius = 3;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 0.01f;
      ballfd.friction = 0.5f;
      ballfd.restitution = 0.01f;
      ballfd.filter.categoryBits = 0x0001;
      ballfd.filter.maskBits =0x0003 | 0x0004;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(-15, 3.0f);
      spherebody = m_world->CreateBody(&ballbd);
      spherebody->CreateFixture(&ballfd);
      ballbd.position.Set(15, 3.0f);
      spherebody2 = m_world->CreateBody(&ballbd);
      spherebody2->CreateFixture(&ballfd);
      ballbd.position.Set(30, 3.0f);
      ballfd.density = 1.0f;
      ballfd.friction = 0.5f;
      spherebody3 = m_world->CreateBody(&ballbd);
      ballfd.filter.categoryBits = 0x0004;
      ballfd.filter.maskBits = 0xFFFF;
      spherebody3->CreateFixture(&ballfd);
      spherebody3->ApplyLinearImpulse(b2Vec2(00,0) , spherebody->GetWorldCenter(),true);
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
      b2FixtureDef ballfd;
      ballfd.shape = &shape;
      ballfd.density = 0.0f;
      ballfd.filter.categoryBits = 0x0003;
      ballfd.filter.maskBits = 0x0004 | 0x0001 | 0x0002;
      perpen->CreateFixture(&ballfd);
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
		vertices[0].Set(7.0f, 0.0f);
		vertices[1].Set(9.5f, 0.0f);
		vertices[2].Set(0.0f, 9.5f);
		vertices[3].Set(0.0f, 7.0f);
		int32 count = 4;
		b2PolygonShape polygon;
		polygon.Set(vertices, count);
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position.Set(1.5f, 4.0f);
		trapfir = m_world->CreateBody(&bd);
		b2FixtureDef ballfd;
		ballfd.shape=&polygon;
		ballfd.density=0.0f;
		ballfd.filter.categoryBits = 0x0002;
		ballfd.filter.maskBits = 0x0004 | 0x0001 | 0x0003;
		trapfir->CreateFixture(&ballfd);
    }
    
    {
		b2RevoluteJointDef jDef;
		b2Vec2 anchor;
		anchor.Set(9.75,4);
		jDef.Initialize(ground,trapfir,anchor);
		jDef.collideConnected=true;
		m_world->CreateJoint(&jDef);
	}
	
    {
		
		b2Vec2 vertices[4];
		vertices[0].Set(-7.0f, 0.0f);
		vertices[1].Set(-9.5f, 0.0f);
		vertices[2].Set(0.0f, 9.5f);
		vertices[3].Set(0.0f, 7.0f);
		int32 count = 4;
		b2PolygonShape polygon;
		polygon.Set(vertices, count);
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position.Set(-1.5f, 4.0f);
		trapsec = m_world->CreateBody(&bd);
		b2FixtureDef ballfd;
		ballfd.shape=&polygon;
		ballfd.density=0.0f;
		ballfd.filter.groupIndex=-1;
		ballfd.filter.categoryBits = 0x0002;
		ballfd.filter.maskBits = 0x0004 | 0x0001 | 0x0003;
		trapsec->CreateFixture(&ballfd);
    }
    
    {
		b2RevoluteJointDef jointDef;
		b2Vec2 anchor;
		anchor.Set(-9.75,4);
		jointDef.Initialize(ground,trapsec,anchor);
		m_world->CreateJoint(&jointDef);
	}
	
	b2Body* top;
	{
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position.Set(0.0f, 18.0f);
		top = m_world->CreateBody(&bd);
		b2PolygonShape shape;
		shape.SetAsBox(10.0f, 0.75f ,b2Vec2(-10.0f,0.0f) , 0.0);
		b2FixtureDef ballfd;
		ballfd.shape=&shape;
		ballfd.density=0.5f;
		ballfd.restitution=0.01f;
		ballfd.filter.categoryBits = 0x0003;
		ballfd.filter.maskBits = 0x0004 | 0x0001 | 0x008F;
		top->CreateFixture(&ballfd);
		
		shape.SetAsBox(3.0f, 2.0f ,b2Vec2(-23.0f,0.0f) , 0.0);
		ballfd.shape=&shape;
		top->CreateFixture(&ballfd);
		
		shape.SetAsBox(5.0f, 1.5f ,b2Vec2(5.0f,0.0f) , 0.0);
		ballfd.shape=&shape;
		top->CreateFixture(&ballfd);
	}
	
	{
		b2RevoluteJointDef jointDef;
		b2Vec2 anchor;
		anchor.Set(0,18);
		jointDef.Initialize(perpen,top,anchor);
		jointDef.collideConnected=false;
		jointDef.referenceAngle = 0;
		jointDef.upperAngle = 0;
		m_world->CreateJoint(&jointDef);
	}
	
	b2Body* circleontop1;
	b2Body* circleontop2;
	{
		b2CircleShape circle;
		circle.m_radius = 0.8f;
		b2FixtureDef ballfd;
		ballfd.shape = &circle;
		ballfd.density = 0.01f;
		ballfd.friction = 100.0f;
		ballfd.restitution = 0.6f;
		b2BodyDef ballbd;
		b2Vec2 ancr;
		ancr.Set(9.0f,18);
		ballbd.type = b2_dynamicBody;
		ballbd.position.Set(ancr.x,ancr.y);
		circleontop1 = m_world->CreateBody(&ballbd);
		ballfd.filter.categoryBits = 0x0008;
		ballfd.filter.maskBits = 0x0004 | 0x0001 | 0x0002;
		circleontop1->CreateFixture(&ballfd);
		
		circle.m_radius = 1.65f;
		ancr.Set(-24.0f,18);
		ballbd.position.Set(ancr.x,ancr.y);
		circleontop2 = m_world->CreateBody(&ballbd);
		circleontop2->CreateFixture(&ballfd);
	}
	
	{
		b2RevoluteJointDef jointDef;
		b2Vec2 anchor;
		anchor.Set(9,18);
		jointDef.Initialize(top,circleontop1,anchor);
		m_world->CreateJoint(&jointDef);
		anchor.Set(-24,18);
		jointDef.Initialize(top,circleontop2,anchor);
		m_world->CreateJoint(&jointDef);
	}
	
	b2Body* box1;
	{
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position.Set(9.0f,13.5f);
		bd.fixedRotation = true;
		b2PolygonShape bs1,bs2,bs3;
		bs1.SetAsBox(3,0.2, b2Vec2(0.0f,-2.5f), 0);
		box1 = m_world->CreateBody(&bd);
		b2FixtureDef fd1;
		fd1.density = 0.001;
		fd1.friction = 0.5;
		fd1.restitution = 0.f;
		fd1.shape = &bs1;
		fd1.filter.categoryBits = 0x0FFF;
		fd1.filter.maskBits = 0x0003;
		bs2.SetAsBox(0.2,2.5, b2Vec2(-3.0f,0.0f), 0);
		b2FixtureDef fd2;
		fd2.density = 0.001;
		fd2.friction = 0.5;
		fd2.restitution = 0.f;
		fd2.shape = &bs2;
		fd2.filter.categoryBits = 0x0FFF;
		fd2.filter.maskBits = 0xFFFF & ~0x0001 & ~0x0002  & ~0x0004;
		bs3.SetAsBox(0.2,2.5, b2Vec2(3.0f,0.0f), 0);
		b2FixtureDef fd3;
		fd3.density = 0.001;
		fd3.friction = 0.5;
		fd3.restitution = 0.f;
		fd3.shape = &bs3;
		fd3.filter.categoryBits = 0x0FFF;
		fd3.filter.maskBits = 0xFFFF & ~0x0002;	
		box1->CreateFixture(&fd1);
		box1->CreateFixture(&fd2);
		box1->CreateFixture(&fd3);
		
		
		b2Vec2 vs[100];
		///chain body
		b2Body* conveyer[100];

		b2FixtureDef chainfd;
		chainfd.filter.categoryBits = 0x0004;
		chainfd.filter.maskBits = 0x0008;
		b2PolygonShape chainshape;
		float wid=0.25,heig=0.1;
		chainshape.SetAsBox(wid, heig);
		chainfd.shape = &chainshape;
		chainfd.density=0.01f;
		chainfd.friction=1000.0f;
		b2BodyDef chainDef;
		chainDef.type = b2_dynamicBody;
		//chainDef.gravityScale = 0.2f;

		///leftmost vertical
		chainshape.SetAsBox(heig, wid);
		 for (int i = 0; i < 6; ++i)
		{
		vs[i].Set(6.0f,16.0f+i*(2*wid));
		chainDef.position.Set(6.0f,16.25f+i*(2*wid));
		conveyer[i]=m_world->CreateBody(&chainDef);
		conveyer[i]->CreateFixture(&chainfd);
		}
		
		///Top horizontal
		chainshape.SetAsBox(wid, heig);
		 for (int i = 0; i < 12; ++i)
		{
		vs[i+6].Set(6.f+(2*wid)*i,19.1f);
		chainDef.position.Set(6.25f+(2*wid)*i,19.1f);
		conveyer[i+6]=m_world->CreateBody(&chainDef);
		conveyer[i+6]->CreateFixture(&chainfd);
		}

		///rightmost vertical
		chainshape.SetAsBox(heig, wid);
		 for (int i = 0; i < 6; ++i)
		{
		vs[i+18].Set(12.0f,19.0f-i*(2*wid));
		chainDef.position.Set(12.0f,18.75f-i*(2*wid));
		conveyer[i+18]=m_world->CreateBody(&chainDef);
		conveyer[i+18]->CreateFixture(&chainfd);
		}
		
		///Adding Revolute joint between chain units
		b2RevoluteJointDef jointDef3;
		 for(int i=1;i<24;i++)
		{
		jointDef3.Initialize(conveyer[i-1], conveyer[i],vs[i]);
		m_world->CreateJoint(&jointDef3);
		}
		b2Vec2 anchorleft,anchorright;
		anchorleft.Set(6,16);
		anchorright.Set(12,16);
		jointDef3.Initialize(conveyer[0], box1,anchorleft);
		m_world->CreateJoint(&jointDef3);
		jointDef3.Initialize(conveyer[23],box1,anchorright);
		m_world->CreateJoint(&jointDef3);
		
		
		heig=0.2;
		///leftmost sling
		chainshape.SetAsBox(heig, wid);
		 for (int i = 0; i < 16; ++i)
		{
		vs[i+24].Set(-26.7f,11.65f+i*(2*wid));
		chainDef.position.Set(-26.7f,11.9f+i*(2*wid));
		conveyer[i+24]=m_world->CreateBody(&chainDef);
		conveyer[i+24]->CreateFixture(&chainfd);
		}
		
		///top sling
		chainshape.SetAsBox(wid, heig);
		 for (int i = 0; i < 10; ++i)
		{
		vs[i+40].Set(-26.5f+(2*wid)*i,19.65f);
		chainDef.position.Set(-26.25f+(2*wid)*i,19.85f);
		conveyer[i+40]=m_world->CreateBody(&chainDef);
		conveyer[i+40]->CreateFixture(&chainfd);
		}
		
		///rightmost sling
		chainshape.SetAsBox(heig, wid);
		 for (int i = 0; i < 16; ++i)
		{
		vs[i+50].Set(-21.3f,19.65f-i*(2*wid));
		chainDef.position.Set(-21.3f,19.4f-i*(2*wid));
		conveyer[i+50]=m_world->CreateBody(&chainDef);
		conveyer[i+50]->CreateFixture(&chainfd);
		}
		
		
		b2Body* sling;
		{
			b2EdgeShape shape;
			shape.Set(b2Vec2(-20.5f, 9.65f), b2Vec2(-20.5f, 7.25f));
			b2FixtureDef groundfd;
			groundfd.shape = &shape;
			groundfd.density = 0.01f;
			groundfd.friction = 1.0f;
			groundfd.restitution = 0.0f;
			groundfd.filter.categoryBits = 0x0001;
			groundfd.filter.maskBits = 0x0004 | 0x008F;
			b2BodyDef bd;
			bd.position.Set(-1.0f,2.0f);
			bd.type = b2_dynamicBody;
			//bd.gravityScale = 0.2f;	
			sling = m_world->CreateBody(&bd);
			sling->CreateFixture(&groundfd);
			
			shape.Set(b2Vec2(-20.5f, 7.25f), b2Vec2(-21.9f, 6.0f));
			groundfd.shape = &shape;
			sling->CreateFixture(&groundfd);
			
			shape.Set(b2Vec2(-21.9f, 6.0f), b2Vec2(-24.1f, 6.0f));
			groundfd.shape = &shape;
			sling->CreateFixture(&groundfd);
			
			shape.Set(b2Vec2(-24.1f, 6.0f), b2Vec2(-25.5f, 7.25f));
			groundfd.shape = &shape;
			sling->CreateFixture(&groundfd);
			
			shape.Set(b2Vec2(-25.5f, 7.25f), b2Vec2(-25.5f, 9.65f));
			groundfd.shape = &shape;
			sling->CreateFixture(&groundfd);
			
			shape.Set(b2Vec2(-25.5f, 9.65f), b2Vec2(-25.1f, 7.65f));
			groundfd.shape = &shape;
			sling->CreateFixture(&groundfd);
			
			shape.Set(b2Vec2(-25.1f, 7.65f), b2Vec2(-24.05f, 7.0f));
			groundfd.shape = &shape;
			sling->CreateFixture(&groundfd);
			
			shape.Set(b2Vec2(-24.05f, 7.0f), b2Vec2(-21.95f, 7.0f));
			groundfd.shape = &shape;
			sling->CreateFixture(&groundfd);
			
			shape.Set(b2Vec2(-21.95f, 7.0f), b2Vec2(-20.9f, 7.65f));
			groundfd.shape = &shape;
			sling->CreateFixture(&groundfd);
			
			shape.Set(b2Vec2(-20.9f, 7.65f), b2Vec2(-20.5f, 9.65f));
			groundfd.shape = &shape;
			sling->CreateFixture(&groundfd);
		}
		
		///Adding Revolute joint between chain units of sling
		b2RevoluteJointDef	 thisjoint;
		 for(int i=25;i<66;i++)
		{
		thisjoint.Initialize(conveyer[i-1], conveyer[i],vs[i]);
		m_world->CreateJoint(&thisjoint);
		}
		b2WeldJointDef weld;
		anchorleft.Set(-26.5,11.65);
		anchorright.Set(-21.5,11.65);
		weld.Initialize(conveyer[24], sling,anchorleft);
		m_world->CreateJoint(&weld);
		weld.Initialize(conveyer[65],sling,anchorright);
		m_world->CreateJoint(&weld);
	}
	
	b2Body* circleonbottom;
	{
		b2CircleShape circle;
		circle.m_radius = 2.0f;
		b2FixtureDef ballfd;
		ballfd.shape = &circle;
		ballfd.density = 0.001f;
		ballfd.friction = 0.5f;
		ballfd.restitution = 0.6f;
		b2BodyDef ballbd;
		b2Vec2 ancr;
		ancr.Set(-24.0f,11.0f);
		ballbd.type = b2_dynamicBody;
		ballbd.position.Set(ancr.x,ancr.y);
		circleonbottom = m_world->CreateBody(&ballbd);
		ballfd.filter.categoryBits = 0x008F;
		ballfd.filter.maskBits = 0x000F | 0x0003;
		circleonbottom->CreateFixture(&ballfd);
	}
	
	b2Body* toptop;
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.5f, 2.5f);

      b2BodyDef bd;
      bd.type = b2_dynamicBody;
      bd.position.Set(-10.0f, 18.0f);
      toptop = m_world->CreateBody(&bd);
      b2FixtureDef ballfd;
      ballfd.shape = &shape;
      ballfd.density = 0.001f;
      ballfd.filter.categoryBits = 0x0003;
      ballfd.filter.maskBits = 0x0004 | 0x0001 | 0x0002;
      toptop->CreateFixture(&ballfd);
    }
	{
		b2WeldJointDef jointDef;
		b2Vec2 anchor;
		anchor.Set(-10,18);
		jointDef.Initialize(top,toptop,anchor);
		m_world->CreateJoint(&jointDef);
	}
	
	{
		b2CircleShape circle;
		circle.m_radius = 1.5f;
		b2FixtureDef ballfd;
		ballfd.shape = &circle;
		ballfd.density = 0.001f;
		ballfd.friction = 100.0f;
		ballfd.restitution = 0.01f;
		b2BodyDef ballbd;
		b2Vec2 ancr;
		ancr.Set(-5.625f,8.125f);
		ballbd.type = b2_dynamicBody;
		ballbd.position.Set(ancr.x,ancr.y);
		circleontrap = m_world->CreateBody(&ballbd);
		ballfd.filter.categoryBits = 0x004F	;
		ballfd.filter.maskBits = 0x0004 || 0x00FF || 0x02FF;
		circleontrap->CreateFixture(&ballfd);
	}
	
	{
			b2PolygonShape shape;
			shape.SetAsBox(0.4,1.0,b2Vec2(0.0,2.5),0.0);
			b2FixtureDef groundfd;
			groundfd.shape = &shape;
			groundfd.density = 0.01f;
			groundfd.friction = 1.0f;
			groundfd.restitution = 0.0f;
			groundfd.filter.categoryBits = 0x002F;
			groundfd.filter.maskBits = 0x0004;\
			circleontrap->CreateFixture(&groundfd);
			
			shape.SetAsBox(1.0,0.4,b2Vec2(2.5,0.0),0.0);
			groundfd.shape = &shape;
			circleontrap->CreateFixture(&groundfd);
			
			shape.SetAsBox(0.4,1.0,b2Vec2(0.0,-2.5),0.0);
			groundfd.shape = &shape;
			circleontrap->CreateFixture(&groundfd);
			
			shape.SetAsBox(1.0,0.4,b2Vec2(-2.5,0.0),0.0);
			groundfd.shape = &shape;
			circleontrap->CreateFixture(&groundfd);
		}
	{
		b2RevoluteJointDef jointDef;
		b2Vec2 anchor;
		anchor.Set(-5.625f,8.125f);
		jointDef.Initialize(trapsec,circleontrap,anchor);
		m_world->CreateJoint(&jointDef);
	}
	
	
	b2Vec2 rope[100];
		///chain body
	b2Body* ropepart[100];

	{
		b2FixtureDef chainfd;
		chainfd.filter.categoryBits = 0x00FF;
		chainfd.filter.maskBits =0xFFFF & ~0x0002;
		b2PolygonShape chainshape;
		float wid=0.25,heig=0.05;
		chainshape.SetAsBox(heig, wid);
		chainfd.shape = &chainshape;
		chainfd.density=0.01f;
		chainfd.friction=1000.0f;
		b2BodyDef chainDef;
		chainDef.type = b2_dynamicBody;

		///leftmost vertical
		for (int i = 0; i < 11; ++i)
		{
		rope[i].Set(-10.0f,15.5f-i*(2*wid));
		chainDef.position.Set(-10.0f,15.25f-i*(2*wid));
		ropepart[i]=m_world->CreateBody(&chainDef);
		ropepart[i]->CreateFixture(&chainfd);
		}
		
		rope[11].Set(-10.0f,10.0f);
		///Top horizontal
		chainshape.SetAsBox(wid, heig);
		 for (int i = 0; i < 12; ++i)
		{
		rope[i+12].Set(-9.55f+(2*wid)*i,9.95f);
		chainDef.position.Set(-9.8f+(2*wid)*i,9.95f);
		ropepart[i+11]=m_world->CreateBody(&chainDef);
		ropepart[i+11]->CreateFixture(&chainfd);
		}

		///rightmost vertical
		chainshape.SetAsBox(heig, wid);
		 for (int i = 0; i < 7; ++i)
		{
		rope[i+24].Set(-4.0f,9.5f-i*(2*wid));
		chainDef.position.Set(-4.0f,9.75f-i*(2*wid));
		ropepart[i+23]=m_world->CreateBody(&chainDef);
		ropepart[i+23]->CreateFixture(&chainfd);
		}
		
		rope[30].Set(-4.05f,6.55f);
		///bottommost horizontal
		chainshape.SetAsBox(wid, heig);
		 for (int i = 0; i < 3; ++i)
		{
		rope[i+31].Set(-4.55f-(2*wid)*i,6.55f);
		chainDef.position.Set(-4.3f-(2*wid)*i,6.55f);
		ropepart[i+30]=m_world->CreateBody(&chainDef);
		ropepart[i+30]->CreateFixture(&chainfd);
		}
		///Adding Revolute joint between chain units
		b2RevoluteJointDef jointDef3;
		 for(int i=1;i<33;i++)
		{
		jointDef3.Initialize(ropepart[i-1], ropepart[i],rope[i]);
		m_world->CreateJoint(&jointDef3);
		}
		b2WeldJointDef weldjoint;
		weldjoint.Initialize(ropepart[0],toptop,rope[0]);
		m_world->CreateJoint(&weldjoint);
		weldjoint.Initialize(ropepart[32],circleontrap,rope[33]);
		m_world->CreateJoint(&weldjoint);
	}
	
	b2Body* horizontal;
	{
      b2PolygonShape shape;
      shape.SetAsBox(5.0f, 0.2f);
      
      b2BodyDef bd;
      bd.position.Set(15.0f, 18.0f);
      horizontal = m_world->CreateBody(&bd);
      b2FixtureDef ballfd;
      ballfd.shape = &shape;
      ballfd.density = 0.001f;
      ballfd.filter.categoryBits = 0x04FF;
      ballfd.filter.maskBits = 0x08FF & ~0x0FFF;
      horizontal->CreateFixture(&ballfd);
    }
    
    {
		b2CircleShape circle;
		circle.m_radius = 2.0f;
		b2FixtureDef ballfd;
		ballfd.shape = &circle;
		ballfd.density = 100.0f;
		ballfd.friction = 100.0f;
		ballfd.restitution = 0.01f;
		b2BodyDef ballbd;
		b2Vec2 ancr;
		ancr.Set(15.0f,24.25f);
		ballbd.type = b2_dynamicBody;
		ballbd.position.Set(ancr.x,ancr.y);
		heavybody = m_world->CreateBody(&ballbd);
		ballfd.filter.categoryBits = 0x08FF	;
		ballfd.filter.maskBits = 0x0FFF & ~0x0003 & ~0x0008 & ~0x0004;
		heavybody->CreateFixture(&ballfd);
	}
		
  }
  
  

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
