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


    //----------------------region 1------------------
    PNMreader reader1("../images/deschutes.pnm");
    Filter* filterPtrSet1[8];
    Crop c;
    TBConcat tbcSet1[3];
    LRConcat lrcSet1[4];
    filterPtrSet1[0] = &c;
    for(int i=1;i<=3;i++)
        filterPtrSet1[i] = &tbcSet1[i-1];
    for(int i=4;i<=7;i++)
        filterPtrSet1[i] = &lrcSet1[i-4];
    int startx1 = 130;
    int starty1 = 353;
    ((Crop*)filterPtrSet1[0])->SetInput(reader1.GetOutput());
    ((Crop*)filterPtrSet1[0])->SetRegion(startx1,startx1+50,starty1,starty1+12);
    for(int i=1;i<=7;i++){
        filterPtrSet1[i]->SetInput(filterPtrSet1[i-1]->GetOutput());
        filterPtrSet1[i]->SetInput2(filterPtrSet1[i-1]->GetOutput());
    }


    //----------------------region 2------------------
    PNMreader reader2("../images/deschutes.pnm");
    Filter* filterPtrSet2[8];
    Crop c2;
    TBConcat tbcSet2[3];
    LRConcat lrcSet2[4];
    filterPtrSet2[0] = &c2;
    for(int i=1;i<=3;i++)
        filterPtrSet2[i] = &tbcSet2[i-1];
    for(int i=4;i<=7;i++)
        filterPtrSet2[i] = &lrcSet2[i-4];
    int startx2 = 450;
    int starty2 = 155;
    ((Crop*)filterPtrSet2[0])->SetInput(reader2.GetOutput());
    ((Crop*)filterPtrSet2[0])->SetRegion(startx2,startx2+50,starty2,starty2+12);
    for(int i=1;i<=7;i++){
        filterPtrSet2[i]->SetInput(filterPtrSet2[i-1]->GetOutput());
        filterPtrSet2[i]->SetInput2(filterPtrSet2[i-1]->GetOutput());
    }


    //----------------------tux------------------
    PNMreader reader3("../images/tux.pnm");
    Color color1(83,438,255,255,255);
    LRConcat lrc1;
    lrc1.SetInput(color1.GetOutput());
    lrc1.SetInput2(reader3.GetOutput());
    LRConcat lrc2;
    lrc2.SetInput(lrc1.GetOutput());
    lrc2.SetInput2(color1.GetOutput());

    Color color2(691,5,255,255,255);
    TBConcat tbc1;
    tbc1.SetInput(color2.GetOutput());
    tbc1.SetInput2(lrc2.GetOutput());        //tbc1:tux has the same size as gnu


    //----------------------gun + tux------------------
    PNMreader reader4("../images/gnu.pnm");
    LRConcat lrc3;
    lrc3.SetInput(reader4.GetOutput());
    lrc3.SetInput2(reader4.GetOutput());
    LRConcat lrc4;
    lrc4.SetInput(tbc1.GetOutput());
    lrc4.SetInput2(tbc1.GetOutput());
    LRConcat lrc5;
    lrc5.SetInput(lrc3.GetOutput());
    lrc5.SetInput2(lrc4.GetOutput());
    Shrinker s1;
    s1.SetInput(lrc5.GetOutput());

    //----------------------region1 and  region2------------------ 1382/2 = 691 (1382*221)
    TBConcat tbc2;
    tbc2.SetInput(filterPtrSet1[7]->GetOutput());
    tbc2.SetInput2(filterPtrSet1[7]->GetOutput());
    TBConcat tbc3;
    tbc3.SetInput(filterPtrSet1[7]->GetOutput());
    tbc3.SetInput2(tbc2.GetOutput());
    Crop c3;
    c3.SetInput(tbc3.GetOutput());
    c3.SetRegion(0,690,0,220);              //region 1

    TBConcat tbc4;
    tbc4.SetInput(filterPtrSet2[7]->GetOutput());
    tbc4.SetInput2(filterPtrSet2[7]->GetOutput());
    TBConcat tbc5;
    tbc5.SetInput(filterPtrSet2[7]->GetOutput());
    tbc5.SetInput2(tbc4.GetOutput());
    Crop c4;
    c4.SetInput(tbc5.GetOutput());
    c4.SetRegion(0,690,0,220);              //region 2

    Color color3(691,221,255,255,255);
    Checkerboard b1;
    b1.SetInput(c4.GetOutput());
    b1.SetInput2(color3.GetOutput());       //region 2 after blending


    //----------------------(region 1  + region 2) + (tux + gnu)------------------

    LRConcat lrc6;
    lrc6.SetInput(c3.GetOutput());
    lrc6.SetInput2(b1.GetOutput());
    TBConcat tbc6;
    tbc6.SetInput(s1.GetOutput());
    tbc6.SetInput2(lrc6.GetOutput());


    /* Make the image "finalImage" be the image at
       the bottom of your pipeline */
    Image *finalImage = tbc6.GetOutput();

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
