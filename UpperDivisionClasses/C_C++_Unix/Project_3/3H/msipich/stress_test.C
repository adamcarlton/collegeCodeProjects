#include <PNMreader.h>
#include <PNMwriter.h>
//#include <filter.h>
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
    
    Transpose t;
    t.SetInput(reader.GetOutput());
    
    LRConcat lr;
    lr.SetInput(t.GetOutput());
    lr.SetInput2(t.GetOutput());
   
    TBConcat tb;
    tb.SetInput(lr.GetOutput());
    tb.SetInput2(lr.GetOutput());
    
    Invert i;
    i.SetInput(tb.GetOutput());
    
    //Transpose t2;
    //t2.SetInput(i.GetOutput());
   
    // Make the image "finalImage" be the image at 
   
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
