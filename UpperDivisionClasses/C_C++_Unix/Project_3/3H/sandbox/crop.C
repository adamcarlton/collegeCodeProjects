#include<crop.h>
void
Crop::Execute(void)
{
    OneInputCheck();
    if (Istart < 0 || Istop < 0 || Jstart < 0 || Jstop < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: uninitialized region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istart >= input->GetWidth() || Istop >= input->GetWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image width", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Jstart >= input->GetHeight() || Jstop >= input->GetHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image height", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istop < Istart || Jstop < Jstart)
    {
        char msg[1024];
        sprintf(msg, "%s: invalid region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }

    int height = Jstop-Jstart+1;
    int width  = Istop-Istart+1;
    int inputWidth = input->GetWidth();
    output.SetSize(width, height);
    output.SetBuffer(width, height);
    unsigned char *buffer = output.GetBuffer();
    const unsigned char *buffer1 = input->GetBuffer();
    for (int i = Istart ; i <= Istop ; i++)
        for (int j = Jstart ; j <= Jstop ; j++)
        {
            int idx1 = j*inputWidth+i;
            int idx  = (j-Jstart)*width+(i-Istart);
            buffer[3*idx]   = buffer1[3*idx1];
            buffer[3*idx+1] = buffer1[3*idx1+1];
            buffer[3*idx+2] = buffer1[3*idx1+2];
        }
}
