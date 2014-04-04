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


#ifndef _CS296BASE_HPP_
#define _CS296BASE_HPP_

#include "render.hpp"
#include <Box2D/Box2D.h>
#include <cstdlib>

#define	RAND_LIMIT 32767

namespace cs296
{
  class base_sim_t;
  struct settings_t;
  
  typedef base_sim_t* sim_create_fcn(); 

  struct settings_t
  {
    settings_t() :
      view_center(0.0f, 20.0f), //!< The origin of World is set to (0.0, 20.0)
      hz(60.0f), //!< Frequency of simulation is set to 60.0 Hz 
      velocity_iterations(8), //!< Velocity iterations set to be 8 initially. It is the number of times constraints are iterated to calculate the velocity
      position_iterations(3), //!< Position iterations set to be 3 initially. It is the number of times constraints are iterated to calculate the position 
      draw_shapes(1), //!< draw_shapes is a boolean value. 1 means all objects will be displayed
      draw_joints(1), //!< draw_joints is a boolean value. 1 means all joints will be displayed
      draw_AABBs(0), //!< draw_AABB is a boolean value. 0 means all Axis-aligned bounding boxes(AABB) will not be displayed
      draw_pairs(0),
      draw_contact_points(0), //!< draw_contact_points is a boolean value. 0 means Contact points between colliding objects will not be displayed
      draw_contact_normals(0), //!< draw_contact_normals is a boolean value. 0 means Contact normals between colliding objects will not be displayed
      draw_contact_forces(0), //!< draw_contact_forces is a boolean value. 0 means Contact forces will not be displayed
      draw_friction_forces(0), //!< draw_friction_forces is a boolean value. 0 means frictional forces will not be shown
      draw_COMs(0), //!< draw_COMs is a boolean value. 0 means Center of mass of objects will not be shown
      draw_stats(0), //!< draw_stats is a boolean value. 0 means Information of bodies,contacts and joints will not be shown
      draw_profile(0), //!< draw_profile is a boolean value. 0 means it will not show calculation done by Box2D
      enable_warm_starting(1), //!< enable_warm_starting is used to enable/disable warm starting. 1 implies enabled
      enable_continuous(1), //!< enable_continuous is used to enable/disable continuous physics. 1 implies enabled
      enable_sub_stepping(0), //!< enable_sub_stepping is used to enable/disable single stepped physics. 0 implies disabled
      pause(0), //!< pause is used to pause the simulation. Initially 0 implies unpaused
      single_step(0) //!< pause is used to enable single step simulation. Initially 0 implies disabled
    {}
    
    b2Vec2 view_center; //!< This option shifts the origin of screen to the value of this vector.
    float32 hz;//!< Represents the frequency of simulation. On incresing this simulation beccomes slower but accurate.
    int32 velocity_iterations; //!< The solver computes the impulses necessary for the bodies to move correctly. It is an int32 type..
    int32 position_iterations; //!< Variable to set position iterations in the simulation. It is an int32 type.
    int32 draw_shapes; //!< This Variable Shows all Box2D objects's shapes.
    int32 draw_joints; //!< This Variable Shows all Box2D objects's joints.
    int32 draw_AABBs; //!< This variable shows axis-aligned bounding boxes(AABB).
    int32 draw_pairs; //!< It is an int32 type object.
    int32 draw_contact_points; //!< This variable is used to set drawing of contact points to true or false.
    int32 draw_contact_normals;//!< This variable is used to set drawing of contact normals to true or false.
    int32 draw_contact_forces; //!< This variable is used to set drawing of contact forces to true or false.
    int32 draw_friction_forces; //!< This variable is used to set drawing of frictional forces to true or false.
    int32 draw_COMs; //!< This variable is used to set drawing of Center of mass to true or false.
    int32 draw_stats; //!< This variavle show all information of bodies,contacts and joints.
    int32 draw_profile; //!< This variavle show all calculation done by Box2D on screen.
    int32 enable_warm_starting; //!< This variable is used for simualting object collitions more accurately
    int32 enable_continuous; //!< Box2d uses Continuous collision detection(CCD).Bodies are moved to their first Time of imapct and then halted for the remainder of the time step.
    int32 enable_sub_stepping; //!< This variable solves the collision after moving the bodies to time of impact.
    int32 pause; //!< This variable pause the simulation.
    int32 single_step; //!< This variable is used to move only single time step.
  };
  //!<struct settings_t: Contains all the variables to control the simulation settings and initialise them.
  
  struct sim_t
  {
    const char *name; //!< A pointer to name that will be given to the simulation.
    sim_create_fcn *create_fcn; //!< It is a variable of type base_sim_t.

	//! This is a constructor for struct sim_t which takes a string, and a base_sim_t type objects and creats a object.
    sim_t(const char *_name, sim_create_fcn *_create_fcn): 
      name(_name), create_fcn(_create_fcn) {;}
  };
  //!< struct sim_t: This struct starts the simulation.
  
  extern sim_t *sim; //!< extern word implies that *sim is defined in another file
  
  
  const int32 k_max_contact_points = 2048; //!< This number means that maximum number of contact points. 
  
  struct contact_point_t
  {
    b2Fixture* fixtureA; //!< It is a fixture type object Body A which contains all attributes of body(height,width,frixtional values, restitution etc) 
    b2Fixture* fixtureB; //!< It is a fixture type object Body B which contains all attributes of body(height,width,frixtional values, restitution etc)
    b2Vec2 normal; //!< It is a vector normal to point of contacts of two colloiding objects.
    b2Vec2 position; //!< It is the position of point of contact.
    b2PointState state; //!< This variable contains information about state of contact points.
  };
  //!< This Struct has all information about point of contact of two colliding objects. By draw_contact_points we can draw this information.
  
  
  //!This is a inherited class of b2ContactListener. This class is implemented to get the contact results after the time step.
  class base_sim_t : public b2ContactListener
  {
  public:
    
    base_sim_t(); //!<It constructs the world and defines its gravity vector

    //! Virtual destructors - amazing objects. Why are these necessary?
    virtual ~base_sim_t(); //!< By using pointer of b2ContactListener(base class) we can delete instance of derived class base_sim_t.
    
    void set_text_line(int32 line) { m_text_line = line; } //!< It will set the line at which debugging messages are to be printed.
    void draw_title(int x, int y, const char *string); //!< Sets the x, y coordinates and string corresponding to the title and draws string on screen
    
    virtual void step(settings_t* settings); //!< This function assign the variables initiall in m_world.

	//! B2_NOT_USED(key) is used to avoid the warnings of not using variable corresponding to the char key on keyboard press.

    virtual void keyboard(unsigned char key) { B2_NOT_USED(key); } //!< This checks if keyboard char key is pressed and accordingly responds.
    virtual void keyboard_up(unsigned char key) { B2_NOT_USED(key); } //!< This checks if keyboard arrows keys are pressed or not.

    void shift_mouse_down(const b2Vec2& p) { B2_NOT_USED(p); } //!< This function checks if shift_mouse_down is used or not.
    virtual void mouse_down(const b2Vec2& p) { B2_NOT_USED(p); } //!< This function checks if mouse_down is used.
    virtual void mouse_up(const b2Vec2& p) { B2_NOT_USED(p); } //!< This function checks if mouse_up is used.
    void mouse_move(const b2Vec2& p) { B2_NOT_USED(p); } //!< This function checks that mouse is moved or not.

    
    // Let derived tests know that a joint was destroyed.	
    virtual void joint_destroyed(b2Joint* joint) { B2_NOT_USED(joint); } //!< This checks joint information of the destroyed joint
    
    // Callbacks for derived classes.
    virtual void begin_contact(b2Contact* contact) { B2_NOT_USED(contact); } //!< This calculates contact information about new contact made between bodies
    virtual void end_contact(b2Contact* contact) { B2_NOT_USED(contact); } //!< This calculates contact information about end of contact between bodies
    virtual void pre_solve(b2Contact* contact, const b2Manifold* oldManifold); //!< This calculates contact information of two bodies in simulation and it contains information of contact points and normal vectors.
    virtual void post_solve(const b2Contact* contact, const b2ContactImpulse* impulse)
    {
      B2_NOT_USED(contact);
      B2_NOT_USED(impulse);
    } //!< This calculates contact information at end of contact between bodies after collision and impulse information after collision

  //!How are protected members different from private memebers of a class in C++ ?
  protected:

    //! What are Friend classes?
    //! Friend classes can use both private and protected members of a class.
    friend class contact_listener_t; //!< Declaration of friend class.
    
    b2Body* m_ground_body; //!< A object corresponding to ground object.
    b2AABB m_world_AABB; //!< Creates the bounding boxes for shapes in GUI.
    contact_point_t m_points[k_max_contact_points]; //!< An array to contain all the contact points.
    int32 m_point_count; //!< Count of current contact points.

    debug_draw_t m_debug_draw; //!< It is used to draw the shapes of the debugging part of the world.
    int32 m_text_line; //!< To keep track of y-position of text printed on the screen.
    b2World* m_world; //!< World objects for containing all shapes and joints.

    int32 m_step_count; //!< Count of number of steps in simulation.
    
    b2Profile m_max_profile; //!< Keeps current profile
    b2Profile m_total_profile; //!< Keeps total profiles
  };
  //!< This class contains information about various interaction of user with simulation. This is also responsible for input from keyboard and mouse.
  
}	

#endif
