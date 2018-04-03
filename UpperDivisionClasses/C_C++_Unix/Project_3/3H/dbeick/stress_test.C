#include <PNMreader.h>
#include <PNMwriter.h>
#include <filters.h>
#include <logging.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using std::cerr;
using std::endl;
using std::ofstream;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <username>" << endl;
        exit(EXIT_FAILURE);
    }

    char event[1024];
    sprintf(event, "Entered program from %s\n", argv[1]);
    Logger::LogEvent(event);

    /* START STUDENT MODIFIABLE SECTION */

    PNMreader reader("../images/puddles.pnm");
    Shrinker s1;
    s1.SetInput(reader.GetOutput());
   
    Color redBar(893, 50, 128, 0, 0);

    TBConcat tb;
    tb.SetInput(s1.GetOutput());
    tb.SetInput2(redBar.GetOutput());

    Color blueBar(50, 722, 0, 0, 128);

    LRConcat lr;
    lr.SetInput(tb.GetOutput());
    lr.SetInput2(blueBar.GetOutput());

    LRConcat lr2;
    lr2.SetInput(lr.GetOutput());
    lr2.SetInput2(tb.GetOutput());

    Color whiteBar(50, 672, 255, 255, 255);

    LRConcat bottomlr;
    bottomlr.SetInput(s1.GetOutput());
    bottomlr.SetInput2(whiteBar.GetOutput());

    LRConcat bottomlr2;
    bottomlr2.SetInput(bottomlr.GetOutput());
    bottomlr2.SetInput2(s1.GetOutput());

    TBConcat tb2;
    tb2.SetInput(lr2.GetOutput());
    tb2.SetInput2(bottomlr2.GetOutput());
    
    Shrinker s2;
    s2.SetInput(tb2.GetOutput());

    PNMreader reader2("../images/hank.pnm");

    int a = (918 - 326);
    int b = (697 - 484);
    int w1 = (a - a/2);
    int w2 = (918 - a/2);

    int h1 = (b - b/2);
    int h2 = (697 - b/2);

    Crop crop;
    crop.SetRegion(w1, w2-1, h1, h2-1);
    crop.SetInput(s2.GetOutput());

    Checkerboard blender;
    blender.SetInput(crop.GetOutput());
    blender.SetInput2(reader2.GetOutput());
 
    Image *finalImage = blender.GetOutput();

    /* END STUDENT MODIFIABLE SECTION */

    try 
    {
        finalImage->Update();
    }
    catch (DataFlowException &)
    {
        ofstream ofile("my_exception");
        if (ofile.fail())
        {
             cerr << "Something is wrong ... can't open my_exception"
                  << " for opening" << endl;
             exit(EXIT_FAILURE);
        }
        ofile << "Exception found!" << endl;
        exit(EXIT_SUCCESS);
    }

    CheckSum cs;
    cs.SetInput(finalImage);
    cs.OutputCheckSum("my_checksum");

    if (argc == 3)
    {
        PNMwriter writer;
        writer.SetInput(finalImage);
        writer.Write("3H.pnm");
    }
    Logger::Finalize();
}
