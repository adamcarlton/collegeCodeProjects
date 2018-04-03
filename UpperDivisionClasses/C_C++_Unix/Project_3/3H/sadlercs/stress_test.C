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

    /* Make the image "finalImage" be the image at
       the bottom of your pipeline */

    Shrinker s2;
    LRConcat lr1;
    LRConcat lr2;
    LRConcat lr3;
    TBConcat tb1;
    TBConcat tb2;
    Checkerboard  blender;
    
    Crop crop;
    crop.SetRegion(300, 1400, 50, 400);
    
    Transpose t;
    
    Invert i;
    
    Color color(50, 1101, 0, 0, 128);
    
    


    lr1.SetInput(s1.GetOutput());
    lr1.SetInput2(s1.GetOutput());

    tb1.SetInput(lr1.GetOutput());
    tb1.SetInput2(lr1.GetOutput());

    s2.SetInput(tb1.GetOutput());

    lr2.SetInput(s2.GetOutput());
    lr2.SetInput2(s1.GetOutput());

    tb2.SetInput(lr2.GetOutput());
    tb2.SetInput2(lr1.GetOutput());

    blender.SetInput(tb2.GetOutput());
    blender.SetInput2(reader.GetOutput());
    
    crop.SetInput(blender.GetOutput());
    t.SetInput(crop.GetOutput());

    i.SetInput(t.GetOutput());
    
    lr3.SetInput(color.GetOutput());
    lr3.SetInput2(i.GetOutput());
    
    Image *finalImage = lr3.GetOutput();

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
