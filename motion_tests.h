#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "motion.h"

using namespace testing;

class mock_object : public movable_iface
{
public:
  MOCK_CONST_METHOD0 (get_position, std::pair<int, int> ());
  MOCK_CONST_METHOD0 (get_velocity, std::pair<int, int> ());
  MOCK_METHOD1 (set_position, void (const std::pair<int, int> &));
};

TEST (motion_test, correct_motion_test)
{
  auto mock_object_ptr = std::make_unique<mock_object> ();
  std::pair<int, int> new_position;
  EXPECT_CALL(*mock_object_ptr, get_position ())
          .WillOnce (Return (std::make_pair (12, 5)));
  EXPECT_CALL(*mock_object_ptr, get_velocity ())
          .WillOnce (Return (std::make_pair (-7, 3)));
  EXPECT_CALL(*mock_object_ptr, set_position (_))
          .WillOnce (SaveArg<0> (&new_position));

  move move_instance (mock_object_ptr.get ());
  move_instance.execute ();

  EXPECT_TRUE (new_position == std::make_pair (5, 8));
}

TEST (motion_test, object_without_position_test)
{
  auto mock_object_ptr = std::make_unique<mock_object> ();
  EXPECT_CALL(*mock_object_ptr, get_position ())
          .WillOnce (Throw (get_exeption ()));

  move move_instance (mock_object_ptr.get ());
  EXPECT_THROW (move_instance.execute (), move_exeption);
}

TEST (motion_test, object_without_velocity_test)
{
  auto mock_object_ptr = std::make_unique<mock_object> ();
  EXPECT_CALL(*mock_object_ptr, get_position ())
          .WillOnce (Return (std::make_pair (12, 5)));
  EXPECT_CALL(*mock_object_ptr, get_velocity ())
          .WillOnce (Throw (get_exeption ()));

  move move_instance (mock_object_ptr.get ());
  EXPECT_THROW (move_instance.execute (), move_exeption);
}

TEST (motion_test, not_movable_object_test)
{
  auto mock_object_ptr = std::make_unique<mock_object> ();
  EXPECT_CALL(*mock_object_ptr, get_position ())
          .WillOnce (Return (std::make_pair (12, 5)));
  EXPECT_CALL(*mock_object_ptr, get_velocity ())
          .WillOnce (Return (std::make_pair (-7, 3)));
  EXPECT_CALL(*mock_object_ptr, set_position (_))
          .WillOnce (Throw (set_exeption ()));

  move move_instance (mock_object_ptr.get ());
  EXPECT_THROW (move_instance.execute (), move_exeption);
}

