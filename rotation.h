#pragma once

#include "exeptions.h"

class rotation_iface
{
public:
  rotation_iface () {}
  virtual ~rotation_iface () = default;

  virtual int get_direction () const = 0;
  virtual int get_angular_velocity () const = 0;
  virtual int calc_next_direction (int direction, int angular_velocity) = 0;
  virtual void set_direction (int direction) = 0;
};

class rotate
{
public:
  rotate (rotation_iface *rotating) : rotating (rotating) {}
  ~rotate () = default;

  void execute ()
  {
    try
    {
      auto direction = rotating->get_direction ();
      auto velocity = rotating->get_angular_velocity ();
      rotating->set_direction (rotating->calc_next_direction (direction, velocity));
    }
    catch (const get_exeption &)
    {
      throw rotate_exeption ();
    }
    catch (const set_exeption &)
    {
      throw rotate_exeption ();
    }
  }

private:
  rotation_iface *rotating = nullptr;
};
