#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "rotation.h"

using namespace testing;

class mock_object_for_rotation : public rotation_iface
{
public:
  MOCK_CONST_METHOD0 (get_direction, int ());
  MOCK_CONST_METHOD0 (get_angular_velocity, int ());
  MOCK_METHOD2 (calc_next_direction, int (int, int));
  MOCK_METHOD1 (set_direction, void (int));
};

TEST (rotation_test, correct_rotation_test)
{
  auto mock_object_ptr = std::make_unique<mock_object_for_rotation> ();
  int new_direction;
  EXPECT_CALL(*mock_object_ptr, get_direction ())
          .WillOnce (Return (15));
  EXPECT_CALL(*mock_object_ptr, get_angular_velocity ())
          .WillOnce (Return (1));
  EXPECT_CALL(*mock_object_ptr, calc_next_direction (_, _))
          .WillOnce (Return (20));
  EXPECT_CALL(*mock_object_ptr, set_direction (_))
          .WillOnce (SaveArg<0> (&new_direction));

  rotate rotate_instance (mock_object_ptr.get ());
  rotate_instance.execute ();

  EXPECT_TRUE (new_direction == 20);
}

TEST (rotation_test, object_without_direction_test)
{
  auto mock_object_ptr = std::make_unique<mock_object_for_rotation> ();
  EXPECT_CALL(*mock_object_ptr, get_direction ())
          .WillOnce (Throw (get_exeption ()));

  rotate rotate_instance (mock_object_ptr.get ());
  EXPECT_THROW (rotate_instance.execute (), rotate_exeption);
}

TEST (rotation_test, object_without_angular_velocity_test)
{
  auto mock_object_ptr = std::make_unique<mock_object_for_rotation> ();
  EXPECT_CALL(*mock_object_ptr, get_direction ())
          .WillOnce (Return (5));
  EXPECT_CALL(*mock_object_ptr, get_angular_velocity ())
          .WillOnce (Throw (get_exeption ()));

  rotate rotate_instance (mock_object_ptr.get ());
  EXPECT_THROW (rotate_instance.execute (), rotate_exeption);
}

TEST (rotation_test, not_rotatable_object_test)
{
  auto mock_object_ptr = std::make_unique<mock_object_for_rotation> ();
  EXPECT_CALL(*mock_object_ptr, get_direction ())
          .WillOnce (Return (5));
  EXPECT_CALL(*mock_object_ptr, get_angular_velocity ())
          .WillOnce (Return (1));
  EXPECT_CALL(*mock_object_ptr, set_direction (_))
          .WillOnce (Throw (set_exeption ()));

  rotate rotate_instance (mock_object_ptr.get ());
  EXPECT_THROW (rotate_instance.execute (), rotate_exeption);
}


