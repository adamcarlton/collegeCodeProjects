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
    Shrinker s;
    s.SetInput(reader.GetOutput());
    
    Color color(50, 1101, 0, 0, 128);
    
    LRConcat lr;
    lr.SetInput(s.GetOutput());
    lr.SetInput2(s.GetOutput());

    TBConcat tb;
    tb.SetInput(lr.GetOutput());
    tb.SetInput2(lr.GetOutput());


    Checkerboard blender;
    blender.SetInput(tb.GetOutput());
    blender.SetInput2(reader.GetOutput());

    Crop crop;
    crop.SetRegion(300, 1400, 50, 400);
    crop.SetInput(blender.GetOutput());

    Transpose t;  
    t.SetInput(crop.GetOutput());
  
    Invert i;
    i.SetInput(t.GetOutput());


    /* Make the image "finalImage" be the image at
   the bottom of your pipeline */

    Image *finalImage = i.GetOutput();

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
