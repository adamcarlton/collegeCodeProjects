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

    PNMreader hank("../images/hank.pnm");
    PNMreader tux("../images/tux.pnm");
    PNMreader puddles("../images/puddles.pnm");

    Crop hank_crop;
    hank_crop.SetRegion(0, 325, 0, 399);
    Crop tux_crop;
    tux_crop.SetRegion(100, 425, 0, 437);
    TBConcat fancy_hank;
    LRConcat double_fancy;

    hank_crop.SetInput(hank.GetOutput());
    tux_crop.SetInput(tux.GetOutput());
    
    fancy_hank.SetInput(hank_crop.GetOutput());
    fancy_hank.SetInput2(tux_crop.GetOutput());
    
    double_fancy.SetInput(fancy_hank.GetOutput());
    double_fancy.SetInput2(fancy_hank.GetOutput());
    
    
    /* Make the image "finalImage" be the image at 
       the bottom of your pipeline */
    Image *finalImage = double_fancy.GetOutput();

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
