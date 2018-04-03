/* this should go in filters.h */
#ifndef CROP_H
#define CROP_H
class Crop : public Filters
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
#endif
