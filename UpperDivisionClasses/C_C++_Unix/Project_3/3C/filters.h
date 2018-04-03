#ifndef FILTERS_H
#define FILTERS_H
#include <source.h>
#include <sink.h>

class Filters : public Source, public Sink
{
};

class Shrinker : public Filters
{
    public:
        virtual void Execute();
};

class LRConcat : public Filters
{
    public:
        virtual void Execute();
};

class TBConcat : public Filters
{
    public:
        virtual void Execute();
};

class Blender : public Filters
{
    private:
        float factor;
    public:
        void SetFactor(float factor);
        float getFactor();
        virtual void Execute();
};

#endif
