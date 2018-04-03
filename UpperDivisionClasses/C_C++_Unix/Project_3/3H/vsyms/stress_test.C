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
    //set up a pipeline, then make so class can acess it

    PNMreader reader("../images/hank.pnm");

    Shrinker s1;
    Shrinker s2;
    LRConcat lr;
    TBConcat tb;
    Checkerboard bl;

    s1.SetInput(reader.GetOutput());  
    lr.SetInput(s2.GetOutput());
    lr.SetInput(s1.GetOutput()); 
    s1.SetInput(lr.GetOutput());
    lr.SetInput(tb.GetOutput());
    tb.SetInput(bl.GetOutput());


    /* Make the image "finalImage" be the image at 
       the bottom of your pipeline */
    Image *finalImage = lr.GetOutput();

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
