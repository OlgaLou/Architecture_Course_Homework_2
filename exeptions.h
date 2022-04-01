#pragma once

class exception_base
{
  public:
    exception_base (const char *value) :value (value) {}
    const char *get_message () const { return value; }
  private:
    const char *value = nullptr;
};

class move_exeption : public exception_base
{
public:
  move_exeption () : exception_base ("Motion Error") {}
};

class get_exeption : public exception_base
{
public:
  get_exeption () : exception_base ("Object Property Getter Error") {}
};

class set_exeption : public exception_base
{
public:
  set_exeption () : exception_base ("Object Property Setter Error") {}
};

class rotate_exeption : public exception_base
{
public:
  rotate_exeption () : exception_base ("Rotation Error") {}
};
