#include <PNMreader.h>
#include <PNMwriter.h>
#include <filters.h>

int main(int argc, char *argv[])
{
    PNMreader reader(argv[1]);

    Color red(2000, 2000, 255, 0, 0);

    Color blue(2000, 2000, 0, 0, 255);

    Blender b;
    b.SetFactor(0.5);
    b.SetInput(red.GetOutput());
    b.SetInput2(blue.GetOutput());

    b.GetOutput()->Update();

    PNMwriter writer;
    writer.SetInput(b.GetOutput());
    writer.Write(argv[2]);
}
