#ifndef FILTERS_H
#define FILTERS_H
#include <source.h>
#include <sink.h>
#include <logging.h>
#include <image.h>
#include <stdio.h>
class Filter : public Source, public Sink
{
  public:
    virtual void Update();
    virtual const char *FilterName()= 0;
    const char *SourceName(){return FilterName();};
    const char *SinkName(){return FilterName();};
};

class Shrinker : public Filter
{
    public:
        virtual void Execute();
        const char *FilterName(){return "Shrinker";};
};

class LRConcat : public Filter
{
    public:
        virtual void Execute();
        const char *FilterName(){return "LRConcat";};
};

class TBConcat : public Filter
{
    public:
        virtual void Execute();
        const char *FilterName(){return "TBConcat";};
};

class Blender : public Filter
{
    private:
        float factor;
    public:
        void SetFactor(float factor);
        float getFactor();
        virtual void Execute();
        const char *FilterName(){return "Blender";};
};
class Crop : public Filter
{
  public:
                   Crop()  { Istart = Istop = Jstart = Jstop = -1; };
    virtual const char *FilterName() { return "Crop"; };
    virtual void   Execute();
    void           SetRegion(int Istart_, int Istop_, int Jstart_, int Jstop_)
                      {
                        Istart = Istart_;
                        Istop  = Istop_;
                        Jstart = Jstart_;
                        Jstop  = Jstop_;
                      }

  private:
    int Istart, Istop, Jstart, Jstop;
};

class Transpose : public Filter
{
public:
  virtual void Execute();
  const char *FilterName(){return "Transpose";};
};

class Invert : public Filter
{
public:
  virtual void Execute();
  const char *FilterName(){return "Invert";};
};
class Color : public Source{
public:
  Color(int, int, int, int, int);
  virtual void Execute();
  const char *SourceName(){return "Constant Color";};
private:
  int _width;
  int _height;
  int _red;
  int _green;
  int _blue;
};
class Checkerboard : public Filter
{
public:
  virtual void Execute();
  const char *FilterName(){return "Invert";};
};

class CheckSum : public Sink
{
public:
  CheckSum(void);
  virtual void OutputCheckSum(const char*);
  const char *SinkName(){return "CheckSum";};
private:
  unsigned char _red;
  unsigned char _green;
  unsigned char _blue;
};
#endif
