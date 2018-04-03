#include <PNMreader.h>
#include <PNMwriter.h>
#include <filters.h>

int main(int argc, char *argv[])
{
    PNMreader reader(argv[1]);
    PNMwriter writer;
    Shrinker shrinker1;
    Shrinker shrinker2;
    LRConcat lrconcat1;
    LRConcat lrconcat2;
    TBConcat tbconcat1;
    TBConcat tbconcat2;
    Blender  blender;
    blender.SetFactor(0.8);

    shrinker1.SetInput(reader.GetOutput());

    lrconcat1.SetInput(shrinker1.GetOutput());
    lrconcat1.SetInput2(shrinker1.GetOutput());

    tbconcat1.SetInput(lrconcat1.GetOutput());
    tbconcat1.SetInput2(lrconcat1.GetOutput());

    shrinker2.SetInput(tbconcat1.GetOutput());

    lrconcat2.SetInput(shrinker2.GetOutput());
    lrconcat2.SetInput2(shrinker1.GetOutput());

    tbconcat2.SetInput(lrconcat2.GetOutput());
    tbconcat2.SetInput2(lrconcat1.GetOutput());

    blender.SetInput(tbconcat2.GetOutput());
    blender.SetInput2(reader.GetOutput());

    writer.SetInput(blender.GetOutput());

    blender.GetOutput()->Update();
    writer.Write(argv[2]);
}
