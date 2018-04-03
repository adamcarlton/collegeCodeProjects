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
    PNMreader r2("../images/hank.pnm");
    PNMreader r3("../images/tux.pnm");
    Shrinker s1;
    s1.SetInput(reader.GetOutput());
    Transpose t;
    t.SetInput(s1.GetOutput());
    Color c(500, 1100, 0, 255, 0);
    Checkerboard b;
    b.SetInput(t.GetOutput());
    b.SetInput2(c.GetOutput());
    LRConcat lr;
    lr.SetInput(b.GetOutput());
    lr.SetInput2(r2.GetOutput());
    TBConcat tb;
    tb.SetInput(lr.GetOutput());
    tb.SetInput2(r3.GetOutput());
    
    /* Make the image "finalImage" be the image at 
       the bottom of your pipeline */
    Image *finalImage = tb.GetOutput();

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
