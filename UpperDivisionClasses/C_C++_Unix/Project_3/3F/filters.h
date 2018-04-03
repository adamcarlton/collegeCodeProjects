#ifndef FILTERS_H
#define FILTERS_H
#include <source.h>
#include <sink.h>
#include <logging.h>
#include <image.h>

class Filters : public Source, public Sink
{
  public:
    virtual void Update();
    virtual const char *FilterName()= 0;
    const char *SourceName(){return FilterName();};
    const char *SinkName(){return FilterName();};
};

class Shrinker : public Filters
{
    public:
        virtual void Execute();
        const char *FilterName(){return "Shrinker";};
};

class LRConcat : public Filters
{
    public:
        virtual void Execute();
        const char *FilterName(){return "LRConcat";};
};

class TBConcat : public Filters
{
    public:
        virtual void Execute();
        const char *FilterName(){return "TBConcat";};
};

class Blender : public Filters
{
    private:
        float factor;
    public:
        void SetFactor(float factor);
        float getFactor();
        virtual void Execute();
        const char *FilterName(){return "Blender";};
};

#endif
