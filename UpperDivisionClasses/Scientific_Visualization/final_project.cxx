#include <stdlib.h>
#include <iostream>
#include <vtkDataSetReader.h>
#include <vtkRectilinearGrid.h>
#include <vtkDataSet.h>
#include <vtkDataArray.h>
#include <vtkPointData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <math.h>

#define numSamples 512
#define sampleRate 500.0

using namespace std;

struct Color 
{
   unsigned char colorsList[numSamples][3];
   double opacityList[numSamples];
};

struct Ray
{
    double rd[3];
};

struct Samples
{
    float sampleList[numSamples];
};

struct Camera
{
    double          near, far;
    double          angle;
    double          position[3];
    double          focus[3];
    double          up[3];
};


struct TransferFunction
{
    double          min;
    double          max;
    int             numBins;
    unsigned char  *colors;  // size is 3*numBins
    double         *opacities; // size is numBins

    // Take in a value and applies the transfer function.
    // Step #1: figure out which bin "value" lies in.
    // If "min" is 2 and "max" is 4, and there are 10 bins, then
    //   bin 0 = 2->2.2
    //   bin 1 = 2.2->2.4
    //   bin 2 = 2.4->2.6
    //   bin 3 = 2.6->2.8
    //   bin 4 = 2.8->3.0
    //   bin 5 = 3.0->3.2
    //   bin 6 = 3.2->3.4
    //   bin 7 = 3.4->3.6
    //   bin 8 = 3.6->3.8
    //   bin 9 = 3.8->4.0
    // and, for example, a "value" of 3.15 would return the color in bin 5
    // and the opacity at "opacities[5]".
    int 
    GetBin(double value)
    {
        float minMaxDiff = max - min;
        float binStepSize = minMaxDiff / numBins;
        int binNum = floor((value - min) / binStepSize);
        
        return binNum;
    }

    void 
    ApplyTransferFunction(double value, unsigned char *RGB, double &opacity)
    {
        int bin = GetBin(value);
        if(bin < 0 || bin >= numBins)
        {
            RGB[0] = 0;
            RGB[1] = 0;
            RGB[2] = 0;
            opacity = 0;
            return;
        }
        RGB[0] = colors[3*bin+0];
        RGB[1] = colors[3*bin+1];
        RGB[2] = colors[3*bin+2];
        opacity = opacities[bin];
    }
};

// ****************************************************************************
//  Function: GetPointIndex
//
//  Arguments:
//      idx:  the logical index of a point.
//              0 <= idx[0] < dims[0]
//              1 <= idx[1] < dims[1]
//              2 <= idx[2] < dims[2] (or always 0 if 2D)
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  the point index
//
// ****************************************************************************

int 
GetPointIndex(const int *idx, const int *dims)
{
    return idx[2] * dims[0] * dims[1] + idx[1] * dims[0] + idx[0];
}

TransferFunction
SetupTransferFunction(void)
{
    int i;

    TransferFunction rv;
    rv.min = 10;
    rv.max = 15;
    rv.numBins = 256;
    rv.colors = new unsigned char[3 * 256];
    rv.opacities = new double[256];
    unsigned char charOpacity[256] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 13, 14, 14, 14, 14, 14, 14, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 5, 4, 3, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 17, 17, 17, 17, 17, 17, 16, 16, 15, 14, 13, 12, 11, 9, 8, 7, 6, 5, 5, 4, 3, 3, 3, 4, 5, 6, 7, 8, 9, 11, 12, 14, 16, 18, 20, 22, 24, 27, 29, 32, 35, 38, 41, 44, 47, 50, 52, 55, 58, 60, 62, 64, 66, 67, 68, 69, 70, 70, 70, 69, 68, 67, 66, 64, 62, 60, 58, 55, 52, 50, 47, 44, 41, 38, 35, 32, 29, 27, 24, 22, 20, 20, 23, 28, 33, 38, 45, 51, 59, 67, 76, 85, 95, 105, 116, 127, 138, 149, 160, 170, 180, 189, 198, 205, 212, 217, 221, 223, 224, 224, 222, 219, 214, 208, 201, 193, 184, 174, 164, 153, 142, 131, 120, 109, 99, 89, 79, 70, 62, 54, 47, 40, 35, 30, 25, 21, 17, 14, 12, 10, 8, 6, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (i = 0; i < 256; i++)
        rv.opacities[i] = charOpacity[i] / 255.0;
    const int numControlPoints = 8;
    unsigned char controlPointColors[numControlPoints * 3] = {
        71, 71, 219, 0, 0, 91, 0, 255, 255, 0, 127, 0,
        255, 255, 0, 255, 96, 0, 107, 0, 0, 224, 76, 76};
    double controlPointPositions[numControlPoints] = {0, 0.143, 0.285, 0.429, 0.571, 0.714, 0.857, 1.0};
    for (i = 0; i < numControlPoints - 1; i++)
    {
        int start = controlPointPositions[i] * rv.numBins;
        int end = controlPointPositions[i + 1] * rv.numBins + 1;
        if (end >= rv.numBins)
            end = rv.numBins - 1;
        for (int j = start; j <= end; j++)
        {
            double proportion = (j / (rv.numBins - 1.0) - controlPointPositions[i]) / (controlPointPositions[i + 1] - controlPointPositions[i]);
            if (proportion < 0 || proportion > 1.)
                continue;
            for (int k = 0; k < 3; k++)
                rv.colors[3 * j + k] = proportion * (controlPointColors[3 * (i + 1) + k] - controlPointColors[3 * i + k]) + controlPointColors[3 * i + k];
        }
    }

    return rv;
}

Camera
SetupCamera(void)
{
    Camera rv;
    rv.focus[0] = 0;
    rv.focus[1] = 0;
    rv.focus[2] = 0;
    rv.up[0] = 0;
    rv.up[1] = -1;
    rv.up[2] = 0;
    rv.angle = 30;
    rv.near = 7.5e+7;
    rv.far = 1.4e+8;
    rv.position[0] = -8.25e+7;
    rv.position[1] = -3.45e+7;
    rv.position[2] = 3.35e+7;

    return rv;
}
double 
EvaluateFieldAtLocation(const double *pt, const int *dims, const float *X, const float *Y, const float *Z, const float *F)
{

    if (pt[0] < X[0] || pt[1] < Y[0] || pt[2] < Z[0] ||  pt[0] > X[dims[0] - 1] || pt[1] > Y[dims[1] - 1] || pt[2] > Z[dims[2] - 1])
    {
        return 0;
    }
    int i;
    int lowestX = -1;
    int lowestY = -1;
    int lowestZ = -1;
    for (i = 1; i < dims[0]; i++)
    {
        if (pt[0] >= X[i - 1] && pt[0] <= X[i])
        {
            lowestX = i - 1;
            break;
        }
    }
    for (i = 1; i < dims[1]; i++)
    {
        if (pt[1] >= Y[i - 1] && pt[1] <= Y[i])
        {
            lowestY = i - 1;
            break;
        }
    }
    for (i = 1; i < dims[2]; i++)
    {
        if (pt[2] >= Z[i - 1] && pt[2] <= Z[i])
        {
            lowestZ = i - 1;
            break;
        }
    }

    int corner0[3] = {lowestX, lowestY, lowestZ};
    int corner1[3] = {lowestX + 1, lowestY, lowestZ};
    int corner2[3] = {lowestX, lowestY + 1, lowestZ};
    int corner3[3] = {lowestX + 1, lowestY + 1, lowestZ};
    int corner4[3] = {lowestX, lowestY, lowestZ + 1};
    int corner5[3] = {lowestX + 1, lowestY, lowestZ + 1};
    int corner6[3] = {lowestX, lowestY + 1, lowestZ + 1};
    int corner7[3] = {lowestX + 1, lowestY + 1, lowestZ + 1};
    
    int corner0pt = GetPointIndex(corner0, dims);
    int corner1pt = GetPointIndex(corner1, dims);
    int corner2pt = GetPointIndex(corner2, dims);
    int corner3pt = GetPointIndex(corner3, dims);
    int corner4pt = GetPointIndex(corner4, dims);
    int corner5pt = GetPointIndex(corner5, dims);
    int corner6pt = GetPointIndex(corner6, dims);
    int corner7pt = GetPointIndex(corner7, dims);

    double frontBottomInterp = F[corner0pt] + ((pt[0] - X[lowestX]) / (X[lowestX + 1] - X[lowestX])) * (F[corner1pt] - F[corner0pt]);
    double backBottomInterp = F[corner4pt] + ((pt[0] - X[lowestX]) / (X[lowestX + 1] - X[lowestX])) * (F[corner5pt] - F[corner4pt]);
    
    double finalBottomInterp = frontBottomInterp + ((pt[2] - Z[lowestZ]) / (Z[lowestZ + 1] - Z[lowestZ])) * (backBottomInterp - frontBottomInterp);
    
    double frontTopInterp = F[corner2pt] + ((pt[0] - X[lowestX]) / (X[lowestX + 1] - X[lowestX])) * (F[corner3pt] - F[corner2pt]);
    double backTopInterp = F[corner6pt] + ((pt[0] - X[lowestX]) / (X[lowestX + 1] - X[lowestX])) * (F[corner7pt] - F[corner6pt]);
   
    double finalTopInterp = frontTopInterp + ((pt[2] - Z[lowestZ]) / (Z[lowestZ + 1] - Z[lowestZ])) * (backTopInterp - frontTopInterp);

    double finalInterp = finalBottomInterp + ((pt[1] - Y[lowestY]) / (Y[lowestY + 1] - Y[lowestY])) * (finalTopInterp - finalBottomInterp);
   
    
    return finalInterp;
}
Ray 
GetRay(Camera cam, int I, int J, int W, int H)
{
    Ray r;
    
    double look[3];
    look[0] = cam.focus[0] - cam.position[0];
    look[1] = cam.focus[1] - cam.position[1];
    look[2] = cam.focus[2] - cam.position[2];

    double ru[3];
    ru[0] = (look[1] * cam.up[2]) - (look[2] * cam.up[1]);
    ru[1] = (look[2] * cam.up[0]) - (look[0] * cam.up[2]);
    ru[2] = (look[0] * cam.up[1]) - (look[1] * cam.up[0]);

    double ruNorm = sqrt(ru[0] * ru[0] + ru[1] * ru[1] + ru[2] * ru[2]);
    ru[0] /= ruNorm;
    ru[1] /= ruNorm;
    ru[2] /= ruNorm;
        
    double rv[3];
    rv[0] = ((look[1] * ru[2]) - (look[2] * ru[1]));
    rv[1] = ((look[2] * ru[0]) - (look[0] * ru[2]));
    rv[2] = ((look[0] * ru[1]) - (look[1] * ru[0]));

    double rvNorm = sqrt(rv[0] * rv[0] + rv[1] * rv[1] + rv[2] * rv[2]);

    rv[0] /= rvNorm;
    rv[1] /= rvNorm;
    rv[2] /= rvNorm;

    double tangent = tan((cam.angle / 2.0) * (M_PI / 180.0));
    double scalarForRu = (2.0 * tangent) / W;
    double scalarForRv = (2.0 * tangent) / H;
    
    double deltaX[3];
    deltaX[0] = scalarForRu * ru[0];
    deltaX[1] = scalarForRu * ru[1];
    deltaX[2] = scalarForRu * ru[2];

    double deltaY[3];
    deltaY[0] = scalarForRv * rv[0];
    deltaY[1] = scalarForRv * rv[1];
    deltaY[2] = scalarForRv * rv[2];

    double lookNorm = sqrt(look[0] * look[0] + look[1] * look[1] + look[2] * look[2]);

    double normalizedLook[3];
    normalizedLook[0] = look[0] / lookNorm;
    normalizedLook[1] = look[1] / lookNorm;
    normalizedLook[2] = look[2] / lookNorm;

    double scalarForDeltaX = (2.0 * I + 1.0 - W) / 2.0;
    double scalarForDeltaY = (2.0 * J + 1.0 - H) / 2.0;
    
    r.rd[0] = normalizedLook[0] + (scalarForDeltaX * deltaX[0]) + (scalarForDeltaY * deltaY[0]);
    r.rd[1] = normalizedLook[1] + (scalarForDeltaX * deltaX[1]) + (scalarForDeltaY * deltaY[1]);
    r.rd[2] = normalizedLook[2] + (scalarForDeltaX * deltaX[2]) + (scalarForDeltaY * deltaY[2]);

    return r;
}

Samples
CalculateSamplesAlongRay(Ray r, Camera cam, const int *dims, const float *X, const float *Y, const float *Z, const float *F)
{
    Samples s;
    double xDir = r.rd[0];
    double yDir = r.rd[1];
    double zDir = r.rd[2];
    
    double nearFarDiff = cam.far - cam.near;
    double stepSize = nearFarDiff/((double)numSamples - 1.0);

    double currentPos[3] = {cam.position[0] + xDir * cam.near, cam.position[1] + yDir * cam.near, cam.position[2] + zDir * cam.near};

    for(int i = 0; i < numSamples; ++i)
    {
        // cerr << "Position for sample[" << i << "] = " << currentPos[0] << ", " << currentPos[1] << ", " << currentPos[2] << endl;
        s.sampleList[i] = EvaluateFieldAtLocation(currentPos, dims, X, Y, Z, F);
        // cerr << "Value at that position is " << s.sampleList[i] << endl;
        currentPos[0] += stepSize * xDir;
        currentPos[1] += stepSize * yDir;
        currentPos[2] += stepSize * zDir;
    }
    
    return s;
}

void
CalculateColor(Color c, unsigned char * pixelBuffer)
{
    double Fr = c.colorsList[0][0] / 255.0;
    double Fg = c.colorsList[0][1] / 255.0;
    double Fb = c.colorsList[0][2] / 255.0;
    double Fa = c.opacityList[0];
    
    double Br = 0.0;
    double Bg = 0.0;
    double Bb = 0.0;
    double Ba = 0.0;

    double oldOr = (Fa * Fr) + (1.0 - Fa) * Ba * Br;
    double oldOg = (Fa * Fg) + (1.0 - Fa) * Ba * Bg;
    double oldOb = (Fa * Fb) + (1.0 - Fb) * Ba * Bb;
    double oldOa = Fa + (1.0 - Fa) * Ba;

    // cerr << "After compositing sample 0, the running values are R:" << oldOr << ", G:" << oldOg << ", B:" << oldOb << ", A:" << oldOa << endl;

    double newOr = 0.0;
    double newOg = 0.0;
    double newOb = 0.0;
    double newOa = 0.0;

    for(int i = 1; i < numSamples; ++i)
    {
        Br = c.colorsList[i][0] / 255.0;
        Bg = c.colorsList[i][1] / 255.0;
        Bb = c.colorsList[i][2] / 255.0;
        Ba = c.opacityList[i];

        newOr = oldOr + (1.0 - oldOa) * Ba * Br;
        newOg = oldOg + (1.0 - oldOa) * Ba * Bg;
        newOb = oldOb + (1.0 - oldOa) * Ba * Bb;
        newOa = oldOa + (1.0 - oldOa) * Ba;

        oldOr = newOr;
        oldOg = newOg;
        oldOb = newOb;
        oldOa = newOa;
        // cerr << "After compositing sample " << i << ", the running values are R:" << oldOr << ", G:" << oldOg << ", B:" << oldOb << ", A:" << oldOa << endl;
    }
    
    pixelBuffer[0] = oldOr*255.0;
    pixelBuffer[1] = oldOg*255.0;
    pixelBuffer[2] = oldOb*255.0;

    // cerr << "Final color for pixel is " << (double)pixelBuffer[0] << ", " << (double)pixelBuffer[1] << ", " << (double)pixelBuffer[2] << endl;
    
    return;    
}

void WriteImage(vtkImageData *img, const char *filename)
{
    std::string full_filename = filename;
    full_filename += ".png";
    vtkPNGWriter *writer = vtkPNGWriter::New();
    writer->SetInputData(img);
    writer->SetFileName(full_filename.c_str());
    writer->Write();
    writer->Delete();
}

vtkImageData *
NewImage(int width, int height)
{
    vtkImageData *image = vtkImageData::New();
    image->SetDimensions(width, height, 1);
    //image->SetWholeExtent(0, width-1, 0, height-1, 0, 0);
    //image->SetUpdateExtent(0, width-1, 0, height-1, 0, 0);
    //image->SetNumberOfScalarComponents(3);
    image->AllocateScalars(VTK_UNSIGNED_CHAR, 3);
    //image->AllocateScalars();

    return image;
}

int 
main()
{
    vtkDataSetReader *rdr = vtkDataSetReader::New();
    // rdr->SetFileName("astro512.vtk");
    rdr->SetFileName("astro64.vtk");
    rdr->Update();

    int dims[3];
    vtkRectilinearGrid *rgrid = (vtkRectilinearGrid *)rdr->GetOutput();
    rgrid->GetDimensions(dims);

    float *X = (float *)rgrid->GetXCoordinates()->GetVoidPointer(0);
    float *Y = (float *)rgrid->GetYCoordinates()->GetVoidPointer(0);
    float *Z = (float *)rgrid->GetZCoordinates()->GetVoidPointer(0);

    float *F = (float *)rgrid->GetPointData()->GetScalars()->GetVoidPointer(0);
    
    TransferFunction tf = SetupTransferFunction();
    Camera cam = SetupCamera();
    
    double opacity = 0.0;
    int imgWidth = 512;
    int imgHeight = 512;
    // int imgWidth = 256;
    // int imgHeight = 256;
    vtkImageData *image = NewImage(imgWidth, imgHeight);
    unsigned char *buffer = (unsigned char *)image->GetScalarPointer(0,0,0);
    for(int i = 0 ; i < 3 * imgWidth * imgHeight; ++i)
    {
        buffer[i] = 0;
    }
    double correctOpacity = 0.0;
    for (int i = 0; i < imgWidth; ++i)
    {
        cerr << "row: " << i << endl;
        for(int j = 0; j < imgHeight; ++j)
        {
            Ray r = GetRay(cam, i, j, imgWidth, imgHeight);
            Samples s = CalculateSamplesAlongRay(r, cam, dims, X, Y, Z, F);
            Color c;
            for(int k = 0; k < numSamples; ++k)
            {
                unsigned char RGB[3];
                tf.ApplyTransferFunction(s.sampleList[k], RGB, opacity);
                correctOpacity = 1.0 - pow((1.0 - opacity), (sampleRate / (double) numSamples));
                c.colorsList[k][0] = RGB[0];
                c.colorsList[k][1] = RGB[1];
                c.colorsList[k][2] = RGB[2];
                c.opacityList[k] = correctOpacity;
            }
            int offset = 3 * (j * imgWidth + i);
            CalculateColor(c, buffer + offset);

        }
    }
    WriteImage(image, "acarltonAstro");

    return 0;
}
 
