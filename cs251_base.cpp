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

#include "cs251_base.hpp"
#include <cstdio>
using namespace std;
using namespace cs251;
b2Joint* jstring;
b2World* global;
int count1=0;
bool destroyjoint=false;
class stars;
stars* astars[20];
int countarrayh[20];
class stars
{
public:
b2Body* m_body;
stars(b2World* world,int posx,int posy) {
      m_body = NULL;
      //m_radius = radius;

      //set up dynamic body, store in class variable
      b2BodyDef myBodyDef;
      myBodyDef.type = b2_dynamicBody;
      myBodyDef.position.Set(posx, posy);
      m_body = world->CreateBody(&myBodyDef);

      //add circle fixture
      b2CircleShape circleShape;
      circleShape.m_p.Set(0, 0);
      circleShape.m_radius = 0.00001; //use class variable
      b2FixtureDef myFixtureDef;
      myFixtureDef.shape = &circleShape;
      myFixtureDef.density = 0.000001;
      m_body->CreateFixture(&myFixtureDef);

      //m_body->SetUserData(this);
        //in Ball class constructor
 // m_contacting = false;
    }

};
class Ball
{
  public:
    //class member variables
         //Ball class member variable
  bool m_contacting;
    b2Body* m_body;
    float m_radius;
        Ball(b2World* world, float radius) {
      m_body = NULL;
      m_radius = radius;

      //set up dynamic body, store in class variable
      b2BodyDef myBodyDef;
      myBodyDef.type = b2_dynamicBody;
      myBodyDef.position.Set(0, 20);
      m_body = world->CreateBody(&myBodyDef);

      //add circle fixture
      b2CircleShape circleShape;
      circleShape.m_p.Set(0, 0);
      circleShape.m_radius = m_radius; //use class variable
      b2FixtureDef myFixtureDef;
      myFixtureDef.shape = &circleShape;
      myFixtureDef.density = 1;
      m_body->CreateFixture(&myFixtureDef);
      m_body->SetUserData(this);
      m_body->SetId(0);
        //in Ball class constructor
  m_contacting = false;
    }




  //Ball class functions
  void startContact() { m_contacting = true; }
  void endContact() { m_contacting = false; }
};
class button
{public:
  int id;
  b2Body* m_body;
  b2FixtureDef fd;
  b2BodyDef box1;
bool m_contacting;
button(b2World* m_world)
{
  box1.position.Set(20.5f,34.5f);
  box1.type=b2_dynamicBody;
  b2PolygonShape boxshape;
  boxshape.SetAsBox(.01f,0.01f);
  fd.shape=&boxshape;
  fd.density=1.f;
  m_body=m_world->CreateBody(&box1);
  m_body->CreateFixture(&fd);
  m_body->SetUserData(this);
  m_body->SetId(1);
  m_contacting=false;
}
};
class MyCL:public b2ContactListener
{
    void BeginContact(b2Contact* contact) {
int id1 = contact->GetFixtureA()->GetBody()->GetId();

if(id1==0){
      //check if fixture A was a ball
      void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Ball*>( bodyUserData )->startContact();
      }
      else
      {if(count1==0){
        destroyjoint=true;count1++;}
        //global->DestroyJoint(jstring);
      }
id1 = contact->GetFixtureA()->GetBody()->GetId();
      //check if fixture B was a ball
      void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Ball*>( bodyUserData )->startContact();

    }

    void EndContact(b2Contact* contact) {
      //check if fixture A was a ball
      //int id=contact->GetFixtureA()-
      void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Ball*>( bodyUserData )->endContact();

      //check if fixture B was a ball
      bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Ball*>( bodyUserData )->endContact();

    }
};

		  //at global scope
  MyCL myContactListenerInstance;

Ball* b;
button* sw;
//stars* astars[50];
base_sim_t::base_sim_t()
{
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
	m_world = new b2World(gravity);

	m_text_line = 30;

	m_point_count = 0;

	m_world->SetDebugDraw(&m_debug_draw);

	m_step_count = 0;

	b2BodyDef body_def;
	m_ground_body = m_world->CreateBody(&body_def);

	memset(&m_max_profile, 0, sizeof(b2Profile));
	memset(&m_total_profile, 0, sizeof(b2Profile));
	    m_world->SetContactListener(&myContactListenerInstance);
	b=new Ball(m_world,1);
  for(int i=0;i<20;i++)
  {
  astars[i]=new stars(m_world,0,0);
  countarrayh[i]=0;
  global=m_world;
}

//##########
b2FixtureDef fd;
b2BodyDef box;
box.position.Set(20.5f,38.0f);
b2PolygonShape boxshape;
boxshape.SetAsBox(2.0f,0.1f);
fd.shape=&boxshape;
fd.density=1.f;
b2Body* boxx=m_world->CreateBody(&box);
boxx->CreateFixture(&fd);
/*
b2BodyDef box1;
box1.position.Set(20.5f,34.5f);
box1.type=b2_dynamicBody;
//b2PolygonShape boxshape;
boxshape.SetAsBox(.01f,0.01f);
fd.shape=&boxshape;
fd.density=1.f;
b2Body* boxx1=m_world->CreateBody(&box1);
boxx1->CreateFixture(&fd);
*/
sw=new button(m_world);
b2BodyDef box2;
box2.position.Set(20.5f,34.4f);
box2.type=b2_dynamicBody;
//b2PolygonShape boxshape;
boxshape.SetAsBox(.01f,0.01f);
fd.shape=&boxshape;
fd.density=1.f;
b2Body* boxx2=m_world->CreateBody(&box2);
boxx2->CreateFixture(&fd);

b2BodyDef ball;
ball.position.Set(20.5f,30.0f);
b2CircleShape circle;
circle.m_radius=1.0f;
fd.shape=&circle;
ball.type=b2_dynamicBody;
fd.density=1.0f;
b2Body* cir=m_world->CreateBody(&ball);
cir->CreateFixture(&fd);
//b2MotorJointDef mjd;
b2RevoluteJointDef string;
b2RevoluteJointDef string1;
b2RevoluteJointDef string2;
b2Vec2 anchor;
anchor.Set(20.5f,38.0f);
b2Vec2 anchor1;
anchor1.Set(20.5f,34.5f);
b2Vec2 anchor2;
anchor2.Set(20.5f,34.4f);
string.Initialize(boxx,sw->m_body,anchor);
string1.Initialize(sw->m_body,boxx2,anchor1);
string2.Initialize(boxx2,cir,anchor2);
//mjd.Initialize(b1,body);
//mjd.maxForce=1.f;
//mjd.maxTorque=1000.f;
//mjd.motorSpeed=1.0f;
//mjd.enableMotor=true;
//m_world->CreateJoint(&mjd);
m_world->CreateJoint(&string);
jstring=m_world->CreateJoint(&string1);
m_world->CreateJoint(&string2);
//m_world->DestroyJoint(jstring);
//################
	/*
	for(int i=0;i<50;i++)
	{
    astars[i]=new stars(m_world,rand()%60,rand()%60);
    }
    */
    //in FooTest constructor

}

base_sim_t::~base_sim_t()
{
	// By deleting the world, we delete the bomb, mouse joint, etc.
	delete m_world;
	m_world = NULL;
}

void base_sim_t::pre_solve(b2Contact* contact, const b2Manifold* oldManifold)
{

  const b2Manifold* manifold = contact->GetManifold();

  if (manifold->pointCount == 0)
    {
      return;
    }

  b2Fixture* fixtureA = contact->GetFixtureA();
  b2Fixture* fixtureB = contact->GetFixtureB();

  b2PointState state1[b2_maxManifoldPoints], state2[b2_maxManifoldPoints];
  b2GetPointStates(state1, state2, oldManifold, manifold);

  b2WorldManifold world_manifold;
  contact->GetWorldManifold(&world_manifold);

  for (int32 i = 0; i < manifold->pointCount && m_point_count < k_max_contact_points; ++i)
    {
      contact_point_t* cp = m_points + m_point_count;
      cp->fixtureA = fixtureA;
      cp->fixtureB = fixtureB;
      cp->position = world_manifold.points[i];
      cp->normal = world_manifold.normal;
      cp->state = state2[i];
      ++m_point_count;
    }
}

void base_sim_t::draw_title(int x, int y, const char *string)
{
    m_debug_draw.DrawString(x, y, string);
}

//b2Vec2 pos;
void base_sim_t::step(settings_t* settings)
{
 m_debug_draw.renderAtBodyPosition(b->m_body,b->m_contacting);
 for(int i=0;i<20;i++)
 {
  if(countarrayh[i]==0)
  {
 m_debug_draw.renderStars(b->m_body,0.5);
 countarrayh[i]=1;
}
else
{
  m_debug_draw.renderStars(astars[i]->m_body,0.5);
}
}
 //pos=b->m_body->GetPosition();
  float32 time_step = settings->hz > 0.0f ? 1.0f / settings->hz : float32(0.0f);

  if (settings->pause)
    {
      if (settings->single_step)
	{
	  settings->single_step = 0;
	}
      else
	{
	  time_step = 0.0f;
	}

      m_debug_draw.DrawString(5, m_text_line, "****PAUSED****");
      m_text_line += 15;
    }

  uint32 flags = 0;
  flags += settings->draw_shapes			* b2Draw::e_shapeBit;
  flags += settings->draw_joints			* b2Draw::e_jointBit;
  flags += settings->draw_AABBs			* b2Draw::e_aabbBit;
  flags += settings->draw_pairs			* b2Draw::e_pairBit;
  flags += settings->draw_COMs				* b2Draw::e_centerOfMassBit;
  m_debug_draw.SetFlags(flags);

  m_world->SetWarmStarting(settings->enable_warm_starting > 0);
  m_world->SetContinuousPhysics(settings->enable_continuous > 0);
  m_world->SetSubStepping(settings->enable_sub_stepping > 0);

  m_point_count = 0;

  m_world->Step(time_step, settings->velocity_iterations, settings->position_iterations);
  if (time_step > 0.0f)
    {
      ++m_step_count;
    }

  if (settings->draw_stats)
    {
      int32 body_count = m_world->GetBodyCount();
      int32 contact_count = m_world->GetContactCount();
      int32 joint_count = m_world->GetJointCount();
      m_debug_draw.DrawString(5, m_text_line, "bodies/contacts/joints = %d/%d/%d", body_count, contact_count, joint_count);
      m_text_line += 15;

      int32 proxy_count = m_world->GetProxyCount();
      int32 height = m_world->GetTreeHeight();
      int32 balance = m_world->GetTreeBalance();
      float32 quality = m_world->GetTreeQuality();
      m_debug_draw.DrawString(5, m_text_line, "proxies/height/balance/quality = %d/%d/%d/%g", proxy_count, height, balance, quality);
      m_text_line += 15;
    }

  // Track maximum profile times
  {
    const b2Profile& p = m_world->GetProfile();
    m_max_profile.step = b2Max(m_max_profile.step, p.step);
    m_max_profile.collide = b2Max(m_max_profile.collide, p.collide);
    m_max_profile.solve = b2Max(m_max_profile.solve, p.solve);
    m_max_profile.solveInit = b2Max(m_max_profile.solveInit, p.solveInit);
    m_max_profile.solveVelocity = b2Max(m_max_profile.solveVelocity, p.solveVelocity);
    m_max_profile.solvePosition = b2Max(m_max_profile.solvePosition, p.solvePosition);
    m_max_profile.solveTOI = b2Max(m_max_profile.solveTOI, p.solveTOI);
    m_max_profile.broadphase = b2Max(m_max_profile.broadphase, p.broadphase);

    m_total_profile.step += p.step;
    m_total_profile.collide += p.collide;
    m_total_profile.solve += p.solve;
    m_total_profile.solveInit += p.solveInit;
    m_total_profile.solveVelocity += p.solveVelocity;
    m_total_profile.solvePosition += p.solvePosition;
    m_total_profile.solveTOI += p.solveTOI;
    m_total_profile.broadphase += p.broadphase;
  }

  if (settings->draw_profile)
    {
      const b2Profile& p = m_world->GetProfile();

      b2Profile ave_profile;
      memset(&ave_profile, 0, sizeof(b2Profile));
      if (m_step_count > 0)
	{
	  float32 scale = 1.0f / m_step_count;
	  ave_profile.step = scale * m_total_profile.step;
	  ave_profile.collide = scale * m_total_profile.collide;
	  ave_profile.solve = scale * m_total_profile.solve;
	  ave_profile.solveInit = scale * m_total_profile.solveInit;
	  ave_profile.solveVelocity = scale * m_total_profile.solveVelocity;
	  ave_profile.solvePosition = scale * m_total_profile.solvePosition;
	  ave_profile.solveTOI = scale * m_total_profile.solveTOI;
	  ave_profile.broadphase = scale * m_total_profile.broadphase;
	}

      m_debug_draw.DrawString(5, m_text_line, "step [ave] (max) = %5.2f [%6.2f] (%6.2f)", p.step, ave_profile.step, m_max_profile.step);
      m_text_line += 15;
      m_debug_draw.DrawString(5, m_text_line, "collide [ave] (max) = %5.2f [%6.2f] (%6.2f)", p.collide, ave_profile.collide, m_max_profile.collide);
      m_text_line += 15;
      m_debug_draw.DrawString(5, m_text_line, "solve [ave] (max) = %5.2f [%6.2f] (%6.2f)", p.solve, ave_profile.solve, m_max_profile.solve);
      m_text_line += 15;
      m_debug_draw.DrawString(5, m_text_line, "solve init [ave] (max) = %5.2f [%6.2f] (%6.2f)", p.solveInit, ave_profile.solveInit, m_max_profile.solveInit);
      m_text_line += 15;
      m_debug_draw.DrawString(5, m_text_line, "solve velocity [ave] (max) = %5.2f [%6.2f] (%6.2f)", p.solveVelocity, ave_profile.solveVelocity, m_max_profile.solveVelocity);
      m_text_line += 15;
      m_debug_draw.DrawString(5, m_text_line, "solve position [ave] (max) = %5.2f [%6.2f] (%6.2f)", p.solvePosition, ave_profile.solvePosition, m_max_profile.solvePosition);
      m_text_line += 15;
      m_debug_draw.DrawString(5, m_text_line, "solveTOI [ave] (max) = %5.2f [%6.2f] (%6.2f)", p.solveTOI, ave_profile.solveTOI, m_max_profile.solveTOI);
      m_text_line += 15;
      m_debug_draw.DrawString(5, m_text_line, "broad-phase [ave] (max) = %5.2f [%6.2f] (%6.2f)", p.broadphase, ave_profile.broadphase, m_max_profile.broadphase);
      m_text_line += 15;
    }

  if (settings->draw_contact_points)
    {
      //const float32 k_impulseScale = 0.1f;
      const float32 k_axis_scale = 0.3f;

      for (int32 i = 0; i < m_point_count; ++i)
	{
	  contact_point_t* point = m_points + i;

	  if (point->state == b2_addState)
	    {
	      // Add
	      m_debug_draw.DrawPoint(point->position, 10.0f, b2Color(0.3f, 0.95f, 0.3f));
	    }
	  else if (point->state == b2_persistState)
	    {
	      // Persist
	      m_debug_draw.DrawPoint(point->position, 5.0f, b2Color(0.3f, 0.3f, 0.95f));
	    }

	  if (settings->draw_contact_normals == 1)
	    {
	      b2Vec2 p1 = point->position;
	      b2Vec2 p2 = p1 + k_axis_scale * point->normal;
	      m_debug_draw.DrawSegment(p1, p2, b2Color(0.9f, 0.9f, 0.9f));
	    }
	  else if (settings->draw_contact_forces == 1)
	    {
	      //b2Vec2 p1 = point->position;
	      //b2Vec2 p2 = p1 + k_forceScale * point->normalForce * point->normal;
	      //DrawSegment(p1, p2, b2Color(0.9f, 0.9f, 0.3f));
	    }

	  if (settings->draw_friction_forces == 1)
	    {
	      //b2Vec2 tangent = b2Cross(point->normal, 1.0f);
	      //b2Vec2 p1 = point->position;
	      //b2Vec2 p2 = p1 + k_forceScale * point->tangentForce * tangent;
	      //DrawSegment(p1, p2, b2Color(0.9f, 0.9f, 0.3f));
	    }
	}
    }
    m_world->DrawDebugData();
  if(destroyjoint)
  {
    //m_world->DestroyBody(sw->m_body);
    //jstring=NULL;
    m_world->DestroyJoint(jstring);
    destroyjoint=false;
  }
}
