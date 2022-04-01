#pragma once

#include <utility>

#include "exeptions.h"

class movable_iface
{
public:
  movable_iface () {}
  virtual ~movable_iface () = default;

  virtual std::pair<int, int> get_position () const = 0;
  virtual std::pair<int, int> get_velocity () const = 0;
  virtual void set_position (const std::pair<int, int> &position) = 0;
};

class move
{
public:
  move (movable_iface *movable) : movable (movable) {}
  ~move () = default;

  void execute ()
  {
    try
    {
      auto position = movable->get_position ();
      auto velocity = movable->get_velocity ();
      movable->set_position (std::make_pair (position.first + velocity.first, position.second + velocity.second));
    }
    catch (const get_exeption &)
    {
      throw move_exeption ();
    }
    catch (const set_exeption &)
    {
      throw move_exeption ();
    }
  }

private:
  movable_iface *movable = nullptr;
};
