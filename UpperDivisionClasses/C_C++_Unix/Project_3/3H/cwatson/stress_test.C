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

    Color bigred1(1000, 50, 128, 0, 0);
    Color bigred2(1000, 50, 128, 0, 0);
    Color bigred3(1000, 50, 128, 0, 0);
    Color bigred4(1000, 50, 128, 0, 0);

    Color bigwhite1(1000, 50, 255, 255, 255);
    Color bigwhite2(1000, 50, 255, 255, 255);
    Color bigwhite3(1000, 50, 255, 255, 255);

    Color smallred1(600, 50, 128, 0, 0);
    Color smallred2(600, 50, 128, 0, 0);
    Color smallred3(600, 50, 128, 0, 0);
    Color smallred4(600, 50, 128, 0, 0);

    Color smallwhite1(600, 50, 255, 255, 255);
    Color smallwhite2(600, 50, 255, 255, 255);
    Color smallwhite3(600, 50, 255, 255, 255);
    Color smallwhite4(600, 50, 255, 255, 255);
    

    Color blue(400, 400, 0, 0, 128);

    TBConcat firstSeg;
    firstSeg.SetInput(smallred1.GetOutput());
    firstSeg.SetInput2(smallwhite1.GetOutput());

    TBConcat secondSeg;
    secondSeg.SetInput(smallred2.GetOutput());
    secondSeg.SetInput2(smallwhite2.GetOutput());

    TBConcat thirdSeg;
    thirdSeg.SetInput(smallred3.GetOutput());
    thirdSeg.SetInput2(smallwhite3.GetOutput());

    TBConcat fourthSeg;
    fourthSeg.SetInput(smallred4.GetOutput());
    fourthSeg.SetInput2(smallwhite4.GetOutput());

    TBConcat smallCombine1;
    smallCombine1.SetInput(firstSeg.GetOutput());
    smallCombine1.SetInput2(secondSeg.GetOutput());

    TBConcat smallCombine2;
    smallCombine2.SetInput(thirdSeg.GetOutput());
    smallCombine2.SetInput2(fourthSeg.GetOutput());

    TBConcat smallCombine3;
    smallCombine3.SetInput(smallCombine1.GetOutput());
    smallCombine3.SetInput2(smallCombine2.GetOutput());

    LRConcat lr;
    lr.SetInput(blue.GetOutput());
    lr.SetInput2(smallCombine3.GetOutput());

    TBConcat bigSeg1;
    bigSeg1.SetInput(bigred1.GetOutput());
    bigSeg1.SetInput2(bigwhite1.GetOutput());

    TBConcat bigSeg2;
    bigSeg2.SetInput(bigred2.GetOutput());
    bigSeg2.SetInput2(bigwhite2.GetOutput());

    TBConcat bigSeg3;
    bigSeg3.SetInput(bigred3.GetOutput());
    bigSeg3.SetInput2(bigwhite3.GetOutput());

    TBConcat bigSeg4;
    bigSeg4.SetInput(bigSeg3.GetOutput());
    bigSeg4.SetInput2(bigred4.GetOutput());

    TBConcat bigSeg5;
    bigSeg5.SetInput(bigSeg1.GetOutput());
    bigSeg5.SetInput2(bigSeg2.GetOutput());

    TBConcat finalBottomSeg;
    finalBottomSeg.SetInput(bigSeg5.GetOutput());
    finalBottomSeg.SetInput2(bigSeg4.GetOutput());

    TBConcat flag;
    flag.SetInput(lr.GetOutput());
    flag.SetInput2(finalBottomSeg.GetOutput());
    
    /* Make the image "finalImage" be the image at 
       the bottom of your pipeline */
    Image *finalImage = flag.GetOutput();

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
