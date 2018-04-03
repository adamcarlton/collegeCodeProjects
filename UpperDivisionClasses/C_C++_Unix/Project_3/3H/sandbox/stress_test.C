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
    PNMreader reader("../images/hank.pnm");
    PNMreader reader1("../images/deschutes.pnm");
    PNMreader reader2("../images/gnu.pnm");
    Shrinker s1;
    Shrinker s2;
    Crop c1;
    Crop c2;
    LRConcat lr;
    TBConcat tb;
    Checkerboard  b;
    Invert i;
    
    s1.SetInput(reader1.GetOutput());
    
    
    c1.SetRegion(0, 300, 0, 197);
    c1.SetInput(reader.GetOutput());
    
    lr.SetInput(s1.GetOutput());
    lr.SetInput2(c1.GetOutput());
    
    tb.SetInput(lr.GetOutput());
    tb.SetInput2(lr.GetOutput());
    
    s2.SetInput(tb.GetOutput());
    
    c2.SetRegion(30, 329, 30, 227);
    c2.SetInput(reader2.GetOutput());
    
    b.SetInput(s2.GetOutput());
    b.SetInput2(c2.GetOutput());
    
    i.SetInput(b.GetOutput());
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
