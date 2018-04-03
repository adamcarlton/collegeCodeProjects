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
    Invert i;
    Crop c;
    TBConcat tb;
    LRConcat lr;
    Invert i2;
    LRConcat lr2;
    
    
    s1.SetInput(reader.GetOutput());
    i.SetInput(s1.GetOutput());
    tb.SetInput(s1.GetOutput());
    tb.SetInput2(i.GetOutput());
    lr.SetInput(tb.GetOutput());
    lr.SetInput2(tb.GetOutput());
    i2.SetInput(lr.GetOutput());
    lr2.SetInput(i2.GetOutput());
    lr2.SetInput2(i2.GetOutput());
    

    
    /* Make the image "finalImage" be the image at 
       the bottom of your pipeline */
    Image *finalImage = lr2.GetOutput();

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
