#include "PNMreader.h"
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
    Crop c1;
    Shrinker sh1;
    Shrinker sh2;
    LRConcat lr2;
    TBConcat tb;
    Checkerboard b;
    sh1.SetInput(reader.GetOutput());
    sh2.SetInput(sh1.GetOutput());
    lr2.SetInput(sh2.GetOutput());
    lr2.SetInput2(sh2.GetOutput());
    tb.SetInput(lr2.GetOutput());
    tb.SetInput2(lr2.GetOutput()); 
    b.SetInput(tb.GetOutput());
    b.SetInput2(sh1.GetOutput());

   for(int i = 0; i < 400; i++) {
	c1.SetRegion(300-i, 1400+i, 50+i, 400-i);
	c1.SetInput(reader.GetOutput());
    }

    

    
    /* Make the image "finalImage" be the image at 
       the bottom of your pipeline */
    Image *finalImage = b.GetOutput();

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
